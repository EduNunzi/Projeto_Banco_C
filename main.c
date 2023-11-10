#include <stdio.h>
#include "biblioteca.h"

//Eduardo Guerra Nunziata RA: 22.123.002-2
//Ana Carolina Lazzuri RA: 22.123.001-4

int main() {
    int opcao;
    Iniciar_Banco();


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

        switch (opcao) {
            case 1:
                Novo_Cliente();
                break;
            case 2:
                Apagar_Cliente();
                break;
            case 3:
                Lista_De_Clientes();
                break;
            case 4:
                Funcao_Debito();
                break;
            case 5:
                Funcao_Deposito();
                break;
            case 6:
                Extrato_Clientes();
                break;
            case 7:
                Transferencia_entre_Contas();
                break;
            case 0:
                printf("Voce saiu. Ate a proxima.\n");
                break;
            default:
                printf("Opcao invalida,\n por favor tente novamente.\n");
        }
    } while (opcao != 0);

    Salvamento_Automatico();
}