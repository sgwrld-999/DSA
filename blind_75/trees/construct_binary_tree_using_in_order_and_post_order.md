# Interview Script — Construct Binary Tree from Inorder and Postorder Traversal

## 1. Opening

**“Let me first restate the problem.”**

We are given two arrays:

* `inorder`
* `postorder`

Both belong to the **same binary tree**, and we need to reconstruct and return that tree.

---

# 2. First key observation

**“The most important property here is the meaning of postorder and inorder.”**

* **Inorder** = Left, Root, Right
* **Postorder** = Left, Right, Root

So in postorder, the **last element is always the root** of the current subtree. That is the main starting point. 

---

# 3. How to split the tree

**“Once I know the root, I can find that root inside the inorder array.”**

Why is that useful?

Because in inorder:

* everything to the **left** of the root belongs to the left subtree
* everything to the **right** of the root belongs to the right subtree

So root position in inorder tells me how to divide the tree into:

* left subtree
* right subtree

That is the core recursive idea. 

---

# 4. Brute-force thought process

**“A brute-force recursive solution would be:”**

1. Take the last element of postorder as root
2. Search for that value inside inorder
3. Split inorder into left and right parts
4. Split postorder into left and right parts based on subtree size
5. Recursively build left and right subtrees

This works, but there is one inefficiency:

* every time I search for the root in inorder, it may take `O(n)`

So if I do that for every node, total time becomes `O(n^2)` in the worst case.

---

# 5. Optimization idea

**“To optimize this, I can preprocess the inorder array into a hash map.”**

This map stores:

* value → index in inorder

So instead of searching linearly every time, I can find the root index in `O(1)`.

That reduces the total time to `O(n)`. 

---

# 6. Recursive structure

## What I would say

**“Now let me explain the recursive function.”**

The recursive function will build a tree from:

* a subarray range in `inorder`
* a subarray range in `postorder`

So instead of slicing arrays again and again, I will pass indices:

* `in_left`, `in_right`
* `post_left`, `post_right`

This avoids extra copying and keeps the solution efficient.

---

# 7. Important formula

Suppose:

* `root_val = postorder[post_right]`
* `root_index = inorder_index_map[root_val]`

Then:

* left subtree size = `root_index - in_left`

That is very important, because it tells me how many nodes belong to the left subtree.

From that, I can derive the recursive ranges.

---

# 8. How ranges are formed

If current subtree uses:

* inorder → `in_left ... in_right`
* postorder → `post_left ... post_right`

Then:

### Root

```python
root_val = postorder[post_right]
```

### Left subtree

In inorder:

```python
in_left ... root_index - 1
```

In postorder:

```python
post_left ... post_left + left_size - 1
```

### Right subtree

In inorder:

```python
root_index + 1 ... in_right
```

In postorder:

```python
post_left + left_size ... post_right - 1
```

That is the full recursive breakdown. 

---

# 9. Code

Here is the clean optimized solution:

```python
class Solution:
    def buildTree(self, inorder: List[int], postorder: List[int]) -> Optional[TreeNode]:
        if not inorder or not postorder or len(inorder) != len(postorder):
            return None

        inorder_index_map = {}
        for index, value in enumerate(inorder):
            inorder_index_map[value] = index

        def build(in_left: int, in_right: int, post_left: int, post_right: int) -> Optional[TreeNode]:
            if in_left > in_right or post_left > post_right:
                return None

            root_val = postorder[post_right]
            root = TreeNode(root_val)

            root_index = inorder_index_map[root_val]
            left_size = root_index - in_left

            root.left = build(
                in_left,
                root_index - 1,
                post_left,
                post_left + left_size - 1
            )

            root.right = build(
                root_index + 1,
                in_right,
                post_left + left_size,
                post_right - 1
            )

            return root

        return build(0, len(inorder) - 1, 0, len(postorder) - 1)
```

---

# 10. How to explain the code in interview

You can say this:

**“First, I create a hash map from the inorder array so I can quickly find the position of any node.”**

**“Then I define a recursive helper that builds a subtree from given inorder and postorder index ranges.”**

**“The last element in the current postorder range is the root.”**

**“Using the hash map, I find that root in inorder, which tells me how many nodes belong to the left subtree.”**

**“Then I recursively build the left subtree and right subtree using the correct index ranges.”**

**“The base case is when the range becomes invalid, in which case I return `None`.”**

---

# 11. Dry run

Let’s take the standard example:

```python
inorder = [9, 3, 15, 20, 7]
postorder = [9, 15, 7, 20, 3]
```

---

## Step 1: Find root

Postorder last element = `3`

So root is:

```python
3
```

Now find `3` in inorder:

```python
[9, 3, 15, 20, 7]
    ^
```

So:

* left inorder = `[9]`
* right inorder = `[15, 20, 7]`

---

## Step 2: Left subtree

Left subtree size = 1

So left postorder must be the first 1 element:

```python
[9]
```

So left subtree root = `9`

That becomes:

```python
   3
  /
 9
```

---

## Step 3: Right subtree

Remaining right postorder:

```python
[15, 7, 20]
```

Last element = `20`

So right subtree root = `20`

Find `20` in inorder:

```python
[15, 20, 7]
      ^
```

So:

* left of 20 = `[15]`
* right of 20 = `[7]`

Thus:

```python
    3
   / \
  9   20
     /  \
    15   7
```

Done.

---

# 12. Why recursion works

**“This problem has recursive structure because once I identify the root, the remaining problem splits into constructing the left subtree and constructing the right subtree.”**

That means the original problem reduces into the same smaller problem again and again.

---

# 13. Complexity

## Brute-force

If I linearly search for root in inorder every time:

* Time = `O(n^2)`

## Optimized

With hash map:

* Building map = `O(n)`
* Constructing tree = `O(n)`

So total:

* **Time = `O(n)`**
* **Space = `O(n)`**

Space comes from:

* hash map
* recursion stack

---

# 14. Common mistakes to mention

These are very interview-relevant.

### Mistake 1

Using array slicing repeatedly

**Why bad?**
Because slicing creates new arrays and increases overhead.

### Mistake 2

Searching inorder linearly every time

**Why bad?**
That makes worst-case time `O(n^2)`.

### Mistake 3

Getting the postorder ranges wrong

This is the most common bug.

The important thing is:

* left subtree size = `root_index - in_left`

Everything depends on that number.

---

# 15. Follow-up questions and answers

## Q1. Why is the last element in postorder always the root?

**Answer:**

**“Because postorder traversal follows Left, Right, Root, so the root of the current subtree is always visited last.”**

---

## Q2. Why do we need inorder as well?

**Answer:**

**“Because postorder alone does not uniquely define the tree. Inorder tells us how to split nodes into left and right subtrees once the root is known.”**

---

## Q3. Can preorder + postorder uniquely build a binary tree?

**Answer:**

**“Not always. In general, preorder and postorder together are not enough to uniquely reconstruct a binary tree unless extra constraints are given, such as the tree being full.”**

---

## Q4. Why use a hash map?

**Answer:**

**“To find the root’s index in inorder in O(1) time instead of O(n). That improves total complexity from O(n^2) to O(n).”**

---

## Q5. Why use indices instead of slicing?

**Answer:**

**“Using indices avoids creating new arrays at every recursive call, which saves both time and space.”**

---

## Q6. What is the base case?

**Answer:**

**“If the inorder or postorder range becomes invalid, there are no nodes to construct, so I return `None`.”**

---

## Q7. What happens if values are not unique?

**Answer:**

**“This approach assumes all values are unique. If duplicates are allowed, the hash map from value to index becomes ambiguous, so extra handling would be needed.”**

---

# 16. 30-second polished answer

**“I solve this recursively. The last element in postorder is the root. I find that root in inorder, which splits the tree into left and right subtrees. Then I recursively build both sides using the corresponding inorder and postorder ranges. To avoid O(n^2) time from repeated searching, I preprocess the inorder array into a hash map of value to index. That gives an O(n) solution.”**

---

# 17. 10-second version

**“Pick root from the end of postorder, split inorder around it, and recursively build left and right using subtree sizes.”**

---

# 18. One polished closing line

**“The whole problem becomes easy once we use the two traversal properties correctly: postorder gives the root, and inorder tells us how to split the tree.”**
