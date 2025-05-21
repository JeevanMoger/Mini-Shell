#include "main.h"

extern char input_string[100];
extern pid_t child;
int insert_at_last(stop_list **head)
{
    stop_list *new = malloc(sizeof(stop_list));
    if(new == NULL)
	    return 1;
    new-> pid = child;
    strcpy(new -> command,input_string);
    new->link=NULL;
    if(*head == NULL)
    {
	    *head=new;
        return 1;
    }
    stop_list *temp=*head;
    while(temp->link!=NULL)
    {
	    temp=temp->link;
    }
    temp->link=new;
    return 1;
}

void print_list(stop_list *head)
{
    while(head != NULL)
    {
        printf("PID : %d Command : %s\n",head -> pid ,head -> command);
        head = head -> link;
    }
}

int delete_at_last(stop_list **head)
{
    if(*head == NULL)
        return 0;
    stop_list *temp=*head;
    stop_list *temp1=NULL;
    if((*head)->link == NULL)
    {
        *head=NULL;
        free(temp);
        return 1;
    }
    while(temp->link!=NULL)
    {
        temp1=temp;
        temp=temp->link;
    }
    temp1->link=NULL;
    free(temp);
}

