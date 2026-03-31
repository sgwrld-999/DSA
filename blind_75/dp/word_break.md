## 1️⃣ Brute Force (Recursion)

```python
class Solution:
    def solve(self, idx, s, word_set):
        # base case
        if idx >= len(s):
            return True

        # try all partitions
        for i in range(idx + 1, len(s) + 1):
            substring = s[idx:i]

            if substring in word_set and self.solve(i, s, word_set):
                return True

        return False

    def wordBreak(self, s, wordDict):
        word_set = set(wordDict)
        return self.solve(0, s, word_set)
```

---

## 2️⃣ Memoization (Optimized)

```python
class Solution:
    def solve(self, idx, s, word_set, dp):
        # base case
        if idx >= len(s):
            return True

        if dp[idx] != -1:
            return dp[idx] == 1

        for i in range(idx + 1, len(s) + 1):
            substring = s[idx:i]

            if substring in word_set and self.solve(i, s, word_set, dp):
                dp[idx] = 1
                return True

        dp[idx] = 0
        return False

    def wordBreak(self, s, wordDict):
        n = len(s)
        word_set = set(wordDict)
        dp = [-1] * (n + 1)

        return self.solve(0, s, word_set, dp)
```

# ✅ Python Code (Bottom-Up / Tabulation)

```python
class Solution:
    def wordBreak(self, s, wordDict):
        n = len(s)
        word_set = set(wordDict)

        dp = [False] * (n + 1)
        dp[n] = True   # base case

        for i in range(n - 1, -1, -1):
            for j in range(i + 1, n + 1):
                if s[i:j] in word_set and dp[j]:
                    dp[i] = True
                    break

        return dp[0]
```

---

---

# 🎤 Interview Script — Word Break Problem

*(Following your document format)* 

---

## 1. Opening

**“Let me restate the problem.”**

We are given:

* A string `s`
* A dictionary of words `wordDict`

We need to check:

> Can we break the string into valid dictionary words?

---

## 2. Intuition

**“At every index, I try to cut the string into valid prefixes.”**

👉 From index `idx`, I try:

* All possible substrings starting from `idx`
* If a substring exists in dictionary → recursively solve remaining

---

## 3. Recursive Idea (Brute Force)

**“Let me first explain the brute force solution.”**

---

### State

```python
f(idx)
```

👉 Meaning:

> Can we break the string starting from index `idx`?

---

### Base case

```python
if idx == len(s):
    return True
```

👉 Entire string is successfully broken

---

### Transition

```python
for i in range(idx+1 → n):
    if s[idx:i] in dict AND f(i) is True:
        return True
```

---

## 4. Dry Thinking

Example:

```text
s = "leetcode"
dict = ["leet", "code"]
```

👉 Try:

* "l", "le", "lee", "leet" ✅
* Now solve remaining `"code"`

👉 Works → return True

---

## 5. Problem with recursion

**“This approach recomputes same indices multiple times.”**

👉 Example:

* `f(4)` can be called multiple times

👉 Time complexity → exponential ❌

---

## 6. Memoization (Optimization)

**“To optimize, I store results for each index.”**

---

### DP Definition

```python
dp[idx] = True/False
```

👉 Whether string from `idx` can be broken

---

### Use

```python
if dp[idx] != -1:
    return dp[idx]
```

---

### Benefit

* Avoid recomputation
* Time → **O(n²)**

---

## 7. Final Logic

```python
if substring in dict AND next state is True:
    mark dp[idx] = True
```

Else:

```python
dp[idx] = False
```

---

## 8. Complexity

### Time

* O(n²) → checking all substrings

### Space

* O(n) → dp array
* recursion stack

---

## 9. How to explain in interview

**“At each index, I try all possible prefixes. If a prefix is valid and the remaining string is also valid, I return true. To optimize, I cache results using DP to avoid recomputation.”**

---

## 10. 30-second answer

**“This is a DP problem where I define a state on index. I try all substrings starting from that index. If a substring is in dictionary and remaining string is valid, I return true. I optimize recursion using memoization.”**

---

## 11. 10-second answer

**“Try all prefixes + recursion + memoization to avoid recomputation.”**

---

## 12. Closing line

**“The key insight is breaking the problem into smaller substrings and caching results for overlapping subproblems.”**

---


