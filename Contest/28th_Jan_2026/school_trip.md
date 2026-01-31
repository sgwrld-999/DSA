# School Trip — Minimum Mind Changes Notes

---

## Problem Goal (Short)

We want:

Number of students going on trip must be divisible by `K`.

We can change student decisions (yes ↔ no).

We must minimize number of changes.

It is allowed that:

```
0 students go
```

---

## Variables Meaning

```
N → Total students
X → Students currently saying YES
K → Bus capacity (must fill fully)
```

---

## Core Requirement

Final number of YES students must be:

```
Multiple of K
```

Because:

```
No partially filled buses allowed
```

---

## Core Mathematical Translation

We want to convert `X` into nearest multiple of `K`.

By:

* Removing YES students OR
* Adding YES students (from NO students)

---

## Why We Use Modulo

```
sub = X % K
```

Meaning:

How many extra students exist after forming full buses.

Example:

```
X = 14
K = 5

14 % 5 = 4
```

Meaning:

```
We have 2 full buses (10 students)
+ 4 extra students (problem)
```

---

## Two Possible Fix Directions

### Option 1 — Remove Students

Remove extra students:

```
Remove = sub
```

Example:

```
Remove 4 → 14 → 10 → Valid
```

---

### Option 2 — Add Students

Add students to reach next multiple:

```
Add = K - sub
```

Example:

```
Add = 5 - 4 = 1
14 → 15 → Valid
```

---

## Key Constraint

We can only add if enough NO students exist.

NO students:

```
N - X
```

---

## Why We Cannot Always Add

If:

```
Required Add > Available NO students
```

Then adding is impossible.

So we must remove.

---

## Code Logic Mapping

### Step 1 — Find Extra

```
sub = X % K
```

---

### Step 2 — Find Required Add

```
more = K - sub
```

---

### Step 3 — Decide Best Option

```
If enough NO students exist:
    choose min(remove, add)
Else:
    must remove
```

---

## Code Line Explanation

```
sub = min(sub, more) if N - X >= more else sub
```

Meaning:

If we can add:

```
Choose minimum cost option
```

Else:

```
Must remove extra students
```

---

## Brainstorm Q&A Section

---

### Q1 — Why do we calculate remainder first?

Because remainder directly tells:

```
How far we are from valid bus count
```

---

### Q2 — Why not directly round X to nearest multiple?

Because rounding might require adding students that don't exist.

Constraint:

```
Cannot create students
```

---

### Q3 — Why not always remove?

Because sometimes adding is cheaper.

Example:

```
X = 9
K = 5

Remove = 4
Add = 1
```

Better to add.

---

### Q4 — Why not always add?

Because maybe not enough NO students exist.

Example:

```
N = 10
X = 9
K = 5

Need Add = 1 → Possible

But if:
N = 9
X = 9
Need Add = 1 → Impossible
```

---

### Q5 — Why do we check `N - X >= more`?

Because:

```
N - X = Available NO students
more = Needed new YES students
```

If available NO < needed YES → Cannot add.

---

### Q6 — Why is removing always possible?

Because YES students always exist (since sub came from X).

---

### Q7 — Why is answer min(remove, add)?

Because goal:

```
Minimum mind changes
```

---

## Decision Visualization

```
If sub == 0
    Already valid → Answer = 0

Else
    remove_cost = sub
    add_cost = K - sub

    If add possible
        answer = min(remove_cost, add_cost)
    Else
        answer = remove_cost
```

---

## Edge Cases

---

### Case 1 — Already Perfect

```
X % K = 0
Answer = 0
```

---

### Case 2 — No One Going Allowed

If removing everything cheaper → allowed.

---

### Case 3 — Not Enough NO Students

Must remove only.

---

## Example Walkthrough

### Example

```
N = 5
X = 4
K = 2
```

```
sub = 4 % 2 = 0
Answer = 0
```

---

### Example

```
N = 5
X = 5
K = 3
```

```
sub = 2
add = 1
NO students = 0 → Cannot add
Answer = remove = 2
```

---

## Complexity

```
O(1) per test case
```

---

## Final Core Insight

We are choosing the cheapest way to move `X` to nearest multiple of `K`, under availability constraints.

---

## Mental Model

Think like:

You have groups of size `K`.

If group incomplete:
Either remove extra members
Or recruit new members

But recruiting requires available pool.

---


