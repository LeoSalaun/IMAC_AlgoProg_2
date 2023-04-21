#include <time.h>
#include "../lib/graph.h"
#include <iostream>
#include <cstdlib>


void Graph::buildFromAdjenciesMatrix(int **adjacencies, int nodeCount)
{
	/**
	  * Make a graph from a matrix
	  * first create all nodes, add it to the graph then connect them
	  * this->appendNewNode
	  * this->nodes[i]->appendNewEdge
	  */

	 for (int i=0 ; i<nodeCount ; i++) {
		this->appendNewNode(new GraphNode(i));
		for (int j=0 ; j<nodeCount ; j++) {
			if (adjacencies[i,j] > 0) {
				this->nodes[i]->appendNewEdge(this->nodes[j],*adjacencies[i,j]);
			}
		}
	 }
}

void Graph::deepTravel(GraphNode *first, GraphNode *nodes[], int &nodesSize, bool visited[])
{
	/**
	  * Fill nodes array by travelling graph starting from first and using recursivity
	  */
	
	visited[first->value] = true;
	nodes[nodesSize] = first;
	nodesSize++;
	Edge* edge = first->edges;
	while (edge != nullptr) {
		if (!(visited[edge->destination->value])) {
			this->deepTravel(edge->destination,nodes,nodesSize,visited);
		}
		edge = edge->next;
	}
}

void Graph::wideTravel(GraphNode *first, GraphNode *nodes[], int &nodesSize, bool visited[])
{
	/**
	 * Fill nodes array by travelling graph starting from first and using queue
	 * nodeQueue.push(a_node)
	 * nodeQueue.front() -> first node of the queue
	 * nodeQueue.pop() -> remove first node of the queue
	 * nodeQueue.size() -> size of the queue
	 */
	std::queue<GraphNode*> nodeQueue;
	nodeQueue.push(first);
}

bool Graph::detectCycle(GraphNode *first, bool visited[])
{
	/**
	  Detect if there is cycle when starting from first
	  (the first may not be in the cycle)
	  Think about what's happen when you get an already visited node
	**/
    return false;
}

void drawMatrix(int** matrix, int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cout << matrix[i][j] << '\t';
        }
        std::cout << '\n';
    }
}

int main(int argc, char *argv[])
{
	int n=7;
    int** matrix = new int*[n];
    for (int i=0; i<n; ++i)
	{
        matrix[i] = new int[n];
        for (int j=0; j<n; ++j)
		{
			matrix[i][j] = (rand() % 300 - 230) / 2;
			if (matrix[i][j] < 0)
				matrix[i][j] = 0;
		}
	}

	drawMatrix(matrix,n);

	Graph * graph = new Graph(n);
	graph->buildFromAdjenciesMatrix(matrix,n);

	GraphNode * nodes[0];
	bool visited[n] = {false,false,false,false,false,false,false};

	graph->deepTravel(graph->nodes[0],nodes,0,visited);


	return 0;
}