## Problem Summary: *Stop The Count*

* There are **N voters**, voting in order from `1` to `N`
* Votes are given as a **binary string `S`**

  * `S[i] = '1'` → vote for **Chef**
  * `S[i] = '0'` → vote for **AntiChef**
* Votes are counted **prefix-wise**
* Chef can **stop the count at any position `i`** (from `1` to `N`)
* Votes after that position are **ignored**

---

## Winning Condition

Chef **wins** if:
[
\text{ChefVotes} > \text{AntiChefVotes}
]

* **Tie is NOT a win**
* Chef may also stop after all `N` votes

---

## What Is Being Asked?

Count the **number of positions `i` (1 ≤ i ≤ N)** such that:

* Considering only the first `i` votes
* Chef has **strictly more votes** than AntiChef

Each valid `i` is a **distinct way to stop the count and win**

---

## Key Insight (Core Logic)

This is a **prefix counting problem**.

At each position `i`:

* Count number of `'1'`s → `ones`
* Count number of `'0'`s → `zeros`

If at any point:
[
\text{ones} > \text{zeros}
]
then **Chef wins by stopping here**.

So:

> **Answer = number of prefixes where ones > zeros**

---

## Code Walkthrough

### Function `solve`

```cpp
int solve(int n, string s){
    int ones = 0, zeros = 0, ways = 0;
```

* `ones` → Chef votes so far
* `zeros` → AntiChef votes so far
* `ways` → valid stopping points

---

```cpp
for(int i = 0; i < n; i++){
```

* Traverse votes **from left to right**
* This corresponds to stopping after voter `i+1`

---

```cpp
if(s[i] == '1') ones++;
else zeros++;
```

* Update vote counts for current prefix

---

```cpp
if(ones > zeros)
    ways++;
```

* If Chef is currently winning
* This position is a **valid way to stop**

---

```cpp
return ways;
```

* Total number of winning stopping positions

---

## `main()` Function

```cpp
int t;
cin >> t;
```

* Number of test cases

```cpp
while(t--){
    int n;
    string s;
    cin >> n >> s;
    cout << solve(n, s) << endl;
}
```

* Solve each test case independently

---

## Sample Case Analysis

### Test Case 1

```
N = 3
S = "111"
```

| Prefix | ones | zeros | Chef wins? |
| ------ | ---- | ----- | ---------- |
| 1      | 1    | 0     | Yes        |
| 11     | 2    | 0     | Yes        |
| 111    | 3    | 0     | Yes        |

**Answer = 3**

---

### Test Case 2

```
N = 3
S = "000"
```

| Prefix | ones | zeros | Chef wins? |
| ------ | ---- | ----- | ---------- |
| 0      | 0    | 1     | No         |
| 00     | 0    | 2     | No         |
| 000    | 0    | 3     | No         |

**Answer = 0**

---

### Test Case 3

```
N = 5
S = "10011"
```

| Prefix | ones | zeros | Chef wins? |
| ------ | ---- | ----- | ---------- |
| 1      | 1    | 0     | Yes        |
| 10     | 1    | 1     | No         |
| 100    | 1    | 2     | No         |
| 1001   | 2    | 2     | No         |
| 10011  | 3    | 2     | Yes        |

**Answer = 2**

---

## Why This Approach Is Optimal

* Only **one pass** through the string
* No extra memory
* No nested loops

### Complexity

* **Time:** `O(N)` per test case
* **Space:** `O(1)`

---

## Conceptual Takeaway

This problem is about:

* **Prefix dominance**
* Not total counts
* Each prefix represents a **decision point**

> Count how many prefixes satisfy a winning condition.

This pattern appears frequently in:

* Voting problems
* Running balances
* Prefix sums
* Greedy decision points

---
