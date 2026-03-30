# Interview Script — Invert Binary Tree

## 1. Opening

**“Let me restate the problem.”**

We are given a binary tree, and we need to **invert it**, meaning:

> for every node, we swap its left and right children

So the tree becomes a mirror of itself.

---

## 2. Intuition

**“At each node, the operation is simple: swap left and right.”**

But since the tree has many nodes, we need to apply this operation **recursively to every node**.

---

## 3. Key idea

**“If I can invert the left subtree and the right subtree, and also swap them at the current node, the whole tree gets inverted.”**

So at each node:

1. Swap left and right
2. Recursively invert both subtrees

---

## 4. Base case

**“If the node is null, I simply return it.”**

This stops the recursion.

---

## 5. Your code (and a small improvement)

Your logic is correct. Just a small stylistic improvement:

You wrote:

```python
self.invertTree(root.right)
self.invertTree(root.left)
```

That works, but it’s slightly clearer to write:

```python
self.invertTree(root.left)
self.invertTree(root.right)
```

(after swapping, both are fine—but clarity matters in interviews)

---

## 6. Clean version of code

```python
class Solution:

    def invertTree(self, root: Optional[TreeNode]) -> Optional[TreeNode]:
        if root is None:
            return None

        # swap children
        root.left, root.right = root.right, root.left

        # recursively invert subtrees
        self.invertTree(root.left)
        self.invertTree(root.right)

        return root
```

---

## 7. Dry Run

**“Let me walk through a simple example.”**

Original tree:

```
    1
   / \
  2   3
```

Step 1 (swap at root):

```
    1
   / \
  3   2
```

Then recursively:

* Node 3 → no children → unchanged
* Node 2 → no children → unchanged

Final tree:

```
    1
   / \
  3   2
```

---

More complex example:

```
    4
   / \
  2   7
 / \ / \
1  3 6  9
```

After inversion:

```
    4
   / \
  7   2
 / \ / \
9  6 3  1
```

---

## 8. Complexity

**“Time complexity:”**

* We visit every node once → **O(n)**

**“Space complexity:”**

* recursion stack → **O(h)**
  where `h` = height of tree

Worst case (skewed tree) → **O(n)**

---

## 9. Alternative approach (Iterative)

**“We can also solve this using BFS or DFS iteratively.”**

### BFS approach (queue)

```python
from collections import deque

class Solution:
    def invertTree(self, root):
        if not root:
            return None

        queue = deque([root])

        while queue:
            node = queue.popleft()

            node.left, node.right = node.right, node.left

            if node.left:
                queue.append(node.left)
            if node.right:
                queue.append(node.right)

        return root
```

---

## 10. Follow-up Questions

### ❓ Why recursion works here?

**“Because the problem has a recursive structure—each subtree can be inverted independently.”**

---

### ❓ Swap before or after recursion?

**“Either works, as long as we consistently apply recursion to both children. Swapping first is slightly more intuitive.”**

---

### ❓ What if the tree is very deep?

**“Recursion could cause stack overflow. In that case, iterative BFS is safer.”**

---

### ❓ Is this in-place?

**“Yes, we modify the existing tree without using extra space for new nodes.”**

---

### ❓ What is the core operation?

**“Swapping left and right pointers at every node.”**

---

## 11. 30-second version

**“I solve this using recursion. For each node, I swap its left and right children, then recursively invert the left and right subtrees. The base case is when the node is null. This visits every node once, so time complexity is O(n), and space is O(h).”**

---

## 12. 10-second version

**“At every node, swap left and right, then recurse.”**

---

## Final insight

**“This problem looks simple, but it’s a classic example of applying a local operation recursively across a tree.”**

---

