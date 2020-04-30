#pragma once

/*
Given a binary array, find the maximum length of a contiguous subarray with equal number of 0 and 1.

Example 1:

Input: [0,1]
Output: 2
Explanation: [0, 1] is the longest contiguous subarray with equal number of 0 and 1.

Example 2:

Input: [0,1,0]
Output: 2
Explanation: [0, 1] (or [1, 0]) is a longest contiguous subarray with equal number of 0 and 1.

Note: The length of the given binary array will not exceed 50,000. 
*/

class Solution {
public:
    int findMaxLength(vector<int>& nums) {
        int result = 0, height = 0;

        //If we plot a graph where height drops by 1 at 0 and height ups by 1 at 1,
        //Equal number of 1's and 0's for a given height would be the last index we
        //encountered that value
        //For Fast lookup of a height for where we first encountered a height, w
        //As height can go from -nums.size() to nums.size(), we use int
        //and to look up a height, we just do height+nums.size()
        std::vector<int> heightAt(2*nums.size() + 1, -2);
        heightAt[nums.size()] = -1;

        for (int i = 0; i < nums.size(); i++) {
            const int n = nums[i];
            height += (n == 0? -1 : 1);
            int heightIndex = height + nums.size();
            if (heightAt[heightIndex] != -2) {
                result = std::max(result, i - heightAt[heightIndex]);
            } else {
                heightAt[heightIndex] = i;
            }

        }

        return result;
    }
};
