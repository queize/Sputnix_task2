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
    {
        /*
            Тест 1
            Входные данные: [[10]]
            Выходные данные: [10]
        */
        ListNode *lists1 = new ListNode(10);
        std::vector<ListNode *> lists = {lists1};
        ListNode *sLists = mergeKLists(lists);
        std::cout << sLists << '\n';
    }
    {
        /*
            Тест 2
            Входные данные: [
                [1--> 4-->10],
                [2--> 3-->5],
            ]
            Выходные данные: [1--> 2--> 3--> 4--> 5-->10]
        */
        ListNode *lists1 = new ListNode(1 , new ListNode(4, new ListNode(10)));
        ListNode *lists2 = new ListNode(2 , new ListNode(3, new ListNode(5)));
        std::vector<ListNode *> lists = {lists1, lists2};
        ListNode *sLists = mergeKLists(lists);
        std::cout << sLists << '\n';    
    }
    {
        /*
            Тест 3
            Входные данные: [
                [(-10)--> 4--> 18-->21],
                [0--> 7-->8],
                [(-10)--> (-5)--> (-4)-->0]
            ]
            Выходные данные: [(-10)--> (-10)--> (-5)--> (-4)--> 0--> 0--> 4--> 7--> 8--> 18-->21]
        */
        ListNode *lists1 = new ListNode(-10, new ListNode(4, new ListNode(18, new ListNode(21))));
        ListNode *lists2 = new ListNode(0, new ListNode(7, new ListNode(8)));
        ListNode *lists3 = new ListNode(-10, new ListNode(-5, new ListNode(-4, new ListNode(0))));

        std::vector<ListNode *> lists = {lists1, lists2, lists3};
        ListNode *sLists = mergeKLists(lists);
        std::cout << sLists << '\n';
    }

}