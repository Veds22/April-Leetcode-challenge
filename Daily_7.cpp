/*
    LEETCODE: 3740 - Minimum Distance Between Three Equal Elements I
    You are given an integer array nums.

A tuple (i, j, k) of 3 distinct indices is good if nums[i] == nums[j] == nums[k].

The distance of a good tuple is abs(i - j) + abs(j - k) + abs(k - i), where abs(x) denotes the absolute value of x.

Return an integer denoting the minimum possible distance of a good tuple. If no good tuples exist, return -1.
*/

#include <bit/stdc++.h>
using namespace std;

class Solution {
public:
    int minimumDistance(vector<int>& nums) {
        int n = nums.size();
        unordered_map<int, vector<int>> groupByVal;
        for(int i = 0; i < n; i++) groupByVal[nums[i]].push_back(i);
        int ans = 1e9 + 7;
        for(int i = 0; i <= n; i++){
            int t = groupByVal[i].size();
            if(t >= 3){
                // if indices a < b < c
                // => abs(b - a) + abs(c - b) + abs(c - a) = 2 * (c - a)
                for(int j = 0; j < t - 2; j++) ans = min(ans, 2 * (groupByVal[i][j + 2] - groupByVal[i][j]));
            }
        }
        if(ans == 1e9 + 7) return -1;
        return ans;
    }
};
