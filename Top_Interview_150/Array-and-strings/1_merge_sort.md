# Merge Sorted Array (LeetCode 88)

## Problem in one line

Given two sorted arrays `nums1` and `nums2`, merge `nums2` into `nums1` **in-place**, producing a single sorted array.

---

## Key Constraints (MOST IMPORTANT)

* `nums1` has size `m + n`
* First `m` elements of `nums1` are valid
* Last `n` elements of `nums1` are **empty space (0s)**
* `nums2` has `n` valid elements
* **Must modify `nums1` in-place**
* Expected time: **O(m + n)**
* Expected space: **O(1)**

---

## Correct Core Idea (What the problem actually wants)

> Merge from the **end**, not from the front.

Why:

* Front merge overwrites useful values
* Backward merge uses extra space already present in `nums1`

---

## Correct Algorithm (High Level)

1. Use three pointers:

   * `i = m - 1` → last valid element of `nums1`
   * `j = n - 1` → last element of `nums2`
   * `k = m + n - 1` → last index of `nums1`
2. Compare `nums1[i]` and `nums2[j]`
3. Place the larger value at `nums1[k]`
4. Move pointers accordingly
5. Stop when `nums2` is exhausted

---

## Correct Code (Reference)

```python
class Solution:
	def merge(self, nums1: List[int], m: int, nums2: List[int], n: int) -> None:
		i = m - 1
		j = n - 1
		k = m + n - 1

		while j >= 0:
			if i >= 0 and nums1[i] > nums2[j]:
				nums1[k] = nums1[i]
				i -= 1
			else:
				nums1[k] = nums2[j]
				j -= 1
			k -= 1
```

---

## Time & Space Complexity

* **Time:** `O(m + n)`
* **Space:** `O(1)` (in-place)

---

# ❌ All Mistakes You Made (Very Important)

This section is gold for interviews.

---

## Mistake 1: Using Merge Sort for This Problem

```python
merge_sort(nums, 0, len(nums)-1)
```

### Why it’s wrong

* Merge Sort = `O(n log n)`
* Problem explicitly expects `O(m + n)`
* You already have sorted arrays — sorting again is unnecessary

### Interview takeaway

> When inputs are already sorted, **don’t re-sort**.

---

## Mistake 2: Creating a New Array Instead of Modifying `nums1`

```python
nums = nums1 + nums2
```

### Why it’s wrong

* Creates a **new array**
* Does **not modify `nums1`**
* Violates problem statement

### Key rule

> Assignment (`=`) does not mean in-place modification.

---

## Mistake 3: Ignoring `m` and `n`

You merged:

* All of `nums1`
* Including trailing zeroes

### Why this is wrong

* Only first `m` elements of `nums1` are valid
* Remaining zeros are placeholders, not values

---

## Mistake 4: Wrong `mid` Calculation → Infinite Recursion (TLE)

```python
mid = high - (high - low) // 2
```

### What happened

* Recursive calls didn’t reduce the range
* Same `(low, high)` repeated
* **Infinite recursion → TLE**

### Correct mid

```python
mid = low + (high - low) // 2
```

---

## Mistake 5: Defining `merger` but Calling `merge`

```python
def merger(...):
	...

merge(nums, low, mid, high)  # wrong function
```

### Why it’s dangerous

* Calls the outer LeetCode `merge`
* Causes unexpected recursion / logic break

---

## Mistake 6: Using Dictionary Instead of List

```python
temp = {}
temp.append(...)
```

### Why it’s wrong

* `{}` creates a dictionary
* Dictionaries do not have `append`

Correct:

```python
temp = []
```

---

## Mistake 7: Incorrect Range While Copying Back

```python
for i in range(low, high):
```

### Why it’s wrong

* `range` is **exclusive**
* Misses `high`

Correct:

```python
for i in range(low, high + 1):
```

---

## Mistake 8: Solving the Wrong Problem Altogether

You treated this as:

* “Merge two arrays using merge sort”

But the actual problem is:

* “Merge into existing space in nums1”

---

## Why Your Code Caused TLE (Final Summary)

| Reason               | Effect                       |
| -------------------- | ---------------------------- |
| Infinite recursion   | Major TLE                    |
| Merge sort usage     | Slower than required         |
| Extra array creation | Memory + time waste          |
| Wrong logic focus    | Problem constraint violation |

---

## Interview-Ready One-Liner (Memorize This)

> “My initial solution failed because I used merge sort and recursion, causing unnecessary overhead and infinite recursion. The correct approach is a backward two-pointer merge that runs in O(m+n) time and modifies nums1 in-place.”

---

## Final Takeaway

* **Read constraints carefully**
* If array is sorted → think **two pointers**
* If in-place is mentioned → **avoid temp arrays**
* If extra space exists → **use it smartly**

---

