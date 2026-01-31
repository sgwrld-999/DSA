# Majority Element (LeetCode 169)

## Problem in one line

Given an array `nums` of size `n`, find the element that appears **more than ⌊n/2⌋ times**.

> The majority element **always exists** (important constraint).

---

# Approach 1: HashMap / Frequency Count

**O(n) Time | O(n) Space**

### Python Code

```python
from typing import List
from collections import defaultdict

class Solution:
    def majorityElementInN(self, nums: List[int]) -> int:
        freq = defaultdict(int)

        for num in nums:
            freq[num] += 1

        n = len(nums)
        for num, count in freq.items():
            if count > n // 2:
                return num
```

---

### Idea

* Count occurrences of each element
* Return the one with frequency `> n/2`

---

### Drawbacks

* Uses extra space
* Not optimal for interviews

---

# Approach 2: Sorting

**O(n log n) Time | O(1) Space**

### Python Code

```python
class Solution:
    def majorityElementInNLogN(self, nums: List[int]) -> int:
        nums.sort()
        return nums[len(nums) // 2]
```

---

### Why this works

* Majority element occupies **more than half** the array
* After sorting, it must appear at the **middle index**

---

### Drawbacks

* Slower than linear time
* Sorting is unnecessary overhead

---

# Approach 3: Boyer–Moore Voting Algorithm (OPTIMAL)

**O(n) Time | O(1) Space**

### Python Code (Final Answer)

```python
class Solution:
    def majorityElement(self, nums: List[int]) -> int:
        candidate = None
        count = 0

        for num in nums:
            if count == 0:
                candidate = num

            count += 1 if num == candidate else -1

        return candidate
```

---

## ✅ Interview Thought Process (Say This Clearly)

> “Since the majority element appears more than n/2 times, it can never be completely canceled out by other elements.
> I maintain a candidate and a count.
> When the count becomes zero, I choose the current element as the new candidate.
> If the current element matches the candidate, I increment the count; otherwise, I decrement it.
> Because the majority element occurs more than all others combined, it will remain as the final candidate.”

---

## 🧠 Intuition (Very Important)

Think of it as **pair cancellation**:

* Majority element = +1 vote
* Other elements = −1 vote
* Since majority has **more votes than all others combined**, it survives

---

## Example Walkthrough

```
nums = [2, 2, 1, 1, 1, 2, 2]
```

| num | candidate | count |
| --- | --------- | ----- |
| 2   | 2         | 1     |
| 2   | 2         | 2     |
| 1   | 2         | 1     |
| 1   | 2         | 0     |
| 1   | 1         | 1     |
| 2   | 1         | 0     |
| 2   | 2         | 1     |

Final candidate = **2**

---

## Why No Second Pass Is Needed

* Problem guarantees the majority element exists
* Otherwise, we would verify candidate frequency

---

## Complexity Comparison

| Approach    | Time       | Space | Interview |
| ----------- | ---------- | ----- | --------- |
| HashMap     | O(n)       | O(n)  | ❌         |
| Sorting     | O(n log n) | O(1)  | ⚠️        |
| Boyer–Moore | O(n)       | O(1)  | ✅         |

---

## Final Interview One-Liner

> “I used the Boyer–Moore Voting Algorithm, which works by canceling out non-majority elements. Since the majority element appears more than n/2 times, it always survives, giving an O(n) time and O(1) space solution.”

---
