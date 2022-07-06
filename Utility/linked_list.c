#include "linked_list.h"




Node* CreateNode(){
    Node* new_node = malloc(sizeof(struct Node));
    if(new_node == NULL){
        printf("Error, couldn't allocate memory");
        return NULL;
    }

    new_node -> data = NULL;
    new_node -> next = NULL;

    return new_node;
}


void InsertNode(struct Node** head_ref, void* new_data)
    {
        struct Node* new_node =
                (struct Node*) malloc(sizeof(struct Node));

        struct Node *last = *head_ref;

        /*Put in the data*/
        new_node->data  = new_data;

        /*3. This new node is going to be the last node, so make next of it as NULL*/
        new_node->next = NULL;

        /*4. If the Linked List is empty, then make the new node as head*/
        if (*head_ref == NULL)
        {
            *head_ref = new_node;
            return;
        }

        /*5. Else traverse till the last node*/
        while (last->next != NULL) {
            last = last->next;
        }
        /* 6. Change the next of last node*/
        last->next = new_node;
        
   }



struct Node *SearchNode(Node* head, void *data, int(*cmp_func)(void*, void*)){
    while(head!= NULL)
    {
        if(cmp_func(data,head -> data) == 0)
            return head;

        head = head -> next;
    }

    return NULL;
}




