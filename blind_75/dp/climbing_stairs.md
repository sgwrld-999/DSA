# Interview Script — Climbing Stairs (DP + Optimization)

## 1. Opening

**“Let me restate the problem.”**

We are given an integer `n`, representing the number of steps.

At each step, we can either:

* climb **1 step**
* or climb **2 steps**

We need to find:

> the total number of distinct ways to reach the top

---

## 2. Intuition

**“At any step `n`, I have only two choices.”**

To reach step `n`, I can:

* come from step `n-1` (by taking 1 step)
* come from step `n-2` (by taking 2 steps)

So:

> ways(n) = ways(n-1) + ways(n-2)

---

## 3. Recognizing the pattern

**“This is exactly the Fibonacci pattern.”**

Each state depends on the previous two states.

---

## 4. Recursive idea (Top-down DP)

**“Let me first explain the recursive thinking.”**

```python
def find_ways(self, n):
```

### Base cases

```python
if n == 1: return 1
if n == 2: return 2
```

* 1 step → only 1 way
* 2 steps → (1+1, 2) → 2 ways

---

### Memoization check

```python
if self._dp[n] != -1:
    return self._dp[n]
```

**“If I already computed this state, I reuse it.”**

---

### Recursive relation

```python
self._dp[n] = self.find_ways(n-1) + self.find_ways(n-2)
```

---

### Return result

```python
return self._dp[n]
```

---

## 5. Problem with recursion

**“Recursive solution works, but it has overhead.”**

* recursion stack
* repeated function calls

So we optimize using **tabulation (bottom-up DP)**

---

## 6. Optimized approach (Tabulation)

```python
def find_ways_optimise(self, n):
```

### Idea

**“Instead of going top-down, I build the solution from bottom.”**

---

### Loop

```python
for i in range(3, n+1):
    self._dp[i] = self._dp[i-1] + self._dp[i-2]
```

**“Each state depends only on previous two values.”**

---

### Return

```python
return self._dp[n]
```

---

## 7. Main function

```python
def climbStairs(self, n):
```

### Base cases

```python
if n == 1: return 1
if n == 2: return 2
```

---

### DP initialization

```python
self._dp = [-1] * (n+1)
self._dp[0] = 0
self._dp[1] = 1
self._dp[2] = 2
```

---

### Compute answer

```python
self.find_ways_optimise(n)
return self._dp[n]
```

---

## 8. How to explain in interview

You can say:

**“To reach step `n`, I can either come from `n-1` or `n-2`, so the recurrence is sum of both.”**

**“I first solve it using recursion with memoization, then optimize it using tabulation to remove recursion overhead.”**

---

## 9. Dry run

### Example: n = 5

```
dp[1] = 1
dp[2] = 2

dp[3] = 3
dp[4] = 5
dp[5] = 8
```

Answer = **8**

---

## 10. Complexity

### Time complexity

**O(n)**
We compute each state once

---

### Space complexity

**O(n)**
Using DP array

---

## 11. Further optimization (Most important follow-up)

**“We can reduce space to O(1)”**

Because we only need last two values

```python
def climbStairs(self, n):
    if n <= 2:
        return n

    prev2 = 1
    prev1 = 2

    for i in range(3, n+1):
        curr = prev1 + prev2
        prev2 = prev1
        prev1 = curr

    return prev1
```

---

## 12. Why this works

**“Each step depends only on the last two steps, so we don’t need full DP array.”**

---

## 13. Brute → Optimized thinking

**“Initially, I think recursively: try all possibilities.”**

→ leads to overlapping subproblems
→ use memoization

Then:

→ remove recursion
→ use tabulation

Then:

→ optimize space to O(1)

---

## 14. 30-second polished answer

**“This is a classic DP problem where each state depends on the previous two states, similar to Fibonacci. I can solve it using recursion with memoization, then optimize it using bottom-up DP in O(n) time. Further, I can reduce space to O(1) by keeping only the last two values.”**

---

## 15. 10-second answer

**“Number of ways = ways(n-1) + ways(n-2), solved using DP.”**

---

## 16. Nice closing line

**“The key insight is recognizing the Fibonacci pattern and optimizing it step by step from recursion to constant space.”**

---
