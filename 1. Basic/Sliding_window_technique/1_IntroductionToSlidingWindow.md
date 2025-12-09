#include <iostream>
#include <vector>

using namespace std;

/*
Problem statement: In the given problem statement it would be mention to find the subarray/substring which can be both fixed or variable.

Brute Force:
    - We'll find all the given subarrays or substring.
    - Find the required thing which can be largest/ maximum or minimum/ smallest.


How we can know the given solution can be Optimized?
1. Repeated work
2. High time complexity
3. Unnecessary Operations

How to identify the given problem statement can be solved using the sliding window technique?
1. Given array or string
2. Sub-array or sub-string
3. Find the largest/maximum or smallest/minimum

Types of sliding window:
1. Fixed: The size of the given window or sub-array/sub-string is fixed
2. Dynamic: Can be changed according to the given problem statement.


Problems based upon the:
-- Fixed SWT:
    1. Max/Min subarray of size K
    2. 1st -ve element in every window size of K
    3. Count occurrence of anagrams
    4. Max of all subarrays of size K
    5. Max of mins for every win size
-- Variable
    1. Largest / Smallest subarray of sum K
    2. Largest sub-string of K distinct characters
    3. Length of largest sub-string with NO repeating characters
    4. Pick Toy
    5. Minimum window substring


TUG_Blog: https://takeuforward.org/sliding-window/constant-window

*/

/*
Generic template for Sliding Window Technique (SWT):alignas

right = 0 , left = 0  windowSize(k) = k

while (right < n) {
    calculations or actions need to be performed by within the first window of size k
    
    if(right - left + 1 < k)  right++;
    
    if (right - left + 1 == k) {
        // Perform actions for the current window
        // e.g., calculate sum, find max/min, etc.

        ans = from the calculations

        //slide the window by incrementing left and adding the next element to the window
        left++;
        right++;
    }


*/

// Code of the Sliding window
class SlidingWindow
{
public:
    // Function to find the maximum sum of any subarray of size k
    int slidingWindowSolution(vector<int> &nums, int k)
    {
        int n = nums.size();

        // Edge case: if the array is smaller than k
        if (n < k)
            return 0;

        int sum = 0;

        // Calculate the sum of the first 'k' elements
        for (int i = 0; i < k; i++)
        {
            sum += nums[i];
        }

        int maxSum = sum;
        int l = 0;

        // Slide the window from index k to n - 1
        for (int r = k; r < n; r++)
        {
            // Remove element going out of the window and add new element coming in
            sum = sum - nums[l] + nums[r];
            maxSum = max(maxSum, sum);
            l++;
        }

        return maxSum;
    }
};

/*
 What to Say in an Interview
 I’m using the sliding window technique to find the maximum sum of any subarray of length k.

 First, I calculate the sum of the initial k elements.
 Then, I slide the window one step at a time: remove the leftmost element and add the next rightmost element.
 At each step, I update the maximum sum found so far.

 This gives an optimal O(n) time solution without recomputing the entire sum for each window.

 */
