Below are **clean, structured DSA notes** written in the **same manner as your previous notes** (problem → approaches → mistakes → optimal solution → dry run → complexity).
Language: **Python**, concise, revision-oriented, interview-ready.

---

# Container With Most Water

## Problem Statement

You are given an integer array `height` where `height[i]` represents the height of a vertical line at index `i`.
Choose **two lines** such that together with the x-axis they form a container that holds the **maximum amount of water**.

The area is calculated as:

```
area = min(height[left], height[right]) × (right − left)
```

---

## Possible Approaches

### 1. Brute Force

* Try all possible pairs `(i, j)`
* Compute area for each pair
* Return the maximum

❌ Time Complexity: `O(n²)`
❌ Not feasible for large inputs

---

### 2. Prefix / Next Greater Element

❌ **Incorrect approach**

Reason:

* The area depends on both **height and distance**
* Prefix max / NGE focuses only on height
* Taller bars closer together may give less area than shorter bars far apart

This approach is suitable for histogram problems, **not this one**.

---

### 3. Two Pointer (Optimal Approach)

✅ **Correct and optimal**

#### Core Idea

* Start with the **widest container** (leftmost and rightmost lines)
* Area is limited by the **shorter line**
* Width decreases as pointers move inward
* To possibly increase area, we must try to **increase the smaller height**

#### Pointer Rule

* If `height[left] < height[right]` → move `left`
* Else → move `right`

This guarantees that no optimal solution is skipped.

---

## Optimal Python Solution

```python
from typing import List

class Solution:
    def maxArea(self, height: List[int]) -> int:
        max_area = 0
        left, right = 0, len(height) - 1

        while left < right:
            curr_area = min(height[left], height[right]) * (right - left)
            max_area = max(max_area, curr_area)

            if height[left] < height[right]:
                left += 1
            else:
                right -= 1

        return max_area
```

---

## Dry Run

### Input

```python
height = [1,8,6,2,5,4,8,3,7]
```

### Steps

```
left=0, right=8 → min(1,7) * 8 = 8
left=1, right=8 → min(8,7) * 7 = 49 (max)
left=1, right=7 → min(8,3) * 6 = 18
left=1, right=6 → min(8,8) * 5 = 40
...
Final Answer = 49
```

---

## Common Mistakes

* Moving the **larger height pointer**
* Increasing pointers outward (`right += 1`)
* Forgetting to handle equal heights
* Using prefix / NGE logic

---

## Time & Space Complexity

* **Time Complexity:** `O(n)`
* **Space Complexity:** `O(1)`

---

## Key Takeaway (Important)

> **Width always decreases, so only increasing the smaller height can improve the area**

This is the **core invariant** behind the two-pointer solution and a frequent interview discussion point.

---








