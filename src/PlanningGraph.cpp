#include <typeinfo>
#include "PlanningGraph.h"

PlanningVertex::PlanningVertex(int id, const RealCoord &state, bool validity)
  : Vertex(id), 
    state_(state), 
    validity_(validity) {
}
PlanningVertex::PlanningVertex(const PlanningVertex &v) 
  : Vertex(v.id_), 
    state_(v.state_), 
    validity_(v.validity_){
}
bool PlanningVertex::validity() const {
  return validity_;
}
void PlanningVertex::set_validity(bool valid) {
  validity_ = valid;
}
RealCoord PlanningVertex::state() const {
  return state_;
}
void PlanningVertex::set_state(const RealCoord &state) {
  state_ = state;
}
// Virtual copy pattern is used to implement deep copy of base class pointer.
Vertex* PlanningVertex::Clone() const {
  return new PlanningVertex(*this);
}
PlanningEdgeNode::PlanningEdgeNode(int target, double weight, bool validity)
  : EdgeNode(target), 
    weight_(weight), 
    validity_(validity) {
}
double PlanningEdgeNode::weight() const {
  return weight_;
}
void PlanningEdgeNode::set_weight(double weight) {
  weight_ = weight;
}
bool PlanningEdgeNode::validity() const {
  return validity_;
}
void PlanningEdgeNode::set_validity(bool valid) {
  validity_ = valid;
}
// Virtual copy pattern is used to implement deep copy of base class pointer.
EdgeNode* PlanningEdgeNode::Clone() const {
  return new PlanningEdgeNode(*this);
}
PlanningGraph::PlanningGraph(bool directed) : Graph(directed) {
}
PlanningGraph::PlanningGraph(const PlanningGraph &graph) : Graph(graph) {
}
int PlanningGraph::AddVertex(const RealCoord &state) {
  PlanningVertex *v = new PlanningVertex(num_vertices_, state);
  vertices_.push_back(v);
  ++num_vertices_;
  return v->id();  
}
IntVector PlanningGraph::AddVertex(const RealCoordVector &states) {
  IntVector vs;
  for (RealCoordVector::const_iterator iter = states.begin(); 
	  iter != states.end(); ++iter) {
    PlanningVertex *v = new PlanningVertex(num_vertices_, *iter);
    vertices_.push_back(v);
    vs.push_back(v->id());
    ++num_vertices_;
  }
  return vs;
}
RealCoordVector PlanningGraph::ExtractStates() const {
  RealCoordVector states;
  for (std::vector<Vertex*>::const_iterator iter = vertices_.begin();
	  iter != vertices_.end(); ++iter) {
    states.push_back(static_cast<PlanningVertex*>(*iter)->state());
  }
  return states;
}
void PlanningGraph::AddEdge(int v1, int v2, double weight, bool valid) {
  if (v1 < 0 || v1 >= num_vertices_ || v2 < 0 || v2 >= num_vertices_) {
    throw std::invalid_argument("Invalid vertex id.");
  }
  PlanningEdgeNode *enode_v2 = new PlanningEdgeNode(v2, weight, valid);
  adjlist_[v1].push_back(enode_v2);
  if (!directed_) {
    PlanningEdgeNode *enode_v1 = new PlanningEdgeNode(v1, weight, valid);
    adjlist_[v2].push_back(enode_v1);
  }
  ++num_edges_;
}
double PlanningGraph::EdgeWeight(int v1, int v2) const {
  EdgeNode *edge = Edge(v1, v2);
  if (!edge) {
    throw std::invalid_argument("No such edge in the graph.");
  }
  return static_cast<PlanningEdgeNode*>(edge)->weight();
}
void PlanningGraph::SetEdgeWeight(int v1, int v2, double weight) {
  EdgeNode *edge1 = Edge(v1, v2);
  if (!edge1) {
    throw std::invalid_argument("No such edge in the graph.");
  }
  static_cast<PlanningEdgeNode*>(edge1)->set_weight(weight);
  if (!directed_) {
    EdgeNode *edge2 = Edge(v2, v1);
    static_cast<PlanningEdgeNode*>(edge2)->set_weight(weight);
  } 
}
bool PlanningGraph::EdgeValidity(int v1, int v2) const {
  EdgeNode *edge = Edge(v1, v2);
  if (!edge) {
    throw std::invalid_argument("No such edge in the graph.");
  }
  return static_cast<PlanningEdgeNode*>(edge)->validity();
}
void PlanningGraph::SetEdgeValidity(int v1, int v2, bool validity) {
  EdgeNode *edge1 = Edge(v1, v2);
  if (!edge1) {
    throw std::invalid_argument("No such edge in the graph.");
  }
  static_cast<PlanningEdgeNode*>(edge1)->set_validity(validity);
  if (!directed_) {
    EdgeNode *edge2 = Edge(v2, v1);
    static_cast<PlanningEdgeNode*>(edge2)->set_validity(validity);
  }
}
