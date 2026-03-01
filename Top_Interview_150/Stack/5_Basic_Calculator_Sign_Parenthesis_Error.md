
## Problem in one line

Evaluate a string mathematical expression containing:
- digits
- '+' and '-'
- parentheses '(' and ')'

Return the computed integer result.

---

## Core Idea (Very Important)

We maintain three variables:

res   → Running evaluated result  
cur   → Current number being built digit by digit  
sign  → Tracks whether current number is +1 or -1  

Stack is used to handle parentheses context.

The golden invariant:

> res always represents a correctly evaluated prefix expression.

---

## Correct Flow of the Algorithm

### When digit appears

Build number:

cur = cur * 10 + digit

---

### When '+' or '-' appears

First, finish previous number:

res += sign * cur

Then:

cur = 0  
Update sign accordingly

+  → sign = 1  
-  → sign = -1  

IMPORTANT:
Never subtract manually.
Always use:
res += sign * cur

---

### When '(' appears

We are entering a new nested level.

Save current context:

stack.append(res)
stack.append(sign)

Reset:

res = 0  
sign = 1  

Now we evaluate inner expression independently.

---

### When ')' appears

Finish inner expression first:

res += sign * cur
cur = 0

Now restore outer context:

res *= stack.pop()     # sign before bracket
res += stack.pop()     # result before bracket

---

## The Exact Mistake That Causes Error

Wrong logic used:

elif ch == '-':
    res -= (cur * sign)
    sign = 1
    cur = 0

Why this is wrong:

You are:
1. Subtracting manually
2. Still maintaining a sign variable

This mixes two different paradigms.

Correct version:

elif ch == '-':
    res += sign * cur
    sign = -1
    cur = 0

---

## Why Parentheses Expose the Bug

Parentheses logic assumes:

res is always correct before pushing to stack.

But when you manually subtract:

res becomes corrupted.

Then when '(' appears:

You push a wrong res into stack.

Later when ')' appears:

You restore using:

res *= saved_sign  
res += saved_res  

Since saved_res was already wrong,
final answer becomes incorrect.

Parentheses do NOT cause the error.
They amplify the incorrect state.

---

## Example That Breaks Buggy Code

Expression:

(1 - 2)

Buggy flow:

At '-':
res -= (1 * 1)
res = -1     ❌ incorrect

Correct should be:

res = 1
sign = -1

Then final becomes wrong.

---

## Mental Model You Must Lock In

Once you maintain a sign variable:

You NEVER manually subtract.

You ALWAYS:

res += sign * cur

Only change sign.

---

## Interview-Ready Explanation

If asked:

"Why were parentheses causing wrong answer?"

Say:

Parentheses were not the root issue.  
The bug was inconsistent sign handling.  
Since I manually subtracted while also tracking sign,  
I violated the invariant that res always holds a correctly evaluated prefix.  
Parentheses rely on that invariant to restore context properly.  
Thus they amplified the incorrect intermediate state.

---

## Time and Space Complexity

Time:  O(n)  
Space: O(n) in worst case due to stack  

---

## Final Takeaway

Parentheses create nested evaluation levels.  
They depend on correct state preservation.  

If your state (res + sign handling) is wrong,  
parentheses will propagate that error.

Golden Rule:

Maintain one consistent evaluation model.

