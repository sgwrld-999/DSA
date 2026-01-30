# Happy Number (HashMap / Cycle Detection)

## Problem in one line

Given a number `n`, repeatedly replace it with the **sum of squares of its digits**.
If this process **eventually reaches 1**, the number is happy; otherwise, it enters a loop.

---

## Core idea

> A number is **not happy** if the sequence of computed values **starts repeating**.

Repetition means:

* The process has entered a **cycle**
* It will **never reach 1**

---

## Why HashMap / Set is used

This is a **cycle detection problem**.

We store each intermediate value:

* If we ever see the same value again → loop detected → `False`
* If we reach `1` → happy number → `True`

A **set** is ideal because:

* Fast lookup `O(1)`
* We only care about existence, not counts

---

## High-level algorithm

1. Initialize an empty set `seen`
2. While the number is not `1`:

   * If the number is already in `seen`, return `False`
   * Add the number to `seen`
   * Replace the number with the sum of squares of its digits
3. If `1` is reached, return `True`

---

## Digit square computation

To compute sum of squares of digits:

* Extract digits using `% 10`
* Reduce number using `// 10`
* Square each digit and add

---

## Correct reference implementation (Python)

```python
class Solution:
    def isHappy(self, n: int) -> bool:
        seen = set()

        while n != 1:
            if n in seen:
                return False
            seen.add(n)

            new_num = 0
            while n > 0:
                digit = n % 10
                new_num += digit * digit
                n //= 10

            n = new_num

        return True
```

---

## Why this solution is correct

* Every transformation is deterministic
* Any non-happy number **must** fall into a loop
* Hashing guarantees loop detection
* Each value is processed only once

---

## Time and space complexity

* **Time Complexity:** `O(log n)` per iteration
  (number of digits is small, and sequence length is bounded)
* **Space Complexity:** `O(log n)`
  (at most a limited set of intermediate values)

---

## Common mistakes to avoid

* Using `/` instead of `//` (causes float errors)
* Forgetting to store visited values
* Using `{}` instead of `set()`
* Overcomplicating with recursion

---

## Interview takeaway

> Happy Number is **not a math problem** — it’s a **cycle detection problem**.

If you recognize:

* repetition
* infinite processes
* convergence vs loop

→ think **HashSet or Floyd’s Cycle Detection**.

---
