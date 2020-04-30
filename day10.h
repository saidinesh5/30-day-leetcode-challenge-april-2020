#pragma once

/*
Design a stack that supports push, pop, top, and retrieving the minimum element in constant time.

    push(x) -- Push element x onto stack.
    pop() -- Removes the element on top of the stack.
    top() -- Get the top element.
    getMin() -- Retrieve the minimum element in the stack.

Example 1:

Input
["MinStack","push","push","push","getMin","pop","top","getMin"]
[[],[-2],[0],[-3],[],[],[],[]]

Output
[null,null,null,null,-3,null,0,-2]

Explanation
MinStack minStack = new MinStack();
minStack.push(-2);
minStack.push(0);
minStack.push(-3);
minStack.getMin(); // return -3
minStack.pop();
minStack.top();    // return 0
minStack.getMin(); // return -2

Constraints:

    Methods pop, top and getMin operations will always be called on non-empty stacks.
*/

class MinStack {
    std::vector<int> mNodes;
    std::vector<int> mMins;

public:
    /** initialize your data structure here. */
    MinStack(){}

    void push(int x) {
        mNodes.push_back(x);

        // if x is less than current minimum, current minimum is updated
        if (mMins.empty() || x <= mMins[mMins.size() - 1]) {
            mMins.push_back(x);
        }
    }

    void pop() {
        if (mNodes.empty())
            return;

        // If current minimum is the top node, then restore current minimum to the value saved before it
        int currentMin = mNodes[mNodes.size() - 1];
        mNodes.pop_back();

        if (currentMin <= mMins[mMins.size() - 1])
            mMins.pop_back();
    }

    int top() {
        if (!mNodes.empty())
            return mNodes[mNodes.size() - 1];
        return INT_MAX;
    }

    int getMin() {
        if (!mMins.empty())
            return mMins[mMins.size() - 1];
        return INT_MAX;
    }
};
