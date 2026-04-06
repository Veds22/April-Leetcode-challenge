/*
LEETCODE: 874. Walking Robot Simulation
A robot on an infinite XY-plane starts at point (0, 0) facing north. The robot receives an array of integers commands, which represents a sequence of moves that it needs to execute. There are only three possible types of instructions the robot can receive:

-2: Turn left 90 degrees.
-1: Turn right 90 degrees.
1 <= k <= 9: Move forward k units, one unit at a time.
Some of the grid squares are obstacles. The ith obstacle is at grid point obstacles[i] = (xi, yi). If the robot runs into an obstacle, it will stay in its current location (on the block adjacent to the obstacle) and move onto the next command.

Return the maximum squared Euclidean distance that the robot reaches at any point in its path (i.e. if the distance is 5, return 25).

Note:

There can be an obstacle at (0, 0). If this happens, the robot will ignore the obstacle until it has moved off the origin. However, it will be unable to return to (0, 0) due to the obstacle.
North means +Y direction.
East means +X direction.
South means -Y direction.
West means -X direction.
*/
class Solution {
    vector<int> dx = {0, 1, 0, -1};
    vector<int> dy = {1, 0, -1, 0};
public:
    int robotSim(vector<int>& commands, vector<vector<int>>& obstacles) {
        unordered_set<long long> obstacleSet;
        // conveting coordinates to int for hashing
        for(auto &o : obstacles){
            long long key = (long long)o[0] * 1000000 + o[1];
            obstacleSet.insert(key);
        }
        long x = 0;
        long y = 0;
        int face = 0;
        long ans = 0;
        for(int command: commands){
            if(command == -1) face = (face + 1) % 4;
            else if (command == -2) face = (face + 3) % 4;
            else{
                for(int i = 0; i < command; i++){
                    int nx = x + dx[face];
                    int ny = y + dy[face];
                    long long key = nx * 1000000 + ny;
                    if(obstacleSet.count(key)) break;
                    x = nx;
                    y = ny;    
                }
                ans = max(ans, (x*x + y*y));
            }
        }
        return ans; 
    }
};