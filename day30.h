#pragma once

/*
Given a binary tree where each path going from the root to any leaf form a valid sequence, check if a given string is a valid sequence in such binary tree. 

We get the given string from the concatenation of an array of integers arr and the concatenation of all values of the nodes along a path results in a sequence in the given binary tree.

Example 1:

Input: root = [0,1,0,0,1,0,null,null,1,0,0], arr = [0,1,0,1]
Output: true
Explanation:
The path 0 -> 1 -> 0 -> 1 is a valid sequence (green color in the figure).
Other valid sequences are:
0 -> 1 -> 1 -> 0
0 -> 0 -> 0

Example 2:

Input: root = [0,1,0,0,1,0,null,null,1,0,0], arr = [0,0,1]
Output: false
Explanation: The path 0 -> 0 -> 1 does not exist, therefore it is not even a sequence.

Example 3:

Input: root = [0,1,0,0,1,0,null,null,1,0,0], arr = [0,1,1]
Output: false
Explanation: The path 0 -> 1 -> 1 is a sequence, but it is not a valid sequence.

Constraints:

    1 <= arr.length <= 5000
    0 <= arr[i] <= 9
    Each node's value is between [0 - 9].
*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    bool isValidSequence(TreeNode* root, const vector<int>& arr) {
        if (arr.empty()) {
            return root == nullptr;
        }

        if (!root) {
            return arr.empty();
        }

        const int n = arr.size();
        std::vector<std::pair<TreeNode*, int>> toVisit;

        toVisit.reserve(n+1);
        toVisit.push_back({root, 0});

        while (!toVisit.empty()) {
            const auto item = toVisit.back(); toVisit.pop_back();
            const auto node = std::get<0>(item);
            const int index = std::get<1>(item);

            if (index >= n) {
                // String is over and the current node has no match
                return false;
            } else if (arr[index] == node->val) {
                // If the current node matches
                // And this is the last element of arr
                if (index == n - 1) {
                    // We have a match
                    return !node->left && !node->right;
                } else {
                    // Else try the next
                    if (node->left) {
                        toVisit.push_back({node->left, index + 1});
                    }
                    // Else try the next
                    if (node->right) {
                        toVisit.push_back({node->right, index + 1});
                    }
                }
            } else {
                // Do nothing
            }
        }

        return false;
    }
};
