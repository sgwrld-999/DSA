# Deleting Array Again
---

## What the Question REALLY Means

You are given:

* An array **A** of size `N`
* A cost array **C** of size `N`

You must perform **exactly `N` deletions**, until **A becomes empty**.

### Operation rules (very important)

1. You choose an index `i` in the **current array A**
2. You delete `A[i]`
3. The cost paid is
   [
   \text{cost} = A[i] \times C[i]
   ]
4. After deletion:

   * Array **A shrinks**
   * Elements **shift left**
   * **C does NOT change**

⚠️ **This is the key twist**:

> The index `i` refers to the *current* array `A`, but the cost multiplier `C[i]` is always taken from the **original, fixed cost array**.

---

## Intuition Behind the Problem

You are deciding the **order of deletions**.

* Every element `A[j]` will eventually be multiplied by **some `C[i]`**
* You want **large values of `A`** to get **small values of `C`**
* You want **small values of `A`** to get **large values of `C`**

This is a **re-ordering / greedy cost-minimisation problem**.

---

## Now Let Us Focus on Your Confusion

### 🔍 Sample Test Case 2

### Input

```
N = 2
A = [4, 2]
C = [1, 2]
```

---

## What You Might Be Thinking (Incorrect Intuition)

> “Why not delete `2` first with cost `2 × 2 = 4` and then `4 × 1 = 4`, total = 8?”

This **looks logical**, but **it is impossible** because of index shifting.

---

## Let Us Simulate Properly

### Initial State

| Index | A | C |
| ----- | - | - |
| 1     | 4 | 1 |
| 2     | 2 | 2 |

---

### Option 1: Delete index `i = 1` twice (the correct optimal path)

#### Step 1

* Delete `A[1] = 4`
* Cost = `4 × C[1] = 4 × 1 = 4`

Remaining array:

| Index | A | C |
| ----- | - | - |
| 1     | 2 | 2 |

#### Step 2

* Delete `A[1] = 2`
* Cost = `2 × C[1] = 2 × 2 = 4`

✅ **Total cost = 4 + 2 = 6**

---

### ❌ Why Your “delete 2 first” idea fails

To delete `2` first, you must choose `i = 2`.

#### Step 1

* Delete `A[2] = 2`
* Cost = `2 × C[2] = 2 × 2 = 4`

Remaining array:

| Index | A | C |
| ----- | - | - |
| 1     | 4 | 1 |

#### Step 2

* Delete `A[1] = 4`
* Cost = `4 × C[1] = 4 × 1 = 4`

❌ **Total = 8**, which is worse than `6`.

So deleting the smaller value first **does not help**, because it gets paired with a larger cost.

---

## Why Sample Output Is 6

Because the **cheapest strategy** is:

* Let **larger A values get multiplied by smaller C values**
* Achieved naturally by **always deleting from the front** in this case

---

## Mental Model That Will Make This Click

Think of it like this:

> You are assigning each `A` value a `C` value, but **the order of assignment depends on deletion order**.

* Earlier deletions use **smaller indices in C**
* Later deletions use **larger indices in C**

So the optimal idea is:

> **Assign the smallest costs to the largest values.**

This is why the problem is **not trivial deletion**, but **order optimisation**.

---

## Final Clarification of Your Understanding

Your statement:

> “delete all array elements with minimum cost”

✅ **Correct**, but with this critical addition:

> “…by choosing the deletion order cleverly, since cost indices are fixed.”

---

