#ifndef TOP_IT_VECTOR_HPP
#define TOP_IT_VECTOR_HPP
#include <cstddef>

namespace topit
{
  template < class T >
  struct Vector
  {
    Vector();
    Vector(const Vector< T >&) = delete;
    ~Vector();
    Vector< T >& operator=(const Vector< T >&) = delete;

    bool isEmpty() const noexcept;
    size_t getSize() const noexcept;
    size_t getCapacity() const noexcept;

    void pushBack(const T&);
    void popBack();

  private:
    T* data_;
    size_t size_, capacity_;
  };
}

template < class T >
bool topit::Vector< T >::isEmpty() const noexcept
{
  return !size_;
}

template < class T >
topit::Vector< T >::Vector(): data_(nullptr), size_(0), capacity_(0)
{
}

template < class T >
topit::Vector< T >::~Vector()
{
  delete[] data_;
}

template < class T >
void topit::Vector< T >::pushBack(const T&)
{
}

#endif
