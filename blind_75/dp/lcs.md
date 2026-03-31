## 1️⃣ Brute Force (Recursion)

```python
class Solution:
    def solve(self, a, b, i, j):
        # base case
        if i == len(a) or j == len(b):
            return 0

        # match
        if a[i] == b[j]:
            return 1 + self.solve(a, b, i + 1, j + 1)

        # not match
        return max(
            self.solve(a, b, i, j + 1),
            self.solve(a, b, i + 1, j)
        )

    def longestCommonSubsequence(self, text1: str, text2: str) -> int:
        return self.solve(text1, text2, 0, 0)
```

---

## 2️⃣ Memoization (Top-down DP)

```python
class Solution:
    def solve(self, a, b, i, j, dp):
        if i == len(a) or j == len(b):
            return 0

        if dp[i][j] != -1:
            return dp[i][j]

        if a[i] == b[j]:
            dp[i][j] = 1 + self.solve(a, b, i + 1, j + 1, dp)
        else:
            dp[i][j] = max(
                self.solve(a, b, i, j + 1, dp),
                self.solve(a, b, i + 1, j, dp)
            )

        return dp[i][j]

    def longestCommonSubsequence(self, text1: str, text2: str) -> int:
        n, m = len(text1), len(text2)
        dp = [[-1] * m for _ in range(n)]
        return self.solve(text1, text2, 0, 0, dp)
```

---

## 3️⃣ Tabulation (Bottom-up DP)

```python
class Solution:
    def longestCommonSubsequence(self, text1: str, text2: str) -> int:
        n, m = len(text1), len(text2)

        dp = [[0] * (m + 1) for _ in range(n + 1)]

        for i in range(n - 1, -1, -1):
            for j in range(m - 1, -1, -1):
                if text1[i] == text2[j]:
                    dp[i][j] = 1 + dp[i + 1][j + 1]
                else:
                    dp[i][j] = max(dp[i][j + 1], dp[i + 1][j])

        return dp[0][0]
```

---

## 4️⃣ Space Optimized (Most Optimized)

```python
class Solution:
    def longestCommonSubsequence(self, text1: str, text2: str) -> int:
        n, m = len(text1), len(text2)

        prev = [0] * (m + 1)

        for i in range(n - 1, -1, -1):
            curr = [0] * (m + 1)
            for j in range(m - 1, -1, -1):
                if text1[i] == text2[j]:
                    curr[j] = 1 + prev[j + 1]
                else:
                    curr[j] = max(curr[j + 1], prev[j])
            prev = curr

        return prev[0]
```

---

# 🎤 Interview Script — Longest Common Subsequence (LCS)

---

## 1. Opening

**“Let me restate the problem.”**

We are given two strings `text1` and `text2`.

We need to find:

> the length of the longest subsequence common in both strings

👉 Subsequence means:

* we can skip characters
* order must remain same

---

## 2. Intuition

**“At every pair of indices (i, j), I have two possibilities.”**

---

### Case 1: Characters match

```python
if text1[i] == text2[j]
```

👉 Then:

> this character is part of LCS

So:

```python
1 + solve(i+1, j+1)
```

---

### Case 2: Characters do NOT match

👉 Then we have two choices:

* skip from first string
* skip from second string

```python
max(
    solve(i, j+1),
    solve(i+1, j)
)
```

---

## 3. Recursive Idea (Brute Force)

**“Let me first explain the recursive solution.”**

---

### State

```python
f(i, j)
```

👉 meaning:

> LCS from index `i` in text1 and `j` in text2

---

### Base case

```python
if i == len(text1) or j == len(text2):
    return 0
```

👉 If any string finishes → no subsequence possible

---

### Transition

```python
if match:
    return 1 + f(i+1, j+1)
else:
    return max(f(i, j+1), f(i+1, j))
```

---

## 4. Problem with recursion

**“This leads to overlapping subproblems.”**

👉 Same `(i, j)` computed many times
👉 Time complexity → exponential ❌

---

## 5. Memoization (Top-down DP)

**“To optimize, I store results in a DP table.”**

```python
dp[i][j]
```

👉 Stores result of `f(i, j)`

---

### Benefit

* Avoid recomputation
* Time becomes **O(n × m)**

---

## 6. Tabulation (Bottom-up DP)

**“Now I convert recursion into iteration.”**

---

### DP definition

```python
dp[i][j] = LCS from i to end of text1 and j to end of text2
```

---

### Base case

```python
dp[n][*] = 0
dp[*][m] = 0
```

---

### Fill table

From bottom to top:

```python
for i from n-1 → 0
for j from m-1 → 0
```

---

### Transition

```python
if match:
    dp[i][j] = 1 + dp[i+1][j+1]
else:
    dp[i][j] = max(dp[i][j+1], dp[i+1][j])
```

---

## 7. Space Optimization

**“We only need next row to compute current row.”**

👉 Use 2 arrays:

* `prev`
* `curr`

---

## 8. Dry Run

### Example:

```text
text1 = "abcde"
text2 = "ace"
```

👉 LCS = `"ace"` → length = **3**

---

## 9. Complexity

### Time

**O(n × m)**

---

### Space

* Tabulation → O(n × m)
* Optimized → O(m)

---

## 10. How to explain in interview

You can say:

**“At each index pair, if characters match I include it, otherwise I try skipping one character from either string and take the maximum.”**

---

## 11. Brute → Optimized thinking

**“Start with recursion.”**

→ overlapping subproblems
→ memoization

→ tabulation

→ space optimization

---

## 12. 30-second answer

**“This is a classic DP problem where I define a state (i, j). If characters match, I include them; otherwise, I take the max by skipping from either string. I optimize from recursion to memoization and then to bottom-up DP with optional space optimization.”**

---

## 13. 10-second answer

**“Use DP on two strings: match → 1 + diagonal, else max of right and down.”**

---

## 14. Closing line

**“The key insight is modeling the problem as decisions on two indices and avoiding recomputation using DP.”**

---
