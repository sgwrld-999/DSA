# Minimum Size Subarray Sum

## Problem Statement

Given an array of **positive integers** `nums` and an integer `target`, return the **minimum length of a contiguous subarray** whose sum is **greater than or equal to `target`**.

If there is no such subarray, return `0`.

---

## Key Observations

* Subarray must be **contiguous**
* All numbers are **positive**
* Brute force will time out
* Positive numbers ⇒ **sliding window** works perfectly
* Goal is to **minimize window size**, not maximize sum

---

## Possible Approaches

### 1. Brute Force

* Try all subarrays
* Compute sum for each
* Track minimum length

Time Complexity: `O(n²)`
Too slow for large `n`

---

### 2. Prefix Sum + Binary Search

* Build prefix sum array
* For each index, binary search for valid subarray

 Time Complexity: `O(n log n)`
 More complex than needed

---

### 3. Sliding Window (Optimal Approach)

 **Best and simplest**

#### Why Sliding Window Works

* All elements are **positive**
* Expanding window increases sum
* Shrinking window decreases sum
* Once sum ≥ target, try to **shrink to minimum**

---

## Optimal Approach (Sliding Window)

### Core Idea

1. Expand window by moving `right`
2. Add `nums[right]` to sum
3. While sum ≥ target:

   * Update answer
   * Shrink window from `left`
4. Repeat until end

---

## Python Implementation

```python
from typing import List

class Solution:
    def minSubArrayLen(self, target: int, nums: List[int]) -> int:
        left = 0
        total = 0
        ans = float('inf')

        for right in range(len(nums)):
            total += nums[right]

            while total >= target:
                ans = min(ans, right - left + 1)
                total -= nums[left]
                left += 1

        return 0 if ans == float('inf') else ans
```

---

## Dry Run

### Input

```python
target = 7
nums = [2,3,1,2,4,3]
```

### Execution

```
right=0 → sum=2
right=1 → sum=5
right=2 → sum=6
right=3 → sum=8 ≥ 7 → length=4
shrink → sum=6
right=4 → sum=10 ≥ 7 → length=3
shrink → sum=7 ≥ 7 → length=2
shrink → sum=4
right=5 → sum=7 ≥ 7 → length=2
```

### Output

```
2
```

---

## Common Mistakes

* Checking `sum == target` instead of `sum >= target`
* Initializing answer as `0` instead of infinity
* Shrinking window **before** adding `nums[right]`
* Forgetting to return `0` when no valid subarray exists
* Trying prefix/NGE logic (not suitable)

---

## Time & Space Complexity

* **Time Complexity:** `O(n)`
* **Space Complexity:** `O(1)`

---

## Key Takeaways

* This is a **minimum window** problem
* Always:

  * expand first
  * shrink while valid
* Condition is **≥ target**, not equality
* Pattern repeats in:

  * Longest subarray
  * Minimum window substring
  * Variable-size sliding window problems


---
