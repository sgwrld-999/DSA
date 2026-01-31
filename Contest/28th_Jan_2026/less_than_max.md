## Goal (short)

Given an array `A` of size `N`, find the length of the **largest good subsequence**.

A subsequence `B` is **good** if for every element `B[i]`:

* either `B[i] == 1`
* or there exists some earlier element `B[j] = B[i] - 1`

Order must be preserved.

---

## Key Observation

The condition for a good subsequence is **existence-based**, not count-based.

For a value `x` to be included:

* `x = 1` is always allowed
* `x > 1` is allowed **only if `x - 1` already exists earlier in the subsequence**

We **do not need**:

* frequencies
* sorting
* longest increasing sequence logic
* dynamic programming

We only need to ensure that the subsequence grows **level by level**.

---

## Core Idea (Greedy Construction)

We process the array **left to right**, building a valid good subsequence greedily.

Maintain:

* `curr`: the **maximum valid level** we have constructed so far
* `ans`: length of the subsequence formed

Interpretation of `curr`:

* If `curr = k`, then the subsequence already contains valid elements:

  ```
  1, 2, 3, ..., k
  ```

  (not necessarily once each, order preserved)

---

## Decision Rule for Each Element

For each element `A[i]`:

### Case 1: `A[i] <= curr`

This element can always be added.

Reason:

* If `A[i] == 1`, condition is trivially satisfied
* If `A[i] > 1`, then `A[i] - 1 <= curr - 1` already exists in the subsequence

So we:

* increment `ans`
* do **not** change `curr`

---

### Case 2: `A[i] == curr + 1`

This element **extends** the subsequence to the next level.

Reason:

* `curr` exists
* so `curr + 1` satisfies the good condition

So we:

* increment `curr`
* increment `ans`

---

### Case 3: `A[i] > curr + 1`

This element **cannot** be added.

Reason:

* required predecessor `A[i] - 1` does not exist yet
* adding it would violate the good subsequence condition

So we:

* skip the element

---

## Algorithm (Step-by-step)

1. Initialize:

   ```
   curr = 0
   ans = 0
   ```
2. Traverse the array from left to right
3. Apply the decision rules above
4. Output `ans`

---

## Code (As Given)

```python
testcase = int(input())

while testcase > 0:
    n = int(input())
    arr = list(map(int, input().split()))

    ans = 0
    curr = 0

    for val in range(n):
        if arr[val] <= curr:
            ans += 1
        elif arr[val] == curr + 1:
            curr += 1
            ans += 1

    print(ans)
    testcase -= 1
```

---

## Worked Examples

### Example 1

```
A = [1, 2, 3, 4]
```

Progress:

```
1 → curr = 1
2 → curr = 2
3 → curr = 3
4 → curr = 4
```

Answer: `4`

---

### Example 2

```
A = [1, 3, 1, 2, 3]
```

Progress:

```
1 → curr = 1
3 → skipped (needs 2)
1 → allowed
2 → curr = 2
3 → curr = 3
```

Subsequence length = `4`

---

### Example 3

```
A = [2, 2, 2]
```

Progress:

```
2 → skipped (needs 1)
2 → skipped
2 → skipped
```

Answer: `0`

---

## Why This Greedy Approach Is Correct

* The problem only asks whether a predecessor **exists**, not how many times
* Once a level `k` is formed, **any future value ≤ k** is always valid
* Extending to `k+1` requires exactly one condition: `k` must exist
* Taking an element earlier can never block a better solution later

Thus:

* Always take what is valid
* Extend only when allowed
* Skip everything else

This guarantees the maximum possible length.

---

## Time and Space Complexity

* Time: `O(N)` per test case
* Space: `O(1)`

---
