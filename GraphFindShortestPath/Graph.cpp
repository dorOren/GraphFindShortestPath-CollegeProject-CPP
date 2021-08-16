#include "Graph.h"

namespace GraphTheory
{
	// Constructor to initialize a directed graph
	DirectedGraph::DirectedGraph(int n)
	{
		size = n;
		d = new int[size];
		p = new int[size];
		Init();
		MakeEmptyGraph();
	}

	// Distructor
	DirectedGraph::~DirectedGraph()
	{
		for (int i = 0; i < size; i++)
			adjacencyList[i].~LinkedList();
		delete d;
		delete p;
	}

	// Utility function initiate parent and distance ("p[]/d[]") arrays
	void DirectedGraph::Init()
	{
		for (int i = 0; i < size; i++)
		{
			d[i] = -1;
			p[i] = -1;
		}
	}

	// Utility function to check if the graph is empty or not
	int DirectedGraph::IsEmpty()
	{
		return (adjacencyList == nullptr);
	}

	// Utility function to create an empty graph
	void DirectedGraph::MakeEmptyGraph()
	{
		adjacencyList = new LinkedList<int>[size];
	}

	// Utility function to add an edge to the graph
	void DirectedGraph::AddEdge(int i, int j)
	{
		if (j <= size && j > 0 &&
			i <= size && i > 0)
		{
			adjacencyList[i - 1].InsertAfter(nullptr, j);
		}
		else {
			cout << "invalid input" << endl;
			exit(1);
		}
	}

	// Utility function to check if vertex 'v' has an edge pointing to 'u' or not
	int DirectedGraph::IsAdjacent(int u, int v)
	{
		if (u > 0 && u <= size)
			return adjacencyList[u - 1].IsItemExist(v);
		else {
			cout << "VERTEX " << v << " DOES NOT EXIST";
			exit(1);
		}
	}

	// Utility function to remove an edge from graph
	void DirectedGraph::RemoveEdge(int u, int v)
	{
		if (u > 0 && u <= size && v > 0 && v <= size)
		{
			if (IsAdjacent(u, v))
			{
				adjacencyList[u - 1].RemoveNode(v);
			}
		}
		else
		{
			cout << "VERTEX DOES NOT EXIST";
			exit(1);
		}
	}

	// Utility function to read a graph(=its edges) from keyboard. edges must come in pairs
	void DirectedGraph::ReadGraph()
	{
		int i = -1, j = -1;

		cin >> i;
		if (i != cin.eof())
			cin >> j;
		else {
			cout << "invalid input" << endl;
			exit(1);
		}

		while (cin.eof() != i)
		{
			if (i <= 0 || i > size || j <= 0 || j > size || j == cin.eof()) //i or j is invalid vertex or incomplete edge
			{
				cout << "invalid input" << endl;
				exit(1);
			}
			else
				AddEdge(i, j);

			cin >> i >> j;
		}
	}

	// Utility function that gets an empty graph and makes it the transpose graph of "this" graph
	// True = succeeded, False = otherwise
	bool DirectedGraph::CreateTransposeGraph(DirectedGraph& other)
	{
		if (other.size != this->size) return false;

		node<int>* newNode;
		for (int i = 1; i <= size; i++)
		{
			newNode = Adj(i);
			while (newNode != nullptr)
			{
				other.AddEdge(newNode->data, i);
				newNode = newNode->next;
			}
		}
		return true;
	}

	// Utility function BFS scan. Sets distances and parents in "d[]/p[]", considering the shortest paths of each vertex from 's'
	void DirectedGraph::BFS(int s)
	{
		Queue<int> Q(size);

		Init();

		Q.Enqueue(s);
		d[s - 1] = 0;

		int u, v;
		node<int>* pnode = nullptr;

		while (!(Q.IsEmpty()))
		{
			u = Q.Dequeue();

			pnode = Adj(u);


			while (pnode != nullptr)
			{
				v = pnode->data;
				if (d[v - 1] == -1)
				{
					d[v - 1] = d[u - 1] + 1;
					p[v - 1] = u;
					Q.Enqueue(v);
				}
				pnode = pnode->next;
			}
		}
	}

	// Utility function to print the graph (prints all edges)
	void DirectedGraph::PrintGraph()
	{
		node<int>* newNode = nullptr;
		for (int i = 1; i <= size; i++)
		{
			newNode = Adj(i);
			while (newNode != nullptr)
			{
				cout << i << " " << newNode->data << " " << endl;
				newNode = newNode->next;
			}
		}
		cout << endl;
	}

	// Utility function to get "i's" distance from 's' (after BFS scan)
	int DirectedGraph::getDdata(int i)
	{
		return d[i];
	}

	// Utility function to get "i's" parent from shortest path from 's' (after BFS scan)
	int DirectedGraph::getPdata(int i)
	{
		return p[i];
	}

	// Utility function to return all verteces which 'i' has an edge to
	node<int>* DirectedGraph::Adj(int i)
	{
		return adjacencyList[i - 1].GetListHead();
	}

	// Utility function that gets an empty graph, source vertex and destanation vertex, and return shortest path tree from 's' to 't'
	// True = succeeded, False = otherwise
	bool DirectedGraph::findShortestPathsTree(DirectedGraph& other, int s, int t)
	{
		if (other.size != this->size) return false;

		node<int>* curr = nullptr;
		node<int>* temp = nullptr;

		BFS(s);

		for (int i = 1; i <= size; i++)
		{
			curr = Adj(i);

			while (curr != nullptr)
			{
				temp = curr->next;

				int j = curr->data;

				if (getDdata(j - 1) != (getDdata(i - 1) + 1))
				{
					RemoveEdge(i, j);
					curr = temp;
				}
				else
					curr = curr->next;
			}
		}

		DirectedGraph Gt(size);
		CreateTransposeGraph(Gt);

		Gt.BFS(t);

		for (int i = 1; i <= size; i++)
		{
			if (Gt.getDdata(i - 1) == -1)
			{
				curr = Gt.Adj(i);
				while (curr != nullptr)
				{
					temp = curr->next;

					int j = curr->data;

					Gt.RemoveEdge(i, j);
					curr = temp;
				}
			}
		}
		Gt.CreateTransposeGraph(other);
		return true;
	}
}