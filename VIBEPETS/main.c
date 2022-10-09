//
//  main.c
//  VIBEPETS
//
//  Created by Nathelia Braz on 24/09/22.
//

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>


// #############################################################################
// CONSTANTES
#define BIN_FUN "vibe_pet-persistencia_func.bin"
#define BIN_CLI "vibe_pet-persistencia_cli.bin"
#define BIN_SER "vibe_pet-persistencia_serv.bin"
#define BIN_TEL "vibe_pet-persistencia_tel.bin"
#define BIN_END "vibe_pet-persistencia_end.bin"


#define SHOW_DEBUG 1    // 1 = Mostra coisas na tela, msg de erro e etc.
#define DELETE_FILES 0  // 1 = Apaga os arquivos ao iniciar o sistema(zera o BD)

// Ponteiro para indicar o 'endereco' do arquivo a ser manipulado.
FILE *ponteiroArquivoFUN;
FILE *ponteiroArquivoCLI;
//FILE *ponteiroArquivoSER;
//FILE *ponteiroArquivoTEL;
//FILE *ponteiroArquivoEND;


// #############################################################################
// DECLARACAO DE TIPOS

struct Funcionario {
    int  codigo;
    char nome[30];
    char cpf[12];
    char senha[25];
    int  cargo;      // 0 = admin || 1 = funcionario
    char ativo;     // '*' = inativo/deletado
};

// CLIENTE
struct Cliente {
    int codigo;
    char nome[30];
    char email[30];
    char endereco[30];
    char cpf[12];
    int  nascimentoDia;
    int  nascimentoMes;
    int  nascimentoAno;
    int  telefone;
    char ativo;      // '*' = inativo/deletado
};

// #############################################################################
// PROTOTIPOS

void abrirTodosArquivos(void);
void fecharTodosArquivos(void);
void abrirArquivoCliente(void);
void abrirArquivoFuncionario(void);


void mainMenu(void);


void menuCliente(void);
void menuClienteListarTodos(void);
void menuClienteInserir(void);
void menuClienteAlterar(void);
void menuClienteDeletar(void);

int  salvarRegistroCliente(struct Cliente);
void printarMensagem(char *msg);
void printarTodosRegistrosCliente(void);
void printarClienteLista(struct Cliente);
void printarClienteTopicos(struct Cliente);
int  buscarClientePorCod(int);
void alterarCliente(int);
void printarMensagemContinuar(void);
int  acessarUltimoCodigoCliente(void);
void deletarCliente(int);
void lerDadosCliente(struct Cliente*);


void menuFuncionario(void);
void menuFuncionarioListarTodos(void);
void menuFuncionarioInserir(void);
void menuFuncionarioAlterar(void);
void menuFuncionarioDeletar(void);

int  salvarRegistroFuncionario(struct Funcionario);
void printarMensagem(char *msg);
void printarTodosRegistrosFuncionario(void);
void printarFuncionarioLista(struct Funcionario);
void printarFuncionarioTopicos(struct Funcionario);
int  buscarFuncionarioPorCod(int);
void alterarFuncionario(int);
void printarMensagemContinuar(void);
int  acessarUltimoCodigoFuncionario(void);
void deletarFuncionario(int);
void lerDadosFuncionario(struct Funcionario*);



int main(int argc, char *argv[]) {
    //    struct Funcionario funcionario;
    char opcao = 'a';
    
    
    // INICIALIZACOES
    // Cuidado, esta acao apaga todo o Banco de Dados.
    if(DELETE_FILES == 1) {
        printarMensagem("-----------------------------------------------------------\n");
        printarMensagem("DESEJA APAGAR TODOS OS REGISTROS (s/n)?\n(Acao irreversivel) ");
        fflush(stdin); opcao = getchar();
        if(opcao == 's' || opcao == 'S') {
            remove(BIN_FUN);
        }
    }
    
    abrirTodosArquivos();
    
    
    // Propriedades
    //    char opcao;
    //	struct Cliente cliente;
    
    
    
    
    
    // MENU PRINCIPAL
    mainMenu();
    
    //
    //    // Processamento
    //
    //    // Saida
    //    printf("\n\n\n\n\n\n");
    //    printf("O nome inserido: %s\n",cliente. nome);
    //    printf("O email inserido: %s\n", cliente.email);
    //    printf("O dia inserido:  %d\n", cliente.nascimentoDia);
    //    printf("O telefone inserido: %d\n", cliente.telefone);
    //    printf("O CPF inserido: %s\n", cliente.cpf);
    //    printf("O dia inserido: %i\n", cliente.nascimentoDia);
    //    printf("O mes inserido: %i\n", cliente.nascimentoMes);
    //    printf("O ano inserido: %i\n", cliente.nascimentoAno);
    //
    //    printf("Escolha os produtos que deseja da linha para o dia de Spa do seu pet\n");
    //    printf("Escolha o Shampoo para seu pet:\n");
    //    printf("A- Shampoo Pro-Banho Pelencio \nB- Shampoo Pelos Claros Pelôncio \nC- Shampoo Pelos Escuros Pelôncio \nFragrancias:	Avela - Melancia - Dove - Morango\n");
    //    printf("Opcao:\n");
    //    scanf ("%s", &opcao);
    //    fflush (stdin);
    //    system ("cls");
    //
    //    switch (opcao) {
    //        case 'A':
    //        case 'a':
    //            printf("Voce escolheu  Shampoo Pro-Banho Pelôncio\n");
    //            break;
    //        case 'B':
    //        case 'b':
    //            printf("Voc escolheu Shampoo Pelos Claros Pelôncio\n");
    //            break;
    //        case 'C':
    //        case 'c':
    //            printf("Voce escolheu Shampoo Pelos Escuros Pelôncio\n");
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
    //    system ("cls");
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
    //    system ("cls");
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
    
    
    //    if(SHOW_DEBUG == 1) {
    //        int ultimoCod = acessarUltimoCodigoFuncionario();
    //        if(ultimoCod == -1) {
    //
    //        } else {
    //            printf("\n\nULTIMO COD: %d\n\n", ultimoCod);
    //        }
    //    }
    system("pause");
    
    fecharTodosArquivos();
    
    printf("\n\n\n");
    return 0;
}




// #############################################################################
// MAIN MENU
void mainMenu() {
    char opcao = 'a';
    
    while(opcao != 'x' && opcao != 'X') {
        
        printf("\nMENU PRINCIPAL\n");
        printf("  a) MENU AGENDAMENTO\n");
        printf("  p) MENU PRODUTO\n");
        printf("  c) MENU CLIENTE\n");
        printf("  f) MENU FUNCIONARIO\n");
        printf("  x) SAIR\n");
        printf("OPCAO: ");
        //        scanf("%c", &opcao); fflush(stdin);
        opcao = getchar();
        fflush(stdin);
        
        switch(opcao) {
            case 'a':
            case 'A':
                printf("---> FAZER MENU AGENDAMENTO <--- ");
                break;
                
            case 'f':
            case 'F':
                menuFuncionario();
                break;
                
            case 'c':
            case 'C':
                printf("---> FAZER MENU CLIENTE <--- ");
                break;
                
            case 'p':
            case 'P':
                printf("---> FAZER MENU PRODUTO <--- ");
                break;
                
            case 'x':
            case 'X':
                printf("SAINDO!");
                break;
                
            default:
                printf("OPCAO INVALIDA!");
        }
    }
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
    // Abrir arquivo de Funcionarios
    ponteiroArquivoFUN = fopen(BIN_FUN, "r+b"); //tentar abrir
    
    if(ponteiroArquivoFUN == NULL){
        ponteiroArquivoFUN  = fopen(BIN_FUN, "w+b"); // criar o arquivo
        
        if(ponteiroArquivoFUN == NULL){
            if(SHOW_DEBUG == 1) {
                printf("Erro fatal: impossível abrir/criar o arquivo '%s'\n", BIN_FUN);
            }
            
            // Se chegar ate aqui, quer dizer que não conseguiu abrir de jeito nehum...
            // ai encerra o programa 🍃
            exit(1);
        }
    }
    
    // ---------------------------------
    // Abrir arquivo de Clientes
    ponteiroArquivoCLI = fopen(BIN_CLI, "r+b"); //tentar abrir
    
    if(ponteiroArquivoCLI == NULL){
        ponteiroArquivoCLI  = fopen(BIN_CLI, "w+b"); // criar o arquivo
        
        if(ponteiroArquivoCLI == NULL){
            if(SHOW_DEBUG == 1) {
                printf("Erro fatal: impossível abrir/criar o arquivo '%s'\n", BIN_CLI);
            }
            
            // Se chegar ate aqui, quer dizer que não conseguiu abrir de jeito nehum...
            // ai encerra o programa 🍃
            exit(1);
        }
    }
    
    //    #define BIN_SER "vibe_pet-persistencia_serv.bin"
    //    #define BIN_TEL "vibe_pet-persistencia_tel.bin"
    //    #define BIN_END "vibe_pet-persistencia_end.bin"
}

void abrirArquivoFuncionario() {
    ponteiroArquivoFUN = fopen(BIN_FUN, "r+b"); //tentar abrir
    
    if(ponteiroArquivoFUN == NULL){
        ponteiroArquivoFUN  = fopen(BIN_FUN, "w+b"); // criar o arquivo
        
        if(ponteiroArquivoFUN == NULL){
            if(SHOW_DEBUG == 1) {
                printf("Erro fatal: impossível abrir/criar o arquivo '%s'\n", BIN_FUN);
            }
            
            // Se chegar ate aqui, quer dizer que não conseguiu abrir de jeito nehum...
            // ai encerra o programa 🍃
            exit(1);
        }
    }
}

void abrirArquivoCliente() {
    ponteiroArquivoCLI = fopen(BIN_CLI, "r+b"); //tentar abrir
    
    if(ponteiroArquivoCLI == NULL){
        ponteiroArquivoCLI  = fopen(BIN_CLI, "w+b"); // criar o arquivo
        
        if(ponteiroArquivoCLI == NULL){
            if(SHOW_DEBUG == 1) {
                printf("Erro fatal: impossível abrir/criar o arquivo '%s'\n", BIN_CLI);
            }
            
            // Se chegar ate aqui, quer dizer que não conseguiu abrir de jeito nehum...
            // ai encerra o programa 🍃
            exit(1);
        }
    }
}


void fecharTodosArquivos() {
    
    fclose(ponteiroArquivoFUN);
    fclose(ponteiroArquivoCLI);
//    fclose(ponteiroArquivoSER);
//    fclose(ponteiroArquivoTEL);
//    fclose(ponteiroArquivoEND);
}




















// #############################################################################
// CLIENTE


// #################################
// MENU CLIENTE
void menuCliente() {
    char opcao = 'a';
    
    while(opcao != 'x' && opcao != 'X') {
        
        printf("\n MENU CLIENTE\n");
        printf("  i) INSERIR NOVO\n");
        printf("  a) ALTERAR\n");
        printf("  l) LISTAR\n");
        printf("  d) DELETAR\n");
        printf("  x) SAIR\n");
        printf("OPCAO: ");
        //        scanf("%c", &opcao); fflush(stdin);
        opcao = getchar();
        fflush(stdin);
        
        switch(opcao) {
            case 'i':
            case 'I':
                menuClienteInserir();
                break;
                
            case 'a':
            case 'A':
                menuClienteAlterar();
                break;
                
            case 'l':
            case 'L':
                menuClienteListarTodos();
                break;
                
            case 'd':
            case 'D':
                menuClienteDeletar();
                break;
                
            case 'x':
            case 'X':
                printf("SAINDO!");
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
    int codigo = 0;
    int registro = 0;
    
    printarTodosRegistrosCliente();
    
    printf("INFORME O CODIGO PARA ALTERAR: ");
    scanf("%d", &codigo);
    
    registro = buscarClientePorCod(codigo);
    deletarCliente(registro);
    printarMensagemContinuar();
}

// #################################
// LER OS DADOS DE CLIENTE
void lerDadosCliente(struct Cliente *cliente) {
    
    printf("Nome : "); fflush(stdin);
    gets(cliente->nome); fflush(stdin);
    
    printf("CPF:");
    gets(cliente->cpf); fflush(stdin);
    
    printf("Email: ");
    gets(cliente->email); fflush(stdin);
    
    printf("Endereco:");
    gets(cliente->endereco); fflush (stdin);
    
    printf("Telefone:");
    scanf("%d", &cliente->telefone); fflush (stdin);
    
    printf("DATA DE NASCIMENTO\n");
    printf("Dia: ");
    scanf("%d", &cliente->nascimentoDia);
    
    printf("Mes: ");
    scanf("%d", &cliente->nascimentoMes);
    
    printf("Ano: ");
    scanf("%d", &cliente->nascimentoAno);
    
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
    fseek(ponteiroArquivoCLI, 0L, SEEK_END);
    if(fwrite(&cliente, sizeof(cliente), 1, ponteiroArquivoCLI)!= 1) {
        if(SHOW_DEBUG == 1) {
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
    if (ponteiroArquivoCLI != NULL) {
        if(SHOW_DEBUG == 1) {
            printf("\n\nArquivo %s foi aberto com sucesso\n\n", BIN_CLI);
        }
        
    } else {
        if(SHOW_DEBUG == 1) {
            printf("\n\nERRO: O arquivo %s não foi aberto e criado\n", BIN_CLI);
        }
        system ("pause");
        exit(1);
    }
    
    rewind(ponteiroArquivoCLI);
    // Procura em todos os registros do documento.
    while(fread(&adm, sizeof(struct Cliente), 1, ponteiroArquivoCLI)) {
        // Incrementa ++ porque comeca com -1.
        codigo += 1;
        
        // Compara o cod recebido.
        if(adm.codigo == cod) {
            // Se encontrar, retorna a poisicao(linha) do registro.
            return  codigo;
        }
    }
    
    // Se não achar o codigo, retorna -1 para indicar que nao achou.
    if(SHOW_DEBUG == 1) {
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
    
    fseek(ponteiroArquivoCLI, -1 * sizeof(struct Cliente), SEEK_END);
    if(fread(&cliente, sizeof(struct Cliente), -1, ponteiroArquivoCLI)!= 1){
        if(SHOW_DEBUG == 1) {
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
    printf("%05d|%-30s|%-15s|%-30s|%-30s|%5d|%d/%d/%d\n\n", cliente.codigo, cliente.nome, cliente.cpf, cliente.email, cliente.endereco, cliente.telefone, cliente.nascimentoDia, cliente.nascimentoMes, cliente.nascimentoAno);
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
        printf("%-8s: %d\n", "TELEFONE", cliente.telefone);
        printf("%-10s: %d/%d/%d\n", "NASCIMENTO", cliente.nascimentoDia, cliente.nascimentoMes, cliente.nascimentoAno);
        
    } else {
        printf("\nCLIENTE DELETADO!\n");
    }
}

// #################################
// LER TODOS PERFIS DE CLIENTE
void printarTodosRegistrosCliente() {
    struct Cliente cliente;
    int n_Linhas = 0;
    
    // Volta o ponteiro para o inicio.
    rewind(ponteiroArquivoCLI);
    
    
        printf("%-10s: %s\n", "EMAIL", cliente.email);
        printf("%-10s: %s\n", "ENDERECO", cliente.endereco);
        printf("%-8s: %d\n", "TELEFONE", cliente.telefone);
        printf("%-10s: %d/%d/%d\n", "NASCIMENTO", cliente.nascimentoDia, cliente.nascimentoMes, cliente.nascimentoAno);
    
    
    printf("CLIENTES\n");
    printf("---------------------------------------------------------------------------------------------------------------------\n");
    printf("%-5s|%-30s|%-15s|%-30s|%-30s|%-15s|%-10s|\n", "COD", "NOME", "CPF", "EMAIL", "ENDERECO","TELEFONE", "NASC");
    printf("---------------------------------------------------------------------------------------------------------------------\n");
    
    while(1){
        if(fread(&cliente, sizeof(cliente), 1, ponteiroArquivoCLI)!= 1)break; /*Sair do laço*/
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
    
    if(fseek(ponteiroArquivoCLI, (registro)*sizeof(clienteAux), SEEK_SET) != 0){
        printarMensagem("Registro inexistente ou problemas no posicionamento!!!");
        return;
    }
    
    if(fread(&clienteAux, sizeof(struct Cliente), 1, ponteiroArquivoCLI)!= 1){
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
    fseek(ponteiroArquivoCLI, -(int) sizeof(struct Cliente), SEEK_CUR);
    // reescrever o registro;
    fwrite(&clienteAux, sizeof(struct Cliente), 1, ponteiroArquivoCLI);
    fflush(ponteiroArquivoCLI); /*despejar os arquivos no disco rígido*/
}

// #################################
// DELETAR UM PERFIL DE CLIENTE
// Encontra a posicao do registro pelo numero que representa a linha na qual está
// e apaga logicamente (deixa invisivel);
// PARAMETRO:
//   - registro: int da 'linha' que está o referido registro.
void deletarCliente(int registro) {
    struct Cliente clienteAux;
    
    if(fseek(ponteiroArquivoCLI, (registro)*sizeof(clienteAux), SEEK_SET) != 0){
        printarMensagem("Registro inexistente ou problemas no posicionamento!!!");
        return;
    }
    
    if(fread(&clienteAux, sizeof(struct Cliente), 1, ponteiroArquivoCLI)!= 1){
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
    fseek(ponteiroArquivoCLI, -(int) sizeof(struct Cliente), SEEK_CUR);
    // reescrever o registro;
    fwrite(&clienteAux, sizeof(struct Cliente), 1, ponteiroArquivoCLI);
    fflush(ponteiroArquivoCLI); /*despejar os arquivos no disco rígido*/
    
    
    // recuar um registro no arquivo
    fseek(ponteiroArquivoCLI, -(int) sizeof(struct Cliente), SEEK_CUR);
    // reescrever o registro;
    fwrite(&clienteAux, sizeof(struct Cliente), 1, ponteiroArquivoCLI);
    fflush(ponteiroArquivoCLI); /*despejar os arquivos no disco rígido*/
}


























// #############################################################################
// FUNCIONARIO


// #################################
// MENU FUNCIONARIO
void menuFuncionario() {
    char opcao = 'a';
    
    while(opcao != 'x' && opcao != 'X') {
        
        printf("\n MENU FUNCIONARIO\n");
        printf("  i) INSERIR NOVO\n");
        printf("  a) ALTERAR\n");
        printf("  l) LISTAR\n");
        printf("  d) DELETAR\n");
        printf("  x) SAIR\n");
        printf("OPCAO: ");
        //        scanf("%c", &opcao); fflush(stdin);
        opcao = getchar();
        fflush(stdin);
        
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
                printf("SAINDO!");
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
// LER OS DADOS DE FUNCIONARIO
void lerDadosFuncionario(struct Funcionario *funcionario) {
    
    fflush(stdin);
    printf("Nome : ");
    gets(funcionario->nome);
    fflush(stdin);
    
    printf("CPF  : ");
    gets(funcionario->cpf);
    fflush(stdin);
    
    printf("Senha: ");
    gets(funcionario->senha);
    fflush(stdin);
    
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
    fseek(ponteiroArquivoFUN, 0L, SEEK_END);
    if(fwrite(&funcionario, sizeof(funcionario), 1, ponteiroArquivoFUN)!= 1) {
        if(SHOW_DEBUG == 1) {
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
    if (ponteiroArquivoFUN != NULL) {
        if(SHOW_DEBUG == 1) {
            printf("\n\nArquivo %s foi aberto com sucesso\n\n", BIN_FUN);
        }
        
    } else {
        if(SHOW_DEBUG == 1) {
            printf("\n\nERRO: O arquivo %s não foi aberto e criado\n", BIN_FUN);
        }
        system ("pause");
        exit(1);
    }
    
    rewind(ponteiroArquivoFUN);
    // Procura em todos os registros do documento.
    while(fread(&adm, sizeof(struct Funcionario), 1, ponteiroArquivoFUN)) {
        // Incrementa ++ porque comeca com -1.
        codigo += 1;
        
        // Compara o cod recebido.
        if(adm.codigo == cod) {
            // Se encontrar, retorna a poisicao(linha) do registro.
            return  codigo;
        }
    }
    
    // Se não achar o codigo, retorna -1 para indicar que nao achou.
    if(SHOW_DEBUG == 1) {
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
    
    fseek(ponteiroArquivoFUN, -1 * sizeof(struct Funcionario), SEEK_END);
    if(fread(&funcionario, sizeof(struct Funcionario), -1, ponteiroArquivoFUN)!= 1){
        if(SHOW_DEBUG == 1) {
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
    rewind(ponteiroArquivoFUN);
    
    printf("FUNCIONARIOES\n");
    printf("-----------------------------------------------------------------------------------\n");
    printf("%-5s|%-30s|%-15s|%-30s\n", "COD", "NOME", "CPF", "SENHA");
    printf("-----------------------------------------------------------------------------------\n");
    
    while(1){
        if(fread(&funcionario, sizeof(funcionario), 1, ponteiroArquivoFUN)!= 1)break; /*Sair do laço*/
        if(funcionario.ativo == '*') continue; /*Passa ao próximo*/
        printarFuncionarioLista(funcionario);
        //        printarFuncionarioTopicos(funcionario);
        n_Linhas++;
        if(n_Linhas%20 == 0)
            printarMensagem("Pressione <Enter> para continuar .  .  .");
    }
    //    printf("\n\n\n");
    
}

// #################################
// ALTERAR UM PERFIL DE FUNCIONARIO
// Encontra a posicao do registro pelo numero que representa a linha na qual está
// e mostra como está momento antes da alteracao, apos isso rece novos dados e atualiza.
// PARAMETRO:
//   - registro: int da 'linha' que está o referido registro.
void alterarFuncionario(int registro) {
    struct Funcionario funcionarioAux;
    
    if(fseek(ponteiroArquivoFUN, (registro)*sizeof(funcionarioAux), SEEK_SET) != 0){
        printarMensagem("Registro inexistente ou problemas no posicionamento!!!");
        return;
    }
    
    if(fread(&funcionarioAux, sizeof(struct Funcionario), 1, ponteiroArquivoFUN)!= 1){
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
    fseek(ponteiroArquivoFUN, -(int) sizeof(struct Funcionario), SEEK_CUR);
    // reescrever o registro;
    fwrite(&funcionarioAux, sizeof(struct Funcionario), 1, ponteiroArquivoFUN);
    fflush(ponteiroArquivoFUN); /*despejar os arquivos no disco rígido*/
}

// #################################
// DELETAR UM PERFIL DE FUNCIONARIO
// Encontra a posicao do registro pelo numero que representa a linha na qual está
// e apaga logicamente (deixa invisivel);
// PARAMETRO:
//   - registro: int da 'linha' que está o referido registro.
void deletarFuncionario(int registro) {
    struct Funcionario funcionarioAux;
    
    if(fseek(ponteiroArquivoFUN, (registro)*sizeof(funcionarioAux), SEEK_SET) != 0){
        printarMensagem("Registro inexistente ou problemas no posicionamento!!!");
        return;
    }
    
    if(fread(&funcionarioAux, sizeof(struct Funcionario), 1, ponteiroArquivoFUN)!= 1){
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
    fseek(ponteiroArquivoFUN, -(int) sizeof(struct Funcionario), SEEK_CUR);
    // reescrever o registro;
    fwrite(&funcionarioAux, sizeof(struct Funcionario), 1, ponteiroArquivoFUN);
    fflush(ponteiroArquivoFUN); /*despejar os arquivos no disco rígido*/
    
    
    // recuar um registro no arquivo
    fseek(ponteiroArquivoFUN, -(int) sizeof(struct Funcionario), SEEK_CUR);
    // reescrever o registro;
    fwrite(&funcionarioAux, sizeof(struct Funcionario), 1, ponteiroArquivoFUN);
    fflush(ponteiroArquivoFUN); /*despejar os arquivos no disco rígido*/
}

























// #############################################################################
// FUNCOES AUXILIARES


/*Colocar uma mensagem na tela*/
//TODO: COLOCAR ALINHAMENTO: esq, dir, centralizado.
void printarMensagem(char *msg){
    printf("%s", msg);
}

void printarMensagemContinuar() {
    printf("%s", "\n\n Pressione <Enter> para continuar . . .");
    getchar();
}
