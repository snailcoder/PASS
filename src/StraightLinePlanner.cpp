#include "StraightLinePlanner.h"

#include <fstream>

StraightLinePlanner::StraightLinePlanner(double resolution, 
                                         ConfigurationChecker *checker, 
                                         Metric *metric)
  : LocalPlanner(checker, metric), 
    resolution_(resolution) {
}
bool StraightLinePlanner::Plan(const RealCoord &begin, 
							   const RealCoord &end) const {
  if (!checker_ || !metric_) {
    return false;
  }
  int step = (int)(metric_->Distance(begin, end) / resolution_);
  if (step > 0) {
    unsigned dim = checker_->cspace()->dim();
    RealCoord delta(dim);
	for (unsigned i = 0; i < dim; ++i) {
      delta[i] = (double)(end[i] - begin[i]) / step;
	}
    RealCoord current = begin;
	for (int i = 0; i < step; ++i) {
      current += delta;
	  if (!checker_->FreeConfiguration(current)) {
        return false;
	  }
	}
  }
  return true;
}
bool StraightLinePlanner::operator ()(const RealCoord &begin, 
									  const RealCoord &end) const {
  return Plan(begin, end);
}