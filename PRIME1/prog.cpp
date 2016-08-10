
#include <iostream>
#include <vector>

// For debugging.
#define DEBUG if (true) printf

// Integer fast exponentiation
unsigned long long pow(
  unsigned long long base,
  unsigned long long exp,
  unsigned long long mod = LLONG_MAX / 2
) {
  if (exp <= 0) {
    return 1;
  } else if (exp == 1) {
    return base % mod;
  } else if (exp % 2 == 1) {
    unsigned long long tmp = pow(base, (exp - 1) / 2, mod);
    return (tmp * tmp * base) % mod;
  } else {
    unsigned long long tmp = pow(base, exp / 2, mod);
    return (tmp * tmp) % mod;
  }
}

bool isPrime_MillerTest(unsigned long long n) {
  if (n <= 1) {
    return false;
  } else if (n == 2 || n == 3 || n == 5) {
    // Handle 3 and 5 since we subtract up to 3 from n
    return true;
  } else if (n % 2 == 0) {
    return false;
  }

  // Notice: n is an odd integer > 1.
  // Find d and s such that: n - 1 = pow(2, s) * d.
  // Notice: n - 1 is even, s > 1, d is odd.

  unsigned long long d = n - 1;
  unsigned long long s = 0;
  while (d % 2 == 0) {
    d /= 2;
    s += 1;
  }

  // These are lists of witnesses that can verify n's primality.
  // If any witness claims n is composite, it's composite, otherwise it's prime.
  // This list can verify any n < 18446744073709551616 = (2^64)
  // If that is not performant enough, consider: {2, 7, 61} for n < 4759123141
  unsigned long long witnesses [] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
  // unsigned long long witnesses [] = {5};

  for (const unsigned long long a : witnesses) {
    // Witnesses must be less than n.
    if (a >= n) {
      continue;
    }

    DEBUG("testing\nn: %llu\nn - 1: %llu\na: %llu\ns: %llu\nd: %llu\n", n, n - 1, a, s, d);

    unsigned long long ad = pow(a, d, n);
    DEBUG("a^d: %llu\na^d (mod n): %llu\n", ad, ad % n);

    bool composite = true;

    // This witness cannot claim n is composite
    if (pow(a, d, n) % n == 1) {
      DEBUG("%llu thinks %llu may be prime, a^d\n", a, n);
      composite = false;
    }

    for (unsigned long long r = 0; r < s; r++) {
      DEBUG("r: %llu\n2^r*d: %llu\n", r, pow(2, r) * d);
      unsigned long long a2rd = pow(a, pow(2, r) * d, n);
      DEBUG("a^(2^r*d): %llu\na^(2^r*d) (mod n): %llu\n", a2rd, a2rd % n);
      // This witness cannot claim n is composite
      if (a2rd % n == n -1) {
        DEBUG("%llu thinks %llu may be prime, a^(2^%llu*d)\n", a, n, r);
        composite = false;
        break;
      }
    }

    // Witness a has verified n is composite, return false.
    if (composite) {
      DEBUG("returning false\n");
      return false;
    }
  }

  // No witnesses have verified n as composite, so n is prime.
  DEBUG("%llu is prime\n", n);
  return true;
}

int main() {
  long i, j;
  long t, a, b;
  std::cin >> t;
  for (i = 0; i < t; i++) {
    std::cin >> a >> b;
    for (j = a; j <= b; j++) {
      if (isPrime_MillerTest(j)) {
        printf("%ld\n", j);
      }
    }
    printf("\n");
  }
}
