#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cofo.h"

#define TRUE 1
#define FALSE 0

// Estrutura CD com os quatro atributos
typedef struct {
    char nome[50];
    char genero[30];
    char data_lancamento[11];   // formato "YYYY-MM-DD"
    char nome_banda[50];
} CD;

// Função para criar um CD (aloca e preenche)
CD *criarCD(char *nome, char *genero, char *data, char *banda) {
    CD *cd = (CD *)malloc(sizeof(CD));
    if (cd != NULL) {
        strncpy(cd->nome, nome, 49);
        cd->nome[49] = '\0';
        strncpy(cd->genero, genero, 29);
        cd->genero[29] = '\0';
        strncpy(cd->data_lancamento, data, 10);
        cd->data_lancamento[10] = '\0';
        strncpy(cd->nome_banda, banda, 49);
        cd->nome_banda[49] = '\0';
    }
    return cd;
}

int compararNomeCD(void *a, void *b) {
    CD *cd = (CD *)a;
    char *nome = (char *)b;
    if (strcmp(cd->nome, nome) == 0) {
        return TRUE;
    } else {
        return FALSE;
    }
}

int compararGeneroCD(void *a, void *b) {
    CD *cd = (CD *)a;
    char *genero = (char *)b;
    if (strcmp(cd->genero, genero) == 0) {
        return TRUE;
    } else {
        return FALSE;
    }
}

int compararDataCD(void *a, void *b) {
    CD *cd = (CD *)a;
    char *data = (char *)b;
    if (strcmp(cd->data_lancamento, data) == 0) {
        return TRUE;
    } else {
        return FALSE;
    }
}

int compararBandaCD(void *a, void *b) {
    CD *cd = (CD *)a;
    char *banda = (char *)b;
    if (strcmp(cd->nome_banda, banda) == 0) {
        return TRUE;
    } else {
        return FALSE;
    }
}
// Impressão formatada de um CD
void imprimirCD(CD *cd) {
    if (cd) {
        printf("Nome: %s | Genero: %s | Data: %s | Banda: %s\n",
               cd->nome, cd->genero, cd->data_lancamento, cd->nome_banda);
    }
}

int main() {
    Cofo *cofo = NULL;
    int opcao;
    int maxItens;
    CD *cd;

    // Critério para busca/remoção (agora 4 opções)
    int criterio;
    char buffer[50];  // para entrada de strings

    // Strings para criação do CD
    char nome[50], genero[30], data[11], banda[50];

    do {
        printf("\n=== MENU CD ===\n");
        printf("1. Criar cofo\n");
        printf("2. Inserir CD\n");
        printf("3. Listar CDs\n");
        printf("4. Consultar CD\n");
        printf("5. Remover CD\n");
        printf("6. Esvaziar cofo\n");
        printf("7. Destruir cofo\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); // limpa o '\n' deixado pelo scanf

        switch (opcao) {
            case 1:
                if (cofo != NULL) {
                    printf("Cofo ja criado.\n");
                } else {
                    printf("Tamanho maximo do cofo: ");
                    scanf("%d", &maxItens);
                    getchar();
                    cofo = cofCreate(maxItens);
                    if (cofo) {
                        printf("Cofo criado com sucesso.\n");
                    } else {
                        printf("Erro ao criar o cofo.\n");
                    }
                }
                break;

            case 2:
                if (cofo == NULL) {
                    printf("Crie o cofo primeiro.\n");
                    break;
                }

                printf("Nome do CD: ");
                fgets(nome, 50, stdin);
                nome[strcspn(nome, "\n")] = '\0';

                printf("Genero: ");
                fgets(genero, 30, stdin);
                genero[strcspn(genero, "\n")] = '\0';

                printf("Data de lancamento (AAAA-MM-DD): ");
                fgets(data, 11, stdin);
                data[strcspn(data, "\n")] = '\0';

                printf("Nome da banda: ");
                fgets(banda, 50, stdin);
                banda[strcspn(banda, "\n")] = '\0';

                cd = criarCD(nome, genero, data, banda);
                if (cd == NULL) {
                    printf("Erro ao alocar memoria.\n");
                    break;
                }

                if (cofInsert(cofo, cd)) {
                    printf("CD inserido com sucesso.\n");
                } else {
                    printf("Erro ao inserir CD – cofo cheio ou entrada invalida.\n");
                    free(cd);
                }
                break;

            case 3:
                if (cofo == NULL) {
                    printf("Crie o cofo primeiro.\n");
                    break;
                }
                cd = (CD *)cofGetFirst(cofo);
                if (cd == NULL) {
                    printf("Cofo vazio.\n");
                }
                while (cd != NULL) {
                    imprimirCD(cd);
                    cd = (CD *)cofGetNext(cofo);
                }
                break;

            case 4:
                if (cofo == NULL) {
                    printf("Crie o cofo primeiro.\n");
                    break;
                }
                printf("Consultar por:\n");
                printf("1 - Nome\n2 - Genero\n3 - Data de lancamento\n4 - Banda\n");
                scanf("%d", &criterio);
                getchar();

                cd = NULL;
                switch (criterio) {
                    case 1:
                        printf("Nome: ");
                        fgets(buffer, 50, stdin);
                        buffer[strcspn(buffer, "\n")] = '\0';
                        cd = (CD *)cofQuery(cofo, buffer, compararNomeCD);
                        break;
                    case 2:
                        printf("Genero: ");
                        fgets(buffer, 30, stdin);
                        buffer[strcspn(buffer, "\n")] = '\0';
                        cd = (CD *)cofQuery(cofo, buffer, compararGeneroCD);
                        break;
                    case 3:
                        printf("Data (AAAA-MM-DD): ");
                        fgets(buffer, 11, stdin);
                        buffer[strcspn(buffer, "\n")] = '\0';
                        cd = (CD *)cofQuery(cofo, buffer, compararDataCD);
                        break;
                    case 4:
                        printf("Banda: ");
                        fgets(buffer, 50, stdin);
                        buffer[strcspn(buffer, "\n")] = '\0';
                        cd = (CD *)cofQuery(cofo, buffer, compararBandaCD);
                        break;
                    default:
                        printf("Criterio invalido.\n");
                        break;
                }

                if (cd != NULL) {
                    printf("CD encontrado:\n");
                    imprimirCD(cd);
                } else {
                    printf("CD nao encontrado.\n");
                }
                break;

            case 5:
                if (cofo == NULL) {
                    printf("Crie o cofo primeiro.\n");
                    break;
                }
                printf("Remover por:\n");
                printf("1 - Nome\n2 - Genero\n3 - Data de lancamento\n4 - Banda\n");
                scanf("%d", &criterio);
                getchar();

                cd = NULL;
                switch (criterio) {
                    case 1:
                        printf("Nome: ");
                        fgets(buffer, 50, stdin);
                        buffer[strcspn(buffer, "\n")] = '\0';
                        cd = (CD *)cofRemove(cofo, buffer, compararNomeCD);
                        break;
                    case 2:
                        printf("Genero: ");
                        fgets(buffer, 30, stdin);
                        buffer[strcspn(buffer, "\n")] = '\0';
                        cd = (CD *)cofRemove(cofo, buffer, compararGeneroCD);
                        break;
                    case 3:
                        printf("Data (AAAA-MM-DD): ");
                        fgets(buffer, 11, stdin);
                        buffer[strcspn(buffer, "\n")] = '\0';
                        cd = (CD *)cofRemove(cofo, buffer, compararDataCD);
                        break;
                    case 4:
                        printf("Banda: ");
                        fgets(buffer, 50, stdin);
                        buffer[strcspn(buffer, "\n")] = '\0';
                        cd = (CD *)cofRemove(cofo, buffer, compararBandaCD);
                        break;
                    default:
                        printf("Criterio invalido.\n");
                        break;
                }

                if (cd != NULL) {
                    printf("CD removido:\n");
                    imprimirCD(cd);
                    free(cd);
                } else {
                    printf("CD nao encontrado.\n");
                }
                break;

            case 6:
                if (cofo != NULL) {
                    cofEsvaziar(cofo);
                    printf("Cofo esvaziado.\n");
                } else {
                    printf("Crie o cofo primeiro.\n");
                }
                break;

            case 7:
                if (cofo != NULL) {
                    if (cofDestroy(cofo)) {
                        cofo = NULL;
                        printf("Cofo destruido.\n");
                    } else {
                        printf("Nao pode destruir um cofo que ainda tem elementos.\n");
                    }
                } else {
                    printf("Crie o cofo primeiro.\n");
                }
                break;

            case 0:
                printf("Encerrando programa.\n");
                break;

            default:
                printf("Opcao invalida.\n");
        }
    } while (opcao != 0);

    return 0;
}