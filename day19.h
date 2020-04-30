#pragma once

/*
Suppose an array sorted in ascending order is rotated at some pivot unknown to you beforehand.

(i.e., [0,1,2,4,5,6,7] might become [4,5,6,7,0,1,2]).

You are given a target value to search. If found in the array return its index, otherwise return -1.

You may assume no duplicate exists in the array.

Your algorithm's runtime complexity must be in the order of O(log n).

Example 1:

Input: nums = [4,5,6,7,0,1,2], target = 0
Output: 4

Example 2:

Input: nums = [4,5,6,7,0,1,2], target = 3
Output: -1
*/

class Solution {
public:
    int search(vector<int>& nums, int target) {
        if (nums.size() < 2) {
            return nums.size() == 1 && nums[0] == target ? 0
                                                         : -1;
        }

        int rotation = 0;
        int start = 0, end = nums.size();

        while (end > start) {
            int mid = start + (end - start)/2;

            if (nums[std::max(0, mid - 1)] > nums[0]) {
                rotation = std::max(mid - 1, rotation);
            }

            if (nums[mid] > nums[0]) {
                rotation = std::max(mid, rotation);
                start = mid + 1;
            } else {
                end = mid - 1;
            }
        }

        // std::cout << "Rotation: " << rotation << std::endl;

        auto it = std::lower_bound(nums.cbegin(), nums.cbegin() + std::min(rotation + 1, (int)nums.size() - 1), target);
        if (target == *it) {
            return std::distance(nums.cbegin(), it);
        }

        it = std::lower_bound(nums.cbegin() + std::min(rotation + 1, (int) nums.size() - 1), nums.cend(), target);
        if (it != nums.cend() && target == *it) {
            return std::distance(nums.cbegin(), it);
        }

        return -1;
    }
};
