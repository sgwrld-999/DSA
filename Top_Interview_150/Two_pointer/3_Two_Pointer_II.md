Below are **clean, structured DSA notes**, written in the **same manner as your previous ones** (problem → approach → mistakes → correct solution → dry run → complexity).
Language: **Python**, tone: **professional**, concise, revision-friendly.

---

# Two Sum II – Input Array Is Sorted

## Problem Statement

Given a **1-indexed sorted array** `numbers` and an integer `target`, find **two numbers** such that they add up to `target`.
Return the **indices (1-based)** of the two numbers.

* Exactly one solution exists
* No extra space allowed
* Array is sorted in non-decreasing order

---

## Key Observation

Since the array is **sorted**, we can use the **two-pointer technique** instead of hashing.

---

## Optimal Approach (Two Pointer)

### Idea

* Place one pointer at the **start** (`left`)
* Place one pointer at the **end** (`right`)
* Compare `numbers[left] + numbers[right]` with `target`
* Move pointers **inward** based on comparison

---

## Common Mistakes (From Your Code)

### ❌ Wrong loop condition

```python
while right < n:
```

Correct condition:

```python
while left < right:
```

---

### ❌ Incorrect pointer movement

```python
if sum < target:
    right -= 1
elif sum > target:
    left += 1
```

This is **reversed**.

Correct logic:

* If sum is smaller → move `left`
* If sum is larger → move `right`

---

### ❌ Unconditional pointer increment

```python
right += 1
```

This **breaks the two-pointer invariant** and may cause:

* Infinite loop
* Index out of bounds
* Skipped solution

---

## Correct Python Solution

```python
from typing import List

class Solution:
    def twoSum(self, numbers: List[int], target: int) -> List[int]:
        left, right = 0, len(numbers) - 1

        while left < right:
            curr_sum = numbers[left] + numbers[right]

            if curr_sum == target:
                return [left + 1, right + 1]  # 1-based indexing
            elif curr_sum < target:
                left += 1
            else:
                right -= 1

        return []
```

---

## Dry Run

### Input

```python
numbers = [2, 7, 11, 15]
target = 9
```

### Steps

```
left = 0 (2), right = 3 (15) → sum = 17 > 9 → right--
left = 0 (2), right = 1 (7)  → sum = 9  → return [1, 2]
```

---

## Time & Space Complexity

* **Time Complexity:** `O(n)`
* **Space Complexity:** `O(1)` (constant extra space)

---

## Key Takeaways

* Two Sum II **always uses two pointers**
* Pointers must move **inward**
* Loop condition is **left < right**
* Return **1-based indices**
* Never move both pointers blindly

---







