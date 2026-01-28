# Longest Substring Without Repeating Characters

## Problem Statement

Given a string `s`, find the **length of the longest substring** without repeating characters.

* Substring must be **contiguous**
* Characters must be **unique**
* Return `0` for an empty string

---

## Key Observations

* Brute force checks all substrings → very slow
* Repetition invalidates the substring immediately
* We need to **expand and shrink dynamically**
* This is a **variable-size sliding window** problem

---

## Possible Approaches

### 1. Brute Force (Your First Attempt)

* Fix starting index `i`
* Fix ending index `j`
* Check substring `s[i:j]` for uniqueness using a hashmap

❌ Time Complexity: `O(n³)`
❌ Not scalable
❌ Repeated work for overlapping substrings

---

### 2. Sliding Window + HashMap (Optimal)

✅ **Correct and intended solution**

* Maintain a window `[left, right]`
* Expand `right`
* Shrink `left` only when duplicates appear
* Track maximum window size

---

## Your Sliding Window Approach — What Went Wrong

### ❌ Mistake 1: Impossible shrinking condition

```python
while left > right and mp[s[right]] > 2:
```

**Why wrong**

* `left` never becomes greater than `right`
* This condition is **never true**
* Shrinking never happens

---

### ❌ Mistake 2: Wrong duplicate threshold

```python
mp[s[right]] > 2
```

**Why wrong**

* Duplicate appears at count **2**
* Correct condition is `> 1`

---

### ❌ Mistake 3: Updating answer inside invalid window

```python
ans = max(ans, right - left + 1)
```

**Why wrong**

* This runs while duplicates exist
* Answer must be updated **only after the window is valid**

---

### ❌ Mistake 4: Incorrect dictionary cleanup

```python
if mp[s[left]] is 0:
    mp.remove(s[left])
```

**Why wrong**

* `is` checks identity, not value
* `dict` has no `remove()` method

---

### ❌ Mistake 5: Wrong initialization

```python
ans = float("-inf")
```

**Why wrong**

* Substring length is never negative
* Leads to unnecessary edge-case handling

---

## Correct Sliding Window Solution

```python
class Solution:
    def lengthOfLongestSubstring(self, s: str) -> int:
        n = len(s)
        ans = 0
        left = 0
        mp = dict()

        for right in range(n):

            if s[right] not in mp:
                mp[s[right]] = 0
            mp[s[right]] += 1

            # shrink until window becomes valid
            while mp[s[right]] > 1:
                mp[s[left]] -= 1
                if mp[s[left]] == 0:
                    del mp[s[left]]
                left += 1

            # update answer only when window is valid
            ans = max(ans, right - left + 1)

        return ans
```

---

## Dry Run

### Input

```python
s = "abcabcbb"
```

### Pointer Movement

```
right=0 → "a" → window="a" → ans=1
right=1 → "ab" → ans=2
right=2 → "abc" → ans=3
right=3 → duplicate 'a' → shrink → "bca"
right=4 → duplicate 'b' → shrink → "cab"
right=5 → duplicate 'c' → shrink → "abc"
right=6 → duplicate 'b' → shrink → "cb"
right=7 → duplicate 'b' → shrink → "b"
```

Final Answer = `3`

---

## Time & Space Complexity

* **Time Complexity:** `O(n)`
* **Space Complexity:** `O(min(n, charset))`

---

## Common Mistakes (Mapped to Your Code)

* Shrinking based on pointer comparison instead of frequency
* Allowing two occurrences of a character
* Updating answer inside an invalid window
* Resetting or mismanaging hashmap entries
* Using brute-force thinking in sliding window problems

---

## Key Takeaways

* Sliding window problems rely on **invariants**

* For this problem:

  > **Window must always contain unique characters**

* Shrink **only when invariant breaks**

* Update answer **only when invariant holds**

* Hashmap lifecycle must match window lifecycle

---

