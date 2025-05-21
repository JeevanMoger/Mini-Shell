#include "main.h"

stop_list *get_command_fg_bg(stop_list *head)
{
    if(head -> link == NULL)
        return head;
    while(head -> link != NULL)
    {
        head = head ->link;
    }
    return head;

}