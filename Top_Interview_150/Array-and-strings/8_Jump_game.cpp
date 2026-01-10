class Solution {

private: 
    bool is_possible(vector<int>& nums,
                     int index,
                     vector<int>& dp)
    {
        int n = nums.size();

        // Base case: reached or crossed last index
        if(index >= n - 1) 
            return true;

        // already computed
        if(dp[index] != -1) 
            return dp[index];

        int maxJump = nums[index];

        // Try all jumps from 1 to maxJump
        for(int step = 1; step <= maxJump; step++){
            if(is_possible(nums, index + step, dp))
                return dp[index] = true;
        }

        return dp[index] = false;  
    }

public:
    bool canJump(vector<int>& nums) {
        vector<int> dp(nums.size(), -1);   // <-- FIXED
        return is_possible(nums, 0, dp);
    }
};
