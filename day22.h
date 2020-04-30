#pragma once

/*
Given an array of integers and an integer k, you need to find the total number of continuous subarrays whose sum equals to k.

Example 1:

Input:nums = [1,1,1], k = 2
Output: 2

Note:
    The length of the array is in range [1, 20,000].
    The range of numbers in the array is [-1000, 1000] and the range of the integer k is [-1e7, 1e7].
*/

class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        std::unordered_map<int, int> sumFrequency;

        int result = 0;
        int sum = 0;

        for (const auto n: nums) {
            sum += n;

            if (sum == k) {
                result++;
            }

            auto it = sumFrequency.find(sum - k);
            if (it != sumFrequency.end()) {
                result += it->second;
            }

            sumFrequency[sum]++;
        }
        return result;
    }
};
