/*
    LEETCODE: 3655. XOR After Range Multiplication Queries II
    
    You are given an integer array nums of length n and a 2D integer array queries of size q, 
    where queries[i] = [li, ri, ki, vi].
    For each query, you must apply the following operations in order:

    Set idx = li.
    While idx <= ri:
    Update: nums[idx] = (nums[idx] * vi) % (109 + 7).
    Set idx += ki.
    Return the bitwise XOR of all elements in nums after processing all queries.
*/

#include <bit/stdc++.h>
using namespace std;
class Solution {
    int mod = 1e9 + 7;
    int power(long long a, long long b){
        if(a == 0 || a == 1) return a;
        if (b == 0) return 1; 
        int half = power(a, b/2);
        int ans = (long long)half * half % mod;
        if (b % 2) ans = a * ans % mod;
        return ans;
    }
public:
    int xorAfterQueries(vector<int>& nums, vector<vector<int>>& queries) {
        int n = nums.size();
        int blockSize = sqrt(n);
        vector<vector<vector<int>>> groupByK(blockSize);
        for(auto &q: queries){
            int l = q[0], r = q[1], k = q[2], v = q[3];
            if(k < blockSize) groupByK[k].push_back({l, r, v});
            else {
                for(int i = l; i <= r; i += k) nums[i] = 1LL * nums[i] * v % mod;
            }
        }
        vector<long long> diff(n + blockSize);
        for(int k = 1; k < blockSize; k++){
            if (groupByK[k].empty()) continue;
            fill(diff.begin(), diff.end(), 1);
            for(auto &q: groupByK[k]){
                int l = q[0], r = q[1], v = q[2];
                diff[l] = diff[l] * v % mod;
                int steps = (r - l) / k;
                int next = l + (steps + 1) * k;
                diff[next] = diff[next] * power(v, mod - 2) % mod;
            }
            for(int i = k; i < n; i++) diff[i] = diff[i] * diff[i - k] % mod;
            for(int i = 0; i < n; i++) nums[i] = 1LL * nums[i] * diff[i] % mod;
        }
        int res = 0;
        for(int i = 0; i < n; i++) res ^= nums[i];
        return res;
    }
};