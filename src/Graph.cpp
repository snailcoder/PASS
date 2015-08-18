#include <cstddef>
#include <stdexcept>
#include <iostream>
#include <algorithm>
#include "Graph.h"

using namespace std;

Vertex::Vertex(int id) : id_(id) {
}
Vertex::~Vertex() {
}
int Vertex::id() const {
  return id_;
}
// Virtual copy pattern is used to implement deep copy of base class pointer.
Vertex* Vertex::Clone() const {
  return new Vertex(*this);
}
EdgeNode::EdgeNode(int target) : target_(target) {
}
EdgeNode::~EdgeNode() {
}
int EdgeNode::target() const {
  return target_;
}
// Virtual copy pattern is used to implement deep copy of base class pointer.
EdgeNode* EdgeNode::Clone() const {
  return new EdgeNode(*this);
}
Graph::Graph(bool directed) 
  : num_vertices_(0), 
    num_edges_(0), 
    directed_(directed) {
}
Graph::Graph(const Graph &graph)
  : vertices_(graph.vertices_), 
    adjlist_(graph.adjlist_), 
    num_vertices_(graph.num_vertices_), 
    num_edges_(graph.num_edges_), 
    directed_(graph.directed_) {
  for (std::vector<Vertex*>::iterator iter = vertices_.begin();
	  iter != vertices_.end(); ++iter) {
    *iter = (*iter)->Clone();  // Virtual copy
  }
  for (std::map<int, std::list<EdgeNode*> >::iterator aiter = adjlist_.begin();
	  aiter != adjlist_.end(); ++aiter) {
    for (std::list<EdgeNode*>::iterator eiter = aiter->second.begin();
		eiter != aiter->second.end(); ++eiter) {
      *eiter = (*eiter)->Clone();  // Virtual copy
	}
  }
}
Graph::~Graph() {
  Clear();
}
EdgeNode* Graph::Edge(int v1, int v2) const {
  if (v1 < 0 || v1 >= num_vertices_ || v2 < 0 || v2 >= num_vertices_) {
    throw std::invalid_argument("Invalid vertex id.");
  }
  std::list<EdgeNode*> edges;
  for (std::map<int, std::list<EdgeNode*> >::const_iterator
      iter = adjlist_.begin(); iter != adjlist_.end(); ++iter) {
    if (iter->first == v1) {
      edges = iter->second;
      break;
	}
  }
  for (std::list<EdgeNode*>::const_iterator iter = edges.begin();
      iter != edges.end(); ++iter) {
    if ((*iter)->target() == v2) {
      return *iter;
    }
  }
  return NULL;
}
std::vector<Vertex*> Graph::vertices() const {
  return vertices_;
}
std::map<int, std::list<EdgeNode*> > Graph::adjlist() const {
  return adjlist_;
}
std::list<EdgeNode*> Graph::neighbors(int v) {
  if (v < 0 || v >= num_vertices_) {
    throw std::invalid_argument("Invalid vertex id.");
  }
  return adjlist_[v];
}
int Graph::num_vertices() const {
  return num_vertices_;
}
int Graph::num_edges() const {
  return num_edges_;
}
bool Graph::directed() const {
  return directed_;
}
void Graph::Clear() {
  for (std::map<int, std::list<EdgeNode*> >::iterator viter = adjlist_.begin();
	  viter != adjlist_.end(); ++viter) {
    for (std::list<EdgeNode*>::iterator eiter = viter->second.begin();
		eiter != viter->second.end(); ++eiter) {
      delete *eiter;
	}
  }
  for (std::vector<Vertex*>::iterator iter = vertices_.begin();
	  iter != vertices_.end(); ++iter) {
    delete *iter;
  }
  num_vertices_ = num_edges_ = 0;
  adjlist_.clear();
  vertices_.clear();
}
