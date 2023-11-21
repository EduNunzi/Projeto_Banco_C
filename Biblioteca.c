#include <stdio.h>
#include <string.h>
#include "biblioteca.h"

Cliente clientes[1000];
int numClientes = 0;
Transacao transacoes[100];
int numTransacoes = 0;

void clear_buffer(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

void Iniciar_Banco(Cliente clientes[], int *numClientes, Transacao transacoes[], int *numTransacoes) {
    FILE* arquivo = fopen("Dados_do_Banco.bin", "rb");

    if (arquivo != NULL) {
        fread(numClientes, sizeof(int), 1, arquivo);
        fread(clientes, sizeof(Cliente), *numClientes, arquivo);

        fread(numTransacoes, sizeof(int), 1, arquivo);
        fread(transacoes, sizeof(Transacao), *numTransacoes, arquivo);

        fclose(arquivo);
    }
}

int Salvamento_Automatico(Cliente clientes[], int numClientes, Transacao transacoes[], int numTransacoes) {
    FILE* arquivo = fopen("Dados_do_Banco.bin", "wb");

    if (arquivo != NULL) {
        fwrite(&numClientes, sizeof(int), 1, arquivo);
        fwrite(clientes, sizeof(Cliente), numClientes, arquivo);

        fwrite(&numTransacoes, sizeof(int), 1, arquivo);
        fwrite(transacoes, sizeof(Transacao), numTransacoes, arquivo);

        fclose(arquivo);
        return 0;
    } else {
        return 1;
    }
}

int Novo_Cliente(Cliente clientes[], int *numClientes) {
    printf("----------------*Novo Cliente----------------*\n");
    if (*numClientes >= 100) {
        printf("Limite maximo de clientes atingido.\n");
        return 1;
    }

    printf("Seu Nome: ");
    scanf("%s", clientes[*numClientes].nome);
    clear_buffer();
    printf("Seu CPF: ");
    scanf("%s", clientes[*numClientes].cpf);
    clear_buffer();
    printf("Tipo de conta (comum ou plus): ");
    scanf(" %s", clientes[*numClientes].tipo_conta);
    clear_buffer();
    printf("Saldo inicial: ");
    scanf("%d", &clientes[*numClientes].saldo);

    if (strcmp(clientes[*numClientes].tipo_conta, "comum") == 0) {
        clientes[*numClientes].limite = -1000;
    } else if (strcmp(clientes[*numClientes].tipo_conta, "plus") == 0) {
        clientes[*numClientes].limite = -5000;
    } else {
        printf("Tipo de conta nao existente.\n");
        return 1;
    }

    printf("Crie uma senha de 6 digitos: ");
    scanf("%s", clientes[*numClientes].senha);

    (*numClientes)++;

    if (Salvamento_Automatico(clientes, *numClientes, NULL, 0) == 0) {
        return 0;
    } else {
        return 1;
    }
}

int Apagar_Cliente(Cliente clientes[], int *numClientes) {
    char cpf[12];
    printf("---------------*Apagar Cliente---------------*\n");
    printf("Digite o CPF do cliente a ser apagado: ");
    scanf("%s", cpf);
    clear_buffer();

    int clienteIndex = -1;
    for (int i = 0; i < *numClientes; i++) {
        if (strcmp(clientes[i].cpf, cpf) == 0) {
            clienteIndex = i;
            break;
        }
    }

    if (clienteIndex == -1) {
        printf("Cliente com CPF %s nao existe.\n", cpf);
        return 1;
    }

    clientes[clienteIndex] = clientes[*numClientes - 1];
    (*numClientes)--;

    printf("Cliente com CPF %s apagado.\n", cpf);

    if (Salvamento_Automatico(clientes, *numClientes, NULL, 0) == 0) {
        return 0;
    } else {
        return 1;
    }
}

int Lista_De_Clientes(Cliente clientes[], int numClientes) {
    if (numClientes == 0) {
        printf("--------------*Lista de Clientes-------------*\n");
        printf("Lista vazia!\n");
        printf("Nenhum cliente cadastrado ainda.\n");
    } else {
        printf("--------------*Lista de Clientes-------------*\n");
        printf("Lista de clientes:\n");
        for (int i = 0; i < numClientes; i++) {
            printf("Nome do cliente: %s\n", clientes[i].nome);
            printf("CPF do cliente: %s\n", clientes[i].cpf);
            printf("Tipo de conta: %s\n", clientes[i].tipo_conta);
            printf("Saldo na conta: %d\n", clientes[i].saldo);
            printf("Limite de saldo negativo: %d\n", clientes[i].limite);
            printf("\n");
        }
    }
    if (Salvamento_Automatico(clientes, numClientes, NULL, 0) == 0) {
        return 0;
    } else {
        return 1;
    }
}

int Funcao_Debito(Cliente clientes[], int numClientes, Transacao transacoes[], int *numTransacoes) {
    char cpf[12];
    char senha[7];
    int valor;

    printf("-------------------*Debito-------------------*\n");
    printf("Digite seu CPF: ");
    scanf("%s", cpf);
    clear_buffer();
    printf("Coloque sua senha de 6 digitos: ");
    scanf("%s", senha);
    clear_buffer();

    int clienteIndex = -1;
    for (int i = 0; i < numClientes; i++) {
        if (strcmp(clientes[i].cpf, cpf) == 0 && strcmp(clientes[i].senha, senha) == 0) {
            clienteIndex = i;
            break;
        }
    }

    if (clienteIndex == -1) {
        printf("CPF ou senha invalidos.\n");
        return 1;
    }

    printf("Valor a ser debitado: ");
    scanf("%d", &valor);

    if (valor <= 0) {
        printf("Valor invalido.\n");
        return 1;
    }

    int tarifa = 0;
    if (strcmp(clientes[clienteIndex].tipo_conta, "comum") == 0){
        tarifa = 0.05 * valor;
    } else if (strcmp(clientes[clienteIndex].tipo_conta, "plus") == 0) {
        tarifa = 0.03 * valor;
    }

    if (clientes[clienteIndex].saldo - valor - tarifa < clientes[clienteIndex].limite) {
        printf("Limite de saldo ultrapassado.\n");
        return 1;
    }

    clientes[clienteIndex].saldo -= valor + tarifa;

    strcpy(transacoes[*numTransacoes].cpf_debito, cpf);
    strcpy(transacoes[*numTransacoes].cpf_deposito, "N/A");
    transacoes[*numTransacoes].valor = valor;
    (*numTransacoes)++;

    printf("Operacao realizada com sucesso. Seu saldo atual: %d\n", clientes[clienteIndex].saldo);

    if (Salvamento_Automatico(clientes, numClientes, transacoes, *numTransacoes) == 0) {
        return 0;
    } else {
        return 1;
    }
}

int Funcao_Deposito(Cliente clientes[], int numClientes, Transacao transacoes[], int *numTransacoes) {
    char cpf[12];
    int valor;

    printf("------------------*Deposito------------------*\n");
    printf("Digite o CPF de destino: ");
    scanf("%s", cpf);
    clear_buffer();

    int clienteIndexDestino = -1;
    for (int i = 0; i < numClientes; i++) {
        if (strcmp(clientes[i].cpf, cpf) == 0) {
            clienteIndexDestino = i;
            break;
        }
    }

    if (clienteIndexDestino == -1) {
        printf("Conta de destino nao localizada.\n");
        return 1;
    }

    printf("Quantia a ser depositada: ");
    scanf("%d", &valor);

    if (valor <= 0) {
        printf("Quantia invalida.\n");
        return 1;
    }

    clientes[clienteIndexDestino].saldo += valor;
    printf("Operacao realizada com sucesso. Saldo atual de %s: %d\n", clientes[clienteIndexDestino].cpf, clientes[clienteIndexDestino].saldo);

    strcpy(transacoes[*numTransacoes].cpf_deposito, cpf);
    strcpy(transacoes[*numTransacoes].cpf_debito, "N/A");
    transacoes[*numTransacoes].valor = valor;
    (*numTransacoes)++;

    if (Salvamento_Automatico(clientes, numClientes, transacoes, *numTransacoes) == 0) {
        return 0;
    } else {
        return 1;
    }
}

int Extrato_Clientes(Cliente clientes[], int numClientes, Transacao transacoes[], int numTransacoes) {
    char cpf[12];
    char senha[7];

    printf("-----------------*Extratos-------------------*\n");
    printf("Digite seu CPF: ");
    scanf("%s", cpf);
    clear_buffer();
    printf("Coloque sua senha de 6 digitos: ");
    scanf("%s", senha);
    clear_buffer();

    int clienteIndex = -1;
    for (int i = 0; i < numClientes; i++) {
        if (strcmp(clientes[i].cpf, cpf) == 0 && strcmp(clientes[i].senha, senha) == 0) {
            clienteIndex = i;
            break;
        }
    }

    if (clienteIndex == -1) {
        printf("CPF ou senha invalidos.\n");
        return 1;
    }

    char arquivo_extrato[50];
    sprintf(arquivo_extrato, "extrato_%s.txt", cpf);
    FILE* arquivo = fopen(arquivo_extrato, "w");

    if (arquivo == NULL) {
        printf("Erro ao gerar extrato.\n");
        return 1;
    }

    fprintf(arquivo, "Extrato da Conta - CPF: %s\n", cpf);

    fprintf(arquivo, "*------------------- Débitos: -------------------*\n");
    for (int i = numTransacoes - 1; i >= 0; i--) {
        if (strcmp(transacoes[i].cpf_debito, cpf) == 0) {
            if (strcmp(transacoes[i].cpf_deposito, "N/A") == 0) {
                int tarifa = 0;
                if (strcmp(clientes[clienteIndex].tipo_conta, "comum") == 0) {
                    tarifa = 0.05 * transacoes[i].valor;
                } else if (strcmp(clientes[clienteIndex].tipo_conta, "plus") == 0) {
                    tarifa = 0.03 * transacoes[i].valor;
                }
                fprintf(arquivo, "Débito: %d (Tarifa: %d)\n", transacoes[i].valor + tarifa, tarifa);
            }
        }
    }

    fprintf(arquivo, "*------------------- Transferências: -------------------*\n");
    for (int i = numTransacoes - 1; i >= 0; i--) {
        if (strcmp(transacoes[i].cpf_origem, cpf) == 0 && strcmp(transacoes[i].cpf_destino, "N/A") != 0) {
            fprintf(arquivo, "Transferência para %s: %d\n", transacoes[i].cpf_destino, transacoes[i].valor);
        } else if (strcmp(transacoes[i].cpf_destino, cpf) == 0 && strcmp(transacoes[i].cpf_origem, "N/A") != 0) {
            fprintf(arquivo, "Transferência de %s: %d\n", transacoes[i].cpf_origem, transacoes[i].valor);
        }
    }

    fprintf(arquivo, "*------------------- Depósitos: -------------------*\n");
    for (int i = numTransacoes - 1; i >= 0; i--) {
        if (strcmp(transacoes[i].cpf_deposito, cpf) == 0) {
            fprintf(arquivo, "Depósito: %d\n", transacoes[i].valor);
        }
    }

    fclose(arquivo);
    printf("Extrato gerado. Verifique o arquivo: %s.\n", arquivo_extrato);

    if (Salvamento_Automatico(clientes, numClientes, transacoes, numTransacoes) == 0) {
        return 0;
    } else {
        return 1;
    }
}
int Transferencia_entre_Contas(Cliente clientes[], int numClientes, Transacao transacoes[], int *numTransacoes) {

    char cpf_origem[12];
    char senha[7];
    char cpf_destino[12];
    int valor;

    printf("---------------*Transferência---------------*\n");
    printf("Digite o CPF da conta de origem: ");
    scanf("%s", cpf_origem);
    clear_buffer();
    printf("Coloque a senha de 6 digitos da conta de origem: ");
    scanf("%s", senha);
    clear_buffer();
    int clienteIndexOrigem = -1;
    for (int i = 0; i < numClientes; i++) {
        if (strcmp(clientes[i].cpf, cpf_origem) == 0 && strcmp(clientes[i].senha, senha) == 0) {
            clienteIndexOrigem = i;
            break;
        }
    }

    if (clienteIndexOrigem == -1) {
        printf("CPF ou senha da conta de origem inválidos.\n");
        return 1;
    }

    printf("Digite o CPF da conta de destino:");
    scanf("%s", cpf_destino);

    int clienteIndexDestino = -1;
    for (int i = 0; i < numClientes; i++) {
        if (strcmp(clientes[i].cpf, cpf_destino) == 0) {
            clienteIndexDestino = i;
            break;
        }
    }

    if (clienteIndexDestino == -1) {
        printf("Conta de destino não localizada.\n");
        return 1;
    }

    printf("Quantia da transferencia: ");
    scanf("%d", &valor);

    if (valor <= 0 || clientes[clienteIndexOrigem].saldo - valor < clientes[clienteIndexOrigem].limite) {
        printf("Quantia de transferencia inválida ou limite de saldo ultrapassado.\n");
        return 1;
    } else {
        clientes[clienteIndexOrigem].saldo -= valor;
        clientes[clienteIndexDestino].saldo += valor;
        printf("Transferencia realizada com sucesso.\n Seu saldo atual eh de: %d\n", clientes[clienteIndexOrigem].saldo);

        strcpy(transacoes[*numTransacoes].cpf_origem, cpf_origem);
        strcpy(transacoes[*numTransacoes].cpf_destino, cpf_destino);
        transacoes[*numTransacoes].valor = valor;
        (*numTransacoes)++;
    }

    return 0;
}
