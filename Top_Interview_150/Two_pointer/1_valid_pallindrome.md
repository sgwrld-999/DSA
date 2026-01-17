# Valid Palindrome — Full Explanation

---

## Problem Restatement (Simplified)

You are given a string `s`.

Your task is to determine whether it is a **palindrome**, considering **only alphanumeric characters** and **ignoring case**.

### Definition

A string is a **palindrome** if it reads the same **forward and backward** after preprocessing.

---

## Key Requirements

1. Ignore **non-alphanumeric characters**
2. Treat **uppercase and lowercase as the same**
3. Compare the cleaned string with its reverse

---

## Example

```
Input:  "A man, a plan, a canal: Panama"
Cleaned: "amanaplanacanalpanama"
Output: True
```

```
Input:  "race a car"
Cleaned: "raceacar"
Output: False
```

---

## ASCII Fundamentals (Critical for Manual Approach)

Characters are internally stored as **ASCII values**.

### Alphabet Ranges

```
'a' to 'z' → 97 to 122
'A' to 'Z' → 65 to 90
'0' to '9' → 48 to 57
```

### Key ASCII Insight

To convert uppercase to lowercase:

```
'A' → 'a'
ASCII difference = 32
```

So:

```
lowercase_char = chr(ord(ch) + 32)
```

---

## High-Level Strategy

### Step 1: Remove unwanted characters

Keep only:

* lowercase letters
* uppercase letters
* digits

### Step 2: Normalize case

Convert all letters to **lowercase**

### Step 3: Check palindrome

Compare characters from both ends.

---

## Variant A — Python Using Inbuilt Functions (Clean & Optimal)

### Why This Works

Python already provides:

* `isalnum()` → checks alphanumeric
* `lower()` → handles case normalization
* slicing → reverse comparison

---

### Algorithm

1. Filter only alphanumeric characters
2. Convert everything to lowercase
3. Compare string with its reverse

---

### Code

```python
class Solution:
    def isPalindrome(self, s: str) -> bool:
        cleaned = ""

        for ch in s:
            if ch.isalnum():
                cleaned += ch.lower()

        return cleaned == cleaned[::-1]
```

---

### Time & Space Complexity

```
Time:  O(n)
Space: O(n)
```

---

## Variant B — Manual ASCII-Based Implementation (Your Style)

This version avoids **all inbuilt helpers** and relies only on:

* `ord()`
* `chr()`
* ASCII range checks

---

## Step-by-Step Breakdown

### Step 1: Remove Non-Alphanumeric Characters

Keep character `ch` **only if**:

```
'a' <= ch <= 'z'
'A' <= ch <= 'Z'
'0' <= ch <= '9'
```

---

### Step 2: Convert Uppercase to Lowercase

If:

```
'A' <= ch <= 'Z'
```

Convert using:

```
ch = chr(ord(ch) + 32)
```

---

### Step 3: Two-Pointer Palindrome Check

```
left = 0
right = len(cleaned) - 1
```

Compare until pointers cross.

---

### Code (Manual, Corrected & Clean)

```python
class Solution:
    def isPalindrome(self, s: str) -> bool:
        filtered = []

        # Step 1 & 2: Filter + lowercase manually
        for ch in s:
            ascii_val = ord(ch)

            # lowercase letters
            if 97 <= ascii_val <= 122:
                filtered.append(ch)

            # uppercase letters → convert to lowercase
            elif 65 <= ascii_val <= 90:
                filtered.append(chr(ascii_val + 32))

            # digits
            elif 48 <= ascii_val <= 57:
                filtered.append(ch)

        # Step 3: Two-pointer palindrome check
        left, right = 0, len(filtered) - 1

        while left < right:
            if filtered[left] != filtered[right]:
                return False
            left += 1
            right -= 1

        return True
```

---

## Dry Run (Manual Version)

### Input

```
s = "A man, a plan, a canal: Panama"
```

### Filtered Result

```
['a','m','a','n','a','p','l','a','n','a','c','a','n','a','l','p','a','n','a','m','a']
```

### Pointer Comparison

```
a == a
m == m
a == a
...
```

All match → **Palindrome**

---

## Common Mistakes (What Went Wrong in Original Snippet)

1. Using `ch - 'a'` → ❌ **C/C++ style**, invalid in Python
2. Looping over `str` instead of `s`
3. Mixing index-based and char-based iteration
4. No proper ASCII boundary checks

---

## Variant C — O(1) Space (Two Pointer / Sliding Pointer)

### Key Idea

Instead of:

* creating a new cleaned string (O(n) space)

We:

* **scan from both ends**
* **skip invalid characters**
* **compare characters on the fly**

This guarantees:

```
Extra Space = O(1)
```

### Core Insight

At any time:

* `left` points to the next valid character from the start
* `right` points to the next valid character from the end

Only **valid alphanumeric characters** participate in comparison.

### ASCII Conditions (Reused)

A character is **valid** if:

```
'a'–'z' → 97–122
'A'–'Z' → 65–90
'0'–'9' → 48–57
```

Uppercase → lowercase conversion:

```
chr(ord(ch) + 32)
```

### Algorithm (High Level)

1. Initialize two pointers:

   ```
   left = 0
   right = len(s) - 1
   ```

2. While `left < right`:

   * Skip invalid characters on the left
   * Skip invalid characters on the right
   * Normalize both characters to lowercase
   * Compare
   * Move pointers inward

3. If all comparisons pass → palindrome

### Pointer Movement Logic

```
if s[left] is NOT alphanumeric → left++
if s[right] is NOT alphanumeric → right--
else:
    compare(s[left], s[right])
    left++, right--
```

### Python Code — O(1) Space (ASCII-based, Manual)

```python
class Solution:
    def isPalindrome(self, s: str) -> bool:
        left, right = 0, len(s) - 1

        while left < right:
            # Skip non-alphanumeric on left
            while left < right and not self.is_alnum(s[left]):
                left += 1

            # Skip non-alphanumeric on right
            while left < right and not self.is_alnum(s[right]):
                right -= 1

            if self.to_lower(s[left]) != self.to_lower(s[right]):
                return False

            left += 1
            right -= 1

        return True

    def is_alnum(self, ch: str) -> bool:
        ascii_val = ord(ch)
        return (
            97 <= ascii_val <= 122 or   # a-z
            65 <= ascii_val <= 90  or   # A-Z
            48 <= ascii_val <= 57       # 0-9
        )

    def to_lower(self, ch: str) -> str:
        ascii_val = ord(ch)
        if 65 <= ascii_val <= 90:       # A-Z
            return chr(ascii_val + 32)
        return ch
```

### Dry Run (Important)

### Input

```
"A man, a plan, a canal: Panama"
```

### Pointer Movement

```
left → 'A'  → 'a'
right → 'a'

left → ' '  skip
right → 'm'

compare a == a
compare m == m
compare a == a
...
```

Pointers cross → **Palindrome**

### Why This Is O(1) Space

* No auxiliary string
* No extra arrays or lists
* Only a few variables (`left`, `right`)

### Time & Space Complexity

```
Time:  O(n)
Space: O(1)
```

---

