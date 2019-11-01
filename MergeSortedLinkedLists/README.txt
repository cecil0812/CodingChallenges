Merge two sorted linked lists and return it as a new list. The new list should be made by splicing together the nodes of the first two lists.

Example:

Input: 1->2->4, 1->3->4
Output: 1->1->2->3->4->4


/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        
    }
};


There are two ways to do this, one way is to create a new list out of the two lists.  This is what my mind went to initially because in practice, I rarely want to destroy the two lists just to create a new one.

That said, there ARE use cases for this so I also implemented this using pointers.  This results in the destruction of the lists but gives the desired result.