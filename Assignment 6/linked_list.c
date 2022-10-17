/**
 * @file linked_list.c
 * @author Abhiroop Mukherjee (510519109.abhirup@students.iiests.ac.in)
 * @date 2022-09-12
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define STR_SIZE 10

typedef struct ll_node ll_node;

struct ll_node
{
    int scope;
    char *var_type;
    char *var_name;
    ll_node *next;
};

ll_node *create_node(int scope, char *var_type, char *var_name)
{
    ll_node *ptr = (ll_node *)malloc(sizeof(ll_node));

    ptr->scope = scope;

    ptr->var_name = (char *)malloc(STR_SIZE);
    strcpy(ptr->var_name, var_name);

    ptr->var_type = (char *)malloc(STR_SIZE);
    strcpy(ptr->var_type, var_type);

    ptr->next = NULL;

    return ptr;
}

ll_node *free_node(ll_node *node)
{
    free(node->var_name);
    free(node->var_type);
    free(node);
    return NULL;
}

ll_node *ll_insert_start(ll_node *head, int scope, char *var_type, char *var_name)
{
    ll_node *ptr = create_node(scope, var_type, var_name);
    ptr->next = head;
    head = ptr;

    return head;
}

ll_node *ll_remove_scope(ll_node *head, int scopeNumber)
{
    if (head == NULL)
        return NULL;

    while (head != NULL && head->scope == scopeNumber)
    {
        ll_node *ptr = head;
        head = head->next;
        ptr = free_node(ptr);
    }

    return head;
}

ll_node *isPresent(ll_node *head, char* var_name)
{
    ll_node *ptr = head;

    while (ptr != NULL)
    {
        if (strcmp(ptr->var_name, var_name) == 0)
            return ptr;

        ptr = ptr->next;
    }

    return NULL;
}

// void printLL(ll_node *head)
// {
//     ll_node *ptr = head;

//     while (ptr != NULL)
//     {
//         printf("%d,%s,%s -> ", ptr->scope, ptr->var_name, ptr->var_type);
//         ptr = ptr->next;
//     }

//     printf("NULL\n");
// }

// void main()
// {
//     ll_node *head = ll_insert_start(NULL, 1, "int", "abc");
//     head = ll_insert_start(head, 1, "float", "ax");
//     head = ll_insert_start(head, 2, "long", "ass");
//     head = ll_insert_start(head, 3, "char", "ac");
//     head = ll_insert_start(head, 3, "int", "ad");
//     head = ll_insert_start(head, 3, "double", "ag");
//     head = ll_remove_scope(head, 3);
//     printLL(head);

//     ll_node *ptr = isPresent(head, "abc");
//     if(ptr != NULL)
//         printf("%d,%s,%s", ptr->scope, ptr->var_name, ptr->var_type);
// }

// NOTES

// 1)   making ll sorted by scope decending will make lookup
//      faster under the fact that generally variables
//      declared inside a scope are used more than the
//      varible defined before the scope start

// 2)   when a scope ends, all the the variables defined
//      inside the scope will be deleted, hence implementing (1)
//      essentailly becomes similar to stack,
//      i.e. add elements in the front for every variable in the curr scope
//      and delete all the entries from the front when the scpe gets over