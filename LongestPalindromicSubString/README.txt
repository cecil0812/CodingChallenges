Given a string s, find the longest palindromic substring in s. You may assume that the maximum length of s is 1000.

Example 1:

Input: "babad"
Output: "bab"
Note: "aba" is also a valid answer.
Example 2:

Input: "cbbd"
Output: "bb"


The way I implemented this was in two different methods:

First was implementing Manacher's algorithm (https://en.wikipedia.org/wiki/Longest_palindromic_substring#Manacher's_algorithm).  Though I implemented it, I admit, I don't really understand it.

Second was by creating boundaries around the characters and then searching from the middle.  This is one of the problems I don't really get too well as my mind can't see palindromes that easily by itself, let alone code them.