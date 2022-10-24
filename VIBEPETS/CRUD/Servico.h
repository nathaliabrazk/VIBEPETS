//
//  Servico.h
//  VIBEPETS
//
//  Created by Luiz Araujo on 14/10/22.
//

// #############################################################################
// SERVICO

#ifndef Servico_h
#define Servico_h

// #################################
// CONSTANTES
FILE *ponteiroArquivoSERVICO;


// #################################
// PROTOTIPOS
void menuServico(int, int);
void menuServicoAlterar(int, int);
void menuServicoDeletar(int, int);
void menuServicoInserir(int);
void menuServicoListarTodos(int);
void menuServicoListarCombos(int);

int  acessarUltimoCodigoServico(int);
void alterarServico(int, int);
int  buscarRegistroServicoPorCod(int, int);
struct Servico buscarServicoPorCod(int, int);
void deletarServico(int);
void lerDadosServico(struct Servico*, int);
void printarServicoLista(struct Servico);
void printarServicoTopicos(struct Servico);
void printarTodosRegistrosServico(int);
int  salvarRegistroServico(struct Servico, int);

void abrirArquivoServico(int);
void fecharArquivoServico(void);


// #################################
// FUNCOES

void menuServico(int mostrar_debug, int tema) {
    char opcao = 'a';
    
    while(opcao != 'X' && opcao != 'x') {
        limparTela(mostrar_debug);
        
        printf("\n MENU SERVICO\n");
        printf("\tC) COMBOS\n");
        printf("\tA) ALTERAR\n");
        printf("\tI) INSERIR NOVO\n");
        printf("\tD) DELETAR\n");
        printf("\tX) VOLTAR\n");
        printf("OPCAO: ");
        //        scanf("%c", &opcao); fflush(stdin);
        opcao = getchar();
        fflush(stdin);
        
        switch(opcao) {
            case 'a':
            case 'A':
                menuServicoAlterar(mostrar_debug, tema);
                break;
                
            case 'c':
            case 'C':
//                menuServicoListarTodos(tema);
                menuServicoListarCombos(tema);
                break;
                
            case 'i':
            case 'I':
                menuServicoInserir(mostrar_debug);
                break;
                
            case 'd':
            case 'D':
                menuServicoDeletar(mostrar_debug, tema);
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

void menuServicoAlterar(int mostrar_debug, int tema) {
    int codigo = 0;
    int registro = 0;
    
    printarTodosRegistrosServico(tema);
    
    printf("INFORME O CODIGO PARA ALTERAR: ");
    scanf("%d", &codigo);
    
    registro = buscarRegistroServicoPorCod(codigo, mostrar_debug);
    alterarServico(registro, mostrar_debug);
    
    printarMensagemContinuar();
}

void menuServicoDeletar(int mostrar_debug, int tema) {
    int codigo = 0;
    int registro = 0;
    
    printarTodosRegistrosServico(tema);
    
    printf("INFORME O CODIGO PARA ALTERAR: ");
    scanf("%d", &codigo);
    
    registro = buscarRegistroServicoPorCod(codigo, mostrar_debug);
    deletarServico(registro);
    printarMensagemContinuar();
}

void menuServicoInserir(int mostrar_debug) {
    struct Servico servico;
    
    lerDadosServico(&servico, mostrar_debug);
    salvarRegistroServico(servico, mostrar_debug);
    printarServicoLista(servico);
    printarServicoTopicos(servico);
}

void menuServicoListarTodos(int tema) {
    printarTodosRegistrosServico(tema);
    printarMensagemContinuar();
}

void menuServicoListarCombos(int tema) {
    struct Servico servico;
    char opcao = ' ';
    
    servico.ativo = ' ';
    
    interfaceLinhaSeparadoraSemQuebraDeLinha(100, 1);
    printf ("\nEscolha um dos nossos servicos!\n ");
    printf("\nOBSERVACAO (SO PODE SER ESCOLHIDO UM COMBO DE SERVICO POR DIA E POR PET)\n");
    
    interfaceLinhaSeparadoraSemQuebraDeLinha(100, 1);
    printf("\nA)");
    printf("\n-Tosa e banho");
    printf("\n-Shampoo Banho de Carinho Petz");
    printf("\n-Condicionador Chegou o Brincalhao Petz");
    printf("\n-Colonia Hydra Groomers Forevers");
    printf("\n-Creme Hidratante de Patinhas");
    printf("\n-Vela Aromatica Perfumada | Lavanda");
    printf("\n|VALOR: 100,00|");
    
    interfaceLinhaSeparadoraSemQuebraDeLinha(100, 1);
    printf("\nB)");
    printf("\n-Tosa e banho");
    printf("\n-Shampoo Pet Society Neutro");
    printf("\n-Condicionador Pet Society");
    printf("\n-Colonia Pet Society Lovely");
    printf("\n-Creme hidrantante Pet Society Lovely");
    printf("\n-Vela Aromatica Perfumada| Canela");
    printf("\n|VALOR: 90,00|");
    
    interfaceLinhaSeparadoraSemQuebraDeLinha(100, 1);
    printf("\nC)");
    printf("\n-Tosa e banho");
    printf("\n-Shampoo Matacura Sarnicida e Anti-Pulgas");
    printf("\n-Condicionador Matacura Sarnicida e Anti-Pulgas");
    printf("\n-Perfume Ibasa de ColÙnia Affection para Caes e Gatos");
    printf("\n-Creme Hidratante Equilibrio Hidrapet");
    printf("\n-Vela Aromatica Perfumada | Baunilha");
    interfaceLinhaSeparadoraSemQuebraDeLinha(100, 1);
    
    printf("\n|VALOR: 80,00|");
    printf("\nOPCAO:\n");
    scanf ("%s", &opcao);
    fflush (stdin);
    system ("cls");
    
    while(opcao == ' ') {
        
        switch (opcao) {
            case 'A':
            case 'a':
                printf ("\nVoce escolheu o combo (A)");
                printf("\n-Tosa e banho");
                printf("\n-Shampoo Banho de Carinho Petz");
                printf("\n-Condicionador Chegou o Brincalhao Petz");
                printf("\n-Colonia Hydra Groomers Forevers");
                printf("\n-Creme Hidratante de Patinhas");
                printf("\n-Vela Aromatica Perfumada | Lavanda");
                printf("\n|VALOR: 100,00|\n");
                strcpy(servico.nome, "COMBO A");
                servico.valor = 100;
                break;
                
            case 'B':
            case 'b':
                printf("\nVoce escolheu o combo (B)");
                printf("\n-Tosa e banho\n-Shampoo Pet Society Neutro");
                printf("\n-Condicionador Pet Society");
                printf("\n-Colonia Pet Society Lovely");
                printf("\n-Creme hidrantante Pet Society Lovely");
                printf("\n-Vela Aromatica Perfumada| Canela");
                printf("\n|VALOR: 90,00|\n");
                strcpy(servico.nome, "COMBO B");
                servico.valor = 90;
                break;
                
            case 'C':
            case 'c':
                printf("\nVoce escolheu o combo (C)");
                printf("\n-Tosa e banho");
                printf("\n-Shampoo Matacura Sarnicida e Anti-Pulgas");
                printf("\n-Condicionador Matacura Sarnicida e Anti-Pulgas");
                printf("\n-Perfume Ibasa de Colonia Affection para Caes e Gatos");
                printf("\n-Creme Hidratante Equilibrio Hidrapet");
                printf("\n-Vela Aromatica Perfumada | Baunilha");
                printf("\n|VALOR: 80,00|");
                strcpy(servico.nome, "COMBO C");
                servico.valor = 80;
                break;
                
            default:
                printf ("\nOPCAO INVALIDA\n");
                opcao = ' ';
        }
    }
    
    printarTodosRegistrosServico(tema);
    printarMensagemContinuar();
}


void abrirArquivoServico(int mostrar_debug) {
    ponteiroArquivoSERVICO = fopen(BIN_SER, "r+b"); //tentar abrir
    
    if(ponteiroArquivoSERVICO == NULL){
        ponteiroArquivoSERVICO  = fopen(BIN_SER, "w+b"); // criar o arquivo
        
        if(ponteiroArquivoSERVICO == NULL){
            if(mostrar_debug == 1) {
                printf("Erro fatal: impossivel abrir/criar o arquivo '%s'\n", BIN_SER);
            }
            
            // Se chegar ate aqui, quer dizer que nao conseguiu abrir de jeito neNhum...
            // ai encerra o programa 🍃
            exit(1);
        }
    }
}

void fecharArquivoServico() {
    // Atualizar o arquivo.
    fflush(ponteiroArquivoSERVICO);
    
    // Fechar o arquivo.
    fclose(ponteiroArquivoSERVICO);
}



// #################################
// BUSCAR CODIGO DO ULTIMO REGISTRO
// Uma funçao para ir ate o ultimo registro, ultimo servico cadastrado e
// retorna seu respectivo codigo.
// RETORNO:
//  - O int do codigo.
int acessarUltimoCodigoServico(int mostrar_debug) {
    struct Servico servico;
    
    fseek(ponteiroArquivoSERVICO, -1 * sizeof(struct Servico), SEEK_END);
    if(fread(&servico, sizeof(struct Servico), -1, ponteiroArquivoSERVICO)!= 1){
        if(mostrar_debug == 1) {
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
// ALTERAR UM PERFIL DE SERVICO
// Encontra a posicao do registro pelo numero que representa a linha na qual está
// e mostra como está momento antes da alteracao, apos isso rece novos dados e atualiza.
// PARAMETRO:
//   - registro: int da 'linha' que está o referido registro.
void alterarServico(int registro, int mostrar_debug) {
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
    lerDadosServico(&servicoAux, mostrar_debug);
    
    // recuar um registro no arquivo
    fseek(ponteiroArquivoSERVICO, -(int) sizeof(struct Servico), SEEK_CUR);
    // reescrever o registro;
    fwrite(&servicoAux, sizeof(struct Servico), 1, ponteiroArquivoSERVICO);
    fflush(ponteiroArquivoSERVICO); /*despejar os arquivos no disco rígido*/
}
// #################################
// BUSCAR SERVICO POR CODIGO
// Uma funçao para retornar o registro (posicao no arquivo) procurando pelo codigo.
// RETORNO:
//  - A instancia de Servico com os dados encontrados;
//  - 'servico.codigo = -1' caso nao encontre.
struct Servico buscarServicoPorCod(int codigo, int mostrar_debug) {
    struct Servico servico;
    int contadorCodigo = -1;
    
    servico.codigo = -1;
    
    // Testando se o arquivo foi aberto com sucesso
    if(ponteiroArquivoSERVICO != NULL) {
        if(mostrar_debug == 1) {
            printf("\n\nArquivo %s foi aberto com sucesso\n\n", BIN_FUN);
        }
        
    } else {
        if(mostrar_debug == 1) {
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
    if(mostrar_debug == 1) {
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
int buscarRegistroServicoPorCod(int codigo, int mostrar_debug) {
    struct Servico servico;
    int contadorCodigo = -1;
    
    // Testando se o arquivo foi aberto com sucesso
    if(ponteiroArquivoSERVICO != NULL) {
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
    if(mostrar_debug == 1) {
        printf("\n\nERRO: registro nao encontrado.");
    }
    contadorCodigo = -1;
    
    return contadorCodigo;
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

// #################################
// LER OS DADOS DE SERVICO
void lerDadosServico(struct Servico *servico, int mostrar_debug) {
    
    fflush(stdin);
    printf("Nome   : ");
    gets(servico->nome); fflush(stdin);
    
    printf("Duracao: ");
    scanf("%d", &servico->duracao);
    
    printf("Valor  : ");
    scanf("%f", &servico->valor);
    
    if(mostrar_debug == 1) {
        printf("🤔 VALOR INSERIDO: %f", servico->valor);
    }
    
    servico->ativo = ' '; // Qualquer coisa menos '*' significa ativo
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
void printarTodosRegistrosServico(int tema) {
    struct Servico servico;
    int n_Linhas = 0;
    
    // Volta o ponteiro para o inicio.
    rewind(ponteiroArquivoSERVICO);
    
    printf("SERVICOS\n");
    interfaceLinhaSeparadora(100, tema);
    printf("%-5s|%-30s|%-10s|%-10s\n", "COD", "NOME", "DURACAO", "VALOR");
    interfaceLinhaSeparadora(100, tema);
    
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
// SALVAR DADOS DE SERVICO
// RETORNO:
//  -    0: se nao houve erros;
//  - != 0: se houve erro(s);
int salvarRegistroServico(struct Servico servico, int mostrar_debug) {
    int resultado = 0;
    
    // Adicionar codigo, auto-incrementando,
    // pega o codigo do ultimo registro e incrementa.
    servico.codigo = acessarUltimoCodigoServico(mostrar_debug) + 1;
    
    // Poe o novo servico no final do arquivo.
    fseek(ponteiroArquivoSERVICO, 0L, SEEK_END);
    if(fwrite(&servico, sizeof(servico), 1, ponteiroArquivoSERVICO)!= 1) {
        if(mostrar_debug == 1) {
            printarMensagem("Adicionar servico: Falhou a escrita do registro");
        }
        
        resultado = 1;
    }
    
    // Retornando o valor do resultado.
    return(resultado);
}

#endif /* Servico_h */
