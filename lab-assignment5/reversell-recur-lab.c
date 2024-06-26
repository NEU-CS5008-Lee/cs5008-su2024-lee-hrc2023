// Hendrick Chen
// chen.haoyang4@northeastern.edu
#include<stdio.h>
#include<stdlib.h>
typedef struct node
{
    int data;
    struct node *next;
}node_t;

typedef struct list{
    struct node* head;
}List;

/*-----creating the nodes----------*/
node_t* newNode(int num)
{
 
}
/*---creating linked list----*/
List* init_LL(){
    
}

/*---Insert the nodes at the begining of the list---*/
void insertFirst(List* l, int data){
    

}

/*----display the output--------*/
void display(List* l)
{
    node_t *temp;
    temp=l->head;
    while(temp!=NULL)
    {
        printf("%d->",temp->data);
        temp=temp->next;
    }
    printf("NULL\n");
}

/*-------reversing the linked list using recursion------*/
void reverse(List* l, node_t* ptr)
{
    //insert your code here
    if (ptr == NULL || ptr->next == NULL) {
        l->head = ptr; // Set the current node as the head of the list
        return;
    }

    reverse(l, ptr->next); // Recursion

    ptr->next->next = ptr; // Makes the next node's next pointer point
    // to the current node
    ptr->next = NULL;  // Break the old next node
    
}

/*----Free the nodes-----*/
void freenode(List* l){
  node_t *temp;
    while(l->head)
    {
        temp=l->head->next;
        free(l->head);
        l->head=temp;
    }  
    
}
/*-----Main program--------------*/
int main()
{
    List *list=init_LL();
    

    insertFirst(list,44);
    insertFirst(list,33);
    insertFirst(list,22);
    insertFirst(list,11);
    display(list);
    reverse(list,list->head);
    display(list);
    
    freenode(list);
    free(list);
    return 0;
}
