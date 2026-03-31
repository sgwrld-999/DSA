# Interview Script — Coin Change 2 (DP + Optimization)

---

## 1. Opening

**“Let me restate the problem.”**

We are given:

* an array `coins[]`
* an integer `amount`

We need to find:

> the total number of ways to make the given amount using the coins

👉 Important:

* We can use a coin **unlimited times**
* Order does NOT matter (combinations, not permutations)

---

## 2. Intuition

**“At each coin, I have two choices.”**

For a coin at index `idx`, I can:

* **not take it** → move to next smaller index
* **take it** → reduce amount, stay at same index

So:

> ways(idx, target) = ways(idx-1, target) + ways(idx, target - coins[idx])

---

## 3. Recognizing the pattern

**“This is an Unbounded Knapsack pattern.”**

* Same coin can be reused → stay at same index
* We explore all combinations

---

# 4. Recursive Approach (Brute Force)

**“Let me first explain the recursive thinking.”**

```python
def f(idx, target):
```

---

### Base case

```python
if idx == 0:
    return 1 if target % coins[0] == 0 else 0
```

**“If only one coin is left, I check whether I can form the target using it.”**

---

### Choices

```python
not_take = f(idx - 1, target)

take = 0
if target >= coins[idx]:
    take = f(idx, target - coins[idx])
```

---

### Return

```python
return take + not_take
```

**“Since I need total number of ways, I sum both possibilities.”**

---

## 5. Problem with recursion

**“This solution works but has overlapping subproblems.”**

* Same `(idx, target)` computed multiple times
* Leads to exponential time

👉 So we optimize using **Memoization**

---

# 6. Memoization (Top-down DP)

```python
dp[idx][target]
```

---

### Memo check

```python
if dp[idx][target] != -1:
    return dp[idx][target]
```

**“If already computed, reuse it.”**

---

### Same recurrence

```python
dp[idx][target] = take + not_take
```

---

### Return

```python
return dp[idx][target]
```

---

## 7. Why memoization works

**“Because the problem has overlapping subproblems.”**

👉 Number of states = `n × amount`

---

# 8. Tabulation (Bottom-up DP)

**“Now I convert recursion into iteration.”**

---

### DP definition

```python
dp[idx][target] = number of ways
```

---

### Base case

```python
for target in range(amount + 1):
    dp[0][target] = 1 if target % coins[0] == 0 else 0
```

---

### Transition

```python
for idx in range(1, n):
    for target in range(amount + 1):

        not_take = dp[idx - 1][target]

        take = 0
        if target >= coins[idx]:
            take = dp[idx][target - coins[idx]]

        dp[idx][target] = take + not_take
```

---

### Return

```python
return dp[n-1][amount]
```

---

## 9. Key observation (Very Important)

**“In the take case, we stay at the same index.”**

```python
take = dp[idx][target - coins[idx]]
```

👉 Because:

> coins can be reused (unbounded)

---

# 10. Space Optimization (Most Optimized)

**“We can reduce 2D DP to 1D.”**

---

### Idea

We only need:

* current row (reuse same array)

---

### Code logic

```python
dp = [0] * (amount + 1)

# base case
for target in range(amount + 1):
    if target % coins[0] == 0:
        dp[target] = 1
```

---

### Transition

```python
for idx in range(1, n):
    for target in range(amount + 1):

        not_take = dp[target]

        take = 0
        if target >= coins[idx]:
            take = dp[target - coins[idx]]

        dp[target] = take + not_take
```

---

### Return

```python
return dp[amount]
```

---

## 11. Dry Run

### Example:

```text
coins = [1,2]
amount = 4
```

Ways:

```
1+1+1+1
1+1+2
2+2
```

Answer = **3**

---

## 12. Complexity

### Recursion

* Time: Exponential ❌

### Memoization

* Time: O(n × amount)
* Space: O(n × amount)

### Tabulation

* Time: O(n × amount)
* Space: O(n × amount)

### Optimized

* Time: O(n × amount)
* Space: O(amount) ✅

---

## 13. How to explain in interview

You can say:

**“At every coin, I decide whether to take it or skip it. Since coins can be reused, I stay at the same index in the take case. Because I need total number of ways, I sum both choices.”**

---

## 14. Brute → Optimized thinking

**“First, I try recursion (explore all ways).”**

→ overlapping subproblems
→ use memoization

→ remove recursion → tabulation

→ reduce space → 1D DP

---

## 15. 30-second polished answer

**“This is an unbounded knapsack problem where at each index I either take or skip the coin. I solve it using recursion with memoization in O(n × amount), then optimize it using bottom-up DP and finally reduce space to O(amount).”**

---

## 16. 10-second answer

**“Ways = take + not_take, solved using unbounded knapsack DP.”**

---

## 17. Closing line

**“The key insight is recognizing the unbounded knapsack pattern and optimizing step by step from recursion to 1D DP.”**

---
