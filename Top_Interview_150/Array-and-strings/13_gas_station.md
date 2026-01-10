# Gas Station — Full Explanation

---

## Problem Restatement (Simplified)

You are given:

* An integer **n**, the number of gas stations arranged in a **circular route**
* Two arrays of length **n**:

  * **gas[i]** — amount of gas available at station `i`
  * **cost[i]** — gas required to travel from station `i` to station `(i + 1) % n`
* You start with an **empty tank**
* The gas tank has **unlimited capacity**

---

### Task

Return the **unique index** of the gas station from which you can:

* Start with `0` gas
* Travel **exactly one full circle clockwise**
* Never let the gas in the tank become negative

If no such station exists, return **`-1`**.

---

## Key Observations

---

## 1. Reformulating the Problem

Instead of thinking in terms of *gas stations*, think in terms of **net gain per station**:

[
\text{net}[i] = \text{gas}[i] - \text{cost}[i]
]

At each station:

* If `net[i] > 0` → you gain fuel
* If `net[i] < 0` → you lose fuel

The journey becomes:

> Can we find a starting index such that the **cumulative sum of net values never drops below 0** while completing a full cycle?

---

## 2. Necessary Global Condition (Feasibility Check)

Let:

[
\text{Total} = \sum_{i=0}^{n-1} (\text{gas}[i] - \text{cost}[i])
]

### Why this matters

* The route is circular
* You must traverse **all stations exactly once**
* Total fuel gained must be at least the total fuel spent

---

### Case Analysis

#### If `Total < 0`

* Even with perfect starting choice
* You run out of fuel somewhere

[
\boxed{\text{No solution exists}}
]

#### If `Total ≥ 0`

* A solution **must exist**
* (Problem guarantees uniqueness)

---

### Conclusion

[
\boxed{
\text{If } \sum (\text{gas}[i] - \text{cost}[i]) < 0,\ \text{return } -1
}
]

This condition is **necessary**, not yet sufficient to find the start.

---

## 3. Brute Force Insight (Baseline Thinking)

Brute force would:

* Try starting at every station `i`
* Simulate travelling `n` steps
* Track fuel level
* Stop early if fuel becomes negative

This works logically but takes **O(n²)** time.

However, brute force reveals a **crucial pattern**.

---

## 4. Critical Greedy Insight (Why We Can Skip Starts)

Suppose:

* You start at station `s`
* While travelling, at station `k`, your fuel becomes negative

That means:

[
\sum_{i=s}^{k} (\text{gas}[i] - \text{cost}[i]) < 0
]

---

### Key Question

Can **any station between `s` and `k`** be a valid starting point?

---

### Answer: **No**

#### Reason

Starting later (say at `s + 1`) removes some prefix fuel gain, so:

[
\sum_{i=s+1}^{k} (\text{net}[i]) \le \sum_{i=s}^{k} (\text{net}[i]) < 0
]

So:

> If starting at `s` fails at `k`,
> **every start in `[s, k]` is guaranteed to fail**.

---

### This is the core greedy invariant

[
\boxed{
\text{A failure eliminates a whole range of starting positions}
}
]

---

## 5. Greedy Strategy (One-Pass Logic)

Instead of restarting simulation from each station:

* Maintain a **running fuel balance**
* Track the **current candidate start**

---

### Variables Meaning

* `total` — fuel accumulated since the current candidate start
* `res` — current candidate starting index

---

### Greedy Traversal Logic

Iterate once from `0` to `n-1`:

1. Add net fuel:
   [
   \text{total} += \text{gas}[i] - \text{cost}[i]
   ]

2. If `total < 0`:

   * Current candidate start fails
   * All stations from `res` to `i` are invalid
   * Reset:

     ```
     res = i + 1
     total = 0
     ```

---

### Why this is safe

Because of the proven invariant:

> Once a prefix sum goes negative, none of the starts within that prefix can work.

So skipping is **logically sound**, not heuristic.

---

## 6. Why Only One Pass Is Enough

Each station is:

* Added to the running sum once
* Causes at most one reset

Hence:

* No backtracking
* No repeated simulation
* Time complexity is **O(n)**

---

## 7. Final Algorithm Summary

1. Compute total net fuel

   * If negative → return `-1`
2. Initialise:

   ```
   total = 0
   res = 0
   ```
3. Traverse stations once:

   * Accumulate net fuel
   * On failure, reset candidate start
4. Return `res`

---

## Correct Code

```cpp
class Solution {
public:
    int greedySolution(vector<int>& gas, vector<int>& cost) {
        int n = gas.size();

        int totalCost = 0;
        for(int i = 0; i < n; i++) {
            totalCost += gas[i] - cost[i];
        }

        if(totalCost < 0) return -1;

        int total = 0;
        int res = 0;

        for(int i = 0; i < n; i++) {
            total += gas[i] - cost[i];
            if(total < 0) {
                total = 0;
                res = i + 1;
            }
        }

        return res;
    }
};
```

---

## Why This Works (Intuition Summary)

* The problem is about **prefix sums on a circular array**
* A negative prefix sum proves **impossibility of all earlier starts**
* Greedy skips entire invalid ranges at once
* A global fuel check ensures feasibility
* One pass is sufficient due to monotonic elimination

---

## Complexity

* **Time:** `O(n)`
* **Space:** `O(1)`

---

