#include "linked_list.h"


struct Node
{
    void *data;
    struct Node *next;
};

linklist_t CreatLinkList(){
    linklist_t new_list = malloc(sizeof(struct Node));
    if(new_list == null){
        printf("error");
        return NULL;
    }

    new_list -> data = NULL;
    new_list -> next = NULL;

    return new_list;


}


void InserNode(struct Node** head_ref,int new_data)
    {
        struct Node* new_node =
                (struct Node*) malloc(sizeof(struct Node));

        struct Node *last = *head_ref;

        /*Put in the data*/
        new_node->data  = new_data;

        /*3. This new node is going to be the*/
        /*last node, so make next of it as NULL*/
        new_node->next = NULL;

        /*4. If the Linked List is empty, then make*/
        /*the new node as head*/
        if (*head_ref == NULL)
        {
            *head_ref = new_node;
            return;
        }

        /*5. Else traverse till the last node*/
        while (last->next != NULL) {
            last = last->next;

            /* 6. Change the next of last node*/
            last->next = new_node;
        }
   }



struct Node *SearchNode(linklist_t head, void *data, int(*cmp_func)(void*, void*)){
    while(head!= NULL)
    {
        if(cmp_func(data,head -> data) == 0)
            break;

        head = head -> next;
    }

    return head;
}




