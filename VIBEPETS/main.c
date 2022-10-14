//
//  main.c
//  VIBEPETS
//
//  Created by Nathalia Braz on 24/09/22.
//

//#include "main.h"
#include "Headers/main.h"

int main(int argc, char *argv[]) {
    //    struct Funcionario funcionario;
    char opcao = 'a';
    
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
    abrirTodosArquivos();

    // MENU PRINCIPAL
    menuPrincipal();

    fecharTodosArquivos();
//    mostrarQuadroHorarios();
    
    printf("\n\n\n");
    system("pause");
    
    return 0;
}


// #############################################################################
// MENUS
void menuPrincipal() {
    char opcao = 'a';
    
    while(opcao != 'x' && opcao != 'X') {
        limparTela(MOSTRAR_DEBUG);
        
        printf("\nMENU PRINCIPAL\n");
        printf("\tA) MENU AGENDAMENTO\n");
        printf("\tC) MENU CLIENTE\n");
        printf("\tF) MENU FUNCIONARIO\n");
//        printf("\tP) MENU PRODUTO\n");
        printf("\tS) MENU SERVICOS\n");
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
 //    limparTela(MOSTRAR_DEBUG);
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
 //    limparTela(MOSTRAR_DEBUG);
 //
 //    switch (opcao)
 //    {
 //        case 'A':
 //        case 'a':
 //            printf("Voce escolheu Amendoas e Ameixa\n");
 //            break;
 //        case 'B':
 x
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
 */
