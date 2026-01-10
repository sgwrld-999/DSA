# Reverse String Prefix — Full Explanation (From First Principles)

---

## 1. Understanding the Question (Very Important)

You are given:

* A **string** `s`
* An **integer** `k`

```
s = "s0 s1 s2 ... s(n−1)"
```

Your task is to:

👉 **Reverse only the first `k` characters** of the string
👉 Keep the remaining characters **unchanged**

---

### Important Constraints

* `k` can be **less than**, **equal to**, or **greater than** the length of `s`
* String indices are **0-based**

---

## 2. What Exactly Is Being Asked?

After performing the operation:

* Characters from index `0` to `k−1` are **reversed**
* Characters from index `k` to `n−1` remain **as they are**

You must return the **final resulting string**.

---

## 3. Rewriting the Operation Conceptually

Let:

```
s = prefix + suffix
```

Where:

```
prefix = s[0 : k]
suffix = s[k : n]
```

The required output is:

```
reverse(prefix) + suffix
```

This decomposition is the **core idea** of the problem.

---

## 4. Handling the Edge Case (`k ≥ length of s`)

### Why This Case Matters

If:

```
k ≥ len(s)
```

Then:

* The **entire string** is considered the prefix
* So we simply reverse the whole string

### Operation

```
answer = reverse(s)
```

This avoids unnecessary slicing.

---

## 5. Understanding Python Slicing Used Here

### Prefix Extraction

```python
s[:k]
```

Means:

* Start from index `0`
* Stop **before** index `k`

Example:

```
s = "abcd", k = 2
s[:2] = "ab"
```

---

### Reversing Using Step = -1

```python
[::-1]
```

Means:

* Traverse the string **backwards**
* Reverse the sequence

Example:

```
"ab"[::-1] = "ba"
```

---

### Remaining Suffix

```python
s[k:]
```

Means:

* Start from index `k`
* Go till the end

Example:

```
s[2:] = "cd"
```

---

## 6. Final Construction of the Answer

```python
s[:k][::-1] + s[k:]
```

Meaning:

1. Take first `k` characters
2. Reverse them
3. Append the untouched remaining part

---

## 7. Annotated Explanation of the Code

```python
class Solution(object):
    def reversePrefix(self, s, k):
```

Defines the solution class and function.

---

### Length Calculation

```python
n = len(s)
```

Stores the length of the string.

---

### Edge Case Handling

```python
if k >= n:
    return s[::-1]
```

If `k` exceeds string length:

* Reverse the whole string
* Return immediately

---

### Main Logic

```python
return s[:k][::-1] + s[k:]
```

Breakdown:

* `s[:k]` → prefix
* `[::-1]` → reverse prefix
* `s[k:]` → suffix
* `+` → concatenate

---

## 8. Sample Walkthrough (Critical for Understanding)

### Example 1

```
s = "abcd"
k = 2
```

Steps:

```
prefix = "ab"
reverse(prefix) = "ba"
suffix = "cd"
```

Final result:

```
"ba" + "cd" = "bacd"
```

---

### Example 2 (Edge Case)

```
s = "abc"
k = 5
```

Since `k ≥ len(s)`:

```
reverse("abc") = "cba"
```

---

## 9. Why This Approach Is Optimal

* Time Complexity: **O(n)**
* Space Complexity: **O(n)** (new string creation)
* Uses **built-in slicing**, which is:

  * Safe
  * Clean
  * Interview-acceptable

No loops, no extra logic, no edge-case bugs.

---
