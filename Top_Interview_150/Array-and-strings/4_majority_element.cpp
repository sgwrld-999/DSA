#include<bits/stdc++.h>
using namespace std;

// O(n) Time | O(n) Space
class Solution {
public:
    int majorityElementInN(vector<int>& nums) {
        int n = nums.size();
        unordered_map<int, int> freq;

        for (int num : nums)
            freq[num]++;

        for (auto &p : freq)
            if (p.second > n / 2)
                return p.first;

        return -1; // (not needed as per constraints)
    }

    int majorityElementInNLogN(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        return nums[nums.size() / 2];
    }

    int majorityElement(vector<int>& nums) {
        int candidate = 0;
        int count = 0;

        for (int num : nums) {
            if (count == 0)
                candidate = num;
            
            count += (num == candidate ? 1 : -1);
        }

        return candidate;
    }
};
