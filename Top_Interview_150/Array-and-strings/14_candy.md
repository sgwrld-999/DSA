# Candy — Full Explanation

---

## Problem Restatement (Simplified)

You are given:

* An integer array **ratings** of size **N**
* Each element `ratings[i]` represents the rating of the `i`-th child
* You must distribute candies to the children subject to the rules below

### Rules

1. Every child must receive **at least one candy**
2. If `ratings[i] > ratings[i−1]`, then
   `candies[i] > candies[i−1]`
3. If `ratings[i] > ratings[i+1]`, then
   `candies[i] > candies[i+1]`

### Task

* Distribute candies so that **all rules are satisfied**
* Minimise the **total number of candies**
* Return the minimum total

---

## Key Observations

---

## 1. This is a **relative constraint problem**, not a local one

The constraints are **comparative**, not absolute.

You are not deciding:

> “How many candies does this child get?”

You are enforcing:

> “This child must get **more than** their neighbour.”

So the problem is about **satisfying inequalities**, not assigning fixed values.

---

## 2. Why naïve single-pass logic fails

Consider:

```
ratings = [1, 2, 3, 4]
```

Correct candies:

```
candies = [1, 2, 3, 4]
```

Each child depends on **how many candies the previous child got**, which depends on **how long the increasing sequence is**.

A single local check like:

```
if rating increases → add 1
```

cannot capture this dependency depth.

---

## 3. The key idea: split constraints into two independent directions

Each child has **two independent constraints**:

1. **Left constraint**

   ```
   If ratings[i] > ratings[i-1]
   ⇒ candies[i] ≥ candies[i-1] + 1
   ```

2. **Right constraint**

   ```
   If ratings[i] > ratings[i+1]
   ⇒ candies[i] ≥ candies[i+1] + 1
   ```

To satisfy both, we must ensure:

```
candies[i] = max(
    candies required by left,
    candies required by right
)
```

This naturally leads to **two passes**.

---

## 4. First Pass — Left to Right

### Goal

Ensure all **left neighbour** constraints are satisfied.

### Strategy

* Start by giving **1 candy to every child**
* Move from left to right
* If the rating increases, increase candy count accordingly

### Rule

```
If ratings[i] > ratings[i−1]:
    candies[i] = candies[i−1] + 1
Else:
    candies[i] = 1
```

### Example

```
ratings:  [1, 2, 3, 2, 1]
candies:  [1, 2, 3, 1, 1]
```

Left constraints are satisfied, but right constraints may still be violated.

---

## 5. Second Pass — Right to Left

### Goal

Ensure all **right neighbour** constraints are satisfied **without breaking left constraints**.

### Strategy

* Traverse from right to left
* If a rating is greater than the right neighbour, enforce the constraint
* Use `max()` to preserve earlier guarantees

### Rule

```
If ratings[i] > ratings[i+1]:
    candies[i] = max(candies[i], candies[i+1] + 1)
```

### Example (continuation)

```
Before: [1, 2, 3, 1, 1]
After:  [1, 2, 3, 2, 1]
```

Now **both left and right constraints are satisfied**.

---

## 6. Why this approach is optimal

* Every child starts with the minimum (1 candy)
* Candies are increased **only when a rule is violated**
* Each increase is **forced**, not arbitrary
* No redundant candies are added

Therefore, the total is **minimal by construction**.

---

## 7. Special Case: `N = 1`

If there is only one child:

* No neighbour constraints exist
* Minimum candies required:

[
\boxed{1}
]

---

## Time and Space Complexity

* **Time:** `O(N)`

  * Two linear passes
* **Space:** `O(N)`

  * Candy array

---

## Intuition Summary

* The problem is about **inequalities**, not values
* Local decisions are insufficient
* Constraints apply from **both directions**
* Solve each direction independently
* Combine using `max()` to preserve all guarantees

---

## Correct Code

```cpp
class Solution {
public:
    int candy(vector<int>& ratings) {
        int n = ratings.size();
        if (n == 1) return 1;

        vector<int> candies(n, 1);

        // Left to right pass
        for (int i = 1; i < n; i++) {
            if (ratings[i] > ratings[i - 1]) {
                candies[i] = candies[i - 1] + 1;
            }
        }

        // Right to left pass
        for (int i = n - 2; i >= 0; i--) {
            if (ratings[i] > ratings[i + 1]) {
                candies[i] = max(candies[i], candies[i + 1] + 1);
            }
        }

        int total = 0;
        for (int c : candies) {
            total += c;
        }

        return total;
    }
};
```

---

