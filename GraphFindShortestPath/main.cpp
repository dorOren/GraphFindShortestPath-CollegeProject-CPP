/*
The program recieves a number of vertices, source vertex and destination vertex as well as the edges of the graph.
It builds a graph according to the input, runs BFS algorithm on it and deletes every edge that is not a part of the BFS tree that recieved - Gs.
After that the program builds the transpose graph of Gs - Gst, and runs BFS algorithm on it.
Every edge of Gst that is not a part of the BFS tree recieved is deleted and the graph remains is Ht.
Ht transposed graph is created - H, and this is the output of the program; a graph of the shortest paths from the source vertex to the destination vertex.

Data structures used:
    - Directed Graph.
    - Queue: used in the BFS algorithm.
    - Linked list: used as adjacency list of each vertex.
    The project was built considering OOP concepts, and acknowledging importance of reusable- maintainability code.

Operation:
    insert number of overall vertices in the graph, source and destination vertices,  pairs of vertices that represents edges.
    The program will start running after ^Z is inserted.
*/
#include "Graph.h"
#include <chrono>
#include <iomanip>

using namespace std;
using namespace GraphTheory;

int main()
{
    int n, s, t;
    cin >> n >> s >> t;

    if (s <= 0 || s > n || t <= 0 || t > n || s == cin.eof() || t == cin.eof())
    {
        cout << "invalid input" << endl;
        exit(1);
    }

    DirectedGraph G(n);

    G.ReadGraph();

    DirectedGraph H(n);

    auto start = chrono::high_resolution_clock::now();
    // unsync the I/O of C and C++.
    ios_base::sync_with_stdio(false);
    G.findShortestPathsTree(H, s, t);   // Here you put the name of the function you wish to measure
    auto end = chrono::high_resolution_clock::now();
    // Calculating total time taken by the program.
    double time_taken =
        chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    time_taken *= 1e-9;
    cout << "\nPrint H:" << endl;
    H.PrintGraph();
    cout << "running time: ";
    cout << fixed << time_taken << setprecision(9) << endl;
}