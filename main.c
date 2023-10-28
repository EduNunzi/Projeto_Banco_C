#include <stdio.h>
#include "biblioteca.h"

int main() {
    int opcao;


    do {
        printf("\n*------------Banco Quem Poupa Tem------------*");
        printf("\nMenu de Operacoes:\n");
        printf("1. Novo cliente\n");
        printf("2. Apagar cliente\n");
        printf("3. Listar clientes\n");
        printf("4. Debito\n");
        printf("5. Deposito\n");
        printf("6. Extrato\n");
        printf("7. Transferencia entre Contas\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
    } while (opcao != 0);
}