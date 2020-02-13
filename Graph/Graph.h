#pragma once
#include <Head.h>

class Graph
{
private:
	const ush MAX_SIZE = 512;
	struct Node
	{
		long long x, y;
		bool used = 0;
		int min_dist = INT_MAX,
			degrees = 0,
			connections[512] = { INT_MAX };
	};
	Node* graph = new Node[MAX_SIZE];
	uint V, start, last;

	// all additional functions are located in "private" 
	
	// setup all private vars to default values
	void reset(),

		// outputting the shortest way from START to FINISH (use if dij() is used befor)
		printPrice(),

		// recursive utilite for topological sort
		TSUtil(int n, stack<int>& _stack),

		// find minimal cost edge of curr vertex
		MinUV(uint& curr, uint& MINv, uint& MIdx, uint& LIdx),
		
		// find leftmost point
		FindLeftmostPoint(int&);


	// find shortest way with comparison of dij
	int shortestPath(),
		
		// returns true - eulerian path exist, otherwise - false
		detectStartEuler(),

		// current graph have at list one connection - return true, otherwise - false
		haveNeighbours(int curr = 0),

		// return 1 if ham. path exist, otherwise 0
		detectHamiltonPath(),

		//
		Orientation(Node&, Node&, Node&);
public:
	// constructor of Graph class
	Graph();

	// destructor of Graph class
	~Graph();

	// initializing the input data of graph
	void init(uint start = 1, uint last = 1),

		// print matrix of connections with each node
		printGraph(),

		// Breath First Searching
		bfs(),

		// Depth First Searching
		dfs(),

		// returns the value of the shortest way
		dij(),

		// returns the trail of eulerian path, from start position
		findEulerianPath(),

		// returns the trail of Hamilton Path, from start position
		findHamiltonPath(),

		// return topological oredered graph
		TopSort(),

		// return Yes if complete, other - No
		isComplete(),

		// make spanning tree
		SpanningTree(),

		// biult minimum spanning tree by Prim's algorithm, for weighted edges
		MinSpanningTreePrima(),

		// Convex hall by Jarvis
		JarvisHall();
};

// Graph v1.1 Updates:
// - .used parameter has bool type
// - shortestPath() returns min. vertex index to dij(),
//	instead of void return type and past func. logic
// - dij() works correctly
// - now printPrice() does not take an argument
// - INT_MAX constant changed to INT_MAX