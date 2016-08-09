
#include <iostream>
#include <vector>

int main() {
  long long i, j;

  // Sieve of Eratosthenes
  std::vector<bool> sieve (1000000001, true);

  // Hardcode 0, 1, and even numbers to false.
  sieve[0] = false;
  sieve[1] = false;
  for (i = 4; i < sieve.size(); i += 2)  {
    sieve[i] = false;
  }

  // Filter out all other non-primes.
  for (i = 3; i * i < sieve.size(); i += 2) {
    if (sieve[i]) {
      for (j = i * 2; j < sieve.size(); j += i) {
        sieve[j] = false;
      }
    }
  }

  // Now check each test case.
  long long t, a, b;
  std::cin >> t;
  for (i = 0; i < t; i++) {
    std::cin >> a >> b;
    for (j = a; j <= b; j++) {
      if (sieve[j]) {
        printf("%lld\n", j);
      }
    }
    printf("\n");
  }
}
