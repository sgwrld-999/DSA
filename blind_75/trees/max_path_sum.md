# Interview Script — Binary Tree Maximum Path Sum

---

## 1. Opening

**“Let me restate the problem.”**

We are given a binary tree, and we need to find the **maximum path sum**.

A path:

* Can start and end at **any node**
* Must be **continuous**
* Cannot revisit nodes

---

## 2. Intuition

**“At each node, there are two different things happening.”**

1. A path can **pass through the node** (left → node → right)
2. A path can **extend upward to its parent** (only one side)

This distinction is the heart of the problem.

---

## 3. Key idea

**“For every node, I compute two values.”**

### 1. Path passing through the node (candidate answer)

```text
left_sum + right_sum + node.val
```

### 2. Path returned to parent (one direction only)

```text
node.val + max(left_sum, right_sum)
```

---

## 4. Important constraint

**“We ignore negative paths.”**

```python
left_sum = max(0, left_subtree)
right_sum = max(0, right_subtree)
```

Why?

> Because adding a negative path would reduce the total sum.

---

## 5. Global tracking (very important)

**“The best path may not go to the root.”**

So we maintain a **global maximum**:

```python
self.maxi
```

This gets updated at every node.

---

## 6. Base case

**“If the node is null, return 0.”**

---

## 7. Clean code

```python
class Solution:

    def find_path_sum(self, root: Optional[TreeNode]) -> int:
        if root is None:
            return 0

        left_sum = max(0, self.find_path_sum(root.left))
        right_sum = max(0, self.find_path_sum(root.right))

        # path passing through current node
        self.maxi = max(self.maxi, left_sum + right_sum + root.val)

        # return one side to parent
        return root.val + max(left_sum, right_sum)


    def maxPathSum(self, root: Optional[TreeNode]) -> int:
        self.maxi = float("-inf")
        self.find_path_sum(root)
        return self.maxi
```

---

## 8. Dry Run

**“Let me walk through a classic example.”**

Tree:

```
       -10
       /  \
      9    20
          /  \
         15   7
```

### Step-by-step:

* Node 15 → returns 15
* Node 7 → returns 7

At node 20:

```
left = 15, right = 7
path = 15 + 20 + 7 = 42  ← update maxi
return = 20 + max(15,7) = 35
```

At root (-10):

```
left = 9, right = 35
path = 9 + (-10) + 35 = 34
```

Final answer:

```
maxi = 42
```

---

## 9. Complexity

**Time complexity:**

* Visit each node once → **O(n)**

**Space complexity:**

* Recursion stack → **O(h)**
  Worst case → **O(n)** (skewed tree)

---

## 10. Common mistakes (important in interviews)

### ❌ Mistake 1: Returning both sides to parent

```python
return left + right + root.val
```

→ Not allowed (path cannot branch upward)

---

### ❌ Mistake 2: Not using global variable

→ You will miss paths not going through root

---

### ❌ Mistake 3: Forgetting `max(0, …)`

→ Negative paths reduce result

---

### ❌ Mistake 4 (your earlier bug)

```python
maxi = max(self.maxi, ...)
```

→ creates local variable instead of updating global

Correct:

```python
self.maxi = max(self.maxi, ...)
```

---

## 11. Follow-up Questions

### ❓ Why do we return only one side?

**“Because a parent path cannot split into both children through a single node.”**

---

### ❓ Why do we need a global variable?

**“Because the best path may be entirely inside a subtree and never reach the root.”**

---

### ❓ What if all values are negative?

**“We initialize `self.maxi = -inf`, so the least negative node is chosen correctly.”**

---

### ❓ Can we solve without `self`?

Yes, using a list or tuple—but `self` keeps it cleaner.

---

## 12. 30-second version

**“At each node, I compute the maximum path sum passing through it using left + right + node value, and update a global maximum. For recursion, I return only one side (max of left or right) to the parent. I ignore negative paths using max(0, …). This ensures we explore all possible paths in O(n) time.”**

---

## 13. 10-second version

**“Track global max using left + node + right, return one-side path to parent.”**

---

## Final insight

**“This problem is a classic example where recursion carries one value upward, while a global variable captures the best answer across all nodes.”**

---
