// Write Function to support generic linked list

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node // definition of node
{
    void *data;
    struct node *next;

} node;

typedef struct gll // definition of gll
{
    int dsize;
    struct node *list;
    int (*compareFn)(void *a, void *b);
    void (*printFn)(void *a);
} gll;

typedef struct gll *genericLL;
typedef char *string;

genericLL createGLL(int dsize, int (*cfunction)(void *, void *)) // makes and inserts node
{
    genericLL g;
    g = (gll *)malloc(sizeof(gll));

    g->dsize = dsize;
    g->list = NULL;
    g->compareFn = cfunction;

    return g;
}

void addNodeGLL(genericLL g, void *d) // add node in the end
{
    node *temp = (node *)malloc(sizeof(node));
    temp->data = malloc(g->dsize);
    memcpy(temp->data, d, g->dsize);
    temp->next = NULL;

    if (g->list == NULL)
        g->list = temp;
    else
    {
        node *temp2 = g->list;

        while (temp2->next != NULL)
            temp2 = temp2->next;

        temp2->next = temp;
    }
}

void addNodeGLLSorted(genericLL g, void *d) // add node to make ascending order
{
    node *temp = (node *)malloc(sizeof(node));
    temp->data = malloc(g->dsize);
    memcpy(temp->data, d, g->dsize);
    temp->next = NULL;

    if (g->list == NULL)
    {
        g->list = temp;
    }
    else
    {
        if (g->compareFn(temp->data, g->list->data) == -1)
        {
            temp->next = g->list;
            g->list = temp;
        }
        else
        {
            node *temp2 = g->list;

            while (!(((g->compareFn(temp2->data, temp->data) == -1) || g->compareFn(temp2->data, temp->data) == 0) && g->compareFn(temp2->next->data, temp->data) == 1))
                temp2 = temp2->next;

            temp->next = temp2->next;
            temp2->next = temp;
        }
    }
}

int isPresentGLL(genericLL g, void *d) // checks of value present in node
{
    node *temp = g->list;

    int pos = 1;
    int is_found = 0;

    while (temp != NULL)
    {
        if (g->compareFn(temp->data, d) == 0)
        {
            is_found = 1;
            return pos;
        }

        pos++;
        temp = temp->next;
    }

    if (is_found == 0)
        return 0;
}

int deleteNodeGLL(genericLL g, void *d) // deletes node
{
    node *temp = g->list;
    int pos = 1;

    while (temp != NULL)
    {
        if (g->compareFn(temp->data, d) == 0)
        {
            if (temp == g->list)
                g->list = g->list->next;
            else
            {
                node *temp2 = g->list;
                while (temp2->next != temp)
                    temp2 = temp2->next;

                temp2->next = temp->next;
            }

            free(temp);
            return pos;
        }
        temp = temp->next;
        pos++;
    }
    return 0;
}

int getNodeDataGLL(genericLL g, int i, void *d) // give output of ith node
{
    int pos = 1;
    node *temp = g->list;

    while (temp != NULL && pos != i)
    {
        temp = temp->next;
        pos++;
    }
    if (temp == NULL)
        return 0;

    memcpy(d, temp->data, g->dsize);
    return 1;
}

int int_compare(void *a, void *b) // compare function for int
{

    if (*(int *)a == *(int *)b)
        return 0;
    else if (*(int *)a < *(int *)b)
        return -1;
    else
        return 1;
}

// here a and b are of type string*
int string_compare(void *aPtr, void *bPtr)
{
    string a = *((string *)aPtr);
    string b = *((string *)bPtr);

    int compareResult = strcmp(a, b);

    if (compareResult == 0)
        return 0;
    else if (compareResult < 0)
        return -1;
    else
        return 1;
}

void main()
{
    genericLL g = createGLL(sizeof(string), string_compare); // makes stack

    char *a = "1";
    addNodeGLL(g, &a);
    printf("list = 1\n");

    char *b = "3";
    addNodeGLL(g, &b);
    printf("list = 1->3\n");

    char *c = "2";
    addNodeGLLSorted(g, &c);
    printf("list = 1->2->3\n");

    char *d = "4";
    addNodeGLL(g, &d);
    printf("list = 1->2->3->4\n");

    printf("isPresentNode for 2: %d\n", isPresentGLL(g, &c));

    printf("deleteNodeGLL() for 3 : %d\n", deleteNodeGLL(g, &b));
    printf("list = 1->2->4\n");

    string* ptr = (string*)malloc(sizeof(string));
    getNodeDataGLL(g, 3, (void *)ptr);
    printf("getNodeDataGLL for 3: %s\n", *ptr);
}