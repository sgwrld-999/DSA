# Longest Consecutive Sequence

## Problem in one line

Given an unsorted array of integers, find the **length of the longest sequence of consecutive numbers**.

---

## Approach 1: Sorting-Based Solution

### Code (given)

```python
class Solution:
    def longestConsecutive(self, nums: List[int]) -> int:
        if not nums:
            return 0

        nums.sort()
        ctr = 1
        ans = 1

        for i in range(1, len(nums)):
            if nums[i] == nums[i-1] + 1:
                ctr += 1
            elif nums[i] != nums[i-1]:
                ans = max(ans, ctr)
                ctr = 1

        return max(ans, ctr)
```

---

## Logic (Sorting Approach)

### Key idea

> After sorting, **consecutive numbers appear next to each other**.

So the problem becomes:

* Count consecutive runs
* Reset when the sequence breaks
* Ignore duplicates

---

### Step-by-step logic

1. **Handle empty input**

   * No numbers → no sequence

2. **Sort the array**

   * Makes consecutive numbers adjacent

3. **Initialize counters**

   * `ctr` → current consecutive length
   * `ans` → maximum length found

4. **Traverse from index 1**

   * Compare current element with previous

5. **If consecutive**

   * Increase `ctr`

6. **If duplicate**

   * Ignore (do nothing)

7. **If sequence breaks**

   * Update `ans`
   * Reset `ctr`

8. **Final max**

   * Ensures last sequence is counted

---

## Complexity (Sorting Approach)

* **Time Complexity:** `O(n log n)`
* **Space Complexity:** `O(1)` (ignoring sort internals)

---

## Interview note

✔ Correct solution
❌ Not optimal

Interviewers usually expect an **O(n)** solution using HashSet.

---

---

# Approach 2: HashSet-Based Optimal Solution (Expected in Interviews)

### Code (Optimal)

```python
class Solution:
    def longestConsecutive(self, nums: List[int]) -> int:
        num_set = set(nums)
        longest = 0

        for num in num_set:
            if num - 1 not in num_set:
                curr = num
                length = 1

                while curr + 1 in num_set:
                    curr += 1
                    length += 1

                longest = max(longest, length)

        return longest
```

---

## Logic (HashSet Approach)

### Core idea

> Start counting **only from the beginning of a sequence**.

A number is a **sequence start** if:

```
num - 1 is NOT present
```

This avoids recounting sequences multiple times.

---

### Step-by-step logic

1. **Insert all numbers into a HashSet**

   * Enables `O(1)` lookups

2. **Iterate through the set**

   * Each number is checked once

3. **Check for sequence start**

   * If `num - 1` does not exist

4. **Expand forward**

   * Keep checking `num + 1`, `num + 2`, ...

5. **Update maximum length**

---

## Why this solution is optimal

* Each number is visited **at most twice**
* No sorting required
* No redundant sequence checks
* Works efficiently for large inputs

---

## Complexity (HashSet Approach)

* **Time Complexity:** `O(n)`
* **Space Complexity:** `O(n)`

---

## Comparison Summary

| Aspect                | Sorting Approach | HashSet Approach |
| --------------------- | ---------------- | ---------------- |
| Time                  | `O(n log n)`     | `O(n)`           |
| Space                 | `O(1)`           | `O(n)`           |
| Simplicity            | Easy             | Moderate         |
| Interview Expectation | Acceptable       | Preferred        |

---

## Common mistakes to avoid

* Resetting count on duplicates
* Counting sequences from every number
* Using nested loops unnecessarily
* Forgetting edge case of empty array

---

## Final Interview Takeaway

> **Sorting makes it easy to see.
> HashSet makes it optimal.**

Always mention:

* Sorting solution first (baseline)
* Then improve to HashSet (optimal)

That shows **problem-solving maturity**.

---
