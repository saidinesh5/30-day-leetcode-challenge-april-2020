#pragma once

/*
Return the root node of a binary search tree that matches the given preorder traversal.

(Recall that a binary search tree is a binary tree where for every node, any descendant of node.left has a value < node.val, and any descendant of node.right has a value > node.val.  Also recall that a preorder traversal displays the value of the node first, then traverses node.left, then traverses node.right.)

It's guaranteed that for the given test cases there is always possible to find a binary search tree with the given requirements.

Example 1:

Input: [8,5,1,7,10,12]
Output: [8,5,10,1,7,null,12]

Constraints:

    1 <= preorder.length <= 100
    1 <= preorder[i] <= 10^8
    The values of preorder are distinct.
*/

class Solution {
    int preorderInserter(TreeNode* parent, vector<int>& preorder, int index, int rightBound) {
        if (index + 1 < preorder.size() && preorder[index + 1] < parent->val) {
            parent->left = new TreeNode(preorder[index + 1]);
            index = preorderInserter(parent->left, preorder, index + 1, parent->val);
        }

        if (index + 1 < preorder.size() && preorder[index + 1] > parent->val && preorder[index + 1] < rightBound) {
            parent->right = new TreeNode(preorder[index + 1]);
            index = preorderInserter(parent->right, preorder, index + 1, rightBound);
        }

        return index;
    }

public:
    TreeNode* bstFromPreorder(vector<int>& preorder) {
        if (preorder.empty()) {
            return nullptr;
        }

        auto root = new TreeNode(preorder[0]);
        preorderInserter(root, preorder, 0, INT_MAX);
        return root;
    }
};
