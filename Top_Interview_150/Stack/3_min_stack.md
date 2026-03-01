# Min Stack

## Problem Statement

Design a stack that supports the following operations in constant time:

* `push(val)` → Push element onto stack
* `pop()` → Remove top element
* `top()` → Get top element
* `getMin()` → Retrieve the minimum element in the stack

All operations must run in **O(1)** time complexity.

---

## Example

```

Input:
push(5)
push(3)
push(7)
getMin() → 3
pop()
getMin() → 3
pop()
getMin() → 5

```

---

## Key Observations

* A normal stack supports push/pop/top in O(1)
* Finding minimum normally takes O(n)
* We must maintain minimum information dynamically
* This is a **Stack Design Problem**
* We need to store extra information while pushing

---

## Why Normal Stack Fails

If we only store values:

```

[5, 3, 7]

```

To find min, we must scan entire stack → O(n)

That violates the requirement.

---

## Core Idea of the Algorithm

Store not just the value, but also the **minimum so far** at each level.

Each stack entry will store:

```

(value, minimum_so_far)

```

This ensures:

* When pushing → compute new minimum
* When popping → previous minimum automatically restored
* `getMin()` becomes O(1)

---

## Data Structure Used

### Stack (List of Tuples)

Each element:

```

(val, current_min)

```

Example state:

```

push(5) → [(5,5)]
push(3) → [(5,5), (3,3)]
push(7) → [(5,5), (3,3), (7,3)]

````

---

## Correct Python Implementation

```python
class MinStack:

    def __init__(self):
        self.stack = []

    def push(self, val: int) -> None:
        if not self.stack:
            self.stack.append((val, val))
        else:
            current_min = min(val, self.stack[-1][1])
            self.stack.append((val, current_min))

    def pop(self) -> None:
        if self.stack:
            self.stack.pop()

    def top(self) -> int:
        return self.stack[-1][0]

    def getMin(self) -> int:
        return self.stack[-1][1]
````

---

## Dry Run

### Operations

```
push(5)
push(2)
push(8)
```

### Stack State

```
[(5,5)]
[(5,5), (2,2)]
[(5,5), (2,2), (8,2)]
```

`getMin()` → 2

After `pop()`:

```
[(5,5), (2,2)]
```

Minimum still correctly maintained.

---

## Alternative Approach (Two Stacks)

Maintain:

* `stack` → normal values
* `min_stack` → track minimums only

Push to `min_stack` only when:

```
val <= current_min
```

Pop from both stacks accordingly.

---

## Common Mistakes

### ❌ Overwriting Python built-in `min`

Never assign:

```
self.min = min
```

---

### ❌ Not Using `self.` for Instance Variables

Must use:

```
self.stack
```

---

### ❌ Trying to Recalculate Minimum During Pop

Minimum must be stored per element.

Do not recompute using full stack.

---

## Time & Space Complexity

* `push()` → O(1)
* `pop()` → O(1)
* `top()` → O(1)
* `getMin()` → O(1)
* Space Complexity → O(n)

---

## Key Takeaways

* This is a **design + stack augmentation problem**
* Store extra metadata with each element
* Think in terms of maintaining invariants
* Frequently asked in interviews
* Pattern appears in:

  * Monotonic stack problems
  * Sliding window minimum
  * Data structure design questions

