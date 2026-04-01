

# ✅ Python Code (All Approaches)

---

## 🔴 1. Recursion (Brute Force)

```python
class Solution:
    def solve(self, i, j):
        # base cases
        if i == 0 and j == 0:
            return 1
        
        if i < 0 or j < 0:
            return 0

        # move up + move left
        up = self.solve(i - 1, j)
        left = self.solve(i, j - 1)

        return up + left

    def uniquePaths(self, m, n):
        return self.solve(m - 1, n - 1)
```

---

## 🟡 2. Memoization (Top-Down DP)

```python
class Solution:
    def solve(self, i, j):
        if i == 0 and j == 0:
            return 1
        
        if i < 0 or j < 0:
            return 0

        if self.dp[i][j] != -1:
            return self.dp[i][j]

        up = self.solve(i - 1, j)
        left = self.solve(i, j - 1)

        self.dp[i][j] = up + left
        return self.dp[i][j]

    def uniquePaths(self, m, n):
        self.dp = [[-1]*n for _ in range(m)]
        return self.solve(m - 1, n - 1)
```

---

## 🟢 3. Tabulation (Bottom-Up DP)

```python
class Solution:
    def uniquePaths(self, m, n):
        dp = [[0]*n for _ in range(m)]

        for i in range(m):
            for j in range(n):
                
                if i == 0 and j == 0:
                    dp[i][j] = 1
                else:
                    up = dp[i-1][j] if i > 0 else 0
                    left = dp[i][j-1] if j > 0 else 0

                    dp[i][j] = up + left

        return dp[m-1][n-1]
```

---

## 🔵 4. Space Optimization (Best)

```python
class Solution:
    def uniquePaths(self, m, n):
        prev = [0]*n

        for i in range(m):
            curr = [0]*n
            for j in range(n):

                if i == 0 and j == 0:
                    curr[j] = 1
                else:
                    up = prev[j]
                    left = curr[j-1] if j > 0 else 0

                    curr[j] = up + left

            prev = curr

        return prev[n-1]
```

---

# 🎤 Interview Script — Unique Paths

---

## 1. Opening

**“Let me restate the problem.”**

We are given:

* A grid of size `m x n`
* A robot starts at top-left `(0,0)`
* It can only move **right or down**

We need to:

> Find total number of unique paths to reach bottom-right `(m-1, n-1)`

---

## 2. Intuition

**“At every cell, I can come from two directions.”**

👉 Either:

* From **top** `(i-1, j)`
* From **left** `(i, j-1)`

---

## 3. Recursive Idea (Brute Force)

---

### State

```python
f(i, j)
```

👉 Number of ways to reach `(i, j)`

---

## 4. Base Cases

### ✅ Start cell

```python
if i == 0 and j == 0:
    return 1
```

---

### ❌ Out of bounds

```python
if i < 0 or j < 0:
    return 0
```

---

## 5. Transition

```python
f(i, j) = f(i-1, j) + f(i, j-1)
```

👉 Total ways = from top + from left

---

## 6. Problem with Recursion

👉 Overlapping subproblems

Example:

```
f(2,2) calls f(1,2) and f(2,1)
Both again call f(1,1)
```

👉 Repeated computation → inefficient

---

## 7. Memoization (Optimization)

**“I store already computed states.”**

```python
dp[i][j]
```

👉 Avoid recomputation

---

## 8. Tabulation (Bottom-Up)

**“Instead of recursion, I build the solution iteratively.”**

👉 Start from `(0,0)`
👉 Fill row by row

---

## 9. Space Optimization

**“We only need previous row.”**

👉 Instead of full matrix:

* Use 1D arrays
* Reduce space from `O(m*n)` → `O(n)`

---

## 10. Dry Run

Example:

```text
m = 3, n = 3
```

Grid:

```
1 1 1
1 2 3
1 3 6
```

👉 Answer = **6**

---

## 11. Key Insight

**“Each cell depends only on top and left.”**

👉 That’s why DP works perfectly

---

## 12. Complexity

### Time Complexity

```
O(m * n)
```

---

### Space Complexity

| Approach   | Space  |
| ---------- | ------ |
| Recursion  | O(m+n) |
| Memo       | O(m*n) |
| Tabulation | O(m*n) |
| Optimized  | O(n)   |

---

## 13. How to explain in interview

**“At each cell, I can reach it either from top or left. So I use DP where each cell stores the sum of ways from top and left. I optimize space by using only one row.”**

---

## 14. 30-second answer

**“This is a DP problem where each cell depends on top and left. I use dp[i][j] = dp[i-1][j] + dp[i][j-1] and optimize space to O(n).”**

---

## 15. 10-second answer

**“Grid DP: ways = top + left, optimized to O(n) space.”**

---

## 16. Closing line

**“The key idea is recognizing overlapping subproblems and using DP to build the solution efficiently.”**

---

