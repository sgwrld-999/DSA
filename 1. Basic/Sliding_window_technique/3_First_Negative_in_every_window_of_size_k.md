#include<iostream>
#include<vector>
#include<queue>

using namespace std;
/*
Function to find the first negative integer in every window of size k
in the given array.

Time Complexity: O(n)
Space Complexity: O(k) for the queue to store negative integers
where n is the size of the array and k is the size of the window.

The function returns a vector containing the first negative integer
for each complete window of size k, or 0 if there are no negative integers
in that window.

Example:
Input: arr = {-1, 2, -3, 4, -5}, k = 3
Output: {-1, -3, -3}
Explanation:
  Window 1: {-1, 2, -3} → First negative is -1
  Window 2: {2, -3, 4} → First negative is -3
  Window 3: {-3, 4, -5} → First negative is -3

If a window does not contain any negative integers, 0 is returned for that window.
Example: arr = {1, 2, 3}, k = 2 → Output: {0, 0}

The function uses a sliding window approach with a queue to efficiently track
the first negative integer in each window of size k as it moves through the array.
*/


class Solution {
public:
    vector<int> firstNegInt(vector<int>& arr, int k) {
        int left = 0, right = 0;
        int n = arr.size();
        vector<int> ans;
        queue<int> container;

        while (right < n) {
            // Add the current element to the container if it's negative
            if (arr[right] < 0) {
                container.push(arr[right]);
            }

            // Check if window size reached
            if (right - left + 1 == k) {
                // Add the front negative element or 0
                if (!container.empty()) {
                    ans.push_back(container.front());
                } else {
                    ans.push_back(0);
                }

                // Remove the element going out of the window
                if (arr[left] < 0 && !container.empty() && container.front() == arr[left]) {
                    container.pop();
                }

                left++;  // Slide the window
            }

            right++;
        }

        return ans;
    }
};


int main (){
	int n1;
	cin >> n1;
	vector<int> nums1(n1);
    for(int &num: nums1) cin >> num;
    Solution sol;
    int k;
    cin >> k;
    vector<int> ans = sol.firstNegInt(nums1, k);
    for(int num: ans) cout << num << " ";
    cout << endl;
}
