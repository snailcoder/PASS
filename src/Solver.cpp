#include "Solver.h"

Solver::Solver(ConfigurationSpace *cspace, Metric *metric)
  : cspace_(cspace), metric_(metric) {
}
void Solver::set_cspace(ConfigurationSpace *cspace) {
  cspace_ = cspace;
}
void Solver::set_metric(Metric *metric) {
  metric_ = metric;
}