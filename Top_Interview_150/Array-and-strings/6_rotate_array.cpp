#include<bits/stdc++.h>
using namespace std;

class Solution {
public:

    // 🔹 Brute-force Approach
    // Thought process:
    // - Rotate the array `k` times one by one.
    // - In each rotation, move the last element to the front and shift all other elements right by one.
    // Time Complexity: O(n * k)
    // Space Complexity: O(1)
    void rotate1(vector<int>& nums, int k) {
        int n = nums.size();
        int temp = 0;
        for (int i = 1; i <= k; i++) {
            temp = nums[n - 1];
            for (int i = n - 2; i >= 0; --i) {
                nums[i + 1] = nums[i];
            }
            nums[0] = temp;
        }
    }

    // 🔹 Optimal In-place Reverse Approach
    // Thought process:
    // - Instead of shifting elements `k` times, we reverse parts of the array to achieve the same result more efficiently.
    // Steps:
    //   1. Reverse the entire array.
    //   2. Reverse the first `k` elements.
    //   3. Reverse the remaining `n - k` elements.
    // - This simulates rotating the array to the right by `k` steps.
    // Time Complexity: O(n)
    // Space Complexity: O(1)
    void rotate2(vector<int>& nums, int k) {
        int n = nums.size();
        k %= n;
        reverse(nums, 0, n - 1);
        reverse(nums, 0, k - 1);
        reverse(nums, k, n - 1);
    }

    // 🔹 Extra Array Approach
    // Thought process:
    // - Use an extra array to directly place each element at its correct rotated position.
    // - For each index `i`, move `nums[i]` to `(i + k) % n`.
    // Time Complexity: O(n)
    // Space Complexity: O(n)
    void rotate3(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> temp(n, 0);
        for (int i = 0; i < n; i++) {
            temp[(i + k) % n] = nums[i];
        }
        nums = temp;
    }

private:
    // Helper function for in-place reversal
    void reverse(vector<int>& nums, int left, int right) {
        while (left < right) {
            swap(nums[left], nums[right]);
            left++;
            right--;
        }
    }
};
