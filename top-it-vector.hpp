#ifndef TOP_IT_VECTOR_HPP
#define TOP_IT_VECTOR_HPP

#include <cassert>
#include <cstddef>
#include <initializer_list>
#include <stdexcept>
#include <iterator>
#include <type_traits>
#include <utility>

namespace topit
{
  template< class T >
  struct Vector
  {
    struct Iterator;
    struct ConstIterator;

    Vector< T >();
    Vector< T >(const Vector< T >&);
    Vector< T >(Vector< T >&&) noexcept;
    explicit Vector< T >(std::initializer_list< T > il);
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
    void reserve(size_t cap);
    void shrinkToFit();
    template< class IT >
    size_t pushBackRange(IT, size_t);
    void pop_back();
    void popFront();
    void insert(size_t i, const T& val);
    void erase(size_t i);
    void insert(size_t i, const Vector< T >& rhs, size_t beg, size_t end);
    void erase(size_t beg, size_t end);
    template< class VecIterator, class FwdIterator,
      class = typename std::enable_if< !std::is_integral< FwdIterator >::value >::type >
    void insert(VecIterator pos, FwdIterator beg, FwdIterator end);
    Iterator insert(Iterator pos, const T& val);
    Iterator insert(Iterator pos, size_t count, const T& val);
    Iterator erase(Iterator pos);
    Iterator begin() noexcept;
    Iterator end() noexcept;
    ConstIterator begin() const noexcept;
    ConstIterator end() const noexcept;
    ConstIterator cbegin() const noexcept;
    ConstIterator cend() const noexcept;
    T& at(size_t id);
    const T& at(size_t id) const;
    void swap(Vector< T >& rhs) noexcept;

  private:
    T *data_;
    size_t size_, capacity_;

    explicit Vector< T >(size_t k);
    void pushBackImpl(const T&);
  };
  template< class T >
  struct Vector< T >::Iterator
  {
    using value_type = T;
    using pointer = T *;
    using reference = T&;
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::random_access_iterator_tag;

    explicit Iterator(T *ptr) noexcept:
      ptr_(ptr)
    {}

    T *base() const noexcept { return ptr_; }
    T& operator*() const noexcept { return *ptr_; }
    T *operator->() const noexcept { return ptr_; }
    T& operator[](difference_type n) const noexcept { return ptr_[n]; }

    Iterator& operator++() noexcept { ++ptr_; return *this; }
    Iterator operator++(int) noexcept { Iterator t(*this); ++(*this); return t; }
    Iterator& operator--() noexcept { --ptr_; return *this; }
    Iterator operator--(int) noexcept { Iterator t(*this); --(*this); return t; }
    Iterator& operator+=(difference_type n) noexcept { ptr_ += n; return *this; }
    Iterator& operator-=(difference_type n) noexcept { ptr_ -= n; return *this; }
    Iterator operator+(difference_type n) const noexcept { return Iterator(ptr_ + n); }
    Iterator operator-(difference_type n) const noexcept { return Iterator(ptr_ - n); }
    difference_type operator-(const Iterator& r) const noexcept { return ptr_ - r.ptr_; }

    bool operator==(const Iterator& r) const noexcept { return ptr_ == r.ptr_; }
    bool operator!=(const Iterator& r) const noexcept { return ptr_ != r.ptr_; }
    bool operator<(const Iterator& r) const noexcept { return ptr_ < r.ptr_; }
    bool operator>(const Iterator& r) const noexcept { return ptr_ > r.ptr_; }
    bool operator<=(const Iterator& r) const noexcept { return ptr_ <= r.ptr_; }
    bool operator>=(const Iterator& r) const noexcept { return ptr_ >= r.ptr_; }

  private:
    T *ptr_;
  };

  template< class T >
  struct Vector< T >::ConstIterator
  {
    using value_type = const T;
    using pointer = const T *;
    using reference = const T&;
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::random_access_iterator_tag;

    explicit ConstIterator(const T *ptr) noexcept:
      ptr_(ptr)
    {}

    ConstIterator(const Iterator& it) noexcept:
      ptr_(it.base())
    {}

    const T& operator*() const noexcept { return *ptr_; }
    const T *operator->() const noexcept { return ptr_; }
    const T& operator[](difference_type n) const noexcept { return ptr_[n]; }

    ConstIterator& operator++() noexcept { ++ptr_; return *this; }
    ConstIterator operator++(int) noexcept { ConstIterator t(*this); ++(*this); return t; }
    ConstIterator& operator--() noexcept { --ptr_; return *this; }
    ConstIterator operator--(int) noexcept { ConstIterator t(*this); --(*this); return t; }
    ConstIterator& operator+=(difference_type n) noexcept { ptr_ += n; return *this; }
    ConstIterator& operator-=(difference_type n) noexcept { ptr_ -= n; return *this; }
    ConstIterator operator+(difference_type n) const noexcept { return ConstIterator(ptr_ + n); }
    ConstIterator operator-(difference_type n) const noexcept { return ConstIterator(ptr_ - n); }
    difference_type operator-(const ConstIterator& r) const noexcept { return ptr_ - r.ptr_; }

    bool operator==(const ConstIterator& r) const noexcept { return ptr_ == r.ptr_; }
    bool operator!=(const ConstIterator& r) const noexcept { return ptr_ != r.ptr_; }
    bool operator<(const ConstIterator& r) const noexcept { return ptr_ < r.ptr_; }
    bool operator>(const ConstIterator& r) const noexcept { return ptr_ > r.ptr_; }
    bool operator<=(const ConstIterator& r) const noexcept { return ptr_ <= r.ptr_; }
    bool operator>=(const ConstIterator& r) const noexcept { return ptr_ >= r.ptr_; }

  private:
    const T *ptr_;
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
topit::Vector< T >::Vector(std::initializer_list< T > il):
  Vector(il.size())
{
  for (auto&& v: il)
  {
    pushBackImpl(v);
  }
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
void topit::Vector< T >::reserve(size_t cap)
{
  if (capacity_ >= cap)
  {
    return;
  }
  T *d = static_cast< T * >(::operator new(sizeof(T) * cap));
  size_t i = 0;
  try
  {
    for (; i < size_; ++i)
    {
      new (d + i) T(std::move(data_[i]));
    }
  }
  catch (...)
  {
    for (size_t j = 0; j < i; ++j)
    {
      (d + j)->~T();
    }
    ::operator delete(d);
    throw;
  }
  for (size_t j = 0; j < size_; ++j)
  {
    data_[j].~T();
  }
  ::operator delete(data_);
  data_ = d;
  capacity_ = cap;
}

template< class T >
void topit::Vector< T >::shrinkToFit()
{
  if (size_ == capacity_)
  {
    return;
  }
  if (size_ == 0)
  {
    ::operator delete(data_);
    data_ = nullptr;
    capacity_ = 0;
    return;
  }
  Vector< T > tmp(size_);
  for (size_t i = 0; i < size_; ++i)
  {
    tmp.pushBackImpl(data_[i]);
  }
  swap(tmp);
}

template< class T >
template< class IT >
size_t topit::Vector< T >::pushBackRange(IT it, size_t k)
{
  reserve(size_ + k);
  for (size_t i = 0; i < k; ++i, ++it)
  {
    pushBackImpl(*it);
  }
  return k;
}

template< class T >
void topit::Vector< T >::popFront()
{
  erase(0);
}

template< class T >
T& topit::Vector< T >::at(size_t id)
{
  const Vector< T > *cthis = this;
  return const_cast< T& >(cthis->at(id));
}

template< class T >
const T& topit::Vector< T >::at(size_t id) const
{
  if (id < size_)
  {
    return (*this)[id];
  }
  throw std::out_of_range("bad id");
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
  if (size_ == capacity_)
  {
    reserve(capacity_ == 0 ? 1 : capacity_ * 2);
  }
  pushBackImpl(val);
}

template< class T >
void topit::Vector< T >::pushFront(const T& val)
{
  insert(0, val);
}

template< class T >
void topit::Vector< T >::pop_back()
{
  assert(size_ > 0);
  data_[--size_].~T();
}

template< class T >
void topit::Vector< T >::insert(size_t i, const T& val)
{
  assert(i <= size_);
  Vector< T > tmp(size_ + 1);
  for (size_t j = 0; j < i; ++j)
  {
    tmp.pushBackImpl(data_[j]);
  }
  tmp.pushBackImpl(val);
  for (size_t j = i; j < size_; ++j)
  {
    tmp.pushBackImpl(data_[j]);
  }
  swap(tmp);
}

template< class T >
void topit::Vector< T >::erase(size_t i)
{
  assert(i < size_);
  for (size_t j = i; j < size_ - 1; ++j)
  {
    data_[j] = std::move(data_[j + 1]);
  }
  data_[--size_].~T();
}

template< class T >
void topit::Vector< T >::insert(size_t i, const Vector< T >& rhs, size_t beg, size_t end)
{
  assert(i <= size_);
  assert(beg <= end && end <= rhs.getSize());
  size_t count = end - beg;
  Vector< T > tmp(size_ + count);
  for (size_t j = 0; j < i; ++j)
  {
    tmp.pushBackImpl(data_[j]);
  }
  for (size_t j = beg; j < end; ++j)
  {
    tmp.pushBackImpl(rhs[j]);
  }
  for (size_t j = i; j < size_; ++j)
  {
    tmp.pushBackImpl(data_[j]);
  }
  swap(tmp);
}

template< class T >
void topit::Vector< T >::erase(size_t beg, size_t end)
{
  assert(beg <= end && end <= size_);
  size_t count = end - beg;
  for (size_t j = beg; j < size_ - count; ++j)
  {
    data_[j] = std::move(data_[j + count]);
  }
  for (size_t j = size_ - count; j < size_; ++j)
  {
    data_[j].~T();
  }
  size_ -= count;
}

template< class T >
template< class VecIterator, class FwdIterator, class >
void topit::Vector< T >::insert(VecIterator pos, FwdIterator beg, FwdIterator end)
{
  size_t i = static_cast< size_t >(pos - begin());
  for (FwdIterator it = beg; it != end; ++it, ++i)
  {
    insert(i, *it);
  }
}

template< class T >
typename topit::Vector< T >::Iterator topit::Vector< T >::insert(Iterator pos, const T& val)
{
  size_t i = static_cast< size_t >(pos - begin());
  insert(i, val);
  return begin() + static_cast< std::ptrdiff_t >(i);
}

template< class T >
typename topit::Vector< T >::Iterator topit::Vector< T >::insert(Iterator pos, size_t count, const T& val)
{
  size_t i = static_cast< size_t >(pos - begin());
  for (size_t j = 0; j < count; ++j)
  {
    insert(i + j, val);
  }
  return begin() + static_cast< std::ptrdiff_t >(i);
}

template< class T >
typename topit::Vector< T >::Iterator topit::Vector< T >::erase(Iterator pos)
{
  size_t i = static_cast< size_t >(pos - begin());
  erase(i);
  return begin() + static_cast< std::ptrdiff_t >(i);
}

template< class T >
typename topit::Vector< T >::Iterator topit::Vector< T >::begin() noexcept
{
  return Iterator(data_);
}

template< class T >
typename topit::Vector< T >::Iterator topit::Vector< T >::end() noexcept
{
  return Iterator(data_ + size_);
}

template< class T >
typename topit::Vector< T >::ConstIterator topit::Vector< T >::begin() const noexcept
{
  return ConstIterator(data_);
}

template< class T >
typename topit::Vector< T >::ConstIterator topit::Vector< T >::end() const noexcept
{
  return ConstIterator(data_ + size_);
}

template< class T >
typename topit::Vector< T >::ConstIterator topit::Vector< T >::cbegin() const noexcept
{
  return ConstIterator(data_);
}

template< class T >
typename topit::Vector< T >::ConstIterator topit::Vector< T >::cend() const noexcept
{
  return ConstIterator(data_ + size_);
}

#endif
