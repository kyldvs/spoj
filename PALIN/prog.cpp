
#include <climits>
#include <iostream>
#include <string>
#include <vector>

#define DEBUG if (true) printf

using namespace std;

// Increment string s starting at the position r. Ex:
// increment("1030", 1) gives "1130"
// increment("1030", 2) gives "1040"
// increment("1030", 3) gives "1031"
// increment("9030", 0) gives "10030"
string increment(string s, long long r) {
  for (long long i = r; i >= 0; i--) {
    if (s[i] < '9') {
      s[i] = s[i] + 1;
      break;
    } else {
      s[i] = '0';
    }
  }
  // If it starts with a 0 that means the number was all nines and we didn't
  // increment yet. This is not true if the input number can have leading
  // zeros though.
  if (s[0] == '0') {
    s = "1" + s;
  }
  return s;
}

string nextPalindrome(string s) {
  s = increment(s, s.size() - 1);

  // Already a palindrome, not sure if this base case is actually necessary..
  if (s.size() == 1) {
    return s;
  }

  // First figure out where we have to increment s so that it is easy to make
  // a palindrome. E.g. 111222 cannot be easily made a palindrome, but once we
  // increment as position 2 and get 112222 it is easy to make it into a
  // larger palindrome than the original: 112211

  long long n = s.size();
  long long odd = n & 1; // 1 if size is odd, used to "skip" the center char
  long long st = (n / 2) + odd; // index of the first important char on right
  long long ct = n / 2; // How many positions from st we need to check.
  for (long long i = 0; i < ct; i++) {
    long long l = st - 1 - i - odd;
    long long r = st + i;
    if (s[l] < s[r]) {
      s = increment(s, r - 1);
      break;
    }
  }

  // Size may have changed with the increment, update n.
  n = s.size();

  // Now we can safely make it a palindrome, copying the left side.
  for (long i = 0; i < n / 2; i++) {
    s[n - 1 - i] = s[i];
  }

  return s;
}

int main() {
  long t;
  std::cin >> t;
  for (long i = 0; i < t; i++) {
    string s;
    cin >> s;
    cout << nextPalindrome(s) << "\n";
  }
}
