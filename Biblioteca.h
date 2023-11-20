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

void Iniciar_Banco();
void Salvamento_Automatico();
void Novo_Cliente();
void Apagar_Cliente();
void Lista_De_Clientes();
void Funcao_Debito();
void Funcao_Deposito();
void Extrato_Clientes();
void Transferencia_entre_Contas();

#endif //PROJETO_BANCO_C_BIBLIOTECA_H