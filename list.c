#include "list.h"
#include <stdlib.h>

int define(List *l)
{
    l->head = NULL;
    l->category[0] = '\0';
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

}
