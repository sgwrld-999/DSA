# Substring with Concatenation of All Words

## Problem Statement

You are given a string `s` and an array of strings `words`.

* All strings in `words` are of the **same length**
* A valid substring is formed by concatenating **all words exactly once**
* Words can appear in **any order**
* Substring must be **contiguous**

Return the **starting indices** of all valid substrings in `s`.

---

## Key Observations

* Each word has **equal length** (explicitly stated in the problem)
* Total length of a valid substring is **fixed**
* Order of words does **not** matter
* Duplicate words **can exist**
* Character-based sliding window **will not work**
* This is a **word-based sliding window** problem

---

## Important Constraints (Very Important)

> **All strings of `words` are of the same length**

This single line enables:

* Fixed-size window
* Pointer jumps by `word_len`
* Linear-time sliding window solution

Without this, the problem becomes significantly harder.

---

## Possible Approaches

### 1. Brute Force (Not Feasible)

* Generate all permutations of `words`
* Concatenate each permutation
* Search each in `s`

❌ Time Complexity: `O(n × k!)`
❌ Completely impractical

---

### 2. Check Every Substring of Length `total_len`

* Precompute frequency of `words`
* For each index `i`, check substring `s[i:i+total_len]`
* Split into chunks of `word_len`
* Compare frequency maps

⚠️ Time Complexity: `O(n × word_count)`
⚠️ Passes small cases, but inefficient

---

### 3. Sliding Window (Optimal Approach)

✅ **Correct and intended solution**

---

## Optimal Approach (Word-Based Sliding Window)

### Core Idea

* Use a window of size `total_len = word_len × word_count`
* Slide the window in **steps of `word_len`**
* Maintain a frequency map of words inside the window
* Shrink window when frequency exceeds allowed count

---

## Why Multiple Starting Offsets?

Since we move in steps of `word_len`, valid substrings can start at:

```
0, 1, 2, ..., word_len - 1
```

Example:

```
s = "barfoothefoobarman"
word_len = 3
```

Valid parsing must try offsets `0`, `1`, and `2`.

---

## Algorithm Steps

1. If `s` or `words` is empty → return `[]`
2. Compute:

   ```
   word_len = len(words[0])
   word_count = len(words)
   total_len = word_len * word_count
   ```
3. Build frequency map of `words`
4. For each offset in `0 … word_len-1`:

   * Initialize `left = offset`
   * Slide `right` in steps of `word_len`
   * Extract word from `s`
   * Update window frequency
   * Shrink window if frequency exceeds
   * If window contains all words → record index

---

## Correct Python Implementation

```python
from typing import List
from collections import defaultdict

class Solution:
    def findSubstring(self, s: str, words: List[str]) -> List[int]:
        if not s or not words:
            return []

        word_len = len(words[0])
        word_count = len(words)
        total_len = word_len * word_count
        n = len(s)

        word_dict = defaultdict(int)
        for w in words:
            word_dict[w] += 1

        ans = []

        for offset in range(word_len):
            left = offset
            count = 0
            window = defaultdict(int)

            for right in range(offset, n - word_len + 1, word_len):
                word = s[right:right + word_len]

                if word in word_dict:
                    window[word] += 1
                    count += 1

                    while window[word] > word_dict[word]:
                        left_word = s[left:left + word_len]
                        window[left_word] -= 1
                        left += word_len
                        count -= 1

                    if count == word_count:
                        ans.append(left)
                else:
                    window.clear()
                    count = 0
                    left = right + word_len

        return ans
```

---

## Dry Run

### Input

```python
s = "barfoothefoobarman"
words = ["foo", "bar"]
```

### Setup

```
word_len = 3
word_count = 2
total_len = 6
```

### Valid Windows

```
"barfoo" at index 0
"foobar" at index 9
```

### Output

```
[0, 9]
```

---

## Time & Space Complexity

* **Time Complexity:** `O(n)`
* **Space Complexity:** `O(k)` where `k` is number of unique words

---

## Common Mistakes (Very Important)

* Treating this as a **character-based sliding window**
* Ignoring the **equal word length constraint**
* Sliding `right` by `1` instead of `word_len`
* Comparing incorrect frequency maps
* Not resetting window on invalid word
* Forgetting duplicate words handling

---

## Key Takeaways

* This is **not** a substring problem — it’s a **token window** problem
* Equal word length is the **key enabler**
* Sliding window moves in **fixed steps**
* Frequency control defines correctness
* Pattern appears in **log parsing**, **token streams**, and **compiler-style problems**

---
