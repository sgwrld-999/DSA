# Valid Parentheses

## Problem Statement

Given a string `s` containing just the characters:

```
( ) { } [ ]
```

Determine if the input string is **valid**.

A string is valid if:

* Open brackets must be closed by the same type of brackets
* Open brackets must be closed in the correct order
* Every closing bracket has a corresponding opening bracket

Return `True` if valid, otherwise `False`.

---

## Example

```
Input:  s = "()[]{}"
Output: True
```

```
Input:  s = "(]"
Output: False
```

```
Input:  s = "([)]"
Output: False
```

```
Input:  s = "{[]}"
Output: True
```

---

## Key Observations

* Brackets follow **LIFO (Last In, First Out)** order
* The most recently opened bracket must be closed first
* This naturally suggests a **Stack**
* If at any point a mismatch occurs → invalid
* At the end, stack must be empty

---

## Why Stack is the Correct Data Structure

Consider:

```
( [ { } ] )
```

When we see `{`, it must be closed before `[` and `(`.

This is exactly how a stack works:

```
Push → Push → Push
Pop  → Pop  → Pop
```

---

## Core Idea of the Algorithm

1. Create an empty stack
2. Iterate through each character in the string
3. If opening bracket → push to stack
4. If closing bracket:

   * Check if stack is empty → invalid
   * Pop top element
   * Check if it matches expected opening bracket
5. After processing all characters:

   * If stack empty → valid
   * Else → invalid

---

## Data Structure Used

### Stack (List in Python)

Stores opening brackets temporarily.

### Mapping Dictionary

Maps closing bracket → expected opening bracket

```
')' → '('
'}' → '{'
']' → '['
```

This makes matching clean and efficient.

---

## Correct Python Implementation

```python
class Solution:
    def isValid(self, s: str) -> bool:
        stack = []
        mapping = {
            ')': '(',
            '}': '{',
            ']': '['
        }

        for char in s:
            if char not in mapping:
                stack.append(char)
            else:
                if not stack or stack.pop() != mapping[char]:
                    return False

        return not stack
```

---

## Dry Run

### Input

```
s = "({[]})"
```

### Execution

```
(  → push → ['(']
{  → push → ['(', '{']
[  → push → ['(', '{', '[']
]  → pop '[' → ['(', '{']
}  → pop '{' → ['(']
)  → pop '(' → []
```

Stack is empty → Valid

---

## Invalid Case Example

```
s = "([)]"
```

Execution:

```
( → push
[ → push
) → pop '[' but expected '(' → mismatch
```

Return False

---

## Common Mistakes

### ❌ Using `stack.top()`

Python lists do not have `top()`.
Correct: `stack[-1]`

---

### ❌ Not Checking Empty Stack Before Pop

Leads to runtime error.

Correct:

```python
if not stack:
    return False
```

---

### ❌ Not Checking Final Stack State

Even if no mismatch found, stack must be empty.

---

### ❌ Reversing Matching Logic

Wrong:

```
if char == '(' and top == ')'
```

Correct:

```
if mapping[char] == top
```

---

## Time & Space Complexity

* **Time Complexity:** `O(n)`
* **Space Complexity:** `O(n)` (worst case all opening brackets)

---

## Key Takeaways

* This is a **classic stack problem**
* Matching problems → think LIFO
* Always check empty stack before pop
* Final validation requires empty stack
* Pattern appears in:

  * Expression evaluation
  * Syntax parsing
  * Compiler design
  * XML/HTML validation

---
