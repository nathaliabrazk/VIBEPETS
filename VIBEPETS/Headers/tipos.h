//
//  tipos.h
//  VIBEPETS
//
//  Created by Luiz Araujo on 14/10/22.
//

#ifndef tipos_h
#define tipos_h


// #############################################################################
// CONSTANTES
#define BIN_AGE "vibe_pet-persistencia_agend.bin"
#define BIN_CLI "vibe_pet-persistencia_cli.bin"
#define BIN_FUN "vibe_pet-persistencia_func.bin"
#define BIN_SER "vibe_pet-persistencia_serv.bin"
//#define BIN_PRO "vibe_pet-persistencia_prod.bin"
//#define BIN_TEL "vibe_pet-persistencia_tel.bin"
//#define BIN_END "vibe_pet-persistencia_end.bin"

// #############################################################################
// DECLARACAO DE TIPOS

// 'typedef' e uma outra forma de declarar um novo tipo de struct.
// Serve para criar um "apelido" a 'struct NomdoTipo', para quando for declarar uma variável
// do tipo nao precisar escrever 'struct'antes do tipo.

// #################################
// Data
typedef struct {
    //    int codigo;
    int dia;
    int mes;
    int ano;
} Data;

// #################################
// Endereco
typedef struct {
    //    int codigo;
    char cep[10];
    char pais[20];
    char estado[20];
    char cidade[20];
    char bairro[20];
    char logradouro[20];
    char numero[20];
} Endereco;

// #################################
// Hora
typedef struct {
    //    int codigo;
    int segundo;
    int minuto;
    int hora;
} Hora;

// #################################
// Telefone
typedef struct {
    //    int codigo;
    int numero;
    int ddd;
    char temWhatsApp;   // 1 = se o número tem WhatApp.
} Telefone;

// #################################
// Agendamento
struct Agendamento {
    int codigo;
    int codigoCliente;
    int codigoFuncionario;
    int codigoServico;
    Data data;
    Hora hora;
    char  ativo;     // '*' = inativo/deletado
};

// #################################
// Cliente
struct Cliente {
    int  codigo;
    char nome[30];
    char email[30];
//    Endereco endereco;
    char endereco[30];  // Passar para struct.
    char cpf[12];
    Data nascimento;
    int telefone;
//    Telefone telefone;
    char ativo;         // '*' = inativo/deletado.
};

// #################################
// Funcionario
struct Funcionario {
    int  codigo;
    char nome[30];
    char cpf[12];
    char senha[25];
    int  cargo;      // 0 = admin || 1 = funcionario
    char ativo;     // '*' = inativo/deletado
};

// #################################
// Horarios
struct Horario {
    int  codigo;
    int  codigoAgendamento;
    char ocupado; // '*' = ocupado, agendado.
};

// #################################
// Servico
struct Servico {
    int   codigo;
    char  nome[30];
    int   duracao;
    float valor;
    char  ativo;     // '*' = inativo/deletado
};

#endif /* Tipos_h */
