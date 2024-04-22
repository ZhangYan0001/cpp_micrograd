#ifndef __TEST_H__
#define __TEST_H__

#include "engine.h"
#include <iostream>

namespace Test {
using namespace CMG;

void test_value_init() {
  int a = 10;
  int b = 20;
  //std::cout << __cplusplus << "\n";
  Value<int> v_a(a);
  //Value<int> v_b(b);

  //Value<int> out = v_a + v_b;

  //std::cout << v_a.data << " " << v_a.grad << " " << v_a._op << " " << '\n';
  //std::cout << v_b.data << " " << v_a.grad << " " << v_a._op << " " << '\n';
 /* std::cout << out.data << " " << out.grad << " " << out._op << " " << '\n';*/


}
  

}  // namespace Test

#endif  // !__TEST_H__
