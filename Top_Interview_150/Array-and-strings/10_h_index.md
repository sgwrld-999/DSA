# H-Index — Full Explanation

---

## Problem Restatement (Simplified)

You are given:

* An array **C** of size **N**
* Each element **Cᵢ** represents the number of citations of the *i-th* paper
* `0 ≤ Cᵢ`

### Definition (H-Index)

The **H-index** is the **maximum integer `h`** such that:

* At least **`h` papers** have **`≥ h` citations** each

---

### Task

Compute and return the **H-index** of the given citations array.

---

## Key Observations

---

## 1. What does the H-Index actually measure?

The H-index is **not**:

* Maximum citations
* Average citations
* Count of papers with high citations

Instead, it is a **balance point**.

Formally, define:
[
f(h) = \text{number of papers with citations } \ge h
]

Then:
[
\boxed{
\text{H-index} = \max { h \mid f(h) \ge h }
}
]

---

## 2. Why brute force works — and why it is inefficient

### Brute Force Idea

For every `h` from `0` to `N`:

1. Count papers with citations ≥ `h`
2. If `count ≥ h`, `h` is valid
3. Take the maximum such `h`

### Complexity

* Each `h` → full scan of array
* Total:
  [
  O(N^2)
  ]

Correct, but wasteful.

---

## 3. Critical Insight — Monotonicity

Consider:
[
f(h) = \text{number of papers with citations } \ge h
]

### Property

As `h` increases:

* `f(h)` **never increases**
* It can only **stay same or decrease**

Reason:

> Increasing the requirement cannot increase qualifying papers.

This monotonic behaviour is the **key to optimisation**.

---

## 4. Why the H-Index has only one valid “breaking point”

We check:
[
f(h) \ge h
]

* Left side (`f(h)`) → decreasing
* Right side (`h`) → increasing

Once this condition fails, it **can never become true again**.

So:

* Valid `h` values form a prefix
* The H-index is the **largest valid `h`**

---

## 5. Upper Bound on H-Index

[
\boxed{h \le N}
]

Because:

* You cannot have more than `N` papers
* Citations beyond `N` behave the same for H-index

So we safely **cap all citations at `N`**.

---

## 6. Optimal Counting (Bucket) Strategy

### Core Idea

Instead of recomputing `f(h)` every time:

* Count how many papers have **exactly `c` citations**
* Use a frequency array

Define:

```
freq[i] = number of papers with exactly i citations
```

Any citation ≥ `N` is added to `freq[N]`.

---

## 7. Computing H-Index Using Buckets

Algorithm:

1. Build `freq[0…N]`
2. Initialise `papers = 0`
3. Traverse `h` from `N → 0`

   * `papers += freq[h]`
   * If `papers ≥ h`, return `h`

This finds the **maximum valid `h`** directly.

---

## 8. Dry Run (Step-by-Step)

### Input

```
citations = [3, 0, 6, 1, 5]
N = 5
```

---

### Step 1: Build frequency array

```
freq size = 6 (0 to 5)
```

Process citations:

| Citation | Action    | freq state    |
| -------- | --------- | ------------- |
| 3        | freq[3]++ | [0,0,0,1,0,0] |
| 0        | freq[0]++ | [1,0,0,1,0,0] |
| 6        | freq[5]++ | [1,0,0,1,0,1] |
| 1        | freq[1]++ | [1,1,0,1,0,1] |
| 5        | freq[5]++ | [1,1,0,1,0,2] |

Final:

```
index: 0 1 2 3 4 5
freq : 1 1 0 1 0 2
```

---

### Step 2: Traverse from highest `h`

| h | papers (≥ h) | Check   |
| - | ------------ | ------- |
| 5 | 2            | 2 < 5 ❌ |
| 4 | 2            | 2 < 4 ❌ |
| 3 | 3            | 3 ≥ 3 ✅ |

✔ Return **3**

---

### Final Answer

```
H-index = 3
```

---

## 9. Your Common Doubts — Explained Clearly

---

### Doubt 1: “Why are we iterating over `h` again?”

✔ We are **not recomputing** anything.

* Brute force recalculates `f(h)` every time
* Bucket method **reuses previous counts**
* Each paper is counted **once**

So this iteration is **O(N)**, not `O(N²)`.

---

### Doubt 2: “Why cap citations at `N`?”

Because:

* H-index ≤ number of papers
* Citations `10` and `1000` behave the same if `N = 5`
* Extra magnitude gives no additional power

---

### Doubt 3: “Why check `papers ≥ h`, not equality?”

Definition says:

> *at least* `h` papers with *at least* `h` citations

More papers is fine.
We want the **maximum valid `h`**, not an exact match.

---

### Doubt 4: “Why traverse from right to left?”

Because:

* We want the **largest possible h**
* Once condition is true, it is guaranteed optimal

---

### Doubt 5 (Your Main Logical Mistake Earlier)

❌ You were trying to **maximise the number of papers**

✔ H-index maximises the **threshold `h`**, not the count

That inversion is the biggest conceptual fix.

---

## Time and Space Complexity

| Aspect | Complexity |
| ------ | ---------- |
| Time   | **O(N)**   |
| Space  | **O(N)**   |

Optimal.

---

## Final Code (Optimal)

```cpp
class Solution {
public:
    int hIndex(vector<int>& citations) {
        int n = citations.size();
        vector<int> freq(n + 1, 0);

        for (int c : citations) {
            if (c >= n)
                freq[n]++;
            else
                freq[c]++;
        }

        int papers = 0;
        for (int h = n; h >= 0; h--) {
            papers += freq[h];
            if (papers >= h) {
                return h;
            }
        }
        return 0;
    }
};
```

---

## One-Line Takeaway

> **H-Index is the highest point where “how many papers you have” is still ≥ “how many citations you demand”.**

