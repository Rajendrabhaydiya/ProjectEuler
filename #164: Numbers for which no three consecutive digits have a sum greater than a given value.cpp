#include <iostream>

// Hackerrank: up to 100 digits
// Project Euler: 20 digits
const unsigned int MaxDigits = 100;

// bonus feature: change maximum sum of three consecutive digits
unsigned int maxSum = 9;

// count matching numbers
// prevprev: the digit two positions to the left of the current digit
// prev    : the digit one position  to the left of the current digit
// digits  : number of remainings digits
// isFirst : true only for the first digit (which must not be zero)
unsigned long long search(unsigned int prevprev, unsigned int prev, unsigned int digits, bool isFirst) {
  // done ?
  if (digits == 0)
    return 1;

  // memoize
  unsigned int id = digits * 100 + prevprev * 10 + prev; // simple hash
  static unsigned long long cache[(MaxDigits + 1) * 100] = {
    0
  };
  if (cache[id] != 0)
    return cache[id];

  // iterate over all digits such that current + prev + prevprev <= 9
  unsigned long long result = 0;
  for (unsigned int current = 0; current + prev + prevprev <= maxSum; current++) {
    // no leading zero
    if (current == 0 && isFirst)
      continue;

    // add next digit
    result += search(prev, current, digits - 1, false);
  }

  #ifndef ORIGINAL
  // Hackerrank only
  result %= 1000000007;
  #endif

  // memoize
  cache[id] = result;
  return result;
}

int main() {
  unsigned int digits = 20;
  std::cin >> digits;
  if (digits > MaxDigits)
    return 1;

  std::cout << search(0, 0, digits, true) << std::endl;

  return 0;
}
