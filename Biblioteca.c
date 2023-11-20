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
    printf("*----------------*Novo Cliente*----------------*\n");
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

void Apagar_Cliente() {
    char cpf[12];
    printf("*---------------*Apagar Cliente*---------------*\n");
    printf("Digite o CPF do cliente a ser apagado: ");
    scanf("%s", cpf);

    int clienteIndex = -1;
    for (int i = 0; i < numClientes; i++) {
        if (strcmp(clientes[i].cpf, cpf) == 0) {
            clienteIndex = i;
            break;
        }
    }

    if (clienteIndex == -1) {
        printf("Cliente com CPF %s nao existe.\n", cpf);
        return;
    }

    clientes[clienteIndex] = clientes[numClientes - 1];
    numClientes--;

    printf("Cliente com CPF %s apagado.\n", cpf);

    Salvamento_Automatico();
}

void Lista_De_Clientes() {
    if (numClientes == 0) {
        printf("*--------------*Lista de Clientes*-------------*\n");
        printf("Lista vazia!\n");
        printf("Nenhum cliente cadastrado ainda.\n");
    } else {
        printf("*--------------*Lista de Clientes*-------------*\n");
        printf("Lista de clientes:\n");
        for (int i = 0; i < numClientes; i++) {
            printf("Nome do cliente: %s\n", clientes[i].nome);
            printf("CPF do cliente: %s\n", clientes[i].cpf);
            printf("Tipo de conta: %s\n", clientes[i].tipo_conta);
            printf("Saldo na conta: %.2f\n", clientes[i].saldo);
            printf("Limite de saldo negativo: %.2f\n", clientes[i].limite);
            printf("\n");
        }
    }
    Salvamento_Automatico();
}

void Funcao_Debito() {
    char cpf[12];
    char senha[7];
    float valor;

    printf("*-------------------*Debito*-------------------*\n");
    printf("Digite seu CPF: ");
    scanf("%s", cpf);
    printf("Coloque sua senha de 6 digitos: ");
    scanf("%s", senha);

    int clienteIndex = -1;
    for (int i = 0; i < numClientes; i++) {
        if (strcmp(clientes[i].cpf, cpf) == 0 && strcmp(clientes[i].senha, senha) == 0) {
            clienteIndex = i;
            break;
        }
    }

    if (clienteIndex == -1) {
        printf("CPF ou senha invalidos.\n");
        return;
    }

    printf("Valor a ser debitado: ");
    scanf("%f", &valor);

    if (valor <= 0) {
        printf("Valor invalido.\n");
        return;
    }

    float tarifa = 0.00;
    if (strcmp(clientes[clienteIndex].tipo_conta, "comum") == 0){
        tarifa = 0.05 * valor;
    } else if (strcmp(clientes[clienteIndex].tipo_conta, "plus") == 0) {
        tarifa = 0.03 * valor;
    }

    if (clientes[clienteIndex].saldo - valor - tarifa < clientes[clienteIndex].limite) {
        printf("Limite de saldo ultrapassado.\n");
        return;
    }

    clientes[clienteIndex].saldo -= valor + tarifa;

    strcpy(transacoes[numTransacoes].cpf_debito, cpf);
    strcpy(transacoes[numTransacoes].cpf_deposito, "N/A");
    transacoes[numTransacoes].valor = valor;
    numTransacoes++;

    printf("Operacao realizada com sucesso. Seu saldo atual: %.2f\n", clientes[clienteIndex].saldo);

    Salvamento_Automatico();
}

void Funcao_Deposito() {
    char cpf[12];
    float valor;

    printf("*------------------*Deposito*------------------*\n");
    printf("Digite o CPF de destino: ");
    scanf("%s", cpf);

    int clienteIndexDestino = -1;
    for (int i = 0; i < numClientes; i++) {
        if (strcmp(clientes[i].cpf, cpf) == 0) {
            clienteIndexDestino = i;
            break;
        }
    }

    if (clienteIndexDestino == -1) {
        printf("Conta de destino nao localizada.\n");
        return;
    }

    printf("Quantia a ser depositada: ");
    scanf("%f", &valor);

    if (valor <= 0) {
        printf("Quantia invalida.\n");
        return;
    }

    clientes[clienteIndexDestino].saldo += valor;
    printf("Operacao realizada com sucesso. Saldo atual de %s: %.2f\n", clientes[clienteIndexDestino].cpf, clientes[clienteIndexDestino].saldo);

    strcpy(transacoes[numTransacoes].cpf_deposito, cpf);
    strcpy(transacoes[numTransacoes].cpf_debito, "N/A");
    transacoes[numTransacoes].valor = valor;
    numTransacoes++;

    Salvamento_Automatico();
}

void Extrato_Clientes() {
    char cpf[12];
    char senha[7];

    printf("*-----------------*Extratos*-------------------*\n");
    printf("Digite seu CPF: ");
    scanf("%s", cpf);
    printf("Coloque sua senha de 6 digitos: ");
    scanf("%s", senha);

    int clienteIndex = -1;
    for (int i = 0; i < numClientes; i++) {
        if (strcmp(clientes[i].cpf, cpf) == 0 && strcmp(clientes[i].senha, senha) == 0) {
            clienteIndex = i;
            break;
        }
    }

    if (clienteIndex == -1) {
        printf("CPF ou senha invalidos.\n");
        return;
    }

    char arquivo_extrato[50];
    sprintf(arquivo_extrato, "extrato_%s.txt", cpf);
    FILE* arquivo = fopen(arquivo_extrato, "w");

    if (arquivo == NULL) {
        printf("Erro ao gerar extrato.\n");
        return;
    }

    fprintf(arquivo, "Extrato da Conta - CPF: %s\n", cpf);

    fprintf(arquivo, "*------------------- Débitos: -------------------*\n");
    for (int i = numTransacoes - 1; i >= 0; i--) {
        if (strcmp(transacoes[i].cpf_debito, cpf) == 0) {
            if (strcmp(transacoes[i].cpf_deposito, "N/A") == 0) {
                float tarifa = 0.0;
                if (strcmp(clientes[clienteIndex].tipo_conta, "comum") == 0) {
                    tarifa = 0.05 * transacoes[i].valor;
                } else if (strcmp(clientes[clienteIndex].tipo_conta, "plus") == 0) {
                    tarifa = 0.03 * transacoes[i].valor;
                }
                fprintf(arquivo, "Débito: %.2f (Tarifa: %.2f)\n", transacoes[i].valor + tarifa, tarifa);
            }
        }
    }

    fprintf(arquivo, "*------------------- Transferências: -------------------*\n");
    for (int i = numTransacoes - 1; i >= 0; i--) {
        if (strcmp(transacoes[i].cpf_origem, cpf) == 0 && strcmp(transacoes[i].cpf_destino, "N/A") != 0) {
            fprintf(arquivo, "Transferência para %s: %.2f\n", transacoes[i].cpf_destino, transacoes[i].valor);
        } else if (strcmp(transacoes[i].cpf_destino, cpf) == 0 && strcmp(transacoes[i].cpf_origem, "N/A") != 0) {
            fprintf(arquivo, "Transferência de %s: %.2f\n", transacoes[i].cpf_origem, transacoes[i].valor);
        }
    }

    fprintf(arquivo, "*------------------- Depósitos: -------------------*\n");
    for (int i = numTransacoes - 1; i >= 0; i--) {
        if (strcmp(transacoes[i].cpf_deposito, cpf) == 0) {
            fprintf(arquivo, "Depósito: %.2f\n", transacoes[i].valor);
        }
    }

    fclose(arquivo);
    printf("Extrato gerado. Verifique o arquivo: %s.\n", arquivo_extrato);

    Salvamento_Automatico();
}

void Transferencia_entre_Contas() {
    char cpf_origem[12];
    char senha[7];
    char cpf_destino[12];
    float valor;

    printf("*---------------*Tranferencias*---------------*\n");
    printf("Digite o CPF da conta de origem: ");
    scanf("%s", cpf_origem);
    printf("Coloque a senha de 6 digitos da conta de origem: ");
    scanf("%s", senha);

    int clienteIndexOrigem = -1;
    for (int i = 0; i < numClientes; i++) {
        if (strcmp(clientes[i].cpf, cpf_origem) == 0 && strcmp(clientes[i].senha, senha) == 0) {
            clienteIndexOrigem = i;
            break;
        }
    }

    if (clienteIndexOrigem == -1) {
        printf("CPF ou senha da conta de origem invalidos.\n");
        return;
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
        printf("Conta de destino nao localizada.\n");
        return;
    }
    printf("\n Quantia da transferencia: ");
    scanf("%f", &valor);

    if (valor <= 0 || clientes[clienteIndexOrigem].saldo - valor < clientes[clienteIndexOrigem].limite) {
        printf("Quantia de transferencia invalida ou limite de saldo ultrapassado.\n");
    } else {
        clientes[clienteIndexOrigem].saldo -= valor;
        clientes[clienteIndexDestino].saldo += valor;
        printf("Transferencia realizada com sucesso.\n Seu saldo atual de: %.2f\n", clientes[clienteIndexOrigem].saldo);

        strcpy(transacoes[numTransacoes].cpf_origem, cpf_origem);
        strcpy(transacoes[numTransacoes].cpf_destino, cpf_destino);
        transacoes[numTransacoes].valor = valor;
        numTransacoes++;
    }
    Salvamento_Automatico();
}