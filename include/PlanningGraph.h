#ifndef PLANNINGGRAPH_H_
#define PLANNINGGRAPH_H_

#include "Graph.h"

// PlanningVertex = Vertex + state + validity
class PlanningVertex : public Vertex {
 public:
  PlanningVertex(int id, const RealCoord &state, bool validity = true);
  PlanningVertex(const PlanningVertex &v);
  bool validity() const;
  void set_validity(bool valid);
  RealCoord state() const;
  void set_state(const RealCoord &state);
  virtual Vertex* Clone() const;
 private:
  bool validity_;
  RealCoord state_;
};
// PlanningEdgeNode = EdgeNode + weight + validity
class PlanningEdgeNode : public EdgeNode {
 public:
  PlanningEdgeNode(int target, double weight = 1.0, bool validity = true);
  double weight() const;
  void set_weight(double weight);
  bool validity() const;
  void set_validity(bool valid);
  virtual EdgeNode* Clone() const;
 private:
  double weight_;
  bool validity_;
};
// PlanningGraph is used in any planning task.
class PlanningGraph : public Graph {
 public:
  PlanningGraph(bool directed = false);
  PlanningGraph(const PlanningGraph &graph);
  int AddVertex(const RealCoord &state);
  IntVector AddVertex(const RealCoordVector &states);
  // Extract the coordinate(or state) of all vertices.
  RealCoordVector ExtractStates() const;
  void AddEdge(int v1, int v2, double weight = 1.0, bool valid = true);
  double EdgeWeight(int v1, int v2) const;
  void SetEdgeWeight(int v1, int v2, double weight);
  bool EdgeValidity(int v1, int v2) const;
  void SetEdgeValidity(int v1, int v2, bool validity);
};

#endif