#include <limits>
#include <stdexcept>
#include <algorithm>
#include "IndexPriorityQueue.h"
#include "DijkstraPlanner.h"

IntVector DijkstraPlanner::Plan(int start, 
                                int goal, 
                                const PlanningGraph &graph) const {
  IntVector path;
  int num_vertices = graph.num_vertices();
  if (start < 0 || start >= num_vertices 
	  || goal < 0 || goal >= num_vertices) {
    throw std::invalid_argument("Invalid vertex id.");
  }
  IndexPriorityQueue<double> prique;
  std::map<int, int> came_from;
  std::map<int, std::list<EdgeNode*> > adjlist = graph.adjlist();
  RealVector dist(graph.num_vertices());
  dist[start] = 0.0;
  for (int i = 0; i < num_vertices; ++i) {
    if (i != start) {
      dist[i] = std::numeric_limits<double>::max();
	}
    prique.Push(i, dist[i]);
  }
  while (!prique.Empty()) {
    int current = prique.Pop();
	for (std::list<EdgeNode*>::iterator iter = adjlist[current].begin();
		iter != adjlist[current].end(); ++iter) {
      int neighbor = static_cast<PlanningEdgeNode*>(*iter)->target();
      double temp_dist = dist[current]
          + graph.EdgeWeight(current, neighbor);
      if (temp_dist < dist[neighbor]) {
        dist[neighbor] = temp_dist;
        came_from[neighbor] = current;
        prique.Update(neighbor, dist[neighbor]);
	  }
	}
  }
  int current = goal;
  path.push_back(current);
  while (current != start) {
    current = came_from[current];
    path.push_back(current);
  }
  std::reverse(path.begin(), path.end());
  return path;
}
IntVector DijkstraPlanner::operator ()(int start, 
                                       int goal, 
                                       const PlanningGraph &graph) const {
  return Plan(start, goal, graph);
}