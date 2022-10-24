//
//  main.c
//  VIBEPETS
//
//  Created by Nathalia Braz on 24/09/22.
//

//#include "main.h"
#include "Headers/main.h"

int main(int argc, char *argv[]) {
    // Propriedades
    struct Funcionario login;
    char opcao = 'a';
    //    char nome[50], email[50];
    //    int  dia, mes, ano, endereco, cpf, tel;
    
    //Entradas do sistema de login
    char senha[50];
    int codigo = -1, j = 0, logado = 1;
    
    login.codigo = -1;
    
    abrirTodosArquivos();
    
    while (logado == 1){
        while(codigo <= -1) {
            printf("Digite o seu codigo: ");
            scanf("%d", &codigo);
            login.codigo = codigo;
            
            if(codigo == 0) {
                if(MOSTRAR_DEBUG == 1) {
                    printarMensagem("\nCODIGO ADMINISTRADOR!");
                }
                login.codigo = 0;
                strcpy(senha, "admin123");
                strcpy(login.senha, "admin123");
                logado = 0;
                
            } else if(codigo >= 1) {
                login = buscarFuncionarioPorCod(codigo, MOSTRAR_DEBUG);
                                
                if(login.codigo <= -1) {
                    if(MOSTRAR_DEBUG == 1) {
                        printarMensagem("\nCODIGO INVALIDO!");
                    }
                    logado = 1;

                } else {
                    logado = 0;
                }
            } else {
                logado = 1;
            }
        }
        
        if(login.codigo >= 0) {
            
            printf("Digite sua senha: ");
            //        while((getc(c)) != '13') {
            fflush(stdin); gets(senha);
            j = 0;
            
            // Checa se o login está certo
            if(login.codigo == 0) {
                if(strcmp(senha, "admin123") == 0){
                    logado = 0;
                } else {
                    logado = 1;
                }
                
            } else {
                if(strcmp(senha, login.senha) == 0){
                    logado = 0;
                    
                } else {
                    logado = 1;
                }
            }
            
            if(logado == 0){
                printf("\n\nLogin autorizado!");
                if(login.codigo == 0) {
                    printf("\nSeja bem vindo(a) ADMINISTRADOR.\n\n");
                } else {
                    printf("\nSeja bem vindo(a) %s.\n\n", login.nome);
                }
                
            } else{
                printf("Login não autorizado! Usuário ou senha estão incorretos!");
                printf("\nTente novamente.\n");
                logado = 1;
            }
        } else {
            logado = 1;
        }
    }
    
    if(logado == 0) {
        // INICIALIZACOES
        // Cuidado, esta acao apaga todo o Banco de Dados.
        if(LIMPAR_BD == 1) {
            interfaceLinhaSeparadora(100, TEMA);
            printarMensagem("DESEJA APAGAR TODOS OS REGISTROS (s/n)?\n(Acao irreversivel) ");
            fflush(stdin); opcao = getchar();
            if(opcao == 's' || opcao == 'S') {
                remove(BIN_FUN);
            }
        }
        
        // MENU PRINCIPAL
        menuPrincipal();
    }
    
    
    fecharTodosArquivos();
    //    mostrarQuadroHorarios();
    
    printf("\n\n\n");
    system("pause");
    
    // Saida
    /*printf("O nome digitado e: %s", nome);
     printf("O email digitado e: %s", email);*/
    //    scanf("O dia digitado foi:  %d", &dia);
    
    return 0;
}
//    struct Funcionario funcionario;
//    char opcao = 'a';
//
//    // INICIALIZACOES
//    // Cuidado, esta acao apaga todo o Banco de Dados.
//    if(LIMPAR_BD == 1) {
//        interfaceLinhaSeparadora(100, TEMA);
//        printarMensagem("----- DESEJA APAGAR TODOS OS REGISTROS (s/n)? -----\n(Acao irreversivel) ");
//        fflush(stdin); opcao = getchar();
//        if(opcao == 's' || opcao == 'S') {
//            remove(BIN_FUN);
//        }
//    }
//    abrirTodosArquivos();
//
//    // MENU PRINCIPAL
//    menuPrincipal();
//
//    fecharTodosArquivos();
////    mostrarQuadroHorarios();
//
//    printf("\n\n\n");
//    system("pause");
//
//    return 0;
//}


// #############################################################################
// MENUS
void menuPrincipal() {
    char opcao = 'a';
    
    while(opcao != 'x' && opcao != 'X') {
        limparTela(MOSTRAR_DEBUG);
        
        printf("\n --------------- MENU PRINCIPAL ---------------\n \n--------------- SELECIONE A OPCAO QUE VOCÊ DESEJA ACESSAR ---------------\n");
        printf("\tA) MENU DOS AGENDAMENTOS\n");
        printf("\tC) MENU DOS CLIENTES\n");
        printf("\tF) MENU DOS FUNCIONARIOS\n");
        //        printf("\tP) MENU PRODUTO\n");
        printf("\tS) MENU DE SERVICOS\n");
        printf("\tX) SAIR\n");
        opcao = receberValidarOpcaoLetra("acfxs"); // add p depois.
        
        switch(opcao) {
            case 'a':
                menuAgendamento(MOSTRAR_DEBUG, TEMA);
                break;
                
            case 'c':
                menuCliente(MOSTRAR_DEBUG, TEMA);
                break;
                
            case 'f':
                menuFuncionario(MOSTRAR_DEBUG, TEMA);
                break;
                //
                //            case 'p':
                //                printf("---> FAZER MENU PRODUTO <--- ");
                //                break;
                
            case 's':
                menuServico(MOSTRAR_DEBUG, TEMA);
                break;
                
            case 'x':
                printf("\n--------------- SAINDO DOS MENUS ---------------\n");
                printf("\n--------------- OBRIGADO ---------------\n");
                break;
                
            default:
                printf("OPCAO INVALIDA! POR FAVOR SELECIONE UMA LETRA VÁLIDA");
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

/* PODE SER UTIL DEPOIS
 
 // Propriedades
 //    char opcao;
 //    struct Cliente cliente;
 //
 //    printf("Escolha os produtos que deseja da linha para o dia de Spa do seu pet\n");
 //    printf("Escolha o Shampoo para seu pet:\n");
 //    printf("A- Shampoo Pro-Banho Pelencio \nB- Shampoo Pelos Claros Peloncio \nC- Shampoo Pelos Escuros Peloncio \nFragrancias:    Avela - Melancia - Dove - Morango\n");
 //    printf("Selecione a letra do produto desejado:\n");
 //    scanf ("%s", &opcao);
 //    fflush (stdin);
 //    sho
 //
 //    switch (opcao) {
 //        case 'A':
 //        case 'a':
 //            printf("MUITO BOM!!! Voce escolheu  Shampoo Pro-Banho Peloncio\n");
 //            break;
 //        case 'B':
 //        case 'b':
 //            printf("MUITO BOM!!! Voce escolheu Shampoo Pelos Claros Peloncio\n");
 //            break;
 //        case 'C':
 //        case 'c':
 //            printf("MUITO BOM!!! Voce escolheu Shampoo Pelos Escuros Peloncio\n");
 //            break;
 //        default:
 //            printf("Opcao invalida, favor escolher uma opçao correta");
 //    }
 //
 //    printf("Escolha a fragrancia do Condicionador para seu pet:\n");
 //    printf("A-Avela \nB- Melancia \nC- Morango\n");
 //    printf("Selecione uma letra para fragrancia desejada:\n");
 //    scanf ("%c", &opcao);
 //    fflush (stdin);
 //    limparTela(MOSTRAR_DEBUG);
 //
 //    switch (opcao) {
 //        case 'A':
 //        case 'a':
 //            printf("MUITO BOM!!! Voce escolheu Avela\n");
 //            break;
 //        case 'B':
 //        case 'b':
 //            printf("MUITO BOM!!! Voce escolheu Melancia\n");
 //            break;
 //        case 'C':
 //        case 'c':
 //            printf("MUITO BOM!!! Voce escolheu Morango\n");
 //            break;
 //        default:
 //
 //            printf("Opcao invalida, favor selecionar uma opçao correta");
 //    }
 //    printf("Escolha a colonia Perfume Pet Clean Max para seu pet:\n");
 //    printf("A-  Amendoas e Ameixa \nB- Avela e Cereja \nC- Melancia\n");
 //    printf("Selecione uma letra para a colonia desejada:\n");
 //    scanf ("%c", &opcao);
 //    fflush (stdin);
 //    limparTela(MOSTRAR_DEBUG);
 //
 //    switch (opcao)
 //    {
 //        case 'A':
 //        case 'a':
 //            printf("MUITO BOM!!! Voce escolheu Amendoas e Ameixa\n");
 //            break;
 //        case 'B':
 x
 //        case 'b':
 //            printf("MUITO BOM!!! Voce escolheu Avela e Cereja\n");
 //            break;
 //        case 'C':
 //        case 'c':
 //            printf("MUITO BOM!!! Voce escolheu Melancia\n");
 //            break;
 //        default:
 //            printf("Opcao invalida, favor selecioanr uma opçao valida");
 //    }
 */




//############################################################################
//tive que testa na branch de produto!! Estava funcionando perfeitamente
// temos que decidir onde vamos introduzir no cÛdigo/ pensei na hora de abrir o "MENU SERVICOS" na parte de "LISTAR" poderia aparecer os combos
//                COOOOOOOOOOOOOOOOOOOOOOOOOOMBOS
 
