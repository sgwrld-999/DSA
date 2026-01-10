# Collatz Conjecture (Easy) — Complete Notes

---

## Problem Restatement (Simplified)

You are given an integer **N**.

You can perform the following operations:

### Operations

* **If N is even**, you may choose one of:

  * ( N \rightarrow (3 \oplus N) + 1 )
  * ( N \rightarrow \frac{N}{2} )

* **If N is odd**, you must perform:

  * ( N \rightarrow (3 \oplus N) + 1 )

Here, `⊕` denotes the **bitwise XOR** operator.

---

## Goal

Determine whether it is **possible to reach `N = 1`** by applying the allowed operations any number of times.

* Print **Yes** if possible
* Print **No** otherwise

---

## Constraints

* ( 1 \le T \le 10^4 )
* ( 1 \le N \le 10^{15} )

Because **N can be very large**, we **cannot simulate** the process.
We must rely on **bitwise patterns and observations**.

---

## Understanding the XOR Operation

### Binary form of `3`

```
3 = 11 (binary)
```

So `(3 ⊕ N)`:

* Flips the **last two bits** of `N`
* Leaves all higher bits unchanged

Then we **add 1**, which may cause a carry.

---

## Behavior for Odd Numbers

Odd numbers always end with `1` in binary.

### Case 1: Last two bits = `01`

```
N      = xxxx01
3 ⊕ N  = xxxx10
+1     = xxxx11
```

### Case 2: Last two bits = `11`

```
N      = xxxx11
3 ⊕ N  = xxxx00
+1     = xxxx01
```

### Observation

* The number **keeps toggling** between:

  * ending in `01`
  * ending in `11`
* **Higher bits never change**
* This creates an **infinite loop**

---

### Exceptions

* **N = 1**

  * Already at target
* **N = 3**

  ```
  3 ⊕ 3 = 0
  0 + 1 = 1
  ```

---

### Conclusion for Odd Numbers

| N             | Reach 1? |
| ------------- | -------- |
| 1             | Yes      |
| 3             | Yes      |
| Any other odd | ❌ No     |

---

## Behavior for Even Numbers

Even numbers have last bit `0`.

Two possible operations:

1. Divide by 2
2. Apply `(3 ⊕ N) + 1`

We analyze based on **last two bits**.

---

## Case 1: Even Numbers Ending with `10`

Binary:

```
xxxx10
```

Dividing by 2 removes the last bit:

```
xxxx1   (odd)
```

From earlier:

* Odd numbers (except 1 and 3) **cannot reach 1**

So this is **bad**.

### Examples

| N  | Binary | N/2 | Result |
| -- | ------ | --- | ------ |
| 10 | 1010   | 5   | ❌      |
| 14 | 1110   | 7   | ❌      |

---

### Exceptions

| N | N/2   | Outcome |
| - | ----- | ------- |
| 2 | 1     | Yes     |
| 6 | 3 → 1 | Yes     |

---

## Case 2: Even Numbers Ending with `00`

Binary:

```
xxxx00
```

These numbers are **multiples of 4**.

---

### What does `(3 ⊕ N) + 1` do here?

```
xxxx00
⊕ 0011
------
xxxx11
+   1
------
(xxxx + 1)00
```

So:
[
(3 ⊕ N) + 1 = N + 4
]

---

### Strategy for Multiples of 4

There are two subcases:

#### Subcase A: Divisible by 8 (`xxxx000`)

* Divide by 2 safely
* Remains a multiple of 4

#### Subcase B: `N ≡ 4 (mod 8)` (`xxxx100`)

* Dividing by 2 gives `xxxx10` ❌ (bad case)
* Instead:

  * Add 4 → becomes divisible by 8
  * Then divide by 2 safely

This guarantees **eventual reduction**.

---

## Key Insight

> Any number divisible by **4** can always be reduced to `1`.

---

## Final Reachability Rules

### Always Reachable

* `1`, `2`, `3`, `6`
* Any **even number divisible by 4**

### Never Reachable

* Odd numbers except `1` and `3`
* Even numbers ending in `10` (except `2` and `6`)

---

## Final Condition (Logic)

```cpp
If N == 1, 2, 3, or 6 → Yes
Else if N is odd → No
Else if N % 4 == 0 → Yes
Else → No
```

---

## Mapping to Code

### Code Used

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long

class Solution{
  public:
    bool can_reach_one(ll n){
        if(n == 1 || n == 2 || n == 3 || n == 6)
            return true;

        if((n & 1) == 1)
            return false;

        ll last_bit = n % 2;
        ll second_last_bit = (n / 2) % 2;

        if(last_bit == 0 && second_last_bit == 0)
            return true;

        return false;
    }
};

int main() {
    int t;
    cin >> t;
    while(t--) {
        ll n;
        cin >> n;
        Solution sol;
        cout << (sol.can_reach_one(n) ? "Yes" : "No") << endl;
    }
    return 0;
}
```

---

## Dry Run Examples

### Example 1: `N = 5`

```
5 → odd
5 ⊕ 3 = 6
+1 = 7
7 ⊕ 3 = 4
+1 = 5   (loop)
```

❌ Output: No

---

### Example 2: `N = 12`

```
12 = 1100
12 / 2 = 6
6 / 2 = 3
3 → 1
```

✅ Output: Yes

---

### Example 3: `N = 10`

```
10 = 1010
10 / 2 = 5 (odd, not 1 or 3)
5 loops forever
```

❌ Output: No

---

### Example 4: `N = 100`

```
100 % 4 == 0 → Yes
```

Valid path exists.

---

## Time Complexity

* **O(1)** per test case
* Pure bit checks
* No simulation

---

## Final Takeaway

This problem is **not a Collatz simulation problem**.

It is a **bit-pattern reachability problem**.

> If `N` is divisible by **4**, you can always reach `1`.
> Otherwise, you get trapped in loops (except small base cases).

---
