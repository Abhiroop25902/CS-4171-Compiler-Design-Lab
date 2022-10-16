/**
 * @file hash_table.c
 * @author Abhiroop Mukherjee (510519109.abhirup@students.iiests.ac.in)
 * @date 2022-09-12
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "linked_list.c"

#define HASH_TABLE_SIZE 10

typedef struct hash_table hash_table;

struct hash_table
{
    ll_node *tab[HASH_TABLE_SIZE];
};

hash_table *create_hash_table()
{
    hash_table *ht = (hash_table *)malloc(HASH_TABLE_SIZE * sizeof(hash_table));
    for (int i = 0; i < HASH_TABLE_SIZE; i++)
        ht->tab[i] = NULL;
}

void hash_table_insert(hash_table *h, int scope, char *var_type, char *var_name)
{
    int ll_num = var_name[0] % HASH_TABLE_SIZE;

    ll_node *prev_var = isPresent(h->tab[ll_num], var_name);

    if (prev_var == NULL || prev_var->scope != scope)
        h->tab[ll_num] = ll_insert_start(h->tab[ll_num], scope, var_type, var_name);
    else if (prev_var->scope == scope){
        printf("Error in line %d: Variable %s already defined of type %s\n", yylineno, prev_var->var_name, prev_var->var_type);
        exit(1);
    }
}

void hash_table_end_scope(hash_table *ht, int scopeNo)
{
    for (int i = 0; i < HASH_TABLE_SIZE; i++)
        ht->tab[i] = ll_remove_scope(ht->tab[i], scopeNo);
}

bool hash_table_isPresent(hash_table *ht, char* var_name){
    int idx = var_name[0] % HASH_TABLE_SIZE;

    return isPresent(ht->tab[idx], var_name) != NULL;
}

// void printHash(hash_table *h)
// {
//     for (int i = 0; i < HASH_TABLE_SIZE; i++)
//     {
//         printLL(h->tab[i]);
//     }
// }

// void main()
// {
//     hash_table *ht = create_hash_table();

//     hash_table_insert(ht, 1, "int", "abc");
//     hash_table_insert(ht, 1, "float", "bx");
//     hash_table_insert(ht, 2, "long", "css");
//     hash_table_insert(ht, 3, "char", "dc");
//     hash_table_insert(ht, 3, "int", "da");
//     hash_table_insert(ht, 3, "double", "a");
//     printHash(ht);
//     printf("-------------------------------\n");
//     hash_table_end_scope(ht, 3);
//     printHash(ht);
// }