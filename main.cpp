#include "top-it-vector.hpp"
#include <iostream>

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

bool testOperator()
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

int main()
{
  using test_t = bool (*)();
  using pair_t = std::pair< const char*, test_t >;
  pair_t tests[] =
  {
    {"Default vector should be empty", testDefaultVector},
    {"Vector with any value is not empty", testVectorWithValue},
    {"Sizes must be equal as elements", testCopyConstructor},
    {"Inbound access elements", testElementAccess},
    {"Empty vector capacity is zero", testEmptyCapacity},
    {"pushFront inserts element at beginning", testPushFront},
    {"pop_back removes last element", testPopBack},
    {"multiple pushBack keeps correct order", testPushBack2},
    {"pop_back works for single element", testPopBack2},
    {"multiple pushFront keeps correct order", testPushFront2},
    {"copy constructor creates independent copy", testCopyIndependence},
    {"assignment operator creates independent copy", testOperator},
    {"isEmpty works for empty and non-empty vector", testIsEmpty},
    {"pushFront and pop_back edge case", testPushFrontPopBack}
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
