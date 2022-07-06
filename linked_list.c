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


struct Node *SearchNode(linklist_t head, void *data, int(*cmp_func)(void*, void*)){
    while(head!= NULL)
    {
        if(cmp_func(data,head -> data) == 0)
            break;

        head = head -> next;
    }

    return head;
}




