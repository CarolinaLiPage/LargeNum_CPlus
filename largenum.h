#include <iostream>
#include <string>
#include <vector>

using namespace std;

class LargeNum {
  // output number with a comma after ever 3 digits,
  // e.g. 1234567890 -> 1,234,567,890
  friend ostream &operator<<(ostream &out, const LargeNum &num);

private:
  // Define private data members and methods here
  bool isPositive;
  string str;
  // Other helper methods

public:
  // default constructor from string
  explicit LargeNum(const string &str = "0");

  // constructor from int
  explicit LargeNum(int anInteger);

  // use the default copy constructor
  LargeNum(const LargeNum &other) = default;

  // use the default copy assignment operator
  LargeNum &operator=(const LargeNum &other) = default;

  // use the default destructor
  ~LargeNum() = default;

  // helper function to perform main addition
  void mainAddition(string &result, int &left, int &right, bool &carry,
                    const LargeNum &rhs) const;

  // helper function to reverse string
  static string reverse(const string &str);

  // returns true if the number is zero
  bool isZero() const;

  // negate the number, positive becomes negative, negative becomes positive
  // Zero is always positive
  LargeNum &negate();

  // add two numbers
  LargeNum operator+(const LargeNum &rhs) const;

  // subtract two numbers
  LargeNum operator-(const LargeNum &rhs) const;

  // multiply two numbers
  LargeNum operator*(const LargeNum &rhs) const;

  // divide two numbers. rhs is the divisor
  // similar to integer division, ignore remainder
  LargeNum operator/(const LargeNum &rhs) const;

  // return true if the numbers are equal
  bool operator==(const LargeNum &rhs) const;

  // return true if the numbers are not equal
  bool operator!=(const LargeNum &rhs) const;

  // return true if the left-hand-side number is less than the
  // right-hand-side number
  bool operator<(const LargeNum &rhs) const;

  // return true if the left-hand-side number is greater than the
  // right-hand-side number
  bool operator>(const LargeNum &rhs) const;

  // return true if the left-hand-side number is less than or equal to the
  // right-hand-side number
  bool operator<=(const LargeNum &rhs) const;

  // return true if the left-hand-side number is greater than or equal to the
  // right-hand-side number
  bool operator>=(const LargeNum &rhs) const;

  // prefix increment
  LargeNum &operator++();

  // postfix increment
  LargeNum operator++(int);

  // prefix decrement
  LargeNum &operator--();

  // postfix decrement
  LargeNum operator--(int);
};