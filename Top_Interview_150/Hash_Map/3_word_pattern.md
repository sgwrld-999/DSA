## Problem in one line

Given:

* a string `pattern` (single characters)
* a string `s` (space-separated words)

Determine whether **each character in `pattern` maps to exactly one word in `s`**, and vice versa.

This mapping must be:

* **consistent**
* **one-to-one (bijective)**

---

## High-level idea

> Enforce a **two-way mapping**:

* word → pattern character
* pattern character → word

This prevents:

* one word mapping to multiple characters
* multiple words mapping to the same character

---

## Step-by-step explanation

### 1️⃣ Split the string into words

```python
list_str = s.split(" ")
```

Now:

```
s = "dog cat cat dog"
list_str = ["dog", "cat", "cat", "dog"]
```

---

### 2️⃣ Length check (very important)

```python
if len(pattern) != len(list_str):
    return False
```

Why?

* Each pattern character must correspond to exactly one word
* If lengths differ → impossible to map

---

### 3️⃣ Dictionaries for bidirectional mapping

```python
mp_s = {}        # word -> pattern character
mp_pattern = {} # pattern character -> word
```

These two maps together ensure **bijective mapping**.

---

### 4️⃣ Iterate position by position

```python
for i in range(len(pattern)):
```

At index `i`, we compare:

```
pattern[i]  <-->  list_str[i]
```

---

### 5️⃣ Conflict checks (core logic)

```python
if (list_str[i] in mp_s and mp_s[list_str[i]] != pattern[i]) or \
   (pattern[i] in mp_pattern and mp_pattern[pattern[i]] != list_str[i]):
    return False
```

This checks **two failure cases**:

#### Case 1: Word already mapped incorrectly

* The word was seen before
* But now maps to a different pattern character ❌

#### Case 2: Pattern character already mapped incorrectly

* The character was seen before
* But now maps to a different word ❌

If either happens → return `False`.

---

### 6️⃣ Store the mapping if no conflict

```python
mp_s[list_str[i]] = pattern[i]
mp_pattern[pattern[i]] = list_str[i]
```

Safe because conflicts were already checked.

---

### 7️⃣ Final result

```python
return True
```

If the loop finishes, the pattern is valid.

---

## Example walkthrough

### Example 1

```
pattern = "abba"
s = "dog cat cat dog"
```

Mappings:

```
dog → a
cat → b
```

Consistent both ways ✅
Return `True`

---

### Example 2

```
pattern = "abba"
s = "dog cat cat fish"
```

Conflict:

```
a → dog
a → fish ❌
```

Return `False`

---

### Example 3 (important)

```
pattern = "abba"
s = "dog dog dog dog"
```

Conflict:

```
a → dog
b → dog ❌ (two characters to one word)
```

Caught by reverse map
Return `False`

---

## Why two maps are necessary

If you used **only one map**, this would incorrectly pass:

```
pattern = "ab"
s = "dog dog"
```

Because:

```
a → dog
b → dog  ❌
```

The reverse map prevents this.

---

## Time and space complexity

* **Time Complexity:** `O(n)`
* **Space Complexity:** `O(n)`

Where `n` is the number of words / pattern length.

---

## Key takeaway (very important)

> Word Pattern is the **same logic as Isomorphic Strings**,
> just with **words instead of characters**.

Once you recognize that, the solution becomes mechanical.

