# Linked List Cycle (Floyd’s Tortoise and Hare)

## Problem in one line

Given the head of a singly linked list, determine if the list contains a cycle.

---

## My Initial Mistakes (Important)

### 1. Syntax Error

I wrote:

    if slow = fast:

This is assignment, not comparison.

Correct:

    if slow == fast:

---

### 2. Missing Null Safety

I wrote:

    if head.next == None:

But if head itself is None, this crashes.

Correct:

    if head is None or head.next is None:
        return False

---

### 3. Wrong While Condition

I wrote:

    while fast.next != None:

But inside I used:

    fast = fast.next.next

If fast.next exists but fast.next.next does not, it crashes.

Correct condition:

    while fast and fast.next:

This guarantees safe access.

---

## Correct Implementation

```python
class Solution(object):
    def hasCycle(self, head):

        if head is None or head.next is None:
            return False

        slow = head
        fast = head

        while fast and fast.next:
            slow = slow.next
            fast = fast.next.next

            if slow == fast:
                return True

        return False
````

---

# Why Fast and Slow Pointer Works (Mathematical Proof)

## Circular Track Analogy

Imagine the cycle as a circular track of circumference C.

Let:

```
L = distance from head to start of cycle
C = length of the cycle
x = distance from cycle start to meeting point
```

Slow pointer speed = 1 step
Fast pointer speed = 2 steps

---

## Step 1: When They Meet

Assume they meet after t steps.

Distance traveled:

```
Slow distance = t
Fast distance = 2t
```

Since fast moves twice as fast:

```
2t − t = t
```

This means fast has traveled exactly t more distance than slow.

That extra distance must be full loops inside the cycle.

So:

```
2t = t + kC
t = kC
```

for some integer k ≥ 1

This means when they meet, slow has traveled a multiple of the cycle length inside the loop.

---

## Step 2: Breaking the Distance into Parts

Total slow distance:

```
t = L + x
```

Because slow first travels L to enter the cycle, then x inside the cycle.

From earlier:

```
t = kC
```

So:

```
L + x = kC
```

Rearranging:

```
L = kC − x
```

This proves:

The distance from head to cycle start equals the remaining distance from meeting point back to cycle start (mod C).

---

## Why Collision Is Guaranteed

Inside the cycle:

Relative speed of fast with respect to slow = 1 step per iteration.

Think of it like:

Slow is standing still.
Fast moves 1 step per iteration relative to slow.

On a circular track of length C, if you move 1 step per round,
you will meet the stationary person within at most C steps.

Therefore collision is guaranteed.

---

## Why It Fails When No Cycle Exists

If no cycle:

Eventually fast becomes None.

Because it moves 2 steps at a time,
it reaches the end before slow.

Hence we exit the loop safely.

---

## Interview Explanation (Concise Version)

1. Use two pointers.
2. Slow moves 1 step.
3. Fast moves 2 steps.
4. If a cycle exists, fast laps slow.
5. If no cycle exists, fast hits None.
6. Time Complexity O(n)
7. Space Complexity O(1)

---

## Core Insight

Fast pointer gains 1 step per iteration relative to slow.

On a closed loop, gaining 1 step per iteration guarantees collision within C steps.

This is not intuition.

This is modular arithmetic on a circular circumference.

