#include <iostream>

#include <set>
#include <map>
#include <queue>

typedef unsigned int Node;
typedef unsigned int Weight;

// connect two nodes and assign a weight
struct Edge
{
  Node from;
  Node to;
  Weight weight;

  // for sorting
  bool operator<(const Edge& other) const
  {
    // STL's priority queue returns the __largest__ element first, therefore I invert the comparison sign
    if (weight != other.weight)
      return weight > other.weight;

    // sort by nodes, too, to avoid collisions of nodes with the same weight
    // the order doesn't matter, these nodes just "have to be different"
    if (from   != other.from)
      return from   < other.from;

    return to < other.to;
  }
};

// all edges (full network)
std::map<std::pair<Node, Node>, Weight> network;
// all nodes
std::set<Node> nodes;
// weight of the full network, including duplicate connections
unsigned int initialSum = 0;

// insert an edge into the network, true if already existing
void addEdge(Node from, Node to, Weight weight)
{
  // count all originals weights
  initialSum += weight;

  // all edges have the lower ID first (I can do that because it's an undirected graph)
  if (from > to)
    std::swap(from, to);

  // already existing edge ?
  auto fromTo = std::make_pair(from, to);
  if (network.count(fromTo) != 0)
    // has the existing edge a lower or the same weight ? => we're done
    if (network[fromTo] <= weight)
      return;

  // store new (or improved) connection between two nodes
  network[fromTo] = weight;
  nodes.insert(from);
  nodes.insert(to);
}

int main()
{
#ifdef ORIGINAL
  // read Project Euler's weird file format
  for (unsigned int i = 0; i < 40; i++)
    for (unsigned int j = 0; j < 40; j++)
    {
      char c = 0;
      unsigned int weight = 0;
      // CSV-format
      while (c != ',' && c != '\n')
      {
        c = std::cin.get();
        // ignore dashes
        if (c >= '0' && c <= '9')
        {
          weight *= 10;
          weight += c - '0';
        }
      }

      // only valid weights
      if (weight != 0 && i < j)
        addEdge(i, j, weight);
    }

#else

  // read Hackerrank input
  unsigned int numNodes, numEdges;
  std::cin >> numNodes >> numEdges;
  for (unsigned int i = 0; i < numEdges; i++)
  {
    Node   from, to;
    Weight weight;
    std::cin >> from >> to >> weight;
    addEdge(from, to, weight);
  }
#endif

  // optimized graph, initially empty
  std::set<Edge> minimal;

  // start with a random node
  std::set<Node> done;
  done.insert(*nodes.begin());

  // not all nodes optimized yet ?
  while (done.size() < nodes.size())
  {
    // add all edges where one node is part of tree and the other isn't
    std::priority_queue<Edge> next;
    for (auto e : network)
    {
      auto fromTo  = e.first;
      bool hasFrom = done.count(fromTo.first)  != 0;
      bool hasTo   = done.count(fromTo.second) != 0;
      if (hasFrom == hasTo) // both nodes are already optimized or both aren't ?
        continue;

      next.push({fromTo.first, fromTo.second, e.second});
    }

    // get edge with minimal weight
    auto add = next.top();

    // add new edge to tree
    done.insert(add.from); // one insert is redundant but set::set throws it away
    done.insert(add.to);

    // add edge to the optimized graph
    minimal.insert(add);
  }

  // "measure" both graphs
  unsigned int optimizedSum = 0;
  for (auto i : minimal)
    optimizedSum += i.weight;

#ifdef ORIGINAL
  // difference
  auto gain = initialSum - optimizedSum;
  std::cout << gain << std::endl;
#else
  std::cout << optimizedSum << std::endl;
#endif

  return 0;
}
