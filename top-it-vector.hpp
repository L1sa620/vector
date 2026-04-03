#ifndef TOP_IT_VECTOR_HPP
#define TOP_IT_VECTOR_HPP

#include <cassert>
#include <cstddef>
#include <utility>

namespace topit
{
  template< class T >
  struct Vector
  {
    Vector< T >();
    Vector< T >(const Vector< T >&);
    Vector< T >(Vector< T >&&) noexcept;
    Vector< T >& operator=(const Vector< T >&);
    Vector< T >& operator=(Vector< T >&&) noexcept;
    ~Vector< T >();

    T& operator[](size_t id) noexcept;
    const T& operator[](size_t id) const noexcept;
    size_t getSize() const noexcept;
    size_t getCapacity() const noexcept;
    bool isEmpty() const noexcept;
    void pushBack(const T&);
    void pushFront(const T&);
    void pop_back();
    void swap(Vector< T >& rhs) noexcept;

  private:
    T *data_;
    size_t size_, capacity_;

    explicit Vector< T >(size_t k);
    void pushBackImpl(const T&);
  };
}

template< class T >
topit::Vector< T >::Vector(size_t k):
  data_(static_cast< T * >(::operator new(sizeof(T) * k))),
  size_(0),
  capacity_(k)
{}

template< class T >
topit::Vector< T >::Vector():
  data_(nullptr),
  size_(0),
  capacity_(0)
{}

template< class T >
topit::Vector< T >::Vector(const Vector< T >& rhs):
  Vector(rhs.getSize())
{
  for (size_t i = 0; i < rhs.getSize(); ++i)
  {
    pushBackImpl(rhs[i]);
  }
}

template< class T >
topit::Vector< T >::Vector(Vector< T >&& rhs) noexcept:
  data_(rhs.data_),
  size_(rhs.size_),
  capacity_(rhs.capacity_)
{
  rhs.data_ = nullptr;
  rhs.size_ = 0;
  rhs.capacity_ = 0;
}

template< class T >
topit::Vector< T >& topit::Vector< T >::operator=(Vector< T >&& rhs) noexcept
{
  if (this == std::addressof(rhs))
  {
    return *this;
  }
  Vector< T > cpy(std::move(rhs));
  swap(cpy);
  return *this;
}

template< class T >
topit::Vector< T >::~Vector()
{
  for (size_t i = 0; i < size_; ++i)
  {
    data_[i].~T();
  }
  ::operator delete(data_);
}

template< class T >
topit::Vector< T >& topit::Vector< T >::operator=(const Vector< T >& rhs)
{
  if (this == std::addressof(rhs))
  {
    return *this;
  }
  Vector< T > cpy(rhs);
  swap(cpy);
  return *this;
}

template< class T >
void topit::Vector< T >::swap(Vector< T >& rhs) noexcept
{
  std::swap(data_, rhs.data_);
  std::swap(size_, rhs.size_);
  std::swap(capacity_, rhs.capacity_);
}

template< class T >
T& topit::Vector< T >::operator[](size_t id) noexcept
{
  const Vector< T > *cthis = this;
  return const_cast< T& >((*cthis)[id]);
}

template< class T >
const T& topit::Vector< T >::operator[](size_t id) const noexcept
{
  assert(id < size_);
  return data_[id];
}

template< class T >
size_t topit::Vector< T >::getSize() const noexcept
{
  return size_;
}

template< class T >
size_t topit::Vector< T >::getCapacity() const noexcept
{
  return capacity_;
}

template< class T >
bool topit::Vector< T >::isEmpty() const noexcept
{
  return !size_;
}

template< class T >
void topit::Vector< T >::pushBackImpl(const T& val)
{
  new (data_ + size_) T(val);
  ++size_;
}

template< class T >
void topit::Vector< T >::pushBack(const T& val)
{
  Vector< T > cpy(getSize() + 1);
  for (size_t i = 0; i < getSize(); ++i)
  {
    cpy.pushBackImpl(data_[i]);
  }
  cpy.pushBackImpl(val);
  swap(cpy);
}

template< class T >
void topit::Vector< T >::pushFront(const T& val)
{
  Vector< T > cpy(getSize() + 1);
  cpy.pushBackImpl(val);
  for (size_t i = 0; i < getSize(); ++i)
  {
    cpy.pushBackImpl(data_[i]);
  }
  swap(cpy);
}

template< class T >
void topit::Vector< T >::pop_back()
{
  assert(size_ > 0);
  data_[--size_].~T();
}

#endif
