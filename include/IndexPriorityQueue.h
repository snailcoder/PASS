#ifndef INDEXPRIORITYQUEUE_H_
#define INDEXPRIORITYQUEUE_H_

#include <stdexcept>
#include <functional>
#include <vector>
#include <map>

// Index priority queue is a special priority queue. Items in index priority
// queue are indices instead of real values. However, if you pop these indices 
// one by one, you will find that they are actually ordered by the value of 
// which they are pointing to! If you have nay questions about this amazing data
// structure, please refer to Algorithms(4th edition, Robert Sedgewick and
// Kevin Wayne).
template<class T, class Compare = std::less<T> >
class IndexPriorityQueue {
 public:
  IndexPriorityQueue(const Compare &cmp = Compare());
  // Push val into queue and associate it with the index k.
  void Push(int k, const T &val);
  // Pop the minimal item in the queue and return its index.
  int Pop();
  // Peek the minimal item in the queue.
  const T& Top() const;
  // Return the index of minimal item.
  int TopIndex() const;
  // Delete the item associated with index k.
  void Delete(int k);
  // Update the value associated with index k as val.
  void Update(int k, const T &val);
  // Check if the queue contains index k.
  bool Contain(int k) const;
  // Check if the queue is empty.
  bool Empty() const;
  typedef typename std::vector<T>::size_type size_type;
  size_type Size() const;
 private:
  // Exchange the ith and jth item in the queue.
  void Exchange(size_type i, size_type j);
  // Bottom-up reheapify when ith node is greater(less) than its parents.
  void Swim(size_type i);
  // Top-down reheapify when ith node is less(greater) than its children.
  void Sink(size_type i);
  // Trace the position of index. 
  std::map<int, size_type> index_accompany_;
  // The heap consist of indices.
  std::vector<int> index_heap_;
  // Map index to its value.
  std::map<int, T> values_;
  size_type size_;
  Compare comp_;
};
template<class T, class Compare>
IndexPriorityQueue<T, Compare>::IndexPriorityQueue(const Compare &cmp)
  : size_(0), 
    comp_(cmp) {
}
template<class T, class Compare>
void IndexPriorityQueue<T, Compare>::Push(int k, const T &val) {
  if (Contain(k)) {
    throw std::invalid_argument("Index is already in the priority queue.");
  }
  values_[k] = val;
  // Put k at the end of index_heap_.
  index_heap_.push_back(k);
  // Record the current position of index k in index_heap_.
  index_accompany_[k] = size_; 
  // Let k bubble up to reheapify.
  Swim(size_);
  ++size_;
}
template<class T, class Compare>
int IndexPriorityQueue<T, Compare>::Pop() {
  if (Empty()) {
    throw std::out_of_range("Priority queue empty before pop.");
  }
  int index = index_heap_.front();
  // Swap the first and the last element of index_heap_.
  // At the same time, swap their positions recorded in the index_accompany_.
  Exchange(0, --size_);
  // Then, let the first element of index_heap_ sink to reheapify.
  Sink(0);
  index_heap_.pop_back();
  values_.erase(index);
  index_accompany_.erase(index);
  return index;
}
template<class T, class Compare>
void IndexPriorityQueue<T, Compare>::Delete(int k) {
  if (!Contain(k)) {
    throw std::invalid_argument("Index is not in the priority queue.");
  }
  // Locate the position of index k.
  int i = index_accompany_[k];
  // Swap the ith and the last element of index_heap_.
  // At the same time, swap their positions recorded in the index_accompany_.
  Exchange(i, --size_);
  // Let the ith element of index_heap_ swim and sink to reheapify.
  Swim(i);
  Sink(i);
  index_heap_.pop_back();
  values_.erase(k);
  index_accompany_.erase(k);
}
template<class T, class Compare>
void IndexPriorityQueue<T, Compare>::Update(int k, const T &val) {
  if (!Contain(k)) {
    throw std::invalid_argument("Index is not in the priority queue.");
  }
  values_[k] = val;
  Swim(index_accompany_[k]);
  Sink(index_accompany_[k]);
}
template<class T, class Compare>
const T& IndexPriorityQueue<T, Compare>::Top() const {
  if (Empty()) {
	  throw std::out_of_range("Priority queue underflow.");
  }
  return values_.find(index_heap_.front())->second;
}
template<class T, class Compare>
int IndexPriorityQueue<T, Compare>::TopIndex() const {
  return index_heap_.front();
}
template<class T, class Compare>
bool IndexPriorityQueue<T, Compare>::Contain(int k) const {
  return index_accompany_.find(k) != index_accompany_.end();
}
template<class T, class Compare>
bool IndexPriorityQueue<T, Compare>::Empty() const {
  return size_ == 0;
}
template<class T, class Compare>
typename IndexPriorityQueue<T, Compare>::size_type 
    IndexPriorityQueue<T, Compare>::Size() const {
  return size_;
}
template<class T, class Compare>
void IndexPriorityQueue<T, Compare>::Exchange(
    typename IndexPriorityQueue<T, Compare>::size_type i, 
    typename IndexPriorityQueue<T, Compare>::size_type j) {
  int temp = index_heap_[i];
  index_heap_[i] = index_heap_[j];
  index_heap_[j] = temp;
  index_accompany_[index_heap_[i]] = i;
  index_accompany_[index_heap_[j]] = j;
}
template<class T, class Compare>
void IndexPriorityQueue<T, Compare>::Swim(
    typename IndexPriorityQueue<T, Compare>::size_type i) {
  while (i > 0
      && comp_(values_[index_heap_[i]], 
               values_[index_heap_[(i - 1) / 2]])) {
    Exchange(i, (i - 1) / 2);
    i = (i - 1) / 2;
  }
}
template<class T, class Compare>
void IndexPriorityQueue<T, Compare>::Sink(
    typename IndexPriorityQueue<T, Compare>::size_type i) {
  if (size_ != 0) {
    while (2 * i + 1 <= size_ - 1) {
      size_type j = 2 * i + 1;
	  if (j < size_ - 1 
          && comp_(values_[index_heap_[j + 1]], 
                   values_[index_heap_[j]])) {
        ++j;
	  }
	  if (comp_(values_[index_heap_[i]], values_[index_heap_[j]])) {
        break;
	  }
      Exchange(i, j);
      i = j;
    }
  }
}

#endif