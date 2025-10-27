#include <stdio.h>
#include <ctype.h>
#include "list.h"

void displayMenu() {
    printf("\n--- MENU ---\n");
    printf("1 - Inserir produto (A - Alimentacao, H - Higiene, L - Limpeza, V - Vestuario)\n");
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
    char type_char;
    int count;

    // Inicializa a tabela
    if (!defineTable(hashTable)) {
        printf("Erro ao inicializar a tabela hash.\n");
        return 1;
    }

    printf("Tabela Hash de Produtos Inicializada com %d categorias.\n", NUM_TYPES);

    do {
        displayMenu();
        if (scanf(" %c", &option) != 1) { // Lendo a opção
            // Limpa o buffer de entrada em caso de falha de leitura
            while(getchar() != '\n');
            continue;
        }

        switch(option) {
            case '1': // Inserir produto
                printf("Digite a descricao do produto: ");
                // Limpa o buffer antes de ler a string (para evitar problemas com o '\n' anterior)
                while(getchar() != '\n'); 
                if (scanf(" %49[^\n]", description) != 1) { 
                    printf("Erro ao ler a descricao.\n");
                    break;
                }
                
                printf("Digite o tipo (A, H, L, V): ");
                scanf(" %c", &type_char);
                type_char = toupper(type_char); // Converte para maiúscula
                
                int index = hash(type_char);

                // Assumindo que o defineTable preencheu o campo category para exibição
                if (index != -1 && insert(&hashTable[index], description)) {
                    // Nota: Usamos 'A'/'H'/'L'/'V' como chave. O nome completo da categoria 
                    // (e.g., "Alimentacao") deve ser acessível via hashTable[index].category.
                    printf("Produto \"%s\" inserido com sucesso na categoria %s.\n", description, hashTable[index].category);
                } else {
                    printf("Falha na insercao. Tipo de produto invalido ou erro de memoria.\n");
                }
                break;

            case '2': // Consultar produtos
                printf("Digite o tipo a consultar (A, H, L, V): ");
                scanf(" %c", &type_char);
                type_char = toupper(type_char);
                
                searchByCategory(hashTable, type_char);
                break;

            case '3': // Contar produtos
                printf("\n--- Contagem de Produtos ---\n");
                
                // Itera sobre o array da Tabela Hash
                for (int i = 0; i < NUM_TYPES; i++) {
                    
                    // Nota: O hash deve ser baseado na chave (e.g., 'A'), mas como as categorias 
                    // foram preenchidas sequencialmente no defineTable, podemos usar a chave 
                    // da categoria para contagem se a chave não estiver armazenada no nó.
                    // Estou usando o primeiro caractere do nome da categoria como chave, 
                    // seguindo a lógica do seu código.
                    char key_for_count = hashTable[i].category[0]; 
                    
                    if (key_for_count != '\0') { // Verifica se a categoria foi definida
                        count = countByCategory(hashTable, key_for_count);
                        printf("%s (%c) - %d produto(s)\n", hashTable[i].category, key_for_count, count);
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

    // Libera a memória alocada
    for (int i = 0; i < NUM_TYPES; i++) {
        destroyList(&hashTable[i]);
    }
    
    return 0;
}
