#include "application_ui.h"
#include "SDL2_gfxPrimitives.h"
#include <vector>
#include <list>
#include <map>
#include <queue>
#include <algorithm>

#include <iostream>
using namespace std;

#define EPSILON 0.0001f

struct Coords
{
    int x, y;

    bool operator==(const Coords& other)
    {
        return x == other.x and y == other.y;
    }
};

struct Segment
{
    Coords p1, p2;
};

struct Triangle
{
    Coords p1, p2, p3;
    bool complet=false;
};

struct Polygone
{
    Sint16 vx[20];
    Sint16 vy[20];
    int number;
    int colour[3];
};

struct Application
{
    int width, height;
    Coords focus{100, 100};

    std::vector<Coords> points;
    std::vector<Triangle> triangles;
};

bool compareCoords(Coords point1, Coords point2)
{
    if (point1.y == point2.y)
        return point1.x < point2.x;
    return point1.y < point2.y;
}

void drawPoints(SDL_Renderer *renderer, const std::vector<Coords> &points)
{
    for (std::size_t i = 0; i < points.size(); i++)
    {
        filledCircleRGBA(renderer, points[i].x, points[i].y, 3, 240, 240, 23, SDL_ALPHA_OPAQUE);
    }
}

void drawSegments(SDL_Renderer *renderer, const std::vector<Segment> &segments)
{
    for (std::size_t i = 0; i < segments.size(); i++)
    {
        lineRGBA(
            renderer,
            segments[i].p1.x, segments[i].p1.y,
            segments[i].p2.x, segments[i].p2.y,
            240, 240, 20, SDL_ALPHA_OPAQUE);
    }
}

void drawTriangles(SDL_Renderer *renderer, const std::vector<Triangle> &triangles)
{
    for (std::size_t i = 0; i < triangles.size(); i++)
    {
        const Triangle& t = triangles[i];
        trigonRGBA(
            renderer,
            t.p1.x, t.p1.y,
            t.p2.x, t.p2.y,
            t.p3.x, t.p3.y,
            0, 240, 160, SDL_ALPHA_OPAQUE
        );
    }
}

void drawPolygones(SDL_Renderer *renderer, const std::vector<Polygone> &polygones)
{
}

void draw(SDL_Renderer *renderer, const Application &app)
{
    /* Remplissez cette fonction pour faire l'affichage du jeu */
    int width, height;
    SDL_GetRendererOutputSize(renderer, &width, &height);

    drawPoints(renderer, app.points);
    drawTriangles(renderer, app.triangles);
}

/*
   Détermine si un point se trouve dans un cercle définit par trois points
   Retourne, par les paramètres, le centre et le rayon
*/
bool CircumCircle(
    float pX, float pY,
    float x1, float y1, float x2, float y2, float x3, float y3,
    float *xc, float *yc, float *rsqr
)
{
    float m1, m2, mx1, mx2, my1, my2;
    float dx, dy, drsqr;
    float fabsy1y2 = fabs(y1 - y2);
    float fabsy2y3 = fabs(y2 - y3);

    /* Check for coincident points */
    if (fabsy1y2 < EPSILON && fabsy2y3 < EPSILON)
        return (false);

    if (fabsy1y2 < EPSILON)
    {
        m2 = -(x3 - x2) / (y3 - y2);
        mx2 = (x2 + x3) / 2.0;
        my2 = (y2 + y3) / 2.0;
        *xc = (x2 + x1) / 2.0;
        *yc = m2 * (*xc - mx2) + my2;
    }
    else if (fabsy2y3 < EPSILON)
    {
        m1 = -(x2 - x1) / (y2 - y1);
        mx1 = (x1 + x2) / 2.0;
        my1 = (y1 + y2) / 2.0;
        *xc = (x3 + x2) / 2.0;
        *yc = m1 * (*xc - mx1) + my1;
    }
    else
    {
        m1 = -(x2 - x1) / (y2 - y1);
        m2 = -(x3 - x2) / (y3 - y2);
        mx1 = (x1 + x2) / 2.0;
        mx2 = (x2 + x3) / 2.0;
        my1 = (y1 + y2) / 2.0;
        my2 = (y2 + y3) / 2.0;
        *xc = (m1 * mx1 - m2 * mx2 + my2 - my1) / (m1 - m2);
        if (fabsy1y2 > fabsy2y3)
        {
            *yc = m1 * (*xc - mx1) + my1;
        }
        else
        {
            *yc = m2 * (*xc - mx2) + my2;
        }
    }

    dx = x2 - *xc;
    dy = y2 - *yc;
    *rsqr = dx * dx + dy * dy;

    dx = pX - *xc;
    dy = pY - *yc;
    drsqr = dx * dx + dy * dy;

    return ((drsqr - *rsqr) <= EPSILON ? true : false);
}

void construitVoronoi(Application &app)
{
    std::sort(app.points.begin(), app.points.end(), compareCoords);

    app.triangles.clear();

    Triangle t;
    t.p1.x = -1000;
    t.p1.y = -1000;
    t.p2.x = 500;
    t.p2.y = 3000;
    t.p3.x = 1500;
    t.p3.y = -1000;
    app.triangles.push_back(t);

    float rsqr, cx, cy;
    Segment s1, s2, s3;
    Triangle t2;

    for (int i = 0; i < app.points.size(); i++)
    {
        std::vector<Segment> ls;
        for (int j = 0; j < app.triangles.size(); j++)
        {
            if (CircumCircle(app.points[i].x, app.points[i].y,
                             app.triangles[j].p1.x, app.triangles[j].p1.y,
                             app.triangles[j].p2.x, app.triangles[j].p2.y,
                             app.triangles[j].p3.x, app.triangles[j].p3.y,
                             &cx, &cy, &rsqr))
            {

                s1.p1.x = app.triangles[j].p1.x;
                s1.p1.y = app.triangles[j].p1.y;
                s1.p2.x = app.triangles[j].p2.x;
                s1.p2.y = app.triangles[j].p2.y;

                s2.p1.x = app.triangles[j].p1.x;
                s2.p1.y = app.triangles[j].p1.y;
                s2.p2.x = app.triangles[j].p3.x;
                s2.p2.y = app.triangles[j].p3.y;

                s3.p1.x = app.triangles[j].p3.x;
                s3.p1.y = app.triangles[j].p3.y;
                s3.p2.x = app.triangles[j].p2.x;
                s3.p2.y = app.triangles[j].p2.y;

                ls.push_back(s1);
                ls.push_back(s2);
                ls.push_back(s3);

                app.triangles.erase(app.triangles.begin() + j);
                j--;
            }
        }

        for (int s = 0; s < ls.size(); s++)
        {
            bool isDuplicate = false;
            for (int s2 = 0; s2 < ls.size(); s2++)
            {
                if (s2 != s && ((ls[s].p1 == ls[s2].p2 && ls[s].p2 == ls[s2].p1) || (ls[s].p1 == ls[s2].p1 && ls[s].p2 == ls[s2].p2)))
                {
                    isDuplicate = true;
                    ls.erase(ls.begin()+s2);
                    s2--;
                }
            }
            if (!isDuplicate)
            {
                t2.p1 = ls[s].p1;
                t2.p2 = ls[s].p2;
                t2.p3 = app.points[i];
                app.triangles.push_back(t2);
            }
            else {
                ls.erase(ls.begin()+s);
                s--;
            }
        }
    }
}

bool partageSegment(Triangle t1, Triangle t2) {
    return ((t1.p1 == t2.p1 || t1.p1 == t2.p2 || t1.p1 == t2.p3) && (t1.p2 == t2.p1 || t1.p2 == t2.p2 || t1.p2 == t2.p3))
        || ((t1.p1 == t2.p1 || t1.p1 == t2.p2 || t1.p1 == t2.p3) && (t1.p3 == t2.p1 || t1.p3 == t2.p2 || t1.p3 == t2.p3))
        || ((t1.p2 == t2.p1 || t1.p2 == t2.p2 || t1.p2 == t2.p3) && (t1.p3 == t2.p1 || t1.p3 == t2.p2 || t1.p3 == t2.p3));
}

double getAngleABC(int xA, int yA, int xB, int yB, int xC, int yC) {
    Coords ba, bc;
    ba.x = xA-xB;
    ba.y = yA-yB;
    bc.x = xC-xB;
    bc.y = yC-yB;

    double angleBA = atan2(ba.y, ba.x);
    double angleBC = atan2(bc.y, bc.x);

    return angleBA-angleBC;

    /*int prodScal = ba.x*bc.x + ba.y*bc.y;

    double normBA = sqrt(pow(ba.x,2) + pow(ba.y,2));
    double normBC = sqrt(pow(bc.x,2) + pow(bc.y,2));

    double cosAngle = prodScal / (normBA*normBC);



    int cooX = x2-x1, cooY = y2-y1;
    double angle = acos(-cooY / sqrt(pow(cooX,2) + pow(cooY,2)));
    if (cooX <= 0) {
        return angle;
    }
    else {
        return angle+180;
    }*/
}

void updateDual(Application &app, /*std::vector<Coords> &points, std::vector<Segment> &segments*/ std::vector<Polygone> &polygones) {

    /**
     * Pour chaque point de app
     *     créer un nouveau polygone
     *     pour chaque triangle de app
     *         si le triangle a le point courant
     *             ajouter le centre de son cercle circonscrit au polygone
     * 
     */

    float cx,cy,rsqr;
    polygones.clear();

    for (int p=0 ; p<app.points.size() ; p++) {
        Polygone pol;
        *(pol.vx) = 0;
        *(pol.vy) = 0;
        pol.number = 0;
        pol.colour[0] = rand()%256;
        pol.colour[1] = rand()%256;
        pol.colour[2] = rand()%256;
        for (int t=0 ; t<app.triangles.size() ; t++) {
            if ((app.triangles[t].p1 == app.points[p]) || (app.triangles[t].p2 == app.points[p]) || (app.triangles[t].p3 == app.points[p])) {
                CircumCircle(0,0,app.triangles[t].p1.x,app.triangles[t].p1.y,
                                 app.triangles[t].p2.x,app.triangles[t].p2.y,
                                 app.triangles[t].p3.x,app.triangles[t].p3.y,
                                 &cx,&cy,&rsqr);
                int coo = 0;
                //cout << angleY(app.points[p].x,app.points[p].y,(Sint16) cx,(Sint16) cy) << " - " << angleY(app.points[p].x,app.points[p].y,pol.vx[coo],pol.vx[coo]) << endl;
                while (coo < pol.number && getAngleABC((Sint16) cx,(Sint16) cy,app.points[p].x,app.points[p].y,pol.vx[coo],pol.vx[coo]) > 0.0) {
                    
                    coo++;
                }
                for (int i=pol.number-1 ; i>=coo ; i--) {
                    pol.vx[i+1] = pol.vx[i];
                    pol.vy[i+1] = pol.vy[i];
                }
                pol.vx[coo] = (Sint16) cx;
                pol.vy[coo] = (Sint16) cy;
                pol.number++;
            }
        }
        polygones.push_back(pol);
    }


    /*points.clear();
    segments.clear();

    for (int t=0 ; t<app.triangles.size() ; t++) {
        Coords c;
        float cx,cy,rsqr;
        CircumCircle(0,0,app.triangles[t].p1.x,app.triangles[t].p1.y,
                         app.triangles[t].p2.x,app.triangles[t].p2.y,
                         app.triangles[t].p3.x,app.triangles[t].p3.y,
                         &cx,&cy,&rsqr);
        c.x = int(cx);
        c.y = int(cy);
        points.push_back(c);
    }
    
    for (int t=0 ; t<app.triangles.size() ; t++) {
        std::vector<Triangle> adjacents;

        for (int t2=0 ; t2<app.triangles.size() ; t2++) {
            if (t != t2 && partageSegment(app.triangles[t],app.triangles[t2])) {
                Segment s;
                s.p1 = points[t];
                s.p2 = points[t2];
                segments.push_back(s);
            }
        }
    }*/
}

bool handleEvent(Application &app, /*std::vector<Coords> &points, std::vector<Segment> &segments*/ std::vector<Polygone> &polygones)
{
    /* Remplissez cette fonction pour gérer les inputs utilisateurs */
    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
        if (e.type == SDL_QUIT)
            return false;
        else if (e.type == SDL_WINDOWEVENT_RESIZED)
        {
            app.width = e.window.data1;
            app.height = e.window.data1;
        }
        else if (e.type == SDL_MOUSEWHEEL)
        {
        }
        else if (e.type == SDL_MOUSEBUTTONUP)
        {
            if (e.button.button == SDL_BUTTON_RIGHT)
            {
                app.focus.x = e.button.x;
                app.focus.y = e.button.y;
                app.points.clear();
            }
            else if (e.button.button == SDL_BUTTON_LEFT)
            {
                app.focus.y = 0;
                app.points.push_back(Coords{e.button.x, e.button.y});
                construitVoronoi(app);
                updateDual(app,/*points,segments*/polygones);
            }
        }
    }
    return true;
}

int main(int argc, char **argv)
{
    SDL_Window *gWindow;
    SDL_Renderer *renderer;
    Application app{720, 720, Coords{0, 0}};
    bool is_running = true;

    std::vector<Coords> points;
    std::vector<Segment> segments;

    std::vector<Polygone> polygones;

    // Creation de la fenetre
    gWindow = init("Awesome Voronoi", 720, 720);

    if (!gWindow)
    {
        SDL_Log("Failed to initialize!\n");
        exit(1);
    }

    renderer = SDL_CreateRenderer(gWindow, -1, 0); // SDL_RENDERER_PRESENTVSYNC

    /*  GAME LOOP  */
    while (true)
    {
        // INPUTS
        //is_running = handleEvent(app,points,segments);
        is_running = handleEvent(app,polygones);
        if (!is_running)
            break;

        // EFFACAGE FRAME
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // DESSIN

        /*for (int p=0 ; p<points.size() ; p++) {
            pixelRGBA(renderer, points[p].x, points[p].y, 255, 0, 0, 255);
        }

        for (int s=0 ; s<segments.size() ; s++) {
            lineRGBA(renderer, segments[s].p1.x, segments[s].p1.y, segments[s].p2.x, segments[s].p2.y, 255, 0, 0, 255);
        }*/

        for (int p=0 ; p<polygones.size() ; p++) {
            filledPolygonRGBA(renderer, polygones[p].vx, polygones[p].vy, polygones[p].number, polygones[p].colour[0], polygones[p].colour[1], polygones[p].colour[2], 255);
        }

        draw(renderer, app);

        // VALIDATION FRAME
        SDL_RenderPresent(renderer);

        // PAUSE en ms
        SDL_Delay(1000 / 30);
    }

    // Free resources and close SDL
    close(gWindow, renderer);

    return 0;
}
