#include<bits/stdc++.h>
using namespace std;

class Solution {
    /*
    Brute force:
        Time-complexity: O(n)
        Space-complexity: O(n-num_of_val_present)
    */
    int brute_force(vector<int>& nums, int val) {
        int n = nums.size();
        if(n == 1 && val == nums[0]) return 0;

        vector<int> temp;
        for(int it: nums){
            if(it == val) 
                continue;
            temp.push_back(it);
        }

        for(int i = 0 ; i < temp.size() ; i++){
            nums[i] = temp[i];
        }

        return temp.size();
    }

    /*
    Optimal Solution:
        Time-complexity: O(n)
        Space-complexity: O(1)
    */
   int optimal(vector<int>& nums, int val){
    int index = 0 ; 
    for(int i = 0 ; i < nums.size() ; i++){ 
        if(nums[i] != val){
             nums[index++] = nums[i]; 
        } 
    } 
    return index;
   }
public:
    int removeElement(vector<int>& nums, int val) {
        return brute_force(nums,val);
    }
};