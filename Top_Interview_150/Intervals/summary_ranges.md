# 📌 Summary Ranges (LeetCode 228)

---

## 1. Understanding the Problem (Very Important)

You are given a **sorted array of unique integers** `nums`.

Your task is to summarize **continuous ranges**:

* Consecutive numbers → `"start->end"`
* Single number → `"num"`

### Example

```
Input: nums = [0,1,2,4,5,7]
Output: ["0->2","4->5","7"]
```

---

## 2. Key Observations

* The array is **sorted**
* Consecutive means:

  ```
  nums[i + 1] == nums[i] + 1
  ```
* We must detect:

  * when a range **continues**
  * when a range **ends**

This naturally suggests a **two-pointer technique**.

---

## 3. Core Idea (Two Pointers)

We use two indices:

```text
lower_bound → start of current range
upper_bound → expanding pointer
```

### Strategy

1. `lower_bound` marks where a range starts
2. `upper_bound` moves forward
3. When the sequence breaks (or array ends):

   * finalize the range
   * move `lower_bound` to the next position

---

## 4. Algorithm in Steps

### Step 1: Handle edge case

```python
if not nums:
    return []
```

---

### Step 2: Initialize pointers and result

```python
ans = []
lower_bound = 0
```

---

### Step 3: Traverse using `upper_bound`

```python
for upper_bound in range(len(nums)):
```

We check **two conditions**:

```python
upper_bound == len(nums) - 1
```

➡ last element (must close the range)

```python
nums[upper_bound + 1] != nums[upper_bound] + 1
```

➡ sequence breaks

---

### Step 4: Finalize the range

* If single number:

  ```python
  "num"
  ```
* If multiple numbers:

  ```python
  "start->end"
  ```

---

## 5. Final Correct Code (Reference)

```python
class Solution(object):
    def summaryRanges(self, nums):
        if not nums:
            return []

        ans = []
        lower_bound = 0

        for upper_bound in range(len(nums)):
            if upper_bound == len(nums) - 1 or nums[upper_bound + 1] != nums[upper_bound] + 1:
                if lower_bound == upper_bound:
                    ans.append(str(nums[lower_bound]))
                else:
                    ans.append(str(nums[lower_bound]) + "->" + str(nums[upper_bound]))
                lower_bound = upper_bound + 1

        return ans
```

---

## 6. Mistakes You Made (Very Important 🚨)

### ❌ Mistake 1: Comparing the same element

```python
abs(nums[upper_bound] - nums[upper_bound]) == 1
```

✔️ Always evaluates to `0`
✔️ Condition never true
✔️ Pointer never moves correctly

✅ Correct comparison:

```python
nums[upper_bound + 1] == nums[upper_bound] + 1
```

---

### ❌ Mistake 2: Using `abs()` unnecessarily

This problem is **sorted + increasing**.

Using `abs()`:

* hides logical intent
* is unnecessary
* can mask bugs

✅ Direct comparison is clearer and safer.

---

### ❌ Mistake 3: Using `.join()` incorrectly

```python
"".join(temp_list)
```

Problems:

* `.join()` returns a **new string**
* result was **not stored**
* list contained **integers**, not strings

```python
[temp_list = [lower_bound, "->", upper_bound]]  # ❌
```

✅ Correct approach:

```python
str(nums[start]) + "->" + str(nums[end])
```

---

### ❌ Mistake 4: Appending indices instead of values

```python
lower_bound, upper_bound  # indices ❌
```

Expected output requires **values**:

```python
nums[lower_bound], nums[upper_bound]  # ✅
```

---

### ❌ Mistake 5: Missing the last range

```python
while upper_bound < len(nums) - 1:
```

This **skips final element / range**.

✅ Fixed by explicitly checking:

```python
upper_bound == len(nums) - 1
```

---

## 7. Dry Run (Must Understand)

### Input

```
nums = [0,1,2,4,5,7]
```

---

### Initial State

```
lower_bound = 0
ans = []
```

---

### Iteration Breakdown

| upper_bound | nums[upper] | Action               |
| ----------- | ----------- | -------------------- |
| 0           | 0           | next is 1 → continue |
| 1           | 1           | next is 2 → continue |
| 2           | 2           | next is 4 → break    |
|             |             | append "0->2"        |
|             |             | lower_bound = 3      |
| 3           | 4           | next is 5 → continue |
| 4           | 5           | next is 7 → break    |
|             |             | append "4->5"        |
|             |             | lower_bound = 5      |
| 5           | 7           | last element         |
|             |             | append "7"           |

---

### Final Output

```
["0->2", "4->5", "7"]
```

---

## 8. Time & Space Complexity

* **Time Complexity:** `O(n)`
* **Space Complexity:** `O(1)` (excluding output)

---

## 9. Key Takeaway (Lock This In 🔒)

> Two-pointer problems fail **not because of logic**,
> but because of:
>
> * wrong comparisons
> * index vs value confusion
> * off-by-one errors

This pattern repeats in:

* Interval problems
* Sliding window
* Array compression tasks

---
