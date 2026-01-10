# Roman to Integer — Full Explanation

---

## Problem Restatement (Simplified)

You are given a string **s** representing a Roman numeral.

Each Roman numeral consists of characters from the set:

```
{ I, V, X, L, C, D, M }
```

Each symbol has a fixed integer value:

| Symbol | Value |
| ------ | ----- |
| I      | 1     |
| V      | 5     |
| X      | 10    |
| L      | 50    |
| C      | 100   |
| D      | 500   |
| M      | 1000  |

### Task

Convert the given Roman numeral string **s** into its corresponding **integer value**.

---

## Roman Numeral Rules

Roman numerals follow **two key rules**:

---

### 1. Additive Rule (Normal Case)

If a symbol is followed by another symbol of **equal or smaller value**, its value is **added**.

#### Examples

```
III  = 1 + 1 + 1 = 3
XII  = 10 + 1 + 1 = 12
LV   = 50 + 5 = 55
```

---

### 2. Subtractive Rule (Special Case)

If a symbol is followed by a symbol of **greater value**, the current symbol is **subtracted**.

Only specific subtractive pairs are valid:

| Pair | Value |
| ---- | ----- |
| IV   | 4     |
| IX   | 9     |
| XL   | 40    |
| XC   | 90    |
| CD   | 400   |
| CM   | 900   |

#### Examples

```
IV  = 5 − 1 = 4
IX  = 10 − 1 = 9
XL  = 50 − 10 = 40
CM  = 1000 − 100 = 900
```

---

## Key Observation

Instead of hard-coding all subtractive cases, we can generalise:

> **If the value of the current symbol is smaller than the value of the next symbol, subtract it. Otherwise, add it.**

This rule captures **all valid Roman numeral cases**.

---

## Algorithm Strategy

### High-Level Idea

1. Traverse the string from **left to right**
2. Compare the current character with the next character
3. Decide whether to **add or subtract**
4. Accumulate the total

---

## Step-by-Step Algorithm

1. Initialise `sum = 0`
2. For each index `i` in the string:

   * If `i + 1 < n` and
     `value(s[i]) < value(s[i+1])`
     → subtract `value(s[i])`
   * Else
     → add `value(s[i])`
3. Return `sum`

---

## Why This Works

* Roman numerals are processed **left to right**
* Subtractive notation always involves **two adjacent symbols**
* By comparing adjacent values, we automatically detect:

  * `I` before `V` or `X`
  * `X` before `L` or `C`
  * `C` before `D` or `M`
* No special cases or lookups are required

---

## Example Walkthrough

### Input

```
s = "MCMXCIV"
```

### Values

```
M = 1000
C = 100
M = 1000
X = 10
C = 100
I = 1
V = 5
```

### Iteration

| Index | Current | Next | Action       | Total |
| ----- | ------- | ---- | ------------ | ----- |
| 0     | M       | C    | add 1000     | 1000  |
| 1     | C       | M    | subtract 100 | 900   |
| 2     | M       | X    | add 1000     | 1900  |
| 3     | X       | C    | subtract 10  | 1890  |
| 4     | C       | I    | add 100      | 1990  |
| 5     | I       | V    | subtract 1   | 1989  |
| 6     | V       | —    | add 5        | 1994  |

### Output

```
1994
```

---

## Edge Cases

* Single character (`"I"`, `"V"`, `"M"`)
* Entirely additive (`"III"`, `"XXII"`)
* Entirely subtractive combinations (`"IV"`, `"IX"`)
* Largest valid Roman numeral (`"MMMCMXCIX" = 3999`)

---

## Time & Space Complexity

* **Time Complexity:**
  [
  O(n)
  ]
  where `n` is the length of the string

* **Space Complexity:**
  [
  O(1)
  ]
  (only constant extra variables)

---

## Correct Code (C++)

```cpp
class Solution {
public:
    int romanToInt(string s) {
        int sum = 0;
        int n = s.size();

        for (int i = 0; i < n; i++) {
            if (i + 1 < n && value(s[i]) < value(s[i + 1])) {
                sum -= value(s[i]);
            } else {
                sum += value(s[i]);
            }
        }

        return sum;
    }

private:
    int value(char c) {
        if (c == 'I') return 1;
        if (c == 'V') return 5;
        if (c == 'X') return 10;
        if (c == 'L') return 50;
        if (c == 'C') return 100;
        if (c == 'D') return 500;
        if (c == 'M') return 1000;
        return 0;
    }
};
```

---

## Intuition Summary

* Roman numerals rely on **relative ordering**
* Smaller before larger → subtract
* Otherwise → add
* A single comparison with the next character is sufficient
* This produces a **clean, optimal, and error-free solution**

---

