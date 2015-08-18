#ifndef PRIORITYQUEUE_H_
#define PRIORITYQUEUE_H_

#include <vector>
#include <algorithm>

template <class T, class Compare>
class PriorityQueue {
 public:
  PriorityQueue(const Compare &cmp);
  void Push(const T &val);
  void Pop();
  void Update();
  const T& Top() const;
  bool Empty() const;
  bool Contain(const T &val) const;
  typename std::vector<T>::size_type Size() const;
 private:
  std::vector<T> v_;
  Compare comp_;
};

template<class T, class Compare>
PriorityQueue<T, Compare>::PriorityQueue(const Compare &cmp) : comp_(cmp) {
}
template<class T, class Compare>
void PriorityQueue<T, Compare>::Push(const T &val) {
  v_.push_back(val);
  std::push_heap(v_.begin(), v_.end(), comp_);
}
template<class T, class Compare>
void PriorityQueue<T, Compare>::Pop() {
  std::pop_heap(v_.begin(), v_.end(), comp_);
  v_.pop_back();
}
template<class T, class Compare>
void PriorityQueue<T, Compare>::Update() {
  std::make_heap(v_.begin(), v_.end(), comp_);
}
template<class T, class Compare>
const T& PriorityQueue<T, Compare>::Top() const {
  return v_.front();
}
template<class T, class Compare>
bool PriorityQueue<T, Compare>::Empty() const {
  return v_.empty();
}
template<class T, class Compare>
bool PriorityQueue<T, Compare>::Contain(const T &val) const {
  return std::find(v_.begin(), v_.end(), T) != v_.end();
}
template<class T, class Compare>
typename std::vector<T>::size_type PriorityQueue<T, Compare>::Size() const {
  return v_.size();
}

#endif