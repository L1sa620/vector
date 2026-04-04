#include <iostream>
#include "top-it-vector.hpp"

bool testDefaultVector()
{
  topit::Vector< int > v;
  return v.isEmpty();
}

bool testVectorWithValue()
{
  topit::Vector< int > v;
  v.pushBack(1);
  return !v.isEmpty();
}

bool testCopyConstructor()
{
  topit::Vector< int > v;
  v.pushBack(1);
  topit::Vector< int > yay = v;
  bool isAllEqual = v.getSize() == yay.getSize();
  for (size_t i = 0; i < v.getSize(); i++)
  {
    isAllEqual = isAllEqual && v[i] == yay[i];
  }
  return isAllEqual;
}

bool testElementAccess()
{
  topit::Vector< int > v;
  v.pushBack(1);
  v.pushBack(2);
  return v[0] == 1 && v[1] == 2;
}

bool testEmptyCapacity()
{
  topit::Vector< int > v;
  return v.getCapacity() == 0;
}

bool testPushFront()
{
  topit::Vector< int > v;
  v.pushBack(2);
  v.pushFront(1);
  return v.getSize() == 2 && v[0] == 1 && v[1] == 2;
}

bool testPopBack()
{
  topit::Vector< int > v;
  v.pushBack(1);
  v.pushBack(2);
  v.pop_back();
  return v.getSize() == 1 && v[0] == 1;
}

bool testPushBack2()
{
  topit::Vector< int > v;
  v.pushBack(1);
  v.pushBack(2);
  v.pushBack(3);
  return v.getSize() == 3 && v[0] == 1 && v[1] == 2 && v[2] == 3;
}

bool testPopBack2()
{
  topit::Vector< int > v;
  v.pushBack(5);
  v.pop_back();
  return v.getSize() == 0 && v.isEmpty();
}

bool testPushFront2()
{
  topit::Vector< int > v;
  v.pushFront(3);
  v.pushFront(2);
  v.pushFront(1);
  return v.getSize() == 3 && v[0] == 1 && v[1] == 2 && v[2] == 3;
}

bool testCopyIndependence()
{
  topit::Vector< int > v;
  v.pushBack(1);
  v.pushBack(2);
  topit::Vector< int > copy = v;
  v.pushBack(3);
  return copy.getSize() == 2 && copy[0] == 1 && copy[1] == 2;
}

bool testAssignOperator()
{
  topit::Vector< int > a;
  a.pushBack(1);
  a.pushBack(2);
  topit::Vector< int > b;
  b = a;
  a.pushBack(3);
  return b.getSize() == 2 && b[0] == 1 && b[1] == 2;
}

bool testIsEmpty()
{
  topit::Vector< int > v;
  if (!v.isEmpty())
  {
    return false;
  }
  v.pushBack(1);
  if (v.isEmpty())
  {
    return false;
  }
  v.pop_back();
  return v.isEmpty();
}

bool testPushFrontPopBack()
{
  topit::Vector< int > v;
  v.pushFront(1);
  v.pushFront(2);
  v.pop_back();
  v.pop_back();
  return v.getSize() == 0 && v.isEmpty();
}
bool testElementConstAccess()
{
  topit::Vector< int > v;
  v.pushBack(1);
  v.pushBack(2);
  const topit::Vector< int >& rv = v;
  return rv[0] == 1 && rv[1] == 2;
}

bool testInitializerList()
{
  topit::Vector< int > v{1, 2, 3};
  return v.getSize() == 3 && v[0] == 1 && v[1] == 2 && v[2] == 3;
}

bool testAtOutOfBound()
{
  topit::Vector< int > v;
  try
  {
    v.at(0);
    return false;
  }
  catch (const std::out_of_range&)
  {
    return true;
  }
  catch (...)
  {
    return false;
  }
}

bool testAtInbound()
{
  topit::Vector< int > v;
  v.pushBack(42);
  try
  {
    int& val = v.at(0);
    return val == 42;
  }
  catch (...)
  {
    return false;
  }
}

bool testConstAtOutOfBound()
{
  const topit::Vector< int > v;
  try
  {
    v.at(0);
    return false;
  }
  catch (const std::out_of_range&)
  {
    return true;
  }
  catch (...)
  {
    return false;
  }
}

bool testConstAtInbound()
{
  topit::Vector< int > v;
  v.pushBack(42);
  const topit::Vector< int >& rv = v;
  try
  {
    const int& val = rv.at(0);
    return val == 42;
  }
  catch (...)
  {
    return false;
  }
}
bool testReserve()
{
  topit::Vector< int > v;
  v.reserve(10);
  return v.getCapacity() >= 10 && v.getSize() == 0;
}

bool testShrinkToFit()
{
  topit::Vector< int > v;
  v.reserve(100);
  v.pushBack(1);
  v.pushBack(2);
  v.shrinkToFit();
  return v.getCapacity() == 2 && v.getSize() == 2 && v[0] == 1 && v[1] == 2;
}

bool testPushBackRange()
{
  int arr[] = {4, 5, 6};
  topit::Vector< int > v{1, 2, 3};
  v.pushBackRange(arr, 3);
  return v.getSize() == 6 && v[3] == 4 && v[4] == 5 && v[5] == 6;
}

bool testPopFront()
{
  topit::Vector< int > v{1, 2, 3};
  v.popFront();
  return v.getSize() == 2 && v[0] == 2 && v[1] == 3;
}
bool testIteratorTraversal()
{
  topit::Vector< int > v{1, 2, 3};
  int sum = 0;
  for (auto it = v.begin(); it != v.end(); ++it)
  {
    sum += *it;
  }
  return sum == 6;
}

bool testIteratorArithmetic()
{
  topit::Vector< int > v{10, 20, 30};
  auto it = v.begin();
  it += 2;
  bool ok = *it == 30;
  ok = ok && *(it - 1) == 20;
  ok = ok && it[0] == 30;
  ok = ok && (v.end() - v.begin()) == 3;
  return ok;
}

bool testConstIterator()
{
  topit::Vector< int > v{1, 2, 3};
  const topit::Vector< int >& rv = v;
  int sum = 0;
  for (auto it = rv.cbegin(); it != rv.cend(); ++it)
  {
    sum += *it;
  }
  return sum == 6;
}

bool testIteratorConvertsToConst()
{
  topit::Vector< int > v{5, 6};
  topit::Vector< int >::ConstIterator it = v.begin();
  return *it == 5 && *(it + 1) == 6;
}

int main()
{
  using test_t = bool(*)();
  using pair_t = std::pair< const char *, test_t >;

  pair_t tests[] =
  {
    {"Default vector should be empty", testDefaultVector},
    {"Vector with any value is not empty", testVectorWithValue},
    {"Sizes must be equal as elements", testCopyConstructor},
    {"Inbound access elements", testElementAccess},
    {"Const inbound access elements", testElementConstAccess},
    {"Empty vector capacity is zero", testEmptyCapacity},
    {"pushFront inserts element at beginning", testPushFront},
    {"pop_back removes last element", testPopBack},
    {"multiple pushBack keeps correct order", testPushBack2},
    {"pop_back works for single element", testPopBack2},
    {"multiple pushFront keeps correct order", testPushFront2},
    {"copy constructor creates independent copy", testCopyIndependence},
    {"assignment operator creates independent copy", testAssignOperator},
    {"isEmpty works correctly", testIsEmpty},
    {"pushFront and pop_back edge case", testPushFrontPopBack},
    {"initializer_list constructor", testInitializerList},
    {"at() throws out_of_range", testAtOutOfBound},
    {"at() returns correct value", testAtInbound},
    {"const at() throws out_of_range", testConstAtOutOfBound},
    {"const at() returns correct value", testConstAtInbound},
    {"reserve increases capacity", testReserve},
    {"shrinkToFit reduces capacity to size", testShrinkToFit},
    {"pushBackRange appends elements", testPushBackRange},
    {"popFront removes first element", testPopFront},
    {"iterator traversal sums correctly", testIteratorTraversal},
    {"iterator arithmetic: +=, -, [], end-begin", testIteratorArithmetic},
    {"ConstIterator traversal via cbegin/cend", testConstIterator},
    {"Iterator converts to ConstIterator", testIteratorConvertsToConst},
  };

  const size_t count = sizeof(tests) / sizeof(pair_t);
  std::cout << std::boolalpha;
  bool pass = true;
  for (size_t i = 0; i < count; ++i)
  {
    bool res = tests[i].second();
    std::cout << res << ": ";
    std::cout << tests[i].first << '\n';
    pass = pass && res;
  }
  std::cout << pass;
  std::cout << ": RESULT\n";
}
