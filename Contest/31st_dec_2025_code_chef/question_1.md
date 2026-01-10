# Cake Baking — Full Explanation

---

## Problem Restatement (Simplified)

You are given:

* **N** customers
* **M** cakes, where **M ≥ N**

Rules:

* Every customer must receive **at least 1 cake**, otherwise they are **unhappy**
* A customer is **happy** if they receive **2 or more cakes**
* The chef wants to **maximize the number of happy customers**
* **No customer should be unhappy**

---

## Key Observations

1. Since no customer can be unhappy, **each customer must get at least one cake**
2. Giving **more than 2 cakes** to a customer does **not increase happiness**
3. Each **extra cake beyond the first** can be used to make **one customer happy**
4. Therefore, happiness is limited by:

   * Number of customers
   * Number of remaining cakes after minimum distribution

---

## Step-by-Step Logical Breakdown

### Step 1: Mandatory Distribution

Each customer must receive **1 cake**.

* Cakes used: `N`
* Remaining cakes:

  ```
  remaining = M − N
  ```

---

### Step 2: Creating Happy Customers

* To make a customer happy, we need **1 extra cake**
* So the number of happy customers depends on how many extra cakes are available

Thus:

```
happy_customers = min(N, M − N)
```

---

## Case Analysis

### Case 1: Enough Cakes for Everyone to be Happy

Condition:

```
M ≥ 2N
```

Explanation:

* Each customer can get 2 cakes
* All customers are happy

Result:

```
happy_customers = N
```

---

### Case 2: Limited Extra Cakes

Condition:

```
M < 2N
```

Explanation:

* After giving 1 cake to everyone, only `M − N` cakes remain
* Each remaining cake makes exactly one customer happy

Result:

```
happy_customers = M − N
```

---

## Final Formula

```
happy_customers = min(N, M − N)
```

---

## Code Explanation

### Implementation

```cpp
#include <bits/stdc++.h>
using namespace std;

int solve(int n, int m){
    if (n * 2 < m)
        return n;
    else
        return m - n;
}

int main() {
    int n, m;
    cin >> n >> m;
    cout << solve(n, m) << endl;
}
```

---

## Why This Code Is Correct

* `n * 2 < m` checks if there are enough cakes to give **2 cakes to all customers**
* If true → all customers are happy
* Otherwise → happy customers are limited by extra cakes (`m − n`)
* This directly implements:

  ```
  min(N, M − N)
  ```

---

## Sample Walkthroughs

### Sample 1

**Input**

```
N = 3, M = 7
```

**Explanation**

* Minimum needed: `3` cakes
* Remaining: `4`
* Enough to make all 3 customers happy

**Output**

```
3
```

---

### Sample 2

**Input**

```
N = 4, M = 6
```

**Explanation**

* Minimum needed: `4` cakes
* Remaining: `2`
* Only 2 customers can be upgraded

**Output**

```
2
```

---

## Time and Space Complexity

* **Time Complexity:** `O(1)`
* **Space Complexity:** `O(1)`

---

## Key Takeaway

This problem reduces to a **simple greedy observation**:

> After satisfying the minimum requirement, each remaining cake increases happiness by exactly one — until customers run out.

This makes the solution both **optimal and trivial to compute**.

---
