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

}
