#include <iostream>
#include <vector>

// compute sum(coeff[i] * x^i)
template <typename T>
T sequence(T x, const std::vector<T>& coefficients)
{
  T xx = 1;
  T result = 0;
  for (auto i : coefficients)
  {
    result += i * xx;
    xx *= x;
  }
  return result;
}

// given f(1),f(2),f(3),...f(n) then find f(n+1)
// (Lagrange polynomials)
template <typename T>
T lagrange(const std::vector<T>& known)
{
  T result = 0;

  size_t next = known.size() + 1;
  for (size_t i = 1; i < next; i++)
  {
    // build Lagrange polynomials

    // n = numerator, d = denominator
    T n = 1;
    T d = 1;
    for (size_t j = 1; j < next; j++)
    {
      if (i == j)
        continue;

      n *= next - j;
      d *= i - j;
    }

    // evaluate
    result += known[i - 1] * (n / d);
  }
  return result;
}

// given f(1),f(2),f(3),...f(n) then find f(n+1)
// (Newton divided differences)
template <typename T>
T newton(std::vector<T> known)
{
  T result = known[0];

  size_t j = 1;
  size_t k = known.size();
  for (size_t last = known.size() - 1; last > 0; last--)
  {
    for (size_t i = 0; i < last; i++)
      known[i] = (known[i + 1] - known[i]) / j;

    T multDiff = 1;
    for (size_t i = 0; i < j; i++)
      multDiff *= k - i;

    result += known[0] * multDiff;
    j++;
  }

  return result;
}

int main()
{
  // read coefficients
#ifdef ORIGINAL
  std::vector<long long> coefficients = { +1, -1, +1, -1, +1, -1, +1, -1, +1, -1, +1 };
#else
  size_t numCoefficients;
  std::cin >> numCoefficients;
  std::vector<long long> coefficients(numCoefficients + 1);
  for (auto& i : coefficients)
    std::cin >> i;
#endif

  long long sum = 0;
  std::vector<long long> data;
  // iterate over 10 points
  for (long long x = 1; x < (long long)coefficients.size(); x++)
  {
    // add the next point
    data.push_back(sequence(x, coefficients));

    // estimate next point
    long long next = lagrange(data);
    //long long next = newton(data);
    sum += next;

#ifndef ORIGINAL
    std::cout << (next % 1000000007) << " ";
#endif
  }
#ifdef ORIGINAL
  std::cout << sum << std::endl;
#endif

  return 0;
}
