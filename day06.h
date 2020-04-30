#pragma once

/*
Given an array of strings, group anagrams together.

Example:

Input: ["eat", "tea", "tan", "ate", "nat", "bat"],
Output:
[
  ["ate","eat","tea"],
  ["nat","tan"],
  ["bat"]
]

Note:

    All inputs will be in lowercase.
    The order of your output does not matter.

*/

class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        vector<vector<string>> result;
        unordered_map<string, ssize_t> anagramKeyIndex;

        for (const auto &s: strs) {
            string key = s;
            std::sort(key.begin(), key.end());
            ssize_t keyIndex = -1;

            auto it = anagramKeyIndex.find(key);
            if (it == anagramKeyIndex.end()) {
                keyIndex = result.size();
                anagramKeyIndex.insert({key, result.size()});
                result.push_back({});
            } else {
                keyIndex = it->second;
            }

            result[keyIndex].push_back(std::move(s));
        }

        return result;
    }
};
