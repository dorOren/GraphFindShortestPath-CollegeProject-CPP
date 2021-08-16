// this file contains all necessary methods for implementing a directed graph and performing operations on it, including BFS scan and find shortest path tree.
#pragma once
#include "LinkedList.h"
#include "Queue.h"

using namespace std;

namespace GraphTheory
{
	class DirectedGraph
	{
	private:
		LinkedList<int>* adjacencyList;
		int size;
		int* d;
		int* p;

	public:
		DirectedGraph(int n = 0);											  // constructor - input: number of vetices, output: empty graph with n vertices
		~DirectedGraph();													  // distructor
																	  
		// basic methodes											  
		void MakeEmptyGraph();										  // no input, outpur: empty graph
		int IsEmpty();												  // no input, output: true if the graph is empty, false otherwise
		void Init();												  // no input, outpur: initalized d and p arrays
		int IsAdjacent(int u, int v);								  // input: vertices u and v, output: true if there is an edge between u and v, false otherwise
		void AddEdge(int i, int j);									  // input: vertices i and j, output: graph with an edge between u and v
		void RemoveEdge(int u, int v);								  // input: vertices u and v, output: graph without an edge between u and v 
		void ReadGraph();											  // reads edges from buffer, output: graph with all edges inserted (using addEdge function)
		bool CreateTransposeGraph(DirectedGraph& other);					  // input: other graph object, output: transpose of this graph 
		void PrintGraph();											  // no input, output: prints graph
		node<int>* Adj(int i);										  // input: vertex i, output: first vertex in i's adjacency list
		int getDdata(int i);										  // input: vertex i, output: d[i] after BFS
		int getPdata(int i);										  // input: vertex i, output: p[i] after BFS 
		void BFS(int s);											  // input: vertex s, output: d and p arrays after BFS when s is the source vertex
		bool findShortestPathsTree(DirectedGraph& other, int s, int t);		  //input: other graph, source and destination vertices, output: shortest path tree of this graph
	};
}
