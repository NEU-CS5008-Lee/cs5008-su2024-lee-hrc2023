// Haoyang (Hendrick) Chen
// chen.haoyang4@northeastern.edu

#include <stdio.h>

int d[20];

long long int dp(int n) {
    if (n == 0) return 1;
    if (n == 1) return 0;
    if (n == 2) return 3;

    // Base cases
    d[0] = 1; // There's one way to fill a 3x0 floor (doing nothing)
    d[1] = 0; // There's no way to fill a 3x1 floor with 1x2 and 2x1 tiles
    d[2] = 3; // Three ways to fill a 3x2 floor

    // Fill the dp array using the recurrence relation
    for (int i = 3; i <= n; i++) {
        d[i] = d[i-2] * 3 + d[i-3] * 2;
    }

    return d[n];
}

int main(void) {
    int n;
    scanf("%d", &n);
    printf("%lld\n", dp(n));
}
