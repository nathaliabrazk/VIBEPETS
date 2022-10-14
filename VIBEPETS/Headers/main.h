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

#include "utilidades.h"
#include "validacoes.h"
#include "Servico.h"
#include "Agendamento.h"

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
FILE *ponteiroArquivoCLIENTE;
FILE *ponteiroArquivoFUNCIONARIO;
FILE *ponteiroArquivoHORARIO;
//FILE *ponteiroArquivoPRODUTO;
//FILE *ponteiroArquivoTELEFONE;
//FILE *ponteiroArquivoENDERECO;




// #############################################################################
// PROTOTIPOS

// #################################
// ARQUIVOS
void abrirTodosArquivos(void);
void abrirArquivoCliente(void);
void abrirArquivoFuncionario(void);
void abrirArquivoHorario(void);

void fecharTodosArquivos(void);
void fecharArquivoCliente(void);
void fecharArquivoHorario(void);
void fecharArquivoFuncionario(void);


// #################################
// MENUS
void menuPrincipal(void);


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






#endif /* main_h */
