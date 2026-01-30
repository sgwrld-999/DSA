longestConsecutive# Contains Duplicate II (HashMap)

## Problem in one line

Given an integer array `nums` and an integer `k`, determine whether there exist **two equal values** such that the **absolute difference of their indices is at most `k`**.

---

## Core idea

> We don’t care how many times a value appears —
> we care **how far apart the duplicates are**.

This is an **index-distance tracking problem**, not a frequency problem.

---

## Why HashMap is used

A HashMap allows us to:

* Store the **last index** where a value was seen
* Check index distance in **O(1)** time

Mapping:

```
value → last index
```

---

## High-level algorithm

1. Create an empty HashMap `last_index`
2. Traverse the array using index `i`
3. For each value:

   * If it exists in the map and
     `i − last_index[value] ≤ k` → return `True`
   * Update the value’s last index
4. If no valid pair is found, return `False`

---

## Correct reference implementation

```python
class Solution:
    def containsNearbyDuplicate(self, nums: List[int], k: int) -> bool:
        last_index = {}

        for i, val in enumerate(nums):
            if val in last_index and i - last_index[val] <= k:
                return True
            last_index[val] = i

        return False
```

---

## Why this solution is correct

* Always compares **nearest duplicates**
* Keeps only the most recent index
* Early exits as soon as a valid pair is found
* No unnecessary comparisons

---

## Time and space complexity

* **Time Complexity:** `O(n)`
* **Space Complexity:** `O(n)`

---

## Common mistakes to avoid

* Using `abs()` unnecessarily
* Using a HashSet (loses index information)
* Checking all pairs (`O(n²)`)
* Forgetting to update the index after checking

---

## Alternative approach (sliding window)

* Use a HashSet of size `k + 1`
* Remove elements when window moves
* Also `O(n)` time

But **HashMap with index tracking is clearer** in interviews.

---

## Interview takeaway

> When a problem asks **“how close”**, think **indices**, not counts.

If you see:

* distance constraints
* recent occurrence
* nearest duplicate

→ use **HashMap (value → index)**.

---
