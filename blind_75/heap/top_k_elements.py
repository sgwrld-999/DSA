# Interview Script

**“I’ll first explain my approach clearly.”**

We need to return the `k` elements that appear most frequently in the array.
So the first natural step is to count how many times each number appears.

I’ll use a hash map for that, where:

* key = number
* value = frequency

For example, if `nums = [1,1,1,2,2,3]`, then the frequency map becomes:

* `1 -> 3`
* `2 -> 2`
* `3 -> 1`

---

**“Now the question is how to get the top k frequent elements efficiently.”**

One simple way is:

* build the frequency map
* sort all elements by frequency in descending order
* take the first `k`

That works, but sorting all unique elements takes `O(m log m)`, where `m` is the number of unique elements.

We can do better using a **min heap of size k**.

---

**“Why min heap?”**

Because while scanning all unique elements, I only want to keep track of the best `k` candidates seen so far.

So I push pairs like:

```python
(frequency, number)
```

into a min heap.

The heap is useful because:

* the smallest frequency stays at the top
* if the heap size becomes greater than `k`, I remove the smallest frequency element

That means the heap always stores the current top `k` most frequent elements.

So in short:

* push every `(freq, num)` into heap
* if size exceeds `k`, pop once
* after processing everything, heap contains the answer

---

# Dry Run Script

**“Let me do a quick dry run.”**

Suppose:

```python
nums = [1,1,1,2,2,3], k = 2
```

Frequency map:

* `1 -> 3`
* `2 -> 2`
* `3 -> 1`

Now process each pair:

### Step 1:

Push `(3, 1)`
Heap = `[(3, 1)]`

### Step 2:

Push `(2, 2)`
Heap = `[(2, 2), (3, 1)]`

### Step 3:

Push `(1, 3)`
Heap = `[(1, 3), (3, 1), (2, 2)]`

Now heap size is 3, but `k = 2`, so pop once.

Pop smallest frequency:
remove `(1, 3)`

Heap becomes:
`[(2, 2), (3, 1)]`

Now heap has the 2 most frequent elements: `2` and `1`.

So answer is `[2, 1]` or `[1, 2]`, depending on output order requirements.

---

# Complexity Script

**“Now I’ll discuss time and space complexity.”**

Let:

* `n` = total elements in input
* `m` = number of unique elements

### Step 1: Frequency map

This takes `O(n)`

### Step 2: Heap operations

For each unique element, I do one push.
Each push/pop costs `O(log k)`

So this part takes `O(m log k)`

### Total time:

```python
O(n + m log k)
```

In the worst case, `m` can be `n`, so:

```python
O(n log k)
```

### Space complexity:

* frequency map: `O(m)`
* heap: `O(k)`

So overall:

```python
O(m)
```

---

# Why This Is Better Than Sorting

**“This is better than sorting when k is small compared to the number of unique elements.”**

Because sorting all unique elements costs:

```python
O(m log m)
```

But heap only maintains `k` elements, so it costs:

```python
O(m log k)
```

When `k << m`, heap is more efficient.

---

# Code Explanation Script

You can explain the code like this:

```python
import heapq
from typing import List

class Solution:
    def topKFrequent(self, nums: List[int], k: int) -> List[int]:
        freq_map = {}

        for num in nums:
            freq_map[num] = freq_map.get(num, 0) + 1

        min_heap = []

        for num, freq in freq_map.items():
            heapq.heappush(min_heap, (freq, num))

            if len(min_heap) > k:
                heapq.heappop(min_heap)

        result = []

        while min_heap:
            result.append(heapq.heappop(min_heap)[1])

        return result
```

Then say:

**“In this code, first I count frequencies using `freq_map`.”**

**“Then I iterate through all unique numbers and push `(frequency, number)` into the min heap.”**

**“If the heap grows larger than `k`, I remove the smallest frequency element.”**

**“At the end, the heap contains exactly the top `k` frequent elements, so I extract the numbers and return them.”**

---

# Very Polished Interview Version

Here is a smoother version you can speak in one go:

**“My approach is to first count the frequency of each element using a hash map. After that, instead of sorting all elements by frequency, I use a min heap of size `k`. For each unique element, I push `(frequency, element)` into the heap. If the heap size exceeds `k`, I pop the smallest frequency element. This way, the heap always stores the `k` most frequent elements seen so far. At the end, I extract the elements from the heap and return them. The time complexity is `O(n + m log k)`, where `m` is the number of unique elements, and the space complexity is `O(m)` for the frequency map.”**

---

# If Interviewer Asks “Why Not Max Heap?”

You can say:

**“A max heap would also work, but then I would need to insert all unique elements and pop `k` times. That would take `O(m log m)` or `O(m + k log m)` depending on implementation. With a min heap of size `k`, I only keep the top `k` candidates at all times, which is more space-efficient and usually faster when `k` is small.”**

---

# If Interviewer Asks “Can We Do Better?”

You can say:

**“Yes, we can also solve this using bucket sort in linear time, because the maximum possible frequency of an element is `n`. We can group numbers by frequency and then collect the top `k`. That gives `O(n)` time in the average sense, but the heap solution is often easier to explain and very interview-friendly.”**

---

# Final 30-Second Script

If you want a short version to memorize:

**“I first count frequencies using a hash map. Then I maintain a min heap of size `k`, where each entry is `(frequency, number)`. For every unique number, I push it into the heap, and if the heap size exceeds `k`, I pop the smallest frequency. This ensures the heap always contains the top `k` most frequent elements. Finally, I extract the numbers from the heap. This takes `O(n + m log k)` time and `O(m)` space.”**

---

