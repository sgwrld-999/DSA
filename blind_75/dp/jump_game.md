# ✅ Python Code (All Approaches)

---

## 🔴 1. Recursion (Brute Force)

```python
class Solution:
    def solve(self, nums, index):
        # base
        if index >= len(nums) - 1:
            return True

        max_jump = nums[index]

        for step in range(1, max_jump + 1):
            if self.solve(nums, index + step):
                return True

        return False

    def canJump(self, nums):
        return self.solve(nums, 0)
```

---

## 🟡 2. Memoization (Top-Down DP)

```python
class Solution:
    def solve(self, nums, index):
        if index >= len(nums) - 1:
            return True

        if self.dp[index] != -1:
            return self.dp[index]

        max_jump = nums[index]

        for step in range(1, max_jump + 1):
            if self.solve(nums, index + step):
                self.dp[index] = True
                return True

        self.dp[index] = False
        return False

    def canJump(self, nums):
        self.dp = [-1] * len(nums)
        return self.solve(nums, 0)
```

---

## 🟢 3. Tabulation (Bottom-Up DP)

```python
class Solution:
    def canJump(self, nums):
        n = len(nums)
        dp = [False] * n
        dp[n-1] = True

        for i in range(n-2, -1, -1):
            max_jump = nums[i]

            for step in range(1, max_jump + 1):
                if i + step < n and dp[i + step]:
                    dp[i] = True
                    break

        return dp[0]
```

---

## 🔵 4. Space Optimization (Greedy — BEST)

```python
class Solution:
    def canJump(self, nums):
        max_reach = 0

        for i in range(len(nums)):
            if i > max_reach:
                return False

            max_reach = max(max_reach, i + nums[i])

        return True
```

---

# 🎤 Interview Script — Jump Game

---

## 1. Opening

**“Let me restate the problem.”**

We are given:

* An array `nums`
* Each element represents the **maximum jump length**

We start at index `0`

We need to:

> Check if we can reach the last index

---

## 2. Intuition

**“At every index, I can jump multiple steps.”**

👉 From index `i`, I can go to:

```
i + 1, i + 2, ..., i + nums[i]
```

---

## 3. Recursive Idea (Brute Force)

---

### State

```python
f(index)
```

👉 Can I reach the end from this index?

---

## 4. Base Case

```python
if index >= n-1:
    return True
```

👉 Reached or crossed last index

---

## 5. Choices

👉 Try all possible jumps:

```python
for step in range(1, nums[index] + 1)
```

👉 If any path works → return True

---

## 6. Problem with Recursion

👉 Too many repeated states

```
O(2^n) → exponential
```

---

## 7. Memoization

**“Store result of each index.”**

```python
dp[index]
```

👉 Avoid recomputation

---

## 8. Tabulation

**“Build solution from the back.”**

👉 Start from last index

👉 Mark positions that can reach the end

---

## 9. Optimal Insight (Greedy)

**“Instead of checking all paths, track maximum reachable index.”**

---

### Key Idea

```python
max_reach = max(max_reach, i + nums[i])
```

---

### Failure Condition

```python
if i > max_reach:
    return False
```

👉 Means we cannot even reach this position

---

## 10. Dry Run

Example:

```text
nums = [2,3,1,1,4]
```

```
i=0 → max_reach=2
i=1 → max_reach=4
i=2 → ok
i=3 → ok
i=4 → reached
```

👉 Answer = True

---

## 11. Key Insight

**“We don’t need to try all paths — we only need to track how far we can reach.”**

---

## 12. Complexity

### Recursion

```
O(2^n)
```

### DP

```
O(n^2)
```

### Greedy

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
| Greedy     | O(1)  |

---

## 13. How to explain in interview

**“Instead of exploring all jump paths, I track the farthest index I can reach. If at any point my current index exceeds this reach, I cannot proceed.”**

---

## 14. 30-second answer

**“I maintain a max reachable index. If I ever reach a point beyond it, I return false. Otherwise, I update it greedily.”**

---

## 15. 10-second answer

**“Greedy: track max reach, fail if index exceeds it.”**

---

## 16. Closing line

**“The key idea is reducing exponential recursion into a linear greedy solution by tracking reachability.”**

---

