# Problem: Minimum Cost to Acquire Required Items (LeetCode 3789)

You are given five integers:

* `cost1`: cost of an item that contributes only to type 1
* `cost2`: cost of an item that contributes only to type 2
* `costBoth`: cost of an item that contributes to both type 1 and type 2
* `need1`: minimum required contribution for type 1
* `need2`: minimum required contribution for type 2

You must purchase items such that:

```
type1 ≥ need1
type2 ≥ need2
```

Return the **minimum total cost** required.

---

## Key Observations

1. Type 3 items are special because they contribute to **both** requirements.
2. Buying extra items beyond the requirement is allowed.
3. The constraints are large:

   * `need1, need2 ≤ 10^9`
   * So brute force or DP over counts is not feasible.
4. The decision is fundamentally **greedy**, based on cost comparisons.

---

## Core Insight

There are only two meaningful strategies:

1. **Never use type 3 items**
2. **Use type 3 items optimally**, then fill the remaining requirements with the cheapest option

The difficulty is understanding **when type 3 items are beneficial** and **how many to use**.

---

## Strategy Breakdown

### Case 1: Do not use type 3 items

Simply satisfy both requirements independently:

```
cost = need1 * cost1 + need2 * cost2
```

This is always a valid baseline answer.

---

### Case 2: Use type 3 items

Type 3 items behave differently in two phases.

---

### Phase 1: Satisfy both requirements together

Each type 3 item contributes:

```
+1 to type1
+1 to type2
```

So we can use at most:

```
both = min(need1, need2)
```

Cost:

```
both * costBoth
```

After this:

```
need1 -= both
need2 -= both
```

---

### Phase 2: Satisfy remaining requirements

At this point, only **one side (or both)** may still need items.

For remaining `need1`:

* Either buy type 1 items
* Or buy type 3 items (even though type 2 is already satisfied)

Choose the cheaper option:

```
min(need1 * cost1, need1 * costBoth)
```

Similarly for remaining `need2`:

```
min(need2 * cost2, need2 * costBoth)
```

---

## Final Answer

Take the minimum of:

* Cost without type 3 items
* Cost with optimal usage of type 3 items

---

## Correct Code

```cpp
class Solution {
public:
    long long minimumCost(int cost1, int cost2, int costBoth,
                          int need1, int need2) {

        long long ans = LLONG_MAX;

        // Case 1: Never use type-3 items
        ans = 1LL * need1 * cost1 + 1LL * need2 * cost2;

        // Case 2: Use type-3 items optimally
        long long both = min(need1, need2);
        long long cost = 0;

        // Phase 1: satisfy both needs together
        cost += 1LL * both * costBoth;
        need1 -= both;
        need2 -= both;

        // Phase 2: satisfy remaining needs optimally
        cost += min(
            1LL * need1 * cost1,
            1LL * need1 * costBoth
        );

        cost += min(
            1LL * need2 * cost2,
            1LL * need2 * costBoth
        );

        ans = min(ans, cost);

        return ans;
    }
};
```

---

## Dry Run Example 1

**Input**

```
cost1 = 3, cost2 = 2, costBoth = 1
need1 = 3, need2 = 2
```

**Process**

```
both = 2
cost = 2 * 1 = 2
remaining need1 = 1
remaining need2 = 0

remaining cost1:
min(1*3, 1*1) = 1

total cost = 3
```

**Output**

```
3
```

---

## Dry Run Example 2

**Input**

```
cost1 = 5, cost2 = 4, costBoth = 15
need1 = 2, need2 = 3
```

**Observation**

```
costBoth > cost1 + cost2
```

So type 3 is never useful.

**Cost**

```
2*5 + 3*4 = 22
```

---

## Edge Cases

1. `need1 = 0` and `need2 = 0`

   * Answer is `0`
2. One requirement is zero

   * Type 3 may still be cheaper than the single-type item
3. Large values

   * All calculations must use `long long` to avoid overflow

---

## Common Mistakes

1. Assuming type 3 items can be used only up to `min(need1, need2)`
2. Ignoring that type 3 items may still be cheaper even after one side is satisfied
3. Trying brute force over number of type 3 items
4. Using `int` instead of `long long`

---

## Time and Space Complexity

* Time Complexity: `O(1)`
* Space Complexity: `O(1)`

---

## Key Takeaway

This problem is a greedy optimization problem with **two phases**:

* First, use type 3 items to cover both needs
* Then, for leftover requirements, choose the cheapest per-unit option

Once this two-phase behavior is understood, the solution becomes straightforward and efficient.
