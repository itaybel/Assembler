#include "LinkedList.h"





/*
This function is used to allocate memory and create a new node
@return a pointer to the new empty node
*/

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


/*
This function is used insert a new node to the linked list
@param head_ref - the current head of the linked list
@param new_data - the data of the new node to be added
*/
void InsertNode(Node** head_ref, void* new_data)
{
    
    /* Allocate node*/ 
    Node* new_node = CreateNode();

    /*put in the data*/
    new_node->data  = malloc(sizeof(new_data));

    new_node->data  = new_data;
    if (!(*head_ref)) /* if the list is empty */
    {
        *head_ref = new_node;

    }else{

        /*Make next of new node as head*/
        new_node->next = (*head_ref);

        /*move the head to point to the new node*/

        (*head_ref)  = new_node;
    }
}


/*
This function is used to search for a specific node in a linked list
@param head - the current head of the linked list
@param data - the data to search
@param cmp_func - a function that compares between nodes and the data
@return the found node, 0 if it couldn't be found
*/
Node* SearchNode(Node* head, void *data, int(*cmp_func)(void*, void*)){

    while(head != NULL){

        if(cmp_func(head -> data, data) == 0){
            return head;
        }
        head = head -> next;
    }
    return NULL;
}



/*
This function is used to free a linked list
@param head - the current head of the linked list
@param free_func - the function that frees each node invidually
@return none
*/
void freeList(Node* head, void(*free_func)(void*)){
    if(head != NULL){
        freeList(head->next, free_func);
        free_func(head);
    }
}