//
//  main.c
//  VIBEPETS
//
//  Created by Nathelia Braz on 24/09/22.
//

#include <ctype.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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
void abrirArquivoServico(void);

void fecharTodosArquivos(void);
void fecharArquivoAgendamento(void);
void fecharArquivoCliente(void);
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
void interfaceLinhaSeparadoraGrande(void);
void interfaceLinhaSeparadoraMedia(void);
void interfaceLinhaSeparadoraPequena(void);


int main(int argc, char *argv[]) {
    //    struct Funcionario funcionario;
    char opcao = 'a';
    
    // INICIALIZACOES
    // Cuidado, esta acao apaga todo o Banco de Dados.
    if(LIMPAR_BD == 1) {
        interfaceLinhaSeparadoraMedia();
        printarMensagem("DESEJA APAGAR TODOS OS REGISTROS (s/n)?\n(Acao irreversivel) ");
        fflush(stdin); opcao = getchar();
        if(opcao == 's' || opcao == 'S') {
            remove(BIN_FUN);
        }
    }
    abrirTodosArquivos();

    // MENU PRINCIPAL
    menuPrincipal();

    fecharTodosArquivos();
    
    printf("\n\n\n");
    system("pause");
    
    return 0;
}


// #############################################################################
// MENUS
void menuPrincipal() {
    char opcao = 'a';
    
    while(opcao != 'x' && opcao != 'X') {
        limparTela();
        
        printf("\nMENU PRINCIPAL\n");
        printf("\tA) MENU AGENDAMENTO\n");
        printf("\tC) MENU CLIENTE\n");
        printf("\tF) MENU FUNCIONARIO\n");
        printf("\tP) MENU PRODUTO\n");
        printf("\tS) MENU SERVICOS\n");
        printf("\tX) SAIR\n");
        opcao = receberValidarOpcaoLetra("apcfxs");
        
        switch(opcao) {
            case 'a':
                menuAgendamento();
                break;
                
            case 'c':
                menuCliente();
                break;
                
            case 'f':
                menuFuncionario();
                break;
                
            case 'p':
                printf("---> FAZER MENU PRODUTO <--- ");
                break;
                
            case 's':
                menuServico();
                break;
                
            case 'x':
                printf("SAINDO!");
                break;
                
            default:
                printf("OPCAO INVALIDA!");
        }
    }
}

// #################################
// MENU AGENDAMENTO
void menuAgendamento() {
    char opcao = 'a';
    
    while(opcao != 'x' && opcao != 'X') {
        limparTela();
        
        printf("\nMENU AGENDAMENTO\n");
        printf("\tI) INSERIR NOVO\n");
        printf("\tA) ALTERAR\n");
        printf("\tL) LISTAR\n");
        printf("\tD) DELETAR\n");
        printf("\tX) VOLTAR\n");
        opcao = receberValidarOpcaoLetra("ialdx");
        
        switch(opcao) {
            case 'a':
                menuAgendamentoAlterar();
                break;
                
            case 'd':
                menuAgendamentoDeletar();
                break;
                
            case 'i':
                menuAgendamentoInserir();
                break;
                
            case 'l':
                menuAgendamentoListarTodos();
                break;
                
            case 'x':
                printf("VOLTANDO!");
                break;
                
            default:
                printf("OPCAO INVALIDA!");
        }
    }
}

void menuAgendamentoListarTodos() {
    printarTodosRegistrosAgendamento();
    printarMensagemContinuar();
}

void menuAgendamentoInserir() {
    struct Agendamento agendamento;
    
    lerDadosAgendamento(&agendamento);
    salvarRegistroAgendamento(agendamento);
    printarAgendamentoLista(agendamento);
    printarAgendamentoTopicos(agendamento);
}

void menuAgendamentoAlterar() {
    int codigo = 0;
    int registro = 0;
    
    printarTodosRegistrosAgendamento();
    
    printf("INFORME O CODIGO PARA ALTERAR: ");
    scanf("%d", &codigo);
    
    registro = buscarRegistroAgendamentoPorCod(codigo);
    alterarAgendamento(registro);
    
    printarMensagemContinuar();
}

void menuAgendamentoDeletar() {
    int codigo   = 0;
    int registro = 0;
    
    printarTodosRegistrosAgendamento();
    
    printf("INFORME O CODIGO PARA ALTERAR: ");
    scanf("%d", &codigo);
    
    registro = buscarRegistroAgendamentoPorCod(codigo);
    deletarAgendamento(registro);
    printarMensagemContinuar();
}



// #################################
// MENU CLIENTE
void menuCliente() {
    char opcao = 'a';
    
    while(opcao != 'x' && opcao != 'X') {
        limparTela();
        
        printf("\nMENU CLIENTE\n");
        printf("\tA) ALTERAR\n");
        printf("\tD) DELETAR\n");
        printf("\tI) INSERIR\n");
        printf("\tL) LISTAR\n");
        printf("\tX) VOLTAR\n");
        opcao = receberValidarOpcaoLetra("ialdx");
        
        switch(opcao) {
            case 'a':
                menuClienteAlterar();
                break;
                
            case 'd':
                menuClienteDeletar();
                break;
                
            case 'i':
                menuClienteInserir();
                break;
                
            case 'l':
                menuClienteListarTodos();
                break;
                
            case 'x':
                printf("VOLTANDO!");
                break;
                
            default:
                printf("OPCAO INVALIDA!");
        }
    }
}

void menuClienteListarTodos() {
    printarTodosRegistrosCliente();
    printarMensagemContinuar();
}

void menuClienteInserir() {
    struct Cliente cliente;
    
    lerDadosCliente(&cliente);
    salvarRegistroCliente(cliente);
    printarClienteLista(cliente);
    printarClienteTopicos(cliente);
}

void menuClienteAlterar() {
    int codigo = 0;
    int registro = 0;
    
    printarTodosRegistrosCliente();
    
    printf("INFORME O CODIGO PARA ALTERAR: ");
    scanf("%d", &codigo);
    
    registro = buscarRegistroClientePorCod(codigo);
    alterarCliente(registro);
    
    printarMensagemContinuar();
}

void menuClienteDeletar() {
    int codigo   = 0;
    int registro = 0;
    
    printarTodosRegistrosCliente();
    
    printf("INFORME O CODIGO PARA ALTERAR: ");
    scanf("%d", &codigo);
    
    registro = buscarRegistroClientePorCod(codigo);
    deletarCliente(registro);
    printarMensagemContinuar();
}

// #################################
// MENU FUNCIONARIO
void menuFuncionario() {
    char opcao = 'a';
    
    while(opcao != 'x' && opcao != 'X') {
        limparTela();
        
        printf("\n MENU FUNCIONARIO\n");
        printf("\tI) INSERIR NOVO\n");
        printf("\tA) ALTERAR\n");
        printf("\tL) LISTAR\n");
        printf("\tD) DELETAR\n");
        printf("\tX) VOLTAR\n");
        opcao = receberValidarOpcaoLetra("ialdx");
        
        switch(opcao) {
            case 'i':
            case 'I':
                menuFuncionarioInserir();
                break;
                
            case 'a':
            case 'A':
                menuFuncionarioAlterar();
                break;
                
            case 'l':
            case 'L':
                menuFuncionarioListarTodos();
                break;
                
            case 'd':
            case 'D':
                menuFuncionarioDeletar();
                break;
                
            case 'x':
            case 'X':
                printf("VOLTANDO!");
                break;
                
            default:
                printf("OPCAO INVALIDA!");
        }
    }
}

void menuFuncionarioListarTodos() {
    printarTodosRegistrosFuncionario();
    printarMensagemContinuar();
}

void menuFuncionarioInserir() {
    struct Funcionario funcionario;
    
    lerDadosFuncionario(&funcionario);
    salvarRegistroFuncionario(funcionario);
    printarFuncionarioLista(funcionario);
    printarFuncionarioTopicos(funcionario);
}

void menuFuncionarioAlterar() {
    int codigo = 0;
    int registro = 0;
    
    printarTodosRegistrosFuncionario();
    
    printf("INFORME O CODIGO PARA ALTERAR: ");
    scanf("%d", &codigo);
    
    registro = buscarRegistroFuncionarioPorCod(codigo);
    alterarFuncionario(registro);
    
    printarMensagemContinuar();
}

void menuFuncionarioDeletar() {
    int codigo = 0;
    int registro = 0;
    
    printarTodosRegistrosFuncionario();
    
    printf("INFORME O CODIGO PARA ALTERAR: ");
    scanf("%d", &codigo);
    
    registro = buscarRegistroFuncionarioPorCod(codigo);
    deletarFuncionario(registro);
    printarMensagemContinuar();
}

// #################################
// MENU SERVICO
void menuServico() {
    char opcao = 'a';
    
    while(opcao != 'X' && opcao != 'x') {
        limparTela();
        
        printf("\n MENU SERVICO\n");
        printf("\tI) INSERIR NOVO\n");
        printf("\tA) ALTERAR\n");
        printf("\tL) LISTAR\n");
        printf("\tD) DELETAR\n");
        printf("\tX) VOLTAR\n");
        printf("OPCAO: ");
        //        scanf("%c", &opcao); fflush(stdin);
        opcao = getchar();
        fflush(stdin);
        
        switch(opcao) {
            case 'i':
            case 'I':
                menuServicoInserir();
                break;
                
            case 'a':
            case 'A':
                menuServicoAlterar();
                break;
                
            case 'l':
            case 'L':
                menuServicoListarTodos();
                break;
                
            case 'd':
            case 'D':
                menuServicoDeletar();
                break;
                
            case 'x':
            case 'X':
                printf("VOLTANDO!");
                break;
                
                
            default:
                printf("OPCAO INVALIDA!");
        }
    }
}

void menuServicoListarTodos() {
    printarTodosRegistrosServico();
    printarMensagemContinuar();
}

void menuServicoInserir() {
    struct Servico servico;
    
    lerDadosServico(&servico);
    salvarRegistroServico(servico);
    printarServicoLista(servico);
    printarServicoTopicos(servico);
}

void menuServicoAlterar() {
    int codigo = 0;
    int registro = 0;
    
    printarTodosRegistrosServico();
    
    printf("INFORME O CODIGO PARA ALTERAR: ");
    scanf("%d", &codigo);
    
    registro = buscarRegistroServicoPorCod(codigo);
    alterarServico(registro);
    
    printarMensagemContinuar();
}

void menuServicoDeletar() {
    int codigo = 0;
    int registro = 0;
    
    printarTodosRegistrosServico();
    
    printf("INFORME O CODIGO PARA ALTERAR: ");
    scanf("%d", &codigo);
    
    registro = buscarRegistroServicoPorCod(codigo);
    deletarServico(registro);
    printarMensagemContinuar();
}

// #############################################################################
// PERSISTENCIA EM BINARIOS

/*
 TIPOS DE ABERTURA DE ARQUIVOS BINARIOS
 
 rb  = Abre um arquivo binario para leitura. Igual ao modo "r" anterior,
 so que o arquivo e binario;
 wb  = Cria um arquivo binario para escrita, como no modo "w" anterior,
 so que o arquivo e binario;
 ab  = Acrescenta dados binarios no fim do arquivo, como no modo "a" anterior,
 so que o arquivo e binario;
 r+b = Abre um arquivo binario para leitura e escrita. O mesmo que "r+" acima,
 so que o arquivo e binario;
 w+b = Cria um arquivo binario para leitura e escrita. O mesmo que "w+" acima,
 so que o arquivo e binario;
 a+b = Acrescenta dados ou cria uma arquivo binario para leitura e escrita.
 O mesmo que "a+" acima, so que o arquivo e binario
 */

// #################################
// ABRIR OS ARQUIVOS
// Verifica se o arquivo já existe. Se nao existir, ele e criado
// se já existir, abre-o em modo de leitura e escrita (r+b)
void abrirTodosArquivos() {
    
    // ---------------------------------
    // Abrir arquivo de Agendamento.
    ponteiroArquivoAGENDAMENTO = fopen(BIN_AGE, "r+b"); //tentar abrir
    
    if(ponteiroArquivoAGENDAMENTO == NULL){
        ponteiroArquivoAGENDAMENTO  = fopen(BIN_AGE, "w+b"); // criar o arquivo
        
        if(ponteiroArquivoAGENDAMENTO == NULL){
            if(MOSTRAR_DEBUG == 1) {
                printf("Erro fatal: impossivel abrir/criar o arquivo '%s'\n", BIN_AGE);
            }
            
            // Se chegar ate aqui, quer dizer que nao conseguiu abrir de jeito neNhum...
            // ai encerra o programa 🍃
            exit(1);
        }
    }
    
    // ---------------------------------
    // Abrir arquivo de Clientes
    ponteiroArquivoCLIENTE = fopen(BIN_CLI, "r+b"); //tentar abrir
    
    if(ponteiroArquivoCLIENTE == NULL){
        ponteiroArquivoCLIENTE  = fopen(BIN_CLI, "w+b"); // criar o arquivo
        
        if(ponteiroArquivoCLIENTE == NULL){
            if(MOSTRAR_DEBUG == 1) {
                printf("Erro fatal: impossivel abrir/criar o arquivo '%s'\n", BIN_CLI);
            }
            
            // Se chegar ate aqui, quer dizer que nao conseguiu abrir de jeito neNhum...
            // ai encerra o programa 🍃
            exit(1);
        }
    }
    
    // ---------------------------------
    // Abrir arquivo de Funcionarios
    ponteiroArquivoFUNCIONARIO = fopen(BIN_FUN, "r+b"); //tentar abrir
    
    if(ponteiroArquivoFUNCIONARIO == NULL){
        ponteiroArquivoFUNCIONARIO  = fopen(BIN_FUN, "w+b"); // criar o arquivo
        
        if(ponteiroArquivoFUNCIONARIO == NULL){
            if(MOSTRAR_DEBUG == 1) {
                printf("Erro fatal: impossivel abrir/criar o arquivo '%s'\n", BIN_FUN);
            }
            
            // Se chegar ate aqui, quer dizer que nao conseguiu abrir de jeito neNhum...
            // ai encerra o programa 🍃
            exit(1);
        }
    }
    
    // ---------------------------------
    // Abrir arquivo de Servico
    ponteiroArquivoSERVICO = fopen(BIN_SER, "r+b"); //tentar abrir
    
    if(ponteiroArquivoSERVICO == NULL){
        ponteiroArquivoSERVICO  = fopen(BIN_SER, "w+b"); // criar o arquivo
        
        if(ponteiroArquivoSERVICO == NULL){
            if(MOSTRAR_DEBUG == 1) {
                printf("Erro fatal: impossivel abrir/criar o arquivo '%s'\n", BIN_SER);
            }
            
            // Se chegar ate aqui, quer dizer que nao conseguiu abrir de jeito neNhum...
            // ai encerra o programa 🍃
            exit(1);
        }
    }
    
    //    #define BIN_TEL "vibe_pet-persistencia_tel.bin"
    //    #define BIN_END "vibe_pet-persistencia_end.bin"
}

void abrirArquivoAgendamento() {
    ponteiroArquivoAGENDAMENTO = fopen(BIN_AGE, "r+b"); //tentar abrir
    
    if(ponteiroArquivoAGENDAMENTO == NULL){
        ponteiroArquivoAGENDAMENTO  = fopen(BIN_AGE, "w+b"); // criar o arquivo
        
        if(ponteiroArquivoAGENDAMENTO == NULL){
            if(MOSTRAR_DEBUG == 1) {
                printf("Erro fatal: impossivel abrir/criar o arquivo '%s'\n", BIN_AGE);
            }
            
            // Se chegar ate aqui, quer dizer que nao conseguiu abrir de jeito neNhum...
            // ai encerra o programa 🍃
            exit(1);
        }
    }
}

void abrirArquivoCliente() {
    ponteiroArquivoCLIENTE = fopen(BIN_CLI, "r+b"); //tentar abrir
    
    if(ponteiroArquivoCLIENTE == NULL){
        ponteiroArquivoCLIENTE  = fopen(BIN_CLI, "w+b"); // criar o arquivo
        
        if(ponteiroArquivoCLIENTE == NULL){
            if(MOSTRAR_DEBUG == 1) {
                printf("Erro fatal: impossivel abrir/criar o arquivo '%s'\n", BIN_CLI);
            }
            
            // Se chegar ate aqui, quer dizer que nao conseguiu abrir de jeito neNhum...
            // ai encerra o programa 🍃
            exit(1);
        }
    }
}

void abrirArquivoFuncionario() {
    ponteiroArquivoFUNCIONARIO = fopen(BIN_FUN, "r+b"); //tentar abrir
    
    if(ponteiroArquivoFUNCIONARIO == NULL){
        ponteiroArquivoFUNCIONARIO  = fopen(BIN_FUN, "w+b"); // criar o arquivo
        
        if(ponteiroArquivoFUNCIONARIO == NULL){
            if(MOSTRAR_DEBUG == 1) {
                printf("Erro fatal: impossivel abrir/criar o arquivo '%s'\n", BIN_FUN);
            }
            
            // Se chegar ate aqui, quer dizer que nao conseguiu abrir de jeito neNhum...
            // ai encerra o programa 🍃
            exit(1);
        }
    }
}

void abrirArquivoServico() {
    ponteiroArquivoSERVICO = fopen(BIN_SER, "r+b"); //tentar abrir
    
    if(ponteiroArquivoSERVICO == NULL){
        ponteiroArquivoSERVICO  = fopen(BIN_SER, "w+b"); // criar o arquivo
        
        if(ponteiroArquivoSERVICO == NULL){
            if(MOSTRAR_DEBUG == 1) {
                printf("Erro fatal: impossivel abrir/criar o arquivo '%s'\n", BIN_SER);
            }
            
            // Se chegar ate aqui, quer dizer que nao conseguiu abrir de jeito neNhum...
            // ai encerra o programa 🍃
            exit(1);
        }
    }
}

// #################################
// FECHAR OS ARQUIVOS
void fecharTodosArquivos() {
    // Atualizar os arquivos.
    fflush(ponteiroArquivoAGENDAMENTO);
    fflush(ponteiroArquivoCLIENTE);
    fflush(ponteiroArquivoFUNCIONARIO);
    fflush(ponteiroArquivoSERVICO);
    //    fflush(ponteiroArquivoTELEFONE);
    //    fflush(ponteiroArquivoENDERECO);
    
    // Fechar os arquivos.
    fclose(ponteiroArquivoAGENDAMENTO);
    fclose(ponteiroArquivoCLIENTE);
    fclose(ponteiroArquivoFUNCIONARIO);
    fclose(ponteiroArquivoSERVICO);
    //    fclose(ponteiroArquivoTELEFONE);
    //    fclose(ponteiroArquivoENDERECO);
}

void fecharArquivoAgendamento() {
    // Atualizar o arquivo.
    fflush(ponteiroArquivoAGENDAMENTO);
    
    // Fechar o arquivo.
    fclose(ponteiroArquivoAGENDAMENTO);
}

void fecharArquivoCliente() {
    // Atualizar o arquivo.
    fflush(ponteiroArquivoCLIENTE);
    
    // Fechar o arquivo.
    fclose(ponteiroArquivoCLIENTE);
}

void fecharArquivoFuncionario() {
    // Atualizar o arquivo.
    fflush(ponteiroArquivoFUNCIONARIO);
    
    // Fechar o arquivo.
    fclose(ponteiroArquivoFUNCIONARIO);
}

void fecharArquivoServico() {
    // Atualizar o arquivo.
    fflush(ponteiroArquivoSERVICO);
    
    // Fechar o arquivo.
    fclose(ponteiroArquivoSERVICO);
}


// #############################################################################
// AGENDAMENTO

// #################################
// LER OS DADOS DE AGENDAMENTO
void lerDadosAgendamento(struct Agendamento *agendamento) {
    char entradaValida = 'n', opcao = ' ';
    char pesquisaCPF[12];
    int pesquisaCodigo = -1;
    
    agendamento->ativo = ' '; // Qualquer coisa menos '*' significa ativo
    
    //----------------------------------
    // Receber a data do agendamento.
    while(entradaValida == 'n') {
        fflush(stdin);
        printf("Data (DD/MM/AAAA)\n");
        printf("%s: ", "Dia");
        scanf("%d", &agendamento->data.dia);
        
        printf("%s: ", "Mes");
        scanf("%d", &agendamento->data.mes);
        
        printf("%s: ", "Ano");
        scanf("%d", &agendamento->data.ano);
        
        if(verificarTempoAteData(agendamento->data) <= 1) {
            printarMensagem("\nAgendamento somente com 48h de antecedencia!\n");
            
        } else {
            entradaValida = 's';
        }
    }
    
    //----------------------------------
    // Receber a hora do agendamento.
    entradaValida = 'n';
    while(entradaValida == 'n') {
        fflush(stdin);
        printf("\nHora (hh:mm:ss)\n");
        printf("%s: ", "Hora");
        scanf("%d", &agendamento->hora.hora);
        
        printf("%s: ", "Minuto");
        scanf("%d", &agendamento->hora.minuto);
        
        //    printf("%s: ", "Segundo");
        //    scanf("%d", &agendamento->hora.segundo);
        agendamento->hora.segundo = 0;
        
        entradaValida = verificarHoraDentroExpediente(agendamento->hora);
    }
    
    //----------------------------------
    // Pegar codigo Cliente.
    entradaValida = 'n';
    while(entradaValida == 'n') {
        printf("\nINSERIR CLIENTE POR:\n");
        printf("\t1) CODIGO\n");
        printf("\t2) CPF\n");
        printf("\t3) LISTAR CLIENTES\n");
        //        printf("\tX) SAIR\n");
        opcao = receberValidarOpcaoLetra("123");
        
        switch(opcao) {
            case '1':
                while(pesquisaCodigo <= -1) {
                    printf("%s: ", "Codigo do cliente");
                    scanf("%d", &pesquisaCodigo);
                    
                    pesquisaCodigo = buscarClientePorCod(pesquisaCodigo).codigo;
                    
                    if(pesquisaCodigo == -1) {
                        if(MOSTRAR_DEBUG == 1) {
                            printarMensagem("\nCodigo nao encontrado!\n");
                        }
                        
                    } else {
                        agendamento->codigoCliente = pesquisaCodigo;
                        entradaValida = 's';
                    }
                }
                break;
                
            case '2':
                while(pesquisaCodigo <= -1) {
                    printf("%s: ", "CPF do cliente");
                    fflush(stdin); gets(pesquisaCPF); fflush(stdin);
                    
                    pesquisaCodigo = buscarClientePorCPF(pesquisaCPF).codigo;
                    
                    if(pesquisaCodigo == -1) {
                        if(MOSTRAR_DEBUG == 1) {
                            printarMensagem("\nCodigo nao encontrado!\n");
                        }
                        
                    } else {
                        agendamento->codigoCliente = pesquisaCodigo;
                        entradaValida = 's';
                    }
                }
                break;
                
            case '3':
                menuClienteListarTodos();
                entradaValida = 'n';
                break;
                
                //            case 'x':
                //                printf("SAINDO!");
                //                entradaValida = 's';
                //                break;
                
            default:
                printf("OPCAO INVALIDA!");
        }
        
        
        if(agendamento->codigoCliente >= 0) {
            entradaValida = 's';
        }
    }
    
    //----------------------------------
    // Pegar codigo Servico.
    entradaValida = 'n';
    while(entradaValida == 'n') {
        menuServicoListarTodos();
        printf("\nCODIGO DO SERVICO\n");
        scanf("%d", &pesquisaCodigo);
        
        pesquisaCodigo = buscarServicoPorCod(pesquisaCodigo).codigo;
        
        if(pesquisaCodigo == -1) {
            if(MOSTRAR_DEBUG == 1) {
                printarMensagem("\nCodigo nao encontrado!\n");
            }
            
        } else {
            agendamento->codigoServico = pesquisaCodigo;
        }
        
        if(agendamento->codigoServico >= 0) {
            entradaValida = 's';
        }
    }
    
    //----------------------------------
    // Pegar codigo Funcionario.
    //TODO: Pegar o id do funcionario que estiver logado no momento
    agendamento->codigoFuncionario = 0;
}

// #################################
// SALVAR DADOS DE AGENDAMENTO
// RETORNO:
//  -    0: se nao houve erros;
//  - != 0: se houve erro(s);
int salvarRegistroAgendamento(struct Agendamento agendamento) {
    int resultado = 0;
    
    // Adicionar codigo, auto-incrementando,
    // pega o codigo do ultimo registro e incrementa.
    agendamento.codigo = acessarUltimoCodigoAgendamento() + 1;
    
    // Poe o novo agendamento no final do arquivo.
    fseek(ponteiroArquivoAGENDAMENTO, 0L, SEEK_END);
    if(fwrite(&agendamento, sizeof(agendamento), 1, ponteiroArquivoAGENDAMENTO)!= 1) {
        if(MOSTRAR_DEBUG == 1) {
            printarMensagem("Adicionar agendamento: Falhou a escrita do registro");
        }
        
        resultado = 1;
    }
    
    // Retornando o valor do resultado.
    return(resultado);
}

// #################################
// BUSCAR AGENDAMENTO POR CODIGO
// Uma funçao para retornar o agendamento procurando pelo codigo.
// RETORNO:
//  - A instancia de Agendamento com os dados encontrados;
//  - 'agendamento.codigo = -1' caso nao encontre.
struct Agendamento buscarAgendamentoPorCod(int codigo) {
    struct Agendamento agendamento;
    int contadorCodigo = -1;
    
    agendamento.codigo = -1;
    
    // Testando se o arquivo foi aberto com sucesso
    if(ponteiroArquivoAGENDAMENTO != NULL) {
        if(MOSTRAR_DEBUG == 1) {
            printf("\n\nArquivo %s foi aberto com sucesso\n\n", BIN_FUN);
        }
        
    } else {
        if(MOSTRAR_DEBUG == 1) {
            printf("\n\nERRO: O arquivo %s nao foi aberto e criado\n", BIN_FUN);
        }
        system ("pause");
        exit(1);
    }
    
    rewind(ponteiroArquivoAGENDAMENTO);
    // Procura em todos os registros do documento.
    while(fread(&agendamento, sizeof(struct Agendamento), 1, ponteiroArquivoAGENDAMENTO)) {
        // Incrementa ++ porque comeca com -1.
        contadorCodigo += 1;
        
        // Compara o cod recebido.
        if(agendamento.codigo == codigo) {
            // Se encontrar, retorna a poisicao(linha) do registro.
            return  agendamento;
        }
    }
    
    // Se nao achar o codigo, retorna -1 para indicar que nao achou.
    if(MOSTRAR_DEBUG == 1) {
        printf("\n\nERRO: registro nao encontrado.");
    }
    
    return agendamento;
}

// #################################
// BUSCAR REGISTRO AGENDAMENTO POR CODIGO
// Uma funçao para retornar o registro (posicao no arquivo) procurando pelo codigo.
// RETORNO:
//  -  O numero do registro, caso encontre;
//  - -1 caso, nao encontre.
int buscarRegistroAgendamentoPorCod(int codigo) {
    struct Agendamento agendamento;
    int contadorCodigo = -1;
    
    // Testando se o arquivo foi aberto com sucesso
    if(ponteiroArquivoAGENDAMENTO != NULL) {
        if(MOSTRAR_DEBUG == 1) {
            printf("\n\nArquivo %s foi aberto com sucesso\n\n", BIN_FUN);
        }
        
    } else {
        if(MOSTRAR_DEBUG == 1) {
            printf("\n\nERRO: O arquivo %s nao foi aberto e criado\n", BIN_FUN);
        }
        system ("pause");
        exit(1);
    }
    
    rewind(ponteiroArquivoAGENDAMENTO);
    // Procura em todos os registros do documento.
    while(fread(&agendamento, sizeof(struct Agendamento), 1, ponteiroArquivoAGENDAMENTO)) {
        // Incrementa '++' porque comeca com -1.
        contadorCodigo += 1;
        
        // Compara o cod recebido.
        if(agendamento.codigo == codigo) {
            // Se encontrar, retorna a poisicao(linha) do registro.
            return  contadorCodigo;
        }
    }
    
    // Se nao achar o codigo, retorna -1 para indicar que nao achou.
    if(MOSTRAR_DEBUG == 1) {
        printf("\n\nERRO: registro nao encontrado.");
    }
    contadorCodigo = -1;
    
    return contadorCodigo;
}

// #################################
// BUSCAR CODIGO DO ULTIMO REGISTRO
// Uma funçao para ir ate o ultimo registro, ultimo agendamento cadastrado e
// retorna seu respectivo codigo.
// RETORNO:
//  - O int do codigo.
int acessarUltimoCodigoAgendamento() {
    struct Agendamento agendamento;
    
    fseek(ponteiroArquivoAGENDAMENTO, -1 * sizeof(struct Agendamento), SEEK_END);
    if(fread(&agendamento, sizeof(struct Agendamento), -1, ponteiroArquivoAGENDAMENTO)!= 1){
        if(MOSTRAR_DEBUG == 1) {
            printarMensagem("01 - Problemas na leitura do registro!!!");
        }
        return -1;
    }
    
    if(agendamento.codigo <= -1){
        return 0;
        
    } else {
        return agendamento.codigo;
    }
}


// #################################
// PRINTAR O CABECALHO DA LISTA DE AGENDAMENTO
// Mostra na tela os nomes dos 'campos'.
void printarCabecalhoListaAgendamento() {
    printf("AGENDAMENTOS\n");
    interfaceLinhaSeparadoraGrande();
    printf("%-5s|%-10s|%-5s|%-30s|%-30s|%-30s\n", "COD", "DATA", "HORA", "SERVICO", "CLIENTE", "FUNCIONARIO");
    interfaceLinhaSeparadoraGrande();
}

// #################################
// PRINTAR UM PERFIL DE AGENDAMENTO:
// mostra na tela os dados existentes no registro
void printarAgendamentoLista(struct Agendamento agendamento) {
    //TODO: criar View de perfil AGENDAMENTO.
    struct Cliente cliente;
    struct Funcionario funcionario;
    struct Servico servico;
    
    cliente     = buscarClientePorCod(agendamento.codigoCliente);
    funcionario = buscarFuncionarioPorCod(agendamento.codigoFuncionario);
    servico     = buscarServicoPorCod(agendamento.codigoServico);
    
    printf("%05d|%-10s|%5s", agendamento.codigo, stringDataFormatada(agendamento.data), stringHoraFormatada(agendamento.hora));
    printf("|%-30s|%-30s|%-30s\n", servico.nome, cliente.nome, funcionario.nome);
}

void printarAgendamentoTopicos(struct Agendamento agendamento) {
    struct Cliente cliente;
    struct Funcionario funcionario;
    struct Servico servico;
    
    cliente     = buscarClientePorCod(agendamento.codigoCliente);
    funcionario = buscarFuncionarioPorCod(agendamento.codigoFuncionario);
    servico     = buscarServicoPorCod(agendamento.codigoServico);
    
    if(agendamento.ativo == ' ') {
        printf("%-11s: %d\n", "CODIGO", agendamento.codigo);
        
        printf("%-11s: ", "DATA"); printarDataFormatada(agendamento.data); printf("\n");
        printf("%-11s: ", "HORA"); printarHoraFormatada(agendamento.hora); printf("\n");
        
        printf("%-11s: %s\n", "SERVICO", servico.nome);
        printf("%-11s: %s\n", "CLIENTE", cliente.nome);
        printf("%-11s: %s\n", "FUNCIONARIO", funcionario.nome);
        
    } else {
        printf("\nAGENDAMENTO DELETADO!\n");
    }
}

// #################################
// LER TODOS PERFIS DE AGENDAMENTO
void printarTodosRegistrosAgendamento() {
    struct Agendamento agendamento;
    struct Cliente cliente;
    struct Funcionario funcionario;
    struct Servico servico;
    
    cliente     = buscarClientePorCod(agendamento.codigoCliente);
    funcionario = buscarFuncionarioPorCod(agendamento.codigoFuncionario);
    servico     = buscarServicoPorCod(agendamento.codigoServico);
    
    int n_Linhas = 0;
    
    // Volta o ponteiro para o inicio.
    rewind(ponteiroArquivoAGENDAMENTO);
    
    printarCabecalhoListaAgendamento();
    
    while(1){
        if(fread(&agendamento, sizeof(agendamento), 1, ponteiroArquivoAGENDAMENTO)!= 1)break; /*Sair do laço*/
        if(agendamento.ativo == '*') continue; /*Passa ao proximo*/
        printarAgendamentoLista(agendamento);
        //        printarAgendamentoTopicos(agendamento);
        n_Linhas++;
        if(n_Linhas%20 == 0)
            printarMensagem("Pressione <Enter> para continuar .  .  .");
    }
}

// #################################
// ALTERAR UM PERFIL DE AGENDAMENTO
// Encontra a posicao do registro pelo numero que representa a linha na qual está
// e mostra como está momento antes da alteracao, apos isso rece novos dados e atualiza.
// PARAMETRO:
//   - registro: int da 'linha' que está o referido registro.
void alterarAgendamento(int registro) {
    struct Agendamento agendamentoAux;
    
    if(fseek(ponteiroArquivoAGENDAMENTO, (registro)*sizeof(agendamentoAux), SEEK_SET) != 0){
        printarMensagem("Registro inexistente ou problemas no posicionamento!!!");
        return;
    }
    
    if(fread(&agendamentoAux, sizeof(struct Agendamento), 1, ponteiroArquivoAGENDAMENTO)!= 1){
        printarMensagem("02 - Problemas na leitura do registro!!!");
        return;
    }
    
    if(agendamentoAux.ativo == '*'){
        printarMensagem("Um registro apagado nao pode ser alterado!!! \n\n");
        return;
    }
    
    printf("\n\n Dados Atuais \n\n");
    printarAgendamentoTopicos(agendamentoAux);
    
    printf("\n\n Novos dados \n\n");
    lerDadosAgendamento(&agendamentoAux);
    
    // recuar um registro no arquivo
    fseek(ponteiroArquivoAGENDAMENTO, -(int) sizeof(struct Agendamento), SEEK_CUR);
    // reescrever o registro;
    fwrite(&agendamentoAux, sizeof(struct Agendamento), 1, ponteiroArquivoAGENDAMENTO);
    fflush(ponteiroArquivoAGENDAMENTO); /*despejar os arquivos no disco rígido*/
}

// #################################
// DELETAR UM PERFIL DE AGENDAMENTO
// Encontra a posicao do registro pelo numero que representa a linha na qual está
// e apaga logicamente (deixa invisivel);
// PARAMETRO:
//   - registro: int da 'linha' que está o referido registro.
void deletarAgendamento(int registro) {
    struct Agendamento agendamentoAux;
    
    if(fseek(ponteiroArquivoAGENDAMENTO, (registro)*sizeof(agendamentoAux), SEEK_SET) != 0){
        printarMensagem("Registro inexistente ou problemas no posicionamento!!!");
        return;
    }
    
    if(fread(&agendamentoAux, sizeof(struct Agendamento), 1, ponteiroArquivoAGENDAMENTO)!= 1){
        printarMensagem("03 - Problemas na leitura do registro!!!");
        return;
    }
    
    if(agendamentoAux.ativo == '*'){
        printarMensagem("Registro já está apagado!!!\n\n");
        return;
    }
    
    printf("\n\n Dados Atuais \n\n");
    printarAgendamentoTopicos(agendamentoAux);
    
    fflush(stdin);
    printf("\n\n Apagar o registro (s/n)???: ");
    char resp = getchar();
    
    if(resp != 's' && resp != 'S') {
        return;
    }
    
    fflush(stdin);
    agendamentoAux.ativo = '*';
    
    // recuar um registro no arquivo
    fseek(ponteiroArquivoAGENDAMENTO, -(int) sizeof(struct Agendamento), SEEK_CUR);
    // reescrever o registro;
    fwrite(&agendamentoAux, sizeof(struct Agendamento), 1, ponteiroArquivoAGENDAMENTO);
    fflush(ponteiroArquivoAGENDAMENTO); /*despejar os arquivos no disco rígido*/
    
    
    // recuar um registro no arquivo
    fseek(ponteiroArquivoAGENDAMENTO, -(int) sizeof(struct Agendamento), SEEK_CUR);
    // reescrever o registro;
    fwrite(&agendamentoAux, sizeof(struct Agendamento), 1, ponteiroArquivoAGENDAMENTO);
    fflush(ponteiroArquivoAGENDAMENTO); /*despejar os arquivos no disco rígido*/
}


// #############################################################################
// CLIENTE

// #################################
// LER OS DADOS DE CLIENTE
void lerDadosCliente(struct Cliente *cliente) {
    
    printf("Nome : "); fflush(stdin);
    gets(cliente->nome); fflush(stdin);
    
    //    printf("CPF:");
    //    gets(cliente->cpf); fflush(stdin);
    //TODO: Testar depois
    receberValidarCPF(cliente->cpf);
    
//    printf("Email: ");
//    gets(cliente->email); fflush(stdin);
    receberValidarCPF(cliente->email);
    
    printf("Endereco:");
    gets(cliente->endereco); fflush (stdin);
    
    printf("Telefone:");
    scanf("%d", &cliente->telefone); fflush (stdin);
    
    printf("DATA DE NASCIMENTO\n");
//    printf("Dia: ");
//    scanf("%d", &cliente->nascimento.dia);
//
//    printf("Mes: ");
//    scanf("%d", &cliente->nascimento.mes);
//
//    printf("Ano: ");
//    scanf("%d", &cliente->nascimento.ano);
    cliente->nascimento = receberValidarData();
    
    cliente->ativo = ' '; // Qualquer coisa menos '*' significa ativo
}


// #################################
// SALVAR DADOS DE CLIENTE
// RETORNO:
//  -    0: se nao houve erros;
//  - != 0: se houve erro(s);
int salvarRegistroCliente(struct Cliente cliente) {
    int resultado = 0;
    
    // Adicionar codigo, auto-incrementando,
    // pega o codigo do ultimo registro e incrementa.
    cliente.codigo = acessarUltimoCodigoCliente() + 1;
    
    // Poe o novo cliente no final do arquivo.
    fseek(ponteiroArquivoCLIENTE, 0L, SEEK_END);
    if(fwrite(&cliente, sizeof(cliente), 1, ponteiroArquivoCLIENTE)!= 1) {
        if(MOSTRAR_DEBUG == 1) {
            printarMensagem("Adicionar cliente: Falhou a escrita do registro");
        }
        
        resultado = 1;
    }
    
    // Retornando o valor do resultado.
    return(resultado);
}

// #################################
// BUSCAR CLIENTE POR CODIGO
// Uma funçao para retornar o cliente procurando pelo codigo.
// RETORNO:
//  -  Uma instancia de Cliente com os dados encontrados.
//  - A instancia de Agendamento com os dados encontrados;
//  - 'cliente.codigo = -1' caso nao encontre.
struct Cliente buscarClientePorCod(int codigo) {
    struct Cliente clienteAuxiliar;
    int contadorCodigo = -1;
    
    clienteAuxiliar.codigo = -1;
    
    // Testando se o arquivo foi aberto com sucesso
    if(ponteiroArquivoCLIENTE != NULL) {
        if(MOSTRAR_DEBUG == 1) {
            printf("\n\nArquivo %s foi aberto com sucesso\n\n", BIN_CLI);
        }
        
    } else {
        if(MOSTRAR_DEBUG == 1) {
            printf("\n\nERRO: O arquivo %s nao foi aberto e criado\n", BIN_CLI);
        }
        system("pause");
        exit(1);
    }
    
    rewind(ponteiroArquivoCLIENTE);
    // Procura em todos os registros do documento.
    while(fread(&clienteAuxiliar, sizeof(struct Cliente), 1, ponteiroArquivoCLIENTE)) {
        // Incrementa '++' porque comeca com -1.
        contadorCodigo += 1;
        
        // Compara o cod recebido.
        if(clienteAuxiliar.codigo == codigo) {
            // Se encontrar, retorna a poisicao(linha) do registro.
            return  clienteAuxiliar;
        }
    }
    
    // Se nao achar o codigo, retorna -1 para indicar que nao achou.
    if(MOSTRAR_DEBUG == 1) {
        printf("\n\nERRO: registro nao encontrado.");
    }
    
    return clienteAuxiliar;
}

// #################################
// BUSCAR CLIENTE POR CODIGO
// Uma funçao para retornar o cliente procurando pelo codigo.
// RETORNO:
//  -  Uma instancia de Cliente com os dados encontrados.
//  - A instancia de Agendamento com os dados encontrados;
//  - 'cliente.codigo = -1' caso nao encontre.
struct Cliente buscarClientePorCPF(char cpf[12]) {
    struct Cliente clienteAuxiliar;
    int contadorCodigo = -1;
    
    clienteAuxiliar.codigo = -1;
    
    // Testando se o arquivo foi aberto com sucesso
    if(ponteiroArquivoCLIENTE != NULL) {
        if(MOSTRAR_DEBUG == 1) {
            printf("\n\nArquivo %s foi aberto com sucesso\n\n", BIN_CLI);
        }
        
    } else {
        if(MOSTRAR_DEBUG == 1) {
            printf("\n\nERRO: O arquivo %s nao foi aberto e criado\n", BIN_CLI);
        }
        system("pause");
        exit(1);
    }
    
    rewind(ponteiroArquivoCLIENTE);
    // Procura em todos os registros do documento.
    while(fread(&clienteAuxiliar, sizeof(struct Cliente), 1, ponteiroArquivoCLIENTE)) {
        // Incrementa '++' porque comeca com -1.
        contadorCodigo += 1;
        
        // Compara o cod recebido.
        if(clienteAuxiliar.cpf == cpf) {
            // Se encontrar, retorna a poisicao(linha) do registro.
            return  clienteAuxiliar;
        }
    }
    
    // Se nao achar o codigo, retorna -1 para indicar que nao achou.
    if(MOSTRAR_DEBUG == 1) {
        printf("\n\nERRO: registro nao encontrado.");
    }
    
    return clienteAuxiliar;
}

// #################################
// BUSCAR REGISTRO DE CLIENTE POR CODIGO
// Uma funçao para retornar o registro (posicao no arquivo) procurando pelo codigo.
// RETORNO:
//  -  O numero do registro, caso encontre;
//  - -1 caso, nao encontre.
int buscarRegistroClientePorCod(int codigo) {
    struct Cliente clienteAuxiliar;
    int contadorCodigo = -1;
    
    // Testando se o arquivo foi aberto com sucesso
    if(ponteiroArquivoCLIENTE != NULL) {
        if(MOSTRAR_DEBUG == 1) {
            printf("\n\nArquivo %s foi aberto com sucesso\n\n", BIN_CLI);
        }
        
    } else {
        if(MOSTRAR_DEBUG == 1) {
            printf("\n\nERRO: O arquivo %s nao foi aberto e criado\n", BIN_CLI);
        }
        system ("pause");
        exit(1);
    }
    
    rewind(ponteiroArquivoCLIENTE);
    // Procura em todos os registros do documento.
    while(fread(&clienteAuxiliar, sizeof(struct Cliente), 1, ponteiroArquivoCLIENTE)) {
        // Incrementa ++ porque comeca com -1.
        contadorCodigo += 1;
        
        // Compara o cod recebido.
        if(clienteAuxiliar.codigo == codigo) {
            // Se encontrar, retorna a poisicao(linha) do registro.
            return  contadorCodigo;
        }
    }
    
    // Se nao achar o codigo, retorna -1 para indicar que nao achou.
    if(MOSTRAR_DEBUG == 1) {
        printf("\n\nERRO: registro nao encontrado.");
    }
    contadorCodigo = -1;
    
    return contadorCodigo;
}

// #################################
// BUSCAR CODIGO DO ULTIMO REGISTRO
// Uma funçao para ir ate o ultimo registro, ultimo cliente cadastrado e
// retorna seu respectivo codigo.
// RETORNO:
//  - O int do codigo.
int acessarUltimoCodigoCliente() {
    struct Cliente cliente;
    
    fseek(ponteiroArquivoCLIENTE, -1 * sizeof(struct Cliente), SEEK_END);
    if(fread(&cliente, sizeof(struct Cliente), -1, ponteiroArquivoCLIENTE)!= 1){
        if(MOSTRAR_DEBUG == 1) {
            printarMensagem("07 - Problemas na leitura do registro!!!");
        }
        return -1;
    }
    
    if(cliente.codigo <= -1){
        return 0;
        
    } else {
        return cliente.codigo;
    }
}

// #################################
// PRINTAR UM PERFIL DE CLIENTE:
// mostra na tela os dados existentes no registro
void printarClienteLista(struct Cliente cliente) {
    //TODO: criar View de perfil CLIENTE.
    
    printf("%05d|%-30s|%-15s|%-30s|%-30s|%-15d|%02d/%02d/%d\n", cliente.codigo, cliente.nome, formatarCPF(cliente.cpf), cliente.email, cliente.endereco, cliente.telefone, cliente.nascimento.dia, cliente.nascimento.mes, cliente.nascimento.ano);
}

void printarClienteTopicos(struct Cliente cliente) {
    
    printf("%-8s: %d\n", "", cliente.codigo);
    
    if(cliente.ativo != '*') {
        printf("%-10s: %d\n", "CODIGO", cliente.codigo);
        printf("%-10s: %s\n", "NOME", cliente.nome);
        printf("%-10s: %s\n", "CPF", formatarCPF(cliente.cpf));
        printf("%-10s: %s\n", "EMAIL", cliente.email);
        printf("%-10s: %s\n", "ENDERECO", cliente.endereco);
        printf("%-10s: %d\n", "TELEFONE", cliente.telefone);
        printf("%-10s: %02d/%02d/%d\n", "NASCIMENTO", cliente.nascimento.dia, cliente.nascimento.mes, cliente.nascimento.ano);
        
    } else {
        printf("\nCLIENTE DELETADO!\n");
    }
}

void printarCabecalhoTodosClientes() {
    printf("CLIENTES\n");
    interfaceLinhaSeparadoraGrande();
    printf("%-5s|%-30s|%-15s|%-30s|%-30s|%-15s|%-10s|\n", "COD", "NOME", "CPF", "EMAIL", "ENDERECO","TELEFONE", "NASC");
    interfaceLinhaSeparadoraGrande();
}

// #################################
// LER TODOS PERFIS DE CLIENTE
void printarTodosRegistrosCliente() {
    struct Cliente cliente;
    int n_Linhas = 0;
    
    // Volta o ponteiro para o inicio.
    rewind(ponteiroArquivoCLIENTE);
    
    printarCabecalhoTodosClientes();
    
    while(1){
        if(fread(&cliente, sizeof(cliente), 1, ponteiroArquivoCLIENTE)!= 1) break; /*Sair do laço*/
        if(cliente.ativo == '*') continue; /*Passa ao proximo*/
        printarClienteLista(cliente);
        //        printarClienteTopicos(cliente);
        n_Linhas++;
        if(n_Linhas%20 == 0)
            printarMensagem("Pressione <Enter> para continuar .  .  .");
    }
    //    printf("\n\n\n");
    
}

// #################################
// ALTERAR UM PERFIL DE CLIENTE
// Encontra a posicao do registro pelo numero que representa a linha na qual está
// e mostra como está momento antes da alteracao, apos isso rece novos dados e atualiza.
// PARAMETRO:
//   - registro: int da 'linha' que está o referido registro.
void alterarCliente(int registro) {
    struct Cliente clienteAux;
    
    if(fseek(ponteiroArquivoCLIENTE, (registro)*sizeof(clienteAux), SEEK_SET) != 0){
        printarMensagem("Registro inexistente ou problemas no posicionamento!!!");
        return;
    }
    
    if(fread(&clienteAux, sizeof(struct Cliente), 1, ponteiroArquivoCLIENTE)!= 1){
        printarMensagem("08 - Problemas na leitura do registro!!!");
        return;
    }
    
    if(clienteAux.ativo == '*'){
        printarMensagem("Um registro apagado nao pode ser alterado!!! \n\n");
        return;
    }
    
    printf("\n\n Dados Atuais \n\n");
    printarClienteTopicos(clienteAux);
    
    printf("\n\n Novos dados \n\n");
    lerDadosCliente(&clienteAux);
    
    // recuar um registro no arquivo
    fseek(ponteiroArquivoCLIENTE, -(int) sizeof(struct Cliente), SEEK_CUR);
    // reescrever o registro;
    fwrite(&clienteAux, sizeof(struct Cliente), 1, ponteiroArquivoCLIENTE);
    fflush(ponteiroArquivoCLIENTE); /*despejar os arquivos no disco rígido*/
}

// #################################
// DELETAR UM PERFIL DE CLIENTE
// Encontra a posicao do registro pelo numero que representa a linha na qual está
// e apaga logicamente (deixa invisivel);
// PARAMETRO:
//   - registro: int da 'linha' que está o referido registro.
void deletarCliente(int registro) {
    struct Cliente clienteAux;
    
    if(fseek(ponteiroArquivoCLIENTE, (registro)*sizeof(clienteAux), SEEK_SET) != 0){
        printarMensagem("Registro inexistente ou problemas no posicionamento!!!");
        return;
    }
    
    if(fread(&clienteAux, sizeof(struct Cliente), 1, ponteiroArquivoCLIENTE)!= 1){
        printarMensagem("09 - Problemas na leitura do registro!!!");
        return;
    }
    
    if(clienteAux.ativo == '*'){
        printarMensagem("Registro já está apagado!!!\n\n");
        return;
    }
    
    printf("\n\n Dados Atuais \n\n");
    printarClienteTopicos(clienteAux);
    
    fflush(stdin);
    printf("\n\n Apagar o registro (s/n)???: ");
    char resp = getchar();
    
    if(resp != 's' && resp != 'S') {
        return;
    }
    
    fflush(stdin);
    clienteAux.ativo = '*';
    
    // recuar um registro no arquivo
    fseek(ponteiroArquivoCLIENTE, -(int) sizeof(struct Cliente), SEEK_CUR);
    // reescrever o registro;
    fwrite(&clienteAux, sizeof(struct Cliente), 1, ponteiroArquivoCLIENTE);
    fflush(ponteiroArquivoCLIENTE); /*despejar os arquivos no disco rígido*/
    
    
    // recuar um registro no arquivo
    fseek(ponteiroArquivoCLIENTE, -(int) sizeof(struct Cliente), SEEK_CUR);
    // reescrever o registro;
    fwrite(&clienteAux, sizeof(struct Cliente), 1, ponteiroArquivoCLIENTE);
    fflush(ponteiroArquivoCLIENTE); /*despejar os arquivos no disco rígido*/
}


// #############################################################################
// FUNCIONARIO

// #################################
// LER OS DADOS DE FUNCIONARIO
void lerDadosFuncionario(struct Funcionario *funcionario) {
    
    fflush(stdin);
    printf("Nome : ");
    gets(funcionario->nome); fflush(stdin);
    
    //    printf("CPF  : ");
    //    gets(funcionario->cpf); fflush(stdin);
    //TODO: Testar depois
    receberValidarCPF(funcionario->cpf);
    
    printf("Senha: ");
    gets(funcionario->senha); fflush(stdin);
    
    printf("Cargo: ");
    scanf("%d", &funcionario->cargo); // Funcionario 0 = adm
    fflush(stdin);
    
    funcionario->ativo = ' '; // Qualquer coisa menos '*' significa ativo
}

// #################################
// SALVAR DADOS DE FUNCIONARIO
// RETORNO:
//  -    0: se nao houve erros;
//  - != 0: se houve erro(s);
int salvarRegistroFuncionario(struct Funcionario funcionario) {
    int resultado = 0;
    
    // Adicionar codigo, auto-incrementando,
    // pega o codigo do ultimo registro e incrementa.
    funcionario.codigo = acessarUltimoCodigoFuncionario() + 1;
    
    // Poe o novo funcionario no final do arquivo.
    fseek(ponteiroArquivoFUNCIONARIO, 0L, SEEK_END);
    if(fwrite(&funcionario, sizeof(funcionario), 1, ponteiroArquivoFUNCIONARIO)!= 1) {
        if(MOSTRAR_DEBUG == 1) {
            printarMensagem("Adicionar funcionario: Falhou a escrita do registro");
        }
        
        resultado = 1;
    }
    
    // Retornando o valor do resultado.
    return(resultado);
}

// #################################
// BUSCAR FUNCIONARIO POR CODIGO
// Uma funçao para retornar o funcionario procurando pelo codigo.
// RETORNO:
//  - A instancia com os dados encontrados.
//  - A instancia de Agendamento com os dados encontrados;
//  - 'funcionario.codigo = -1' caso nao encontre.
struct Funcionario buscarFuncionarioPorCod(int codigo) {
    struct Funcionario funcionario;
    int contadorCodigo = -1;
    
    funcionario.codigo = -1;
    
    // Testando se o arquivo foi aberto com sucesso
    if(ponteiroArquivoFUNCIONARIO != NULL) {
        if(MOSTRAR_DEBUG == 1) {
            printf("\n\nArquivo %s foi aberto com sucesso\n\n", BIN_FUN);
        }
        
    } else {
        if(MOSTRAR_DEBUG == 1) {
            printf("\n\nERRO: O arquivo %s nao foi aberto e criado\n", BIN_FUN);
        }
        system ("pause");
        exit(1);
    }
    
    rewind(ponteiroArquivoFUNCIONARIO);
    // Procura em todos os registros do documento.
    while(fread(&funcionario, sizeof(struct Funcionario), 1, ponteiroArquivoFUNCIONARIO)) {
        // Incrementa ++ porque comeca com -1.
        contadorCodigo += 1;
        
        // Compara o cod recebido.
        if(funcionario.codigo == codigo) {
            // Se encontrar, retorna a poisicao(linha) do registro.
            return funcionario;
        }
    }
    
    // Se nao achar o codigo, retorna -1 para indicar que nao achou.
    if(MOSTRAR_DEBUG == 1) {
        printf("\n\nERRO: registro nao encontrado.");
    }
    
    return funcionario;
}

// #################################
// BUSCAR FUNCIONARIO POR CODIGO
// Uma funçao para retornar o funcionario procurando pelo codigo.
// RETORNO:
//  - A instancia com os dados encontrados.
//  - A instancia de Agendamento com os dados encontrados;
//  - 'funcionario.codigo = -1' caso nao encontre.
struct Funcionario buscarFuncionarioPorCPF(char cpf[12]) {
    struct Funcionario funcionario;
    int contadorCodigo = -1;
    
    funcionario.codigo = -1;
    
    // Testando se o arquivo foi aberto com sucesso
    if(ponteiroArquivoFUNCIONARIO != NULL) {
        if(MOSTRAR_DEBUG == 1) {
            printf("\n\nArquivo %s foi aberto com sucesso\n\n", BIN_FUN);
        }
        
    } else {
        if(MOSTRAR_DEBUG == 1) {
            printf("\n\nERRO: O arquivo %s nao foi aberto e criado\n", BIN_FUN);
        }
        system ("pause");
        exit(1);
    }
    
    rewind(ponteiroArquivoFUNCIONARIO);
    // Procura em todos os registros do documento.
    while(fread(&funcionario, sizeof(struct Funcionario), 1, ponteiroArquivoFUNCIONARIO)) {
        // Incrementa ++ porque comeca com -1.
        contadorCodigo += 1;
        
        // Compara o cod recebido.
        if(funcionario.cpf == cpf) {
            // Se encontrar, retorna a poisicao(linha) do registro.
            return funcionario;
        }
    }
    
    // Se nao achar o codigo, retorna -1 para indicar que nao achou.
    if(MOSTRAR_DEBUG == 1) {
        printf("\n\nERRO: registro nao encontrado.");
    }
    
    return funcionario;
}

// #################################
// BUSCAR REGISTRO DE FUNCIONARIO POR CODIGO
// Uma funçao para retornar o registro (posicao no arquivo) procurando pelo codigo.
// RETORNO:
//  -  O numero do registro, caso encontre;
//  - -1 caso, nao encontre.
int buscarRegistroFuncionarioPorCod(int codigo) {
    struct Funcionario funcionario;
    int contadorCodigo = -1;
    
    // Testando se o arquivo foi aberto com sucesso
    if(ponteiroArquivoFUNCIONARIO != NULL) {
        if(MOSTRAR_DEBUG == 1) {
            printf("\n\nArquivo %s foi aberto com sucesso\n\n", BIN_FUN);
        }
        
    } else {
        if(MOSTRAR_DEBUG == 1) {
            printf("\n\nERRO: O arquivo %s nao foi aberto e criado\n", BIN_FUN);
        }
        system ("pause");
        exit(1);
    }
    
    rewind(ponteiroArquivoFUNCIONARIO);
    // Procura em todos os registros do documento.
    while(fread(&funcionario, sizeof(struct Funcionario), 1, ponteiroArquivoFUNCIONARIO)) {
        // Incrementa ++ porque comeca com -1.
        contadorCodigo += 1;
        
        // Compara o cod recebido.
        if(funcionario.codigo == codigo) {
            // Se encontrar, retorna a poisicao(linha) do registro.
            return  contadorCodigo;
        }
    }
    
    // Se nao achar o codigo, retorna -1 para indicar que nao achou.
    if(MOSTRAR_DEBUG == 1) {
        printf("\n\nERRO: registro nao encontrado.");
    }
    contadorCodigo = -1;
    
    return contadorCodigo;
}

// #################################
// BUSCAR CODIGO DO ULTIMO REGISTRO
// Uma funçao para ir ate o ultimo registro, ultimo funcionario cadastrado e
// retorna seu respectivo codigo.
// RETORNO:
//  - O int do codigo.
int acessarUltimoCodigoFuncionario() {
    struct Funcionario funcionario;
    
    fseek(ponteiroArquivoFUNCIONARIO, -1 * sizeof(struct Funcionario), SEEK_END);
    if(fread(&funcionario, sizeof(struct Funcionario), -1, ponteiroArquivoFUNCIONARIO)!= 1){
        if(MOSTRAR_DEBUG == 1) {
            printarMensagem("10 - Problemas na leitura do registro!!!");
        }
        return -1;
    }
    
    if(funcionario.codigo <= -1){
        return 0;
        
    } else {
        return funcionario.codigo;
    }
}

// #################################
// PRINTAR UM PERFIL DE FUNCIONARIO:
// mostra na tela os dados existentes no registro
void printarFuncionarioLista(struct Funcionario funcionario) {
    //TODO: criar View de perfil FUNCIONARIO.
    
    printf("%05d|%-30s|%-15s|%-30s\n", funcionario.codigo, funcionario.nome, formatarCPF(funcionario.cpf), funcionario.senha);
}

void printarFuncionarioTopicos(struct Funcionario funcionario) {
    
    if(funcionario.ativo == ' ') {
        printf("%-6s: %d\n", "CODIGO", funcionario.codigo);
        printf("%-6s: %s\n", "NOME", funcionario.nome);
        printf("%-6s: %s\n", "CPF", formatarCPF(funcionario.cpf));
        printf("%-6s: %s\n", "SENHA", funcionario.senha);
        if(funcionario.cargo == 1) {
            printf("%-6s: %s\n", "CARGO", "Funcionario");
            
        } else if(funcionario.cargo == 0) {
            printf("%-6s: %s\n", "CARGO", "Funcionario");
        }
        
    } else {
        printf("\nFUNCIONARIO DELETADO!\n");
    }
}

// #################################
// LER TODOS PERFIS DE FUNCIONARIO
void printarTodosRegistrosFuncionario() {
    struct Funcionario funcionario;
    int n_Linhas = 0;
    
    // Volta o ponteiro para o inicio.
    rewind(ponteiroArquivoFUNCIONARIO);
    
    printf("FUNCIONARIOS\n");
    interfaceLinhaSeparadoraGrande();
    printf("%-5s|%-30s|%-15s|%-30s\n", "COD", "NOME", "CPF", "SENHA");
    interfaceLinhaSeparadoraGrande();
    
    while(1){
        if(fread(&funcionario, sizeof(funcionario), 1, ponteiroArquivoFUNCIONARIO)!= 1)break; /*Sair do laço*/
        if(funcionario.ativo == '*') continue; /*Passa ao proximo*/
        printarFuncionarioLista(funcionario);
        //        printarFuncionarioTopicos(funcionario);
        n_Linhas++;
        if(n_Linhas%20 == 0)
            printarMensagem("Pressione <Enter> para continuar .  .  .");
    }
}

// #################################
// ALTERAR UM PERFIL DE FUNCIONARIO
// Encontra a posicao do registro pelo numero que representa a linha na qual está
// e mostra como está momento antes da alteracao, apos isso rece novos dados e atualiza.
// PARAMETRO:
//   - registro: int da 'linha' que está o referido registro.
void alterarFuncionario(int registro) {
    struct Funcionario funcionarioAux;
    
    if(fseek(ponteiroArquivoFUNCIONARIO, (registro)*sizeof(funcionarioAux), SEEK_SET) != 0){
        printarMensagem("Registro inexistente ou problemas no posicionamento!!!");
        return;
    }
    
    if(fread(&funcionarioAux, sizeof(struct Funcionario), 1, ponteiroArquivoFUNCIONARIO)!= 1){
        printarMensagem("11 - Problemas na leitura do registro!!!");
        return;
    }
    
    if(funcionarioAux.ativo == '*'){
        printarMensagem("Um registro apagado nao pode ser alterado!!! \n\n");
        return;
    }
    
    printf("\n\n Dados Atuais \n\n");
    printarFuncionarioTopicos(funcionarioAux);
    
    printf("\n\n Novos dados \n\n");
    lerDadosFuncionario(&funcionarioAux);
    
    // recuar um registro no arquivo
    fseek(ponteiroArquivoFUNCIONARIO, -(int) sizeof(struct Funcionario), SEEK_CUR);
    // reescrever o registro;
    fwrite(&funcionarioAux, sizeof(struct Funcionario), 1, ponteiroArquivoFUNCIONARIO);
    fflush(ponteiroArquivoFUNCIONARIO); /*despejar os arquivos no disco rígido*/
}

// #################################
// DELETAR UM PERFIL DE FUNCIONARIO
// Encontra a posicao do registro pelo numero que representa a linha na qual está
// e apaga logicamente (deixa invisivel);
// PARAMETRO:
//   - registro: int da 'linha' que está o referido registro.
void deletarFuncionario(int registro) {
    struct Funcionario funcionarioAux;
    
    if(fseek(ponteiroArquivoFUNCIONARIO, (registro)*sizeof(funcionarioAux), SEEK_SET) != 0){
        printarMensagem("Registro inexistente ou problemas no posicionamento!!!");
        return;
    }
    
    if(fread(&funcionarioAux, sizeof(struct Funcionario), 1, ponteiroArquivoFUNCIONARIO)!= 1){
        printarMensagem("12 - Problemas na leitura do registro!!!");
        return;
    }
    
    if(funcionarioAux.ativo == '*'){
        printarMensagem("Registro já está apagado!!!\n\n");
        return;
    }
    
    printf("\n\n Dados Atuais \n\n");
    printarFuncionarioTopicos(funcionarioAux);
    
    fflush(stdin);
    printf("\n\n Apagar o registro (s/n)???: ");
    char resp = getchar();
    
    if(resp != 's' && resp != 'S') {
        return;
    }
    
    fflush(stdin);
    funcionarioAux.ativo = '*';
    
    // recuar um registro no arquivo
    fseek(ponteiroArquivoFUNCIONARIO, -(int) sizeof(struct Funcionario), SEEK_CUR);
    // reescrever o registro;
    fwrite(&funcionarioAux, sizeof(struct Funcionario), 1, ponteiroArquivoFUNCIONARIO);
    fflush(ponteiroArquivoFUNCIONARIO); /*despejar os arquivos no disco rígido*/
    
    
    // recuar um registro no arquivo
    fseek(ponteiroArquivoFUNCIONARIO, -(int) sizeof(struct Funcionario), SEEK_CUR);
    // reescrever o registro;
    fwrite(&funcionarioAux, sizeof(struct Funcionario), 1, ponteiroArquivoFUNCIONARIO);
    fflush(ponteiroArquivoFUNCIONARIO); /*despejar os arquivos no disco rígido*/
}


// #############################################################################
// SERVICO

// #################################
// LER OS DADOS DE SERVICO
void lerDadosServico(struct Servico *servico) {
    
    fflush(stdin);
    printf("Nome   : ");
    gets(servico->nome); fflush(stdin);
    
    printf("Duracao: ");
    scanf("%d", &servico->duracao);
    
    printf("Valor  : ");
    scanf("%f", &servico->valor);
    
    if(MOSTRAR_DEBUG == 1) {
        printf("🤔 VALOR INSERIDO: %f", servico->valor);
    }
    
    servico->ativo = ' '; // Qualquer coisa menos '*' significa ativo
}

// #################################
// SALVAR DADOS DE SERVICO
// RETORNO:
//  -    0: se nao houve erros;
//  - != 0: se houve erro(s);
int salvarRegistroServico(struct Servico servico) {
    int resultado = 0;
    
    // Adicionar codigo, auto-incrementando,
    // pega o codigo do ultimo registro e incrementa.
    servico.codigo = acessarUltimoCodigoServico() + 1;
    
    // Poe o novo servico no final do arquivo.
    fseek(ponteiroArquivoSERVICO, 0L, SEEK_END);
    if(fwrite(&servico, sizeof(servico), 1, ponteiroArquivoSERVICO)!= 1) {
        if(MOSTRAR_DEBUG == 1) {
            printarMensagem("Adicionar servico: Falhou a escrita do registro");
        }
        
        resultado = 1;
    }
    
    // Retornando o valor do resultado.
    return(resultado);
}

// #################################
// BUSCAR SERVICO POR CODIGO
// Uma funçao para retornar o registro (posicao no arquivo) procurando pelo codigo.
// RETORNO:
//  - A instancia de Servico com os dados encontrados;
//  - 'servico.codigo = -1' caso nao encontre.
struct Servico buscarServicoPorCod(int codigo) {
    struct Servico servico;
    int contadorCodigo = -1;
    
    servico.codigo = -1;
    
    // Testando se o arquivo foi aberto com sucesso
    if(ponteiroArquivoSERVICO != NULL) {
        if(MOSTRAR_DEBUG == 1) {
            printf("\n\nArquivo %s foi aberto com sucesso\n\n", BIN_FUN);
        }
        
    } else {
        if(MOSTRAR_DEBUG == 1) {
            printf("\n\nERRO: O arquivo %s nao foi aberto e criado\n", BIN_FUN);
        }
        system("pause");
        exit(1);
    }
    
    rewind(ponteiroArquivoSERVICO);
    // Procura em todos os registros do documento.
    while(fread(&servico, sizeof(struct Servico), 1, ponteiroArquivoSERVICO)) {
        // Incrementa ++ porque comeca com -1.
        contadorCodigo += 1;
        
        // Compara o cod recebido.
        if(servico.codigo == codigo) {
            // Se encontrar, retorna a poisicao(linha) do registro.
            return  servico;
        }
    }
    
    // Se nao achar o codigo, retorna -1 para indicar que nao achou.
    if(MOSTRAR_DEBUG == 1) {
        printf("\n\nERRO: registro nao encontrado.");
    }
    
    return servico;
}

// #################################
// BUSCAR SERVICO POR CODIGO
// Uma funçao para retornar o registro (posicao no arquivo) procurando pelo codigo.
// RETORNO:
//  -  O numero do registro, caso encontre;
//  - -1 caso, nao encontre.
int buscarRegistroServicoPorCod(int codigo) {
    struct Servico servico;
    int contadorCodigo = -1;
    
    // Testando se o arquivo foi aberto com sucesso
    if(ponteiroArquivoSERVICO != NULL) {
        if(MOSTRAR_DEBUG == 1) {
            printf("\n\nArquivo %s foi aberto com sucesso\n\n", BIN_FUN);
        }
        
    } else {
        if(MOSTRAR_DEBUG == 1) {
            printf("\n\nERRO: O arquivo %s nao foi aberto e criado\n", BIN_FUN);
        }
        
        system ("pause");
        exit(1);
    }
    
    rewind(ponteiroArquivoSERVICO);
    // Procura em todos os registros do documento.
    while(fread(&servico, sizeof(struct Servico), 1, ponteiroArquivoSERVICO)) {
        // Incrementa ++ porque comeca com -1.
        contadorCodigo += 1;
        
        // Compara o cod recebido.
        if(servico.codigo == codigo) {
            // Se encontrar, retorna a poisicao(linha) do registro.
            return  contadorCodigo;
        }
    }
    
    // Se nao achar o codigo, retorna -1 para indicar que nao achou.
    if(MOSTRAR_DEBUG == 1) {
        printf("\n\nERRO: registro nao encontrado.");
    }
    contadorCodigo = -1;
    
    return contadorCodigo;
}

// #################################
// BUSCAR CODIGO DO ULTIMO REGISTRO
// Uma funçao para ir ate o ultimo registro, ultimo servico cadastrado e
// retorna seu respectivo codigo.
// RETORNO:
//  - O int do codigo.
int acessarUltimoCodigoServico() {
    struct Servico servico;
    
    fseek(ponteiroArquivoSERVICO, -1 * sizeof(struct Servico), SEEK_END);
    if(fread(&servico, sizeof(struct Servico), -1, ponteiroArquivoSERVICO)!= 1){
        if(MOSTRAR_DEBUG == 1) {
            printarMensagem("04 - Problemas na leitura do registro!!!");
        }
        return -1;
    }
    
    if(servico.codigo <= -1){
        return 0;
        
    } else {
        return servico.codigo;
    }
}

// #################################
// PRINTAR UM PERFIL DE SERVICO:
// mostra na tela os dados existentes no registro
void printarServicoLista(struct Servico servico) {
    //TODO: criar View de perfil SERVICO.
    
    printf("%05d|%-30s|%-3d%-7s|R$ %5.2f\n", servico.codigo, servico.nome, servico.duracao, "min", servico.valor);
}

void printarServicoTopicos(struct Servico servico) {
    
    if(servico.ativo != '*') {
        printf("%-7s: %d\n", "CODIGO", servico.codigo);
        printf("%-7s: %s\n", "NOME", servico.nome);
        
        printf("%-7s: %d\n", "DURACAO", servico.duracao);
        printf("%-7s: %f\n", "VALOR", servico.valor);
        
    } else {
        printf("\nSERVICO DELETADO!\n");
    }
}

// #################################
// LER TODOS PERFIS DE SERVICO
void printarTodosRegistrosServico() {
    struct Servico servico;
    int n_Linhas = 0;
    
    // Volta o ponteiro para o inicio.
    rewind(ponteiroArquivoSERVICO);
    
    printf("SERVICOS\n");
    interfaceLinhaSeparadoraGrande();
    printf("%-5s|%-30s|%-10s|%-10s\n", "COD", "NOME", "DURACAO", "VALOR");
    interfaceLinhaSeparadoraGrande();
    
    while(1){
        if(fread(&servico, sizeof(servico), 1, ponteiroArquivoSERVICO)!= 1)break; /*Sair do laço*/
        if(servico.ativo == '*') continue; /*Passa ao proximo*/
        printarServicoLista(servico);
        //        printarServicoTopicos(servico);
        n_Linhas++;
        if(n_Linhas%20 == 0)
            printarMensagem("Pressione <Enter> para continuar .  .  .");
    }
}

// #################################
// ALTERAR UM PERFIL DE SERVICO
// Encontra a posicao do registro pelo numero que representa a linha na qual está
// e mostra como está momento antes da alteracao, apos isso rece novos dados e atualiza.
// PARAMETRO:
//   - registro: int da 'linha' que está o referido registro.
void alterarServico(int registro) {
    struct Servico servicoAux;
    
    if(fseek(ponteiroArquivoSERVICO, (registro)*sizeof(servicoAux), SEEK_SET) != 0){
        printarMensagem("Registro inexistente ou problemas no posicionamento!!!");
        return;
    }
    
    if(fread(&servicoAux, sizeof(struct Servico), 1, ponteiroArquivoSERVICO)!= 1){
        printarMensagem("05 - Problemas na leitura do registro!!!");
        return;
    }
    
    if(servicoAux.ativo == '*'){
        printarMensagem("Um registro apagado nao pode ser alterado!!! \n\n");
        return;
    }
    
    
    printf("\n\n Dados Atuais \n\n");
    printarServicoTopicos(servicoAux);
    
    printf("\n\n Novos dados \n\n");
    lerDadosServico(&servicoAux);
    
    // recuar um registro no arquivo
    fseek(ponteiroArquivoSERVICO, -(int) sizeof(struct Servico), SEEK_CUR);
    // reescrever o registro;
    fwrite(&servicoAux, sizeof(struct Servico), 1, ponteiroArquivoSERVICO);
    fflush(ponteiroArquivoSERVICO); /*despejar os arquivos no disco rígido*/
}

// #################################
// DELETAR UM PERFIL DE SERVICO
// Encontra a posicao do registro pelo numero que representa a linha na qual está
// e apaga logicamente (deixa invisivel);
// PARAMETRO:
//   - registro: int da 'linha' que está o referido registro.
void deletarServico(int registro) {
    struct Servico servicoAux;
    
    if(fseek(ponteiroArquivoSERVICO, (registro)*sizeof(servicoAux), SEEK_SET) != 0){
        printarMensagem("Registro inexistente ou problemas no posicionamento!!!");
        return;
    }
    
    if(fread(&servicoAux, sizeof(struct Servico), 1, ponteiroArquivoSERVICO)!= 1){
        printarMensagem("06 - Problemas na leitura do registro!!!");
        return;
    }
    
    if(servicoAux.ativo == '*'){
        printarMensagem("Registro já está apagado!!!\n\n");
        return;
    }
    
    
    printf("\n\n Dados Atuais \n\n");
    printarServicoTopicos(servicoAux);
    
    fflush(stdin);
    printf("\n\n Apagar o registro (s/n)???: ");
    char resp = getchar();
    
    if(resp != 's' && resp != 'S') {
        return;
    }
    
    fflush(stdin);
    servicoAux.ativo = '*';
    
    // recuar um registro no arquivo
    fseek(ponteiroArquivoSERVICO, -(int) sizeof(struct Servico), SEEK_CUR);
    // reescrever o registro;
    fwrite(&servicoAux, sizeof(struct Servico), 1, ponteiroArquivoSERVICO);
    fflush(ponteiroArquivoSERVICO); /*despejar os arquivos no disco rígido*/
    
    
    // recuar um registro no arquivo
    fseek(ponteiroArquivoSERVICO, -(int) sizeof(struct Servico), SEEK_CUR);
    // reescrever o registro;
    fwrite(&servicoAux, sizeof(struct Servico), 1, ponteiroArquivoSERVICO);
    fflush(ponteiroArquivoSERVICO); /*despejar os arquivos no disco rígido*/
}


// #############################################################################
// FUNCOES AUXILIARES

// #################################
// Dá um system cls, limpa a tela.
void limparTela() {
    if(LIMPAR_TELA == 1) {
        system("cls");
    }
}

// #################################
// Dá um system cls, limpa a tela.
void listarCaracteresASCII() {
    int indice;
    
//    printf("%c\n\n\n\n", 187);
    
    for(indice = -255; indice <= 255; indice++) {
        printf("CHAR %3d: %-3c\t", indice, indice);
        
        if(indice % 10 == 0) {
            printf("\n");
        }
    }
}

// #################################
// Colocar uma mensagem na tela
//TODO: COLOCAR ALINHAMENTO: esq, dir, centralizado.
void printarMensagem(char *msg){
    printf("%s", msg);
}

void printarMensagemContinuar() {
    printf("%s", "\n\n Pressione <Enter> para continuar . . .");
    getchar();
}

// #################################
// FORMATAR CPF
// Por pontos e hifen. Ex.:
//    123.456.789-10
char *formatarCPF(char *cpf) {
    int i, j = 0;
    
    //Aloca o espaço necessário
    char *cpfFormatado = (char*) malloc(15 * sizeof(char));
    
    if(!cpfFormatado) {
        //Se malloc retornar nulo e porque nao há memoria suficiente para alocar o espaço necessário
        if(MOSTRAR_DEBUG == 1) {
            printarMensagem("Nao ha espaco suficiente na memoria.");
        }
        return cpfFormatado;
    }
    
    // Uma forma de acrescentar os '.' e o '-'
    //    cpfFormatado[0] = cpf[0];
    //    cpfFormatado[1] = cpf[1];
    //    cpfFormatado[2] = cpf[2];
    //    cpfFormatado[3] = '.';
    //    cpfFormatado[4] = cpf[3];
    //    cpfFormatado[5] = cpf[4];
    //    cpfFormatado[6] = cpf[5];
    //    cpfFormatado[7] = '.';
    //    cpfFormatado[8] = cpf[6];
    //    cpfFormatado[9] = cpf[7];
    //    cpfFormatado[10] = cpf[8];
    //    cpfFormatado[11] = '-';
    //    cpfFormatado[12] = cpf[9];
    //    cpfFormatado[13] = cpf[10];
    
    
    // Outra forma de acrescentar
    for(i = 0; i < 15; i++) {
        
        if(i == 3 || i == 7) {
            cpfFormatado[i] = '.';
            i++;
            
        } else if(i == 11) {
            cpfFormatado[i] = '-';
            i++;
        }
        
        cpfFormatado[i] = cpf[j];
        j++;
    }
    
    return cpfFormatado;
}

// #################################
// PEGA INT E TRANSFORMA EM STRING
char* intParaString(int val, int base){
    static char buf[32] = {0};
    int i = 30;
    
    for(; val && i ; --i, val /= base)
        buf[i] = "0123456789abcdef"[val % base];
    
    return &buf[i+1];
    
}

// #################################
// PEGA A DATA ATUAL DO SISTEMA
Data pegarDataDoSistema() {
    Data dataAtual;
    struct tm *p;
    time_t seconds;

    time(&seconds);
    p = localtime(&seconds);

    if(MOSTRAR_DEBUG == 1) {
        printf("Dia do ano: %d\n", p->tm_yday);
        printf("Data: %d/%02d/%d\n", p->tm_mday, p->tm_mon + 1, p->tm_year + 1900);
        
        printf("\nGeral: %s\n", ctime(&seconds));
    }
    
    dataAtual.dia = p->tm_mday;
    dataAtual.mes = p->tm_mon + 1;
    dataAtual.ano = p->tm_year + 1900;
    
    return dataAtual;
}

// #################################
// PEGA A HORA ATUAL DO SISTEMA
Hora pegarHoraDoSistema() {
    Hora horaAtual;
    struct tm *p;
    time_t seconds;

    time(&seconds);
    p = localtime(&seconds);

    if(MOSTRAR_DEBUG == 1) {
        printf("Dia do ano: %d\n", p->tm_yday);
        printf("Hora: %02d:%02d:%d\n", p->tm_hour, p->tm_min, p->tm_sec);
        
        printf("\nGeral: %s\n", ctime(&seconds));
    }
    
    horaAtual.segundo = p->tm_sec;
    horaAtual.minuto  = p->tm_min;
    horaAtual.hora    = p->tm_hour;
    
    return horaAtual;
}

// #################################
// VERIFICAR QUANTOS DIAS FALTAM PARA A DATA RECEBIDA
// PARAMETRO:
//   - Uma instancia de Data
// RETORNO:
//   - -1: data passada;
//   -  0: é hoje!;
//   -  1: é amanha;
//   -  2: falta dois ou mais dias.
int verificarTempoAteData(Data dataEscolhida) {
    Data dataAtual, resultado;
    
    //----------------------------------
    // Pegar a data atual.
    dataAtual = pegarDataDoSistema();
    
    //----------------------------------
    // Comparar ano.
    if(dataEscolhida.ano < dataAtual.ano) {
        return -1;
        
    } else if(dataEscolhida.ano == dataAtual.ano) {
        resultado.ano = 0;
        
    } else if(dataEscolhida.ano > dataAtual.ano) {
        resultado.ano = 1;
    }
    
    //----------------------------------
    // Comparar mes.
    if(dataEscolhida.mes < dataAtual.mes) {
        resultado.mes = -1;
        
    } else if(dataEscolhida.mes == dataAtual.mes) {
        resultado.mes = 0;
        
    } else if(dataEscolhida.mes > dataAtual.mes) {
        resultado.mes = 1;
    }
    
    //----------------------------------
    // Comparar dia.
    if(dataEscolhida.dia < dataAtual.dia) {
        resultado.dia = -1;
        
    } else if(dataEscolhida.dia == dataAtual.dia) {
        resultado.dia = 0;
        
    } else if(dataEscolhida.dia > dataAtual.dia) {
        resultado.dia = 1;
    }
    
    
    //----------------------------------
    // Se ano atual
    if(resultado.ano == 0) {
        //------------------------------
        // Se mes passado.
        if(resultado.mes == -1) {
            return -1;
        }
        
        //------------------------------
        // Se mesmo ano e mes.
        if(resultado.mes == 0) {
            // Dia passado.
            if(resultado.dia == -1) {
                return  -1;
            }
            
            //--------------------------
            // Se mesmo dia, mes, ano.
            // HOJE!
            if(resultado.dia == 0) {
                return 0;
            }
            
            //--------------------------
            // Se mesmo mes e ano, mas dia superior.
            if(resultado.dia == 1) {
                //----------------------
                // Ver se é amanha.
                if(dataEscolhida.dia == dataAtual.dia + 1) {
                    return  1;
                }
                
                //----------------------
                // 2 dias ou mais
                if(dataEscolhida.dia > dataAtual.dia + 1) {
                    return  2;
                }
            }
        }
        
        //------------------------------
        // Se mesmo ano, mas mes seguinte.
        if(resultado.mes == 1) {
            //--------------------------
            // Se dia 2 ou mais
            if(dataEscolhida.dia >= 2) {
                return 2;
            }
            
            if(dataEscolhida.dia == 1) {
                return 1;
            }
        }
    }
    
    //----------------------------------
    // Se ano seguinte
    if(resultado.ano == 1) {
        //------------------------------
        // Se pula 1 ano.
        if(dataEscolhida.ano > dataAtual.ano + 1) {
            return 2;
        }
        
        //------------------------------
        // Se ano seguinte.
        if(dataEscolhida.ano == dataAtual.ano + 1) {
            //--------------------------
            // Se primeiro dia do ano.
            if(dataEscolhida.dia == 1) {
                return 1;
            }
            
            //--------------------------
            // Se primeiro dia do ano.
            if(dataEscolhida.dia > 1) {
                return 2;
            }
        }
    }

    printarMensagem("\n\nERRO (func verificarTempoAteData): CHEGOU ONDE NAO DEVERIA\n\n");
    printf("\nDATA RESULTADO");
    printf("\nDIA: %d", resultado.dia);
    printf("\nMES: %d", resultado.mes);
    printf("\nANO: %d", resultado.ano);
    printf("\nDATA ATUAL");
    printf("\nDIA: %d", dataAtual.dia);
    printf("\nMES: %d", dataAtual.mes);
    printf("\nANO: %d", dataAtual.ano);
    printf("\nDATA ESCOLHIDA");
    printf("\nDIA: %d", dataEscolhida.dia);
    printf("\nMES: %d", dataEscolhida.mes);
    printf("\nANO: %d", dataEscolhida.ano);
    
    return -404;
}

// #################################
// VERIFICAR SE A HORA RECEBIDA ESTA DENTRO DO EXPEDIENTE DA LOJA
// PARAMETRO:
//   - Uma instancia de Hora
// RETORNO:
//   - 'n': caso esteja fora do expediente;
//   - 's': tah safe.
char verificarHoraDentroExpediente(Hora horaEscolhida) {
    char dentroExpediente = 's';
    int inicioExpediente = 8, fimExpediente = 18;
    
    if((horaEscolhida.hora < inicioExpediente) || (horaEscolhida.hora > fimExpediente)) {
        printarMensagem("\nFora do horario de funcionamento!(8h as 18h)\n");
        return 'n';
    }
    
    return dentroExpediente;
}


// #################################
// FORMATAR DATA E PRINTAR
// Por barras. Ex.:
//    01/01/2001
void printarDataFormatada(Data data) {
    printf("%02d/%02d/%d", data.dia, data.mes, data.ano);
}

// #################################
// FORMATAR DATA E RETORNAR A STRING
// Por barras. Ex.:
//    01/01/2001
char* stringDataFormatada(Data data) {
    char* resultado = (char*)calloc(11,sizeof(char));
    char diaAux[3];
    char mesAux[3];
    char anoAux[5];
    
    strcpy(resultado, "00-00-0000");
    
    strcpy(diaAux, intParaString(data.dia, 10));
    strcpy(mesAux, intParaString(data.mes, 10));
    strcpy(anoAux, intParaString(data.ano, 10));
    
    if(data.dia <= 9) {
        resultado[0] = '0';
        resultado[1] = diaAux[0];
    } else {
        resultado[0] = diaAux[0];
        resultado[1] = diaAux[1];
    }
    resultado[2] = '/';
    
    if(data.mes <= 9) {
        resultado[3] = '0';
        resultado[4] = mesAux[0];
    } else {
        resultado[3] = mesAux[0];
        resultado[4] = mesAux[1];
    }
    
    resultado[5] = '/';
    
    if(data.ano <= 9) {
        resultado[6] = '0';
        resultado[7] = mesAux[0];
        resultado[8] = mesAux[1];
        resultado[9] = mesAux[2];
    } else {
        resultado[6] = anoAux[0];
        resultado[7] = anoAux[1];
        resultado[8] = anoAux[2];
        resultado[9] = anoAux[3];
    }
    //    resultado[6] = anoAux[0];
    //    resultado[7] = anoAux[1];
    //    resultado[8] = anoAux[2];
    //    resultado[9] = anoAux[3];
    
    return resultado;
}

// #################################
// FORMATAR HORA E PRINTAR
// Por dois pontos. Ex.:
//    12:59:00
void printarHoraFormatada(Hora hora) {
    printf("%02d:%02d:%d", hora.hora, hora.minuto, hora.segundo);
}

// #################################
// FORMATAR HORA E RETORNAR A STRING
// Por dois pontos. Ex.:
//    12:59:00
char* stringHoraFormatada(Hora hora) {
    char* resultado = (char*)calloc(6,sizeof(char));
    char horaAux[3];
    char minutoAux[3];
    //    char segundoAux[3];
    
    strcpy(resultado, "00:00:00");
    
    //    strcpy(segundoAux, itoa(hora.segundo, 10));
    strcpy(minutoAux, intParaString(hora.minuto, 10));
    strcpy(horaAux, intParaString(hora.hora, 10));
    
    resultado[0] = horaAux[0];
    resultado[1] = horaAux[1];
    resultado[2] = ':';
    resultado[3] = minutoAux[0];
    resultado[4] = minutoAux[1];
    resultado[5] = '\0';
    //    resultado[6] = segundoAux[0];
    //    resultado[7] = segundoAux[1];
    
    return resultado;
}


// #############################################################################
// VALIDACOES

// #################################
// VALIDAR OPCOES PARA MENUS NUMERICOS
// PARAMETRO:
//    - min: o valor minimo que e aceito
//    - max: o valor maximo que e aceito
int receberValidarOpcaoNumero(int min, int max) {
    int opcao = min - 1;
    int contadorErros = 0;
    
    while(opcao < min || opcao > max) {
        if(contadorErros > 2) {
            printarMensagem("\nNumero invalido, informe de ");
            printf("%d a %d\n", min, max);
        }
        printf("OPCAO: ");
        scanf("%d", &opcao);
        
        contadorErros++;
    }
    
    return opcao;
}

// #################################
// VALIDAR OPCOES PARA MENUS DE LETRAS
// PARAMETRO:
//    - opcoes: 'string' com as possibilidades, as opcoes.
char receberValidarOpcaoLetra(char *opcoes) {
    int contadorErros = 0;
    int indice;
    char opcao = ' ', entradaValida = 'n';
    
    // Pegar a quantidade de caracteres digitado.
    int contadorCaracteres = (int) strlen(opcoes);
    
    while(entradaValida == 'n') {
        if(contadorErros > 2) {
            printarMensagem("\nOpcao invalida.\n");
        }
        
        printf("OPCAO: ");
        opcao = getchar(); fflush(stdin);
        
        // Passar pra minuscula.
        opcao = tolower(opcao);
        
        for(indice = 0; indice < contadorCaracteres; indice++) {
            
            if(tolower(opcoes[indice]) == opcao) {
                entradaValida = 's';
            }
        }
        
        contadorErros++;
    }
    
    return opcao;
}

// #################################
// VALIDAR CPF
// Recebe e valida a entrada de CPF.
// RETORNOS:
//    - O cpf se a entrada for valida;
//    - '*' se erro, ou entrada invalida
void receberValidarCPF(char *cpf) {
    char entradaValida = 'n';
    int indice = 0;
    int contadorErros = 0;
    
    char entrada[15];
    
    while(entradaValida == 'n') {
        
        printf("CPF: ");
        gets(entrada); fflush(stdin);
        
        // Pegar a quantidade de caracteres digitado.
        int contadorCaracteres = (int) strlen(entrada);
        
        // Checar quantidade inserida.
        if(contadorCaracteres == 11) {
            entradaValida = 's';
            
        } else {
            if(contadorErros >= 2) {
                printarMensagem("\nQuantidade de numeros incorreta.\n");
            }
            entradaValida = 'n';
        }
        
        
        // Checar se tem somente numeros.
        if(entradaValida == 's') {
            for(indice = 0; indice < contadorCaracteres; indice++){
                if(entrada[indice] < '0' || entrada[indice] > '9'){
                    if(contadorErros >= 2) {
                        printarMensagem("\nInforme apenas valores numericos.\n");
                    }
                    entradaValida = 'n';
                    break;
                }
            }
        }
        
        contadorErros++;
    }
    
    // Passar a entrada por parametro.
    if(entradaValida == 's') {
        strcpy(cpf, entrada);
    }
}

// #################################
// VALIDAR EMAIL
// Recebe e valida a entrada de EMAIL.
// RETORNOS:
//    - O email validado;
void receberValidarEmail(char *email) {
    char entradaValida = 'n';
    int indice = 0, contadorErros = 0;
    int contadorArroba = 0, contadorPonto = 0;
    char entrada[30];
    
    while(entradaValida == 'n') {
        
        printf("Email: ");
        gets(entrada); fflush(stdin);
        
        //----------------------------------
        // Pegar a quantidade de caracteres digitado.
        int contadorCaracteres = (int) strlen(entrada);
        
        //----------------------------------
        // Checar quantidade inserida.
        if(contadorCaracteres >= 5) {
            entradaValida = 's';
            
        } else {
            entradaValida = 'n';
        }
        
        //----------------------------------
        // Checar se tem '@' e '.'.
        if(entradaValida == 's') {
            contadorPonto = contadorArroba = 0;
            
            for(indice = 0; indice < contadorCaracteres; indice++){
                if(email[indice] == '@'){
                    contadorArroba++;
                }
                
                if(email[indice] == '.'){
                    contadorPonto++;
                }
            }
            
            if(contadorArroba != 1) {
                entradaValida = 'n';
            }
            
            if(contadorPonto <= 0) {
                entradaValida = 'n';
            }
        }
        
        if(contadorErros >= 2) {
            printarMensagem("\nEmail invalido.\n");
        }
        
        contadorErros++;
    }
    
    // Passar a entrada por parametro.
    if(entradaValida == 's') {
        strcpy(email, entrada);
    }
}

// #################################
// VALIDAR DATA
Data receberValidarData() {
    Data data;
    int contadorErros = 0, maxDias = 31;
    char entradaValida =  'n';
    
    data.dia = 00;
    data.mes = 00;
    data.ano = 0000;
    
    while(entradaValida != 's') {
        if(contadorErros > 2) {
            printarMensagem("\nData invalida");
        }
        
        printf("Data (dd/mm/aaaa): \n");
        scanf("%d", &data.dia);
        printf("/");
        scanf("%d", &data.mes);
        printf("/");
        scanf("%d", &data.ano);
        
        if((data.mes < 1) || (data.mes > 12)) {
            entradaValida = 'n';
            
        } else {
            entradaValida = 's';
            
            if(data.mes == 1 || data.mes == 3 || data.mes == 5 || data.mes == 7 || data.mes == 8 || data.mes == 10 || data.mes == 12) {
                maxDias = 31;
                
            } else if(data.mes == 4 || data.mes == 6 || data.mes == 9 || data.mes == 11) {
                maxDias = 30;
                
            } else {
                maxDias = 28;
                
                //TODO: Tratar ano bissexto!
            }
            
            /* Quantos dias tem cada mes
             Num     Mes         Dias
             2       Fevereiro   28 dias (29 dias nos anos bissextos)
             
             4       Abril       30 dias
             6       Junho       30 dias
             9       Setembro    30 dias
             11      Novembro    30 dias
             
             1       Janeiro     31 dias
             3       Março       31 dias
             5       Maio        31 dias
             7       Julho       31 dias
             8       Agosto      31 dias
             10      Outubro     31 dias
             12      Dezembro    31 dias
             */
            
        }
        
        //        if((agendamento.data. < 1) || (agendamento.data. > maxDias)) {
        //            entradaValida = 'n';
        //
        //        }
        contadorErros++;
    }
    
    return data;
}


// #############################################################################
// ELEMENTOS DE INTERFACE

// #################################
// LINHA SEPARADORA
void interfaceLinhaSeparadoraGrande() {
    switch(TEMA) {
        default:
            printf("-------------------------------------------------------------------------------------------------------------------------------------------------\n");
    }
}

void interfaceLinhaSeparadoraMedia() {
    switch(TEMA) {
        default:
            printf("-------------------------------------------------------------------------\n");
    }
}

void interfaceLinhaSeparadoraPequena() {
    switch(TEMA) {
        default:
            printf("------------------------------------\n");
    }
}

//tive que testa na branch de produto!! Estava funcionando perfeitamente
				COOOOOOOOOOOOOOOOOOOOOOOOOOMBOS
 
	char opcao;		
 	struct Cliente cliente;
 	printf ("Escolha um dos nossos servicos!\n "); 
	printf ("OBSERVA��O (S� PODE SER ESCOLHIDO UM COMBO DE SERVI�O POR DIA E POR PET)\n");
	printf ("A)------------------------------------------------------------------\n-Tosa e banho\n-Shampoo Banho de Carinho Petz\n-Condicionador Chegou o Brincalh�o Petz\n-Col�nia Hydra Groomers Forevers\n-Creme Hidratante de Patinhas\n-Vela Arom�tica Perfumada | Lavanda\n|VALOR: 100,00|\nB)------------------------------------------------------------------\n-Tosa e banho\n-Shampoo Pet Society Neutro\n-Condicionador Pet Society\n-Col�nia Pet Society Lovely\n-Creme hidrantante Pet Society Lovely\n-Vela Arom�tica Perfumada| Canela\n|VALOR: 90,00|\nC)------------------------------------------------------------------\n-Tosa e banho\n-Shampoo Matacura Sarnicida e Anti-Pulgas\n-Condicionador Matacura Sarnicida e Anti-Pulgas\n-Perfume Ibasa de Col�nia Affection para C�es e Gatos\n-Creme Hidratante Equil�brio Hidrapet\nVela Arom�tica Perfumada | Baunilha\n|VALOR: 80,00|\n"); 
	printf ("OPCAO:\n"); 
	scanf ("%s", &opcao); 
	fflush (stdin); 
	system ("cls"); 
	  
	switch (opcao) 
	
	{ 
	case 'A':  
	case 'a': 
	printf ("Voce escolheu o combo (A)\n-Tosa e banho\n-Shampoo Banho de Carinho Petz\n-Condicionador Chegou o Brincalh�o Petz\n-Col�nia Hydra Groomers Forevers\n-Creme Hidratante de Patinhas\n-Vela Arom�tica Perfumada | Lavanda\n|VALOR: 100,00|\n"); 
	break; 
	case 'B': 
	case 'b': 
	printf ("Voce escolheu o combo (B)\n-Tosa e banho\n-Shampoo Pet Society Neutro\n-Condicionador Pet Society\n-Col�nia Pet Society Lovely\n-Creme hidrantante Pet Society Lovely\n-Vela Arom�tica Perfumada| Canela\n|VALOR: 90,00|\n"); 
	break;
	case 'C':  
	case 'c': 
	printf ("Voce escolheu o combo (C)\n-Tosa e banho\n-Shampoo Matacura Sarnicida e Anti-Pulgas\n-Condicionador Matacura Sarnicida e Anti-Pulgas\n-Perfume Ibasa de Col�nia Affection para C�es e Gatos\n-Creme Hidratante Equil�brio Hidrapet\nVela Arom�tica Perfumada | Baunilha\n|VALOR: 80,00|\n"); 
	break; 
	default: 
	printf ("OPCAO INVALIDA"); 
	}

	
	  
	    
	    return 0;
	    
	}
	
