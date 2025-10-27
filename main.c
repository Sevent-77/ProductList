#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define NUM_TYPES 4
#define DESCRIPTION_SIZE 20
#define CATEGORY_SIZE 20

typedef struct Node
{
    char description[DESCRIPTION_SIZE];
    struct Node *next;
}Node;

typedef struct List
{
    char category[CATEGORY_SIZE];
    struct Node *head;
}List;

int hash(char key)
{
    return key % NUM_TYPES;
}

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
    if (!table)                                                         //Proteção contra ponteiros nulos
    {
        printf("Tabela invalida!\n");
        return 0;
    }

    int index = hash(category);

    int count = 0;
    while (table[index].category[0] != category && count < NUM_TYPES)   //Tratamento de uma possível colisão
    {
        index = (index + 1) % NUM_TYPES;
        count++;
    }

    if (count == NUM_TYPES) 
    {
        printf("Tipo não encontrado!\n");
        return 0;
    }

    printf("%s:", table[index].category);

    Node * aux = table[index].head;

    while(aux)
    {
        printf(" - %s",aux->description);                                 //Imprime todos os produtos da lista
        aux = aux->next;
    }
    printf("\n");

    return 1;
}

int countByCategory(List table[NUM_TYPES], char category)
{
    if (!table) return 0;                                               //Proteção contra ponteiros nulos

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


void displayMenu()
{
    printf("\n--- MENU ---\n");
    printf("1 - Inserir produto\n");
    printf("2 - Consultar todos os produtos de um tipo\n");
    printf("3 - Contar quantos produtos estao cadastrados em cada tipo\n");
    printf("4 - Sair\n");
    printf("Escolha uma opcao: ");
}

int main()
{
    List hashTable[NUM_TYPES];
    char option;
    char description[DESCRIPTION_SIZE];
    char all_type[CATEGORY_SIZE];
    char type_char;
    int count;

    if (!defineTable(hashTable))
    {
        printf("Erro ao inicializar a tabela hash.\n");
        return 1;
    }

    printf("Tabela hash de produtos inicializada com %d categorias.\n", NUM_TYPES);

    do
    {
        displayMenu();

        if (scanf(" %c", &option) != 1)
        {
            while (getchar() != '\n');                                  // Limpa o buffer de entrada em caso de falha de leitura
            continue;
        }

        switch (option)
        {
        case '1': // Inserir produto
        {
            printf("Digite a descricao do produto: ");                  //Tratamento de entrada
            while (getchar() != '\n');

            if (scanf(" %19s", description) != 1)
            {
                printf("Erro ao ler a descricao.\n");
                break;
            }

            printf("Digite o tipo: ");

            if (scanf(" %19s", all_type) != 1)
            {
                printf("Erro ao ler o tipo.\n");
                break;
            }

            all_type[0] = toupper(all_type[0]);
            type_char = all_type[0];

            int index = hash(type_char);

            int count = 0;
            while (hashTable[index].category[0] != type_char && hashTable[index].head && count < NUM_TYPES) //Procura o tipo ou um espaço vazio para inserir
            {
                index = (index + 1) % NUM_TYPES;
                count++;
            }

            if (count == NUM_TYPES)                                     //Não tem espaço na tabela
            {
                printf("Tabela cheia!\n");
                break;
            }

            if (!hashTable[index].head)                                 //Significa que essa categoria ainda não existe
                strcpy(hashTable[index].category, all_type);            //e deve ser inserida

            if (insert(&hashTable[index], description))
            {
                printf("Produto \"%s\" inserido com sucesso na categoria %s.\n", description, hashTable[index].category);
            }
            else
            {
                printf("Falha na insercao.\n");                         //Falha na alocação de memoria
            }
            break;
        }

        case '2': // Consultar produtos
        {
            printf("\nTipos válidos:");                        //Tratamento de entrada
            for (int i = 0; i < NUM_TYPES; i++)                         //Esse for para mostrar os tipos que a tabela possui
            {
                if (hashTable[i].head)
                {
                    printf(" - %c", hashTable[i].category[0]);
                }
            }
            printf("\nDigite o tipo a consultar: ");
            while (getchar() != '\n');

            scanf(" %c", &type_char);
            type_char = toupper(type_char);

            searchByCategory(hashTable, type_char);

            break;
        }

        case '3': // Contar produtos
            printf("\n--- Contagem de Produtos ---\n");

            for (int i = 0; i < NUM_TYPES; i++)
            {
                if (hashTable[i].head)
                {
                    type_char = hashTable[i].category[0];
                    count = countByCategory(hashTable, type_char);
                    printf("%s (%c) - %d produto(s)\n", hashTable[i].category, type_char, count);
                }
            }
            break;

        case '4': // Sair
            printf("Encerrando o programa e liberando a memoria...\n");
            break;

        default:
            printf("Opcao invalida. Tente novamente.\n");
        }
    } while (option != '4');

    for (int i = 0; i < NUM_TYPES; i++)                                             //Desaloca as listas da tabela
        destroyList(&hashTable[i]);

    return 0;
}
