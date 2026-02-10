
# Minimum Number of Arrows to Burst Balloons

## 1. Understanding the Problem (Very Important)

You are given a list of balloons, where each balloon is represented as an **interval**:

```
[x_start, x_end]
```

Meaning:

* The balloon spans horizontally from `x_start` to `x_end`
* You can shoot an arrow **vertically at any x-coordinate**
* One arrow bursts **all balloons whose intervals include that x**

### Goal

👉 Find the **minimum number of arrows** required to burst **all balloons**.

---

## 2. Key Observations

* Vertical position does **not matter**
* Only **horizontal overlap** matters
* If multiple balloons overlap at some x-coordinate, **one arrow is enough**
* If they **don’t overlap**, you must use a **new arrow**
* This is an **interval overlap** problem, not geometry

This immediately hints at a **greedy interval strategy**.

---

## 3. Core Pattern Recognition

This problem is a variant of:

> **“Minimum resources to cover overlapping intervals”**

Key insight:

* One arrow = one **overlapping interval group**
* We want to **maximize overlap per arrow**
* That means shooting the arrow at the **tightest possible x**

Which translates to:

> **Track the minimum end of overlapping intervals**

---

## 4. Why Sorting Is Mandatory

Without sorting:

* You can’t reason about overlap order
* You might falsely group non-overlapping balloons

After sorting:

```text
[1,6], [2,8], [7,12], [10,16]
```

You can clearly see:

* `[1,6]` and `[2,8]` overlap
* But `[7,12]` does NOT overlap with the overlap window ending at `6`

---

## 5. Correct Greedy Strategy

### Mental Model

1. Sort balloons by start coordinate
2. Start with **one arrow**
3. Maintain `min_end`:

   * the **smallest ending x** among all overlapping balloons
4. For each new balloon:

   * If it overlaps (`start <= min_end`)

     * Shrink overlap window → `min_end = min(min_end, end)`
   * Else:

     * Overlap broken → need a **new arrow**
     * Reset `min_end`

---

## 6. Why “Minimum End” Is Crucial (Your Key Insight)

Example:

```text
[1,6], [2,8], [7,12]
```

Mistake if careless:

* You may think all three overlap

Reality:

* Overlap window after first two = `[2,6]`
* `7` is **outside** that window

That’s why:

> **The arrow must be shot at the minimum end of the overlap**

This is the heart of the solution.

---

## 7. Common Logical Mistakes (Important Learning)

### ❌ Mistake 1: Tracking current end instead of minimum end

```python
cur_end = points[i][1]   # wrong mental model
```

Why wrong:

* Loses the tightest overlap window
* Allows invalid overlaps

---

### ❌ Mistake 2: Incrementing arrows too late

Waiting until all intervals are processed breaks greediness.

Correct:

* Increment **exactly when overlap breaks**

---

### ❌ Mistake 3: Initializing `min_end` incorrectly

```python
min_end = -inf   # wrong
```

Correct:

```python
min_end = points[0][1]
```

---

## 8. Final Correct Code (Greedy Interval Solution)

```python
class Solution(object):
    def findMinArrowShots(self, points):
        """
        :type points: List[List[int]]
        :rtype: int
        """
        if not points:
            return 0

        points.sort()
        min_end = points[0][1]
        min_arows = 1

        for i in range(len(points)):
            if points[i][0] <= min_end:
                # still overlapping → tighten window
                min_end = min(min_end, points[i][1])
            else:
                # overlap breaks → need new arrow
                min_arows += 1
                min_end = points[i][1]

        return min_arows
```

---

## 9. Dry Run (Must Be Clear in Your Head)

### Input

```python
points = [[10,16],[2,8],[1,6],[7,12]]
```

### After Sorting

```text
[1,6], [2,8], [7,12], [10,16]
```

### Execution

* Start → `arrows = 1`, `min_end = 6`
* `[2,8]` overlaps → `min_end = 6`
* `[7,12]` does NOT overlap → arrows = 2, `min_end = 12`
* `[10,16]` overlaps → `min_end = 12`

Final Answer → **2**

---

## 10. Time and Space Complexity

* **Time Complexity:** `O(n log n)` (sorting)
* **Space Complexity:** `O(1)` (in-place greedy)

---

## 11. Pattern Mapping (Very Important for Interviews)

This problem belongs to the family of:

* Interval scheduling
* Minimum resources allocation
* Greedy overlap compression

Same thinking applies to:

* Meeting Rooms
* Non-overlapping intervals
* Burst balloons
* Minimum platforms

---

## 12. Final Takeaway (Memorize This)

> Sort intervals
> Track minimum end
> Overlap → shrink
> Break → count + reset


