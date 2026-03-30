# Interview Script — Subtree of Another Tree

## 1. Opening

**“Let me restate the problem.”**

We are given two binary trees: `root` and `subRoot`.

We need to determine:

> whether `subRoot` exists inside `root` as a subtree with the **same structure and node values**

A subtree means:

* a node in `root`
* along with all of its descendants

---

## 2. Intuition

**“This problem reminds me of the Same Tree problem.”**

If I could check whether two trees are identical, then I can:

* try that check at every node in `root`

So the idea becomes:

> “For every node in `root`, check if the subtree starting from that node is identical to `subRoot`.”

---

## 3. Key idea

**“The solution has two parts.”**

### 1. Compare two trees (Same Tree logic)

Check:

* values match
* structure matches
* left subtree matches
* right subtree matches

---

### 2. Traverse the main tree

At each node:

1. Check if current subtree == `subRoot`
2. If not, check left subtree
3. If not, check right subtree

---

## 4. Recursive relation

**“At every node, I have three possibilities.”**

```text
isSubtree(root, subRoot) =
    isSameTree(root, subRoot)
    OR isSubtree(root.left, subRoot)
    OR isSubtree(root.right, subRoot)
```

---

## 5. Base cases

### For `isSameTree(p, q)`:

* both `None` → True
* one `None` → False
* values differ → False

---

### For `isSubtree(root, subRoot)`:

* if `root` is `None` → False
* if trees match → True

---

## 6. Clean version of code

```python
class Solution:

    def isSameTree(self, first_tree, second_tree):
        # both empty
        if first_tree is None and second_tree is None:
            return True
        
        # one empty
        if first_tree is None or second_tree is None:
            return False
        
        # value mismatch
        if first_tree.val != second_tree.val:
            return False
        
        # check left and right
        return (
            self.isSameTree(first_tree.left, second_tree.left) and
            self.isSameTree(first_tree.right, second_tree.right)
        )

    def isSubtree(self, root, subRoot):
        if root is None:
            return False
        
        # check current node
        if self.isSameTree(root, subRoot):
            return True
        
        # check left or right
        return (
            self.isSubtree(root.left, subRoot) or
            self.isSubtree(root.right, subRoot)
        )
```

---

## 7. Explanation of the code

**“Let me walk through how the code works.”**

### Step 1: `isSameTree`

This function checks if two trees are identical.

* If both nodes are `None` → they match
* If only one is `None` → mismatch
* If values differ → mismatch
* Otherwise:

  * recursively compare left children
  * recursively compare right children

So this ensures:

> both **structure + values** match perfectly

---

### Step 2: `isSubtree`

This function scans the main tree.

At each node:

1. First, check:

   ```python
   self.isSameTree(root, subRoot)
   ```

   → “Does subtree match here?”

2. If yes → return `True`

3. If not:

   * search in left subtree
   * search in right subtree

So we are essentially:

> trying every possible starting point

---

## 8. Dry Run

**“Let me walk through a simple example.”**

```
root:
      3
     / \
    4   5
   / \
  1   2

subRoot:
    4
   / \
  1   2
```

* Start at node `3` → not same
* Go left → node `4`
* Compare with `subRoot` → match found

Return `True`

---

## 9. Complexity

**“Time complexity:”**

* For each node in `root` (N nodes)
* we may compare up to M nodes (`subRoot`)

So:

> **O(N × M)**

---

**“Space complexity:”**

* recursion stack height

> **O(h1 + h2)**

Worst case (skewed trees):

> **O(N)**

---

## 10. Follow-up Questions

### ❓ Why use two functions?

**“One function handles comparison (Same Tree), the other handles traversal. This separation keeps the logic clean.”**

---

### ❓ Can this be optimized?

**“Yes, using tree serialization + string matching or hashing (like KMP), we can reduce average complexity.”**

---

### ❓ What is the core idea?

**“Try matching subRoot at every node using Same Tree logic.”**

---

### ❓ Why not just compare values?

**“Because structure also matters. Even if values match, the shape must be identical.”**

---

### ❓ What if subRoot is null?

**“An empty tree is always a subtree → return True.”**

---

## 11. 30-second version

**“I traverse every node in the main tree. At each node, I check whether the subtree starting there is identical to subRoot using a Same Tree helper. If any match is found, I return True. Otherwise, I continue searching left and right. Time complexity is O(N × M).”**

---

## 12. 10-second version

**“At each node, check Same Tree. If not, search left and right.”**

---

## Final insight

**“This problem is a direct extension of Same Tree — the only extra step is trying the comparison at every node.”**

---


