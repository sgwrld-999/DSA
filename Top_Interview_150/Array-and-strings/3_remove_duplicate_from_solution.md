# Remove Duplicates from Sorted Array (LeetCode 26)

## Problem in one line

Given a **sorted array** `nums`, remove duplicates **in-place** such that each element appears **only once** and return the number of unique elements.

* Must modify `nums` in-place
* Extra space is **not allowed**
* Order of elements must be preserved

---

## Key Observation (MOST IMPORTANT)

> The array is already **sorted**.

That means:

* All duplicates are **adjacent**
* No HashSet is required
* Comparison with the **previous element** is enough

---

# ❌ What You Tried (Your Code)

```python
seen = set()
idx = 0 
for i in range(1, len(nums)):
    if nums[i-1] == nums[i]:
        nums[idx] = nums[i]
        idx += 1
return idx
```

---

# ❌ All Mistakes in Your Code (Very Important)

### Mistake 1: Using `set` (even conceptually)

```python
seen = set()
```

* ❌ Extra space not allowed
* ❌ Breaks the idea of sorted-array optimization
* ❌ Not needed at all

> If the array is sorted, **HashSet is a red flag**.

---

### Mistake 2: Wrong condition (`==` instead of `!=`)

```python
if nums[i-1] == nums[i]:
```

You are detecting **duplicates**, but you should be **keeping unique elements**.

Correct logic:

```python
if nums[i] != nums[i-1]
```

---

### Mistake 3: Wrong meaning of `idx`

You used `idx` as:

* A position to store duplicates ❌

But `idx` should represent:

> The index where the **next unique element** should be placed

---

### Mistake 4: `idx` initialized incorrectly

```python
idx = 0
```

The **first element is always unique**, so:

```python
idx = 1
```

---

### Mistake 5: Loop logic does not preserve uniqueness

Your code:

* Writes duplicates into the array
* Never correctly builds the unique prefix
* Returns the wrong count

---

# ✅ Correct Thought Process

Because the array is sorted:

* First element is always unique
* Compare each element with the **last unique element**
* If different → keep it

This is a **two-pointer overwrite pattern**.

---

# ✅ Correct Code (Optimal & Interview-Ready)

```python
from typing import List

class Solution:
    def removeDuplicates(self, nums: List[int]) -> int:
        if not nums:
            return 0

        idx = 1  # index for next unique element

        for i in range(1, len(nums)):
            if nums[i] != nums[i - 1]:
                nums[idx] = nums[i]
                idx += 1

        return idx
```

---

# Step-by-step Logic

1. Start `idx = 1` (first element already unique)
2. Traverse from index `1`
3. Compare `nums[i]` with `nums[i-1]`
4. If different:

   * Copy to `nums[idx]`
   * Increment `idx`
5. Return `idx` as count of unique elements

---

# Example Dry Run

Input:

```
nums = [1, 1, 2, 2, 3]
```

| i | nums[i] | Action      | nums        | idx |
| - | ------- | ----------- | ----------- | --- |
| 1 | 1       | same → skip | [1,1,2,2,3] | 1   |
| 2 | 2       | copy        | [1,2,2,2,3] | 2   |
| 3 | 2       | skip        | [1,2,2,2,3] | 2   |
| 4 | 3       | copy        | [1,2,3,2,3] | 3   |

Return `3`.

---

# Complexity

* **Time Complexity:** `O(n)`
* **Space Complexity:** `O(1)`

---

# Interview One-Liner (Memorize This)

> “Since the array is sorted, duplicates are adjacent. I use a write pointer to overwrite duplicates and keep only unique elements in-place.”

---

# Pattern Recognition (Very Important)

This problem uses the **same pattern** as:

* Remove Element
* Move Zeroes
* Deduplicate Sorted Array

➡️ **Overwrite + write pointer**

---
