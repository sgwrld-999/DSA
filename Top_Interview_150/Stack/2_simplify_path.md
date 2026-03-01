# Simplify Path

## Problem Statement

Given a string `path`, which represents an absolute path for a Unix-style file system, convert it to the simplified canonical path.

Rules:

* The path starts with a single slash `/`
* Multiple consecutive slashes should be treated as a single slash
* `.` refers to the current directory (ignore it)
* `..` refers to the parent directory (move one level up)
* The canonical path must:
  * Start with a single slash `/`
  * Not end with a slash (unless it is root)
  * Not contain `.` or `..`

Return the simplified canonical path.

---

## Example

```

Input:  path = "/home/"
Output: "/home"

```
```

Input:  path = "/../"
Output: "/"

```
```

Input:  path = "/home//foo/"
Output: "/home/foo"

```
```

Input:  path = "/a/./b/../../c/"
Output: "/c"

```

---

## Key Observations

* The path is absolute (always starts from root)
* `.` does nothing
* `..` removes the previous directory (if possible)
* Multiple `/` collapse into one
* This is naturally solved using a **Stack**
* You cannot go above root

---

## Why Stack is the Correct Data Structure

When we see:

```

/a/b/../c

```

The sequence is:

```

Push "a"
Push "b"
See ".." → Pop "b"
Push "c"

````

This is exactly LIFO behavior.

---

## Core Idea of the Algorithm

1. Split the path by `/`
2. Iterate through each part
3. If part is:
   * `""` or `"."` → ignore
   * `".."` → pop from stack if not empty
   * otherwise → push directory name
4. Join the stack with `/`
5. Add leading `/`

---

## Data Structure Used

### Stack (List in Python)

Stores valid directory names.

---

## Correct Python Implementation

```python
class Solution:
    def simplifyPath(self, path: str) -> str:
        stack = []

        for part in path.split("/"):
            if part == "" or part == ".":
                continue
            elif part == "..":
                if stack:
                    stack.pop()
            else:
                stack.append(part)

        return "/" + "/".join(stack)
````

---

## Dry Run

### Input

```
path = "/a/./b/../../c/"
```

### Split

```
["", "a", ".", "b", "..", "..", "c", ""]
```

### Execution

```
"a"   → push → ["a"]
"."   → ignore
"b"   → push → ["a","b"]
".."  → pop  → ["a"]
".."  → pop  → []
"c"   → push → ["c"]
```

Result:

```
"/c"
```

---

## Invalid Case Insight

```
"/../../a"
```

We cannot go above root.

Stack stays empty until `"a"`.

Result:

```
"/a"
```

---

## Common Mistakes

### ❌ Pushing `".."` when stack is empty

You cannot go above root.

---

### ❌ Forgetting to push normal directory names

Directories must be added to stack.

---

### ❌ Returning `"/".join(stack)` without leading slash

Would produce relative path.

Correct:

```python
"/" + "/".join(stack)
```

---

## Time & Space Complexity

* **Time Complexity:** `O(n)`
* **Space Complexity:** `O(n)`

---

## Key Takeaways

* This is a stack-based path normalization problem
* Always ignore `.` and empty segments
* Pop only when possible for `..`
* Final result must start with `/`
* Pattern appears in:

  * File system navigation
  * URL normalization
  * Compiler path resolution

