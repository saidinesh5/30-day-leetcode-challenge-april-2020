#pragma once

/*
Given an array nums of n integers where n > 1,  return an array output such that output[i] is equal to the product of all the elements of nums except nums[i].

Example:

Input:  [1,2,3,4]
Output: [24,12,8,6]

Constraint: It's guaranteed that the product of the elements of any prefix or suffix of the array (including the whole array) fits in a 32 bit integer.

Note: Please solve it without division and in O(n).

Follow up:
Could you solve it with constant space complexity? (The output array does not count as extra space for the purpose of space complexity analysis.)
*/

class Solution {
public:
    vector<int> productExceptSelf(const vector<int>& nums) {
        if (nums.size() < 2) {
            return nums;
        }

        const int n = nums.size();
        // Populate output with suffixes
        std::vector<int> output(n, 0);
        output[n-1] = nums[n-1];

        for (int i = n-2; i >= 0; i--) {
            output[i] = output[i+1]*nums[i];
        }

        //Update the output
        int prefix = 1;

        for (int i = 0; i < n - 1; i++) {
            output[i] = prefix*output[i+1];
            prefix *= nums[i];
        }

        output[n-1] = prefix;

        return output;
    }
};
