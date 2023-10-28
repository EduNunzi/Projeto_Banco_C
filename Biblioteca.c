#include <stdio.h>
#include <string.h>
#include "biblioteca.h"

Cliente clientes[1000];
int numClientes = 0;
Transacao transacoes[100];
int numTransacoes = 0;

void Iniciar_Banco() {
    FILE* arquivo = fopen("Dados_do_Banco.bin", "rb");

    if (arquivo != NULL) {
        fread(&numClientes, sizeof(int), 1, arquivo);
        fread(clientes, sizeof(Cliente), numClientes, arquivo);

        fread(&numTransacoes, sizeof(int), 1, arquivo);
        fread(transacoes, sizeof(Transacao), numTransacoes, arquivo);

        fclose(arquivo);
    }
}

void Salvamento_Automatico() {
    FILE* arquivo = fopen("Dados_do_Banco.bin", "wb");

    if (arquivo != NULL) {

        fwrite(&numClientes, sizeof(int), 1, arquivo);
        fwrite(clientes, sizeof(Cliente), numClientes, arquivo);


        fwrite(&numTransacoes, sizeof(int), 1, arquivo);
        fwrite(transacoes, sizeof(Transacao), numTransacoes, arquivo);

        fclose(arquivo);
    }
}

void Novo_Cliente() {
    printf("----------------*Novo Cliente----------------*\n");
    if (numClientes >= 1000) {
        printf("Limite maximo de clientes atingido.\n");
        return;
    }

    printf("Seu Nome: ");
    scanf("%s", clientes[numClientes].nome);
    printf("Seu CPF: ");
    scanf("%s", clientes[numClientes].cpf);
    printf("Tipo de conta (comum ou plus): ");
    scanf(" %s", &clientes[numClientes].tipo_conta);
    printf("Saldo inicial: ");
    scanf("%f", &clientes[numClientes].saldo);

    if (strcmp(clientes[numClientes].tipo_conta, "comum") == 0) {
        clientes[numClientes].limite = -1000.0;
    } else if (strcmp(clientes[numClientes].tipo_conta, "plus") == 0) {
        clientes[numClientes].limite = -5000.0;
    } else {
        printf("Tipo de conta nao existente.\n");
        return;
    }
    printf("Crie uma senha de 6 digitos: ");
    scanf("%s", clientes[numClientes].senha);

    numClientes++;

    Salvamento_Automatico();
}