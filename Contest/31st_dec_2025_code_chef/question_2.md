# Pizza Comparison — Full Explanation

---

## Problem Restatement (Simplified)

Chef makes **two types of square pizzas**:

* **Small pizza**

  * Side length = `10` inches
  * Cost = `A` rupees
* **Large pizza**

  * Side length = `15` inches
  * Cost = `B` rupees

The **amount of pizza** is measured by **area**.

Goal:

* Determine which pizza gives **more area per rupee spent**
* Output:

  * `"Small"` if small pizza is better
  * `"Large"` if large pizza is better
  * `"Equal"` if both give the same value

---

## Key Observations

1. Both pizzas are **square**
2. Area of a square:

   ```
   area = side × side
   ```
3. Value for money is:

   ```
   area / cost
   ```
4. Comparing two ratios is sufficient — no need for absolute values

---

## Area Calculations

### Small Pizza

```
side = 10
area = 10 × 10 = 100
```

### Large Pizza

```
side = 15
area = 15 × 15 = 225
```

These areas are **constant** for all test cases.

---

## What Needs to Be Compared

For each test case:

```
Small value  = 100 / A
Large value  = 225 / B
```

* If `100 / A > 225 / B` → Small is better
* If `100 / A < 225 / B` → Large is better
* Else → Equal

---

## Mathematical Simplification (Important Insight)

Instead of division, we can cross-multiply to avoid precision issues:

Compare:

```
100 × B  vs  225 × A
```

* If `100 × B > 225 × A` → Small
* If `100 × B < 225 × A` → Large
* Else → Equal

This keeps everything in **integers** and is more reliable.

---

## Code Explanation

### Given Code

```cpp
#include <bits/stdc++.h>
using namespace std;

#define COST_SMALL 100
#define COST_LARGE 225

string solve(int small, int large){
    if(((float)COST_SMALL / small) > ((float)COST_LARGE / large)){
        return "Small";
    } else if(((float)COST_SMALL / small) < ((float)COST_LARGE / large)){
        return "Large";
    }
    return "Equal";
}

int main() {
    int test_case;
    cin >> test_case;
    while(test_case--){
        int a, b;
        cin >> a >> b;
        cout << solve(a, b) << endl;
    }
    return 0;
}
```

---

## Why the Logic Is Correct

1. The constants:

   ```cpp
   COST_SMALL = 100
   COST_LARGE = 225
   ```

   correctly represent the **areas** of the pizzas.

2. The function computes:

   ```
   area per rupee = area / cost
   ```

3. Direct comparison of the two ratios correctly determines which pizza gives more value.

4. The logic exactly matches the mathematical requirement of the problem.

---

## Important Note on Floating Point Usage

* The logic is **conceptually correct**
* Floating point division works here because:

  * Inputs are small
  * Precision loss is unlikely within constraints

However, a **better contest-safe approach** would be integer comparison:

```cpp
if (100 * large > 225 * small) return "Small";
else if (100 * large < 225 * small) return "Large";
else return "Equal";
```

This avoids floating-point precision issues entirely.

---

## Sample Walkthrough

### Sample Input

```
A = 100, B = 400
```

Calculations:

```
Small  = 100 / 100 = 1
Large  = 225 / 400 = 0.5625
```

Result:

```
Small
```

---

### Sample Input

```
A = 178, B = 400
```

Calculations:

```
Small  = 100 / 178
Large  = 225 / 400
Both ≈ 0.562
```

Result:

```
Equal
```

---

## Time and Space Complexity

* **Time Complexity:** `O(T)`
* **Space Complexity:** `O(1)`

---

## Final Takeaway

This problem is a **pure ratio comparison** problem:

* Precompute fixed areas
* Compare **area per rupee**
* Use integer arithmetic where possible

Your solution is **logically correct**, and with a minor improvement (avoiding floats), it becomes **perfectly contest-safe**.

---
