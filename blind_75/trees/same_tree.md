# Interview Script — Same Tree

## 1. Opening

**“Let me restate the problem.”**

We are given two binary trees, and we need to check whether they are **identical**.

Two trees are considered the same if:

* they have the **same structure**, and
* corresponding nodes have the **same values**

---

## 2. Key intuition

**“At any pair of nodes, I need to check three things:”**

1. Both nodes exist (or both are null)
2. Their values are equal
3. Their left subtrees are identical
4. Their right subtrees are identical

This naturally suggests a **recursive comparison**.

---

## 3. Base cases (very important — and where your bug was)

Your code had:

```python
if p is None or q is None:
    return False
```

This is not fully correct.

### Correct logic:

```python
if p is None and q is None:
    return True
```

👉 Both null → trees match at this position

```python
if p is None or q is None:
    return False
```

👉 One null, one not → mismatch

---

## 4. Approach

**“So the recursive strategy is:”**

* If both nodes are null → return True
* If one is null → return False
* If values differ → return False
* Otherwise:

  * check left subtrees
  * check right subtrees

---

## 5. Corrected Code

```python
class Solution:
    def isSameTree(self, p: Optional[TreeNode], q: Optional[TreeNode]) -> bool:

        if p is None and q is None:
            return True

        if p is None or q is None:
            return False

        if p.val != q.val:
            return False

        return (self.isSameTree(p.left, q.left) and
                self.isSameTree(p.right, q.right))
```

---

## 6. Dry Run

**“Let me walk through a quick example.”**

Tree 1:

```
   1
  / \
 2   3
```

Tree 2:

```
   1
  / \
 2   3
```

* Root: 1 == 1 → OK
* Left: 2 == 2 → OK
* Right: 3 == 3 → OK

👉 Result = True

---

Now mismatch case:

Tree 1:

```
1
/
2
```

Tree 2:

```
1
 \
  2
```

* Left vs Right mismatch → returns False

---

## 7. Complexity

**“Time complexity:”**

* We visit each node once → **O(n)**

**“Space complexity:”**

* recursion stack → **O(h)**
  (worst case O(n) if tree is skewed)

---

## 8. Why recursion works

**“Because the problem has a recursive structure—two trees are the same if their roots match and their subtrees are also the same.”**

---

## 9. Alternative approach (Iterative)

**“We can also solve this using a queue (BFS).”**

Idea:

* Push `(p, q)` pairs into a queue
* Compare them level by level

---

### Iterative Code (optional)

```python
from collections import deque

class Solution:
    def isSameTree(self, p, q):
        queue = deque([(p, q)])

        while queue:
            node1, node2 = queue.popleft()

            if not node1 and not node2:
                continue

            if not node1 or not node2:
                return False

            if node1.val != node2.val:
                return False

            queue.append((node1.left, node2.left))
            queue.append((node1.right, node2.right))

        return True
```

---

## 10. Follow-up Questions

### ❓ Why check `both None` first?

**“Because that is the only case where null nodes match. If I check `or` first, I might incorrectly reject valid cases.”**

---

### ❓ What if trees are very deep?

**“Recursion may cause stack overflow, so iterative BFS/DFS is safer.”**

---

### ❓ What is the core property here?

**“We are checking both structure and value equality simultaneously.”**

---

### ❓ Can this be extended?

**“Yes, this idea is used in problems like subtree checking, symmetric trees, and tree isomorphism.”**

---

## 11. 30-second version

**“I solve this using recursion. At each node, I check if both nodes are null, then return true. If only one is null or values differ, return false. Otherwise, I recursively compare the left and right subtrees. This ensures both structure and values match. Time complexity is O(n).”**

---

## 12. 10-second version

**“Two trees are the same if roots match and left and right subtrees are also identical.”**

---

## Final insight

**“The key idea is that equality of trees is defined recursively—so the solution mirrors that definition directly.”**

---
