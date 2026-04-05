/*
LEETCODE: 3661. Maximum Walls Destroyed by Robots

There is an endless straight line populated with some robots and walls. You are given integer arrays robots, distance, and walls:
robots[i] is the position of the ith robot.
distance[i] is the maximum distance the ith robot's bullet can travel.
walls[j] is the position of the jth wall.
Every robot has one bullet that can either fire to the left or the right at most distance[i] meters.

A bullet destroys every wall in its path that lies within its range. Robots are fixed obstacles: if a bullet hits another robot before reaching a wall, it immediately stops at that robot and cannot continue.

Return the maximum number of unique walls that can be destroyed by the robots.

Notes:

A wall and a robot may share the same position; the wall can be destroyed by the robot at that position.
Robots are not destroyed by bullets.
*/
class Solution {
public:
    int maxWalls(vector<int>& robots, vector<int>& distance,
                 vector<int>& walls) {
        int n = robots.size();

        vector<pair<int, int>> r;
        for (int i = 0; i < n; i++) {
            r.push_back({robots[i], distance[i]});
        }

        sort(r.begin(), r.end());
        sort(walls.begin(), walls.end());

        // Store intervals as indices
        vector<pair<int, int>> leftInt(n), rightInt(n);

        for (int i = 0; i < n; i++) {
            int pos = r[i].first;
            int dist = r[i].second;

            // LEFT
            int left_limit = pos - dist;
            if (i > 0)
                left_limit = max(left_limit, r[i - 1].first);

            int l = lower_bound(walls.begin(), walls.end(), left_limit) -
                    walls.begin();
            int r1 = upper_bound(walls.begin(), walls.end(), pos) -
                     walls.begin() - 1;

            leftInt[i] = {l, r1};

            // RIGHT
            int right_limit = pos + dist;
            if (i < n - 1)
                right_limit = min(right_limit, r[i + 1].first);

            int l2 =
                lower_bound(walls.begin(), walls.end(), pos) - walls.begin();
            int r2 = upper_bound(walls.begin(), walls.end(), right_limit) -
                     walls.begin() - 1;

            rightInt[i] = {l2, r2};
        }

        // DP: map last covered index → max walls
        map<int, int> dp;
        dp[-1] = 0; // no walls covered yet

        for (int i = 0; i < n; i++) {
            map<int, int> newdp;

            for (auto [last, val] : dp) {

                // LEFT choice
                auto [L, R] = leftInt[i];
                int gain = 0;
                if (L <= R) {
                    int start = max(L, last + 1);
                    if (start <= R)
                        gain = R - start + 1;
                }
                newdp[R] = max(newdp[R], val + gain);

                // RIGHT choice
                auto [L2, R2] = rightInt[i];
                gain = 0;
                if (L2 <= R2) {
                    int start = max(L2, last + 1);
                    if (start <= R2)
                        gain = R2 - start + 1;
                }
                newdp[R2] = max(newdp[R2], val + gain);
            }

            dp = newdp;
        }

        int ans = 0;
        for (auto [_, v] : dp)
            ans = max(ans, v);

        return ans;
    }
};