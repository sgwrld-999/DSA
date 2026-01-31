Below are **clean, structured notes** written in the **same format you prefer** (exam/interview-ready, no emojis, no dashes, clear sections).

---

## Problem Overview

You are given two arrays **A** and **B**, each of length **N**.

You are allowed to perform the following operation any number of times:

Choose an integer **X**.
Let **i** be the leftmost index such that **A[i] ≥ X**.
Increment **A[i]** by **1**.

The task is to determine whether array **A** can be converted into array **B** using this operation.

---

## Key Observations

1. Elements of array **A** can only increase.
   Therefore, if for any index **i**, **A[i] > B[i]**, the conversion is impossible.

2. Hence, a necessary condition is:
   For all **i**, **A[i] ≤ B[i]**

3. Now consider indices where **A[i] < B[i]**.
   We need to increase **A[i]** using valid operations.

---

## Important Insight About the Operation

To increase **A[i]**, we must choose some **X ≤ A[i]**.

However, the operation always increases the **leftmost** index with value **≥ X**.

This creates a critical constraint:

If there exists any index **j < i** such that
**A[j] ≥ A[i]**,
then **A[i] can never be increased**.

Reason:

* If **X > A[i]**, index **i** will never be chosen.
* If **X ≤ A[i]**, then **A[j] ≥ X**, and since **j < i**, index **j** will be increased instead.

So once a larger or equal value appears before index **i**, **A[i] is blocked forever**.

---

## Necessary and Sufficient Condition

For every index **i** such that **A[i] < B[i]**, the following must hold:

**A[i] > max(A[0], A[1], ..., A[i−1])**

In words:
Whenever we need to increase **A[i]**, it must be **strictly greater than all previous elements**.

If this condition fails for any index, the answer is **No**.

If this condition holds for all indices, the answer is **Yes**.

---

## Why This Condition Is Sufficient

If **A[i]** is strictly greater than all previous elements, then:

Choosing **X = A[i]** guarantees that index **i** is the leftmost element satisfying **A[i] ≥ X**.

Thus, the operation will increase **A[i]** by **1**.

By repeatedly applying this process to the largest index where **A[i] < B[i]**, we can eventually make **A = B**.

---

## Algorithm Logic (Linked to Code)

We scan the array from left to right while maintaining:

* **curr**: the maximum value seen so far in array **A**
* **check**: a boolean flag indicating feasibility

For each index **i**:

1. If **A[i] > curr**

   * Update **curr = A[i]**
   * Check that **A[i] ≤ B[i]**
2. Else

   * Since a larger or equal value already exists before
   * We must have **A[i] == B[i]**, otherwise impossible

If any condition fails, stop early and print **No**.

Otherwise, after full traversal, print **Yes**.
 
---

## Code

```python
testcase = int(input())

while testcase > 0:
    n = int(input())
    a = list(map(int, input().split()))
    b = list(map(int, input().split()))
    
    curr = 0
    check = True
    
    for idx, val in enumerate(a):
        if val > curr:
            curr = val   
            if val > b[idx]:
                check = False
        else:
            if val != b[idx]:
                check = False
        
        if not check:
            break
    
    print("Yes" if check else "No")
    
    testcase -= 1   

```
---

## Time Complexity

Each test case is processed in a single pass.

Time Complexity per test case: **O(N)**
Space Complexity: **O(1)** (excluding input arrays)

---

## Final Takeaway

The problem is not about simulating operations.
It is about understanding **which positions are ever allowed to grow**.

Only elements that are **strictly increasing prefix maximums** can be increased.

This observation reduces a seemingly complex operation-based problem into a simple linear scan.
