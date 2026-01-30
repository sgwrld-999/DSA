# 1. Group Anagrams (HashMap)



## Problem in one line

Given a list of strings, group all strings that are **anagrams of each other**.

---

## Core idea

**Anagrams share the same normalized representation.**

The most reliable normalization:

* **Sort the characters of each string**

All anagrams produce the **same sorted key**.

---

## HashMap strategy

Use a dictionary where:

```
key   → sorted string
value → list of original strings
```

Each string is placed into exactly one group.

---

## Algorithm steps

1. Initialize an empty HashMap
2. For each string:

   * Sort characters to form a key
   * Insert the string into the list mapped by that key
3. Return all HashMap values as the result

---

## Why this solution is correct

* Sorting captures **both character identity and frequency**
* Necessary and sufficient condition for anagrams
* No false positives or negatives
* Each string is processed exactly once

---

## Complexity analysis

* Time: `O(n · k log k)`
  where `n` = number of strings, `k` = max string length
* Space: `O(n)`

---

## Interview takeaway

> **Normalize → hash → group**
> This is the standard, expected HashMap solution.

---

# 2. Valid Anagram (HashMap)



## Problem in one line

Determine whether two strings are **anagrams of each other**.

---

## Core idea

**Order does not matter. Frequency does.**

Two strings are anagrams **if and only if**:

* They have the same characters
* With the same counts

---

## HashMap strategy

Track character frequencies and compare them.

---

## Correct approach

1. If lengths differ → return `False`
2. Count characters from the first string
3. Decrease counts using the second string
4. If any count goes negative or missing → not an anagram

---

## Why this works

* Ensures exact frequency match
* Early exits on mismatch
* Avoids redundant comparisons

---

## Complexity analysis

* Time: `O(n)`
* Space: `O(1)` (fixed alphabet) or `O(n)` (general case)

---

## Interview takeaway

> Anagram checking is a **pure frequency comparison problem**.
> Once you see that, the solution is mechanical.

---

# 3. Word Pattern (HashMap)



## Problem in one line

Check whether a pattern string maps **one-to-one** with words in a sentence.

---

## Core idea

The mapping must be **bijective**:

* Each pattern character → one word
* Each word → one pattern character

---

## HashMap strategy (very important)

Use **two HashMaps**:

* word → pattern character
* pattern character → word

This prevents invalid many-to-one mappings.

---

## Algorithm steps

1. Split the sentence into words
2. If pattern length ≠ word count → return `False`
3. Traverse both simultaneously
4. Check for mapping conflicts in both directions
5. Store mappings if valid

---

## Why two maps are required

Without reverse mapping, cases like this would pass incorrectly:

```
pattern = "ab"
s = "dog dog"
```

Reverse mapping catches this violation.

---

## Complexity analysis

* Time: `O(n)`
* Space: `O(n)`

---

## Interview takeaway

> Word Pattern = **Isomorphic Strings**, but with words instead of characters.

Recognizing this pattern makes the problem trivial.

---

