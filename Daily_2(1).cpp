/*
LEELTCODE: 3418. Maximum Amount of Money Robot Can Earn

You are given an m x n grid. A robot starts at the top-left corner of the grid (0, 0) and wants to reach the bottom-right corner (m - 1, n - 1). The robot can move either right or down at any point in time.

The grid contains a value coins[i][j] in each cell:

If coins[i][j] >= 0, the robot gains that many coins.
If coins[i][j] < 0, the robot encounters a robber, and the robber steals the absolute value of coins[i][j] coins.
The robot has a special ability to neutralize robbers in at most 2 cells on its path, preventing them from stealing coins in those cells.

Note: The robot's total coins can be negative.

Return the maximum profit the robot can gain on the route.
*/
int maximumAmount(vector<vector<int>>& coins) {
    int m = coins.size(), n = coins[0].size();
    
    // dp[i][j][k]
    vector<vector<vector<int>>> dp(m, vector<vector<int>>(n, vector<int>(3, INT_MIN)));
    
    // Base case (0,0)
    for(int k = 0; k < 3; k++) {
        if(coins[0][0] >= 0)
            dp[0][0][k] = coins[0][0];
        else {
            if(k > 0) dp[0][0][k] = 0;  // neutralize
            else dp[0][0][k] = coins[0][0];
        }
    }
    
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {
            if(i == 0 && j == 0) continue;
            
            for(int k = 0; k < 3; k++) {
                
                int best = INT_MIN;
                
                // from top
                if(i > 0 && dp[i-1][j][k] != INT_MIN) {
                    best = max(best, dp[i-1][j][k]);
                }
                
                // from left
                if(j > 0 && dp[i][j-1][k] != INT_MIN) {
                    best = max(best, dp[i][j-1][k]);
                }
                
                if(best == INT_MIN) continue;
                
                // Case 1: no neutralization
                dp[i][j][k] = max(dp[i][j][k], best + coins[i][j]);
                
                // Case 2: neutralize (if robber)
                if(coins[i][j] < 0 && k > 0) {
                    int prev_best = INT_MIN;
                    
                    if(i > 0 && dp[i-1][j][k-1] != INT_MIN)
                        prev_best = max(prev_best, dp[i-1][j][k-1]);
                    
                    if(j > 0 && dp[i][j-1][k-1] != INT_MIN)
                        prev_best = max(prev_best, dp[i][j-1][k-1]);
                    
                    if(prev_best != INT_MIN) {
                        dp[i][j][k] = max(dp[i][j][k], prev_best);
                    }
                }
            }
        }
    }
    
    return max({dp[m-1][n-1][0], dp[m-1][n-1][1], dp[m-1][n-1][2]});
}