#include "list.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int defineTable(List table[NUM_TYPES])
{
    for (int i = 0; i < NUM_TYPES; i++)
    {
        table[i].head = NULL;
        table[i].category[0] = '\0';
    }

    return 1;
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
    if (!table) return 0;   

    int position = hash(category);
    if(position == -1) return 0;
    
    Node * curr = table[position].head;
    while(curr != NULL)
    {
        printf("%s ",curr->description);
        curr = curr->next;
    }
    printf("\n");
    return 1;
}

int countByCategory(List table[NUM_TYPES], char category)
{
    int index = hash(category);

    int count = 0;
    while (table[index].category[0] != category && count < NUM_TYPES)   //Tratamento de uma possível colisão
    {
        index = (index + 1) % NUM_TYPES;
        count++;
    }

    if (count == NUM_TYPES) return 0;                                   //Significa que a categoria não existe

    Node *aux = table[index].head;

    int counter = 0;
    while (aux)                                                         //Conta a quantidade iterando a lista
    {
        counter++;
        aux = aux->next;
    }

    return counter;
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
