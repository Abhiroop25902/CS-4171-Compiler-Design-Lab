// Write Function to support generic linked list

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ------------------------- GenericLL Code Start -------------------------
typedef struct node // definition of node
{
    void *data;
    struct node *next;

} node;

typedef struct gll // definition of gll
{
    int dsize;
    node *list;
    int (*compareFn)(void *a, void *b);
    void (*printFn)(void *a);
} gll;

typedef gll *genericLL;
typedef char *string;

genericLL createGLL(int dsize, int (*cfunction)(void *, void *), void (*pfunction)(void *a)) // makes and inserts node
{
    genericLL g;
    g = (gll *)malloc(sizeof(gll));

    g->dsize = dsize;
    g->list = NULL;
    g->compareFn = cfunction;
    g->printFn = pfunction;

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

// d is address of the data to be inserted
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

/**
 * @brief give the position of d if present (1 indexed) or 0 if not found
 *
 * @param g  genericLL where you want to search
 * @param d d address of the data to be compared
 * @return int position of d if present (1 indexed) or 0 if not found
 */
int isPresentGLL(genericLL g, void *d) // checks of value present in node
{
    if (g == NULL)
    {
        printf("Error: genericLL is NULL");
        exit(-1);
    }

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

void printGLL(genericLL g)
{
    node *curr = g->list;

    while (curr != NULL)
    {
        g->printFn(curr->data);
        printf("->");
        curr = curr->next;
    }
    printf("NULL\n");
}

// ------------------------- GenericLL Code End ---------------------------

// ------------------------- Set Code Start -------------------------
// idea: an array of genericLL, whose index will be found by hashing the data, we add the data in the end

typedef struct gset
{
    int hashArraySize;
    genericLL *hashArray;
    int (*hashFn)(void *data);
} gset;

typedef struct gset *genericSet;

genericSet createSet(int dsize, int hashArraySize, int (*hfunction)(void *data), int (*cfunction)(void *a, void *b), void (*pfunction)(void *a))
{
    genericSet set;
    set = (gset *)malloc(sizeof(gset));

    set->hashArraySize = hashArraySize;
    set->hashArray = (genericLL *)malloc(hashArraySize * sizeof(genericLL));
    set->hashFn = hfunction;

    for (int i = 0; i < hashArraySize; i++)
        set->hashArray[i] = createGLL(dsize, cfunction, pfunction);

    return set;
}

// data is of type string*
void insertGSet(genericSet set, void *data)
{
    int hash = abs(set->hashFn(data));
    int arrSize = set->hashArraySize;
    int arrIdx = hash % arrSize;

    if (!isPresentGLL(set->hashArray[arrIdx], data))
        addNodeGLL(set->hashArray[arrIdx], data);
}

void printGSet(genericSet set)
{
    for (int i = 0; i < set->hashArraySize; i++)
        printGLL(set->hashArray[i]);
}

// ------------------------- Set Code End ---------------------------

// type of aPtr is string*
void string_print(void *aPtr)
{
    string s = *((string *)aPtr);

    printf("%s", s);
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

// https://www.geeksforgeeks.org/string-hashing-using-polynomial-rolling-hash-function/
// s is of type string*
int string_hash(void *str)
{
    string s = *((string *)str);
    int stringSize = strlen(s);

    const int p = 31, m = 1e9 + 7;
    int hash = 0;
    long p_pow = 1;
    for (int i = 0; i < stringSize; i++)
    {
        hash = (hash + (s[i] - 'a' + 1) * p_pow) % m;
        p_pow = (p_pow * p) % m;
    }
    return hash;
}

void main()
{
    // genericLL g = createGLL(sizeof(string), string_compare, string_print); // makes stack

    // char *a = "1";
    // addNodeGLL(g, &a);
    // printGLL(g);

    // char *b = "3";
    // addNodeGLL(g, &b);
    // printGLL(g);

    // char *c = "2";
    // addNodeGLLSorted(g, &c);
    // printGLL(g);

    // char *d = "4";
    // addNodeGLL(g, &d);
    // printGLL(g);

    // printf("isPresentNode for 2: %d\n", isPresentGLL(g, &c));

    // printf("deleteNodeGLL() for 3 : %d\n", deleteNodeGLL(g, &b));
    // printGLL(g);

    // string *ptr = (string *)malloc(sizeof(string));
    // getNodeDataGLL(g, 3, (void *)ptr);
    // printf("getNodeDataGLL for 3: %s\n", *ptr);

    genericSet set = createSet(sizeof(string), 5, string_hash, string_compare, string_print);
    char *a = "1";
    insertGSet(set, &a);
    insertGSet(set, &a);
    a = "2";
    insertGSet(set, &a);
    a = "3";
    insertGSet(set, &a);
    a = "4";
    insertGSet(set, &a);

    printGSet(set);
}