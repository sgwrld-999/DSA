# 3 Paths — Full Explanation

---

## Problem Restatement (Simplified)

You are given an integer **N** and must construct a **binary grid `A` of size `N × N`** such that:

* You start at cell `(1,1)` and want to reach `(N,N)`
* You can move only:

  * Right: `(x, y+1)`
  * Down: `(x+1, y)`
* You may only pass through cells where `A[i][j] = 1`
* Let `f(A)` be the number of **distinct right-down paths**

### Goal

* Construct a grid with **exactly 3 valid paths**
* If impossible, output `-1`
* Any valid grid is acceptable

---

## Key Observations

1. The number of paths in a grid depends on:

   * How many branches exist
   * Whether paths merge or split
2. Fully open grids grow paths **combinatorially**
3. To get **exactly 3 paths**, we must:

   * Carefully control branching
   * Prevent accidental extra paths
4. Small grids behave very differently from larger ones

---

## Case Analysis

### Case 1: `N = 2`

Grid size: `2 × 2`

Total possible right-down paths in a fully open grid:

```
C(2,1) = 2
```

Possible path counts are:

* `0` (blocked)
* `1`
* `2`

There is **no way to construct exactly 3 paths**.

#### Conclusion

```
Answer = -1
```

This matches the code:

```cpp
if (N == 2) {
    cout << -1 << "\n";
    continue;
}
```

---

### Case 2: `N = 3`

A special hard-coded construction is used.

#### Grid

```
1 0 0
1 1 1
1 1 1
```

#### Why this works

* From `(1,1)` you are forced to go **down**
* The first row blocks any early right move
* The remaining `2 × 3` area creates **exactly 3 controlled paths**

Enumerating paths:

1. Right → Right → Down → Down
2. Right → Down → Right → Down
3. Right → Down → Down → Right

No extra branches exist.

#### Conclusion

```
f(A) = 3
```

---

## General Case: `N ≥ 4`

This is where the real construction logic applies.

---

## High-Level Strategy

The grid is divided into **two parts**:

1. A **forced corridor**

   * Ensures only **one way** to reach a specific cell
2. A **3 × 3 block**

   * Carefully designed to produce **exactly 3 paths**

Total paths:

```
1 (corridor) × 3 (block) = 3
```

---

## Forced Corridor Construction

```cpp
for (int i = 0; i <= N-3; i++)
    A[i][0] = 1;

for (int j = 0; j <= N-3; j++)
    A[N-3][j] = 1;
```

### What this does

* Forces movement:

  * Down along the first column
  * Then right along row `N-3`
* No branching is possible
* Exactly **one path** reaches cell `(N-2, N-2)` (0-based)

This guarantees **path uniqueness up to the block**.

---

## 3 × 3 Exact-3-Paths Block

Placed at bottom-right:

```
1 0 0
1 1 1
1 1 1
```

### Why this block has exactly 3 paths

* The top-left cell of the block has only **one entry**
* Internal structure allows **3 distinct right-down combinations**
* No cycles
* No additional branching

This block is **path-isolated**, meaning:

* No other parts of the grid can add paths into it

---

## Why No Extra Paths Exist

1. Cells outside the corridor and block are `0`
2. No alternative entry points into the block
3. No alternative exits from the corridor
4. All paths must:

   ```
   Start → corridor → block → end
   ```

Hence:

```
Total paths = 3
```

---

## Code Explanation

### Full Implementation

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T; 
    cin >> T;

    while (T--) {
        int N;
        cin >> N;

        if (N == 2) {
            cout << -1 << "\n";
            continue;
        }

        vector<vector<int>> A(N, vector<int>(N, 0));

        if (N == 3) {
            A = {
                {1,0,0},
                {1,1,1},
                {1,1,1}
            };
        } 
        else {
            // forced corridor
            for (int i = 0; i <= N-3; i++)
                A[i][0] = 1;

            for (int j = 0; j <= N-3; j++)
                A[N-3][j] = 1;

            // 3x3 exact-3-paths block
            int r = N-3, c = N-3;
            A[r][c] = 1;     A[r][c+1] = 0;   A[r][c+2] = 0;
            A[r+1][c] = 1;   A[r+1][c+1] = 1; A[r+1][c+2] = 1;
            A[r+2][c] = 1;   A[r+2][c+1] = 1; A[r+2][c+2] = 1;
        }

        for (auto &row : A) {
            for (int x : row) cout << x << " ";
            cout << "\n";
        }
    }
}
```

---

## Time and Space Complexity

* **Time Complexity:** `O(N²)` per test case (printing dominates)
* **Space Complexity:** `O(N²)`
* Efficient for `N ≤ 50`

---

## Key Takeaways

* Path-count problems are about **controlling branching**
* Small grids require **special handling**
* Larger grids can be built using:

  * Forced paths
  * Localized controlled blocks
* The solution guarantees:

  ```
  f(A) = 3
  ```

This solution is:

* Correct
* Constructive
* Contest-safe
* Accepted for all valid inputs

---
