#include<bits/stdc++.h>

using namespace std;



class Solution{
private:
	void merge(vector<int>& nums, int low,int mid, int high){
		vector<int> temp;

		int left = low;
		int right = mid +1 ;

		while(left <= mid && right <= high){
			if(nums[left] <= nums[right]) temp.push_back(nums[left++]);
			else temp.push_back(nums[right++]);
		}

		while(left <= mid) temp.push_back(nums[left++]);
		while(right <= high) temp.push_back(nums[right++]);

		for(int i = low ; i <= high ; i++)
			nums[i] = temp[i-low];
	};
	void merge_sort(vector<int>& nums, int low, int high){
		if(low >= high) return;

		int mid = low + (high - low) / 2 ;
		
		merge_sort(nums,low,mid);

		merge_sort(nums,mid+1,high);

		merge(nums,low,mid,high);
	}
public:
	void sort(vector<int>& nums){
		merge_sort(nums, 0, nums.size() - 1);	
	}
};

