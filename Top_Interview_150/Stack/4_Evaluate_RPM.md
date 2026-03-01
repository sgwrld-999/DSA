
# ================================
# SLIDING WINDOW MASTER NOTES
# CLI VERSION + INTERVIEW LOGIC
# ================================

# ------------------------------------------------
# 1. Minimum Size Subarray Sum
# Source: :contentReference[oaicite:0]{index=0}
# ------------------------------------------------

PROBLEM:
Given positive integers, find minimum length subarray with sum >= target.

INTERVIEW EXPLANATION:

1. Since all numbers are positive,
   expanding window increases sum,
   shrinking window decreases sum.

2. This guarantees monotonic behavior,
   so sliding window is optimal.

3. Algorithm:
   - Expand right pointer
   - Add to running sum
   - While sum >= target:
       update minimum length
       shrink from left

4. Why it works:
   Because positivity guarantees no future shrink will increase sum.

TIME COMPLEXITY: O(n)
SPACE COMPLEXITY: O(1)

TEMPLATE:
Expand → While valid shrink → Update answer

--------------------------------------------

# ------------------------------------------------
# 2. Longest Substring Without Repeating Characters
# Source: :contentReference[oaicite:1]{index=1}
# ------------------------------------------------

PROBLEM:
Find longest substring with all unique characters.

INTERVIEW EXPLANATION:

Invariant:
Window must always contain unique characters.

1. Expand right pointer.
2. If duplicate appears:
     shrink left until duplicate removed.
3. Update max length only when window valid.

KEY INSIGHT:
Shrink only when invariant breaks.

TIME COMPLEXITY: O(n)
SPACE: O(min(n, charset))

TEMPLATE:
Expand → If invalid shrink → Update max

--------------------------------------------

# ------------------------------------------------
# 3. Substring with Concatenation of All Words
# Source: :contentReference[oaicite:2]{index=2}
# ------------------------------------------------

PROBLEM:
Find starting indices where concatenation of all words appears.

KEY INSIGHT:
All words have equal length.

INTERVIEW EXPLANATION:

1. Treat string as token stream (word-sized jumps).
2. Use word frequency map.
3. Slide window in steps of word_len.
4. Maintain word counts.
5. If frequency exceeds → shrink.
6. If word count matches → record index.

CRITICAL DETAIL:
Must try offsets from 0 to word_len - 1.

TIME COMPLEXITY: O(n)
SPACE: O(k)

TEMPLATE:
Token window, not character window.

--------------------------------------------

# ------------------------------------------------
# 4. Minimum Window Substring
# Source: :contentReference[oaicite:3]{index=3}
# ------------------------------------------------

PROBLEM:
Smallest substring containing all chars of t (including duplicates).

INTERVIEW EXPLANATION:

Invariant:
Window must contain all required characters.

1. Build frequency map of t.
2. required = len(t)
3. Expand right:
      if char needed → required--
4. When required == 0:
      window valid
      try shrinking from left
      update minimum
5. Stop when window invalid again.

IMPORTANT:
Allow negative counts.
Negative means extra chars.

TIME COMPLEXITY: O(n)
SPACE: O(1) (bounded charset)

TEMPLATE:
Expand until valid → Shrink until invalid → Track minimum

--------------------------------------------

# ================================
# SLIDING WINDOW INTERVIEW SUMMARY
# ================================

There are only 3 core patterns:

1. FIXED WINDOW
   Example: max sum of size k

2. VARIABLE WINDOW - MAXIMIZE
   Example: longest substring without repeating

3. VARIABLE WINDOW - MINIMIZE
   Example: minimum size subarray
            minimum window substring

--------------------------------------------

# UNIVERSAL INTERVIEW STRUCTURE

When interviewer asks:

Explain like this:

1. Identify invariant.
2. Explain why sliding window works.
3. Explain when to shrink.
4. Mention time complexity O(n).
5. Mention why pointers only move forward.

--------------------------------------------

# MASTER RULE

Expand → Check invariant → Shrink if broken → Update answer

--------------------------------------------

# IF YOU FORGET EVERYTHING

Ask yourself:

What makes window valid?
When does it become invalid?
Is problem minimizing or maximizing?

That determines everything.

=================================
END OF NOTES
=================================

