//
//  main.h
//  VIBEPETS
//
//  Created by Luiz Araujo on 14/10/22.
//

#ifndef main_h
#define main_h

// #############################################################################
// IMPORTACOES DE LIBs
#include <ctype.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>     // usleep


// #############################################################################
// CONSTANTES
#define BIN_AGE "vibe_pet-persistencia_agend.bin"
#define BIN_CLI "vibe_pet-persistencia_cli.bin"
#define BIN_FUN "vibe_pet-persistencia_func.bin"
#define BIN_SER "vibe_pet-persistencia_serv.bin"
//#define BIN_PRO "vibe_pet-persistencia_prod.bin"
//#define BIN_TEL "vibe_pet-persistencia_tel.bin"
//#define BIN_END "vibe_pet-persistencia_end.bin"

#define MOSTRAR_DEBUG 0 // 1 = Mostra coisas na tela, msg de erro e etc.
#define LIMPAR_TELA 0   // 1 = limpa a tela, habilita o clear screen system("cls").
#define LIMPAR_BD 0     // 1 = Apaga os arquivos ao iniciar o sistema(zera o BD)
#define TEMA 0          // Cada numero representa um tema para a interface.


// Ponteiro para indicar o 'endereco' do arquivo a ser manipulado.
FILE *ponteiroArquivoAGENDAMENTO;
FILE *ponteiroArquivoCLIENTE;
FILE *ponteiroArquivoFUNCIONARIO;
FILE *ponteiroArquivoHORARIO;
FILE *ponteiroArquivoSERVICO;
//FILE *ponteiroArquivoPRODUTO;
//FILE *ponteiroArquivoTELEFONE;
//FILE *ponteiroArquivoENDERECO;


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


// #############################################################################
// PROTOTIPOS

// #################################
// ARQUIVOS
void abrirTodosArquivos(void);
void abrirArquivoAgendamento(void);
void abrirArquivoCliente(void);
void abrirArquivoFuncionario(void);
void abrirArquivoHorario(void);
void abrirArquivoServico(void);

void fecharTodosArquivos(void);
void fecharArquivoAgendamento(void);
void fecharArquivoCliente(void);
void fecharArquivoHorario(void);
void fecharArquivoFuncionario(void);
void fecharArquivoServico(void);


// #################################
// MENUS
void menuPrincipal(void);

void menuAgendamento(void);
void menuAgendamentoListarTodos(void);
void menuAgendamentoInserir(void);
void menuAgendamentoAlterar(void);
void menuAgendamentoDeletar(void);

void menuCliente(void);
void menuClienteListarTodos(void);
void menuClienteInserir(void);
void menuClienteAlterar(void);
void menuClienteDeletar(void);

void menuFuncionario(void);
void menuFuncionarioListarTodos(void);
void menuFuncionarioInserir(void);
void menuFuncionarioAlterar(void);
void menuFuncionarioDeletar(void);

void menuHorario(void);
void menuHorarioListarTodos(void);
void menuHorarioInserir(void);
void menuHorarioAlterar(void);
void menuHorarioDeletar(void);
void menuAgendamentoHorarios(void);
void menuServico(void);
void menuServicoListarTodos(void);
void menuServicoInserir(void);
void menuServicoAlterar(void);
void menuServicoDeletar(void);


// #################################
// FUNCOES CRUD
int  salvarRegistroAgendamento(struct Agendamento);
void printarCabecalhoListaAgendamento(void);
void printarTodosRegistrosAgendamento(void);
void printarAgendamentoLista(struct Agendamento);
void printarAgendamentoTopicos(struct Agendamento);
struct Agendamento buscarAgendamentoPorCod(int);
int  buscarRegistroAgendamentoPorCod(int);
void alterarAgendamento(int);
int  acessarUltimoCodigoAgendamento(void);
void deletarAgendamento(int);
void lerDadosAgendamento(struct Agendamento*);

void printarCabecalhoTodosClientes(void);
int  salvarRegistroCliente(struct Cliente);
void printarTodosRegistrosCliente(void);
void printarClienteLista(struct Cliente);
void printarClienteTopicos(struct Cliente);
struct Cliente buscarClientePorCod(int);
int  buscarRegistroClientePorCod(int);
void alterarCliente(int);
int  acessarUltimoCodigoCliente(void);
void deletarCliente(int);
void lerDadosCliente(struct Cliente*);
struct Cliente buscarClientePorCPF(char[]);

int  salvarRegistroFuncionario(struct Funcionario);
void printarTodosRegistrosFuncionario(void);
void printarFuncionarioLista(struct Funcionario);
void printarFuncionarioTopicos(struct Funcionario);
struct Funcionario buscarFuncionarioPorCod(int);
int  buscarRegistroFuncionarioPorCod(int);
void alterarFuncionario(int);
int  acessarUltimoCodigoFuncionario(void);
void deletarFuncionario(int);
void lerDadosFuncionario(struct Funcionario*);
struct Funcionario buscarFuncionarioPorCPF(char[]);

int  salvarRegistroHorario(struct Horario);
void printarTodosRegistrosHorario(void);
void printarHorarioLista(struct Horario);
void printarHorarioTopicos(struct Horario);
struct Horario buscarHorarioPorCod(int);
int  buscarRegistroHorarioPorCod(int);
void alterarHorario(int);
int  acessarUltimoCodigoHorario(void);
void deletarHorario(int);
void lerDadosHorario(struct Horario*);



void mostrarQuadroHorarios(void);











int  salvarRegistroServico(struct Servico);
void printarTodosRegistrosServico(void);
void printarServicoLista(struct Servico);
void printarServicoTopicos(struct Servico);
struct Servico buscarServicoPorCod(int);
int  buscarRegistroServicoPorCod(int);
void alterarServico(int);
int  acessarUltimoCodigoServico(void);
void deletarServico(int);
void lerDadosServico(struct Servico*);


// #################################
// FUNCOES AUXILIARES
void listarCaracteresASCII(void);
void printarMensagem(char *msg);
void printarMensagemContinuar(void);
char* formatarCPF(char[]);
void limparTela(void);
void printarDataFormatada(Data);
char* stringDataFormatada(Data);
void printarHoraFormatada(Hora);
char* stringHoraFormatada(Hora);
Data pegarDataDoSistema(void);
Hora pegarHoraDoSistema(void);
void printarStringCentralizada(char*, int);
int quantidadeDiaMes(int);
void printarCabecalhoQuadroHorarios(void);
void printarCabecalhoQuadroHorarios(void);

// #################################
// VALIDACOES
void receberValidarCPF(char*);
int  receberValidarOpcaoNumero(int, int);
char receberValidarOpcaoLetra(char*);
Data receberValidarData(void);
Hora receberValidarHora(void);
void receberValidarEmail(char*);
int verificarTempoAteData(Data);
char verificarHoraDentroExpediente(Hora);


// #################################
// ELEMENTOS DE INTERFACE
void interfaceLinhaSeparadora(int);
void interfaceLinhaSeparadoraSemQuebraDeLinha(int);
#endif /* main_h */
