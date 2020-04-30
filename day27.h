#pragma once

/*
Given a 2D binary matrix filled with 0's and 1's, find the largest square containing only 1's and return its area.

Example:

Input:

1 0 1 0 0
1 0 1 1 1
1 1 1 1 1
1 0 0 1 0

Output: 4
*/

class Solution {
public:

    int maximalSquare(const vector<vector<char>>& matrix) {
        if (matrix.empty()) {
            return 0;
        }

        const int rows = matrix.size(), columns = matrix[0].size();
        std::vector<std::vector<int>> dp(2, std::vector<int>(columns + 1, 0));
        int longestSide = 0, previousRow = 0, currentRow = 1;

        for (int r = 1; r <= rows; r++) {
            currentRow = r & 1;

            for (int c = 1; c <= columns; c++) {
                if (matrix[r - 1][c - 1] == '0') {
                    dp[currentRow][c] = 0;
                } else {
                    int side = 1 + std::min(dp[previousRow][c - 1],
                                            std::min(dp[previousRow][c],
                                                     dp[currentRow][c - 1]));
                    longestSide = std::max(longestSide, side);
                    dp[currentRow][c] = side;
                }
            }

            previousRow = currentRow;
        }

        return longestSide*longestSide;
    }
};
