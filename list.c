#include "list.h"
#include <stdlib.h>

int defineTable(List table[NUM_TYPES])
{
    for (int i = 0; i < NUM_TYPES; i++)
    {
        table[i].head = NULL;
        table[i].category[0] = '\0';
    }
}

int insert(List *l, const char description[DESCRIPTION_SIZE])
{

}

int searchByCategory(List table[NUM_TYPES], char category)
{

}

int countByCategory(List table[NUM_TYPES], char category)
{

}

int hash(char key)
{

}

int destroyList(List *l)
{
    if (!l) return 0;                                                   //Proteção contra ponteiros nulos

    l->category[0] = '\0';                                              //Remove a categoria;
    while (l->head)                                                     //Remove os itens
    {
        Node *aux = l->head;
        l->head = l->head->next;
        free(aux);
    }

    return 1;
}
