#include<bits/stdc++.h>
using namespace std;

// Source: modified version of maximum sum sub-rectangle from Competitive Programming 1 (by Steven Halim)
// Complexity: O(n^6) (total loops = n^6 + n^3)
// This code is for a parallelepiped / rectangular prism / cube / 3D rectangle where a, b & c are dimensions
// Make slight changes for minimum result

int main()
{
    int a, b, c;
    scanf("%d%d%d", &a, &b, &c);
    long long int arr[a][b][c];
    for (int i = 0; i < a; i++) {
        for (int j = 0; j < b; j++) {
            for (int k = 0; k < c; k++) {
                scanf("%lld", &arr[i][j][k]);
                if (i) arr[i][j][k] += arr[i-1][j][k];
                if (j) arr[i][j][k] += arr[i][j-1][k];
                if (k) arr[i][j][k] += arr[i][j][k-1];
                if (i && j) arr[i][j][k] -= arr[i-1][j-1][k];
                if (i && k) arr[i][j][k] -= arr[i-1][j][k-1];
                if (j && k) arr[i][j][k] -= arr[i][j-1][k-1];
                if (i && j && k) arr[i][j][k] += arr[i-1][j-1][k-1];
            }
        }
    }
    long long int maxSubRect = LONG_LONG_MIN;
    for (int i = 0; i < a; i++) {
        for (int j = 0; j < b; j++) {
            for (int k = 0; k < c; k++) {
                for (int l = i; l < a; l++) {
                    for (int m = j; m < b; m++) {
                        for (int n = k; n < c; n++) {
                            long long int subRect = arr[l][m][n];
                            if (i) subRect -= arr[i-1][m][n];
                            if (j) subRect -= arr[l][j-1][n];
                            if (k) subRect -= arr[l][m][k-1];
                            if (i && j) subRect += arr[i-1][j-1][n];
                            if (i && k) subRect += arr[i-1][m][k-1];
                            if (j && k) subRect += arr[l][j-1][k-1];
                            if (i && j && k) subRect -= arr[i-1][j-1][k-1];
                            maxSubRect = max(maxSubRect, subRect);
                        }
                    }
                }
            }
        }
    }
    printf("%lld\n", maxSubRect);

    return 0;
}
