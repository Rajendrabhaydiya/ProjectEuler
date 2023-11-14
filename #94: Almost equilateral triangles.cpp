#include <cmath>
#include <vector>
#include <iostream>

// valid perimeters
std::vector<unsigned long long> solutions;

// return true if area is integral
bool isValidTriangle(unsigned long long oneSide, unsigned long long twoSides)
{
  unsigned long long check = 4 * twoSides * twoSides - oneSide * oneSide;
  unsigned long long root  = sqrt(check);
  return root * root == check;
}

// brute-force approach
unsigned long long findMore(unsigned long long perimeter, unsigned long long limit)
{
  // check all perimeters
  while (perimeter <= limit + 3)
  {
    // length of the two equal sides
    auto twoSides = perimeter / 3;

    // assume single side is one unit smaller than the other two sides
    auto oneSide = twoSides - 1;
    if (isValidTriangle(oneSide, twoSides))
      solutions.push_back(perimeter - 1);

    // assume single side is one unit bigger than the other two sides
    oneSide = twoSides + 1;
    if (isValidTriangle(oneSide, twoSides))
      solutions.push_back(perimeter + 1);

    // next group of triangles
    perimeter += 3;
  }

  return perimeter;
}

// just compute sequence
unsigned long long sequence(unsigned long long limit)
{
  // initial values of the equal sides
  unsigned long long plusOne [] = { 1,  5 };
  unsigned long long minusOne[] = { 1, 17 };

  solutions.clear();
  // smallest solutions where:
  solutions.push_back(3 * plusOne [1] + 1); // single side is 1 unit longer  than the equal sides
  solutions.push_back(3 * minusOne[1] - 1); // single side is 1 unit shorter than the equal sides


  while (solutions.back() <= limit + 3)
  {
    // compute next length of equal sides
    unsigned long long nextPlusOne  = 14 * plusOne [1] - plusOne [0] - 4;
    unsigned long long nextMinusOne = 14 * minusOne[1] - minusOne[0] + 4;

    // store it, shift off oldest values
    plusOne [0] = plusOne [1];
    plusOne [1] = nextPlusOne;
    minusOne[0] = minusOne[1];
    minusOne[1] = nextMinusOne;

    // we are interested in the perimeter
    solutions.push_back(3 * nextPlusOne  + 1);
    solutions.push_back(3 * nextMinusOne - 1);
  }

  // largest perimeter found
  return solutions.back();
}


int main()
{
  solutions.push_back(16); // perimeter of smallest triangle
  unsigned long long perimeter = 18; // check 18-1 and 18+1 in next step

  unsigned int tests = 1;
  std::cin >> tests;
  while (tests--)
  {
    unsigned long long limit = 1000000000;
    std::cin >> limit;

    // check all perimeters
    while (perimeter <= limit + 3)
      //perimeter = findMore(perimeter, limit);
      perimeter = sequence(limit);

    // sum of all relevant triangles
    unsigned long long sum = 0;
    for (auto x : solutions)
      if (x <= limit)
        sum += x;

    std::cout << sum << std::endl;
  }

  return 0;
}
