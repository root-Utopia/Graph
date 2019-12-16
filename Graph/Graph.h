#pragma once
#include <Head.h>

class Graph
{
	// all additional functions are located in "private" 
private:
	const ush MAX_SIZE = 512;
	uint V, start, last;
	struct Node
	{
		uint min_dist = INF,
			used = 0,
			degrees = 0;
		int connections[512] = { INF };
	};
	Node* graph = new Node[MAX_SIZE];

	// setup all private vars to default values
	void reset(),

		// find shortest way with comparison of dij
		shortestPath(int& min_vertex),

		// outputting the shortest way from START to FINISH (use if dij() is used befor)
		printPrice(uint& price),

		// recursive utilite for topological sort
		TSUtil(int n, stack<int>& _stack),

		// find minimal cost edge of curr vertex
		MinUV(uint& curr, uint& MINv, uint& MIdx, uint& LIdx);

	// returns true - eulerian path exist, otherwise - false
	int detectStartEuler(),

		// current graph have at list one connection - return true, otherwise - false
		haveNeighbours(int curr = 0),

		// return 1 if ham. path exist, otherwise 0
		detectHamiltonPath();
public:
	// constructor of Graph class
	Graph();

	// destructor of Graph class
	~Graph();

	// initializing the input data of graph
	void init(uint start = 1, uint last = 1),

		// print matrix of connections with each node
		printGraph(),

		/// Breath First Searching
		bfs(),

		// Depth First Searching
		dfs(),

		// required: setup all 0 to -1
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
		MinSpanningTreePrima();
};