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
	}
	for (int i=0 ; i<nodeCount ; i++) {
		for (int j=0 ; j<=nodeCount ; j++) {
			if (adjacencies[i][j] > 0) {
				this->nodes[i]->appendNewEdge(this->nodes[j],adjacencies[i][j]);
			}
			// if (adjacencies[j][i] > 0 && i != j) {
			// 	this->nodes[j]->appendNewEdge(this->nodes[i],adjacencies[j][i]);
			// }
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
			this->Graph::deepTravel(edge->destination,nodes,nodesSize,visited);
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
	//nodeQueue.push(first);

	nodeQueue.push(first);
	visited[first->value] = true;
	nodes[nodesSize] = first;
	nodesSize++;

	while (nodeQueue.size() > 0) {
		GraphNode * current = nodeQueue.front();
		nodeQueue.pop();

		Edge* edge = first->edges;
		while (edge != nullptr) {
			if (!(visited[edge->destination->value])) {
				nodeQueue.push(edge->destination);
				visited[edge->destination->value] = true;
				nodes[nodesSize] = edge->destination;
				nodesSize++;
			}
			edge = edge->next;
		}
	}


	
}

bool Graph::detectCycle(GraphNode *first, bool visited[])
{
	/**
	  Detect if there is cycle when starting from first
	  (the first may not be in the cycle)
	  Think about what's happen when you get an already visited node
	**/

	visited[first->value] = true;
	Edge* edge = first->edges;
	bool hasCycle = false;

	while (edge != nullptr && !(hasCycle)) {
	// 	std::cout << first->value << " -> " << edge->destination->value << std::endl;
		if (!(visited[edge->destination->value])) {
			hasCycle = this->Graph::detectCycle(edge->destination,visited);
			visited[edge->destination->value] = false;
		}
		else {
			hasCycle = true;
		}
		edge = edge->next;
	}

    return hasCycle;
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
	srand(time(0));

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
	graph->Graph::buildFromAdjenciesMatrix(matrix,n);

	GraphNode ** nodes;
	int nodeSize = 0;
	bool visited[n] = {false,false,false,false,false,false,false};

	// graph->Graph::wideTravel(&(graph->Graph::operator[](0)),nodes,nodeSize,visited);

	// std::cout << std::endl;

	// for (int i=0 ; i<nodeSize ; i++) {
	// 	std::cout << nodes[i]->value << " - ";
	// }
	// std::cout << std::endl;

	std::cout << graph->Graph::detectCycle(&(graph->Graph::operator[](0)),visited) << std::endl;

	return 0;
}