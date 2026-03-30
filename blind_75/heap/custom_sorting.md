# 🔹 1. Core Idea of Custom Sorting

In Python, sorting works like this:

```python
sorted(arr, key=???)
```

👉 The `key` tells Python:

> “On what basis should I compare elements?”

Instead of comparing the actual values, Python **transforms each element using the key function**, and sorts based on that value. ([coderivers.org][1])

---

# 🔹 2. What is `lambda` here?

A `lambda` is just a **small one-line function** used for quick logic. ([coderivers.org][2])

```python
lambda x: something
```

---

# 🔥 3. Basic Examples (VERY IMPORTANT)

## ✅ Sort normally

```python
nums = [5, 2, 9, 1]
print(sorted(nums))
# [1, 2, 5, 9]
```

---

## ✅ Custom: Sort by absolute value

```python
nums = [-10, 5, -2, 3]

print(sorted(nums, key=lambda x: abs(x)))
# [-2, 3, 5, -10]
```

👉 Python sorts using `abs(x)` instead of `x`

---

## ✅ Custom: Sort strings by length

```python
words = ["apple", "kiwi", "banana"]

print(sorted(words, key=lambda x: len(x)))
# ['kiwi', 'apple', 'banana']
```

👉 It sorts using length, not the string itself ([ThePythonBook][3])

---

# 🔥 4. Most Important (For DSA)

## ✅ Sorting tuples

```python
arr = [(1, 3), (2, 1), (1, 2)]

print(sorted(arr, key=lambda x: x[1]))
# [(2,1), (1,2), (1,3)]
```

👉 Sort by second element

---

## ✅ Multiple conditions (VERY COMMON)

```python
arr = [(7, 8), (5, 6), (7, 5), (10, 4)]

print(sorted(arr, key=lambda x: (-x[0], x[1])))
```

👉 Meaning:

* First sort by **x[0] descending**
* Then by **x[1] ascending** ([GeeksforGeeks][4])

---

# 🔥 5. How THIS applies to your problem (Top K Frequent)

```python
freq_map = {1:3, 2:2, 3:1}

sorted_items = sorted(freq_map.items(), key=lambda x: x[1], reverse=True)
```

👉 `x` = `(num, frequency)`
👉 `x[1]` = frequency

So sorting is done by **frequency**

---

# 🔥 6. Important Patterns (Memorize these)

### ✔ Sort by value

```python
key=lambda x: x[1]
```

### ✔ Sort descending

```python
key=lambda x: -x
```

### ✔ Sort by multiple things

```python
key=lambda x: (x[1], x[0])
```

### ✔ Reverse using flag

```python
sorted(arr, key=..., reverse=True)
```

---

# 🧠 7. Intuition (THIS is what most people miss)

Think like this:

```python
key=lambda x: something
```

👉 Python converts list:

```
[x1, x2, x3]
```

into:

```
[something(x1), something(x2), something(x3)]
```

and sorts based on that.

---

# ⚡ 8. Quick Real-Life Example

```python
students = [("A", 90), ("B", 80), ("C", 95)]

# sort by marks
sorted(students, key=lambda x: x[1])
```

👉 Sorting is done using marks, not names

---

# 🚀 Final Summary

* `key` = rule for sorting
* `lambda` = quick function to define rule
* Sorting happens on **transformed values**, not original

---

[1]: https://coderivers.org/blog/python-sorted-key-lambda/?utm_source=chatgpt.com "Python `sorted()` with `key` and `lambda`: A Comprehensive Guide - CodeRivers"
[2]: https://coderivers.org/blog/sort-lambda-python/?utm_source=chatgpt.com "Sorting with Lambda Functions in Python - CodeRivers"
[3]: https://pythoncompiler.io/python/python-sorting/?utm_source=chatgpt.com "Python Sorting: sort(), sorted(), Key Functions, and Custom Order | ThePythonBook"
[4]: https://www.geeksforgeeks.org/python-custom-sorting-in-list-of-tuples/?utm_source=chatgpt.com "Custom Sorting in List of Tuples - Python - GeeksforGeeks"

