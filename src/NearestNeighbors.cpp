#include "NearestNeighbors.h"

NearestNeighbors::NearestNeighbors(Metric *metric) : metric_(metric) {
}
NearestNeighbors::~NearestNeighbors() {
}
Metric* NearestNeighbors::metric() const {
  return metric_;
}
void NearestNeighbors::set_metric(Metric *metric) {
  metric_ = metric;
}