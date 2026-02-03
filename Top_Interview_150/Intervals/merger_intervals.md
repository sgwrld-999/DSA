# 📌 Merge Intervals (LeetCode 56)

---

## 1. Understanding the Problem (Very Important)

You are given a list of intervals where:

```text
interval = [start, end]
```

Your task is to **merge all overlapping intervals** and return the resulting list.

---

### Example

```
Input:  [[1,3],[2,6],[8,10],[15,18]]
Output: [[1,6],[8,10],[15,18]]
```

---

## 2. Key Observations

* Intervals can overlap **only after sorting**

* Overlap condition:

  ```
  next_start <= current_end
  ```

* If overlapping → merge

* If not → finalize the previous interval

This problem requires a **greedy + state-carry approach**, not pairwise comparison.

---

## 3. Core Idea (Greedy + Carry Forward)

### Why sorting is mandatory

Sorting by start time ensures:

* Overlaps appear **adjacent**
* We only compare **current interval** with **next interval**

---

### What we track

```text
curr_start → start of current merged interval
curr_end   → end of current merged interval
```

---

## 4. Algorithm in Steps

### Step 1: Handle edge case

```python
if not intervals:
    return []
```

---

### Step 2: Sort intervals

```python
intervals.sort()
```

---

### Step 3: Initialize current interval

```python
curr_start, curr_end = intervals[0]
```

---

### Step 4: Traverse remaining intervals

For each `(start, end)`:

* **If overlapping**:

  ```
  start <= curr_end
  ```

  → extend current interval

* **If not overlapping**:
  → save current interval
  → start a new one

---

### Step 5: Append the last interval

This step is **mandatory** and often forgotten.

---

## 5. Final Correct Code (Reference)

```python
class Solution(object):
    def merge(self, intervals):
        if not intervals:
            return []

        intervals.sort()
        ans = []

        curr_start, curr_end = intervals[0]

        for i in range(1, len(intervals)):
            start, end = intervals[i]

            if start <= curr_end:
                curr_end = max(curr_end, end)
            else:
                ans.append([curr_start, curr_end])
                curr_start, curr_end = start, end

        ans.append([curr_start, curr_end])
        return ans
```

---

## 6. Mistakes You Made (Very Important 🚨)

### ❌ Mistake 1: Wrong variable naming

```python
def merge(self, nums):
"""
:type intervals: List[List[int]]
"""
```

* Variable name and docstring mismatch
* Causes confusion while reasoning

---

### ❌ Mistake 2: Pairwise merging approach

```python
if nums[i][1] < nums[i+1][0]:
```

This checks **only two intervals**, but:

* Merging requires **carrying forward a merged interval**
* You must compare with a **current merged range**, not raw array values

---

### ❌ Mistake 3: Incorrect overlap condition

```python
nums[i][1] > nums[i+1][0]
```

Fails for edge case:

```
[1,4] and [4,5]  → should merge
```

Correct condition:

```python
start <= curr_end
```

---

### ❌ Mistake 4: Syntax error in temp interval

```python
temp = [nums[i][0]], nums[i][1]]
```

Problems:

* Extra closing bracket
* Incorrect list structure

---

### ❌ Mistake 5: Merge logic incomplete

```python
temp = [nums[i][0], nums[i][1]]
```

This **ignores the next interval entirely**.

Correct merge requires:

```python
end = max(curr_end, next_end)
```

---

### ❌ Mistake 6: Last interval never added

Your loop logic never appends the **final merged interval**.

This is a classic interval-problem bug.

---

## 7. Dry Run (Must Understand)

### Input

```python
intervals = [[1,3],[2,6],[8,10],[15,18]]
```

---

### After Sorting

```python
[[1,3],[2,6],[8,10],[15,18]]
```

---

### Execution Trace

| Interval | Action                                   |
| -------- | ---------------------------------------- |
| [1,3]    | initialize curr = [1,3]                  |
| [2,6]    | overlap → curr = [1,6]                   |
| [8,10]   | no overlap → save [1,6], curr = [8,10]   |
| [15,18]  | no overlap → save [8,10], curr = [15,18] |
| end      | append [15,18]                           |

---

### Final Output

```python
[[1,6],[8,10],[15,18]]
```

---

## 8. Time & Space Complexity

* **Time Complexity:** `O(n log n)`
  (due to sorting)

* **Space Complexity:** `O(n)`
  (output list)

---

## 9. Key Takeaways (Lock This In 🔒)

> Merge Intervals is **not** an index problem
> It is a **state-carry greedy problem**

Always remember:

* Sort first
* Track a current interval
* Extend or finalize
* Append the last interval

This exact pattern repeats in:

* Insert Interval
* Meeting Rooms
* Interval Scheduling
* Range Compression problems

---
