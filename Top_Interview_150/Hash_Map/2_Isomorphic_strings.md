## Problem in one line

Two strings `s` and `t` are **isomorphic** if:

> Each character in `s` can be replaced to get `t`,
> with a **one-to-one and consistent mapping**.

No two characters in `s` can map to the same character in `t`.

---

## Core idea (very important)

You must enforce **bijective mapping**:

* `s → t` mapping must be consistent
* `t → s` mapping must also be consistent

That’s why **two maps** are required.

---

## What each map does

```python
map_s = {}  # maps characters from s to t
map_t = {}  # maps characters from t to s
```

These two maps together guarantee **one-to-one correspondence**.

---

## Step-by-step logic

```python
for i in range(len(s)):
```

We compare characters **position by position**.

---

### Case 1: `s[i]` was seen before

```python
s[i] in map_s and map_s[s[i]] != t[i]
```

Meaning:

* `s[i]` already maps to some character
* But now it wants to map to a different one ❌

This breaks consistency → return `False`.

---

### Case 2: `t[i]` was seen before

```python
t[i] in map_t and map_t[t[i]] != s[i]
```

Meaning:

* `t[i]` is already mapped from another character in `s`
* Two characters mapping to one ❌

This breaks one-to-one mapping → return `False`.

---

### If both checks pass

```python
map_s[s[i]] = t[i]
map_t[t[i]] = s[i]
```

We safely record the mapping in both directions.

---

## Final result

If the loop completes without contradiction:

```python
return True
```

---

## Example walkthrough

### Example 1

```
s = "egg"
t = "add"
```

Mappings:

```
e → a
g → d
```

Consistent in both directions ✅
Output: `True`

---

### Example 2

```
s = "foo"
t = "bar"
```

Mappings:

```
f → b
o → a
o → r  ❌ conflict
```

Output: `False`

---

### Example 3 (important)

```
s = "ab"
t = "aa"
```

Mappings:

```
a → a
b → a ❌ two-to-one
```

Caught by `map_t`
Output: `False`

---

## Why two maps are necessary

If you used **only one map**, this case would pass incorrectly:

```
s = "ab"
t = "aa"
```

Because:

```
a → a
b → a  (allowed without reverse check ❌)
```

The second map prevents this.

---

## Time and space complexity

* **Time:** `O(n)`
* **Space:** `O(n)`

Each character is processed once.

---

## Key takeaway (lock this in)

> Isomorphic strings require **bidirectional consistency**.

This **two-hashmap pattern** appears in:

* Word pattern problems
* Encoding / decoding mappings
* Graph isomorphism basics

