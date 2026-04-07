/*
    LEETOCDE: 2069. Walking Robot Simulation II

A width x height grid is on an XY-plane with the bottom-left cell at (0, 0) and the top-right cell at (width - 1, height - 1). 
The grid is aligned with the four cardinal directions ("North", "East", "South", and "West"). 
A robot is initially at cell (0, 0) facing direction "East".

The robot can be instructed to move for a specific number of steps. For each step, it does the following.

Attempts to move forward one cell in the direction it is facing.
If the cell the robot is moving to is out of bounds, the robot instead turns 90 degrees counterclockwise and retries the step.
After the robot finishes moving the number of steps required, it stops and awaits the next instruction.

Implement the Robot class:

Robot(int width, int height) Initializes the width x height grid with the robot at (0, 0) facing "East".
void step(int num) Instructs the robot to move forward num steps.
int[] getPos() Returns the current cell the robot is at, as an array of length 2, [x, y].
String getDir() Returns the current direction of the robot, "North", "East", "South", or "West".
*/


# include <bits/stdc++.h>
using namespace std;

class Robot {
public:
    int width, height;
    int pos = 0;
    int cycle;
    bool moved = false;

    Robot(int width, int height) {
        this->width = width;
        this->height = height;
        cycle = 2 * (width + height - 2);
    }
    void step(int num) {
        pos = (pos + num) % cycle;
        if(num > 0) moved = true;
    }
    vector<int> getPos() {
        int p = pos;
        int w = width, h = height;
        if(p < w) return {p, 0};
        p -= w;
        if(p < h - 1) return {w - 1, p + 1};
        p -= (h - 1);
        if(p < w - 1) return {w - 2 - p, h - 1};
        p -= (w - 1);
        return {0, h - 2 - p};
    }

    string getDir() {
        int p = pos;
        int w = width, h = height;

        if(p == 0) {
            return moved ? "South" : "East";
        }

        if(p < w) return "East";
        p -= w;

        if(p < h - 1) return "North";
        p -= (h - 1);

        if(p < w - 1) return "West";

        return "South";
    }
};