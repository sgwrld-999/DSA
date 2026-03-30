# Interview Script — Maximum Depth of Binary Tree

## 1. Opening

**“Let me first restate the problem.”**

We are given a binary tree, and we need to find its **maximum depth**, which is the number of nodes along the longest path from the root to a leaf.

---

## 2. Intuition (this is the key part)

**“At any node, the depth depends on its children.”**

* If I know the depth of the left subtree
* and the depth of the right subtree

Then the depth of the current node is:

> **1 + max(left_depth, right_depth)**

---

## 3. Base case

**“If the node is null, its depth is 0.”**

That’s our stopping condition.

---

## 4. Approach

**“This naturally suggests a recursive solution.”**

At each node:

1. Recursively compute depth of left subtree
2. Recursively compute depth of right subtree
3. Take the maximum of both and add 1

---

## 5. Corrected Code (important — fix your errors)

Here is your corrected version:

```python
class Solution:
    def maxDepth(self, root: Optional[TreeNode]) -> int:
        if root is None:
            return 0

        left_depth = self.maxDepth(root.left)
        right_depth = self.maxDepth(root.right)

        return 1 + max(left_depth, right_depth)
```

---

## 6. What was wrong in your code (mention if asked)

You had a few small issues:

* `maxDepth()` → should be `self.maxDepth()`
* `rightt` → typo
* `lf` vs `lr` mismatch
* inconsistent variable names

👉 These are small, but in interviews they matter.

---

## 7. Dry Run (always do one)

**“Let me walk through a small example.”**

Tree:

```
    1
   / \
  2   3
 /
4
```

* Node 4 → depth = 1
* Node 2 → depth = 1 + 1 = 2
* Node 3 → depth = 1
* Node 1 → depth = 1 + max(2, 1) = 3

👉 Answer = **3**

---

## 8. Complexity

**“Time complexity:”**

* We visit every node once → **O(n)**

**“Space complexity:”**

* Recursive call stack → **O(h)**
  where `h` = height of tree
* Worst case (skewed tree) → **O(n)**

---

## 9. Alternative approach (BFS)

**“We can also solve this using level-order traversal (BFS).”**

* Use a queue
* Traverse level by level
* Count number of levels

---

## BFS Code (optional if asked)

```python
from collections import deque

class Solution:
    def maxDepth(self, root: Optional[TreeNode]) -> int:
        if not root:
            return 0

        queue = deque([root])
        depth = 0

        while queue:
            for _ in range(len(queue)):
                node = queue.popleft()

                if node.left:
                    queue.append(node.left)
                if node.right:
                    queue.append(node.right)

            depth += 1

        return depth
```

---

## 10. When to use DFS vs BFS

**“DFS (recursion) is simpler and more intuitive.”**
**“BFS is useful when we explicitly want level-wise traversal.”**

---

# 11. Follow-up Questions

### ❓ Why recursion works here?

**“Because the problem has an optimal substructure: depth of a node depends on depths of its children.”**

---

### ❓ What if the tree is very deep?

**“Recursion may cause stack overflow. In that case, BFS or iterative DFS is safer.”**

---

### ❓ What is height vs depth?

**“In this problem, they are effectively the same—maximum depth of the tree.”**

---

### ❓ Can we do it iteratively?

**“Yes, using a stack (DFS) or queue (BFS).”**

---

# 12. 30-second version

**“I solve this using recursion. For each node, I compute the depth of its left and right subtrees and return 1 plus the maximum of the two. The base case is when the node is null, where depth is 0. This runs in O(n) time and O(h) space.”**

---

# 13. 10-second version

**“Depth = 1 + max(left depth, right depth), solved using recursion.”**

---

# Final insight (nice closing line)

**“The key idea is that depth is defined locally at each node but computed globally via recursion.”**

---

