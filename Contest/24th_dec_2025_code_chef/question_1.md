## Problem Summary: *Christmas Trees*

Chef runs a seasonal business:

* He **buys `N` trees**, each costing **`A` rupees**
* He **sells `M` trees**, each for **`B` rupees**

The task is to compute **Chef’s net profit or loss**.

* If profit → print the positive value
* If loss of `X` → print `-X` (negative value)

---

## Key Observations

1. **Total Cost Price (CP)**
   [
   \text{CP} = N \times A
   ]

2. **Total Selling Price (SP)**
   [
   \text{SP} = M \times B
   ]

3. **Profit / Loss Formula**
   [
   \text{Profit} = \text{SP} - \text{CP}
   ]

4. The output format explicitly allows **negative values** to represent loss.

---

## Code Explanation (Line-by-Line)

```cpp
#include <bits/stdc++.h>
using namespace std;
```

* Includes all standard C++ libraries.
* Commonly used in competitive programming.

---

```cpp
int main() {
```

* Entry point of the program.

---

```cpp
int n, a, m, b;
cin >> n >> a >> m >> b;
```

* Reads four integers:

  * `n` → number of trees bought
  * `a` → cost per tree
  * `m` → number of trees sold
  * `b` → selling price per tree

---

```cpp
int profit = ((m * b) - (n * a));
```

* Computes:

  * `m * b` → total selling amount
  * `n * a` → total buying cost
* Their difference gives **net profit or loss**.

---

```cpp
if(profit > 0)
    cout << profit << endl;
else
    cout << "-" << -profit << endl;
```

* If profit is positive, print it directly.
* If profit is negative:

  * Convert it to positive using `-profit`
  * Print with a leading `-` to indicate loss

> Note: This logic ensures the output format strictly follows the problem statement.

---

```cpp
return 0;
}
```

* Ends the program successfully.

---

## Sample Dry Run

### Input

```
5 100 2 1000
```

### Calculation

* Cost = `5 × 100 = 500`
* Selling = `2 × 1000 = 2000`
* Profit = `2000 − 500 = 1500`

### Output

```
1500
```

---

### Input

```
5 100 2 100
```

### Calculation

* Cost = `500`
* Selling = `200`
* Loss = `200 − 500 = -300`

### Output

```
-300
```

---

## Time and Space Complexity

* **Time Complexity:** `O(1)`
* **Space Complexity:** `O(1)`

Only basic arithmetic operations are performed.

---

