# Interview Script

**“I’ll first explain my approach clearly.”**

We are given `numCourses` and a list of prerequisites, where:

* `[a, b]` means:
  👉 to take course `a`, you must first complete course `b`

So this is a **directed graph problem**, where:

* nodes = courses
* edges = dependencies (`b → a`)

Our goal is to check:
👉 **Is it possible to complete all courses?**

---

**“This reduces to detecting a cycle in a directed graph.”**

Because:

* If there is a cycle → impossible to finish all courses
* If no cycle → valid ordering exists

So I’ll use **Topological Sort (BFS – Kahn’s Algorithm)**.

---

# Approach Explanation

**“I’ll use indegree + BFS.”**

### Step 1: Build Graph

* Create adjacency list
* Create indegree array

```python
adj[b].append(a)
indegree[a] += 1
```

---

### Step 2: Push all nodes with indegree = 0

These are courses with **no prerequisites**

---

### Step 3: BFS

* Pick a node
* Reduce indegree of its neighbours
* If any neighbour becomes 0 → push into queue

---

### Step 4: Count processed nodes

* If processed nodes == total courses → ✅ possible
* Else → ❌ cycle exists

---

# Dry Run Script

**“Let me do a quick dry run.”**

```python
numCourses = 4
prerequisites = [[1,0],[2,1],[3,2]]
```

Graph:

```
0 → 1 → 2 → 3
```

Indegree:

```
0:0, 1:1, 2:1, 3:1
```

---

### Step 1:

Queue = `[0]`

---

### Step 2:

Process 0 → reduce indegree of 1
Queue = `[1]`

---

### Step 3:

Process 1 → reduce indegree of 2
Queue = `[2]`

---

### Step 4:

Process 2 → reduce indegree of 3
Queue = `[3]`

---

### Step 5:

Process 3

Total processed = 4 == numCourses

👉 **Answer = True**

---

# Cycle Case

```python
prerequisites = [[1,0],[0,1]]
```

Graph:

```
0 ↔ 1
```

No node has indegree 0 → queue empty

👉 processed = 0

👉 **Answer = False**

---

# Complexity Script

**“Now I’ll discuss time and space complexity.”**

Let:

* `V` = number of courses
* `E` = number of prerequisites

### Time Complexity:

* Build graph → `O(E)`
* BFS traversal → `O(V + E)`

👉 Total:

```python
O(V + E)
```

---

### Space Complexity:

* Adjacency list → `O(V + E)`
* Indegree array → `O(V)`

👉 Total:

```python
O(V + E)
```

---

# Code Explanation Script

```python
from collections import deque
from typing import List

class Solution:
    def canFinish(self, numCourses: int, prerequisites: List[List[int]]) -> bool:
        adj = [[] for _ in range(numCourses)]
        indegree = [0] * numCourses
        
        # build graph
        for a, b in prerequisites:
            adj[b].append(a)
            indegree[a] += 1
        
        queue = deque()
        
        # push nodes with indegree 0
        for i in range(numCourses):
            if indegree[i] == 0:
                queue.append(i)
        
        count = 0
        
        # BFS
        while queue:
            node = queue.popleft()
            count += 1
            
            for neigh in adj[node]:
                indegree[neigh] -= 1
                if indegree[neigh] == 0:
                    queue.append(neigh)
        
        return count == numCourses
```

---

# Code Explanation (Speak Like This)

**“First, I build the graph using an adjacency list and track indegrees.”**

**“Then I push all nodes with indegree 0 into the queue.”**

**“I perform BFS, and for each node, I reduce the indegree of its neighbours.”**

**“If any neighbour’s indegree becomes 0, I push it into the queue.”**

**“Finally, if I’m able to process all courses, I return True, otherwise False.”**

---

# Very Polished Interview Version

**“This problem can be modeled as detecting a cycle in a directed graph. I build the graph using an adjacency list and track indegrees of each node. Then I perform BFS using Kahn’s algorithm by pushing all nodes with indegree 0 into a queue. While processing, I reduce the indegree of neighbours and push new nodes with indegree 0. If I’m able to process all nodes, it means there is no cycle and all courses can be completed. Otherwise, a cycle exists.”**

---

# If Interviewer Asks “Why Topo Sort?”

**Answer:**

👉 *“Because topo sort only exists for DAGs. If we cannot generate a topo ordering, it means a cycle exists.”*

---

# Final 30-Second Script

**“I model the problem as a directed graph and use Kahn’s algorithm for topological sorting. I track indegrees and process nodes with indegree 0 using BFS. If I can process all courses, then it’s possible to finish; otherwise, a cycle exists.”**

---
