# Minimum Subarray Length With Distinct Sum At Least K — Full Explanation (From First Principles)

---

## 1. Understanding the Question (Very Important)

You are given:

* An **integer array** `nums`
* An **integer** `k`

Your task is to:

* Find the **minimum length of a contiguous subarray**
* Such that the **sum of distinct values** in that subarray (each value counted once)
* Is **greater than or equal to `k`**

If **no such subarray exists**, return `-1`.

---

## 2. What Makes This Problem Different?

This is **not** a normal subarray sum problem.

Key difference:

* If a number appears **multiple times** in the subarray
* It must be **counted only once** in the sum

### Example

```
Subarray: [2, 2, 3]
Distinct elements: {2, 3}
Distinct sum = 2 + 3 = 5
```

Even though `2` appears twice, it contributes **only once**.

---

## 3. Important Observations

* The subarray must be **contiguous**
* We want the **minimum possible length**
* All values are **positive**, which allows a **sliding window**
* Distinctness forces us to **track frequency**

This immediately suggests:

**Sliding Window + Frequency Map**

---

## 4. Why Sliding Window Works Here

Because:

* All numbers are positive
* Expanding the window increases (or keeps) the distinct sum
* Shrinking the window can reduce the distinct sum
* We want to **expand to satisfy the condition**, then **shrink to minimize length**

This is the classic **two-pointer optimization pattern**.

---

## 5. Core Idea of the Algorithm

Maintain a window `[left, right]` such that:

* We know how many times each number appears
* We track the **sum of distinct elements** inside the window

### Data We Maintain

* `freq[x]` → frequency of element `x` in the window
* `distinctSum` → sum of elements whose frequency ≥ 1
* `left` → left pointer of window
* `answer` → minimum window length found

---

## 6. How the Window Expands

When moving `right` forward:

1. Add `nums[right]` to the frequency map
2. If its frequency becomes `1`, it is a **new distinct value**
3. Add it to `distinctSum`

Conceptually:

```
if freq[val] == 1:
    distinctSum += val
```

---

## 7. How the Window Shrinks (Key Step)

While:

```
distinctSum >= k
```

We try to **shrink from the left** to minimize length:

1. Update the answer with current window size
2. Reduce frequency of `nums[left]`
3. If frequency becomes `0`, remove it from `distinctSum`
4. Move `left` forward

This guarantees we always keep the window **as small as possible**.

---

## 8. Complete Annotated Code (C++)

```cpp
class Solution {
public:
    int minLength(vector<int>& nums, int k) {
        int n = nums.size();
        unordered_map<int, int> freq;

        long long distinctSum = 0;
        int left = 0;
        int answer = INT_MAX;

        for (int right = 0; right < n; right++) {
            // Add element to window
            freq[nums[right]]++;
            if (freq[nums[right]] == 1) {
                distinctSum += nums[right];
            }

            // Shrink window while condition holds
            while (distinctSum >= k) {
                answer = min(answer, right - left + 1);

                freq[nums[left]]--;
                if (freq[nums[left]] == 0) {
                    distinctSum -= nums[left];
                }
                left++;
            }
        }

        return (answer == INT_MAX ? -1 : answer);
    }
};
```

```python
from collections import defaultdict
class Solution:
    def minLength(self, nums: List[int], k: int) -> int:
 
        n = len(nums)
        freq = defaultdict(int)
        distinct_sum = 0
        left = 0
        answer = float('inf')

        for right in range(n):
            # Add element to window
            freq[nums[right]] += 1
            if freq[nums[right]] == 1:
            distinct_sum += nums[right]
            
            # Shrink window while condition holds
            while distinct_sum >= k:
            answer = min(answer, right - left + 1)
            
            freq[nums[left]] -= 1
            if freq[nums[left]] == 0:
                distinct_sum -= nums[left]
            left += 1
        
        return answer if answer != float('inf') else -1

```

---

## 9. Step-by-Step Walkthrough (Critical)

### Example 1

```
nums = [2, 2, 3, 1], k = 4
```

Window progression:

```
[2]           distinctSum = 2
[2,2]         distinctSum = 2
[2,2,3]       distinctSum = 5  >= k
Shrink → [2,3] length = 2
```

Minimum length = `2`

---

### Example 2

```
nums = [3,2,3,4], k = 5
```

```
[3,2] → distinctSum = 5
Length = 2
```

Answer = `2`

---

### Example 3 (Single Element Case)

```
nums = [5,5,4], k = 5
```

```
[5] → distinctSum = 5
```

Answer = `1`

---

## 10. Edge Cases Handled Automatically

* Single element satisfying `k`
* Duplicate-heavy arrays
* No valid subarray (returns `-1`)
* Large `k` values
* Large input size (`10^5`)

---

## 11. Why This Approach Is Optimal

* **Time Complexity:** `O(n)`

  * Each element enters and leaves the window once
* **Space Complexity:** `O(n)`

  * Frequency map in the worst case
* No nested loops over subarrays
* Fully satisfies constraints

---

## 12. Key Takeaway

This problem is a **sliding window with a twist**:

> You are not summing elements —
> You are summing **distinct elements with frequency tracking**.

Once you recognize that, the solution becomes systematic and reliable.
