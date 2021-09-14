
#include <iostream>
#include <queue>
#include <vector>

// You are given a graph (All vertices are numbered from 1 to n) and two
// vertices. You have to find a length of the shortest path between vertex s and
// vertex v. In your solution you have to follow the template:
// https://github.com/clumpytuna/Data-Structures-and-Algorithms-II-2020/blob/master/homework/graphs-I/shortest_path.cpp

// Input:
// First line: n (number of vertices)
// Second line: m (number of edges)
// Next m lines: e f (edges line by line)
// Last line: s v (vertices you need to find the shortest path between)

// Output:
// First line: distance between s and v

class Graph {
public:
  Graph(int number_of_nodes) {}

  void AddEdge(int from, int to){

  };

  int GetDistance(int s, int v) { return 0; }
};

int main() {

  Graph g(6);

  g.AddEdge(6, 4);
  g.AddEdge(4, 5);
  g.AddEdge(4, 3);
  g.AddEdge(3, 2);
  g.AddEdge(5, 2);
  g.AddEdge(2, 1);
  g.AddEdge(5, 1);

  std::cout << g.GetDistance(4, 2);

  return 0;
}
