#ifndef _GRAPH_HPP_
#define _GRAPH_HPP_

#include <iostream>
#include <string>
#include <sstream>
#include <list>
#include <limits>
#include <math.h>
#include <queue>
class Vertex {
public:
	bool visited;
	int distance;
	int previous;
	int finish;
	std::list<int> adj;
};

class Graph {
public:
	Graph(int V, int E, std::pair<int, int> *edges) {
		_V = V;
		_E = E;
		vertices = new Vertex[_V];
		for (int i = 0; i < _V; i++) {
                    vertices[i].visited = false;//False = white, black = true
                    vertices[i].distance = (int) INFINITY;
                    vertices[i].previous = -1;
		}
		for (int i = 0; i < _E; i++) {
		    addEdge(edges[i].first, edges[i].second);
		}
	}

	virtual ~Graph() {
		for (int i=0; i<_V; ++i) {
		    auto adj = vertices[i].adj;
		    adj.clear(); // clear list
		}

		delete[] vertices; // delete array of vertices
	}

	int V() {
		return _V;
	}

	int E() {
		return _E;
	}

	void addEdge(int u, int v) {
		vertices[u].adj.push_back(v);
	}

	std::list<int> getEdges(int u) {
		return vertices[u].adj;
	}

	int degree(int u) {
		return vertices[u].adj.size();
	}

	void bfs(int s) {
		// Follows pseudocode from textbook

		std::queue<int> container;//Helper queue

		//Ensure queue is empty
		while (!container.empty()) {
			container.pop();
		}

		//Set each vertex other than s as unvisited, distance to infinity, previous as null
		for (int x = 0; x < _V; x++) {
			if (x != s) {
				vertices[x].visited = false;
				vertices[x].distance = (int) INFINITY;
				vertices[x].previous = -1;
			}
		}

		vertices[s].visited = true;//Mark as visited
		vertices[s].distance = 0;//Set distance to 0
		vertices[s].previous = -1;//Mark previous as null

		container.push(s);//Push source vertex into queue

		//While queue contains elements, perform search
		while(!container.empty()) {
			int u = container.front();
			container.pop();
			for (int v : vertices[u].adj) {//Search neighbors of u
				if (!vertices[v].visited) {//Is v being discovered now?
					vertices[v].visited = true;//Mark v as visited
					vertices[v].distance = vertices[u].distance + 1;
					vertices[v].previous = u;//Set v previous to u
					container.push(v);//v is now on the frontier
				}
			}
			vertices[u].visited = true;//Mark u as visited, u is now behind the frontier
		}
	}

	void dfs() {
		// Follows pseudocode from textbook

		//Set each vertex as unvisited, previous as null
		for (int u = 0; u < _V; u++) {
			vertices[u].visited = false;
			vertices[u].previous = -1;
		}

		//Set time to 0
		time = 0;

		//Visit each unvisited vertex
		for (int u = 0; u < _V; u++) {
			if (vertices[u].visited == false) {
				dfs_visit(u);
			}
		}
	}

	void dfs_visit(int u) {

		// Follows pseudocode from textbook

		time++;//Vertex u has just been discovered
		vertices[u].distance = time;
		vertices[u].visited = true;//Mark u as visited

		//Print out the node as it is visited
		std::cout << u << ", ";

		//Explore each unvisited vertex adjacent to u
		for (int v : vertices[u].adj) {
			//If the vertex has not been visited, visit it
			if (!vertices[v].visited) {
				vertices[v].previous = u;//Mark v previous as u
				dfs_visit(v);//Visit v
			}
		}
		time++;//Increment time
		vertices[u].finish = time;//Mark finish time of u
		// vertices[u].visited = true;//Mark u as visited
	}

	void print_path(int s, int v) {
		if (v == s)
		   std::cout << s;
		else if (vertices[v].previous == -1)
		   std::cout << "not connected";
		else {
		   print_path(s,vertices[v].previous);
		   std::cout << "->" << v;
		}
	}

	std::string toString() {
		std::stringbuf buffer;
		std::ostream os(&buffer);
		os << "Vertices = " << _V << ", Edges = " << _E << std::endl;
		for (int i = 0; i < _V; ++i) {
		    os << i << "(" << degree(i) << "): ";
		    for (const auto& l : vertices[i].adj) 
			os << l << " ";
		    os << std::endl;
		}

		return buffer.str();
	}
private:
	int _V; // no. of vertices
	int _E; // no. of edges
	Vertex *vertices; // array of vertices
	int time;//time parameter
};

#endif
