#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

#define TRUE 0
#define FALSE 1
#define DELIMITADORES ";\n";
#define FILE_NAME "dados_clientes1.csv"
#define FILE_SIZE 1024
#define MAX_LINE 300

typedef struct _cliente
{
    int numero;
    char *nome;
    char *telefone;
    float credito_max;

    struct _cliente *next;
}cliente;

cliente *head = NULL;

void encontrar_cliente(int nr)
{
    cliente *aux;

    if (head->numero == nr)
        {
            printf("--------------------------");
            printf("\nNumero: %d\n", head->numero);
            printf("Nome: %s\n", head->nome);
            printf("Telefone: %s\n", head->telefone);
            printf("Credito maximo: %.2f\n", head->credito_max);
            printf("--------------------------");
            return;
        }

        else
        {
            aux = head;

            while(aux->next != NULL)
            {
                aux = aux->next;
                if (aux->numero == nr)
                {
                    printf("--------------------------");
                    printf("\nNumero: %d\n", aux->numero);
                    printf("Nome: %s\n", aux->nome);
                    printf("Telefone: %s\n", aux->telefone);
                    printf("Credito maximo: %.2f\n", aux->credito_max);
                    printf("--------------------------");
                    return;
                }
            }
        }
}

char lista_vazia()
{
    if(head == NULL)
    {
        printf("\nBase de dados vazia...\n");
        return TRUE;
    }

    return FALSE;
}

void leitura_ficheiro(FILE *fp)
{
    int token_pos;
    cliente *ptr, *aux;
    char *token;
    char linha[100];
    char delimitadores[] = DELIMITADORES;

    while (fgets(linha, 100, fp) != NULL)
    {
        ptr = (cliente *)malloc(sizeof(cliente));

        if (ptr == NULL)
        {
            printf("Nao foi possivel alocar memória para a struct!\n\n");
            free(ptr);
            return;
        }

        token = strtok(linha, delimitadores);

        token_pos = 0;

        while (token != NULL)
        {
            if (token_pos == 0)
            {
                ptr->numero = atoi(token);
                token_pos++;
            }
            else if (token_pos == 1)
            {
                ptr->nome = (char *)malloc(sizeof(char) * strlen(token) + 1);
                strcpy(ptr->nome, token);
                token_pos++;
            }
            else if (token_pos == 2)
            {
                ptr->telefone = (char *)malloc(sizeof(char) * strlen(token) + 1);
                strcpy(ptr->telefone, token);
                token_pos++;
            }
            else
            {
                ptr->credito_max = atof(token);
                token_pos++;
            }

            token = strtok(NULL, delimitadores);
        }

        if (head == NULL)
        {
            ptr->next = NULL;
            head = ptr;
        }

        else
        {
            aux = head;

            while (aux->next != NULL)
            {
                aux = aux->next;
            }
            aux->next = ptr;
            ptr->next = NULL;
        }
    }
}

void imprimir_lista()
{
    cliente *ptr;

    ptr = head;

    printf("DADOS DOS CLIENTES:\n");
    printf("-------------------------");

    while(ptr != NULL)
    {
        printf("\nNumero: %d", ptr->numero);
        printf("\nNome: %s", ptr->nome);
        printf("\nTelefone: %s", ptr->telefone);
        printf("\nCredito maximo: %0.2f", ptr->credito_max);
        printf("\n-------------------------\n");
        ptr = ptr->next;
    }
}

void eliminar_cliente()
{
    cliente *ptr = NULL, *aux = head;
    int numero;

    printf("Insira o numero do cliente a eliminar: ");
    scanf("%d", &numero);

    //Eliminar na lista

    if(head == NULL)
    {
        printf("\nLista Vazia...\n");
        return;
    }

    while(aux->numero != numero)
    {
        if(aux->next == NULL)
        {
            printf("\nNúmero de cliente não encontrado!\n");
            return;
        }

        else
        {
            ptr = aux;
            aux = aux->next;
        }
    }

    if (aux == head)
    {
        head = head->next;
    }

    else
    {
        ptr->next = aux->next;
    }

    free(aux);
}

void alterar_nome(int nr)
{
    cliente *aux = head;
    char nome[51];

    printf("\nInsira o nome para o cliente %d: ", nr);
    scanf(" %50[^\n]", nome);
    fflush(stdin);

    if (head->numero == nr)
        {
            strcpy(head->nome, nome);
            return;
        }

        else
        {
            aux = head;

            while(aux->next != NULL)
            {
                aux = aux->next;
                if (aux->numero == nr)
                {
                    strcpy(aux->nome, nome);
                    return;
                }
            }
        }
}

void alterar_telefone(int nr)
{
    cliente *aux = head;
    char telefone[14];

    printf("\nInsira o numero de telefone para o cliente %d: ", nr);
    scanf(" %13[^\n]", telefone);
    fflush(stdin);

    if (head->numero == nr)
        {
            strcpy(head->telefone, telefone);
            return;
        }

        else
        {
            aux = head;

            while(aux->next != NULL)
            {
                aux = aux->next;
                if (aux->numero == nr)
                {
                    strcpy(aux->telefone, telefone);
                    return;
                }
            }
        }

    strcpy(aux->telefone, telefone);
}

void alterar_credito_max(int nr)
{
    cliente *aux = head;
    float credito_max;

    printf("\nInsira o credito maximo para o cliente %d: ", nr);
    scanf(" %f", &credito_max);
    fflush(stdin);

    if (head->numero == nr)
        {
            head->credito_max = credito_max;
            return;
        }

        else
        {
            aux = head;

            while(aux->next != NULL)
            {
                aux = aux->next;
                if (aux->numero == nr)
                {
                    aux->credito_max = credito_max;
                    return;
                }
            }
        }
}
void inserir_cliente(FILE *fp)
{
    cliente *ptr, *aux;
    char nome[51], telefone[14];
    int numero;
    float credito_max;

    printf("\nInsira o numero do cliente: ");
    scanf("%d", &numero);
    fflush(stdin);

    printf("\nInsira o nome do cliente: ");
    scanf("%51[^\n]", nome);
    fflush(stdin);

    printf("\nInsira o telefone do cliente: ");
    scanf("%13[^\n]", telefone);
    fflush(stdin);

    printf("\nInsira o credito maximo do cliente: ");
    scanf("%f", &credito_max);
    fflush(stdin);

    ptr = (cliente*)malloc(sizeof(cliente));

    if (ptr == NULL)
    {
        printf("\nNao foi possivel reservar memoria para o cliente!\n");
        return;
    }

    ptr->numero = numero;

    ptr->nome = (char*)malloc(sizeof(char) * strlen(nome) + 1);
    if (ptr->nome == NULL)
    {
        printf("\nNao foi possivel reservar memoria para o nome!\n");
        return;
    }
    strcpy(ptr->nome, nome);

    ptr->telefone = (char*)malloc(sizeof(char) * strlen(telefone) + 1);
    if (ptr->telefone == NULL)
    {
        printf("\nNao foi possivel reservar memoria para o telefone!\n");
        return;
    }
    strcpy(ptr->telefone, telefone);

    ptr->credito_max = credito_max;

    if (head == NULL)
    {
        ptr->next = NULL;
        head = ptr;
    }
    else
    {
        if (head->numero == ptr->numero)
        {
            printf("\nEste numero de cliente ja existe na lista!\n");
            return;
        }

        else
        {
            aux = head;

            while(aux->next != NULL)
            {
                aux = aux->next;
                if (aux->numero == ptr->numero)
                {
                    printf("\nEste numero de cliente ja existe na lista!\n");
                    return;
                }
            }

            aux->next = ptr;
            ptr->next = NULL;
        }
    }

    fprintf(fp, "%d;%s;%s;%.2f\n", ptr->numero, ptr->nome, ptr->telefone, ptr->credito_max);

}

void libertar_memoria()
{
    cliente *aux;

    while (lista_vazia() == FALSE)
    {
        aux = head;

        head = head->next;

        free(aux);
    }
}

int main()
{
    FILE *fp;
    char linha[MAX_LINE];
    char file_name[] = FILE_NAME;

    int op, nr;

    fp = fopen(file_name, "r");

    if (fp == NULL)
    {
        printf("Ficheiro aberto sem sucesso!\n\n");
        return 0;
    }

    fgets(linha, 100, fp);

    leitura_ficheiro(fp);

    fclose(fp);

    while(1)
    {

        fp = fopen(file_name, "a");

        if (fp == NULL)
        {
            printf("Nao foi possível abrir o ficheiro %s", file_name);
            return 0;
        }

        printf("\nLista de Operacoes\n");
        printf("====================\n");
        printf("1 - Listar Clientes\n");
        printf("2 - Inserir Novo Cliente\n");
        printf("3 - Alterar Cliente Existente\n");
        printf("4 - Eliminar Cliente\n");
        printf("0 - Sair do Programa\n");
        printf("====================\n");
        printf("\nEscolha uma operacao: ");
        scanf("%d", &op);
        system("cls");
        switch(op)
        {
        case 1:
            system("cls");
            if(lista_vazia() == TRUE) break;
            else
            {
                imprimir_lista();
            }
            fclose(fp);
            break;
        case 2:
            inserir_cliente(fp);
            fclose(fp);
            break;
        case 3:
            system("cls");
            imprimir_lista();
            printf("\nInsira o numero do cliente a alterar: ");
            scanf("%d", &nr);
            fflush(stdin);
            system("cls");
            encontrar_cliente(nr);

            printf("\n=========================\n");
            printf("1 - Alterar nome\n");
            printf("2 - Alterar telefone\n");
            printf("3 - Alterar credito maximo\n");
            printf("0 - Voltar atras\n");
            printf("==========================\n");
            printf("\nEscolha uma operacao: ");
            scanf("%d", &op);
            printf("\n\n");
            fflush(stdin);
            system("cls");
            encontrar_cliente(nr);

            switch (op)
            {
            case 1:
                alterar_nome(nr);
                fclose(fp);
                break;
            case 2:
                alterar_telefone(nr);
                fclose(fp);
                break;
            case 3:
                alterar_credito_max(nr);
                fclose(fp);
                break;
            case 0:
                fclose(fp);
                break;
            }
            break;
        case 4:
            if (lista_vazia() == TRUE)
            {
                printf("\n\nLista sem dados...\n\n");
                break;
            }
            else
            {
                fclose(fp);
                imprimir_lista();
                eliminar_cliente();
                break;
            }
        case 0:
            printf("\n\nA gravar as alteracoes no ficheiro...\n");
            libertar_memoria();
            fclose(fp);
            printf("\nA sair do programa...\n");
            return 0;
        default:
            printf("\nOpcao invalida!\n\n");
            fclose(fp);
            break;
        }
    }
    return 0;
}
