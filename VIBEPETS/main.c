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
                menuFuncionario();
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
// #################################
// MENU FUNCIONARIO
void menuFuncionario() {
    char opcao = 'a';
    
    while(opcao != 'x' && opcao != 'X') {
        limparTela(MOSTRAR_DEBUG);
        
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


void fecharArquivoFuncionario() {
    // Atualizar o arquivo.
    fflush(ponteiroArquivoFUNCIONARIO);
    
    // Fechar o arquivo.
    fclose(ponteiroArquivoFUNCIONARIO);
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
    
    printf("%05d|%-30s|%-15s|%-30s\n", funcionario.codigo, funcionario.nome, formatarCPF(funcionario.cpf, MOSTRAR_DEBUG), funcionario.senha);
}

void printarFuncionarioTopicos(struct Funcionario funcionario) {
    
    if(funcionario.ativo == ' ') {
        printf("%-6s: %d\n", "CODIGO", funcionario.codigo);
        printf("%-6s: %s\n", "NOME", funcionario.nome);
        printf("%-6s: %s\n", "CPF", formatarCPF(funcionario.cpf, MOSTRAR_DEBUG));
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
    interfaceLinhaSeparadora(150, TEMA);
    printf("%-5s|%-30s|%-15s|%-30s\n", "COD", "NOME", "CPF", "SENHA");
    interfaceLinhaSeparadora(150, TEMA);
    
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
