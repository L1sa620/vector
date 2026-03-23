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
    {"pushFront inserts element at beginning", testPushFront}
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
