/*
    LEETCODE - 3653: XOR After Range Multiplication Queries I

    You are given an integer array nums of length n and a 2D integer array queries of size q, where queries[i] = [li, ri, ki, vi].

For each query, you must apply the following operations in order:

Set idx = li.
While idx <= ri:
Update: nums[idx] = (nums[idx] * vi) % (109 + 7)
Set idx += ki.
Return the bitwise XOR of all elements in nums after processing all queries.

*/

#include <bit/stdc++.h>
using namespace std;
class Solution {
private:
    int mod = 1e9 + 7;
public:
    int xorAfterQueries(vector<int>& nums, vector<vector<int>>& queries) {
        for(auto &query: queries){
            int l = query[0];
            int r = query[1];
            int k = query[2];
            int v = query[3];
            for(int idx = l; idx <= r; idx += k) nums[idx] = (1LL * nums[idx] * v) % mod;
        }
        int ans = 0;
        for(auto num: nums) ans ^= num;
        return ans;
    }
};
