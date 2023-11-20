#ifndef PROJETO_BANCO_C_BIBLIOTECA_H
#define PROJETO_BANCO_C_BIBLIOTECA_H

typedef struct {
    char nome[100];
    char cpf[12];
    char tipo_conta[5];
    float saldo;
    float limite;
    char senha[7];
} Cliente;

typedef struct {
    char cpf_origem[12];
    char cpf_destino[12];
    char cpf_deposito[12];
    char cpf_debito[12];
    float valor;
} Transacao;

void Iniciar_Banco(Cliente clientes[], int *numClientes, Transacao transacoes[], int *numTransacoes);
int Salvamento_Automatico(Cliente clientes[], int numClientes, Transacao transacoes[], int numTransacoes);
int Novo_Cliente(Cliente clientes[], int *numClientes);
int Apagar_Cliente(Cliente clientes[], int *numClientes);
int Lista_De_Clientes(Cliente clientes[], int numClientes);
int Funcao_Debito(Cliente clientes[], int numClientes, Transacao transacoes[], int *numTransacoes);
int Funcao_Deposito(Cliente clientes[], int numClientes, Transacao transacoes[], int *numTransacoes);
int Extrato_Clientes(Cliente clientes[], int numClientes, Transacao transacoes[], int numTransacoes);
int Transferencia_entre_Contas(Cliente clientes[], int numClientes, Transacao transacoes[], int *numTransacoes);
void clear_buffer();

#endif //PROJETO_BANCO_C_BIBLIOTECA_H
