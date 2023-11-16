#include <iostream>

// return the unique n-digit number with a predefined last digit
// which after multiplication with a multiplier is a right-rotation of itself
// return only that value modulo some power-of-10
// if there is no such number, then return 0
unsigned int search(unsigned int numDigits, unsigned int multiplier, unsigned int lastDigit, unsigned int modulo)
{
  // will be 10, 100, 1000, 10000, ...
  unsigned int shift = 10;
  // first digit of last iteration
  unsigned int carry =  0;

  // set last digit
  unsigned int current = lastDigit;
  unsigned int result  = lastDigit;

  while (--numDigits)
  {
    // process next digit
    auto next = multiplier * current + carry;
    // "next" has at most two digits, carry over the first digit to next iteration
    carry     = next / 10;
    // and its second digit becomes part of "result"
    current   = next % 10;

    // current digit relevant for result ?
    if (shift < modulo)
    {
      result += current * shift;
      shift  *= 10;
    }
  }

  // left-most digit
  auto first = multiplier * current + carry;
  // failed ? (no leading zero, product's first digit must match last digit of factor)
  if (current == 0 || first != lastDigit)
    return 0;

  return result;
}

int main()
{
  unsigned int maxDigits = 100;
  std::cin >> maxDigits;

  // last five digits
  const unsigned int Modulo = 100000;

  unsigned int result = 0;
  // from 2 to 100 digits
  for (unsigned int numDigits = 2; numDigits <= maxDigits; numDigits++)
    // each multiplier between 1 and 9
    for (unsigned int multiplier = 1; multiplier <= 9; multiplier++)
      // last digit can't be zero, therefore 1 to 9 only
      for (unsigned int lastDigit = 1; lastDigit <= 9; lastDigit++)
        result += search(numDigits, multiplier, lastDigit, Modulo);

  std::cout << result % Modulo << std::endl;
  return 0;
}
