# ✅ Python Code (Recursion Only)

```python
class Solution:
    def solve(self, nums, index, end):
        # base case
        if index > end:
            return 0

        # take
        take = nums[index] + self.solve(nums, index + 2, end)

        # skip
        skip = self.solve(nums, index + 1, end)

        return max(take, skip)

    def rob(self, nums):
        n = len(nums)

        if n == 1:
            return nums[0]

        # Case 1: include first, exclude last
        case1 = self.solve(nums, 0, n - 2)

        # Case 2: exclude first, include last
        case2 = self.solve(nums, 1, n - 1)

        return max(case1, case2)
```

---

# ✅ Python Code

```python
class Solution:
    def rob_linear(self, nums):
        prev2 = 0   # dp[i-2]
        prev1 = 0   # dp[i-1]

        for money in nums:
            take = money + prev2
            skip = prev1
            curr = max(take, skip)

            prev2 = prev1
            prev1 = curr

        return prev1

    def rob(self, nums):
        n = len(nums)

        if n == 1:
            return nums[0]

        # Case 1: exclude last house
        case1 = self.rob_linear(nums[:-1])

        # Case 2: exclude first house
        case2 = self.rob_linear(nums[1:])

        return max(case1, case2)
```

---

# 🎤 Interview Script — House Robber II

---

## 1. Opening

**“Let me restate the problem.”**

We are given:

* An array `nums`
* Each element represents money in a house

We need to:

> Rob houses such that no two adjacent houses are robbed, and maximize total money.

👉 **New constraint:**

* Houses are arranged in a **circular manner**

---

## 2. Key Observation

**“The first and last houses are adjacent.”**

👉 So:

* If I rob the **first house**, I **cannot rob the last**
* If I rob the **last house**, I **cannot rob the first**

---

## 3. Intuition

**“Because of circular dependency, I break it into two linear problems.”**

---

### Case 1:

👉 Include first house → exclude last

```python
nums[0...n-2]
```

---

### Case 2:

👉 Exclude first house → include last possible

```python
nums[1...n-1]
```

---

## 4. Reduce to House Robber I

**“Now both cases are simple linear House Robber problems.”**

👉 Solve both and take max

```python
max(case1, case2)
```

---

## 5. Linear Robbery Logic

**“At each house, I have two choices: rob or skip.”**

---

### State

```python
f(i)
```

👉 Maximum money from index `i`

---

### Transition

```python
take = nums[i] + f(i-2)
skip = f(i-1)
```

---

## 6. Space Optimization

Instead of DP array:

👉 Use two variables:

```python
prev2 = dp[i-2]
prev1 = dp[i-1]
```

---

### Update Rule

```python
curr = max(prev1, prev2 + nums[i])
```

---

## 7. Dry Run

Example:

```text
nums = [2, 3, 2]
```

---

### Case 1: [2, 3]

👉 Max = 3

---

### Case 2: [3, 2]

👉 Max = 3

---

👉 Final Answer:

```text
max(3, 3) = 3
```

---

## 8. Edge Case

```python
if len(nums) == 1:
```

👉 Only one house → return it

---

## 9. Key Insight

**“We cannot take both first and last house, so we split into two independent linear problems.”**

---

## 10. Complexity

### Time Complexity

```text
O(n)
```

(We solve 2 linear problems)

---

### Space Complexity

```text
O(1)
```

(Using only variables)

---

## 11. How to explain in interview

**“Since houses are in a circle, the first and last are adjacent. So I solve two cases: excluding the last house and excluding the first house. Each becomes a linear House Robber problem, which I solve using DP with two variables.”**

---

## 12. 30-second answer

**“Break circular into two linear cases: [0..n-2] and [1..n-1], solve both using House Robber I, return max.”**

---

## 13. 10-second answer

**“Circular → split into two linear robberies, take max.”**

---

## 14. Closing line

**“The key idea is reducing the circular problem into two linear subproblems and applying the standard robbery DP.”**

---

