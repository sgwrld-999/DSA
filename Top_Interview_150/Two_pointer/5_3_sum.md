# 3Sum

## Problem Statement

Given an integer array `nums`, return **all unique triplets** `[nums[i], nums[j], nums[k]]` such that:

```
nums[i] + nums[j] + nums[k] == 0
```

* Triplets must be **unique**
* Order of triplets does not matter
* `i ≠ j ≠ k`

---

## Key Observations

* Brute force with 3 loops → `O(n³)` (too slow)
* Sorting enables **two-pointer technique**
* Duplicate handling is **critical**

---

## Optimal Approach (Sorting + Two Pointer)

### High-Level Idea

1. **Sort** the array
2. Fix one element `nums[i]`
3. Use two pointers `j` and `k` to find pairs such that:

   ```
   nums[i] + nums[j] + nums[k] == 0
   ```
4. Skip duplicates at **all levels**

---

## Algorithm Steps

1. Sort the array
2. Iterate `i` from `0` to `n-3`
3. Skip duplicate values for `i`
4. Set:

   * `j = i + 1`
   * `k = n - 1`
5. While `j < k`:

   * Compute sum `s`
   * If `s < 0` → move `j`
   * If `s > 0` → move `k`
   * If `s == 0`:

     * Store the triplet
     * Move both pointers
     * Skip duplicate values for `j` and `k`

---

## Python Implementation

```python
from typing import List

class Solution:
    def threeSum(self, nums: List[int]) -> List[List[int]]:
        ans = []
        nums.sort()
        n = len(nums)

        for i in range(n - 2):
            if i > 0 and nums[i] == nums[i - 1]:
                continue

            j, k = i + 1, n - 1

            while j < k:
                s = nums[i] + nums[j] + nums[k]

                if s < 0:
                    j += 1
                elif s > 0:
                    k -= 1
                else:
                    ans.append([nums[i], nums[j], nums[k]])
                    j += 1
                    k -= 1

                    while j < k and nums[j] == nums[j - 1]:
                        j += 1
                    while j < k and nums[k] == nums[k + 1]:
                        k -= 1

        return ans
```

---

## Duplicate Handling (Very Important)

### Why duplicates occur

* Same value of `nums[i]`
* Same value of `nums[j]`
* Same value of `nums[k]`

### How duplicates are avoided

* Skip duplicate `i`
* After finding a valid triplet:

  * Skip repeated `j`
  * Skip repeated `k`

---

## Dry Run

### Input

```python
nums = [-1, 0, 1, 2, -1, -4]
```

### After Sorting

```
[-4, -1, -1, 0, 1, 2]
```

### Valid Triplets

```
[-1, -1, 2]
[-1, 0, 1]
```

---

## Time & Space Complexity

* **Time Complexity:** `O(n²)`
* **Space Complexity:** `O(1)` (excluding output list)

---

## Common Mistakes

* Forgetting to sort
* Not skipping duplicates
* Using extra hash sets unnecessarily
* Returning duplicate triplets

---

## Key Takeaways

* 3Sum is an extension of **Two Sum with sorting**
* Sorting + two pointers reduces complexity
* Duplicate handling defines correctness
* Pattern appears in **4Sum, kSum**

---

