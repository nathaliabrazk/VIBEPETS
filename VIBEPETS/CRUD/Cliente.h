//
//  Cliente.h
//  VIBEPETS
//
//  Created by Luiz Araujo on 14/10/22.
//

// #############################################################################
// CLIENTE

#ifndef Cliente_h
#define Cliente_h

// #################################
// CONSTANTES
FILE *ponteiroArquivoCLIENTE;


// #################################
// PROTOTIPOS
void abrirArquivoCliente(int);
void fecharArquivoCliente(void);

void menuCliente(int, int);
void menuClienteAlterar(int, int);
void menuClienteDeletar(int, int);
void menuClienteInserir(int);
void menuClienteListarTodos(int, int);

int  acessarUltimoCodigoCliente(int);
void alterarCliente(int, int);
struct Cliente buscarClientePorCod(int, int);
int  buscarRegistroClientePorCod(int, int);
struct Cliente buscarClientePorCPF(char[], int);
void deletarCliente(int, int);
void lerDadosCliente(struct Cliente*);
void printarCabecalhoTodosClientes(int);
void printarClienteLista(struct Cliente, int);
void printarClienteTopicos(struct Cliente, int);
void printarTodosRegistrosCliente(int, int);
int  salvarRegistroCliente(struct Cliente, int);


// #################################
// FUNCOES
void menuCliente(int mostrar_debug, int tema) {
    char opcao = 'a';
    
    while(opcao != 'x' && opcao != 'X') {
        limparTela(mostrar_debug);
        
        printf("\nMENU CLIENTE\n");
        printf("\tA) ALTERAR\n");
        printf("\tD) DELETAR\n");
        printf("\tI) INSERIR\n");
        printf("\tL) LISTAR\n");
        printf("\tX) VOLTAR\n");
        opcao = receberValidarOpcaoLetra("ialdx");
        
        switch(opcao) {
            case 'a':
                menuClienteAlterar(mostrar_debug, tema);
                break;
                
            case 'd':
                menuClienteDeletar(mostrar_debug, tema);
                break;
                
            case 'i':
                menuClienteInserir(mostrar_debug);
                break;
                
            case 'l':
                menuClienteListarTodos(mostrar_debug, tema);
                break;
                
            case 'x':
                printf("VOLTANDO!");
                break;
                
            default:
                printf("OPCAO INVALIDA!");
        }
    }
}

void menuClienteAlterar(int mostrar_debug, int tema) {
    int codigo = 0;
    int registro = 0;
    
    printarTodosRegistrosCliente(mostrar_debug, tema);
    
    printf("INFORME O CODIGO PARA ALTERAR: ");
    scanf("%d", &codigo);
    
    registro = buscarRegistroClientePorCod(codigo, mostrar_debug);
    alterarCliente(registro, mostrar_debug);
    
    printarMensagemContinuar();
}

void menuClienteDeletar(int mostrar_debug, int tema) {
    int codigo   = 0;
    int registro = 0;
    
    printarTodosRegistrosCliente(mostrar_debug, tema);
    
    printf("INFORME O CODIGO PARA ALTERAR: ");
    scanf("%d", &codigo);
    
    registro = buscarRegistroClientePorCod(codigo, mostrar_debug);
    deletarCliente(registro, mostrar_debug);
    printarMensagemContinuar();
}

void menuClienteInserir(int mostrar_debug) {
    struct Cliente cliente;
    
    lerDadosCliente(&cliente);
    salvarRegistroCliente(cliente, mostrar_debug);
    printarClienteLista(cliente, mostrar_debug);
    printarClienteTopicos(cliente, mostrar_debug);
}

void menuClienteListarTodos(int mostrar_debug, int tema) {
    printarTodosRegistrosCliente(mostrar_debug, tema);
    printarMensagemContinuar();
}


void abrirArquivoCliente(int mostrar_debug) {
    ponteiroArquivoCLIENTE = fopen(BIN_CLI, "r+b"); //tentar abrir
    
    if(ponteiroArquivoCLIENTE == NULL){
        ponteiroArquivoCLIENTE  = fopen(BIN_CLI, "w+b"); // criar o arquivo
        
        if(ponteiroArquivoCLIENTE == NULL){
            if(mostrar_debug == 1) {
                printf("Erro fatal: impossivel abrir/criar o arquivo '%s'\n", BIN_CLI);
            }
            
            // Se chegar ate aqui, quer dizer que nao conseguiu abrir de jeito neNhum...
            // ai encerra o programa 🍃
            exit(1);
        }
    }
}

void fecharArquivoCliente() {
    // Atualizar o arquivo.
    fflush(ponteiroArquivoCLIENTE);
    
    // Fechar o arquivo.
    fclose(ponteiroArquivoCLIENTE);
}


// #################################
// BUSCAR CODIGO DO ULTIMO REGISTRO
// Uma funçao para ir ate o ultimo registro, ultimo cliente cadastrado e
// retorna seu respectivo codigo.
// RETORNO:
//  - O int do codigo.
int acessarUltimoCodigoCliente(int mostrar_debug) {
    struct Cliente cliente;
    
    fseek(ponteiroArquivoCLIENTE, -1 * sizeof(struct Cliente), SEEK_END);
    if(fread(&cliente, sizeof(struct Cliente), -1, ponteiroArquivoCLIENTE)!= 1){
        if(mostrar_debug == 1) {
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
// ALTERAR UM PERFIL DE CLIENTE
// Encontra a posicao do registro pelo numero que representa a linha na qual está
// e mostra como está momento antes da alteracao, apos isso rece novos dados e atualiza.
// PARAMETRO:
//   - registro: int da 'linha' que está o referido registro.
void alterarCliente(int registro, int mostrar_debug) {
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
    printarClienteTopicos(clienteAux, mostrar_debug);
    
    printf("\n\n Novos dados \n\n");
    lerDadosCliente(&clienteAux);
    
    // recuar um registro no arquivo
    fseek(ponteiroArquivoCLIENTE, -(int) sizeof(struct Cliente), SEEK_CUR);
    // reescrever o registro;
    fwrite(&clienteAux, sizeof(struct Cliente), 1, ponteiroArquivoCLIENTE);
    fflush(ponteiroArquivoCLIENTE); /*despejar os arquivos no disco rígido*/
}

// #################################
// BUSCAR REGISTRO DE CLIENTE POR CODIGO
// Uma funçao para retornar o registro (posicao no arquivo) procurando pelo codigo.
// RETORNO:
//  -  O numero do registro, caso encontre;
//  - -1 caso, nao encontre.
int buscarRegistroClientePorCod(int codigo, int mostrar_debug) {
    struct Cliente clienteAuxiliar;
    int contadorCodigo = -1;
    
    // Testando se o arquivo foi aberto com sucesso
    if(ponteiroArquivoCLIENTE != NULL) {
        if(mostrar_debug == 1) {
            printf("\n\nArquivo %s foi aberto com sucesso\n\n", BIN_CLI);
        }
        
    } else {
        if(mostrar_debug == 1) {
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
    if(mostrar_debug == 1) {
        printf("\n\nERRO: registro nao encontrado.");
    }
    contadorCodigo = -1;
    
    return contadorCodigo;
}

// #################################
// BUSCAR CLIENTE POR CODIGO
// Uma funçao para retornar o cliente procurando pelo codigo.
// RETORNO:
//  -  Uma instancia de Cliente com os dados encontrados.
//  - A instancia de Agendamento com os dados encontrados;
//  - 'cliente.codigo = -1' caso nao encontre.
struct Cliente buscarClientePorCod(int codigo, int mostrar_debug) {
    struct Cliente clienteAuxiliar;
    int contadorCodigo = -1;
    
    clienteAuxiliar.codigo = -1;
    
    // Testando se o arquivo foi aberto com sucesso
    if(ponteiroArquivoCLIENTE != NULL) {
        if(mostrar_debug == 1) {
            printf("\n\nArquivo %s foi aberto com sucesso\n\n", BIN_CLI);
        }
        
    } else {
        if(mostrar_debug == 1) {
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
    if(mostrar_debug == 1) {
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
struct Cliente buscarClientePorCPF(char cpf[12], int mostrar_debug) {
    struct Cliente clienteAuxiliar;
    int contadorCodigo = -1;
    
    clienteAuxiliar.codigo = -1;
    
    // Testando se o arquivo foi aberto com sucesso
    if(ponteiroArquivoCLIENTE != NULL) {
        if(mostrar_debug == 1) {
            printf("\n\nArquivo %s foi aberto com sucesso\n\n", BIN_CLI);
        }
        
    } else {
        if(mostrar_debug == 1) {
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
    if(mostrar_debug == 1) {
        printf("\n\nERRO: registro nao encontrado.");
    }
    
    return clienteAuxiliar;
}

// #################################
// DELETAR UM PERFIL DE CLIENTE
// Encontra a posicao do registro pelo numero que representa a linha na qual está
// e apaga logicamente (deixa invisivel);
// PARAMETRO:
//   - registro: int da 'linha' que está o referido registro.
void deletarCliente(int registro, int mostrar_debug) {
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
    printarClienteTopicos(clienteAux, mostrar_debug);
    
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
// PRINTAR UM PERFIL DE CLIENTE:
// mostra na tela os dados existentes no registro
void printarClienteLista(struct Cliente cliente, int mostrar_debug) {
    //TODO: criar View de perfil CLIENTE.
    
    printf("%05d|%-30s|%-15s|%-30s|%-30s|%-15d|%02d/%02d/%d\n", cliente.codigo, cliente.nome, formatarCPF(cliente.cpf, mostrar_debug), cliente.email, cliente.endereco, cliente.telefone, cliente.nascimento.dia, cliente.nascimento.mes, cliente.nascimento.ano);
}

void printarClienteTopicos(struct Cliente cliente, int mostrar_debug) {
    
    printf("%-8s: %d\n", "", cliente.codigo);
    
    if(cliente.ativo != '*') {
        printf("%-10s: %d\n", "CODIGO", cliente.codigo);
        printf("%-10s: %s\n", "NOME", cliente.nome);
        printf("%-10s: %s\n", "CPF", formatarCPF(cliente.cpf, mostrar_debug));
        printf("%-10s: %s\n", "EMAIL", cliente.email);
        printf("%-10s: %s\n", "ENDERECO", cliente.endereco);
        printf("%-10s: %d\n", "TELEFONE", cliente.telefone);
        printf("%-10s: %02d/%02d/%d\n", "NASCIMENTO", cliente.nascimento.dia, cliente.nascimento.mes, cliente.nascimento.ano);
        
    } else {
        printf("\nCLIENTE DELETADO!\n");
    }
}

void printarCabecalhoTodosClientes(int tema) {
    printf("CLIENTES\n");
    interfaceLinhaSeparadora(150, tema);
    printf("%-5s|%-30s|%-15s|%-30s|%-30s|%-15s|%-10s|\n", "COD", "NOME", "CPF", "EMAIL", "ENDERECO","TELEFONE", "NASC");
    interfaceLinhaSeparadora(150, tema);
}

// #################################
// LER TODOS PERFIS DE CLIENTE
void printarTodosRegistrosCliente(int mostrar_debug, int tema) {
    struct Cliente cliente;
    int n_Linhas = 0;
    
    // Volta o ponteiro para o inicio.
    rewind(ponteiroArquivoCLIENTE);
    
    printarCabecalhoTodosClientes(tema);
    
    while(1){
        if(fread(&cliente, sizeof(cliente), 1, ponteiroArquivoCLIENTE)!= 1) break; /*Sair do laço*/
        if(cliente.ativo == '*') continue; /*Passa ao proximo*/
        printarClienteLista(cliente, mostrar_debug);
        //        printarClienteTopicos(cliente, mostrar_debug);
        n_Linhas++;
        if(n_Linhas%20 == 0)
            printarMensagem("Pressione <Enter> para continuar .  .  .");
    }
    //    printf("\n\n\n");
    
}

// #################################
// SALVAR DADOS DE CLIENTE
// RETORNO:
//  -    0: se nao houve erros;
//  - != 0: se houve erro(s);
int salvarRegistroCliente(struct Cliente cliente, int mostrar_debug) {
    int resultado = 0;
    
    // Adicionar codigo, auto-incrementando,
    // pega o codigo do ultimo registro e incrementa.
    cliente.codigo = acessarUltimoCodigoCliente(mostrar_debug) + 1;
    
    // Poe o novo cliente no final do arquivo.
    fseek(ponteiroArquivoCLIENTE, 0L, SEEK_END);
    if(fwrite(&cliente, sizeof(cliente), 1, ponteiroArquivoCLIENTE)!= 1) {
        if(mostrar_debug == 1) {
            printarMensagem("Adicionar cliente: Falhou a escrita do registro");
        }
        
        resultado = 1;
    }
    
    // Retornando o valor do resultado.
    return(resultado);
}

#endif /* Cliente_h */
