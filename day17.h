#pragma once

/*
Given a 2d grid map of '1's (land) and '0's (water), count the number of islands. An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically. You may assume all four edges of the grid are all surrounded by water.

Example 1:

Input:
11110
11010
11000
00000

Output: 1

Example 2:

Input:
11000
11000
00100
00011

Output: 3
*/

class Solution {
    inline void nuke(vector<vector<char>>& grid, const int row, const int column, const int rows, const int columns) {
        if (grid[row][column] == '1') {
            grid[row][column] = '0';

            for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <= 1; j++) {
                    const int r = row + i;
                    const int c = column + j;
                    if (abs(i) != abs(j)
                            && r >= 0 && r < rows && c >= 0 && c < columns
                            && grid[r][c] == '1') {
                        nuke(grid, r, c, rows, columns);
                    }
                }
            }
        }
    }

public:

    int numIslands(vector<vector<char>>& grid) {
        int currentIslandCount = 0,
            rows = grid.size(),
            columns = grid.empty() ? 0
                                   : grid[0].size();

        for (int row = 0; row < rows; row++) {
            for (int column = 0; column < columns; column++) {
                // We paint the grid with negative number if there is a 1 at a given position
                if (grid[row][column] == '1') {
                    // If the paint was successful we move on to the next color
                    currentIslandCount++;
                    nuke(grid, row, column, rows, columns);
                }
            }
        }

        return currentIslandCount;
    }
};
