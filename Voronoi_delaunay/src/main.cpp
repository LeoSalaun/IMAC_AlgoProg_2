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
    std::vector<Polygone> polygones;
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
    for (std::size_t p=0 ; p<polygones.size() ; p++) {
        filledPolygonRGBA(renderer, polygones[p].vx, polygones[p].vy, polygones[p].number, polygones[p].colour[0], polygones[p].colour[1], polygones[p].colour[2], 255);
    }
}

void draw(SDL_Renderer *renderer, const Application &app)
{
    /* Remplissez cette fonction pour faire l'affichage du jeu */
    int width, height;
    SDL_GetRendererOutputSize(renderer, &width, &height);

    drawPolygones(renderer, app.polygones);
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

    for (std::size_t i = 0; i < app.points.size(); i++)
    {
        std::vector<Segment> ls;
        for (std::size_t j = 0; j < app.triangles.size(); j++)
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

        for (std::size_t s = 0; s < ls.size(); s++)
        {
            bool isDuplicate = false;
            for (std::size_t s2 = 0; s2 < ls.size(); s2++)
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

void updateDual(Application &app/*, std::vector<Coords> &points, std::vector<Segment> &segments std::vector<Polygone> &polygones*/) {

    /**
     * Pour chaque point de app
     *     créer un nouveau polygone
     *     pour chaque triangle de app
     *         si le triangle a le point courant
     *             ajouter le centre de son cercle circonscrit au polygone
     * 
     */

    float cx,cy,rsqr;
    app.polygones.clear();

    for (std::size_t p=0 ; p<app.points.size() ; p++) {
        Polygone pol;
        *(pol.vx) = 0;
        *(pol.vy) = 0;
        pol.number = 0;
        pol.colour[0] = rand()%256;
        pol.colour[1] = rand()%256;
        pol.colour[2] = rand()%256;
        std::vector<Triangle> tempTriangles;
        for (std::size_t t=0 ; t<app.triangles.size() ; t++) {
            if ((app.triangles[t].p1 == app.points[p]) || (app.triangles[t].p2 == app.points[p]) || (app.triangles[t].p3 == app.points[p])) {
                tempTriangles.push_back(app.triangles[t]);
            }
        }
        std::size_t t1=0;
        while (tempTriangles.size() > 0) {
            CircumCircle(0,0,tempTriangles[t1].p1.x,tempTriangles[t1].p1.y,
                             tempTriangles[t1].p2.x,tempTriangles[t1].p2.y,
                             tempTriangles[t1].p3.x,tempTriangles[t1].p3.y,
                             &cx,&cy,&rsqr);
            pol.vx[pol.number] = (Sint16) cx;
            pol.vy[pol.number] = (Sint16) cy;
            pol.number++;
            if (tempTriangles.size() > 1) {
                std::size_t t2 = 0;
                while (t2 < tempTriangles.size() && (t1 == t2 || !(partageSegment(tempTriangles[t1],tempTriangles[t2])))) {
                    t2++;
                }
                tempTriangles.erase(tempTriangles.begin()+t1);
                if (t2 < t1) {
                    t1 = t2;
                }
                else {
                    t1 = t2-1;
                }
            }
            else {
                tempTriangles.erase(tempTriangles.begin()+t1);
            }
        }
        app.polygones.push_back(pol);
    }
}

bool handleEvent(Application &app)
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
                updateDual(app);
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
        is_running = handleEvent(app);
        if (!is_running)
            break;

        // EFFACAGE FRAME
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // DESSIN
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
