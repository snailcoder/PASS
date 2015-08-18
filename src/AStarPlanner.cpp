#include <iostream>
#include <algorithm>
#include <stdexcept>
#include "IndexPriorityQueue.h"
#include "AStarPlanner.h"

AStarPlanner::AStarPlanner(Metric *heuristic) : heuristic_(heuristic) {
}
IntVector AStarPlanner::Plan(int start, 
                             int goal, 
                             const PlanningGraph &graph) const {
  IntVector path;
  if (start < 0 || start >= graph.num_vertices() 
	  || goal < 0 || goal >= graph.num_vertices()) {
    throw std::invalid_argument("Invalid vertex id.");
  }
  if (!heuristic_) {
    return path;
  }
  IndexPriorityQueue<double> openlist;
  IntVector closedlist;
  std::map<int, int> came_from;
  std::map<int, std::list<EdgeNode*> > adjlist = graph.adjlist();
  RealVector gscore(graph.num_vertices());
  RealVector fscore(graph.num_vertices());
  gscore[start] = 0.0;
  fscore[start] = gscore[start] + Heuristic(start, goal, graph);
  bool found = false;
  openlist.Push(start, fscore[start]);
  while (!openlist.Empty()) {
    int current = openlist.TopIndex();
	if (current == goal) {
      found = true;
      break;
	}
    openlist.Pop();
    closedlist.push_back(current);
	for (std::list<EdgeNode*>::iterator iter = adjlist[current].begin(); 
		iter != adjlist[current].end(); ++iter) {
      int neighbor = static_cast<PlanningEdgeNode*>(*iter)->target();
	  if (std::find(closedlist.begin(), 
                    closedlist.end(), 
                    neighbor) != closedlist.end()) {
        continue;
	  }
      double temp_gscore = gscore[current]
          + graph.EdgeWeight(current, neighbor);
      bool in_openlist = openlist.Contain(neighbor);
      if (!in_openlist || temp_gscore < gscore[neighbor]) {
        came_from[neighbor] = current;
        gscore[neighbor] = temp_gscore;
        fscore[neighbor] = gscore[neighbor] + Heuristic(neighbor, goal, graph);
        if (!in_openlist) {
          openlist.Push(neighbor, fscore[neighbor]);
		}
	  }
	}
  }
  if (found) {
    int current = goal;
    path.push_back(current);
	while (current != start) {
      current = came_from[current];
      path.push_back(current);
	}
    std::reverse(path.begin(), path.end());
  }
  return path;
}
IntVector AStarPlanner::operator ()(int start, 
                                    int goal, 
                                    const PlanningGraph &graph) const {
  return Plan(start, goal, graph);
}
double AStarPlanner::Heuristic(int u, 
                               int v, 
                               const PlanningGraph &graph) const {
  std::vector<Vertex*> vertices = graph.vertices();
  PlanningVertex *pu = static_cast<PlanningVertex*>(vertices[u]);
  PlanningVertex *pv = static_cast<PlanningVertex*>(vertices[v]);
  return heuristic_->Distance(pu->state(), pv->state());
}
void AStarPlanner::set_heuristic(Metric *heuristic) {
  heuristic_ = heuristic;
}