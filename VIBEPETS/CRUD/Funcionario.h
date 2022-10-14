//
//  Funcionario.h
//  VIBEPETS
//
//  Created by Luiz Araujo on 14/10/22.
//

#ifndef Funcionario_h
#define Funcionario_h


FILE *ponteiroArquivoFUNCIONARIO;

void abrirArquivoFuncionario(int);
void fecharArquivoFuncionario(void);





void menuFuncionario(int, int);
void menuFuncionarioListarTodos(int, int);
void menuFuncionarioInserir(int);
void menuFuncionarioAlterar(int, int);
void menuFuncionarioDeletar(int, int);


int  salvarRegistroFuncionario(struct Funcionario, int);
void printarTodosRegistrosFuncionario(int, int);
void printarFuncionarioLista(struct Funcionario, int);
void printarFuncionarioTopicos(struct Funcionario, int);
struct Funcionario buscarFuncionarioPorCod(int, int);
int  buscarRegistroFuncionarioPorCod(int, int);
void alterarFuncionario(int, int);
int  acessarUltimoCodigoFuncionario(int);
void deletarFuncionario(int, int);
void lerDadosFuncionario(struct Funcionario*);
struct Funcionario buscarFuncionarioPorCPF(char[], int);






// #################################
// MENU FUNCIONARIO
void menuFuncionario(int mostrar_debug, int tema) {
    char opcao = 'a';
    
    while(opcao != 'x' && opcao != 'X') {
        limparTela(mostrar_debug);
        
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
                menuFuncionarioInserir(mostrar_debug);
                break;
                
            case 'a':
            case 'A':
                menuFuncionarioAlterar(mostrar_debug, tema);
                break;
                
            case 'l':
            case 'L':
                menuFuncionarioListarTodos(mostrar_debug,tema);
                break;
                
            case 'd':
            case 'D':
                menuFuncionarioDeletar(mostrar_debug, tema);
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

void menuFuncionarioListarTodos(int mostrar_debug, int tema) {
    printarTodosRegistrosFuncionario(mostrar_debug, tema);
    printarMensagemContinuar();
}

void menuFuncionarioInserir(int mostrar_debug) {
    struct Funcionario funcionario;
    
    lerDadosFuncionario(&funcionario);
    salvarRegistroFuncionario(funcionario, mostrar_debug);
    printarFuncionarioLista(funcionario, mostrar_debug);
    printarFuncionarioTopicos(funcionario, mostrar_debug);
}

void menuFuncionarioAlterar(int mostrar_debug, int tema) {
    int codigo = 0;
    int registro = 0;
    
    printarTodosRegistrosFuncionario(mostrar_debug, tema);
    
    printf("INFORME O CODIGO PARA ALTERAR: ");
    scanf("%d", &codigo);
    
    registro = buscarRegistroFuncionarioPorCod(codigo, mostrar_debug);
    alterarFuncionario(registro, mostrar_debug);
    
    printarMensagemContinuar();
}

void menuFuncionarioDeletar(int mostrar_debug, int tema) {
    int codigo = 0;
    int registro = 0;
    
    printarTodosRegistrosFuncionario(mostrar_debug, tema);
    
    printf("INFORME O CODIGO PARA ALTERAR: ");
    scanf("%d", &codigo);
    
    registro = buscarRegistroFuncionarioPorCod(codigo, mostrar_debug);
    deletarFuncionario(registro, mostrar_debug);
    printarMensagemContinuar();
}






void abrirArquivoFuncionario(int mostrar_debug) {
    ponteiroArquivoFUNCIONARIO = fopen(BIN_FUN, "r+b"); //tentar abrir
    
    if(ponteiroArquivoFUNCIONARIO == NULL){
        ponteiroArquivoFUNCIONARIO  = fopen(BIN_FUN, "w+b"); // criar o arquivo
        
        if(ponteiroArquivoFUNCIONARIO == NULL){
            if(mostrar_debug == 1) {
                printf("Erro fatal: impossivel abrir/criar o arquivo '%s'\n", BIN_FUN);
            }
            
            // Se chegar ate aqui, quer dizer que nao conseguiu abrir de jeito neNhum...
            // ai encerra o programa 🍃
            exit(1);
        }
    }
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
int salvarRegistroFuncionario(struct Funcionario funcionario, int mostrar_debug) {
    int resultado = 0;
    
    // Adicionar codigo, auto-incrementando,
    // pega o codigo do ultimo registro e incrementa.
    funcionario.codigo = acessarUltimoCodigoFuncionario(mostrar_debug) + 1;
    
    // Poe o novo funcionario no final do arquivo.
    fseek(ponteiroArquivoFUNCIONARIO, 0L, SEEK_END);
    if(fwrite(&funcionario, sizeof(funcionario), 1, ponteiroArquivoFUNCIONARIO)!= 1) {
        if(mostrar_debug == 1) {
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
struct Funcionario buscarFuncionarioPorCod(int codigo, int mostrar_debug) {
    struct Funcionario funcionario;
    int contadorCodigo = -1;
    
    funcionario.codigo = -1;
    
    // Testando se o arquivo foi aberto com sucesso
    if(ponteiroArquivoFUNCIONARIO != NULL) {
        if(mostrar_debug == 1) {
            printf("\n\nArquivo %s foi aberto com sucesso\n\n", BIN_FUN);
        }
        
    } else {
        if(mostrar_debug == 1) {
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
    if(mostrar_debug == 1) {
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
struct Funcionario buscarFuncionarioPorCPF(char cpf[12], int mostrar_debug) {
    struct Funcionario funcionario;
    int contadorCodigo = -1;
    
    funcionario.codigo = -1;
    
    // Testando se o arquivo foi aberto com sucesso
    if(ponteiroArquivoFUNCIONARIO != NULL) {
        if(mostrar_debug == 1) {
            printf("\n\nArquivo %s foi aberto com sucesso\n\n", BIN_FUN);
        }
        
    } else {
        if(mostrar_debug == 1) {
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
    if(mostrar_debug == 1) {
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
int buscarRegistroFuncionarioPorCod(int codigo, int mostrar_debug) {
    struct Funcionario funcionario;
    int contadorCodigo = -1;
    
    // Testando se o arquivo foi aberto com sucesso
    if(ponteiroArquivoFUNCIONARIO != NULL) {
        if(mostrar_debug == 1) {
            printf("\n\nArquivo %s foi aberto com sucesso\n\n", BIN_FUN);
        }
        
    } else {
        if(mostrar_debug == 1) {
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
    if(mostrar_debug == 1) {
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
int acessarUltimoCodigoFuncionario(int mostrar_debug) {
    struct Funcionario funcionario;
    
    fseek(ponteiroArquivoFUNCIONARIO, -1 * sizeof(struct Funcionario), SEEK_END);
    if(fread(&funcionario, sizeof(struct Funcionario), -1, ponteiroArquivoFUNCIONARIO)!= 1){
        if(mostrar_debug == 1) {
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
void printarFuncionarioLista(struct Funcionario funcionario, int mostrar_debug) {
    //TODO: criar View de perfil FUNCIONARIO.
    
    printf("%05d|%-30s|%-15s|%-30s\n", funcionario.codigo, funcionario.nome, formatarCPF(funcionario.cpf, mostrar_debug), funcionario.senha);
}

void printarFuncionarioTopicos(struct Funcionario funcionario, int mostrar_debug) {
    
    if(funcionario.ativo == ' ') {
        printf("%-6s: %d\n", "CODIGO", funcionario.codigo);
        printf("%-6s: %s\n", "NOME", funcionario.nome);
        printf("%-6s: %s\n", "CPF", formatarCPF(funcionario.cpf, mostrar_debug));
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
void printarTodosRegistrosFuncionario(int mostrar_debug, int tema) {
    struct Funcionario funcionario;
    int n_Linhas = 0;
    
    // Volta o ponteiro para o inicio.
    rewind(ponteiroArquivoFUNCIONARIO);
    
    printf("FUNCIONARIOS\n");
    interfaceLinhaSeparadora(150, tema);
    printf("%-5s|%-30s|%-15s|%-30s\n", "COD", "NOME", "CPF", "SENHA");
    interfaceLinhaSeparadora(150, tema);
    
    while(1){
        if(fread(&funcionario, sizeof(funcionario), 1, ponteiroArquivoFUNCIONARIO)!= 1)break; /*Sair do laço*/
        if(funcionario.ativo == '*') continue; /*Passa ao proximo*/
        printarFuncionarioLista(funcionario, mostrar_debug);
        //        printarFuncionarioTopicos(funcionario, mostrar_debug);
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
void alterarFuncionario(int registro, int mostrar_debug) {
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
    printarFuncionarioTopicos(funcionarioAux, mostrar_debug);
    
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
void deletarFuncionario(int registro, int mostrar_debug) {
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
    printarFuncionarioTopicos(funcionarioAux, mostrar_debug);
    
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






















#endif /* Funcionario_h */
