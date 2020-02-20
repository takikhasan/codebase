#include<bits/stdc++.h>
using namespace std;

// Source: Competitive Programming 1 (by Steven Halim)
// Complexity: O(n^4) (total loops = n^4 + n^2)
// This code is for a square rectangle where n is the length of each side
// Make slight changes for a rectangle of any shape and / or minimum sub-rectangle

int main()
{
    int n;
    scanf("%d", &n);
    int arr[n][n];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &arr[i][j]);
            if (i) arr[i][j] += arr[i-1][j];
            if (j) arr[i][j] += arr[i][j-1];
            if (i && j) arr[i][j] -= arr[i-1][j-1];
        }
    }
    int maxSubRect = -127 * 100 * 100;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = i; k < n; k++) {
                for (int l = j; l < n; l++) {
                    int subRect = arr[k][l];
                    if (i) subRect -= arr[i-1][l];
                    if (j) subRect -= arr[k][j-1];
                    if (i && j) subRect += arr[i-1][j-1];
                    maxSubRect = max(maxSubRect, subRect);
                }
            }
        }
    }
    printf("%d\n", maxSubRect);

    return 0;
}
