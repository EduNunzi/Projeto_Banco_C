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

#endif //PROJETO_BANCO_C_BIBLIOTECA_H