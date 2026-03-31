# Interview Script — Longest Increasing Subsequence (Binary Search Approach)

---

## 1. Opening

**“Let me restate the problem.”**

We are given an array `nums`.

We need to find:

> the length of the longest subsequence such that every next element is strictly greater than the previous one.

👉 Important:

* Subsequence ≠ subarray (we can skip elements)
* Order must be maintained

---

## 2. Intuition

**“A brute force approach would try all subsequences, but that would be exponential.”**

So instead, we optimize.

---

## 3. Key Idea (Greedy + Binary Search)

**“Instead of building the actual subsequence, I maintain a helper array `temp`.”**

👉 `temp[i]` = smallest possible ending element of an increasing subsequence of length `i+1`

---

## 4. Core Insight (Very Important)

**“We don’t need the actual LIS, we only need its length.”**

So:

* Keep `temp` as small as possible
* This allows more room to extend the subsequence later

---

# 5. Algorithm (Step-by-step)

---

### Step 1: Initialize

```python
temp = [nums[0]]
```

---

### Step 2: Traverse the array

For every element:

---

### Case 1: Extend LIS

```python
if nums[i] > temp[-1]:
    temp.append(nums[i])
```

**“If current element is greater than the last element, we extend the sequence.”**

---

### Case 2: Replace using Binary Search

```python
else:
    ind = lower_bound(temp, nums[i])
    temp[ind] = nums[i]
```

**“We find the first element ≥ current number and replace it.”**

---

## 6. Why Replacement Works (Most Important Explanation)

**“We are not building the actual LIS, but maintaining the best candidates.”**

👉 Replacing:

* keeps subsequence length same
* reduces value → better chance to extend later

---

## 7. Binary Search (Lower Bound)

```python
def lower_bound(temp, target):
```

---

### Logic

```python
while left <= right:
    mid = (left + right) // 2
    
    if temp[mid] < target:
        left = mid + 1
    else:
        right = mid - 1
```

---

### Return

```python
return left
```

👉 First index where `temp[ind] >= target`

---

## 8. Dry Run

### Example:

```
nums = [1, 5, 7, 2, 3]
```

---

Step-by-step:

```
temp = [1]

5 → [1,5]
7 → [1,5,7]

2 → replace 5 → [1,2,7]

3 → replace 7 → [1,2,3]
```

---

👉 Final length = **3**

---

## 9. Final Answer

```python
return len(temp)
```

---

# 10. Why this works (Interview Gold)

**“temp array always stores the smallest possible ending elements of increasing subsequences of different lengths.”**

👉 This ensures:

* maximum flexibility
* correct LIS length

---

# 11. Complexity

### Time Complexity

**O(N log N)**

* N iterations
* each uses binary search

---

### Space Complexity

**O(N)**

* temp array

---

# 12. How to explain in interview

You can say:

**“I maintain a helper array where each index represents the smallest possible ending value of an increasing subsequence of that length. If the current element extends the sequence, I append it; otherwise, I replace the appropriate element using binary search.”**

---

# 13. Brute → Optimized Thinking

**“Initially, I would think of DP (O(N²)).”**

→ compare all previous elements

Then:

→ optimize using greedy + binary search

→ reduce to O(N log N)

---

# 14. 30-second polished answer

**“I use a greedy approach with binary search. I maintain a temporary array where each element represents the smallest possible tail of an increasing subsequence of that length. For each number, I either extend the array or replace an element using binary search. The size of this array gives the LIS length in O(N log N).”**

---

# 15. 10-second answer

**“Use greedy + binary search on a temp array; answer is its length.”**

---

# 16. Nice closing line

**“The key idea is not to store the actual subsequence, but to maintain optimal candidates using binary search.”**

---

