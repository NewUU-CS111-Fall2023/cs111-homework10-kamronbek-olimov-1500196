class problem1 {
public:
    ListNode* mergeNodes(ListNode* head) {
        if(head == NULL) {
            return NULL;
        }

        ListNode* current = head->next;
        ListNode* node = head;
        int sum = 0;

        while(current) {
            while(current->val != 0) {
                sum += current->val;
                current = current->next;
            }

            node->next = new ListNode(sum);
            node = node->next;

            sum = 0;
            current = current->next;
        }

        return head->next;
    }
};
