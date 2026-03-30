# Interview Script — Serialize and Deserialize Binary Tree

## 1. Opening

**“Let me restate the problem.”**

We are given a binary tree, and we need to design two functions:

* `serialize(root)` → convert the tree into a string
* `deserialize(data)` → rebuild the exact same tree from that string

The important point is:

> the deserialized tree must have the same values and the same structure as the original tree

---

## 2. What makes this problem important?

**“The main challenge is that storing only the node values is not enough.”**

For example, these two trees are different:

```text
Tree 1:        1
              / \
             2   3

Tree 2:        1
              /
             2
              \
               3
```

If I only store:

```text
1,2,3
```

then I cannot know which structure was the original one.

So while serializing, I must store:

* node values
* null positions also

That is the key to reconstructing the tree correctly.

---

## 3. Intuition

**“A tree can be uniquely reconstructed if I store both the traversal order and the null children.”**

A very clean way to do that is:

* use **preorder traversal**
* whenever a node is null, store `"N"`

So preorder order becomes:

```text
root → left → right
```

And null nodes are explicitly recorded.

This gives enough information to rebuild the tree exactly.

---

## 4. Why preorder works so well

**“Preorder is convenient because when I read the serialized data, the first value tells me the current root immediately.”**

Then recursively:

* build the left subtree
* build the right subtree

So serialization and deserialization naturally mirror each other.

---

## 5. Key idea

At each node:

### During serialization

1. If node is `None`, store `"N"`
2. Otherwise:

   * store node value
   * serialize left subtree
   * serialize right subtree

### During deserialization

1. Read the current token
2. If it is `"N"`, return `None`
3. Otherwise:

   * create a node
   * recursively build its left subtree
   * recursively build its right subtree

---

## 6. Base case

**“If the node is null, I store a marker like `N`.”**

And during rebuilding:

**“If I read `N`, I return `None`.”**

That is the stopping condition for recursion.

---

## 7. Clean version of code

```python
# Definition for a binary tree node.
# class TreeNode(object):
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

class Codec:

    def serialize(self, root):
        """Encodes a tree to a single string.
        
        :type root: TreeNode
        :rtype: str
        """
        result = []

        def preorder(node):
            if node is None:
                result.append("N")
                return

            result.append(str(node.val))
            preorder(node.left)
            preorder(node.right)

        preorder(root)
        return ",".join(result)

    def deserialize(self, data):
        """Decodes your encoded data to tree.
        
        :type data: str
        :rtype: TreeNode
        """
        values = data.split(",")
        self.index = 0

        def build_tree():
            if values[self.index] == "N":
                self.index += 1
                return None

            node = TreeNode(int(values[self.index]))
            self.index += 1

            node.left = build_tree()
            node.right = build_tree()

            return node

        return build_tree()
```

---

## 8. Code explanation

Now let me explain the code line by line in an interview-friendly way.

---

### `serialize()`

```python
result = []
```

This list stores the serialized form of the tree.

---

```python
def preorder(node):
```

I define a helper function to do preorder traversal.

---

```python
if node is None:
    result.append("N")
    return
```

If the node is null, I store `"N"` and stop further recursion from that path.

This is very important because nulls preserve structure.

---

```python
result.append(str(node.val))
```

If the node exists, I first store its value.

This follows preorder: root first.

---

```python
preorder(node.left)
preorder(node.right)
```

Then I recursively serialize the left subtree and right subtree.

---

```python
return ",".join(result)
```

Finally I convert the list into a single string separated by commas.

Example:

```text
1,2,N,N,3,4,N,N,5,N,N
```

---

### `deserialize()`

```python
values = data.split(",")
```

I break the serialized string back into tokens.

---

```python
self.index = 0
```

This keeps track of which token I am currently reading.

---

```python
def build_tree():
```

This helper recursively rebuilds the tree.

---

```python
if values[self.index] == "N":
    self.index += 1
    return None
```

If the current token is `"N"`, that means this child does not exist.

So I move to the next token and return `None`.

---

```python
node = TreeNode(int(values[self.index]))
self.index += 1
```

Otherwise, I create a new node using the current value and move the index forward.

---

```python
node.left = build_tree()
node.right = build_tree()
```

Since the serialized order is preorder, after reading the root, the next part belongs to the left subtree, then the right subtree.

So I recursively rebuild them in that same order.

---

```python
return node
```

Finally I return the rebuilt subtree root.

---

## 9. Dry Run

### Example 1

Tree:

```text
    1
   / \
  2   3
```

---

### Serialization

Preorder traversal with nulls:

* visit `1`
* visit `2`
* left of `2` is null → `N`
* right of `2` is null → `N`
* visit `3`
* left of `3` is null → `N`
* right of `3` is null → `N`

Serialized string:

```text
1,2,N,N,3,N,N
```

---

### Deserialization

Read tokens in order:

```text
1,2,N,N,3,N,N
```

* `1` → create root node `1`
* next token `2` → create left child `2`
* next token `N` → left of `2` is null
* next token `N` → right of `2` is null
* next token `3` → create right child `3`
* next token `N` → left of `3` is null
* next token `N` → right of `3` is null

Rebuilt tree:

```text
    1
   / \
  2   3
```

---

### Example 2

Tree:

```text
      1
     /
    2
     \
      3
```

Serialization:

```text
1,2,N,3,N,N,N
```

Notice how null markers tell us exactly where children are missing.

Without nulls, structure would be lost.

---

### Example 3

Tree:

```text
    4
   / \
  2   7
 / \
1   3
```

Serialization:

```text
4,2,1,N,N,3,N,N,7,N,N
```

This gives both value order and shape.

---

## 10. Complexity

**“Time complexity:”**

### Serialization

* We visit every node once
* and also process null positions

So overall:

**O(n)**

---

### Deserialization

* We read each token once

So:

**O(n)**

---

**“Space complexity:”**

* recursion stack depends on tree height

So:

**O(h)**

where `h` is the height of the tree

Worst case for skewed tree:

**O(n)**

Balanced tree:

**O(log n)** recursion depth

Also, the serialized output itself takes **O(n)** space.

---

## 11. Why this solution is correct

**“This works because preorder tells me the order of roots, and null markers tell me exactly where subtrees stop.”**

So every recursive call consumes exactly the tokens for one subtree.

That is why deserialization reconstructs the same structure.

---

## 12. Alternative approach

**“We can also solve this using level-order traversal.”**

For example:

```text
1,2,3,N,N,4,5
```

Then rebuild the tree using a queue.

That approach is also correct.

But preorder + recursion is usually cleaner and easier to explain in interviews.

---

## 13. Follow-up Questions

### ❓ Why can’t we just store inorder traversal?

**“Because inorder alone is not enough to uniquely reconstruct the tree.”**

Many different trees can have the same inorder traversal.

---

### ❓ Why do we need null markers?

**“Without null markers, we lose the structure of the tree.”**

Values alone do not tell us where left or right children are missing.

---

### ❓ Why does preorder make deserialization easy?

**“Because the first token always represents the current root, so recursion can directly rebuild left and right subtrees in order.”**

---

### ❓ Could we use BFS instead?

**“Yes, level-order serialization is also valid, as long as nulls are included.”**

---

### ❓ Why do we use `self.index`?

**“Because during deserialization, recursive calls need to share one common pointer into the token list.”**

Without that shared pointer, each recursive call would not know where to continue reading.

---

### ❓ What if the tree is empty?

**“Then serialization returns just `N`, and deserialization correctly returns `None`.”**

---

## 14. 30-second version

**“I serialize the tree using preorder traversal and store `N` for null children. This preserves both values and structure. During deserialization, I read the tokens in preorder order: if the token is `N`, I return `None`; otherwise I create a node and recursively build its left and right subtrees. This takes O(n) time.”**

---

## 15. 10-second version

**“Use preorder traversal with null markers, then rebuild recursively in the same order.”**

---

## Final insight

**“The real problem is not storing the values—it is preserving the structure. Preorder plus null markers gives exactly enough information to reconstruct the tree uniquely.”**

---

