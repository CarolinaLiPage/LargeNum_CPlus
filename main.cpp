
#include "largenum.h"
#include <cassert>
#include <iostream>
#include <sstream>

using namespace std;

// check printing and addition
void test1() {
  stringstream strs;

  LargeNum num0("1234567890123456789");
  strs << num0;
  assert(strs.str() == "1,234,567,890,123,456,789");

  strs.str("");
  LargeNum num1(12345);
  strs << num1;
  assert(strs.str() == "12,345");

  strs.str("");
  LargeNum num2(11115);
  LargeNum num3 = num1 + num2;
  strs << num3;
  assert(strs.str() == "23,460");

  strs.str("");
  LargeNum num4(99);
  LargeNum num5 = num1 + num4;
  strs << num5;
  assert(strs.str() == "12,444");

  strs.str("");
  LargeNum num6(99000);
  LargeNum num7 = num1 + num6;
  strs << num7;
  assert(strs.str() == "111,345");
  cout << "test1 complete" << endl;
}

// check comparator operators
void test2() {
  assert(LargeNum(99) == LargeNum(99) && LargeNum(99) != LargeNum(100));
  assert(LargeNum(99) > LargeNum(7) && LargeNum(7) < LargeNum(99));
  assert(LargeNum(105) >= LargeNum(100) && LargeNum(100) <= LargeNum(105));
  assert(LargeNum(99) > LargeNum(-7) && LargeNum(-7) < LargeNum(99));
  assert(LargeNum(-5) > LargeNum(-10) && LargeNum(-10) < LargeNum(-5));
  assert(!(LargeNum(5) > LargeNum(5)));
  cout << "test2 complete" << endl;
}

// check negative numbers
void test3() {
  stringstream strs;
  LargeNum num0("-1234567890123456789");
  strs << num0;
  assert(strs.str() == "-1,234,567,890,123,456,789");

  strs.str("");
  LargeNum num1(-12345);
  strs << num1;
  assert(strs.str() == "-12,345");

  strs.str("");
  LargeNum numZero(-0000);
  strs << numZero;
  assert(strs.str() == "0");

  assert(LargeNum(0).isZero() && LargeNum(-0).isZero());
  assert(LargeNum(0) == LargeNum(-0));
  assert(LargeNum(0).negate() == LargeNum(-0));
  assert(LargeNum(100) - LargeNum(100) == LargeNum(0));
  assert(LargeNum(100) + LargeNum(-100) == LargeNum(0));
  assert(LargeNum(100) - LargeNum(-100) == LargeNum(200));
  assert(LargeNum(-100) - LargeNum(-100) == LargeNum(0));
  assert(LargeNum(-100) + LargeNum(100) == LargeNum(0));
  assert(LargeNum(100) - LargeNum(7) == LargeNum(93));
  assert(LargeNum(7) - LargeNum(100) == LargeNum(-93));
  assert(LargeNum(-7) + LargeNum(-100) == LargeNum(-107));

  cout << "test3 complete" << endl;
}

// check multiplication
void test4() {
  assert(LargeNum(25) * LargeNum(0) == LargeNum(0));
  assert(LargeNum(25) * LargeNum(5) == LargeNum(125));
  assert(LargeNum(-25) * LargeNum(-5) == LargeNum(125));
  assert(LargeNum(-25) * LargeNum(5) == LargeNum(-125));
  assert(LargeNum(25) * LargeNum(-5) == LargeNum(-125));
  assert(LargeNum("123456789123456789") * LargeNum("123456789123456789") ==
         LargeNum("15241578780673678515622620750190521"));
  cout << "test4 complete" << endl;
}

// check division
// use small numbers to avoid excessive computation
void test5() {
  assert(LargeNum(0) / LargeNum(5) == LargeNum(0));
  assert(LargeNum(25) / LargeNum(5) == LargeNum(5));
  assert(LargeNum(-25) / LargeNum(-5) == LargeNum(5));
  assert(LargeNum(-25) / LargeNum(5) == LargeNum(-5));
  assert(LargeNum(25) / LargeNum(-5) == LargeNum(-5));
  assert(LargeNum("25") / LargeNum("7") == LargeNum("3"));
  assert(LargeNum("7") / LargeNum("25") == LargeNum("0"));
  cout << "test5 complete" << endl;
}

// check prefix and postfix operators
void test6() {
  LargeNum num0(10);
  assert(num0++ == LargeNum(10));
  assert(num0 == LargeNum(11));
  assert(--num0 == LargeNum(10));
  assert(num0-- == LargeNum(10));
  assert(num0 == LargeNum(9));
  assert(++num0 == LargeNum(10));
  assert(num0-- == LargeNum(10));
  assert(num0 == LargeNum(9));
  num0.negate();
  assert(++num0 == LargeNum(-8));
  assert(--num0 == LargeNum(-9));

  LargeNum num1(1);
  assert(--num1 == LargeNum(0));
  assert(--num1 == LargeNum(-1));
  assert(++num1 == LargeNum(0));
  cout << "test6 complete" << endl;
}

// run all tests
int main() {
  test1();
  test2();
  test3();
  test4();
  test5();
  test6();

  cout << "Done." << endl;
}
