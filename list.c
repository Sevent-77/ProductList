#include "list.h"
#include <stdlib.h>
#include <string.h>

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
    if (!l) return 0;                                                   //Proteção contra ponteiros nulos

    Node *new = (Node*) malloc(sizeof(Node));

    if (!new) return 0;                                                 //Falha de alocação

    new->next = l->head;                                                //Mudança dos ponteiros
    l->head = new;

    strcpy(new->description, description);                              //Copia dos dados

    return 1;
}

int searchByCategory(List table[NUM_TYPES], char category)
{

}

int countByCategory(List table[NUM_TYPES], char category)
{

}

int hash(char key)
{
    return key % NUM_TYPES;
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
