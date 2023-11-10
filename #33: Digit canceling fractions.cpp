#include <iostream>
#include <string>
#include <algorithm>
#include <unordered_set>

// convert number to string
std::string num2str(unsigned int x, unsigned int digits)
{
  std::string result;
  // it's faster to generate the digits in reverse order ...
  while (digits-- > 0)
  {
    auto digit = x % 10;
    result += char(digit + '0');
    x /= 10;
  }
  // ... and then reverse them into their original order
  std::reverse(result.begin(), result.end());
  return result;
}

// ... and back
unsigned int str2num(const std::string& str)
{
  unsigned int result = 0;
  for (auto s : str)
  {
    result *= 10;
    result += s - '0';
  }
  return result;
}

// fill all gaps in mask (marked as '.') with the digits found in str and return result as a number
unsigned int merge(const std::string& strFill, const std::string& mask)
{
  auto iteFill = strFill.begin();
  unsigned int result = 0;
  for (auto m : mask)
  {
    result *= 10;
    // if placeholder '.' is found, then take next digit from strFill
    if (m == '.')
      result += *iteFill++ - '0';
    else // else take the digit of the mask
      result += m - '0';
  }
  return result;
}

int main()
{
//#define ORIGINAL
#ifdef ORIGINAL
  // brute-force solution for the original problem
  unsigned int multD = 1;
  unsigned int multN = 1;
  for (unsigned int d = 10; d <= 99; d++) // denominator
    for (unsigned int n = 10; n < d; n++) // numerator
      for (unsigned int cancel = 1; cancel <= 9; cancel++)
      {
        auto lowN  = n % 10;
        auto lowD  = d % 10;
        auto highN = n / 10;
        auto highD = d / 10;
        // we could check all combinations:
        // 1. cancel low  digit of denominator and low  digit of numerator
        // 2. cancel high digit of denominator and low  digit of numerator
        // 3. cancel low  digit of denominator and high digit of numerator
        // 4. cancel high digit of denominator and low  digit of numerator
        // but actually only case 2 is relevant
        // (you can prove that but in this problem I focus on the much harder Hackerrank version)
        // two fractions a/b and c/d are equal if a*d=b*c
        if (highD == cancel && lowN == cancel && lowD * n == highN * d)
        {
          multN *= n;
          multD *= d;
        }
      }

  // shorter code than applying the "least common multiple"
  for (unsigned int i = 2; i <= multN; i++)
    // remove all common prime factors
    while (multN % i == 0 && multD % i == 0)
    {
      multN /= i;
      multD /= i;
    }
  std::cout << multD << std::endl;

  return 0;
#endif

  // and now a completely different approach for the Hackerrank version of the problem
  unsigned int digits;
  unsigned int cancel;
  std::cin >> digits >> cancel;
  auto keep = digits - cancel;

  const unsigned int Tens[] = { 1, 10, 100, 1000, 10000 };
  unsigned int sumN  = 0;
  unsigned int sumD  = 0;

  // don't count fractions twice
  std::unordered_set<unsigned int> used;

  // I do the inverse:
  // instead of removing digits, I add digits
  // "d" and "n" stand for denominator and numerator
  // they are small numbers where I insert digits
  // let's iterate over all "reduced" number and then iterate over all digits we could insert
  // note: initially n and d started at Tens[keep - 1] instead of 1 but I learnt the hard way
  //       that Hackerrank thinks 3016/6032 = 01/02 is a valid reduction
  for (unsigned int d = 1; d < Tens[keep]; d++)
    for (unsigned int n = 1; n < d; n++)
    {
      // convert to string
      auto strN = num2str(n, keep);
      auto strD = num2str(d, keep);

      // try to insert all combinations
      for (auto insert = Tens[cancel - 1]; insert < Tens[cancel]; insert++)
      {
        // convert to string
        auto strInsert = num2str(insert, cancel);

        // if number's digits are (partially) descending, then we already saw all its permutations
        bool isAscending = true;
        for (size_t i = 1; i < strInsert.size(); i++)
          if (strInsert[i - 1] > strInsert[i])
          {
            isAscending = false;
            break;
          }
        if (!isAscending)
          continue;

        // prepend placeholders (must be alphabetically smaller than '0')
        strInsert.insert(0, keep, '.');

        // check all permutations
        // strInsertN is permutated until we arrive at the original value again
        auto strInsertN = strInsert;
        do
        {
          auto newN = merge(strN, strInsertN);

          // the leading digit of the not-cancelled fraction must not be zero
          // strangely enough, the leading digit of the cancelled fraction can be zero
          if (newN < Tens[digits - 1])
          continue;

          // strInsertD is permutated until we arrive at the original value again
          auto strInsertD = strInsert;
          do
          {
            auto newD = merge(strD, strInsertD);

            // in case we find the same fraction multiple times
            // two fractions a/b and c/d are equal if a*d=b*c
            if (newN * d == newD * n)
            {
              // ensure we haven't seen that fraction yet
              auto id = newN * 10000 + newD;
              if (used.count(id) == 0)
              {
                sumN  += newN;
                sumD  += newD;

                used.insert(id);
              }
            }
          }
          while (std::next_permutation(strInsertD.begin(), strInsertD.end()));
        }
        while (std::next_permutation(strInsertN.begin(), strInsertN.end()));
      }
    }

  std::cout << sumN << " " << sumD << std::endl;
  return 0;
}
