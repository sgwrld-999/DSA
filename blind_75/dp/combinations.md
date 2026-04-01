# ✅ Python Code

```python
class Solution:
    def find_combinations(self, candidates, target, index, current_list):
        
        if target == 0:
            self.result.append(current_list.copy())
            return 

        if index == len(candidates):
            return

        # not take
        self.find_combinations(candidates, target, index + 1, current_list)

        # take
        if target >= candidates[index]:
            current_list.append(candidates[index])
            self.find_combinations(
                candidates,
                target - candidates[index],
                index,
                current_list
            )
            current_list.pop()

    def combinationSum(self, candidates, target):
        self.result = []
        self.find_combinations(candidates, target, 0, [])
        return self.result
```

---

# 🎤 Interview Script — Combination Sum

---

## 1. Opening

**“Let me restate the problem.”**

We are given:

* An array `candidates`
* A target value `target`

We need to:

> Find all unique combinations where the chosen numbers sum to target.

👉 Important:

* We can **reuse the same element multiple times**
* Order of elements does not matter

---

## 2. Intuition

**“At every index, I have two choices: take or not take.”**

👉 For each element:

* Either I include it in my combination
* Or I skip it

This naturally leads to a **recursion tree**

---

## 3. Recursive Idea (Backtracking)

**“Let me first explain the brute force recursion.”**

---

### State

```python
f(index, target, current_list)
```

👉 Meaning:

> At position `index`, can I build combinations that sum to `target`?

---

## 4. Base Cases

### ✅ Case 1:

```python
if target == 0:
```

👉 We found a valid combination

→ Store it in result

---

### ✅ Case 2:

```python
if index == len(candidates):
```

👉 No elements left → stop

---

## 5. Choices (Core Logic)

---

### ❌ Not Take

```python
move to next index
```

```python
f(index + 1, target)
```

---

### ✅ Take

```python
if candidates[index] <= target:
```

👉 Include element

```python
current_list.append(candidates[index])
```

👉 Reduce target

```python
f(index, target - candidates[index])
```

👉 NOTE:
We **do NOT increase index** because we can reuse the same element

---

### 🔁 Backtracking Step

```python
current_list.pop()
```

👉 Undo the choice

---

## 6. Dry Run

Example:

```text
candidates = [2,3,6,7], target = 7
```

👉 Path exploration:

* Take 2 → [2]

* Take 2 → [2,2]

* Take 3 → [2,2,3] ✅

* Take 7 → [7] ✅

---

## 7. Key Insight

**“This is not DP, this is backtracking.”**

👉 Why?

* We explore all possibilities
* Build combinations step-by-step
* Undo choices (pop)

---

## 8. Important Detail (Common Mistake)

**“We must store a copy of the list.”**

```python
self.result.append(current_list.copy())
```

👉 Because lists are mutable

---

## 9. Complexity

### Time Complexity

👉 Exponential:

```
O(2^n * k)
```

* `k` = average length of combination

---

### Space Complexity

* Recursion stack → O(target)
* Output space → depends on number of combinations

---

## 10. How to explain in interview

**“At each index, I decide whether to include the element or not. If I include it, I reduce the target and stay on the same index because reuse is allowed. If I skip it, I move to the next index. I use backtracking to explore all valid combinations.”**

---

## 11. 30-second answer

**“This is a backtracking problem where I explore take and not-take choices. If I take an element, I stay on the same index since reuse is allowed. I store valid combinations when target becomes zero.”**

---

## 12. 10-second answer

**“Backtracking with take/not-take, reuse allowed, and store when target = 0.”**

---

## 13. Closing line

**“The key idea is exploring all combinations using recursion and undoing choices using backtracking.”**

---

