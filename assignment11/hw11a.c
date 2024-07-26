// Haoyang (Hendrick) Chen
// chen.haoyang4@northeastern.edu

#include <stdio.h>

int d[20];

long long int dp(int n) {
    if (n == 0) return 1;
    if (n == 1) return 1;

    // Base cases
    d[0] = 1; // There's one way to fill a 2x0 floor (doing nothing)
    d[1] = 1; // There's one way to fill a 2x1 floor (using two 2x1 tiles)
    
    // Fill the dp array using the recurrence relation
    for (int i = 2; i <= n; i++) {
        d[i] = d[i-1] + d[i-2];
    }
    
    return d[n];
}

int main(void) {
    int n;
    scanf("%d", &n);
    printf("%lld\n", dp(n));
}
