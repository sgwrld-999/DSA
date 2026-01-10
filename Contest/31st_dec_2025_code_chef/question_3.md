# New Operation — Full Explanation (From First Principles)

---

## 1. Understanding the Question (Very Important)

You are given an array:

```
A = [A1, A2, A3, ..., AN]
```

You must perform **exactly `N−1` operations**, and after that **only one number will remain**.

### The Operation

In **one operation**, you:

1. Choose an index `i` such that:

   ```
   1 ≤ i < current_length
   ```
2. Take **two adjacent elements**:

   ```
   Ai and Ai+1
   ```
3. Replace them with:

   ```
   X = Ai + 2 × Ai+1
   ```

So the array size **shrinks by 1** each time.

---

### Key Insight About the Operation

This is **not commutative**.

That means:

```
Ai + 2 × Ai+1  ≠  Aj + 2 × Aj+1
```

if you choose different pairs or a different order.

👉 **Order matters.**
👉 **Which pairs you merge first matters.**

That’s why the final value is **not unique**.

---

## 2. What Is Being Asked?

After performing all `N−1` operations:

* Only **one number remains**
* You must find:

  * **Minimum possible value**
  * **Maximum possible value**

over **all valid sequences of operations**.

---

## 3. Rewriting the Operation Conceptually

Each operation:

```
X = Ai + 2 × Ai+1
```

Think of it as:

* `Ai+1` is **weighted twice**
* When an element is merged earlier, its value gets multiplied **again and again**

So:

* Elements merged **later** get multiplied **more**
* Elements merged **earlier** get multiplied **less**

This is the core idea.

---

## 4. Strategy to Get the Minimum Value

### Intuition

To minimize the final value:

* You want **small weights** on large numbers
* You want each `Ai` to be multiplied by **2 as few times as possible**

That happens when:
👉 You **always merge from left to right**

---

### What Happens If You Merge Left → Right?

Example:

```
[a0, a1, a2, a3]
```

Operations:

```
(((a0 + 2a1) + 2a2) + 2a3)
```

Final value:

```
a0 + 2a1 + 2a2 + 2a3
```

Notice:

* `a0` is multiplied by 1
* Every other element is multiplied by exactly 2

This is the **minimum possible total weight distribution**.

---

### Minimum Formula

```
x_min = a[0] + 2 × (a[1] + a[2] + ... + a[n−1])
```

---

## 5. Strategy to Get the Maximum Value

### Intuition

To maximize the final value:

* You want **large weights** on large numbers
* So elements should be merged **as late as possible**
* This happens when you merge **right to left**

---

### What Happens If You Merge Right → Left?

Example:

```
[a0, a1, a2, a3]
```

Operations:

```
a0 + 2(a1 + 2(a2 + 2a3))
```

Expanding:

```
a0 + 2a1 + 4a2 + 8a3
```

Here:

* Each element’s weight **doubles every step**
* The rightmost element gets the **largest multiplier**

---

### Maximum Formula (Computed Iteratively)

```
x_max = a[n−1]
x_max = a[n−2] + 2 × x_max
x_max = a[n−3] + 2 × x_max
...
```

---

## 6. Why Only These Two Extremes Matter

* Any mixed order produces values **between** these extremes
* Left-to-right gives **minimum**
* Right-to-left gives **maximum**
* No other order can go beyond them

So brute force is unnecessary.

---

## 7. Annotated Explanation of Your Code

### Reading Input

```cpp
int n;
cin >> n;

vector<int> a(n);
for(int i=0; i<n; i++) cin >> a[i];
```

Reads array size and elements.

---

### Computing Minimum Value

```cpp
int x_mini = a[0];
for(int i=1; i<n; i++){
    x_mini += 2 * a[i];
}
```

Meaning:

```
x_mini = a[0] + 2a[1] + 2a[2] + ... + 2a[n−1]
```

This exactly simulates **left-to-right merging**.

---

### Computing Maximum Value

```cpp
int x_maxi = a[n-1];
for(int i=n-2; i>=0; i--){
    x_maxi = a[i] + 2 * x_maxi;
}
```

Meaning:

* Start from the rightmost element
* Each step increases its weight by ×2
* Simulates **right-to-left merging**

---

### Output

```cpp
cout << x_mini << " " << x_maxi << endl;
```

Prints:

```
minimum maximum
```

---

## 8. Sample Walkthrough (Critical for Understanding)

### Input

```
A = [1, 1, 1]
```

### Minimum

```
1 + 2×1 + 2×1 = 5
```

### Maximum

```
1 + 2(1 + 2×1) = 7
```

Output:

```
5 7
```

---

### Input

```
A = [5, 2, 7]
```

### Minimum

```
5 + 2×2 + 2×7 = 23
```

### Maximum

```
5 + 2(2 + 2×7) = 37
```

---

## 9. Final Takeaway (Most Important)

* The operation **weights elements based on merge order**
* Leftmost-first → **minimum**
* Rightmost-first → **maximum**
* This is a **greedy + associative structure problem**
* Your solution is:

  * Correct
  * Optimal
  * Elegant
  * Contest-safe

---
