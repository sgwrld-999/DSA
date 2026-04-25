# **Sliding Window Technique — Notes (from scratch, simple thinking)**

## **1. What is the actual problem we are solving?**

You are given:

* an **array** or a **string**

And the question says:

* find something inside a **subarray / substring**

Example:

* max sum of subarray of size `k`
* longest substring without repeating characters

---

## **2. How would you normally solve it (Brute Force)?**

You would:

* take every possible subarray
* calculate answer for each

Example:

```
[2, 1, 5, 1, 3], k = 3

Subarrays:
[2,1,5]
[1,5,1]
[5,1,3]
```

For each → compute sum again and again

Problem:

* You are doing **repeated work**
* Time complexity → **O(n²)**

---

## **3. Key Idea (This is Sliding Window)**

Instead of recalculating everything:

👉 **Reuse previous result**

Think like this:

> “If I already know the sum of this window,
> why compute it again from scratch?”

---

### Example Thought:

Window: `[2, 1, 5] → sum = 8`

Next window: `[1, 5, 1]`

Instead of recalculating:

```
(1 + 5 + 1)
```

Do:

```
remove 2, add 1 → 8 - 2 + 1 = 7
```

👉 This is the whole idea.

---

## **4. What does "window" mean?**

A window is just:

* a **range of elements**
* defined by two pointers:

```
[left .... right]
```

You:

* expand window → move `right`
* shrink window → move `left`

---

## **5. When to use Sliding Window?**

Use it when:

1. Array or string is given
2. You are asked about **subarray / substring**
3. You need:

   * max / min
   * length
   * count

---

## **6. Types of Sliding Window**

### **(A) Fixed Window (size = k)**

* size never changes

Example:

* max sum of subarray of size k

---

### **(B) Variable Window**

* size changes dynamically

Example:

* longest substring without repeating characters

---

## **7. Generic Template (Fixed Window)**

Now understand step by step:

```python
left = 0
window_sum = 0

for right in range(len(nums)):

    # Step 1: include new element
    window_sum += nums[right]

    # Step 2: if window size < k → expand
    if right - left + 1 < k:
        continue

    # Step 3: window size == k → process
    if right - left + 1 == k:
        # calculate answer
        ans = max(ans, window_sum)

        # Step 4: slide window
        window_sum -= nums[left]
        left += 1
```

---

## **8. Code Example**

### **Problem: Maximum sum of subarray of size k**

```python
from typing import List

class SlidingWindow:

    def max_sum_subarray(self, nums: List[int], k: int) -> int:
        n = len(nums)

        if n < k:
            return 0

        # Step 1: first window
        window_sum = sum(nums[:k])
        max_sum = window_sum

        left = 0

        # Step 2: slide window
        for right in range(k, n):
            window_sum = window_sum - nums[left] + nums[right]
            max_sum = max(max_sum, window_sum)
            left += 1

        return max_sum
```

---

## **9. What is actually happening (real understanding)**

You are doing only 3 operations repeatedly:

1. Add new element (right side)
2. Remove old element (left side)
3. Update answer

That’s it. Nothing fancy.

---

## **10. How to explain in interview**

“I treat a subarray as a window with two pointers.
Instead of recomputing the sum for every subarray, I reuse the previous window result.

I add the next element and remove the previous one, which reduces time complexity from O(n²) to O(n).”

---
