#ifndef HASHLIST_H
#define HASHLIST_H

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

/**
 * @brief Inicializa uma tabela (define o ponteiro de cabeça como NULL)
 * @param l Ponteiro para a tabela
 * @return 1 se sucesso, 0 caso contrário
 */
int defineTable(List table[NUM_TYPES]);


/* 
Nesse caso, é melhor fazer o hash antes de inserir e passar apenas a lista como parâmetro.
*/


/**
 * @brief Insere um novo produto (descrição) no início da fila
 * @param l Ponteiro para a lista
 * @param description String com a descrição do produto
 * @return 1 se sucesso, 0 se falha
 */
int insert(List *l, const char description[DESCRIPTION_SIZE]);

/**
 * @brief Mostra todos os produtos de uma categoria específica (A, H, L, V)
 * @param table Tabela hash
 * @param category Letra da categoria (A/H/L/V)
 * @return 1 se encontrou produtos, 0 se não havia nenhum
 */
int searchByCategory(List table[NUM_TYPES], char category);

/**
 * @brief Conta quantos produtos estão cadastrados em uma categoria específica
 * @param table Tabela hash
 * @param category Letra da categoria (A/H/L/V)
 * @return Quantidade de produtos
 */
int countByCategory(List table[NUM_TYPES], char category);

/**
 * @brief Função de hash: converte uma letra de tipo em um índice (0–3)
 * @param key Letra do tipo: A, H, L, V
 * @return Índice correspondente ou -1 se inválido
 */
int hash(char key);

/**
 * @brief Libera toda a memória alocada em uma lista
 * @param l Ponteiro para a lista
 * @return 1 se sucesso
 */
int destroyList(List *l);

#endif