#ifndef GRAPH_H
#define GRAPH_H

struct GraphNode;
#include <queue>
#include <string>
#include <cstring>
#include <stdlib.h>

struct Edge
{
	Edge(GraphNode* source, GraphNode* destination, int distance=0);

	GraphNode* source;
	GraphNode* destination;

	int distance;

	Edge* next;
};

struct GraphNode
{
	GraphNode(int value);
	GraphNode(const GraphNode& other);

	void appendNewEdge(GraphNode* destination, int distance=0);
	std::string toString() const;

	int value;
	Edge* edges;
};

class Graph
{
public:
	Graph(int size=20);

	int nodesCount();
	void appendNewNode(GraphNode* node);

	// GraphNode getNode(int n);

	void buildFromAdjenciesMatrix(int** adjacencies, int nodeCount);

	void deepTravel(GraphNode* first, GraphNode* nodes[], int& nodesSize, bool visited[]);

	void wideTravel(GraphNode* first, GraphNode* nodes[], int& nodesSize, bool visited[]);

	bool detectCycle()
	{
		if (!_nodesCount)
			return false;

		bool* visited = new bool[_nodesCount];
		bool result = false;
		for (int i=0; i<_nodesCount; ++i)
		{
			GraphNode* node = nodes[i];
			memset(visited, 0, sizeof(bool) * _nodesCount);
			if(detectCycle(node, visited))
			{
				result = true;
				break;
			}
		}
		delete visited;
		return result;
	}

	bool detectCycle(GraphNode* first, bool visited[]);


	GraphNode& operator[](int index);

private:
	GraphNode** nodes;
	int allocatedSize;
	int _nodesCount;
};

#include "graph.h"

#include <stdexcept>
#include <sstream>
#include <memory>
#include <time.h>
#include <chrono>
#include <thread>

Edge::Edge(GraphNode *source, GraphNode *destination, int distance)
{
	this->next = nullptr;
	this->source = source;
	this->destination = destination;
	this->distance = distance;
}

Graph::Graph(int size)
{
	this->allocatedSize = size;
	this->nodes = new GraphNode*[this->allocatedSize];
	memset(this->nodes, 0, sizeof(GraphNode*) * this->allocatedSize);
	this->_nodesCount = 0;
}

int Graph::nodesCount()
{
	return _nodesCount;
}

// GraphNode Graph::getNode(int n) {
// 	return this.nodes[n];
// }

void Graph::appendNewNode(GraphNode* node)
{
	this->nodes[_nodesCount] = node;
	this->_nodesCount++;
	if (this->_nodesCount >= this->allocatedSize)
	{
		GraphNode** old = this->nodes;
		this->allocatedSize *= 2;
		this->nodes = new GraphNode*[this->allocatedSize];
		memcpy(this->nodes, old, sizeof(GraphNode*) * this->_nodesCount);
		delete old;
	}
	// std::this_thread::sleep_for(std::chrono::milliseconds(MainWindow::instruction_duration*2));
}

GraphNode &Graph::operator[](int index)
{
	if (index >= _nodesCount)
	{
		/*QString error_msg("get(): Index out of bound -> index: %1, size: %2");
		throw std::runtime_error(error_msg.arg(index).arg(_nodesCount)
								 .toStdString());*/
	}
	return *this->nodes[index];
}

GraphNode::GraphNode(int value)
{
	this->edges = nullptr;
	this->value = value;
}

GraphNode::GraphNode(const GraphNode &other)
{
	this->edges = other.edges;
	this->value = other.value;
}

void GraphNode::appendNewEdge(GraphNode* destination, int distance)
{

	Edge* oldFirst = this->edges;
	this->edges = new Edge(this, destination, distance);
	this->edges->next = oldFirst;
	// std::this_thread::sleep_for(std::chrono::milliseconds(MainWindow::instruction_duration));
}

std::string GraphNode::toString() const
{
	std::ostringstream stringStream;
	stringStream << " Node<" << this->value << "> ";
	return stringStream.str();
}


#endif // GRAPH_H
