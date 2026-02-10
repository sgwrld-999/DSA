# Insert Interval (LeetCode 57)

## 1. Understanding the Problem (Very Important)

You are given:

* A list of **non-overlapping intervals** `intervals`
* Intervals are **sorted by start time**
* A single interval `newInterval`

Your task is to:

👉 Insert `newInterval` into `intervals`
👉 Merge any **overlapping intervals**
👉 Return the resulting list of intervals, still sorted and non-overlapping

---

### Example

```
intervals = [[1,3],[6,9]]
newInterval = [2,5]
```

Output:

```
[[1,5],[6,9]]
```

---

## 2. Key Observations

* Intervals are already **sorted**
* Existing intervals **do not overlap**
* Only `newInterval` may cause overlaps
* We must preserve sorted order
* We should merge **only when required**

This strongly hints toward a **single-pass linear scan**.

---

## 3. Core Idea of the Algorithm

We process the intervals in **three distinct phases**:

1. Intervals that come **completely before** `newInterval`
2. Intervals that **overlap** with `newInterval`
3. Intervals that come **completely after** `newInterval`

By handling these phases separately, we avoid complex condition checks.

---

## 4. Data Structures Used

### Result List (`ans`)

* Stores the final merged intervals
* Helps maintain order naturally

### State Variable (`newInterval`)

* Acts as a **mutable merged interval**
* Its start and end are updated during overlap

---

## 5. Edge Case Handling (Very Important)

### Case: Empty `intervals`

If there are no existing intervals:

```
intervals = []
newInterval = [a, b]
```

Then the answer is simply:

```
[[a, b]]
```

Handled explicitly to avoid unnecessary logic.

---

## 6. Phase 1: Intervals Completely Before `newInterval`

### Condition

An interval ends **before** `newInterval` starts:

```
intervals[i][1] < newInterval[0]
```

### Why this works

* Since intervals are sorted and non-overlapping
* These intervals **cannot** overlap with `newInterval`
* They can be safely added to the answer

### Action

* Append interval to `ans`
* Move forward

---

## 7. Phase 2: Merging Overlapping Intervals

### Overlap Condition

An interval overlaps if:

```
intervals[i][0] <= newInterval[1]
```

This means:

* The current interval starts **before or at** the end of `newInterval`

---

### Merge Logic

When overlap occurs:

* New start = minimum of both starts
* New end = maximum of both ends

```
newInterval[0] = min(newInterval[0], intervals[i][0])
newInterval[1] = max(newInterval[1], intervals[i][1])
```

This keeps expanding `newInterval` until overlap ends.

---

## 8. Inserting the Merged Interval

Once all overlapping intervals are processed:

* `newInterval` now represents the **fully merged interval**
* It is safe to append it to the result

This step happens **exactly once**.

---

## 9. Phase 3: Intervals Completely After `newInterval`

After merging is complete:

* Remaining intervals start **after** `newInterval` ends
* No more overlap is possible

### Action

* Append remaining intervals directly to `ans`

---

## 10. Final Correct Code (Reference)

```python
class Solution(object):
    def insert(self, intervals, newInterval):
        # edge case: empty intervals
        if not intervals:
            return [newInterval]

        ans = []
        i = 0
        n = len(intervals)

        # 1. Add all intervals that end before newInterval starts
        while i < n and intervals[i][1] < newInterval[0]:
            ans.append(intervals[i])
            i += 1

        # 2. Merge overlapping intervals
        while i < n and intervals[i][0] <= newInterval[1]:
            newInterval[0] = min(newInterval[0], intervals[i][0])
            newInterval[1] = max(newInterval[1], intervals[i][1])
            i += 1

        # Add merged interval
        ans.append(newInterval)

        # 3. Add remaining intervals
        while i < n:
            ans.append(intervals[i])
            i += 1

        return ans
```

---

## 11. Why This Solution Is Correct and Optimal

### Correctness

* Preserves sorted order
* Merges **all and only** overlapping intervals
* Handles edge cases explicitly
* Avoids unnecessary comparisons

### Optimality

* Single pass through `intervals`
* No extra sorting
* No nested loops

---

## 12. Time and Space Complexity

* **Time Complexity:** `O(n)`
* **Space Complexity:** `O(n)` (for result list)

---

## 13. Common Mistakes (Important Learning)

### ❌ Treating it like unsorted merge intervals

Intervals are already sorted — do **not** re-sort.

### ❌ Over-checking overlap conditions

Overlap depends on **end vs start**, not start vs start.

### ❌ Appending `newInterval` multiple times

It must be appended **once**, after merging.

### ❌ Modifying input list directly

Using a separate result list avoids side effects.

---

## 14. Key Takeaway (Must Remember)

> Break the problem into:
> **before**, **overlap**, and **after**
> Handle each phase cleanly
> Merge only when required

This is a **classic interval insertion pattern** and shows up frequently in interviews.

---



