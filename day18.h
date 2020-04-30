#pragma once

/*
Given a m x n grid filled with non-negative numbers, find a path from top left to bottom right which minimizes the sum of all numbers along its path.

Note: You can only move either down or right at any point in time.

Example:

Input:
[
  [1,3,1],
  [1,5,1],
  [4,2,1]
]
Output: 7
Explanation: Because the path 1→3→1→1→1 minimizes the sum.
*/

class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        int rows = grid.size(), columns = grid.empty() ?  0 : grid[0].size();
        if (rows == 0 || columns == 0)
            return 0;

        // Initialize the base case
        for (int c = 1; c < columns; c++)
            grid[0][c] += grid[0][c-1];

        for (int r = 1; r < rows; r++) {
            grid[r][0] += grid[r - 1][0];

            for (int c = 1; c < columns; c++) {
                grid[r][c] += min(grid[r][c - 1], grid[r - 1][c]);
            }
        }

        return grid[rows - 1][columns - 1];
    }
};
