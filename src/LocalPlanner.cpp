#include "LocalPlanner.h"

LocalPlanner::LocalPlanner(ConfigurationChecker *checker, Metric *metric)
  : checker_(checker), 
    metric_(metric) {
}
LocalPlanner::~LocalPlanner() {
}
Metric *LocalPlanner::metric() const {
  return metric_;
}
void LocalPlanner::set_checker(ConfigurationChecker *checker) {
  checker_ = checker;
}
void LocalPlanner::set_metric(Metric *metric) {
  metric_ = metric;
}