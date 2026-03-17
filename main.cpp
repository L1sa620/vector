#include <iostream>
#include <iomanip>
#include "top-it-vector.hpp"

bool testDefaultVector()
{
  Vector< int > v;
  return v.isEmpty();
}

int main()
{
//  std::cout << "Default: " << testDefaultVector() << "\n";
  using test_t = bool(*)();
  using pair_t = std::pair< const char*, test_t>;
  pait_t tests[] = {
    testDefaultVector
  };
  const size_t count = sizeof(tests) / sizeof(pair_t);
//Только для статических массивов
  for (size_t i=0; i < count; ++i){
    bool res = tests[i].second();
    std::cout << tests[i].first << ": " << res << "\n";
  }
}
