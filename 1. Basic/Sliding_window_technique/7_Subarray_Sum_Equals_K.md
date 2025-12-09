#include<iostream>
#include<vector>
#include<unordered_map>
using namespace std;

/*
Problem link: https://leetcode.com/problems/subarray-sum-equals-k/
Solution: https://leetcode.com/problems/subarray-sum-equals-k/solutions/6871915/solution-by-sgwrld_999-kjke
*/

/*
In this three condition are need to be checked for sliding window technique:
1. If the sum of the current subarray is equal to k, then we have found a valid subarray.
2. If the sum of the current subarray is less than k, we need to expand the window by moving the right pointer.
3. If the sum of the current subarray is greater than k, we need to shrink the window by moving the left pointer.
*/

// 1. Brute Force
class Solution_Brute {
public:
    int subarraySum(vector<int>& nums, int k) {
        int count = 0;
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            for (int j = i; j < n; j++) {
                int sum = 0;
                for (int t = i; t <= j; t++) {
                    sum += nums[t];
                }
                if (sum == k) count++;
            }
        }
        return count;
    }
};

// 2. Prefix Sum
class Solution_PrefixSum {
public:
    int subarraySum(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> prefix(n + 1, 0);
        for (int i = 0; i < n; ++i)
            prefix[i + 1] = prefix[i] + nums[i];

        int count = 0;
        for (int i = 0; i < n; i++) {
            for (int j = i; j < n; j++) {
                if (prefix[j + 1] - prefix[i] == k)
                    count++;
            }
        }
        return count;
    }
};

// 3. Optimal: Prefix Sum + HashMap
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        unordered_map<int, int> prefixSumCount;
        prefixSumCount[0] = 1; // base case: prefix sum 0 seen once
        int count = 0, sum = 0;

        for (int num : nums) {
            sum += num;
            if (prefixSumCount.find(sum - k) != prefixSumCount.end()) {
                count += prefixSumCount[sum - k];
            }
            prefixSumCount[sum]++;
        }

        return count;
    }
};

// 4. Sliding Window (only for non-negative nums)
class Solution_SlidingWindow {
public:
    int subarraySum(vector<int>& nums, int k) {
        int left = 0, right = 0, sum = 0, count = 0;
        int n = nums.size();

        while (right < n) {
            sum += nums[right];

            while (left <= right && sum > k) {
                sum -= nums[left];
                left++;
            }

            if (sum == k)
                count++;

            right++;
        }

        return count;
    }
};
