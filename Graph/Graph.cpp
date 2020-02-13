#pragma once
#include <Graph.h>

// Group commons (DONE)
Graph::Graph()
{
#ifdef DEBUG
	cout << "Graph is running.\n";
#endif // DEBUG
}

void Graph::reset()
{
	for (uint row = 0; row < this->V; ++row)
	{
		graph[row].min_dist = INT_MAX;
		graph[row].used = false;
		graph[row].degrees = NULL;
		graph[row].x = NULL;
		graph[row].y = NULL;
	}
}

void Graph::init(uint start, uint last)
{
	#ifdef DEBUG
		cout << "Start: init.\n";
	#endif // DEBUG

	// opening file with input data of graph
	ifstream input("input.txt", ios::in);

	// input vertices count
	input >> this->V;
	// check the start and last values for correctness
	if ((start && (start <= this->V)) && (last && (last <= this->V)))
	{
		this->start = --start,
		this->last = --last;
	}

	// input the adj. matrix
	for (uint row = 0; row < this->V; ++row)
		for (uint col = 0; col < this->V; ++col)
		{
			input >> graph[row].connections[col];
			// setup degre to each node
			if (graph[row].connections[col])
				++graph[row].degrees;
			else if (graph[row].connections[col] == -1)
				graph[row].connections[col] = INT_MAX;
		}

	#ifdef DEBUG
		cout << "End: init.\n";
	#endif // DEBUG
}

void Graph::printGraph()
{
	for (uint row = 0; row < this->V; ++row, cout << "]\n")
	{
		cout << row + 1 << " -> [ ";
		for (uint col = 0; col < this->V; ++col)
			if (this->graph[row].connections[col])
				cout << col + 1 << ' ';
	}
}

void Graph::isComplete()
{
	uint in = 0, row = 0, col = 0, vcnt = 0;
	for (; row < this->V; ++row)
		for (col = 0, in = 0; col < this->V; ++col)
			if (this->graph[row].connections[col] && (++in == this->V - 1))
				++vcnt;

	if (vcnt == this->V)
		cout << "Yes\n";
	else
		cout << "No. it isn't\n";
}

Graph::~Graph()
{
	delete[] this->graph;
#ifdef DEBUG
	cout << "Graph is destroyed\n";
#endif // DEBUG
}

// Group First Serch algorithms (DONE)
void Graph::bfs()
{
#ifdef DEBUG
	cout << "Start: bfs\n";
#endif // DEBUG

	int ver = 0;
	queue<int> __way__;
	__way__.push(this->start);
	graph[this->start].used = true;

	while (!__way__.empty())
	{
		uint curr = __way__.front();
		cout << curr + 1 << string((++ver == this->V) ? "\n" : " -> ");
		__way__.pop();

		// checking if current vertex has adj with other one to push it to deque
		for (uint col = 0; col < this->V; ++col)
			if (graph[curr].connections[col] && !graph[col].used)
			{
				__way__.push(col);
				graph[col].used = true;
			}
	}
	this->reset();

#ifdef DEBUG
	cout << "End: bfs\n";
#endif // DEBUG	
}

void Graph::dfs()
{
#ifdef DEBUG
	cout << "Start: dfs\n";
#endif // DEBUG

	uint ver = 0;
	stack<uint> __way__;
	__way__.push(this->start);

	while (!__way__.empty())
	{
		uint curr = __way__.top();
		__way__.pop();
		if (!graph[curr].used++)
			cout << curr + 1 << string((++ver == this->V) ? "\n" : " -> ");


		for (uint col = 0; col < this->V; col++)
			if (graph[curr].connections[col] && !graph[col].used)
				__way__.push(col);
	}
	this->reset();

#ifdef DEBUG
	cout << "End: dfs\n";
#endif // DEBUG
}

// Group dij (DONE)
int Graph::shortestPath()
{
	int min_dist = INT_MAX, min_vertex = -1;

	for (uint i = 0; i < V; ++i)
		if (!graph[i].used && (graph[i].min_dist <= min_dist))
			min_dist = graph[i].min_dist,
			min_vertex = i;

	return min_vertex;
}

void Graph::dij()
{
#ifdef DEBUG
	cout << "Start: dij\n";
#endif // DEBUG

	graph[this->start].min_dist = 0;
	for (uint i = 0; i < this->V - 1; ++i)
	{
		int min_vertex = shortestPath();
		graph[min_vertex].used = true;

		// for each vertex: setup new price
		for (uint i = 0; i < this->V; ++i)
			if (!graph[i].used && graph[min_vertex].connections[i] != INT_MAX && graph[min_vertex].connections[i] &&
				(graph[i].min_dist > graph[min_vertex].min_dist + graph[min_vertex].connections[i]))
				graph[i].min_dist = graph[min_vertex].min_dist + graph[min_vertex].connections[i];
	}

	this->printPrice();
	this->reset();

#ifdef DEBUG
	cout << "End: dij\n";
#endif // DEBUG
}

void Graph::printPrice()
{
	if (graph[this->last].min_dist >= INT_MAX || graph[this->last].min_dist < 0)
		cout << "IMPOSSIBLE\n";
	else
		cout << "Shortest path from town #" << this->start + 1 << " to #" << this->last + 1 << " one = " << graph[this->last].min_dist << "\n";
}

// Group Eulerian Path (DONE)
int Graph::detectStartEuler()
{
	for (unsigned int row = 0; row < this->V; ++row)
		for (unsigned int col = 0; col < this->V; ++col)
			if ((graph[row].connections[col] < INT_MAX) && graph[row].connections[col])
				++graph[row].degrees;

	int odd = 0, even = 0, odd_ver = -1, even_ver = -1;
	for (unsigned int i = 0; i < this->V; ++i)
	{
		if (graph[i].degrees)
			if (graph[i].degrees % 2 > 0)
			{
				// path
				if (odd_ver == -1) odd_ver = i;
				++odd;
			}
			else if (graph[i].degrees % 2 == 0)
			{
				// cycle
				if (even_ver == -1) even_ver = i;
				++even;
			}
	}

	/*
		is it Eulerian path or circuit ?
		return number of start vertex
	*/
	return ((odd == 2) ? odd_ver : ((even == this->V) ? even_ver : -1));
}
int Graph::haveNeighbours(int curr)
{
	for (uint i = 0; i < this->V; ++i)
		if (graph[curr].connections[i])
			return true;
	return false;
}

void Graph::findEulerianPath()
{
#ifdef DEBUG
	cout << "Start: findEulerianPath\n";
#endif // DEBUG
	// checking: graph hasn't eulerian path or circuit ?
	int curr = this->detectStartEuler();
	if (curr == -1) return;

	stack<int> _stack;
	_stack.push(curr);

	while (!_stack.empty() || this->haveNeighbours(curr))
	{
		if (!this->haveNeighbours(curr))
		{
			cout << curr + 1 << " -> ";
			curr = _stack.top();
			_stack.pop();
		}
		else
			for (uint i = 0; i < this->V; ++i)
				if (this->graph[curr].connections[i])
				{
					_stack.push(curr);
					this->graph[curr].connections[i] = 0;
					this->graph[i].connections[curr] = 0;
					curr = i;
					break;
				}
	}
	this->reset();

#ifdef DEBUG
	cout << "End: findEulerianPath\n";
#endif // DEBUG
}

// Group Hamilton Path
int Graph::detectHamiltonPath()
{
	// checking if each graph vertex has degree greater equal than number of vertices divided by 2 
	return 0;
	return 1;
}

void Graph::findHamiltonPath()
{
#ifdef DEBUG
	cout << "Start: findHamiltonPath\n";
#endif // DEBUG

	/*int q1 = 0;
	for (int curr = 0; (curr < this->V) && !q1; ++curr)
		if (this->graph[curr][path[k - 1]] || this->graph[path[k - 1]][curr])
			if ((k == n) && curr == this->start) q1 = 1;
			else if (c[curr] == -1)
			{
				c[curr] = k; path[k] = curr;
				q1 = gamilton(k + 1);
				if (!q1) c[curr] = -1;
			}

	return q1;*/

#ifdef DEBUG
	cout << "End: findHamiltonPath\n";
#endif // DEBUG
}

// Group Topological Sort (DONE)
void Graph::TSUtil(int n, stack<int>& _stack)
{
	graph[n].used = 1;
	for (uint i = 0; i < this->V; ++i)
		if (graph[n].connections[i] && !graph[i].used)
			TSUtil(i, _stack);

	_stack.push(n);
}

void Graph::TopSort()
{
#ifdef DEBUG
	cout << "Start: TopSort\n";
#endif // DEBUG

	stack<int> __way__;
	for (uint i = 0; i < this->V; ++i)
		if (!graph[i].used)
			TSUtil(i, __way__);

	// output & reset
	cout << "Top Sorted: ";
	for (uint i = 0; i < this->V; ++i, __way__.pop())
		cout << __way__.top() + 1 << " -> ";
	/* if (graph[__way__.top()].connections[this->start] && (i == this->V - 1))
		cout << this->start + 1 << '\n'; */
	this->reset();

#ifdef DEBUG
	cout << "\nEnd: TopSort\n";
#endif // DEBUG
}

// Group Tree
void Graph::SpanningTree()
{
	this->dfs();
}

void Graph::MinUV(uint& curr, uint& MINv, uint& MIdx, uint& LIdx)
{
	MINv = INT_MAX, MIdx = -1;
	for (uint i = 0; i < this->V; ++i)
		if (graph[curr].connections[i] && !graph[i].used && (MINv > (uint)graph[curr].connections[i]))
			MINv = graph[curr].connections[i], MIdx = i, LIdx = curr;
}

void Graph::MinSpanningTreePrima()
{
#ifdef DEBUG
	cout << "Start: MinSpanningTreePrima\n";
#endif // DEBUG

	uint ver = 0, MINcost = 0, MINv = INT_MAX, MIdx = INT_MAX, LIdx = this->start;
	deque<int> __way__;
	__way__.push_front(LIdx);

	while (!__way__.empty())
	{
		uint curr = __way__.back();
		if (!graph[curr].used)
		{
			// output the connection between two vertex
			string tail = (++ver == this->V) ? "\n" : " -> ";
			cout << '(' << LIdx + 1 << ';' << curr + 1 << ')' << tail;

			graph[curr].used = true;
		}
		__way__.pop_back();

		// find min. cost edge from 'curr' to 'i' vertex, return 'MinIndex' of 'i'
		this->MinUV(curr, MINv, MIdx, LIdx);

		// if min. 
		if (MIdx != -1)
		{
			__way__.push_front(MIdx);
			MINcost += MINv;
		}
	}
	cout << "Weight of Minimal Spanning Tree = " << MINcost << '\n';

	this->reset();

#ifdef DEBUG
	cout << "End: MinSpanningTreePrima\n";
#endif // DEBUG
}

void Graph::FindLeftmostPoint(int& left)
{
	int* tmp = &left;
	for (int i = 1; i < V; i++)
		if (graph[i].x < graph[*tmp].x)
			*tmp = i;
}

int Graph::Orientation(Node& currpoint, Node& mid, Node& next)
{
	int angel = (mid.y - currpoint.y) * (next.x - mid.x) -
		(mid.x - currpoint.x) * (next.y - mid.y);

	// colinear or clock either counterclock wise 
	return (!angel ? 0 : (angel > 0) ? 1 : 2);
}

void Graph::JarvisHall()
{
#ifdef DEBUG
	cout << "Start: JarvisHall\n";
#endif // DEBUG
	
	// input (x, y) coordinates
	for (int i = 0; i < V; ++i)
		cin >> graph[i].x >> graph[i].y;

	// if points count 
	if (V < 3)
	{
		cerr << "Error: no enough points.\n";
		return;
	}

	// find leftmost point

	int left = 0;
	FindLeftmostPoint(left);

	// initilize hull, current point, next point
	vector<Node> hull;
	int currPoint = left, next;
	do
	{
		// add current point to Convex Hull
		hull.push_back(graph[currPoint]);

		// find next correct point
		next = (currPoint + 1) % V;
		for (int i = 0; i < V; ++i)
			if (Orientation(graph[currPoint], graph[i], graph[next]) == 2)
				next = i;

		// set current point to next
		currPoint = next;
	} while (currPoint != left); // While we don't come to start point 

	// print result
	for (int i = 0, len = hull.size(); i < len; ++i)
		cout << "(" << hull[i].x << ", " << hull[i].y << ") -> ";
	cout << "(" << hull[0].x << ", " << hull[0].y << ")\n";

	this->reset();

#ifdef DEBUG
	cout << "End: JarvisHall\n";
#endif // DEBUG
}