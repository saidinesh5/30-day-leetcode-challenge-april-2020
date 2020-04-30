#pragma once
/*
Write an algorithm to determine if a number n is "happy".
A happy number is a number defined by the following process: Starting with any positive integer, replace the number by the sum of the squares of its digits, and repeat the process until the number equals 1 (where it will stay), or it loops endlessly in a cycle which does not include 1. Those numbers for which this process ends in 1 are happy numbers.
Return True if n is a happy number, and False if not.

Example:
Input: 19
Output: true

Explanation:
1^2 + 9^2 = 82
8^2 + 2^22 = 68
6^2 + 8^2 = 100
1^2 + 0^2 + 0^2 = 1
*/


class Solution {
    inline int sumOfSquaresOfDigits(int n) {
        int result = 0;

        while (n > 0) {
            int digit = n%10;
            result += digit*digit;
            n /= 10;
        }

        return result;
    }

public:
    bool isHappy(int n) {
        std::unordered_set<int> numbers {n};

        while (n != 1) {
            n = sumOfSquaresOfDigits(n);

            if (n != 1 && numbers.find(n) != numbers.end()) {
                return false;
            } else {
                numbers.insert(n);
            }
        }

        return true;
    }
};
