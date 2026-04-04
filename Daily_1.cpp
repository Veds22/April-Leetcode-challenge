# include <bits/stdc++.h>
using namespace std;

class Solution {
    bool isValid(int n, int m, int i, int j){
        return i < m && j < n && i >= 0 && j >= 0;
    }
public:
    int calculateMinimumHP(vector<vector<int>>& dungeon) {
        int m = dungeon.size();
        int n = dungeon[0].size();
        if(m == 1 && n == 1 && dungeon[0][0] >= 0) return 1;
        vector<vector<int>> dp(m, vector<int>(n, INT_MAX));
        // dp[i][j] = HP reqd to reach last cell from (i, j) safely (w/o being <= 0)
        dp[m - 1][n - 1] = max(1, 1 - dungeon[m - 1][n- 1]);

        for(int i = m-2; i >= 0; i--)
            dp[i][n-1] = max(1, dp[i+1][n-1] - dungeon[i][n-1]);

        for(int j = n-2; j >= 0; j--)
            dp[m-1][j] = max(1, dp[m-1][j+1] - dungeon[m-1][j]);

        for(int i = m - 2; i >= 0; i--){
            for(int j = n - 2; j >= 0; j--){
                int next = min(dp[i + 1][j], dp[i][j + 1]);
                dp[i][j] = max(1, next - dungeon[i][j]);
            }
        } 
        return dp[0][0];
    }
};

int main(){
    return 0;
}