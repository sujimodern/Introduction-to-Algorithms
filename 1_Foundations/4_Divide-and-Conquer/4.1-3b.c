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

void find_max_crossing_subarray(size_t n, int A[n], int low, int mid,
                                int high, subarray* csa) {
  int max_left, max_right, left_sum, right_sum, sum;
  left_sum = INT_MIN;
  sum = 0;
  for (int i = mid; i >= low; i -= 1) {
    sum += A[i];
    if (sum > left_sum) {
      left_sum = sum;
      max_left = i;
    }
  }
  right_sum = INT_MIN;
  sum = 0;
  for (int j = mid+1; j <= high; j += 1) {
    sum += A[j];
    if (sum > right_sum) {
      right_sum = sum;
      max_right = j;
    }
  }
  *csa = (subarray){.low = max_left, .high = max_right,
                          .sum = left_sum + right_sum};
}

void find_max_subarray(size_t n, int A[n], int low, int high,
                       subarray* sa) {
  int mid;
  subarray lsa, rsa, csa;
  if (high == low) {
    *sa = (subarray){.low = low, .high = high, .sum = A[low]};
  } else {
    mid = (low + high) / 2;
    find_max_subarray(n, A, low, mid, &lsa);
    find_max_subarray(n, A, mid+1, high, &rsa);
    find_max_crossing_subarray(n, A, low, mid, high, &csa);
    if (lsa.sum >= rsa.sum && lsa.sum >= csa.sum) {
      *sa = (subarray){.low = lsa.low, .high = lsa.high,
                       .sum = lsa.sum};
    } else if (rsa.sum >= lsa.sum && rsa.sum >= csa.sum) {
      *sa = (subarray){.low = rsa.low, .high = rsa.high,
                       .sum = rsa.sum};
    } else {
      *sa = (subarray){.low = csa.low, .high = csa.high,
                       .sum = csa.sum};
    }
  }
}

int main(int argc, char* argv[argc+1]) {
  int A[n] = {13, -3, -25, 20, -3, -16, -23, 18,
              20, -7, 12, -5, -22, 15, -4, 7};

  subarray sa = {0};
  find_max_subarray(n, A, 0, n-1, &sa);
  printf("left = %d, right = %d, sum = %d\n", sa.low, sa.high, sa.sum);
  
  return EXIT_SUCCESS;
}
