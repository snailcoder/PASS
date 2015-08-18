#ifndef GRAPH_H_
#define GRAPH_H_

#include <list>
#include <vector>
#include <map>
#include "common.h"
#include "Metric.h"

// Vertex of the graph. It is the base class of PlanningVertex. 
class Vertex {
 public:
  Vertex(int id);
  virtual ~Vertex();
  int id() const;
  virtual Vertex* Clone() const;
 protected:
  int id_;
};
// Edge of the graph. It is the base class of PlanningEdgeNode.
class EdgeNode {
 public:
  EdgeNode(int target);
  virtual ~EdgeNode();
  int target() const;
  virtual EdgeNode* Clone() const;
 protected:
  int target_;
};
// Graph is the base class of PlanningGraph.
class Graph {
 public:
  Graph(bool directed = false);
  Graph(const Graph &graph);
  virtual ~Graph();
  std::vector<Vertex*> vertices() const;
  std::map<int, std::list<EdgeNode*> > adjlist() const;
  std::list<EdgeNode*> neighbors(int v);
  int num_vertices() const;
  int num_edges() const;
  bool directed() const;
  // Get the edge between v1 and v2.
  EdgeNode* Edge(int v1, int v2) const;
  void Clear();
 protected:
  std::vector<Vertex*> vertices_;
  std::map<int, std::list<EdgeNode*> > adjlist_;
  int num_vertices_;
  int num_edges_;
  bool directed_;  // Is it a directed graph?
};
#endif
