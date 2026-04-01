
# ✅ Python Code (All Approaches)

---

## 🔴 1. Recursion (Brute Force)

```python
class Solution:
    def solve(self, s, index):
        # base
        if index == len(s):
            return 1

        # invalid case (leading zero)
        if s[index] == '0':
            return 0

        # take 1 digit
        one = self.solve(s, index + 1)

        # take 2 digits
        two = 0
        if (index + 1 < len(s) and 
            int(s[index:index+2]) <= 26):
            two = self.solve(s, index + 2)

        return one + two

    def numDecodings(self, s):
        return self.solve(s, 0)
```

---

## 🟡 2. Memoization (Top-Down DP)

```python
class Solution:
    def solve(self, s, index):
        if index == len(s):
            return 1

        if s[index] == '0':
            return 0

        if self.dp[index] != -1:
            return self.dp[index]

        one = self.solve(s, index + 1)

        two = 0
        if (index + 1 < len(s) and 
            int(s[index:index+2]) <= 26):
            two = self.solve(s, index + 2)

        self.dp[index] = one + two
        return self.dp[index]

    def numDecodings(self, s):
        self.dp = [-1] * len(s)
        return self.solve(s, 0)
```

---

## 🟢 3. Tabulation (Bottom-Up DP)

```python
class Solution:
    def numDecodings(self, s):
        n = len(s)
        dp = [0] * (n + 1)

        dp[n] = 1  # base

        for i in range(n - 1, -1, -1):

            if s[i] == '0':
                dp[i] = 0
            else:
                # one digit
                dp[i] = dp[i + 1]

                # two digits
                if (i + 1 < n and 
                    int(s[i:i+2]) <= 26):
                    dp[i] += dp[i + 2]

        return dp[0]
```

---

## 🔵 4. Space Optimization (Best)

```python
class Solution:
    def numDecodings(self, s):
        n = len(s)

        next1 = 1  # dp[i+1]
        next2 = 0  # dp[i+2]

        for i in range(n - 1, -1, -1):

            curr = 0

            if s[i] != '0':
                # one digit
                curr = next1

                # two digits
                if (i + 1 < n and 
                    int(s[i:i+2]) <= 26):
                    curr += next2

            next2 = next1
            next1 = curr

        return next1
```

---

# 🎤 Interview Script — Decode Ways

---

## 1. Opening

**“Let me restate the problem.”**

We are given:

* A string `s` containing digits

We need to:

> Count how many ways we can decode it into letters
> (1 → A, 2 → B, …, 26 → Z)

---

## 2. Intuition

**“At every index, I have two choices.”**

👉 I can:

* Take **1 digit**
* Take **2 digits (if valid)**

---

## 3. Recursive Idea

---

### State

```python
f(index)
```

👉 Number of ways to decode from `index` to end

---

## 4. Base Case

```python
if index == len(s):
    return 1
```

👉 Successfully decoded whole string

---

## 5. Invalid Case (VERY IMPORTANT)

```python
if s[index] == '0':
    return 0
```

👉 '0' cannot be decoded alone

---

## 6. Choices

---

### ✅ Take 1 digit

```python
f(index + 1)
```

---

### ✅ Take 2 digits

```python
if s[index:index+2] <= 26:
    f(index + 2)
```

---

## 7. Transition

```python
f(i) = f(i+1) + f(i+2)
```

👉 Only if valid

---

## 8. Problem with Recursion

👉 Overlapping subproblems

```text
O(2^n)
```

---

## 9. Memoization

**“Store result of each index.”**

```python
dp[index]
```

---

## 10. Tabulation

**“Build from end to start.”**

👉 Why?

Because:

```python
f(i) depends on f(i+1), f(i+2)
```

---

## 11. Space Optimization

👉 Only need:

```python
dp[i+1], dp[i+2]
```

So we use 2 variables

---

## 12. Dry Run

Example:

```text
s = "226"
```

Paths:

```
2 2 6 → B B F
22 6 → V F
2 26 → B Z
```

👉 Answer = 3

---

## 13. Key Insight

**“This is a classic DP on strings where each index depends on next two positions.”**

---

## 14. Edge Cases (VERY IMPORTANT)

| Case  | Result |
| ----- | ------ |
| "0"   | 0      |
| "06"  | 0      |
| "10"  | 1      |
| "100" | 0      |

---

## 15. Complexity

### Time

```
O(n)
```

---

### Space

| Approach   | Space |
| ---------- | ----- |
| Recursion  | O(n)  |
| Memo       | O(n)  |
| Tabulation | O(n)  |
| Optimized  | O(1)  |

---

## 16. How to explain in interview

**“At each index, I try to decode one digit or two digits if valid. I use DP since results overlap and optimize space using two variables.”**

---

## 17. 30-second answer

**“DP on string: f(i) = f(i+1) + f(i+2) if valid. Handle zero carefully.”**

---

## 18. 10-second answer

**“DP with 1-step and 2-step decoding, skip invalid zeros.”**

---

## 19. Closing line

**“The key idea is splitting the problem into decoding one or two digits and using DP to avoid recomputation.”**

---


