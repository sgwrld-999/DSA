#include<iostream>
#include<vector>
#include<map>

using namespace std;

class Solution {
  public:
    int longestKSubstr(string &s, int k) {
       	 if(k  == 0) return 0 ;
	 int n = s.size();
	
	unordered_map<char,int> freq;

	int right = 0 ; 
	int left  = 0 ;
	int maxLen = -1 ;

	while(right < n){
		freq[s[right]]++;

		while(freq.size() > k){
			freq[s[left]]--;
			if(freq[s[left]] == 0)
				freq.erase(s[left]);

			left++;
		}

		if(freq.size() == k) maxLen = max(maxLen, right - left + 1);

		right++;
	}
	
	return maxLen;
        
    }
};

/*
Solution: https://chatgpt.com/share/6857d736-b0c8-8006-9bb3-cd3b4b72a63b
*/
