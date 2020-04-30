#pragma once

/*
Given a non-empty binary tree, find the maximum path sum.

For this problem, a path is defined as any sequence of nodes from some starting node to any node in the tree along the parent-child connections. The path must contain at least one node and does not need to go through the root.

Example 1:

Input: [1,2,3]

       1
      / \
     2   3

Output: 6

Example 2:

Input: [-10,9,20,null,null,15,7]

   -10
   / \
  9  20
    /  \
   15   7

Output: 42
*/

class Solution {
    // Returns maximum path sum so far, and maximum height including this node
    inline std::pair<int, int> maxPathSumHelper(const TreeNode* const root) {
        if (root->left && root->right) {
            const auto l = maxPathSumHelper(root->left);
            const auto r = maxPathSumHelper(root->right);
            const int lMaxHeightSum = std::max(0, std::get<1>(l));
            const int rMaxHeightSum = std::max(0, std::get<1>(r));
            const int valLMaxHeightSum = root->val + lMaxHeightSum;
            return {
                       std::max(valLMaxHeightSum + rMaxHeightSum, std::max(std::get<0>(r), std::get<0>(l))),
                       std::max(valLMaxHeightSum, root->val + rMaxHeightSum)
                   };
        } else if (root->left) {
            const auto l = maxPathSumHelper(root->left);
            const int lMaxHeightSum = std::max(0, std::get<1>(l));
            const int valLMaxHeightSum = root->val + lMaxHeightSum;
            return { std::max(valLMaxHeightSum, std::get<0>(l)), valLMaxHeightSum };
        } else if (root->right) {
            const auto r = maxPathSumHelper(root->right);
            const int rMaxHeightSum = std::max(0, std::get<1>(r));
            const int valRMaxHeightSum = root->val + rMaxHeightSum;
            return { std::max(valRMaxHeightSum, std::get<0>(r)), valRMaxHeightSum };
        } else {
            return { root->val, root->val };
        }
    }

public:

    int maxPathSum(TreeNode* root) {
        return std::get<0>(maxPathSumHelper(root));
    }
};
