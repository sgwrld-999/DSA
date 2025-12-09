#include<iostream>
#include<vector>

using namespace std;

/*
Problem Link: https://www.geeksforgeeks.org/problems/count-occurences-of-anagrams5839

Explanation: 
- Anagrams: Two strings are anagrams if they contain the same characters with the same frequencies, but possibly in a different order.

Explanation:
    1. Brute-Force Approach:
        - Given a string, for example: "xfcgv"
        - The brute-force idea is to generate all possible permutations of "xfcgv". For a string of length 5, there are 5! = 120 permutations.
        - For each permutation, check if it appears as a substring in the given text.
        - This approach is highly inefficient for larger strings due to the factorial growth of permutations.
    2. Sliding Window Technique:
        - Instead of generating all permutations, we can use a sliding window of size equal to the length of the anagram string.
        - We maintain a frequency count of characters in the anagram string and compare it with the frequency count of characters in the current window of the text.
        - If they match, we have found an occurrence of the anagram.
        - This approach is much more efficient, as it only requires linear time complexity relative to the length of the text and the anagram string.
*/

/**
Sure! Here's the **brute force version** of your anagram search problem using **factorial-based permutation comparison**. This approach is **not efficient** and is only suitable for **educational or small input size purposes**.

---

### 🧠 **Brute Force Thought Process Using Factorial Idea**

> Two strings are anagrams if:
>
> * They are the same length.
> * They contain the same characters in any order.
>
> Using brute force, we:
>
> * Generate **all substrings of length `k`** from `txt`.
> * Sort or count characters.
> * Compare it to the pattern `pat`.

Factorial-based brute force typically implies **generating all permutations**, which would be `O(k!)` per window, but this is **infeasible** for any practical `k`. Instead, a better brute-force uses **sorted comparison**, which still captures the essence of "brute-force anagram checking."

---

### ✅ **Brute Force Code Using Sorting**

```cpp
class Solution {
public:
    int search(string &pat, string &txt) {
        int n = txt.size();
        int k = pat.size();
        if (k > n) return 0;

        // Sort the pattern string
        string sortedPat = pat;
        sort(sortedPat.begin(), sortedPat.end());

        int count = 0;

        // Check all substrings of length k
        for (int i = 0; i <= n - k; i++) {
            string sub = txt.substr(i, k);
            sort(sub.begin(), sub.end());
            if (sub == sortedPat) {
                count++;
            }
        }

        return count;
    }
};
```

---

### 🕒 Time Complexity

* Sorting each window: O(k log k)
* Number of windows: O(n)
* **Total**: O(n × k log k)

---

### 🧪 Example

```cpp
txt = "cbaebabacd", pat = "abc"

Windows:
"cba" → sorted: "abc" ✅  
"bae" → sorted: "abe" ❌  
"aeb" → sorted: "abe" ❌  
...  
"bac" → sorted: "abc" ✅

Answer: 2

 */
class Solution {
public:

    int search(string &pat, string &txt) {
        int n = txt.size();
        int k = pat.size();

        if (k > n) return 0;

        unordered_map<char, int> freq;

        // Build frequency map for pattern
        for (char &ch : pat) freq[ch]++;

        int count = 0;
        int left = 0, right = 0;
        unordered_map<char, int> windowFreq;

        // Build initial window
        while (right < k) {
            windowFreq[txt[right]]++;
            right++;
        }

        // Check initial window
        if (windowFreq == freq) count++;

        // Slide the window
        while (right < n) {
            windowFreq[txt[right]]++;
            windowFreq[txt[left]]--;

            if (windowFreq[txt[left]] == 0)
                windowFreq.erase(txt[left]);

            left++;
            right++;

            if (windowFreq == freq) count++;
        }

        return count;
    }
};
