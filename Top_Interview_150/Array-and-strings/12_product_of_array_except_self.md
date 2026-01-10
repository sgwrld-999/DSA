# Product of Array Except Self — Full Explanation

---

## Problem Restatement (Simplified)

You are given:

* An integer array **`nums`** of size **N**
* Elements may be **positive, negative, or zero**

### Task

Construct an array **`answer`** such that:

[
answer[i] = \prod_{j \ne i} nums[j]
]

### Constraints

* Do **not** use division in the *final optimal solution*
* Time complexity should be **O(N)**
* Extra space should be **O(1)** (excluding output array)

---

## Key Observations

---

## 1. Why the naive approach fails

### Brute-force idea

For each index `i`:

* Multiply all elements except `nums[i]`

### Complexity

[
O(N^2)
]

This leads to **repeated multiplications** and fails time constraints.

---

## 2. Division-Based Thinking (Why it Appears Attractive)

A natural thought is:

[
answer[i] = \frac{\text{product of all elements}}{nums[i]}
]

However, this introduces:

* Division (disallowed)
* Zero-handling complexity
* Risk of incorrect logic

---

## 3. Correctly Handling Zeros with Division (Your Code)

Below is a **logically correct division-based solution** that explicitly handles zero cases.

### Included Code (Division + Zero Handling)

```cpp
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = nums.size();
        vector<int> temp(nums.begin(), nums.end());

        int zeroCount = 0;
        int product = 1;

        for (int i = 0; i < n; i++) {
            if (temp[i] == 0) {
                zeroCount++;
            } else {
                product *= temp[i];
            }
        }

        for (int i = 0; i < n; i++) {
            if (zeroCount > 1) {
                nums[i] = 0;
            } 
            else if (zeroCount == 1) {
                nums[i] = (temp[i] == 0) ? product : 0;
            } 
            else {
                nums[i] = product / temp[i];
            }
        }

        return nums;
    }
};
```

---

## 4. Why This Code Works (Case Analysis)

### Case 1: More than one zero

```
nums = [1, 0, 2, 0]
```

* Every product except self includes at least one zero
* Output:

```
[0, 0, 0, 0]
```

Correctly handled by:

```cpp
if (zeroCount > 1)
```

---

### Case 2: Exactly one zero

```
nums = [1, 2, 0, 4]
```

* Only the zero position gets the product of non-zero elements
* All others get `0`

Handled by:

```cpp
nums[i] = (temp[i] == 0) ? product : 0;
```

---

### Case 3: No zeros

```
nums = [1, 2, 3, 4]
```

* Safe division
* Each element divides the total product

Handled by:

```cpp
nums[i] = product / temp[i];
```

---

## 5. Why This Is Still Not the Expected Interview Solution

Although **logically correct**, this approach:

* Uses division (explicitly discouraged)
* Requires careful zero counting
* Does not demonstrate reusable computation insight

Interviewers expect a **multiplication-only solution**.

---

## 6. Correct Mental Model (Key Insight)

Instead of:

> “Total product divided by me”

Think:

> “Product of elements to my left × product of elements to my right”

This removes:

* Division
* Zero special cases
* Fragile logic

---

## 7. Prefix–Suffix Decomposition

### Definitions

* `prefix[i]` = product of elements before index `i`
* `suffix[i]` = product of elements after index `i`

Then:

[
answer[i] = prefix[i] \times suffix[i]
]

---

## 8. Optimal Solution (No Division, O(1) Extra Space)

### Correct Code (Expected by Interviewers)

```cpp
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = nums.size();
        vector<int> answer(n, 1);

        int prefix = 1;
        for (int i = 0; i < n; i++) {
            answer[i] = prefix;
            prefix *= nums[i];
        }

        int suffix = 1;
        for (int i = n - 1; i >= 0; i--) {
            answer[i] *= suffix;
            suffix *= nums[i];
        }

        return answer;
    }
};
```

---

## 9. Complexity Analysis

| Approach                 | Time  | Extra Space | Division |
| ------------------------ | ----- | ----------- | -------- |
| Brute force              | O(N²) | O(1)        | No       |
| Division + zero handling | O(N)  | O(N)        | Yes      |
| Prefix–suffix (optimal)  | O(N)  | O(1)        | No       |

---

## Intuition Summary

* Division-based solutions **can be made correct**, but are fragile
* Prefix–suffix:

  * Eliminates recomputation
  * Handles zeros naturally
  * Matches problem intent
* This problem tests **array decomposition thinking**, not arithmetic tricks

---

## Interview Takeaway

When a problem says:

> “For each index, compute something using all other elements”

