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

int gSetSize(genericSet g)
{
    int count = 0;

    for (int i = 0; i < g->hashArraySize; i++)
    {
        node *temp = g->hashArray[i]->list;

        while (temp != NULL)
        {
            count++;
            temp = temp->next;
        }
    }

    return count;
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

const int HASH_ARR_SIZE = 2;
const int WORD_ARR_MAX_SIZE = 100000;
const int WORD_MAX_SIZE = 100;

/**
 * @brief Get the Words From File object
 *
 * @param filePath the path of the file
 * @return string* array of words from the filePath
 */
string *getWordsFromFile(const string filePath)
{
    string *wordArr = malloc(sizeof(string) * WORD_ARR_MAX_SIZE);

    for (int i = 0; i < WORD_ARR_MAX_SIZE; i++)
        wordArr[i] = NULL;

    int wordArrIdx = 0;
    char *word = (char *)malloc(sizeof(char) * WORD_MAX_SIZE);

    FILE *in_file = fopen(filePath, "r");

    if (in_file == NULL)
    {
        printf("Can't open %s for reading.\n", filePath);
        perror("File Open Error");
        exit(-1);
    }

    while (fscanf(in_file, "%s", word) != EOF)
    {
        if (wordArrIdx == WORD_ARR_MAX_SIZE)
        {
            printf("Programme Stopped, increase WORD_ARR_MAX_SIZE");
            exit(-1);
        }
        wordArr[wordArrIdx] = (char *)malloc(strlen(word) * sizeof(char));
        strcpy(wordArr[wordArrIdx], word);
        wordArrIdx++;
    }
    fclose(in_file);
    free(word);

    return wordArr;
}

/**
 * @brief
 *
 * @param wordArr
 * @return int length of the wordArr
 */
int wordArrLength(const string *wordArr)
{
    int size = 0;

    for (int i = 0; i < WORD_ARR_MAX_SIZE && wordArr[i] != NULL; i++)
        size++;

    return size;
}

/**
 * @brief add all the words in the genericSet and returns the resultant Set
 *
 * @param words
 * @return genericSet
 */
genericSet addWordsInSet(string *words)
{
    int idx = 0;
    genericSet set = createSet(sizeof(string), HASH_ARR_SIZE, string_hash, string_compare, string_print);

    while (idx < WORD_ARR_MAX_SIZE && words[idx] != NULL)
    {
        insertGSet(set, &words[idx]);
        idx++;
    }

    return set;
}

/**
 * @brief geives a list of words in the set
 *
 * @param g
 * @return string* array of words in set
 */
string *setToWords(genericSet g)
{
    string *wordArr = malloc(sizeof(string) * WORD_ARR_MAX_SIZE);

    for (int i = 0; i < WORD_ARR_MAX_SIZE; i++)
        wordArr[i] = NULL;

    int wordArrIdx = 0;

    for (int i = 0; i < g->hashArraySize; i++)
    {
        node *temp = g->hashArray[i]->list;

        while (temp != NULL)
        {
            string s = *((string *)temp->data);
            wordArr[wordArrIdx] = (char *)malloc(strlen(s) * sizeof(char));
            strcpy(wordArr[wordArrIdx], s);
            wordArrIdx++;
            temp = temp->next;
        }
    }

    return wordArr;
}

// const string FILE_PATH = "./hello_world.c";
const string FILE_PATH = "./question1.c";
const string OUTPUT_FILE_PATH = "./unique_words.txt";

void saveWordsToFile(string *words, const string outputFilePath)
{
    FILE *fout = fopen(outputFilePath, "w");

    if (fout == NULL)
    {
        perror("fopen() error");
        exit(-1);
    }

    for (int i = 0; i < WORD_ARR_MAX_SIZE && words[i] != NULL; i++)
        fprintf(fout, "%s\n", words[i]);

    fclose(fout);
}

void main()
{
    string *words = getWordsFromFile(FILE_PATH);

    // for (int i = 0; i < WORD_ARR_MAX_SIZE && words[i] != NULL; i++)
    //     printf("%s ", words[i]);
    // printf("\n");

    genericSet uniqueWordSet = addWordsInSet(words);
    string *uniqueWords = setToWords(uniqueWordSet);

    saveWordsToFile(uniqueWords, OUTPUT_FILE_PATH);

    // for (int i = 0; i < WORD_ARR_MAX_SIZE && uniqueWords[i] != NULL; i++)
    //     printf("%s ", uniqueWords[i]);
    // printf("\n");

    printf("Number of Words in the '%s': %d\n", FILE_PATH, wordArrLength(words));
    printf("Number of Unique Words in the '%s': %d\n", FILE_PATH, wordArrLength(uniqueWords));
}