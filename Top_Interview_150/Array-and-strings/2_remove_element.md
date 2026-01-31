# Remove Element (LeetCode 27)

## Problem in one line

Given an array `nums` and an integer `val`, remove **all occurrences** of `val` **in-place** and return the count of remaining elements.

* Order of elements **does not matter**
* Extra space is **not allowed** (except variables)

---

## Key Constraints (Read Carefully)

* Modify `nums` **in-place**
* Only the first `k` elements matter, where `k` is the answer
* Values beyond index `k` are irrelevant

---

# Approach 1: Brute Force (Extra Array)

### Idea

> Create a temporary array containing only elements that are **not equal to `val`**, then copy them back.

---

### Brute Force Code (Python)

```python
class Solution:
    def removeElement(self, nums: list[int], val: int) -> int:
        temp = []

        for x in nums:
            if x != val:
                temp.append(x)

        for i in range(len(temp)):
            nums[i] = temp[i]

        return len(temp)
```

---

### Step-by-step Logic

1. Create an empty temporary list
2. Traverse `nums`
3. Skip elements equal to `val`
4. Store remaining elements in `temp`
5. Copy `temp` back into `nums`
6. Return size of `temp`

---

### Complexity (Brute Force)

* **Time Complexity:** `O(n)`
* **Space Complexity:** `O(n)` (extra array)

---

### Why this is NOT optimal

* Uses extra memory
* Problem explicitly asks for **in-place modification**

---

# Approach 2: Optimal Two-Pointer Solution (Expected)

### Core Idea

> Maintain an index for the **next valid position** and overwrite unwanted values.

This is a **filtering problem**, not a shifting problem.

---

### Optimal Code (Python)

```python
class Solution:
    def removeElement(self, nums: list[int], val: int) -> int:
        index = 0

        for i in range(len(nums)):
            if nums[i] != val:
                nums[index] = nums[i]
                index += 1

        return index
```

---

### Step-by-step Logic

1. Initialize `index = 0`
2. Traverse array using `i`
3. If `nums[i] != val`

   * Copy it to `nums[index]`
   * Increment `index`
4. After traversal, `index` represents the count of valid elements

---

### Why this works

* Overwrites only when needed
* Keeps all valid elements in front
* No extra memory used
* Order preserved (though not required)

---

### Complexity (Optimal)

* **Time Complexity:** `O(n)`
* **Space Complexity:** `O(1)`

---

# Common Mistakes (VERY IMPORTANT)

### Mistake 1: Physically deleting elements

```python
nums.remove(val)  # ❌
```

* Causes shifting
* May skip elements
* Can become `O(n²)`

---

### Mistake 2: Creating a new array and returning it

```python
nums = new_array  # ❌
```

* Does not modify original array in-place
* Violates problem constraints

---

### Mistake 3: Assuming array size must shrink

* Problem only checks first `k` elements
* Values after `k` are ignored

---

### Mistake 4: Using sorting unnecessarily

* Sorting changes relative order
* Adds `O(n log n)` complexity

---

# Interview One-Liner (Memorize)

> “I use a write pointer that tracks the next valid position and overwrite elements not equal to `val`, achieving O(n) time and O(1) space.”

---

# Final Comparison

| Approach    | Time   | Space  | In-place | Interview |
| ----------- | ------ | ------ | -------- | --------- |
| Brute Force | `O(n)` | `O(n)` | ❌        | ❌         |
| Two Pointer | `O(n)` | `O(1)` | ✅        | ✅         |

---

## Final Takeaway

* This is a **filtering problem**
* Use **overwrite, not deletion**
* If asked for in-place → **two pointers**

---

