#include<bits/stdc++.h>

using namespace std;

int main() {
  long n;
  cin >> n;
  long long tiles = n / 4;
  long long k = int(sqrt(tiles));
  long long sum = 0;
  for (int i = 1; i <= k; i++) {
    sum = sum + (tiles / i - i);

  }
  cout << sum;
  return 0;
}
