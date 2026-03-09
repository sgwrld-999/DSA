# Merge Two Sorted Lists

---

## Problem Statement

You are given the heads of two sorted linked lists.

* Both lists are sorted in non-decreasing order.
* Merge the two lists into one sorted list.
* The merged list should be made by splicing together the nodes of the first two lists.
* Return the head of the merged linked list.

---

## Example

Input:

l1 = 1 → 2 → 4
l2 = 1 → 3 → 4

Output:

1 → 1 → 2 → 3 → 4 → 4

---

## Key Observations

* Both lists are already sorted.
* At every step, we only need to compare the current nodes.
* We always attach the smaller node to the merged list.
* After one list finishes, attach the remaining part of the other list.
* Comparison requires both nodes to exist.

---

## Why Your Error Happened

Error:

AttributeError: 'NoneType' object has no attribute 'val'

Cause:

You wrote:

```
while l1 or l2:
    if l1.val > l2.val:
```

Problem:

* The loop runs even if one list is None.
* You accessed `.val` without checking if the node exists.
* Python cannot access `.val` on None.

Correct logic:

Comparison is only valid when:

```
while l1 and l2:
```

---

## Why Dummy Node is Important

When building a merged list:

* We need a stable starting reference.
* The first chosen node could be from either list.
* Without dummy, head handling becomes messy.
* Final answer is dummy.next.

---

## Core Idea of the Algorithm

1. Create a dummy node.
2. Maintain a pointer `tail` to build the result.
3. Traverse while both lists exist.
4. Compare values:

   * Attach smaller node to `tail.next`
   * Move that list forward
5. Move `tail` forward.
6. After loop:

   * Attach remaining list.
7. Return dummy.next.

---

## Important Loop Condition

Correct:

```
while l1 and l2:
```

Why?

* We can only compare when both exist.
* Prevents AttributeError.
* Keeps logic clean.

---

## Data Structure Used

### Linked List

We reuse existing nodes (no new nodes required).

### Variables

* l1 pointer
* l2 pointer
* dummy node
* tail pointer

---

## Correct Python Implementation

```python
class Solution:
    def mergeTwoLists(self, l1, l2):

        dummy = ListNode(0)
        tail = dummy

        while l1 and l2:

            if l1.val <= l2.val:
                tail.next = l1
                l1 = l1.next
            else:
                tail.next = l2
                l2 = l2.next

            tail = tail.next

        # Attach remaining list
        tail.next = l1 if l1 else l2

        return dummy.next
```

---

## Dry Run

Input:

l1 = 1 → 4
l2 = 2 → 3

Step 1:

1 < 2
Attach 1

Result: 1

Step 2:

4 > 2
Attach 2

Result: 1 → 2

Step 3:

4 > 3
Attach 3

Result: 1 → 2 → 3

Step 4:

l2 ends

Attach remaining l1 (4)

Final:

1 → 2 → 3 → 4

---

## Common Mistakes

### ❌ Using `while l1 or l2`

Leads to None access error.

---

### ❌ Not Moving Tail Pointer

Forgetting:

```
tail = tail.next
```

Breaks list construction.

---

### ❌ Not Attaching Remaining List

After loop, one list still contains elements.

---

### ❌ Returning Wrong Head

Always return:

```
dummy.next
```

---

## Time & Space Complexity

Time Complexity: O(n + m)
Space Complexity: O(1)

---

## Pattern Recognition

This pattern appears in:

* Merge step of Merge Sort
* Linked list merging problems
* Two-pointer techniques
* Sorted array merging

---

## Key Takeaways

* Only compare when both nodes exist.
* Dummy node simplifies pointer management.
* Move the tail every iteration.
* Always attach leftover list.
* Think in terms of pointer redirection.

---

