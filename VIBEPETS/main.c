//
//  main.c
//  VIBEPETS
//
//  Created by Nathelia Braz on 24/09/22.
//

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <ctype.h>
#include <string.h>

// #############################################################################
// CONSTANTES
#define BIN_FUN "vibe_pet-persistencia_func.bin"
#define BIN_CLI "vibe_pet-persistencia_cli.bin"
#define BIN_SER "vibe_pet-persistencia_serv.bin"
#define BIN_AGE "vibe_pet-persistencia_agend.bin"
//#define BIN_PRO "vibe_pet-persistencia_prod.bin"
//#define BIN_TEL "vibe_pet-persistencia_tel.bin"
//#define BIN_END "vibe_pet-persistencia_end.bin"

#define MOSTRAR_DEBUG 1 // 1 = Mostra coisas na tela, msg de erro e etc.
#define LIMPAR_TELA 0   // 1 = limpa a tela, habilita o clear screen system("cls").
#define LIMPAR_BD 0     // 1 = Apaga os arquivos ao iniciar o sistema(zera o BD)


// Ponteiro para indicar o 'endereco' do arquivo a ser manipulado.
FILE *ponteiroArquivoFUNCIONARIO;
FILE *ponteiroArquivoCLIENTE;
FILE *ponteiroArquivoSERVICO;
FILE *ponteiroArquivoAGENDAMENTO;
//FILE *ponteiroArquivoPRODUTO;
//FILE *ponteiroArquivoTELEFONE;
//FILE *ponteiroArquivoENDERECO;


// #############################################################################
// DECLARACAO DE TIPOS

// 'typedef' é uma outra forma de declarar um novo tipo de struct.
// Serve para criar um "apelido" a struct, para quando for declarar uma variável
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
// Hora
typedef struct {
//    int codigo;
    int segundo;
    int minuto;
    int hora;
} Hora;

// #################################
// telefone
typedef struct {
//    int codigo;
    int numero;
    int ddd;
    char temWhatsApp;   // 1 = se o número tem WhatApp.
} Telefone;

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
// Servico
struct Servico {
    int   codigo;
    char  nome[30];
    int   duracao;
    float valor;
    char  ativo;     // '*' = inativo/deletado
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


// #############################################################################
// PROTOTIPOS

// #################################
// ARQUIVOS
void abrirTodosArquivos(void);
void abrirArquivoCliente(void);
void abrirArquivoFuncionario(void);
void abrirArquivoServico(void);
void abrirArquivoAgendamento(void);

void fecharTodosArquivos(void);
void fecharArquivoCliente(void);
void fecharArquivoFuncionario(void);
void fecharArquivoServico(void);
void fecharArquivoAgendamento(void);


// #################################
// MENUS
void menuPrincipal(void);

void menuAgendamento(void);
void menuAgendamentoListarTodos(void);
void menuAgendamentoInserir(void);
void menuAgendamentoAlterar(void);
void menuAgendamentoDeletar(void);

void menuServico(void);
void menuServicoListarTodos(void);
void menuServicoInserir(void);
void menuServicoAlterar(void);
void menuServicoDeletar(void);

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


// #################################
// FUNCOES CRUD
int  salvarRegistroAgendamento(struct Agendamento);
void printarTodosRegistrosAgendamento(void);
void printarAgendamentoLista(struct Agendamento);
void printarAgendamentoTopicos(struct Agendamento);
int  buscarAgendamentoPorCod(int);
void alterarAgendamento(int);
int  acessarUltimoCodigoAgendamento(void);
void deletarAgendamento(int);
void lerDadosAgendamento(struct Agendamento*);

int  salvarRegistroServico(struct Servico);
void printarTodosRegistrosServico(void);
void printarServicoLista(struct Servico);
void printarServicoTopicos(struct Servico);
int  buscarServicoPorCod(int);
void alterarServico(int);
int  acessarUltimoCodigoServico(void);
void deletarServico(int);
void lerDadosServico(struct Servico*);

void printarCabecalhoTodosClientes(void);
int  salvarRegistroCliente(struct Cliente);
void printarTodosRegistrosCliente(void);
void printarClienteLista(struct Cliente);
void printarClienteTopicos(struct Cliente);
int  buscarClientePorCod(int);
void alterarCliente(int);
int  acessarUltimoCodigoCliente(void);
void deletarCliente(int);
void lerDadosCliente(struct Cliente*);

int  salvarRegistroFuncionario(struct Funcionario);
void printarTodosRegistrosFuncionario(void);
void printarFuncionarioLista(struct Funcionario);
void printarFuncionarioTopicos(struct Funcionario);
int  buscarFuncionarioPorCod(int);
void alterarFuncionario(int);
int  acessarUltimoCodigoFuncionario(void);
void deletarFuncionario(int);
void lerDadosFuncionario(struct Funcionario*);


// #################################
// FUNCOES AUXILIARES
void printarMensagem(char *msg);
void printarMensagemContinuar(void);
char* formatarCPF(char[]);
void limparTela(void);

// #################################
// VALIDACOES
void receberValidarCPF(char*);
int  receberValidarOpcaoNumero(int, int);
char receberValidarOpcaoLetra(char*);


int main(int argc, char *argv[]) {
    //    struct Funcionario funcionario;
    char opcao = 'a';
    
    // INICIALIZACOES
    // Cuidado, esta acao apaga todo o Banco de Dados.
    if(LIMPAR_BD == 1) {
        printarMensagem("-----------------------------------------------------------\n");
        printarMensagem("DESEJA APAGAR TODOS OS REGISTROS (s/n)?\n(Acao irreversivel) ");
        fflush(stdin); opcao = getchar();
        if(opcao == 's' || opcao == 'S') {
            remove(BIN_FUN);
        }
    }
    abrirTodosArquivos();

    // MENU PRINCIPAL
    menuPrincipal();
    
    // Propriedades
    //    char opcao;
    //	struct Cliente cliente;
    //
    //    printf("Escolha os produtos que deseja da linha para o dia de Spa do seu pet\n");
    //    printf("Escolha o Shampoo para seu pet:\n");
    //    printf("A- Shampoo Pro-Banho Pelencio \nB- Shampoo Pelos Claros Peloncio \nC- Shampoo Pelos Escuros Peloncio \nFragrancias:	Avela - Melancia - Dove - Morango\n");
    //    printf("Opcao:\n");
    //    scanf ("%s", &opcao);
    //    fflush (stdin);
    //    sho
    //
    //    switch (opcao) {
    //        case 'A':
    //        case 'a':
    //            printf("Voce escolheu  Shampoo Pro-Banho Peloncio\n");
    //            break;
    //        case 'B':
    //        case 'b':
    //            printf("Voc escolheu Shampoo Pelos Claros Peloncio\n");
    //            break;
    //        case 'C':
    //        case 'c':
    //            printf("Voce escolheu Shampoo Pelos Escuros Peloncio\n");
    //            break;
    //        default:
    //            printf("Opcao invalida");
    //    }
    //
    //    printf("Escolha a fragrancia do Condicionador para seu pet:\n");
    //    printf("A-Avela \nB- Melancia \nC- Morango\n");
    //    printf("Opcao:\n");
    //    scanf ("%c", &opcao);
    //    fflush (stdin);
    //    limparTela();
    //
    //    switch (opcao) {
    //        case 'A':
    //        case 'a':
    //            printf("Voce escolheu Avela\n");
    //            break;
    //        case 'B':
    //        case 'b':
    //            printf("Voce escolheu Melancia\n");
    //            break;
    //        case 'C':
    //        case 'c':
    //            printf("Voce escolheu Morango\n");
    //            break;
    //        default:
    //
    //            printf("Opcao invalida");
    //    }
    //    printf("Escolha a colonia Perfume Pet Clean Max para seu pet:\n");
    //    printf("A-  Amendoas e Ameixa \nB- Avela e Cereja \nC- Melancia\n");
    //    printf("Opcao:\n");
    //    scanf ("%c", &opcao);
    //    fflush (stdin);
    //    limparTela();
    //
    //    switch (opcao)
    //    {
    //        case 'A':
    //        case 'a':
    //            printf("Voce escolheu Amendoas e Ameixa\n");
    //            break;
    //        case 'B':
    //        case 'b':
    //            printf("Voce escolheu Avela e Cereja\n");
    //            break;
    //        case 'C':
    //        case 'c':
    //            printf("Voce escolheu Melancia\n");
    //            break;
    //        default:
    //            printf("Opcao invalida");
    //    }
    
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
    
    registro = buscarAgendamentoPorCod(codigo);
    alterarAgendamento(registro);
    
    printarMensagemContinuar();
}

void menuAgendamentoDeletar() {
    int codigo   = 0;
    int registro = 0;
    
    printarTodosRegistrosAgendamento();
    
    printf("INFORME O CODIGO PARA ALTERAR: ");
    scanf("%d", &codigo);
    
    registro = buscarAgendamentoPorCod(codigo);
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
    
    registro = buscarClientePorCod(codigo);
    alterarCliente(registro);
    
    printarMensagemContinuar();
}

void menuClienteDeletar() {
    int codigo   = 0;
    int registro = 0;
    
    printarTodosRegistrosCliente();
    
    printf("INFORME O CODIGO PARA ALTERAR: ");
    scanf("%d", &codigo);
    
    registro = buscarClientePorCod(codigo);
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
    
    registro = buscarFuncionarioPorCod(codigo);
    alterarFuncionario(registro);
    
    printarMensagemContinuar();
}

void menuFuncionarioDeletar() {
    int codigo = 0;
    int registro = 0;
    
    printarTodosRegistrosFuncionario();
    
    printf("INFORME O CODIGO PARA ALTERAR: ");
    scanf("%d", &codigo);
    
    registro = buscarFuncionarioPorCod(codigo);
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
    
    registro = buscarServicoPorCod(codigo);
    alterarServico(registro);
    
    printarMensagemContinuar();
}

void menuServicoDeletar() {
    int codigo = 0;
    int registro = 0;
    
    printarTodosRegistrosServico();
    
    printf("INFORME O CODIGO PARA ALTERAR: ");
    scanf("%d", &codigo);
    
    registro = buscarServicoPorCod(codigo);
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
// Verifica se o arquivo já existe. Se não existir, ele é criado
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
            
            // Se chegar ate aqui, quer dizer que não conseguiu abrir de jeito neNhum...
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
            
            // Se chegar ate aqui, quer dizer que não conseguiu abrir de jeito neNhum...
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
            
            // Se chegar ate aqui, quer dizer que não conseguiu abrir de jeito neNhum...
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
            
            // Se chegar ate aqui, quer dizer que não conseguiu abrir de jeito neNhum...
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
            
            // Se chegar ate aqui, quer dizer que não conseguiu abrir de jeito neNhum...
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
            
            // Se chegar ate aqui, quer dizer que não conseguiu abrir de jeito neNhum...
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
            
            // Se chegar ate aqui, quer dizer que não conseguiu abrir de jeito neNhum...
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
            
            // Se chegar ate aqui, quer dizer que não conseguiu abrir de jeito neNhum...
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
    fflush(ponteiroArquivoSERVICO);
    fflush(ponteiroArquivoCLIENTE);
    fflush(ponteiroArquivoFUNCIONARIO);
//    fflush(ponteiroArquivoTELEFONE);
//    fflush(ponteiroArquivoENDERECO);
    
    // Fechar os arquivos.
    fclose(ponteiroArquivoAGENDAMENTO);
    fclose(ponteiroArquivoSERVICO);
    fclose(ponteiroArquivoCLIENTE);
    fclose(ponteiroArquivoFUNCIONARIO);
//    fclose(ponteiroArquivoTELEFONE);
//    fclose(ponteiroArquivoENDERECO);
}

void fecharArquivoAgendamento() {
    // Atualizar o arquivo.
    fflush(ponteiroArquivoAGENDAMENTO);
    
    // Fechar o arquivo.
    fclose(ponteiroArquivoAGENDAMENTO);
}

void fecharArquivoServico() {
    // Atualizar o arquivo.
    fflush(ponteiroArquivoSERVICO);
    
    // Fechar o arquivo.
    fclose(ponteiroArquivoSERVICO);
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













// #############################################################################
// AGENDAMENTO

// #################################
// LER OS DADOS DE AGENDAMENTO
void lerDadosAgendamento(struct Agendamento *agendamento) {
    
    fflush(stdin);
    printf("Data (xx/xx/2022) : ");
    scanf("%d/%d/%d", agendamento->data.dia, agendamento->data.mes, agendamento->data.ano);
    
//    printf("CPF  : ");
//    gets(agendamento->cpf); fflush(stdin);
    //TODO: Testar depois
    receberValidarCPF(agendamento->cpf);
    
    printf("Senha: ");
    gets(agendamento->senha); fflush(stdin);
    
    printf("Cargo: ");
    scanf("%d", &agendamento->cargo); // Agendamento 0 = adm
    fflush(stdin);
    
    agendamento->ativo = ' '; // Qualquer coisa menos '*' significa ativo
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
// Uma função para retornar o registro (posicao no arquivo) procurando pelo código.
// RETORNO:
//  -  O numero do registro, caso encontre;
//  - -1 caso, nao encontre.
int buscarAgendamentoPorCod(int cod) {
    struct Agendamento adm;
    int codigo = -1;
    
    // Testando se o arquivo foi aberto com sucesso
    if (ponteiroArquivoAGENDAMENTO != NULL) {
        if(MOSTRAR_DEBUG == 1) {
            printf("\n\nArquivo %s foi aberto com sucesso\n\n", BIN_FUN);
        }
        
    } else {
        if(MOSTRAR_DEBUG == 1) {
            printf("\n\nERRO: O arquivo %s não foi aberto e criado\n", BIN_FUN);
        }
        system ("pause");
        exit(1);
    }
    
    rewind(ponteiroArquivoAGENDAMENTO);
    // Procura em todos os registros do documento.
    while(fread(&adm, sizeof(struct Agendamento), 1, ponteiroArquivoAGENDAMENTO)) {
        // Incrementa ++ porque comeca com -1.
        codigo += 1;
        
        // Compara o cod recebido.
        if(adm.codigo == cod) {
            // Se encontrar, retorna a poisicao(linha) do registro.
            return  codigo;
        }
    }
    
    // Se não achar o codigo, retorna -1 para indicar que nao achou.
    if(MOSTRAR_DEBUG == 1) {
        printf("\n\nERRO: registro nao encontrado.");
    }
    codigo = -1;
    
    return codigo;
}

// #################################
// BUSCAR CODIGO DO ULTIMO REGISTRO
// Uma função para ir ate o ultimo registro, ultimo agendamento cadastrado e
// retorna seu respectivo codigo.
// RETORNO:
//  - O int do codigo.
int acessarUltimoCodigoAgendamento() {
    struct Agendamento agendamento;
    
    fseek(ponteiroArquivoAGENDAMENTO, -1 * sizeof(struct Agendamento), SEEK_END);
    if(fread(&agendamento, sizeof(struct Agendamento), -1, ponteiroArquivoAGENDAMENTO)!= 1){
        if(MOSTRAR_DEBUG == 1) {
            printarMensagem("Problemas na leitura do registro!!!");
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
// PRINTAR UM PERFIL DE AGENDAMENTO:
// mostra na tela os dados existentes no registro
void printarAgendamentoLista(struct Agendamento agendamento) {
    //TODO: criar View de perfil AGENDAMENTO.
    
    //    printf("-----------------------------------------------------------------------------------\n");
    printf("%05d|%-30s|%-15s|%-30s\n", agendamento.codigo, agendamento.nome, agendamento.cpf, agendamento.senha);
    //    printf("-----------------------------------------------------------------------------------\n");
}

void printarAgendamentoTopicos(struct Agendamento agendamento) {
    
    if(agendamento.ativo == ' ') {
        printf("%-6s: %d\n", "CODIGO", agendamento.codigo);
        printf("%-6s: %s\n", "NOME", agendamento.nome);
        printf("%-6s: %s\n", "CPF", agendamento.cpf);
        printf("%-6s: %s\n", "SENHA", agendamento.senha);
        if(agendamento.cargo == 1) {
            printf("%-6s: %s\n", "CARGO", "Agendamento");
            
        } else if(agendamento.cargo == 0) {
            printf("%-6s: %s\n", "CARGO", "Agendamento");
        }
        
    } else {
        printf("\nAGENDAMENTO DELETADO!\n");
    }
}

// #################################
// LER TODOS PERFIS DE AGENDAMENTO
void printarTodosRegistrosAgendamento() {
    struct Agendamento agendamento;
    int n_Linhas = 0;
    
    // Volta o ponteiro para o inicio.
    rewind(ponteiroArquivoAGENDAMENTO);
    
    printf("AGENDAMENTOS\n");
    printf("-----------------------------------------------------------------------------------\n");
    printf("%-5s|%-30s|%-15s|%-30s\n", "COD", "NOME", "CPF", "SENHA");
    printf("-----------------------------------------------------------------------------------\n");
    
    while(1){
        if(fread(&agendamento, sizeof(agendamento), 1, ponteiroArquivoAGENDAMENTO)!= 1)break; /*Sair do laço*/
        if(agendamento.ativo == '*') continue; /*Passa ao próximo*/
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
        printarMensagem("Problemas na leitura do registro!!!");
        return;
    }
    
    if(agendamentoAux.ativo == '*'){
        printarMensagem("Um registro apagado não pode ser alterado!!! \n\n");
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
        printarMensagem("Problemas na leitura do registro!!!");
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
    
    printf("🤔 VALOR INSERIDO: %f", servico->valor);
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
// Uma função para retornar o registro (posicao no arquivo) procurando pelo código.
// RETORNO:
//  -  O numero do registro, caso encontre;
//  - -1 caso, nao encontre.
int buscarServicoPorCod(int cod) {
    struct Servico adm;
    int codigo = -1;
    
    // Testando se o arquivo foi aberto com sucesso
    if (ponteiroArquivoSERVICO != NULL) {
        if(MOSTRAR_DEBUG == 1) {
            printf("\n\nArquivo %s foi aberto com sucesso\n\n", BIN_FUN);
        }
        
    } else {
        if(MOSTRAR_DEBUG == 1) {
            printf("\n\nERRO: O arquivo %s não foi aberto e criado\n", BIN_FUN);
        }
        system ("pause");
        exit(1);
    }
    
    rewind(ponteiroArquivoSERVICO);
    // Procura em todos os registros do documento.
    while(fread(&adm, sizeof(struct Servico), 1, ponteiroArquivoSERVICO)) {
        // Incrementa ++ porque comeca com -1.
        codigo += 1;
        
        // Compara o cod recebido.
        if(adm.codigo == cod) {
            // Se encontrar, retorna a poisicao(linha) do registro.
            return  codigo;
        }
    }
    
    // Se não achar o codigo, retorna -1 para indicar que nao achou.
    if(MOSTRAR_DEBUG == 1) {
        printf("\n\nERRO: registro nao encontrado.");
    }
    codigo = -1;
    
    return codigo;
}

// #################################
// BUSCAR CODIGO DO ULTIMO REGISTRO
// Uma função para ir ate o ultimo registro, ultimo servico cadastrado e
// retorna seu respectivo codigo.
// RETORNO:
//  - O int do codigo.
int acessarUltimoCodigoServico() {
    struct Servico servico;
    
    fseek(ponteiroArquivoSERVICO, -1 * sizeof(struct Servico), SEEK_END);
    if(fread(&servico, sizeof(struct Servico), -1, ponteiroArquivoSERVICO)!= 1){
        if(MOSTRAR_DEBUG == 1) {
            printarMensagem("Problemas na leitura do registro!!!");
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
    
    printf("%05d|%-30s|%5d min |R$ %5.2f\n", servico.codigo, servico.nome, servico.duracao, servico.valor);
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
    printf("-----------------------------------------------------------------------------------\n");
    printf("%-5s|%-30s|%-10s|%-10s\n", "COD", "NOME", "DURACAO", "VALOR");
    printf("-----------------------------------------------------------------------------------\n");
    
    while(1){
        if(fread(&servico, sizeof(servico), 1, ponteiroArquivoSERVICO)!= 1)break; /*Sair do laço*/
        if(servico.ativo == '*') continue; /*Passa ao próximo*/
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
        printarMensagem("Problemas na leitura do registro!!!");
        return;
    }
    
    if(servicoAux.ativo == '*'){
        printarMensagem("Um registro apagado não pode ser alterado!!! \n\n");
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
        printarMensagem("Problemas na leitura do registro!!!");
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
    
    printf("Email: ");
    gets(cliente->email); fflush(stdin);
    
    printf("Endereco:");
    gets(cliente->endereco); fflush (stdin);
    
    printf("Telefone:");
    scanf("%d", &cliente->telefone); fflush (stdin);
    
    printf("DATA DE NASCIMENTO\n");
    printf("Dia: ");
    scanf("%d", &cliente->nascimento.dia);
    
    printf("Mes: ");
    scanf("%d", &cliente->nascimento.mes);
    
    printf("Ano: ");
    scanf("%d", &cliente->nascimento.ano);
    
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
// Uma função para retornar o registro (posicao no arquivo) procurando pelo código.
// RETORNO:
//  -  O numero do registro, caso encontre;
//  - -1 caso, nao encontre.
int buscarClientePorCod(int cod) {
    struct Cliente adm;
    int codigo = -1;
    
    // Testando se o arquivo foi aberto com sucesso
    if (ponteiroArquivoCLIENTE != NULL) {
        if(MOSTRAR_DEBUG == 1) {
            printf("\n\nArquivo %s foi aberto com sucesso\n\n", BIN_CLI);
        }
        
    } else {
        if(MOSTRAR_DEBUG == 1) {
            printf("\n\nERRO: O arquivo %s não foi aberto e criado\n", BIN_CLI);
        }
        system ("pause");
        exit(1);
    }
    
    rewind(ponteiroArquivoCLIENTE);
    // Procura em todos os registros do documento.
    while(fread(&adm, sizeof(struct Cliente), 1, ponteiroArquivoCLIENTE)) {
        // Incrementa ++ porque comeca com -1.
        codigo += 1;
        
        // Compara o cod recebido.
        if(adm.codigo == cod) {
            // Se encontrar, retorna a poisicao(linha) do registro.
            return  codigo;
        }
    }
    
    // Se não achar o codigo, retorna -1 para indicar que nao achou.
    if(MOSTRAR_DEBUG == 1) {
        printf("\n\nERRO: registro nao encontrado.");
    }
    codigo = -1;
    
    return codigo;
}

// #################################
// BUSCAR CODIGO DO ULTIMO REGISTRO
// Uma função para ir ate o ultimo registro, ultimo cliente cadastrado e
// retorna seu respectivo codigo.
// RETORNO:
//  - O int do codigo.
int acessarUltimoCodigoCliente() {
    struct Cliente cliente;
    
    fseek(ponteiroArquivoCLIENTE, -1 * sizeof(struct Cliente), SEEK_END);
    if(fread(&cliente, sizeof(struct Cliente), -1, ponteiroArquivoCLIENTE)!= 1){
        if(MOSTRAR_DEBUG == 1) {
            printarMensagem("Problemas na leitura do registro!!!");
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
    
    //    printf("-----------------------------------------------------------------------------------\n");
    printf("%05d|%-30s|%-15s|%-30s|%-30s|%-15d|%02d/%02d/%d\n", cliente.codigo, cliente.nome, cliente.cpf, cliente.email, cliente.endereco, cliente.telefone, cliente.nascimento.dia, cliente.nascimento.mes, cliente.nascimento.ano);
    //    printf("-----------------------------------------------------------------------------------\n");
}

void printarClienteTopicos(struct Cliente cliente) {
    
    printf("%-8s: %d\n", "", cliente.codigo);
    
    if(cliente.ativo != '*') {
        printf("%-10s: %d\n", "CODIGO", cliente.codigo);
        printf("%-10s: %s\n", "NOME", cliente.nome);
        printf("%-10s: %s\n", "CPF", cliente.cpf);
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
    printf("----------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("%-5s|%-30s|%-15s|%-30s|%-30s|%-15s|%-10s|\n", "COD", "NOME", "CPF", "EMAIL", "ENDERECO","TELEFONE", "NASC");
    printf("----------------------------------------------------------------------------------------------------------------------------------------------\n");
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
        if(cliente.ativo == '*') continue; /*Passa ao próximo*/
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
        printarMensagem("Problemas na leitura do registro!!!");
        return;
    }
    
    if(clienteAux.ativo == '*'){
        printarMensagem("Um registro apagado não pode ser alterado!!! \n\n");
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
        printarMensagem("Problemas na leitura do registro!!!");
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
// Uma função para retornar o registro (posicao no arquivo) procurando pelo código.
// RETORNO:
//  -  O numero do registro, caso encontre;
//  - -1 caso, nao encontre.
int buscarFuncionarioPorCod(int cod) {
    struct Funcionario adm;
    int codigo = -1;
    
    // Testando se o arquivo foi aberto com sucesso
    if (ponteiroArquivoFUNCIONARIO != NULL) {
        if(MOSTRAR_DEBUG == 1) {
            printf("\n\nArquivo %s foi aberto com sucesso\n\n", BIN_FUN);
        }
        
    } else {
        if(MOSTRAR_DEBUG == 1) {
            printf("\n\nERRO: O arquivo %s não foi aberto e criado\n", BIN_FUN);
        }
        system ("pause");
        exit(1);
    }
    
    rewind(ponteiroArquivoFUNCIONARIO);
    // Procura em todos os registros do documento.
    while(fread(&adm, sizeof(struct Funcionario), 1, ponteiroArquivoFUNCIONARIO)) {
        // Incrementa ++ porque comeca com -1.
        codigo += 1;
        
        // Compara o cod recebido.
        if(adm.codigo == cod) {
            // Se encontrar, retorna a poisicao(linha) do registro.
            return  codigo;
        }
    }
    
    // Se não achar o codigo, retorna -1 para indicar que nao achou.
    if(MOSTRAR_DEBUG == 1) {
        printf("\n\nERRO: registro nao encontrado.");
    }
    codigo = -1;
    
    return codigo;
}

// #################################
// BUSCAR CODIGO DO ULTIMO REGISTRO
// Uma função para ir ate o ultimo registro, ultimo funcionario cadastrado e
// retorna seu respectivo codigo.
// RETORNO:
//  - O int do codigo.
int acessarUltimoCodigoFuncionario() {
    struct Funcionario funcionario;
    
    fseek(ponteiroArquivoFUNCIONARIO, -1 * sizeof(struct Funcionario), SEEK_END);
    if(fread(&funcionario, sizeof(struct Funcionario), -1, ponteiroArquivoFUNCIONARIO)!= 1){
        if(MOSTRAR_DEBUG == 1) {
            printarMensagem("Problemas na leitura do registro!!!");
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
    
    //    printf("-----------------------------------------------------------------------------------\n");
    printf("%05d|%-30s|%-15s|%-30s\n", funcionario.codigo, funcionario.nome, funcionario.cpf, funcionario.senha);
    //    printf("-----------------------------------------------------------------------------------\n");
}

void printarFuncionarioTopicos(struct Funcionario funcionario) {
    
    if(funcionario.ativo == ' ') {
        printf("%-6s: %d\n", "CODIGO", funcionario.codigo);
        printf("%-6s: %s\n", "NOME", funcionario.nome);
        printf("%-6s: %s\n", "CPF", funcionario.cpf);
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
    printf("-----------------------------------------------------------------------------------\n");
    printf("%-5s|%-30s|%-15s|%-30s\n", "COD", "NOME", "CPF", "SENHA");
    printf("-----------------------------------------------------------------------------------\n");
    
    while(1){
        if(fread(&funcionario, sizeof(funcionario), 1, ponteiroArquivoFUNCIONARIO)!= 1)break; /*Sair do laço*/
        if(funcionario.ativo == '*') continue; /*Passa ao próximo*/
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
        printarMensagem("Problemas na leitura do registro!!!");
        return;
    }
    
    if(funcionarioAux.ativo == '*'){
        printarMensagem("Um registro apagado não pode ser alterado!!! \n\n");
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
        printarMensagem("Problemas na leitura do registro!!!");
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
// FUNCOES AUXILIARES

// Dá um system cls, limpa a tela.
void limparTela() {
    if(LIMPAR_TELA == 1) {
        system("cls");
    }
}


/*Colocar uma mensagem na tela*/
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
    
    if (!cpfFormatado) {
        //Se malloc retornar nulo é porque não há memória suficiente para alocar o espaço necessário
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










// #############################################################################
// VALIDACOES

// #################################
// VALIDAR CPF
// Recebe e valida a entrade de CPF.
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
// VALIDAR OPCOES PARA MENUS NUMERICOS
// PARAMETRO:
//    - min: o valor minimo que e aceito
//    - max: o valor maximo que e aceito
Data receberValidarData() {
    Data data;
    int contadorErros = 0, maxDias = 31;
    char entradaValida =  'n';
    
    
    
    
    while(entradaValida != 's') {
        if(contadorErros > 2) {
            printarMensagem("\nData invalida, informe de ");
            printf("%d a %d\n", min, max);
        }
        
        printf("Data (xx/xx/2022): \n");
        scanf("%d", agendamento.data.dia);
        printf("/");
        scanf("%d", agendamento.data.mes);
        printf("/");
        scanf("%d", agendamento.data.ano);
        
        if((agendamento.data.mes < 1) || (agendamento.data.mes > 12)) {
            entradaValida = 'n';
            
        } else {
            entradaValida = 's';
            
            if (agendamento.data.mes == 1 || agendamento.data.mes == 3 || agendamento.data.mes == 5 || agendamento.data.mes == 7 || agendamento.data.mes == 8 || agendamento.data.mes == 10 || agendamento.data.mes == 12) {
                maxDias = 31;
                
            } else if(agendamento.data.mes == 4 || agendamento.data.mes == 6 || agendamento.data.mes == 9 || agendamento.data.mes == 11) {
                maxDias = 30;

            } else {
                maxDias = 28;
                
                //TODO: Tratar ano bissexto!
            }
            
/*
Ordem dos meses    Mês    Dias
2       Fevereiro  tem 28 dias (29 dias nos anos bissextos)

4       Abril      tem 30 dias
6       Junho      tem 30 dias
9       Setembro   tem 30 dias
11      Novembro   tem 30 dias
 
1       Janeiro    tem 31 dias
3       Março      tem 31 dias
5       Maio       tem 31 dias
7       Julho      tem 31 dias
8       Agosto     tem 31 dias
10      Outubro    tem 31 dias
12      Dezembro   tem 31 dias
*/
            
        }
        
        if((agendamento.data. < 1) || (agendamento.data. > maxDias)) {
            entradaValida = 'n';

        }
        contadorErros++;
    }
    
    return data;
}

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

if(/*alguma condição*/)
{
//algum codigo
} 

if(contadorErros > 2) {
    printarMensagem("\nNumero invalido, informe de ");
    printf("%d a %d\n", min, max);
}
