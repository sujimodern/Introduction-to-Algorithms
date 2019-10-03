#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

enum {n = 16};

typedef struct subarray subarray;
struct subarray {
  int low;
  int high;
  int sum; 
};

void find_max_subarray_brute_force(size_t n, int A[n], subarray* sa) {
  int low, high, sum, temp;
  sum = INT_MIN;
  for (size_t left = 0; left < n; left += 1) {
    temp = 0;
    for (size_t right = left; right < n; right += 1) {
      temp += A[right];
      if (temp > sum) {
        sum = temp; 
        low = left;
        high = right;
      }
    }
  }
  *sa = (subarray){.low = low, .high = high, .sum = sum};
}

int main(int argc, char* argv[argc+1]) {
  int A[n] = {13, -3, -25, 20, -3, -16, -23, 18,
              20, -7, 12, -5, -22, 15, -4, 7};

  subarray sa = {0};
  find_max_subarray_brute_force(n, A, &sa);
  printf("left = %d, right = %d, sum = %d\n", sa.low, sa.high, sa.sum);
  
  return EXIT_SUCCESS;
}
