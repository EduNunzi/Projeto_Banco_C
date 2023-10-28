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