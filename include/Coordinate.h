#ifndef COORDINATE_H_
#define COORDINATE_H_

#include <iostream>
#include <cassert>
#include <cstddef>

template <class T>
class Coordinate {
  template <class U>
  friend Coordinate<U> operator +(const Coordinate<U> &c1,
                                  const Coordinate<U> &c2);
  template <class U> 
  friend Coordinate<U> operator -(const Coordinate<U> &c1,
                                  const Coordinate<U> &c2);
  template <class U> 
  friend Coordinate<U> operator -(const Coordinate<U> &c);
  template <class U> 
  friend Coordinate<U> operator *(U k, const Coordinate<U> &c);
  template <class U> 
  friend Coordinate<U> operator *(const Coordinate<U> &c, U k);
  template <class U>
  friend Coordinate<U> operator /(const Coordinate<U> &c, U k);
  template <class U> 
  friend bool operator ==(const Coordinate<U> &c1,
                          const Coordinate<U> &c2);
  template <class U> 
  friend bool operator !=(const Coordinate<U> &c1,
                          const Coordinate<U> &c2);
 public:
  Coordinate();
  Coordinate(unsigned d);
  Coordinate(T x, T y);
  Coordinate(T x, T y, T z);
  Coordinate(T *arr, unsigned d);
  Coordinate(const Coordinate<T> &c);
  ~Coordinate();
  Coordinate& operator +=(const Coordinate &c);
  Coordinate& operator -=(const Coordinate &c);
  Coordinate& operator *=(T k);
  Coordinate& operator /=(T k);
  Coordinate& operator =(const Coordinate &c);
  T operator [](unsigned i) const;
  T& operator [](unsigned i);
  unsigned dim() const;
 private:
  unsigned dim_;
  T *coord_;
};

template <class T>
Coordinate<T>::Coordinate() {
  dim_ = 0;
  coord_ = NULL;
}

template <class T>
Coordinate<T>::Coordinate(unsigned d) {
  dim_ = d;
  coord_ = NULL;
  if(d > 0) {
	coord_ = new T[d];
  }
}

template <class T>
Coordinate<T>::Coordinate(T x, T y) {
  dim_ = 2;
  coord_ = new T[2];
  coord_[0] = x;
  coord_[1] = y;
}

template <class T>
Coordinate<T>::Coordinate(T x, T y, T z) {
  dim_ = 3;
  coord_ = new T[3];
  coord_[0] = x;
  coord_[1] = y;
  coord_[2] = z;
}

template<class T>
Coordinate<T>::Coordinate(T *arr, unsigned d) {
  if (!arr) {
    dim_ = 0;
    coord_ = NULL;
  } else {
    dim_ = d;
    coord_ = new T[dim_];
    for (unsigned i = 0; i < dim_; ++i) {
      coord_[i] = arr[i];
    }
  }
}

template <class T>
Coordinate<T>::Coordinate(const Coordinate<T> &c) {
  dim_ = c.dim_;
  coord_ = NULL;
  if (dim_ > 0) {
    coord_ = new T[dim_];
    for(unsigned i = 0; i < dim_; ++i) {
      coord_[i] = c[i];
    }
  }
}

template <class T>
Coordinate<T>::~Coordinate() {
  if(coord_) {
	delete[] coord_;
	coord_ = NULL;
  }
}

template <class T>
unsigned Coordinate<T>::dim() const {
  return dim_;
}

template <class T>
Coordinate<T>& Coordinate<T>::operator +=(const Coordinate &c) {
  assert(c.dim_ == dim_);

  for(unsigned i = 0; i < dim_; ++i) {
	coord_[i] += c.coord_[i];
  }
  return *this;
}

template <class T>
Coordinate<T>& Coordinate<T>::operator -=(const Coordinate &c) {
  assert(coordinate.dim_ == dim_);

  for(unsigned i = 0; i < dim_; ++i) {
	coord_[i] -= c.coord_[i];
  }
  return *this;
}

template <class T>
Coordinate<T>& Coordinate<T>::operator *=(T k) {
  for(unsigned i = 0; i < dim_; ++i) {
	coord_[i] *= k;
  }
  return *this;
}

template <class T>
Coordinate<T>& Coordinate<T>::operator /=(T k) {
  for (unsigned i = 0; i < dim_; ++i) {
    coord_[i] /= k;
  }
  return *this;
}

template <class T>
Coordinate<T>& Coordinate<T>::operator =(const Coordinate &c) {
  if (*this == c) {
    return *this;
  }
  if(dim_ > 0) {
	delete[] coord_;
  }
  dim_ = c.dim_;
  coord_ = NULL;
  if (dim_ > 0) {
    coord_ = new T[dim_];
    for(unsigned i = 0; i < dim_; ++i) {
	  coord_[i] = c.coord_[i];
    }
  }
  return *this;
}

template <class T>
T Coordinate<T>::operator [](unsigned i) const {
  assert(i < dim_);

  return coord_[i];
}

template <class T>
T& Coordinate<T>::operator [](unsigned i) {
  assert(i < dim_);

  return coord_[i];
}

template <class T>
Coordinate<T> operator +(const Coordinate<T> &c1,
                         const Coordinate<T> &c2) {
  assert(c1.dim_ == c2.dim_);

  Coordinate<T> temp(c1);
  temp += c2;
  return temp;
}

template <class T>
Coordinate<T> operator -(const Coordinate<T> &c1,
                         const Coordinate<T> &c2) {
  assert(c1.dim_ == c2.dim_);

  Coordinate<T> temp(c1);
  temp -= c2;
  return temp;
}

template <class T>
Coordinate<T> operator -(const Coordinate<T> &c) {
  Coordinate<T> temp(c);
  for(unsigned i = 0; i < temp.dim_; ++i) {
    temp.coord_[i] = -temp.coord_[i];
  }
  return temp;
}

template <class T>
Coordinate<T> operator *(T k, const Coordinate<T> &c) {
  Coordinate<T> temp(c);
  for(unsigned i = 0; i < temp.dim_; ++i) {
    temp.coord_[i] *= k;
  }
  return temp;
}

template <class T>
Coordinate<T> operator *(const Coordinate<T> &c, T k) {
  Coordinate<T> temp(c);
  for(unsigned i = 0; i < temp.dim_; ++i) {
    temp.coord_[i] *= k;
  }
  return temp;
}

template <class T>
Coordinate<T> operator /(const Coordinate<T> &c, T k) {
  Coordinate<T> temp(c);
  for (unsigned i = 0; i < temp.dim_; ++i) {
    temp.coord_[i] /= k;
  }
  return temp;
}

template <class T>
bool operator ==(const Coordinate<T> &c1,
                 const Coordinate<T> &c2) {
  if(c1.dim_ == c2.dim_) {
    for(unsigned i = 0; i < c1.dim_; ++i) {
      if(c1.coord_[i] != c2.coord_[i]) {
        return false;
      }
	}
	return true;
  }
  return false;
}

template <class T>
bool operator !=(const Coordinate<T> &c1, 
                 const Coordinate<T> &c2) {
  if(c1.dim_ == c2.dim_) {
    for(unsigned i = 0; i < c1.dim_; ++i) {
      if(c1.coord_[i] != c2.coord_[i]) {
        return true;
      }
	}
	return false;
  }
  return true;
}

#endif
