# Ones and Zeroes II — Full Explanation (Deep Dive)

---

## 1. Re-understanding the Problem (This Is Crucial)

You are given a **binary string `S` of length `N`**.

### Definition of a Good Prefix

A prefix `S[1..i]` is **good** if:

```
number of '1's ≥ number of '0's
```

Let:

```
f(S) = number of good prefixes in S
```

This is **exactly the same definition** as *Ones and Zeroes I*.

---

## 2. What Is New in This Problem?

In **Ones and Zeroes I**:

* You were given `S`
* You just computed `f(S)`

In **Ones and Zeroes II**:

* You are allowed to perform **any number of adjacent swaps**
* You may **reorder the string**, but only via adjacent swaps
* Your goal is:

  1. **Maximize `f(S)`**
  2. Among all ways to get this maximum, find the **minimum number of swaps**

So this is a **two-objective problem**:

1. Maximize `f(S)`
2. Minimize swaps (secondary objective)

---

## 3. Key Insight: What Makes a Prefix Bad?

Let’s define:

```
balance(i) = (# of 1s in S[1..i]) − (# of 0s in S[1..i])
```

A prefix is:

* **Good** if `balance(i) ≥ 0`
* **Bad** if `balance(i) < 0`

So maximizing `f(S)` means:

> Keep the balance non-negative for as many prefixes as possible.

---

## 4. What Is the Best Possible Arrangement?

To maximize the number of good prefixes:

* You want **1s as early as possible**
* Zeros should be pushed **to the right**
* This keeps prefix balance high

The **best possible arrangement** is:

```
All 1s first, then all 0s
```

Example:

```
Original: 010110
Optimal : 111000
```

This arrangement gives the **maximum possible `f(S)`**.

---

## 5. But Why Not Just Sort?

Because:

* You are only allowed **adjacent swaps**
* Each swap has a **cost**
* You must minimize the number of swaps needed

So:

* We want to **simulate making prefixes good**
* By pulling `1`s forward **only when needed**
* Using the **nearest possible `1`**

This is where the greedy logic comes in.

---

## 6. Greedy Strategy (High-Level)

We scan the string **from left to right**, keeping track of:

* `sum` → prefix balance (`+1` for `'1'`, `-1` for `'0'`)
* If at any position the balance becomes negative:

  * We **must fix it**
  * The only way to fix it is:

    * Bring a `'1'` from the right
    * Swap it left until it reaches the current position

If we **cannot find a `'1'` to the right**, we must stop.

---

## 7. What Are We Actually Computing?

* `maxInd` → the **largest prefix length** that can be kept good

  * This is the **maximum `f(S)`**
* `cnt` → total number of swaps used to achieve this

---

## 8. Annotated Explanation of the Code

### Initialization

```cpp
ll pt = 0, cnt = 0;
ll sum = 0, maxInd = 0;
```

* `pt` → pointer used to search for the next `'1'`
* `cnt` → total swap count
* `sum` → prefix balance
* `maxInd` → maximum prefix index that is good

---

### Main Loop: Scan Prefixes

```cpp
for(ll i=0; i<n; i++){
```

We process prefixes one by one.

---

### Update Balance

```cpp
sum += (s[i] == '1' ? 1 : -1);
```

* `'1'` increases balance
* `'0'` decreases balance

---

### Case 1: Prefix Is Still Good

If:

```
sum ≥ 0
```

Then:

* Prefix `S[1..i+1]` is good
* Update:

```cpp
maxInd = max(maxInd, i+1);
```

---

### Case 2: Prefix Becomes Bad (`sum < 0`)

This means:

> There are more zeros than ones so far — this prefix is bad and must be fixed.

---

### Fixing a Bad Prefix

```cpp
while(pt < n && s[pt] != '1'){
    pt++;
}
```

We search **to the right** for the nearest `'1'`.

---

#### If a `'1'` Is Found

```cpp
cnt += pt - i;
s[pt] = '0';
sum += 2;
```

What this means:

* We swap that `'1'` left until index `i`
* Cost = distance moved = `pt - i`
* That `'1'` replaces a `'0'`, so:

  * Balance changes from `-1` to `+1`
  * Net increase = `+2`

This **fixes the prefix** with minimum swaps.

---

#### If No `'1'` Exists

```cpp
if(sum < 0) break;
```

* No way to fix the balance
* No further prefixes can be good
* Stop processing

---

## 9. Why This Greedy Strategy Is Optimal

1. We **only swap when necessary**
2. We always pick the **nearest `'1'`**
3. Any other `'1'` would cost more swaps
4. Once a prefix cannot be fixed, no longer prefixes can be fixed either

Thus:

* `maxInd` is maximized
* `cnt` is minimized

---

## 10. Sample Walkthrough

### Input

```
S = 001
```

Initial:

```
balance = 0
```

Step by step:

* `0` → balance = -1 → bad
* Pull nearest `1` from index 2
* Swaps = 2
* New string: `100`

Prefixes:

* `1` → good
* `10` → good

Result:

```
f(S) = 2
swaps = 2
```

---

## 11. Output Meaning

The output:

```
maxInd cnt
```

Means:

* `maxInd` → maximum possible number of good prefixes
* `cnt` → minimum swaps to achieve that

---

## 12. Final Takeaway (Very Important)

This problem is about:

* **Prefix balance**
* **Greedy fixing**
* **Minimal adjacent swaps**

Your code:

* Does **not brute force**
* Fixes prefixes only when required
* Achieves **global optimality** through local greedy decisions

This is a **classic greedy + prefix invariant problem**, and your solution is:

* Correct
* Efficient (`O(N)` per test case)
* Contest-ready
* Conceptually clean once the question is understood

---

```cpp
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

void solve() {
    ll n;
    cin >> n;

    string s;
    cin >> s;

    ll searchPointer = 0;      // pointer to search for the next '1' on the right
    ll swapCount = 0;          // total number of adjacent swaps performed
    ll prefixBalance = 0;      // (#ones - #zeros) for current prefix
    ll maxGoodPrefixes = 0;    // maximum number of good prefixes achievable

    for (ll i = 0; i < n; i++) {
        // Ensure searchPointer is always ahead of current index
        searchPointer = max(searchPointer, i + 1);

        // Update prefix balance
        if (s[i] == '1')
            prefixBalance++;
        else
            prefixBalance--;

        // If prefix becomes bad, try to fix it
        if (prefixBalance < 0) {

            // Find the nearest '1' to the right
            while (searchPointer < n && s[searchPointer] != '1') {
                searchPointer++;
            }

            // If a '1' is found, bring it left using swaps
            if (searchPointer < n) {
                swapCount += (searchPointer - i); // swaps needed
                s[searchPointer] = '0';           // that '1' is now used
                prefixBalance += 2;               // -1 → +1 net change
            }
        }

        // If prefix is still bad, no further prefixes can be good
        if (prefixBalance < 0)
            break;

        // This prefix is good
        maxGoodPrefixes = max(maxGoodPrefixes, i + 1);
    }

    cout << maxGoodPrefixes << " " << swapCount << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
```

