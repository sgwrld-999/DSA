# ✅ Python Code

```python
class Solution:
    def solve(self, nums, index):
        
        if index >= len(nums):
            return 0

        # skip
        skip = self.solve(nums, index + 1)

        # take
        take = nums[index] + self.solve(nums, index + 2)

        return max(skip, take)

    def rob(self, nums):
        return self.solve(nums, 0)
```

---

# 🎤 Interview Script — House Robber

---

## 1. Opening

**“Let me restate the problem.”**

We are given:

* An array `nums`
* Each element represents money in a house

We need to:

> Rob houses such that no two adjacent houses are robbed, and maximize the total money.

👉 Important:

* Cannot rob adjacent houses

---

## 2. Intuition

**“At every house, I have two choices: rob or skip.”**

👉 For each house:

* Either I rob it
* Or I skip it

This creates a **decision tree (recursion)**

---

## 3. Recursive Idea

**“Let me first explain the brute force recursion.”**

---

### State

```python
f(index)
```

👉 Meaning:

> Maximum money I can rob starting from `index`

---

## 4. Base Case

```python
if index >= len(nums):
```

👉 No houses left

→ Return 0

---

## 5. Choices (Core Logic)

---

### ❌ Skip

```python
move to next house
```

```python
f(index + 1)
```

---

### ✅ Take

👉 If I rob this house:

* I **add its value**
* I **skip next house**

```python
nums[index] + f(index + 2)
```

---

## 6. Final Decision

```python
max(skip, take)
```

👉 Choose the better option

---

## 7. Dry Run

Example:

```text
nums = [2, 7, 9, 3, 1]
```

👉 Choices:

* Rob 2 → skip 7 → rob 9 → skip 3 → rob 1 → total = 12
* Skip 2 → rob 7 → skip 9 → rob 3 → total = 10

👉 Answer = **12**

---

## 8. Key Insight

**“We don’t need to track previous house explicitly.”**

👉 Why?

* If we rob → jump to `index + 2`
* If we skip → go to `index + 1`

So state only depends on `index`

---

## 9. Optimization (DP / Memoization)

```python
class Solution:
    def solve(self, nums, index):
        
        if index >= len(nums):
            return 0

        if index in self.dp:
            return self.dp[index]

        skip = self.solve(nums, index + 1)
        take = nums[index] + self.solve(nums, index + 2)

        self.dp[index] = max(skip, take)
        return self.dp[index]

    def rob(self, nums):
        self.dp = {}
        return self.solve(nums, 0)
```

---

## 10. Complexity

### Time Complexity

👉 Without DP:

```
O(2^n)
```

👉 With DP:

```
O(n)
```

---

### Space Complexity

* Recursion stack → O(n)
* DP → O(n)

---

## 11. How to explain in interview

**“At each house, I decide whether to rob or skip. If I rob, I skip the next house and move to index + 2. If I skip, I move to index + 1. I take the maximum of both choices.”**

---

## 12. 30-second answer

**“This is a recursion + DP problem where at each index I either rob and jump two steps or skip and move one step. I take the maximum and use memoization to optimize.”**

---

## 13. 10-second answer

**“At each house: rob (i+2) or skip (i+1), take max, use DP.”**

---

## 14. Closing line

**“The key idea is making a choice at every house and avoiding adjacent robbery by jumping two steps.”**

---
