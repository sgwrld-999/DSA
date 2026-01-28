## Problem in one line

You are given a list of strings.
You must **group all strings that are anagrams of each other**.

---

## Core idea (the key insight)

> **Anagrams share the same normalized representation.**

For this problem, the most reliable normalization is:

* **Sorting the characters of the string**

Example:

```
"eat" → "aet"
"tea" → "aet"
"tan" → "ant"
```

Strings with the same sorted form **must be anagrams**.

---

## Step-by-step explanation of the code

### 1️⃣ Hash map for grouping

```python
map_str = {}
```

This dictionary maps:

```
sorted_string → list of original strings
```

---

### 2️⃣ Iterate through each string

```python
for s in strs:
```

Each string is processed independently.

---

### 3️⃣ Create a canonical key

```python
key = ''.join(sorted(s))
```

* `sorted(s)` sorts the characters
* `join` converts it to a hashable string
* All anagrams produce the **same key**

This step **removes ordering information**, keeping only character identity and frequency.

---

### 4️⃣ Insert into the correct group

```python
if key not in map_str:
    map_str[key] = []
map_str[key].append(s)
```

* If this anagram group doesn’t exist, create it
* Otherwise, append to the existing group

---

### 5️⃣ Build and return the result

```python
return list(map_str.values())
```

---

## Example walkthrough

### Input

```
["eat","tea","tan","ate","nat","bat"]
```

### Hash map after processing

```
{
  "aet": ["eat", "tea", "ate"],
  "ant": ["tan", "nat"],
  "abt": ["bat"]
}
```

### Output

```
[
  ["eat","tea","ate"],
  ["tan","nat"],
  ["bat"]
]
```

---

## Why this solution is **correct**

### 1️⃣ It uses a **necessary and sufficient condition**

Two strings are anagrams **if and only if**:

* They have the same characters
* With the same frequencies

Sorting characters captures **exactly this condition**.

There are:

* ❌ No false positives (non-anagrams won’t match)
* ❌ No false negatives (all anagrams will match)

---

### 2️⃣ It is deterministic and order-independent

* Input order does not matter
* Output grouping is stable regardless of input permutation
* Every string is classified once and only once

---

### 3️⃣ It avoids all common logical traps

This solution correctly handles:

* Duplicate letters (`"aab"` vs `"aba"`)
* Single-character strings
* Empty strings
* Large input sizes

---

## Why this solution is **optimal**

### Time Complexity

Let:

* `n` = number of strings
* `k` = maximum length of a string

Sorting each string takes:

```
O(k log k)
```

For all strings:

```
O(n · k log k)
```

This is **asymptotically optimal** for a comparison-based normalization.

---

### Space Complexity

* Hash map stores all strings once
* Total auxiliary space: `O(n)`

No redundant structures or nested loops.

---

## Why this approach is better than alternatives

### ❌ Pairwise comparison (brute force)

```
O(n² · k)
```

Too slow for large inputs.

---

### ❌ Sorting the entire list repeatedly

Unnecessary recomputation and poor scalability.

---

### ⚠️ Frequency array as key

```
O(n · k)
```

Slightly faster, but:

* More complex
* Less readable
* More error-prone in interviews

Sorting strikes the **best balance between clarity and performance**.

---

## Interview perspective (important)

> This solution is the **expected standard answer**.

It demonstrates:

* Strong understanding of hashing
* Proper normalization
* Clean grouping logic
* Trade-off awareness

---

## Final takeaway (lock this in)

> **Normalize → hash → group.**

Sorting provides the **most robust normalization**, making this solution:

* Correct
* Optimal
* Readable
* Interview-safe

---


