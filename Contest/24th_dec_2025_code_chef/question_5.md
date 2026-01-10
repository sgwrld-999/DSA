# Counting Optimal Arrays — Full Explanation

---

## Problem Restatement (Simplified)

You are given:

* An array **A** of size **N**
* Each element satisfies **0 ≤ Aᵢ ≤ M**
* Define
  [
  f(A) = \sum_{i=1}^{N-1} (A_i \oplus A_{i+1})
  ]
  where `⊕` denotes **bitwise XOR**
* If **N = 1**, then **f(A) = 0**

### Task

1. Let **S** be the **maximum possible value** of `f(A)` over all valid arrays.
2. Count **how many arrays A** achieve `f(A) = S`.
3. Output the count modulo **998244353**.

---

## Key Observations

---

## 1. What is the maximum possible XOR value, and **why is it `2^k − 1`?**

Let
[
k = \lfloor \log_2(M) \rfloor + 1
]

This means:

* `k` is the **number of bits required to represent M**
* The **highest set bit** of any number ≤ M is at position `k − 1`

---

### Why XOR cannot exceed `2^k − 1`

Consider any two numbers:
[
0 \le A_i, A_{i+1} \le M
]

* Since `M < 2^k`, **no number ≤ M has the k-th bit set**
* Therefore, in both numbers:

  * Bit `k` is always `0`
* XOR at that bit:
  [
  0 \oplus 0 = 0
  ]

So the XOR **can never have a 1 beyond bit `k−1`**.

---

### Which bits *can* be set in XOR?

Bits:
[
0, 1, 2, \dots, k-1
]

These bits **may differ**, so XOR can set all of them to `1`.

To **maximize XOR**, we want:

* Every possible bit to differ
* That gives:

  ```
  111...111  (k bits)
  ```

---

### Why subtract 1?

Binary:

```
2^k     = 1000...000
2^k - 1 = 0111...111
```

So:
[
2^k - 1
]
is the **largest number representable using exactly `k` bits**, with **all bits set to 1**.

---

### Conclusion

[
\boxed{
\max(A_i \oplus A_{i+1}) = 2^k - 1
}
]

This is **not an assumption** — it is forced by the bit limit imposed by `M`.

---

## 2. How do we achieve this maximum XOR?

To get:
[
A_i \oplus A_{i+1} = 2^k - 1
]

Every bit must differ.

That means:

* One number has bit = 1
* The other has bit = 0

So the two numbers must be **bitwise complements** over `k` bits.

---

### Example (`k = 3`)

```
5 = 101
2 = 010
---------
5 ⊕ 2 = 111 = 2^3 - 1
```

Hence:

* Complement pairs always achieve the maximum XOR.

---

## 3. How many such complement pairs exist?

For a number `x`, its complement is:
[
(2^k - 1) - x
]

Both numbers must lie in:
[
[0, M]
]

---

### When does this work?

For the complement to be ≥ 0:
[
x \le 2^k - 1
]

For `x` itself to be ≤ M and have the highest bit set:
[
x \ge 2^{k-1}
]

So valid `x` range:
[
[2^{k-1}, M]
]

---

### Count of valid complement pairs

[
\text{pairs} = M - 2^{k-1} + 1
]

Each such `x` produces **exactly one valid complement pair**.

---

## 4. How do these pairs maximize `f(A)`?

For **N ≥ 2**, `f(A)` is a sum of `N−1` XORs.

To maximize the sum:

* **Every adjacent XOR must be maximal**
* That means **every adjacent pair must be a complement pair**

This forces the array to **alternate**.

---

### For each complement pair `(x, y)`

You can form exactly **two arrays**:

* `[x, y, x, y, ...]`
* `[y, x, y, x, ...]`

Both achieve:
[
f(A) = (N-1) \times (2^k - 1)
]

---

### Total arrays for `N ≥ 2`

[
\boxed{
2 \times (M - 2^{k-1} + 1)
}
]

---

## 5. Special Case: `N = 1`

If `N = 1`:

* `f(A) = 0` for **every array**
* Any value in `[0, M]` works

So:
[
\boxed{M + 1}
]

---

## Final Formula

Let:
[
k = \lfloor \log_2(M) \rfloor
]

### If `N = 1`

[
\boxed{M + 1}
]

### If `N ≥ 2`

[
\boxed{2 \times (M - 2^k + 1)}
]

All results are taken modulo **998244353**.

---

## Why This Works (Intuition Summary)

* XOR is maximized when **bits differ**
* All possible differing bits are limited by `M`
* Maximum XOR = **all available bits set** = `2^k − 1`
* Only **complement pairs** achieve this
* Alternation ensures **every adjacent pair is optimal**
* Counting becomes simple arithmetic

---

## Correct Code

```cpp
#include <bits/stdc++.h>
using namespace std;

static const long long MOD = 998244353;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while(T--){
        long long N, M;
        cin >> N >> M;

        if(N == 1){
            cout << (M + 1) % MOD << '\n';
            continue;
        }

        long long k = floor(log2(M));       // highest bit index
        long long base = 1LL << k;           // 2^k
        long long pairs = M - base + 1;      // complement pairs

        cout << (2 * pairs) % MOD << '\n';
    }
}
```

---

