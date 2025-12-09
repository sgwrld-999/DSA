#include<iostream>
#include<vector>
using namespace std;

/*
Thinking or thought process:

1. As per the question (ATQ), we need to find the maximum length of a sub-array (or substring) with all unique characters.
   So, we'll use a variable to track the maximum length (`maxLen`).

2. To ensure that all characters in the current window are unique, we must keep track of character frequencies.
   For this, we use a frequency map — hence, the choice of an unordered_map (hashmap).

The key point to note here is that no fixed window size `k` is given. 
So, we dynamically adjust the window. A valid window must have:
    - The number of unique characters (`freq.size()`)
    - Equal to the window size (`right - left + 1`)

For example:
    Input: "aasvs"
    - In the window "asv", all characters are unique.
    - Each character appears once, so `freq.size() == windowSize`.
    - This is a valid candidate for the longest substring.
*/
class Solution{
	int lengthOfLongestSubstring(string s){
		int n = s.size();
		int right = 0;
		int left  = 0;  // Fixed: missing semicolon

		int maxLen = 0;

		unordered_map<char,int> freq;

		while(right < n){
			freq[s[right]]++;

			while(freq.size() < right - left + 1){
				freq[s[left]]--;
				if(freq[s[left]] == 0)
					freq.erase(s[left]);

				left++;
			}

			if(freq.size() == right - left + 1)
				maxLen = max(maxLen , right - left + 1);

			right++;
		}

		return maxLen;
	}
};
