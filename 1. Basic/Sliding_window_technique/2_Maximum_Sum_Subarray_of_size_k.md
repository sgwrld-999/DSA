#include<iostream>
#include<vector>

using namespace std;
//Problem link: https://practice.geeksforgeeks.org/problems/maximum-sum-subarray-of-size-k5313/1?utm_source=gfg&utm_medium=article&utm_campaign=bottom_sticky_on_article
class Solution{
public:
    int maximumSumSubarray(vector<int>& nums, int k) {
        // code here
        int n = nums.size();
        if (n < k) return 0;

        int sum = 0;

        // Calculate the sum of the first k elements
        for (int i = 0; i < k; i++) {
            sum += nums[i];
        }

        int l = 0;
        int maxSum = sum;

        // Slide the window from index k to n-1
        for (int i = k; i < n; i++) {
            sum = sum - nums[l] + nums[i];
            maxSum = max(maxSum, sum);
            l++;
        }

        return maxSum;
        
    }
};

int main(){
    int n1 ;
    cin >> n1;
    vector<int> nums1(n1);
    for(int &num : nums1) {
        cin >> num;
    }
    int k1;
    cin >> k1;
    Solution sol;
    int result = sol.maximumSumSubarray(nums1, k1);
    cout << result << endl;
    return 0;
}