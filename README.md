This C++ project implements an optimized algorithm to group rectangles into the minimum number of non-overlapping groups.
Rectangles that touch are considered overlapping by default (configurable in code).

The algorithm is designed for performance, using Interval Trees, Min-Heaps, and efficient sorting to achieve near O(n log n) runtime in practical scenarios.

📌 Problem Overview

Given N axis-aligned rectangles, the goal is to split them into the fewest possible groups such that:

No two rectangles in the same group overlap

(Default) Rectangles touching at edges/corners are considered overlapping

Overlap is determined using X and Y interval intersections

This problem appears in layout verification, spatial indexing, and EDA tooling.

📌 Assumptions

Touching rectangles are treated as overlapping (default).

You may change this by modifying two conditions inside runAlgorithm() (comments included).

Input rectangles are provided via dataset text files.

⚙️ Technologies & Requirements

Language: C++ (C++17 or newer)

OS Used: Windows 11

IDE Recommended: Visual Studio (Release build)

Dependencies: None (Interval tree implemented as a header file)

🔄 Algorithm Summary

The algorithm builds groups using:

Interval Trees to track overlapping on X-axis

Min-Heaps to efficiently determine the highest Y-value in each group

Vectors to store groups and rectangle metadata

Core Idea

A rectangle can be placed in a group if:

It does not horizontally overlap any rectangle in that group

It does not vertically overlap based on ordering

If no existing group fits, a new group is created.

Time Complexity

Average case: O(n log n)

Worst case: O(n²) (when nearly every rectangle forms its own group)

Space Complexity

O(n) due to vectors, interval trees, and heaps.
