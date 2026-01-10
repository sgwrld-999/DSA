# Ones and Zeroes I — Full Explanation

---

## Problem Restatement (Simplified)

You are given a **binary string `S` of length `N`**.

Definitions:

* A **prefix** `S[1..i]` is called **good** if:

  ```
  number of '1's ≥ number of '0's
  ```
* Let `f(S)` be the **number of good prefixes** of `S`.

Your task:

* For each test case, compute `f(S)`.

---

## Key Observations

1. Prefixes are checked **from left to right**
2. For every prefix:

   * We only care about the **count of ones and zeros so far**
3. Each character affects **exactly one counter**
4. Once we maintain prefix counts, checking a prefix is **O(1)**

---

## Core Idea

Maintain two running counters while scanning the string:

* `one_ctr` → number of `'1'` seen so far
* `zero_ctr` → number of `'0'` seen so far

At every index `i`:

```
If one_ctr ≥ zero_ctr → prefix S[1..i] is good
```

Increment the answer accordingly.

---

## Step-by-Step Logic

1. Initialize:

   ```
   one_ctr = 0
   zero_ctr = 0
   good_prefix = 0
   ```
2. Traverse the string from left to right
3. Update counters based on current character
4. Check the good prefix condition
5. Count how many prefixes satisfy it

---

## Code Explanation

### Given Code

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int test_case;
    cin >> test_case;
    
    while(test_case--){
        int n;
        string s;
        cin >> n >> s;
        
        int one_ctr = 0;
        int zero_ctr = 0;
        int good_prefix = 0;
        
        for(int i = 0; i < n; i++){
            if(s[i] == '0') zero_ctr++;
            if(s[i] == '1') one_ctr++;
            
            if(one_ctr >= zero_ctr){
                good_prefix++;
            }
        }
        
        cout << good_prefix << endl;
    }
    return 0;
}
```

---

## Why This Code Is Correct

### 1. Prefix Handling Is Correct

* The loop iterates from `i = 0` to `n - 1`
* At iteration `i`, the counters represent prefix `S[1..i+1]`
* Exactly matches the definition of prefixes

---

### 2. Counters Are Accurate

* Each character contributes **once and only once**
* No reset or miscount occurs
* Prefix counts are cumulative and correct

---

### 3. Good Prefix Condition Is Correct

The condition:

```cpp
if(one_ctr >= zero_ctr)
```

Directly matches the problem definition:

> “A prefix is good if it contains at least as many ones as zeroes.”

---

### 4. All Prefixes Are Considered

* Every prefix is checked exactly once
* No prefix is skipped or double-counted

---

## Sample Walkthroughs

### Test Case 1

```
S = "000"
```

Prefix-wise:

* "0"    → ones = 0, zeros = 1 ❌
* "00"   → ones = 0, zeros = 2 ❌
* "000"  → ones = 0, zeros = 3 ❌

Result:

```
0
```

---

### Test Case 2

```
S = "001"
```

Prefix-wise:

* "0"    → ❌
* "00"   → ❌
* "001"  → ones = 1, zeros = 2 ❌

Result:

```
0
```

---

### Test Case 3

```
S = "01110"
```

Prefix-wise:

* "0"      → ❌
* "01"     → ✔
* "011"    → ✔
* "0111"   → ✔
* "01110"  → ✔

Result:

```
4
```

---

### Test Case 4

```
S = "11111"
```

Every prefix satisfies:

```
ones ≥ zeros
```

Result:

```
5
```

---

## Time and Space Complexity

* **Time Complexity:** `O(N)` per test case
* **Space Complexity:** `O(1)`
* Efficient enough since total `N ≤ 2 × 10^5`

---

## Key Takeaway

This problem is a **classic prefix-count problem**:

* Maintain running counts
* Apply condition at each prefix
* Count valid prefixes

Your solution is:

* Logically correct
* Efficient
* Exactly aligned with problem constraints
* Contest-acceptable and optimal

---
