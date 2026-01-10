# Problem: Maximum Score of a Split (LeetCode 3788)

You are given an integer array `nums` of length `n`.

You must choose an index `i` such that:

```
0 ≤ i < n − 1
```

For a chosen split index `i`:

* `prefixSum(i)` = sum of elements from `nums[0]` to `nums[i]`
* `suffixMin(i)` = minimum value among `nums[i+1]` to `nums[n-1]`

The **score** of a split is:

```
score(i) = prefixSum(i) − suffixMin(i)
```

Your task is to return the **maximum possible score**.

---

## Key Observations

1. The split **must leave at least one element on the right**

    * That's why `i < n - 1`

2. For every index `i`, we need:

    * Sum of elements on the **left**
    * Minimum element on the **right**

3. A brute-force approach would be:

    * For each `i`, recompute sums and minimums
    * Time complexity: **O(n²)** (too slow)

4. This is a classic **prefix + suffix preprocessing problem**

---

## Core Idea (Prefix–Suffix Pattern)

* Build a **suffix minimum array**
* Maintain a **running prefix sum**
* Evaluate the score at each valid split

This reduces time complexity to **O(n)**.

---

## Approach

### Step 1: Build `suffixMin[]`

Define:

```
suffixMin[i] = min(nums[i], nums[i+1], ..., nums[n-1])
```

We compute this **from right to left**.

---

### Step 2: Iterate splits and compute scores

* Maintain a running `prefixSum`
* For each valid split index `i`:

  ```
  score = prefixSum − suffixMin[i + 1]
  ```
* Track the maximum score

---

## Correct Code (Final)

```cpp
class Solution {
public:
     long long maximumScore(vector<int>& nums) {
          int n = nums.size();

          // suffixMin[i] = min(nums[i...n-1])
          vector<int> suffixMin(n);
          suffixMin[n - 1] = nums[n - 1];

          for (int i = n - 2; i >= 0; i--) {
                suffixMin[i] = min(suffixMin[i + 1], nums[i]);
          }

          long long prefixSum = 0;
          long long ans = LLONG_MIN;

          for (int i = 0; i < n - 1; i++) {
                prefixSum += nums[i];
                ans = max(ans, prefixSum - (long long)suffixMin[i + 1]);
          }

          return ans;
     }
};
```

---

## Explanation of the Code

### `suffixMin` construction

* We start from the end because each position depends on the right side
* This guarantees `O(n)` preprocessing

### `prefixSum`

* Accumulated on the fly
* Avoids extra array

### `long long`

* Necessary because:

  * `nums[i]` can be up to `10⁹`
  * Prefix sums can exceed `int` range
* Prevents silent overflow bugs

---

## Dry Run Example

### Input

```
nums = [10, -1, 3, -4, -5]
```

### Suffix Min Array

```
suffixMin = [-5, -5, -5, -5, -5]
```

### Iteration

| i | prefixSum | suffixMin[i+1] | score |
| - | --------- | -------------- | ----- |
| 0 | 10        | -5             | 15    |
| 1 | 9         | -5             | 14    |
| 2 | 12        | -5             | 17    |
| 3 | 8         | -5             | 13    |

**Maximum Score = 17**

---

## Common Pitfalls (Important)

### Out-of-bounds access

```cpp
suffixMin[i + 1]  // only valid when i < n - 1
```

### Using `int` for prefix sums

```cpp
int prefixSum;  // may overflow
```

### Incorrect suffix logic

* Using suffix **sum** instead of suffix **minimum**
* Updating wrong array during suffix computation

---

## Time & Space Complexity

* **Time Complexity:** `O(n)`
* **Space Complexity:** `O(n)` (for suffixMin)

---

## Pattern Recognition

This problem is a textbook example of:

> **"Prefix accumulation + suffix preprocessing"**

You should immediately think of this pattern when:

* One side needs a cumulative value (sum, max, etc.)
* The other side needs a range property (min, max)

---

## Final Takeaway

* The logic is simple once the pattern is recognized
* Most mistakes happen due to:

  * Index boundaries
  * Data type overflow
* The final solution is optimal and clean

