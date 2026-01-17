# Is Subsequence — Full Explanation

---

## Problem Restatement (Simplified)

You are given two strings:

```
s → pattern string
t → target string
```

Your task is to check whether **s is a subsequence of t**.

### Definition

`s` is a subsequence of `t` if **all characters of `s` appear in `t` in the same order**, but **not necessarily contiguously**.

---

## Examples

```
s = "abc", t = "ahbgdc" → True
s = "axc", t = "ahbgdc" → False
```

---

## Important Observation

* Characters must appear **in order**
* Skipping characters in `t` is allowed
* Reordering is NOT allowed

---

## What Was Wrong in Your Original Code

Let’s fix the conceptual issues first:

1. ❌ `&&`, `true`, `false` → **C++ syntax**
2. ❌ Nested loops are unnecessary
3. ❌ Index usage is incorrect (`s[j]`, `t[i]`)
4. ❌ Logic breaks subsequence definition
5. ❌ Extra frequency map is NOT needed

This problem does **not require frequency counting**.

---

## Approach 1 — Brute Force (Naive)

### Idea

For each character in `s`, search it sequentially in `t` **after the last matched position**.

---

### Algorithm

1. Maintain pointer `j` for string `t`
2. For each character in `s`:

   * Move `j` forward until match found
   * If not found → return False
3. If all characters matched → True

---

### Python Code (Brute Force)

```python
class Solution:
    def isSubsequence(self, s: str, t: str) -> bool:
        j = 0

        for i in range(len(s)):
            found = False
            while j < len(t):
                if s[i] == t[j]:
                    found = True
                    j += 1
                    break
                j += 1

            if not found:
                return False

        return True
```

---

### Complexity

```
Time:  O(n * m)   (worst case)
Space: O(1)
```

---

## Approach 2 — Optimized Two Pointer (Best Solution)

This is the **canonical solution**.

---

## Key Insight

You only need:

* One pointer on `s`
* One pointer on `t`

Move forward greedily.

---

## Algorithm (Two Pointer)

1. Initialize:

   ```
   i = 0  # pointer for s
   j = 0  # pointer for t
   ```

2. While `i < len(s)` and `j < len(t)`:

   * If characters match → move `i`
   * Always move `j`

3. At the end:

   * If `i == len(s)` → True
   * Else → False

---

## Python Code — Two Pointer (O(1) Space)

```python
class Solution:
    def isSubsequence(self, s: str, t: str) -> bool:
        i, j = 0, 0

        while i < len(s) and j < len(t):
            if s[i] == t[j]:
                i += 1
            j += 1

        return i == len(s)
```

---

## Dry Run

### Input

```
s = "abc"
t = "ahbgdc"
```

### Pointer Movement

```
a == a → i=1, j=1
h != b → j++
b == b → i=2, j++
g != c → j++
d != c → j++
c == c → i=3
```

`i == len(s)` → True

---

## Time & Space Complexity (Optimal)

```
Time:  O(n + m)
Space: O(1)
```
---
