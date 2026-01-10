# Trapping Rain Water — Full Explanation

---

## Problem Restatement (Simplified)

You are given:

* An array **H** of size **N**
* Each element **Hᵢ** represents the height of a vertical bar
* The width of each bar is **1**

After raining, water may be trapped **between the bars**.

### Task

Compute the **total amount of water** that can be trapped.

---

### Constraints (Implicit)

* Water cannot escape beyond the leftmost and rightmost bars
* Water accumulates only where it is **bounded on both sides**

---

## Key Observation

Water is **never trapped globally** —
it is trapped **locally above each index**.

So the problem reduces to:

> **For each index `i`, how much water can sit on top of bar `i`?**

---

## 1. When can water be stored at an index?

At index `i`, water can be stored **only if**:

* There exists **at least one bar to the left** of `i`
* There exists **at least one bar to the right** of `i`
* Both are **taller than the water level**

---

### Physical interpretation

* Water rises uniformly
* It spills as soon as it finds a lower escape
* The **shorter boundary** determines the maximum water level

---

## 2. Formal water calculation at index `i`

Let:

* `Lᵢ` = maximum height **to the left of index `i`**
* `Rᵢ` = maximum height **to the right of index `i`**

Then:

[
\text{water}_i = \max\big(0,; \min(L_i, R_i) - H_i \big)
]

---

### Why do we take `min(Lᵢ, Rᵢ)`?

* Water spills over the **lower boundary first**
* The taller boundary is irrelevant beyond that point

This is a **physical constraint**, not a heuristic.

---

## 3. Total trapped water

The final answer is:

[
\boxed{
\sum_{i=0}^{N-1} \max(0,; \min(L_i, R_i) - H_i)
}
]

---

## 4. Brute Force Approach

### Idea

For each index:

1. Scan left to find `Lᵢ`
2. Scan right to find `Rᵢ`
3. Compute water at index `i`

---

### Pseudo Code

```
total_water = 0

for i in [0..N-1]:
    left_max = max(H[0..i-1])
    right_max = max(H[i+1..N-1])

    water = min(left_max, right_max) - H[i]
    if water > 0:
        total_water += water
```

---

### Complexity

* **Time:** `O(N²)`
* **Space:** `O(1)`

---

## 5. Dynamic Programming Optimisation

### Observation

Left and right maximums are recomputed repeatedly.

We can **precompute** them.

---

### Precomputation

**Left maximum array**
[
\text{left_max}[i] = \max(H[0..i-1])
]

**Right maximum array**
[
\text{right_max}[i] = \max(H[i+1..N-1])
]

---

### Water computation

[
\text{water}_i = \max(0,; \min(\text{left_max}[i], \text{right_max}[i]) - H[i])
]

---

### Complexity

* **Time:** `O(N)`
* **Space:** `O(N)`

---

## 6. Two-Pointer Optimisation (Space `O(1)`)

### Key Insight

At any point:

* If `left_max ≤ right_max`

  * Water at `left` is fully determined
* Else

  * Water at `right` is fully determined

This works because:
[
\min(left_max, right_max)
]
is already known on the **smaller side**.

---

### Algorithm Invariant

* Maintain:

  * `left`, `right` pointers
  * `left_max`, `right_max`
* Process **one index at a time**
* Move inward from the **limiting boundary**

---

### Pseudo Code

```
left = 0, right = N-1
left_max = 0, right_max = 0
total_water = 0

while left < right:
    if H[left] <= H[right]:
        left_max = max(left_max, H[left])
        total_water += left_max - H[left]
        left++
    else:
        right_max = max(right_max, H[right])
        total_water += right_max - H[right]
        right--
```

---

### Important Clarification

* Water is **never computed between pointers**
* It is computed **at exactly one index per iteration**

---

### Complexity

* **Time:** `O(N)`
* **Space:** `O(1)`

---

## 7. Monotonic Stack Approach

### Core Idea

* Maintain a **decreasing stack of bar indices**
* A higher bar closes a **valley**
* Water is trapped between:

  * Left boundary
  * Valley bottom
  * Right boundary

---

### What the stack computes

Water per **container segment**, not per index.

[
\text{water} = (\text{min(left, right)} - \text{mid}) \times \text{width}
]

---

### Complexity

* **Time:** `O(N)`
* **Space:** `O(N)`

---

## 8. Comparison of Approaches

| Method       | Computes            | Space  |
| ------------ | ------------------- | ------ |
| Brute Force  | Water per index     | `O(1)` |
| DP           | Water per index     | `O(N)` |
| Two Pointers | Water per index     | `O(1)` |
| Stack        | Water per container | `O(N)` |

---

## Why This Works (Intuition Summary)

* Water is constrained by **boundaries**
* The **shorter boundary dominates**
* Each bar contributes **independently**
* Optimisations remove **redundant scans**
* Two pointers apply DP logic **on the fly**

---

## Correct Code (Two Pointers)

```cpp
class Solution {
public:
    int trap(vector<int>& height) {
        int n = height.size();
        if (n < 3) return 0;

        int left = 0, right = n - 1;
        int left_max = 0, right_max = 0;
        int total_water = 0;

        while (left < right) {
            if (height[left] <= height[right]) {
                left_max = max(left_max, height[left]);
                total_water += left_max - height[left];
                left++;
            } else {
                right_max = max(right_max, height[right]);
                total_water += right_max - height[right];
                right--;
            }
        }

        return total_water;
    }
};
```

---

## Final Takeaway

> **Trapping Rain Water is a local problem governed by global boundaries.**
> Understanding *why the minimum boundary limits water* unlocks every solution.

---

