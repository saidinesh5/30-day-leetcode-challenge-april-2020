#pragma once

/*
Given a string containing only three types of characters: '(', ')' and '*', write a function to check whether this string is valid. We define the validity of a string by these rules:

    Any left parenthesis '(' must have a corresponding right parenthesis ')'.
    Any right parenthesis ')' must have a corresponding left parenthesis '('.
    Left parenthesis '(' must go before the corresponding right parenthesis ')'.
    '*' could be treated as a single right parenthesis ')' or a single left parenthesis '(' or an empty string.
    An empty string is also valid.

Example 1:

Input: "()"
Output: True

Example 2:

Input: "(*)"
Output: True

Example 3:

Input: "(*))"
Output: True

Note:

    The string size will be in the range [1, 100].
*/

typedef std::vector< std::vector<int> > ValidityCache;

class Solution {
    bool isValid(std::string const &s, int currentPosition, int openParenthesis, ValidityCache &cache) {
        if (cache[currentPosition][openParenthesis] != -1) {
            return cache[currentPosition][openParenthesis];
        }

        // If there are elements in the string to process, process them
        bool result = false;
        if (currentPosition < s.size()) {
            if (s[currentPosition] == ')') {
                // We don't need the openParenthesis > 0, but it is a nice short circuit optimization
                result = openParenthesis > 0 && isValid(s, currentPosition + 1, openParenthesis - 1, cache);
            } else if (s[currentPosition] == '(') {
                result = isValid(s, currentPosition + 1, openParenthesis + 1, cache);
            } else if (s[currentPosition] == '*') {
                result = (openParenthesis > 0 && isValid(s, currentPosition + 1, openParenthesis - 1, cache)) || // ')'
                          isValid(s, currentPosition + 1, openParenthesis + 1, cache) ||                         // '('
                          isValid(s, currentPosition + 1, openParenthesis, cache);                               // ''
            } else {
                result = false;
            }
        } else {
            // Otherwise we have a valid string if we have no open parenthesis to pop
            result = (openParenthesis == 0);
        }

        cache[currentPosition][openParenthesis] = result;

        return result;
    }
public:
    bool checkValidString(string s) {
        ValidityCache mValidityCache(s.size() + 1,
                                     std::vector<int>(s.size() + 1, -1));
        return isValid(s, 0, 0, mValidityCache);
    }
};
