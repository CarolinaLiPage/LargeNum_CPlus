#include "largenum.h"
#include <algorithm>
#include <cassert>
#include <iostream>

using namespace std;

ostream &operator<<(ostream &out, const LargeNum &num) {
  if (!num.isPositive) {
    out << "-" << endl;
  }
  string strWithComma;
  // insert commas after each 3 characters
  // process forward, go through num.str, append to new str
  // counter to count number of characters
  int counter = 0;
  for (long long i = num.str.size() - 1; i >= 0; i--) {
    counter++;
    strWithComma += num.str[i];
    // if need to append comma
    if (i < num.str.size() - 1 && (num.str.size() - counter) % 3 == 0) {
      strWithComma += ','; // append to the front
    }
  }
  out << strWithComma;
  return out;
}

// default constructor from string
LargeNum::LargeNum(const string &str) {
  // when call constructor LargeNum, if no value passed by str, then
  // str is optional, default value is 0
  // if the 1st char of str = minus, set is posi to false
  if (!str.empty() && str[0] == '-') {
    isPositive = false;
    this->str = str.substr(1, str.size() - 1);
  } else {
    isPositive = true;
    this->str = str; // copy the whole string over
  }
  if (this->str.empty()) {
    this->str = "0";
    isPositive = true;
  }
  // reversed string
  this->str = reverse(this->str);
}

// constructor from int
LargeNum::LargeNum(int anInteger) {
  // check if negative anInteger < 0
  if (anInteger < 0) {
    isPositive = false;
    anInteger *= -1; // set to positive
  } else {
    isPositive = true;
  }
  str = to_string(anInteger); // return a string eg: "3"
  this->str = reverse(this->str);
}

// use the default copy constructor
// LargeNum::LargeNum(const LargeNum &other) {
//   isPositive = other.isPositive;
//   str = other.str;
// }

// helper function to reverse string
string LargeNum::reverse(const string &str) {
  string newStr;
  for (int i = 0; i < str.size(); i++) {
    newStr = str[i] + newStr;
  }
  return newStr;
}
void LargeNum::mainAddition(string &result, int &left, int &right, bool &carry,
                            const LargeNum &rhs) const {
  while (left < str.size() && right < rhs.str.size()) {
    int digit1 = str[left] - '0';
    int digit2 = rhs.str[right] - '0';
    int digit = digit1 + digit2;
    if (carry) {
      digit += 1;
      carry = false;
    }
    if (digit > 9) {
      carry = true;
      digit -= 10;
    }
    result += to_string(digit); // int -> str
    left++;
    right++;
  }
  // process remainder and carry
  while (left < str.size()) {
    int digit1 = str[left] - '0';
    if (carry) {
      digit1 += 1;
      carry = false;
    }
    // to reset carry
    if (digit1 > 9) {
      carry = true;
      digit1 -= 10;
    }
    result += to_string(digit1); // int -> str
    left++;
  }
}
// use the default copy assignment operator
// LargeNum &LargeNum::operator=(const LargeNum &other) {
//   str = other.str;
//   isPositive = other.isPositive;
//   return *this;
// }

// returns true if the number is zero
bool LargeNum::isZero() const { return (str == "0"); }

// negate the number, positive becomes negative, negative becomes positive
// Zero is always positive
LargeNum &LargeNum::negate() {
  isPositive = !isPositive; // flip sign
  return *this;
}

// add two numbers
// (are they int?)67890987656
// are they always positive?
LargeNum LargeNum::operator+(const LargeNum &rhs) const {
  LargeNum num;
  if (isPositive && !rhs.isPositive) {
    num = *this - rhs;
  } else if (!isPositive && rhs.isPositive) {
    num = rhs - *this;
  } else {
    string result;
    // 2 index location
    int index1 = 0;
    int index2 = 0;
    bool carry = false;
    mainAddition(result, index1, index2, carry, rhs);

    while (index2 < rhs.str.size()) {
      int digit2 = rhs.str[index2] - '0';
      if (carry) {
        digit2 += 1;
        carry = false;
      }
      // to reset carry
      if (digit2 > 9) {
        carry = true;
        digit2 -= 10;
      }
      result += to_string(digit2); // int -> str
      index2++;
    }
    if (carry) {
      result += to_string(1);
    }
    LargeNum largeNum; // create a new largeNum
    largeNum.str = result;
    if (!isPositive && !rhs.isPositive) {
      largeNum.isPositive = false;
    }
    return largeNum;
  }
  return num;
}

// subtract two numbers
LargeNum LargeNum::operator-(const LargeNum &rhs) const {
  LargeNum num;
  if (isPositive && !rhs.isPositive) { // positive - negative-> addition
    LargeNum newRhs(rhs);
    newRhs.isPositive = true;
    num = *this + newRhs;
  } else if (!isPositive && rhs.isPositive) { // add 2 nega; if left -, right +,
    LargeNum newRhs(rhs);
    newRhs.isPositive = false; // flip sign
    num = *this + newRhs;      // add 2 neg gives negative sign
  } else {
    LargeNum leftNum(*this);
    LargeNum rightNum(rhs);
    // if left -, right -, flip-> L - R
    bool resultPositive = true; // assuem left > right (13 - 7) = 6 is Pos
    if (leftNum < rightNum) {   // assume left < right, result is negative
      resultPositive = false;
      // swapping; now left > right
      leftNum = rightNum;
      rightNum = *this;
    }

    // leftNum = pos; rightNum = pos; otherwise addition method will be called
    string result;
    // 2 index location
    int index1 = 0;
    int index2 = 0;
    bool borrow = false;
    while (index1 < leftNum.str.size() && index2 < rightNum.str.size()) {
      int digit1 = leftNum.str[index1] - '0'; // ASCII -> num; eg:"1" - "0" = 1
      int digit2 = rightNum.str[index2] - '0';
      // check if we borrow from digit on the left; eg: 13 - 7
      // 13 has 1 more digit than 7
      // digit1: 13; digit2: 7; able to borrow from 13, but not the other way
      // around
      if (borrow) {
        digit1--;
        borrow = false; // turns off borrow, subtract from digit1

        if (digit1 == -1) { // 103 - 7 = 96
          borrow = true;
          digit1 = 9;
        }
      }
      if (digit1 < digit2) {
        digit1 += 10;
        borrow = true;
      }
      int digit = digit1 - digit2;

      result += to_string(digit); // int -> str
      index1++; // goes from right character to left character in the string
      index2++; // goes from right character to left character in the string
    }

    // process remainder and carry
    // eg 103 - 7 -> 2 digits left: process the next string character in the
    // longer string
    while (index1 < leftNum.str.size()) {
      int digit1 = leftNum.str[index1] - '0';
      if (borrow) {
        digit1--;
        borrow = false;
      }
      // to reset carry
      if (digit1 < 9) {
        borrow = true;
        digit1 += 10;
      }
      result += to_string(digit1); // int -> str
      index1++;
    }

    LargeNum largeNum;
    largeNum.str = result;
    if (!resultPositive) {
      largeNum.isPositive = false;
    }
    return largeNum;
  }
  return num;
}

// multiply two numbers
LargeNum LargeNum::operator*(const LargeNum &rhs) const {
  LargeNum largeNum(rhs);
  LargeNum thisNum(*this);
  LargeNum result(*this);
  result.isPositive = true;
  thisNum.isPositive = true;
  largeNum.isPositive = true;
  thisNum--;
  // case: pass in zero
  if (rhs.str == "0") {
    result.str = "0";
    result.isPositive = true;
    return result;
  }
  // case: pass in negative
  while (largeNum.str != "0") {
    if (largeNum.isPositive) { // substract from it
      largeNum--;
    } else {
      largeNum++;
    }
    result = result + thisNum;
  }
  if (isPositive != rhs.isPositive) {
    result.isPositive = false;
  }
  return result;
}

// divide two numbers. rhs is the divisor
// similar to integer division, ignore remainder
// need to work more
LargeNum LargeNum::operator/(const LargeNum &rhs) const { // 12/4 =3
  LargeNum largeNum(rhs);
  LargeNum thisNum(*this);
  LargeNum result("0");
  result.isPositive = true;
  thisNum.isPositive = true;
  largeNum.isPositive = true;
  thisNum--;
  // case: pass in zero
  if (rhs.str == "0") {
    result.str = "0";
    result.isPositive = true;
    return result;
  }
  // case: pass in negative
  while (thisNum > largeNum) {
    if (largeNum.isPositive) { // substract from it
      largeNum--;
    } else {
      largeNum++;
    }
    result++; //
  }
  if (isPositive != rhs.isPositive) {
    result.isPositive = false;
  }

  return result;
}

// return true if the numbers are equal
bool LargeNum::operator==(const LargeNum &rhs) const {
  return isPositive == rhs.isPositive && str == rhs.str;
}

// return true if the numbers are not equal
bool LargeNum::operator!=(const LargeNum &rhs) const {
  return !(*this == rhs); // not equal , then return true
}

// return true if the left-hand-side number is less than the
// right-hand-side number
bool LargeNum::operator<(const LargeNum &rhs) const {
  bool ret = false;
  if (!isPositive && rhs.isPositive) {
    ret = true;
  } else if (isPositive && !rhs.isPositive) {
    ret = false;
  } else if (str == rhs.str) { // same value
    ret = false;
  } else if (str.size() > rhs.str.size()) {
    if (!isPositive) { // compare 2 negatives
      ret = true;
    } else {
      ret = false; // diff str length
    }
  }
  // same str length, diff value
  else if (str < rhs.str) {
    if (isPositive) {
      ret = true;
    } else {
      ret = false;
    }
  } else {
    if (isPositive) {
      ret = false;
    } else {
      ret = true;
    }
  }
  return ret;
}

// return true if the left-hand-side number is greater than the
// right-hand-side number
bool LargeNum::operator>(const LargeNum &rhs) const {
  bool ret = false;
  if (!isPositive && rhs.isPositive) {
    ret = false;
  } else if (isPositive && !rhs.isPositive) {
    ret = true;
  } else if (str == rhs.str) { // same value
    ret = true;
  } else if (str.size() > rhs.str.size()) {
    if (!isPositive) { // compare 2 negatives
      ret = false;
    } else {
      ret = true; // diff str length
    }
  }
  // same str length, diff value
  else if (str < rhs.str) {
    if (isPositive) {
      ret = false;
    } else {
      ret = true;
    }
  } else {
    if (isPositive) {
      ret = true;
    } else {
      ret = false;
    }
  }
  return ret;
}

// return true if the left-hand-side number is less than or equal to the
// right-hand-side number
bool LargeNum::operator<=(const LargeNum &rhs) const {
  return (*this == rhs || *this < rhs);
}

// return true if the left-hand-side number is greater than or equal to the
// right-hand-side number
bool LargeNum::operator>=(const LargeNum &rhs) const {
  return (*this == rhs || *this > rhs);
}

// prefix increment
LargeNum &LargeNum::operator++() {
  LargeNum one(1);
  *this = *this + one;
  return *this;
}

// postfix increment
// make copy, increment
LargeNum LargeNum::operator++(int) {
  LargeNum mycopy(*this);
  ++(*this);
  return mycopy;
}

// prefix decrement
LargeNum &LargeNum::operator--() {
  LargeNum one(1);
  *this = *this - one;
  return *this;
}

// postfix decrement
LargeNum LargeNum::operator--(int) {
  LargeNum mycopy(*this);
  --(*this);
  return mycopy;
}