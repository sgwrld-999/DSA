Perfect, this is **Best Time to Buy and Sell Stock (LeetCode 121)**.
I’ll explain it **slowly, like a teacher to a student**, build intuition step by step, convert **all approaches to Python**, include **dry runs**, and end with **clean summaries**.

---

# Best Time to Buy and Sell Stock (LeetCode 121)

## Problem in one line

You are given an array `prices` where `prices[i]` is the price of a stock on day `i`.
You are allowed to **buy once and sell once**, and you must **buy before you sell**.
Return the **maximum profit** you can achieve. If no profit is possible, return `0`.

---

## Fundamental Observation (MOST IMPORTANT)

👉 You are **not** choosing two arbitrary days.
👉 You are choosing:

* **One day to buy** (minimum so far)
* **One future day to sell** (maximum difference with that minimum)

So the problem reduces to:

> “For every day, what is the **best day before it** to buy?”

---

# 🔹 Approach 1: Brute Force (Try All Buy–Sell Pairs)

## Thought Process (Human Explanation)

Let’s think very naively.

* If I buy on day `i`
* I can sell only on days `j > i`
* Profit = `prices[j] - prices[i]`
* Try **all possible pairs**
* Track the maximum profit

This guarantees correctness but is **slow**.

---

## Python Code (Brute Force)

```python
class Solution:
    def maxProfit(self, prices: list[int]) -> int:
        n = len(prices)
        max_profit = 0

        for i in range(n):
            for j in range(i + 1, n):
                profit = prices[j] - prices[i]
                max_profit = max(max_profit, profit)

        return max_profit
```

---

## Dry Run

```
prices = [7,1,5,3,6,4]
```

| Buy Day | Sell Day | Profit |
| ------- | -------- | ------ |
| 7       | 1        | -6     |
| 1       | 5        | 4      |
| 1       | 6        | 5 ✅    |
| 3       | 6        | 3      |

Final Answer = **5**

---

## Complexity

* **Time:** `O(n²)` ❌
* **Space:** `O(1)`

---

## Summary

✅ Easy to understand
❌ Too slow for large inputs
❌ Will cause TLE

---

# 🔹 Approach 2: Prefix Min & Suffix Max (Preprocessing)

## Key Observation

For any day `i`:

* Best buying price = **minimum price before or on day `i`**
* Best selling price = **maximum price after or on day `i`**

So:

```
profit at i = max_after_i - min_before_i
```

---

## Thought Process (Teacher Explanation)

Instead of recomputing min and max repeatedly:

* Precompute:

  * `mini[i]` → minimum price from day `0` to `i`
  * `maxi[i]` → maximum price from day `i` to `n-1`
* Then calculate profit for each day

---

## Python Code (Prefix–Suffix)

```python
class Solution:
    def maxProfit(self, prices: list[int]) -> int:
        n = len(prices)
        if n == 0:
            return 0

        mini = [0] * n
        maxi = [0] * n

        mini[0] = prices[0]
        for i in range(1, n):
            mini[i] = min(mini[i - 1], prices[i])

        maxi[n - 1] = prices[n - 1]
        for i in range(n - 2, -1, -1):
            maxi[i] = max(maxi[i + 1], prices[i])

        profit = 0
        for i in range(n):
            profit = max(profit, maxi[i] - mini[i])

        return profit
```

---

## Dry Run

```
prices = [7,1,5,3,6,4]
```

### mini array:

```
[7,1,1,1,1,1]
```

### maxi array:

```
[6,6,6,6,4,4]
```

### Profit:

```
max(6-1) = 5
```

---

## Complexity

* **Time:** `O(n)`
* **Space:** `O(n)` ❌

---

## Summary

✅ Linear time
❌ Extra memory
⚠️ Not optimal but good thinking

---

# 🔹 Approach 3: Single Pass (Optimal – Expected in Interviews)

## 🔑 Core Observation (THIS IS THE KEY)

At any day:

* If today’s price is lower than all previous → **better day to buy**
* If today’s price is higher than previous minimum → **candidate for selling**

So:

* Track **minimum price so far**
* Track **maximum profit so far**

---

## Thought Process (Say This in Interview)

> “I keep track of the minimum stock price seen so far.
> For each day, I calculate the profit if I sold on that day using the previous minimum.
> I update the maximum profit and also update the minimum price if a smaller price is found.”

---

## Python Code (Most Pythonic, Optimal)

```python
class Solution:
    def maxProfit(self, prices: list[int]) -> int:
        min_price = float('inf')
        max_profit = 0

        for price in prices:
            if price < min_price:
                min_price = price
            else:
                max_profit = max(max_profit, price - min_price)

        return max_profit
```

---

## Alternative Pythonic Version (Same Logic)

```python
class Solution:
    def maxProfit(self, prices: list[int]) -> int:
        min_price = prices[0]
        profit = 0

        for price in prices[1:]:
            profit = max(profit, price - min_price)
            min_price = min(min_price, price)

        return profit
```

---

## Dry Run (VERY IMPORTANT)

```
prices = [7,1,5,3,6,4]
```

| Day | Price | Min So Far | Profit |
| --- | ----- | ---------- | ------ |
| 0   | 7     | 7          | 0      |
| 1   | 1     | 1          | 0      |
| 2   | 5     | 1          | 4      |
| 3   | 3     | 1          | 4      |
| 4   | 6     | 1          | 5 ✅    |
| 5   | 4     | 1          | 5      |

Final Answer = **5**

---

## Why This Always Works

* You **never sell before buying**
* You always compare current price with **best buying price so far**
* Single transaction guaranteed optimal

---

## Complexity

* **Time:** `O(n)` ✅
* **Space:** `O(1)` ✅

---

## Summary (Quick Revision)

| Approach      | Time  | Space | Interview |
| ------------- | ----- | ----- | --------- |
| Brute Force   | O(n²) | O(1)  | ❌         |
| Prefix–Suffix | O(n)  | O(n)  | ⚠️        |
| Single Pass   | O(n)  | O(1)  | ✅         |

---

## Final Interview One-Liner (Memorize)

> “This problem reduces to tracking the minimum price so far and computing the maximum difference with future prices in a single pass.”

---

## Pattern Recognition (IMPORTANT)

This problem teaches:

* **Prefix minimum**
* **One-pass optimization**
* **Kadane-like thinking (difference tracking)**

Appears again in:

* Maximum subarray variants
* Stock II, III, IV
* Dynamic programming on prices

---

If you want next:

* Stock II (multiple transactions)
* Kadane vs stock comparison
* Common mistakes checklist
* One-page revision notes

Just say the word.
