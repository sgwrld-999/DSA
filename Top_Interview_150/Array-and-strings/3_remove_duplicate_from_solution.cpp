#include<bits/stdc++.h>

using namespace std;

class Solution {
private:
    int optimal(vector<int>& nums){
        int n = nums.size();
        if (n <= 2) return n;

        int left = 2; // First 2 elements always valid

        for (int right = 2; right < n; right++) {
            // Compare current with element two positions before
            if (nums[right] != nums[left - 2]) {
                nums[left] = nums[right];
                left++;
            }
        }

        return left;
    }
public:
    int removeDuplicates(vector<int>& nums) {
        return optimal(nums);
    }
};
