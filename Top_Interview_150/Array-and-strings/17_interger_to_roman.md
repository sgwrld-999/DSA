# Integer to Roman — Full Explanation

---

## Problem Restatement (Simplified)

You are given an integer **num** such that:

```
1 ≤ num ≤ 3999
```

Your task is to **convert this integer into its Roman numeral representation**.

---

## Roman Numeral Rules (Authoritative)

Roman numerals use **fixed symbols** with **fixed values**:

| Symbol | Value |
| ------ | ----- |
| I      | 1     |
| V      | 5     |
| X      | 10    |
| L      | 50    |
| C      | 100   |
| D      | 500   |
| M      | 1000  |

---

### Subtractive Notation (Critical)

Roman numerals allow subtraction **only in specific cases**:

| Value | Representation |
| ----- | -------------- |
| 4     | IV             |
| 9     | IX             |
| 40    | XL             |
| 90    | XC             |
| 400   | CD             |
| 900   | CM             |

❗ These are **not derived dynamically** — they are **explicit rules**.

---

## Key Observations

---

## 1. Roman numerals are a **greedy construction system**

Roman numerals are **canonical**, meaning:

> At each step, subtract the **largest possible Roman value** from the number.

This greedy choice is **always optimal**.

There is **no counterexample** within the Roman numeral system.

---

## 2. Why greedy works here (and why it is safe)

Roman numerals have these properties:

* No symbol overlaps ambiguously
* Larger symbols are always preferred
* Subtractive forms prevent illegal repetitions
* Every integer has **exactly one valid representation**

Because of this:

* Taking the largest possible symbol **cannot block future valid symbols**
* The system is **prefix-safe**

Hence, greedy subtraction is guaranteed to work.

---

## 3. Atomic Roman Building Blocks

There are exactly **13 atomic Roman values**.

These must be treated as **indivisible units**:

```
(1000, "M")
(900,  "CM")
(500,  "D")
(400,  "CD")
(100,  "C")
(90,   "XC")
(50,   "L")
(40,   "XL")
(10,   "X")
(9,    "IX")
(5,    "V")
(4,    "IV")
(1,    "I")
```

❗ You must **never compute** these using arithmetic rules.

They are **fixed by definition**.

---

## 4. Greedy Construction Strategy

Let:

```
num = input number
result = empty string
```

For each `(value, symbol)` in descending order:

* While `num ≥ value`:

  * Append `symbol` to result
  * Subtract `value` from `num`

Stop when `num = 0`.

---

## 5. Step-by-Step Example

### Example: `num = 3749`

| Remaining | Action              |
| --------- | ------------------- |
| 3749      | subtract 1000 → `M` |
| 2749      | subtract 1000 → `M` |
| 1749      | subtract 1000 → `M` |
| 749       | subtract 500 → `D`  |
| 249       | subtract 100 → `C`  |
| 149       | subtract 100 → `C`  |
| 49        | subtract 40 → `XL`  |
| 9         | subtract 9 → `IX`   |
| 0         | stop                |

Final result:

```
MMMDCCXLIX
```

---

## 6. Why division / modulo logic fails

A common mistake is trying:

* thousands = num / 1000
* hundreds = (num % 1000) / 100
* tens = ...
* ones = ...

This fails because:

* Subtractive notation **breaks arithmetic symmetry**
* 9 ≠ V + IV
* 90 ≠ L + XL

Roman numerals are **symbol-driven**, not arithmetic-driven.

---

## 7. Edge Constraints and Guarantees

* Minimum value: `1 → I`
* Maximum value: `3999 → MMMCMXCIX`
* Roman numerals **never exceed 3 consecutive repeats**
* Subtractive forms appear **only once per place value**

These guarantees make the greedy approach safe.

---

## Time and Space Complexity

### Time Complexity

```
O(1)
```

Because:

* At most 13 Roman symbols
* Each symbol used a limited number of times

---

### Space Complexity

```
O(1)
```

Output size is bounded.

---

## Final Algorithm Summary

1. Define all valid Roman values explicitly
2. Traverse them from largest to smallest
3. Subtract greedily while possible
4. Append symbols to the result
5. Stop when number becomes zero

---

## Correct Code

```cpp
class Solution {
public:
    string intToRoman(int num) {
        vector<pair<int, string>> roman = {
            {1000, "M"},
            {900,  "CM"},
            {500,  "D"},
            {400,  "CD"},
            {100,  "C"},
            {90,   "XC"},
            {50,   "L"},
            {40,   "XL"},
            {10,   "X"},
            {9,    "IX"},
            {5,    "V"},
            {4,    "IV"},
            {1,    "I"}
        };

        string result;

        for (const auto& [value, symbol] : roman) {
            while (num >= value) {
                result += symbol;
                num -= value;
            }
        }

        return result;
    }
};
```

---

## Why This Works (Intuition Summary)

* Roman numerals are **fixed-pattern representations**
* The greedy choice is always valid
* Subtractive cases are handled explicitly
* No ambiguity or backtracking exists
* The algorithm mirrors how Romans actually wrote numbers

---

