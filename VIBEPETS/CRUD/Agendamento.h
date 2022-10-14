//
//  Agendamento.h
//  VIBEPETS
//
//  Created by Luiz Araujo on 14/10/22.
//





// #############################################################################
// AGENDAMENTO



#ifndef Agendamento_h
#define Agendamento_h

#include "Cliente.h"
#include "Funcionario.h"

FILE *ponteiroArquivoAGENDAMENTO;

void menuAgendamento(int, int);
void menuAgendamentoListarTodos(int, int);
void menuAgendamentoInserir(int, int);
void menuAgendamentoAlterar(int, int);
void menuAgendamentoDeletar(int, int);
void menuAgendamentoHorarios(int);

void abrirArquivoAgendamento(int);
void fecharArquivoAgendamento(void);


void mostrarQuadroHorarios(int);




void abrirArquivoAgendamento(int mostrar_debug) {
    ponteiroArquivoAGENDAMENTO = fopen(BIN_AGE, "r+b"); //tentar abrir
    
    if(ponteiroArquivoAGENDAMENTO == NULL){
        ponteiroArquivoAGENDAMENTO  = fopen(BIN_AGE, "w+b"); // criar o arquivo
        
        if(ponteiroArquivoAGENDAMENTO == NULL){
            if(mostrar_debug == 1) {
                printf("Erro fatal: impossivel abrir/criar o arquivo '%s'\n", BIN_AGE);
            }
            
            // Se chegar ate aqui, quer dizer que nao conseguiu abrir de jeito neNhum...
            // ai encerra o programa 🍃
            exit(1);
        }
    }
}

void fecharArquivoAgendamento() {
    // Atualizar o arquivo.
    fflush(ponteiroArquivoAGENDAMENTO);
    
    // Fechar o arquivo.
    fclose(ponteiroArquivoAGENDAMENTO);
}







// #################################
// FUNCOES CRUD
int  salvarRegistroAgendamento(struct Agendamento, int);
void printarCabecalhoListaAgendamento(int);
void printarTodosRegistrosAgendamento(int, int);
void printarAgendamentoLista(struct Agendamento, int);
void printarAgendamentoTopicos(struct Agendamento, int);
struct Agendamento buscarAgendamentoPorCod(int, int);
int  buscarRegistroAgendamentoPorCod(int, int);
void alterarAgendamento(int, int, int);
int  acessarUltimoCodigoAgendamento(int);
void deletarAgendamento(int, int);
void lerDadosAgendamento(struct Agendamento*, int, int);











// #################################
// MENU AGENDAMENTO
void menuAgendamento(int mostrar_debug, int tema) {
    char opcao = 'a';
    
    while(opcao != 'x' && opcao != 'X') {
        limparTela(mostrar_debug);
        
        printf("\nMENU AGENDAMENTO\n");
        printf("\tI) INSERIR NOVO\n");
        printf("\tA) ALTERAR\n");
        printf("\tL) LISTAR\n");
        printf("\tH) HORARIOS\n");
        printf("\tD) DELETAR\n");
        printf("\tX) VOLTAR\n");
        opcao = receberValidarOpcaoLetra("iahldx");
        
        switch(opcao) {
            case 'a':
                menuAgendamentoAlterar(mostrar_debug, tema);
                break;
                
            case 'd':
                menuAgendamentoDeletar(mostrar_debug, tema);
                break;
                
            case 'i':
                menuAgendamentoInserir(mostrar_debug, tema);
                break;
                
            case 'h':
                menuAgendamentoHorarios(tema);
                break;
                
            case 'l':
                menuAgendamentoListarTodos(mostrar_debug,tema);
                break;
                
            case 'x':
                printf("VOLTANDO!");
                break;
                
            default:
                printf("OPCAO INVALIDA!");
        }
    }
}

void menuAgendamentoListarTodos(int mostrar_debug, int tema) {
    printarTodosRegistrosAgendamento(mostrar_debug, tema);
    printarMensagemContinuar();
}

void menuAgendamentoInserir(int mostrar_debug, int tema) {
    struct Agendamento agendamento;
    
    lerDadosAgendamento(&agendamento, mostrar_debug, tema);
    salvarRegistroAgendamento(agendamento, mostrar_debug);
    printarAgendamentoLista(agendamento, mostrar_debug);
    printarAgendamentoTopicos(agendamento, mostrar_debug);
}

void menuAgendamentoAlterar(int mostrar_debug, int tema) {
    int codigo = 0;
    int registro = 0;
    
    printarTodosRegistrosAgendamento(mostrar_debug, tema);
    
    printf("INFORME O CODIGO PARA ALTERAR: ");
    scanf("%d", &codigo);
    
    registro = buscarRegistroAgendamentoPorCod(codigo, mostrar_debug);
    alterarAgendamento(registro, mostrar_debug, tema);
    
    printarMensagemContinuar();
}

void menuAgendamentoDeletar(int mostrar_debug, int tema) {
    int codigo   = 0;
    int registro = 0;
    
    printarTodosRegistrosAgendamento(mostrar_debug, tema);
    
    printf("INFORME O CODIGO PARA ALTERAR: ");
    scanf("%d", &codigo);
    
    registro = buscarRegistroAgendamentoPorCod(codigo, mostrar_debug);
    deletarAgendamento(registro, mostrar_debug);
    printarMensagemContinuar();
}

void menuAgendamentoHorarios(int tema) {
    mostrarQuadroHorarios(tema);
}





// #################################
// LER OS DADOS DE AGENDAMENTO
void lerDadosAgendamento(struct Agendamento *agendamento, int mostrar_debug, int tema) {
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
        
        if(verificarTempoAteData(agendamento->data, mostrar_debug) <= 1) {
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
                    
                    pesquisaCodigo = buscarClientePorCod(pesquisaCodigo, mostrar_debug).codigo;
                    
                    if(pesquisaCodigo == -1) {
                        if(mostrar_debug == 1) {
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
                    
                    pesquisaCodigo = buscarClientePorCPF(pesquisaCPF, mostrar_debug).codigo;
                    
                    if(pesquisaCodigo == -1) {
                        if(mostrar_debug == 1) {
                            printarMensagem("\nCodigo nao encontrado!\n");
                        }
                        
                    } else {
                        agendamento->codigoCliente = pesquisaCodigo;
                        entradaValida = 's';
                    }
                }
                break;
                
            case '3':
                menuClienteListarTodos(mostrar_debug, tema);
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
        menuServicoListarTodos(tema);
        printf("\nCODIGO DO SERVICO\n");
        scanf("%d", &pesquisaCodigo);
        
        pesquisaCodigo = buscarServicoPorCod(pesquisaCodigo, mostrar_debug).codigo;
        
        if(pesquisaCodigo == -1) {
            if(mostrar_debug == 1) {
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
int salvarRegistroAgendamento(struct Agendamento agendamento, int mostrar_debug) {
    int resultado = 0;
    
    // Adicionar codigo, auto-incrementando,
    // pega o codigo do ultimo registro e incrementa.
    agendamento.codigo = acessarUltimoCodigoAgendamento(mostrar_debug) + 1;
    
    // Poe o novo agendamento no final do arquivo.
    fseek(ponteiroArquivoAGENDAMENTO, 0L, SEEK_END);
    if(fwrite(&agendamento, sizeof(agendamento), 1, ponteiroArquivoAGENDAMENTO)!= 1) {
        if(mostrar_debug == 1) {
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
struct Agendamento buscarAgendamentoPorCod(int codigo, int mostrar_debug) {
    struct Agendamento agendamento;
    int contadorCodigo = -1;
    
    agendamento.codigo = -1;
    
    // Testando se o arquivo foi aberto com sucesso
    if(ponteiroArquivoAGENDAMENTO != NULL) {
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
    if(mostrar_debug == 1) {
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
int buscarRegistroAgendamentoPorCod(int codigo, int mostrar_debug) {
    struct Agendamento agendamento;
    int contadorCodigo = -1;
    
    // Testando se o arquivo foi aberto com sucesso
    if(ponteiroArquivoAGENDAMENTO != NULL) {
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
    if(mostrar_debug == 1) {
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
int acessarUltimoCodigoAgendamento(int mostrar_debug) {
    struct Agendamento agendamento;
    
    fseek(ponteiroArquivoAGENDAMENTO, -1 * sizeof(struct Agendamento), SEEK_END);
    if(fread(&agendamento, sizeof(struct Agendamento), -1, ponteiroArquivoAGENDAMENTO)!= 1){
        if(mostrar_debug == 1) {
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
void printarCabecalhoListaAgendamento(int tema) {
    printf("AGENDAMENTOS\n");
    interfaceLinhaSeparadora(150, tema);
    printf("%-5s|%-10s|%-5s|%-30s|%-30s|%-30s\n", "COD", "DATA", "HORA", "SERVICO", "CLIENTE", "FUNCIONARIO");
    interfaceLinhaSeparadora(150, tema);
}

// #################################
// PRINTAR UM PERFIL DE AGENDAMENTO:
// mostra na tela os dados existentes no registro
void printarAgendamentoLista(struct Agendamento agendamento, int mostrar_debug) {
    //TODO: criar View de perfil AGENDAMENTO.
    struct Cliente cliente;
    struct Funcionario funcionario;
    struct Servico servico;
    
    cliente     = buscarClientePorCod(agendamento.codigoCliente, mostrar_debug);
    funcionario = buscarFuncionarioPorCod(agendamento.codigoFuncionario, mostrar_debug);
    servico     = buscarServicoPorCod(agendamento.codigoServico, mostrar_debug);
    
    printf("%05d|%-10s|%5s", agendamento.codigo, stringDataFormatada(agendamento.data), stringHoraFormatada(agendamento.hora));
    printf("|%-30s|%-30s|%-30s\n", servico.nome, cliente.nome, funcionario.nome);
}

void printarAgendamentoTopicos(struct Agendamento agendamento, int mostrar_debug) {
    struct Cliente cliente;
    struct Funcionario funcionario;
    struct Servico servico;
    
    cliente     = buscarClientePorCod(agendamento.codigoCliente, mostrar_debug);
    funcionario = buscarFuncionarioPorCod(agendamento.codigoFuncionario, mostrar_debug);
    servico     = buscarServicoPorCod(agendamento.codigoServico, mostrar_debug);
    
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
void printarTodosRegistrosAgendamento(int mostrar_debug, int tema) {
    struct Agendamento agendamento;
    struct Cliente cliente;
    struct Funcionario funcionario;
    struct Servico servico;
    
    cliente     = buscarClientePorCod(agendamento.codigoCliente, mostrar_debug);
    funcionario = buscarFuncionarioPorCod(agendamento.codigoFuncionario, mostrar_debug);
    servico     = buscarServicoPorCod(agendamento.codigoServico, mostrar_debug);
    
    int n_Linhas = 0;
    
    // Volta o ponteiro para o inicio.
    rewind(ponteiroArquivoAGENDAMENTO);
    
    printarCabecalhoListaAgendamento(tema);
    
    while(1){
        if(fread(&agendamento, sizeof(agendamento), 1, ponteiroArquivoAGENDAMENTO)!= 1)break; /*Sair do laço*/
        if(agendamento.ativo == '*') continue; /*Passa ao proximo*/
        printarAgendamentoLista(agendamento, mostrar_debug);
        //        printarAgendamentoTopicos(agendamento, mostrar_debug);
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
void alterarAgendamento(int registro, int mostrar_debug, int tema) {
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
    printarAgendamentoTopicos(agendamentoAux, mostrar_debug);
    
    printf("\n\n Novos dados \n\n");
    lerDadosAgendamento(&agendamentoAux, mostrar_debug, tema);
    
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
void deletarAgendamento(int registro, int mostrar_debug) {
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
    printarAgendamentoTopicos(agendamentoAux, mostrar_debug);
    
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




// #################################
// MOSTRAR HORARIOS POR ANO
// Mostra uma tabela com os horarios do mes selecionado, disponiveis ou nao.
void mostrarQuadroHorarios(int tema) {
    int larguraDaTabela = 125;
    int indiceAno = 2022, indiceMes = 1, indiceDia = 1;
    char anoString[5] = "2022";//, mesString[3] = "12";
    
    int indice, inicioExpediente = 8, fimExpediente = 18;
    
    Data dataEscolhida;
    dataEscolhida.dia = 1;
    dataEscolhida.mes = 10;
    dataEscolhida.ano = 2022;
    
//    char stringMesAno;
    
    for(indiceAno = 2022; indiceAno <= 2023; indiceAno++){
        sprintf(anoString, "%d", indiceAno);
        interfaceLinhaSeparadora(larguraDaTabela, tema);
        printarStringCentralizada(anoString, larguraDaTabela);
        interfaceLinhaSeparadora(larguraDaTabela, tema);
        
        printarCabecalhoQuadroHorarios(); printf("\n");
        interfaceLinhaSeparadoraSemQuebraDeLinha(larguraDaTabela, tema);

        for(indiceMes = 1; indiceMes <= 12; indiceMes++){
            
            for(indiceDia = 1; indiceDia <= quantidadeDiaMes(indiceMes); indiceDia++){
                printf("\n%02d/%02d", indiceDia, indiceMes);
                
                for(indice = inicioExpediente; indice < fimExpediente; indice++) {
                    printf("|%5s|%5s", " ", " ");
                }
                printf("\n");
                interfaceLinhaSeparadoraSemQuebraDeLinha(larguraDaTabela, tema);
//                printf("\n");
            }
        }
        
    }
}




#endif /* Agendamento_h */
