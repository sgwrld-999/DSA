Below are **complete, structured notes** for **Rotate Array (LeetCode 189)** with
✅ **Python conversion of all approaches**
✅ **Clear observations**
✅ **Why each approach works**
✅ **Dry runs for each approach**
✅ **Compressed summaries for revision**

Written in the **same serious interview-prep note style** you’ve been using.

---

# Rotate Array (LeetCode 189)

## Problem in one line

Given an array `nums`, rotate the array to the **right** by `k` steps.

---

## Key Observations (READ FIRST)

1. Rotating right by `k` means:

   * Every element moves from index `i` → `(i + k) % n`
2. `k` can be **larger than `n`**

   * Rotating `n` times gives the same array
   * So always do:

     ```python
     k = k % n
     ```
3. The problem **does not ask for returning anything**

   * You must **modify the array in-place**

---

# 🔹 Approach 1: Brute Force (Rotate One Step at a Time)

## Observation

> A right rotation by `k` is equivalent to performing **1-step right rotation `k` times**.

---

## Thought Process

* In one right rotation:

  * Save the last element
  * Shift all elements one position to the right
  * Put the saved element at index `0`
* Repeat this process `k` times

---

## Python Code

```python
class Solution:
    def rotate(self, nums: list[int], k: int) -> None:
        n = len(nums)
        k %= n

        for _ in range(k):
            last = nums[-1]
            for i in range(n - 2, -1, -1):
                nums[i + 1] = nums[i]
            nums[0] = last
```

---

## Dry Run

```
nums = [1,2,3,4,5], k = 2
```

### First rotation:

```
[5,1,2,3,4]
```

### Second rotation:

```
[4,5,1,2,3]
```

---

## Complexity

* **Time:** `O(n × k)`
* **Space:** `O(1)`

---

## Why this is bad

* If `n = 10^5` and `k = 10^5`
* Operations = `10^10` → **TLE**

---

## Summary

❌ Too slow
❌ Only good for understanding rotation mechanics

---

# 🔹 Approach 2: Extra Array (Index Mapping)

## Key Observation (VERY IMPORTANT)

> After rotation, element at index `i` goes to index
> `(i + k) % n`

This formula **directly describes rotation**.

---

## Thought Process

* Create a new array `temp`
* For every index `i`:

  * Place `nums[i]` at `(i + k) % n` in `temp`
* Copy `temp` back to `nums`

---

## Python Code

```python
class Solution:
    def rotate(self, nums: list[int], k: int) -> None:
        n = len(nums)
        k %= n

        temp = [0] * n
        for i in range(n):
            temp[(i + k) % n] = nums[i]

        nums[:] = temp
```

---

## Dry Run

```
nums = [1,2,3,4,5], k = 2
```

| i | nums[i] | New index `(i+k)%n` | temp        |
| - | ------- | ------------------- | ----------- |
| 0 | 1       | 2                   | [0,0,1,0,0] |
| 1 | 2       | 3                   | [0,0,1,2,0] |
| 2 | 3       | 4                   | [0,0,1,2,3] |
| 3 | 4       | 0                   | [4,0,1,2,3] |
| 4 | 5       | 1                   | [4,5,1,2,3] |

---

## Complexity

* **Time:** `O(n)`
* **Space:** `O(n)`

---

## Why it works

* Every element is placed **exactly where it should be**
* No overwriting issues
* Simple and safe

---

## Summary

✅ Fast
❌ Uses extra space
⚠️ Not optimal for interviews

---

# 🔹 Approach 3: Optimal In-Place Reverse Method (EXPECTED)

## 🔑 Core Observation (THIS IS THE KEY)

Right rotation by `k` means:

```
Original:  [A B C D E F G]
Rotate k=3 → [E F G A B C D]
```

Which can be achieved by **reversals**.

---

## Why Reversal Works (Important Explanation)

### Step-by-step logic

1. Reverse the entire array

   ```
   [G F E D C B A]
   ```
2. Reverse the first `k` elements

   ```
   [E F G D C B A]
   ```
3. Reverse the remaining `n-k` elements

   ```
   [E F G A B C D]
   ```

➡️ Final result = rotated array

---

## Python Code (Optimal)

```python
class Solution:
    def rotate(self, nums: list[int], k: int) -> None:
        n = len(nums)
        k %= n

        self.reverse(nums, 0, n - 1)
        self.reverse(nums, 0, k - 1)
        self.reverse(nums, k, n - 1)

    def reverse(self, nums, left, right):
        while left < right:
            nums[left], nums[right] = nums[right], nums[left]
            left += 1
            right -= 1
```

---

## Dry Run (Very Important)

```
nums = [1,2,3,4,5,6,7], k = 3
```

### Step 1: Reverse whole array

```
[7,6,5,4,3,2,1]
```

### Step 2: Reverse first k elements

```
[5,6,7,4,3,2,1]
```

### Step 3: Reverse remaining elements

```
[5,6,7,1,2,3,4]
```

---

## Complexity

* **Time:** `O(n)`
* **Space:** `O(1)`

---

## Why this is optimal

* No extra array
* Each element swapped a constant number of times
* Uses array properties cleverly

---

## Interview Thought Process (Say This)

> “Instead of rotating one step at a time, I observed that rotation can be decomposed into a sequence of reversals. Reversing the entire array and then reversing the first k and remaining n−k elements gives the rotated result in O(n) time and O(1) space.”

---

# 🔁 Final Comparison Summary

| Approach       | Time   | Space | Interview |
| -------------- | ------ | ----- | --------- |
| Brute Force    | O(n×k) | O(1)  | ❌         |
| Extra Array    | O(n)   | O(n)  | ⚠️        |
| Reverse Method | O(n)   | O(1)  | ✅         |

---

## Final Takeaway

* If rotation + in-place → **think reversal**
* If formula `(i+k)%n` appears → extra array approach
* If brute force seems easy → probably not optimal

---

If you want next:

* Left rotation variant
* Rotate linked list
* Common rotation mistakes checklist
* One-page revision sheet

Just tell me.
