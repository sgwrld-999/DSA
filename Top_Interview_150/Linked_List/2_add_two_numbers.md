# Add Two Numbers

## Problem Statement

You are given two non-empty linked lists representing two non-negative integers.

* The digits are stored in reverse order.
* Each node contains a single digit.
* Add the two numbers and return the sum as a linked list.
* You must return a new linked list (do not modify input).

---

## Example

Input:

l1 = [2,4,3]  
l2 = [5,6,4]

Output:

[7,0,8]

Explanation:

342 + 465 = 807

Stored as:

7 → 0 → 8

---

## Key Observations

* Digits are stored in reverse order.
* Addition naturally proceeds from head to tail.
* This mimics elementary school addition.
* Carry must be maintained.
* Lists may have different lengths.
* After both lists end, carry may still remain.

---

## Why Dummy Node is Important

When building a new linked list:

* We need a stable starting reference.
* The first node might change if we do not use a dummy.
* Dummy simplifies edge cases.
* Final answer is dummy.next.

---

## Core Idea of the Algorithm

1. Create a dummy node.
2. Maintain a pointer `current` to build the result list.
3. Initialize carry = 0.
4. Traverse while:

   l1 exists OR l2 exists OR carry exists

5. At each iteration:

   * Extract value from l1 (0 if None)
   * Extract value from l2 (0 if None)
   * total = val1 + val2 + carry
   * digit = total % 10
   * carry = total // 10
   * Create new node with digit
   * Move current pointer forward

6. Return dummy.next

---

## Important Loop Condition

Correct:

while l1 or l2 or carry:

Why?

* Handles unequal lengths.
* Handles final leftover carry.
* Ensures no digit is missed.

---

## Data Structure Used

### Linked List

We construct a new singly linked list.

### Variables

* l1 pointer
* l2 pointer
* carry
* dummy node
* current pointer

---

## Correct Python Implementation

```python
class Solution:
    def addTwoNumbers(self, l1, l2):

        dummy = ListNode(0)
        current = dummy
        carry = 0

        while l1 or l2 or carry:

            total = carry

            if l1:
                total += l1.val
                l1 = l1.next

            if l2:
                total += l2.val
                l2 = l2.next

            carry = total // 10

            current.next = ListNode(total % 10)
            current = current.next

        return dummy.next
````

---

## Dry Run

Input:

l1 = 9 → 9
l2 = 1

Step 1:

9 + 1 + 0 = 10
digit = 0
carry = 1

Step 2:

9 + 0 + 1 = 10
digit = 0
carry = 1

Step 3:

0 + 0 + 1 = 1
digit = 1
carry = 0

Output:

0 → 0 → 1

---

## Common Mistakes

### ❌ Stopping When One List Ends

Wrong:

while l1 and l2

This fails for unequal lengths.

---

### ❌ Forgetting Final Carry

Example:

5 + 5 = 10

Must create new node for final carry.

---

### ❌ Modifying Original Lists

Never overwrite input nodes.

---

### ❌ Not Using Dummy Node

Leads to messy head handling logic.

---

## Time & Space Complexity

Time Complexity: O(max(n, m))
Space Complexity: O(max(n, m))

---

## Pattern Recognition

This pattern appears in:

* Linked list arithmetic problems
* Large integer addition
* Digit-by-digit processing
* Carry propagation problems

---

## Key Takeaways

* Think digit-wise.
* Always maintain carry.
* Loop until all sources are exhausted.
* Dummy node simplifies list construction.
* Classic linked list + simulation problem.


