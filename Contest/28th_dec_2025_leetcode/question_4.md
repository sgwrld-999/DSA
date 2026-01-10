## Goal (short)

For a number of fixed length `n`, we want the number of ways to choose digits so that

```
sum(digits at odd positions) = sum(digits at even positions).
```

Each digit is independently in `[0..9]`. So, for the remaining `r_odd` odd-position digits we need a certain sum `S`, and for the remaining `r_even` even-position digits we need the same sum `S`. The dp table precomputes “how many ways to get sum `j` using `i` free digits (each 0..9)”.

---

## The dp definition and recurrence (intuitive)

Let `dp[i][j]` = number of ways to pick **i digits** (order matters, each digit 0..9) so that their sum equals `j`.

Base case:

* `dp[0][0] = 1` (zero digits sum to 0 in exactly one way),
* `dp[0][j>0] = 0`.

Now imagine you want `dp[i][j]`. Pick the first digit `k` (it can be `0..9`), then you must make the remaining `i-1` digits sum to `j-k`. So you sum over all possible `k`:

[
\boxed{dp[i][j] = \sum_{k=0}^{9} dp[i-1][,j-k,] \quad\text{(with }dp[*][x]=0\text{ if }x<0\text{)}}
]

That is exactly what the code implements with the triple loop:

```cpp
for (i = 1..8)
  for (j = 0..72)
    for (k = 0..9 && k <= j)
      dp[i][j] += dp[i-1][j-k];
```

This is simply counting all i-digit sequences whose digits sum to j.

**Small example.**
`dp[1][x] = 1` for 0 ≤ x ≤ 9 (only the single digit x).
`dp[2][3]` counts ordered pairs `(a,b)` with `0≤a,b≤9` and `a+b=3`. Those are `(0,3),(1,2),(2,1),(3,0)` → `dp[2][3]=4`. Using the recurrence:
`dp[2][3] = sum_{k=0..3} dp[1][3-k] = dp[1][3]+dp[1][2]+dp[1][1]+dp[1][0] = 1+1+1+1 = 4`.

---

## How `dp` is used in the prefix traversal (`func(high)`)

When counting numbers ≤ `high` you traverse digits from most-significant to least-significant (the digit-DP standard pattern). At each position `i` you consider choosing a digit `cur` smaller than the digit in `high` at that position: if you place `cur` there, the remaining positions to the right can be *any* digits (subject to eventual balance). For those remaining positions we use the precomputed `dp` to count how many completions produce `sum_odd == sum_even`.

Important idea: we maintain `oddsum` and `evensum` as the sums contributed by the prefix we already fixed (the digits to the left). Suppose after fixing the prefix (and picking `cur` at i) we have

* `oddremaining` free odd-position digits left,
* `evenremaining` free even-position digits left,
* current partial sums `oddsum` and `evensum`.

To end up balanced we need a target `T` such that:

* the odd positions total = `T`,
* the even positions total = `T`.

That requires the remaining odd digits to contribute `T - oddsum`, and the remaining even digits to contribute `T - evensum`. The number of ways to do that (for a given `T`) equals:

[
dp[oddremaining][T - oddsum] \times dp[evenremaining][T - evensum]
]

So you loop `T` from `max(oddsum, evensum)` up to the maximum possible sum, and sum the product for every `T`. That gives the number of completions after placing that `cur` digit.

This is exactly this code fragment:

```cpp
for (cur = 0 .. s[i]-'0' - 1) {
  for (targetsum = max(oddsum, evensum) .. 72) {
    ans += dp[oddremaining][targetsum - oddsum] * dp[evenremaining][targetsum - evensum];
  }
  // then update oddsum/evensum if we would actually put digit s[i] and continue prefix
}
```

---

## Where the `oddremaining` / `evenremaining` formulas come from

For a number of length `n`:

* total odd positions = `totOdd = (n + 1) / 2`  (1-based positions: 1,3,5,...),
* total even positions = `totEven = n / 2`.

When you are at index `i` (0-based) and about to decide the digit for position `i`, you are effectively fixing the prefix up to `i`. After placing a digit at index `i` (either a smaller `cur` or equal and continuing), the number of *remaining* odd/even positions to the right depends on how many odd/even positions were already used in the prefix. The code uses integer division formulas that are the same as the natural `total - fixed` expression; they were chosen to be concise and correct with integer truncation in C++:

```cpp
oddremaining  = s.size()/2 - (i+1)/2;
evenremaining = (s.size()+1)/2 - (i/2 + 1);
```

You can rewrite the logic more readably as:

```cpp
int n = s.size();
int totOdd = (n + 1) / 2;   // number of odd positions in the whole number
int totEven = n / 2;        // number of even positions in the whole number

int oddFixed  = (i+1 + 1) / 2; // ceil((i+1)/2) -> how many odd positions among prefix of length i+1
int evenFixed = (i+1) / 2;     // floor((i+1)/2) -> how many even positions among prefix of length i+1

oddremaining  = totOdd - oddFixed;
evenremaining = totEven - evenFixed;
```

(These two forms are algebraically equivalent to the code’s shorter integer-div formulas.)

Example: `n = 5` (positions 1..5), at `i = 1` (we fixed positions 0 and 1)

* `totOdd = 3`, `totEven = 2`
* `oddFixed = ceil(2/2)=1`, `evenFixed = floor(2/2)=1`
* `oddremaining = 3-1=2`, `evenremaining = 2-1=1`.

---

## Why multiply `dp[oddremaining][...] * dp[evenremaining][...]`?

Because choices for odd-position digits are independent from choices for even-position digits. For a fixed `T`:

* there are `A = dp[oddremaining][T - oddsum]` ways to pick odd-position remaining digits,
* and `B = dp[evenremaining][T - evensum]` ways to pick even-position remaining digits.
  Every choice from the first group pairs with every choice from the second group → `A * B` total completions with final target `T`.

---

## The `targetsum` loop lower bound = `max(oddsum, evensum)`

If `T < oddsum` then `T - oddsum` is negative and there are 0 ways (we skip those by indexing check). Similarly for `T < evensum`. So the minimal `T` that could possibly work is `max(oddsum, evensum)`. The upper bound is `9 * max(oddremaining, evenremaining)` but code uses 72 (safe maximum) since with up to 8 digits on one side 9*8 = 72.

---

## Why dp dimensions are `[9][73]`

* Maximum number of digits per parity (when total length ≤ 15) is 8 (e.g., if n=15 then one parity gets 8). So `i` up to 8 → they use 9 rows.
* Maximum sum per side with 8 digits is `8 * 9 = 72`. So `j` up to 72 → they use 73 columns (0..72).

---

## Final check & counting numbers in range

`func(high)` counts numbers in `[0, high]` satisfying the balance condition (the digit-by-digit prefix iteration with `dp` counts exactly those). Then the answer for `[low, high]` is `func(high) - func(low - 1)`.

One small caveat: the problem requires numbers to have **at least two digits**. The implemented logic typically treats shorter numbers as if they had leading zeros (digit-DP style). Leading zeros may or may not produce unwanted single-digit counts; in practice you must ensure single-digit numbers are excluded (e.g., by subtracting them explicitly or by building the DP to ignore 1-digit numbers). The code you posted counts correctly for typical inputs because single-digit numbers cannot satisfy sum(odd) == sum(even) unless both sums are zero with leading zeros — check and adjust if you need strict exclusion. (This is easy to patch if needed.)

---

## TL;DR step-by-step

1. `dp[i][j]` counts ways to get sum `j` using `i` digits each `0..9`.
   Recurrence: `dp[i][j] = sum_{k=0..9} dp[i-1][j-k]` because you choose the first digit `k` and count completions.

2. While iterating digits of `high`, for each prefix and for each smaller `cur` at current position:

   * compute how many odd/even positions remain,
   * loop target sums `T` (≥ current partial sums),
   * add `dp[oddremaining][T - oddsum] * dp[evenremaining][T - evensum]` to the answer.

3. Do this for `high` and `low-1` and subtract.

---

Great — let’s do a **fully concrete, step-by-step worked example** and *explicitly show how the recurrence is used during prefix traversal*. I’ll keep it slow and mechanical so you can internalize *how the recurrence is formed and why it fits perfectly here*.

---

# Part A — Build intuition for the recurrence `dp[i][j]`

## Step 1: What are we really counting?

Forget the original problem for a moment.

> **Question:**
> How many ways can I choose `i` digits (each from 0 to 9) such that their **sum is exactly `j`**?

That’s it. That’s the entire DP.

---

## Step 2: Define the state

We define:

```
dp[i][j] = number of ways to choose i digits whose sum is j
```

Digits are **ordered** and **independent** (important).

---

## Step 3: Base case

If we choose **zero digits**:

* sum 0 → exactly 1 way (choose nothing)
* sum > 0 → impossible

```
dp[0][0] = 1
dp[0][j>0] = 0
```

---

## Step 4: Derive the recurrence (this is the key learning)

Suppose we want `dp[i][j]`.

Think like this:

> “What can the **first digit** be?”

It can be any `k ∈ [0..9]`.

If the first digit is `k`, then the **remaining `i−1` digits must sum to `j−k`**.

So:

```
dp[i][j]
= dp[i−1][j−0]   // first digit = 0
+ dp[i−1][j−1]   // first digit = 1
+ ...
+ dp[i−1][j−9]   // first digit = 9
```

Mathematically:

```
dp[i][j] = Σ dp[i−1][j−k]   for k = 0..9
```

❗ If `j−k < 0`, that term contributes 0.

That is **the recurrence**.

---

## Step 5: Verify with a tiny example

### Example: `dp[2][3]`

How many 2-digit sequences sum to 3?

Valid pairs:

```
(0,3), (1,2), (2,1), (3,0)
```

Answer = 4

Using recurrence:

```
dp[2][3]
= dp[1][3] + dp[1][2] + dp[1][1] + dp[1][0]
= 1 + 1 + 1 + 1
= 4
```

✅ Perfect match.

---

# Part B — Why this recurrence fits the **balanced number** problem

Now we return to the real problem.

## Balanced condition

```
sum(odd positions) = sum(even positions)
```

Suppose we already fixed some prefix digits.
We now have:

* `oddremaining` digits left in odd positions
* `evenremaining` digits left in even positions
* current partial sums:

  ```
  oddsum, evensum
  ```

Let the **final target sum** be `T`.

Then:

```
remaining odd digits must sum to   T − oddsum
remaining even digits must sum to  T − evensum
```

---

## Counting completions

Number of ways:

```
dp[oddremaining][T − oddsum] × dp[evenremaining][T − evensum]
```

Why multiply?

Because:

* odd-position choices are independent of even-position choices
* for each odd choice, all even choices are valid

This is basic **combinatorial product rule**.

---

# Part C — Full worked example (important)

Let’s compute:

```
Count balanced numbers ≤ 321
```

---

## Step 1: Pre-facts

Number `321` has **3 digits**.

Positions:

```
1 (odd), 2 (even), 3 (odd)
```

So:

```
total odd positions  = 2
total even positions = 1
```

---

## Step 2: Traverse digits left to right

We iterate digit by digit.

---

### 🔹 Position 0 (digit '3')

Current:

```
oddsum = 0
evensum = 0
```

We try digits **less than 3** → `cur = 0,1,2`

After placing one digit, remaining positions:

```
oddremaining  = 1
evenremaining = 1
```

---

#### Case: `cur = 0` at pos 0

No sum change yet (pos 1 is odd, but digit is 0).

Now we count completions.

Loop target sum `T`.

Example: `T = 0`

```
odd side:  dp[1][0 - 0] = dp[1][0] = 1
even side: dp[1][0 - 0] = dp[1][0] = 1
ways = 1 × 1 = 1
```

Example: `T = 1`

```
dp[1][1] × dp[1][1] = 1 × 1 = 1
```

…

Example: `T = 9`

```
dp[1][9] × dp[1][9] = 1 × 1 = 1
```

Total contributions from `cur = 0`:

```
10
```

---

#### Case: `cur = 1`

Now:

```
oddsum = 1
```

Remaining:

```
oddremaining = 1
evenremaining = 1
```

Target sum must satisfy:

```
T ≥ max(oddsum, evensum) = 1
```

Example: `T = 1`

```
dp[1][1−1] × dp[1][1−0]
= dp[1][0] × dp[1][1]
= 1 × 1 = 1
```

Example: `T = 2`

```
dp[1][1] × dp[1][2] = 1 × 1 = 1
```

…

Up to `T = 9`.

Total again = 9

---

#### Case: `cur = 2`

Same logic → total = 8

---

### 🔹 Move to next digit (`cur = 3` matches prefix)

We update:

```
oddsum = 3
```

Continue to next digit.

---

### 🔹 Position 1 (digit '2', even position)

Try digits `< 2`: `cur = 0,1`

Remaining positions:

```
oddremaining = 1
evenremaining = 0
```

Now **only odd side remains**.

For balance:

```
T − oddsum must equal 0
⇒ T = oddsum
```

So we count:

```
dp[1][T − oddsum] × dp[0][0]
```

Each valid odd digit that equals the current even sum contributes.

---

### 🔹 Final digit

Finally, if the full number equals `321` and

```
oddsum == evensum
```

we add 1.

---

# Part D — Why the DP size and limits make sense

* Max digits per parity ≤ 8
* Max sum = `8 × 9 = 72`

Thus:

```
dp[9][73]
```

---

# Final mental model (important)

### The recurrence exists because:

> Any digit sum problem is solved by fixing the first digit and solving the rest.

### The multiplication exists because:

> Odd-position choices and even-position choices are independent.

### The prefix loop exists because:

> We count numbers ≤ R by enumerating the first position where they differ.

---

# STAGE 1 — Pure Recursion (No DP)

## Problem (reduced)

> You are given `digitsRemaining`.
> Each digit can be from `0` to `9`.
> Count how many ways you can pick digits such that their sum equals `requiredSum`.

---

## Recursive Definition

### Function meaning

```
countWays(digitsRemaining, requiredSum)
```

### Base cases

* If `digitsRemaining == 0`:

  * If `requiredSum == 0` → return 1
  * Else → return 0

### Recursive choice

Try all digits `d` from `0` to `9`.

---

## Pure Recursive Code

```cpp
long long countWays(int digitsRemaining, int requiredSum) {
    // Base case
    if (digitsRemaining == 0) {
        return (requiredSum == 0);
    }

    long long totalWays = 0;

    // Try all possible digits
    for (int digit = 0; digit <= 9; digit++) {
        if (requiredSum - digit >= 0) {
            totalWays += countWays(
                digitsRemaining - 1,
                requiredSum - digit
            );
        }
    }

    return totalWays;
}
```

---

## What this recursion means

* Fix one digit
* Recursively solve for remaining digits
* Sum all possibilities

❌ Exponential time
✔ Conceptually clean

---

# STAGE 2 — Recursion + Memoization

## Observation

The same states:

```
(digitsRemaining, requiredSum)
```

are computed again and again.

So we **cache** them.

---

## Memo Table Meaning

```
memo[digitsRemaining][requiredSum]
```

---

## Memoized Code

```cpp
long long memo[9][73];

long long countWaysMemo(int digitsRemaining, int requiredSum) {
    // Base case
    if (digitsRemaining == 0) {
        return (requiredSum == 0);
    }

    // If already computed
    if (memo[digitsRemaining][requiredSum] != -1) {
        return memo[digitsRemaining][requiredSum];
    }

    long long totalWays = 0;

    for (int digit = 0; digit <= 9; digit++) {
        if (requiredSum - digit >= 0) {
            totalWays += countWaysMemo(
                digitsRemaining - 1,
                requiredSum - digit
            );
        }
    }

    memo[digitsRemaining][requiredSum] = totalWays;
    return totalWays;
}
```

---

## Why this is fast

* States = `8 × 72 = 576`
* Each computed once
* Time = O(states × 10)

✔ Efficient
✔ Same logic as recursion

---

# STAGE 3 — Tabulation (Bottom-Up DP)

Now we **remove recursion entirely**.

---

## DP Definition (same meaning)

```
dp[numberOfDigits][sum]
```

---

## Step 1: Initialize base case

```cpp
dp[0][0] = 1;
```

---

## Step 2: Fill the table

```cpp
for (int digits = 1; digits <= 8; digits++) {
    for (int currentSum = 0; currentSum <= 72; currentSum++) {
        dp[digits][currentSum] = 0;

        for (int digit = 0; digit <= 9; digit++) {
            if (currentSum - digit >= 0) {
                dp[digits][currentSum] +=
                    dp[digits - 1][currentSum - digit];
            }
        }
    }
}
```

---

## Final Tabular Code

```cpp
long long dp[9][73];

void buildDP() {
    memset(dp, 0, sizeof(dp));

    dp[0][0] = 1;

    for (int digits = 1; digits <= 8; digits++) {
        for (int currentSum = 0; currentSum <= 72; currentSum++) {
            for (int digit = 0; digit <= 9; digit++) {
                if (currentSum - digit >= 0) {
                    dp[digits][currentSum] +=
                        dp[digits - 1][currentSum - digit];
                }
            }
        }
    }
}
```

---

# Mental Mapping (IMPORTANT)

| Concept      | Recursion                | Memoization  | Tabulation |
| ------------ | ------------------------ | ------------ | ---------- |
| State        | `(digitsRemaining, sum)` | Same         | Same       |
| Transition   | Try digits 0–9           | Same         | Same       |
| Optimization | None                     | Cache        | Precompute |
| Core idea    | Fix first digit          | Reuse result | Bottom-up  |

---

# How this fits into the main problem

When counting balanced numbers:

* Odd-position digits → `countWays(oddRemaining, targetSum - oddSum)`
* Even-position digits → `countWays(evenRemaining, targetSum - evenSum)`
* Multiply the results

---

