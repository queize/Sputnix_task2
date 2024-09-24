#include <iostream>
#include <vector>

struct ListNode { 
    int val; 
    ListNode* next; 
    ListNode() : val(0), next(nullptr) {} 
    ListNode(int x) : val(x), next(nullptr) {} 
    ListNode(int x, ListNode* next) : val(x), next(next) {} 
     
};

std::ostream &operator<<(std::ostream &out, const ListNode *list)
{
    while(list->next) {
        out << list->val << "->";
        list = list->next;
    }
    out << list->val;
    return out;
}

ListNode* merge2SortedLists(ListNode *l1, ListNode *l2)
{
    ListNode *head = new ListNode(0);
    ListNode *curr = head;
    while(l1 && l2) {
        if (l1->val < l2->val) {
            curr->next = l1;
            l1 = l1->next;
        } else {
            curr->next = l2;
            l2 = l2->next;
        }   
        curr = curr->next;
    }
    curr->next = (l1) ? l1 : l2;
    return head->next;
}

ListNode* mergeKLists(std::vector<ListNode*>& lists) { 
    if (lists.empty()) {
        return nullptr;
    } else if (lists.size() == 1)  {
        return lists[0];
    }
    
    ListNode *myList = merge2SortedLists(lists[0], lists[1]);
    for (size_t i = 2; i < lists.size(); ++i) {
        myList = merge2SortedLists(myList, lists[i]);
    }
    return myList;
}

int main()
{
    ListNode *lists1 = new ListNode(1 , new ListNode(4, new ListNode(10)));
    ListNode *lists2 = new ListNode(2 , new ListNode(3, new ListNode(5)));
    ListNode *lists3 = new ListNode(-10, new ListNode(0, new ListNode(3, new ListNode(11))));
    ListNode *lists4 = new ListNode(-21, new ListNode(21));

    std::vector<ListNode *> lists = {lists1, lists2, lists3, lists4};
    ListNode *sLists = mergeKLists(lists);
    std::cout << sLists;
}