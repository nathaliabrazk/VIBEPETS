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
#define BIN_ADM "vibe_pet-persistencia_adm1.bin"
#define BIN_FUN "vibe_pet-persistencia_func.bin"
#define BIN_CLI "vibe_pet-persistencia_cli.bin"
#define BIN_SER "vibe_pet-persistencia_serv.bin"
#define BIN_TEL "vibe_pet-persistencia_tel.bin"
#define BIN_END "vibe_pet-persistencia_end.bin"


#define SHOW_DEBUG 1    // 1 = Mostra coisas na tela, msg de erro e etc.
#define DELETE_FILES 0  // 1 = Apaga os arquivos ao iniciar o sistema(zera o BD)

// Ponteiro para indicar o 'endereco' do arquivo a ser manipulado.
FILE *ponteiroArquivoADM;
//FILE *ponteiroArquivoFUN;
//FILE *ponteiroArquivoCLI;
//FILE *ponteiroArquivoSER;
//FILE *ponteiroArquivoTEL;
//FILE *ponteiroArquivoEND;


// #############################################################################
// DECLARACAO DE TIPOS

struct Administrador {
    int cod_adm;
    char nome[30];
    char cpf[12];
    char senha[25];
    int cargo;      // 0 = admin || 1 = funcionario
    char ativo;      // '*' = inativo/deletado
};

// CLIENTE
struct Cliente {
    int cod_cliente;
    char nome[50];
    char email[50];
    char endereco[50];
    char cpf[12];
    int  nascimentoDia;
    int  nascimentoMes;
    int  nascimentoAno;
    int  telefone;
    char ativo;      // '*' = inativo/deletado
};

// #############################################################################
// PROTOTIPOS
void abrirArquivos(void);
int salvarRegistroAdministrador(struct Administrador);
void printarMensagem(char *msg);
void printarTodosPerfisAdministrador(void);
void printarAdministradorLista(struct Administrador);
void printarAdministradorTopicos(struct Administrador);
int buscarAdministradorPorCod(int);
void alterarAdministrador(int);
void printarMensagemContinuar(void);
int acessarUltimoCodigoAdministrador(void);

void lerDadosAdministrador(struct Administrador*);



int main(int argc, char *argv[]) {
    setlocale (LC_ALL, "");
    
    // INICIALIZACOES
    abrirArquivos();
    
    // Propriedades
    //    char opcao;
    //	struct Cliente cliente;
    
    // Entradas
    
    //    printf("Digite o nome: ");
    //    fgets(cliente.nome, sizeof(cliente.nome), stdin);
    //    fflush (stdin);
    //    system ("cls");
    //
    //    printf("Digite email: ");
    //    fgets(cliente.email, sizeof(cliente.email), stdin);
    //    fflush (stdin);
    //    system ("cls");
    //
    //    printf("Digite Endereco:");
    //    fgets(cliente.endereco, sizeof(cliente.endereco), stdin);
    //    fflush (stdin);
    //    system("cls");
    //
    //    printf("Digite o telefone:");
    //    scanf("%d", &cliente.telefone);
    //    fflush (stdin);
    //
    //    printf("Digite o CPF:");
    //    fgets(cliente.cpf, sizeof(cliente.cpf), stdin);
    //    fflush (stdin);
    //
    //    printf("DIGITE SUA DATA DE NASCIMENTO\n");
    //    printf("Digite o dia: ");
    //    scanf("%d", &cliente.nascimentoDia);
    //
    //    printf("Digite o mes: ");
    //    scanf("%d", &cliente.nascimentoMes);
    //
    //    printf("Digite o ano: ");
    //    scanf("%d", &cliente.nascimentoAno);
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
    
    /*
    // Criar um ADM.
    struct Administrador administrador1;
    administrador1.cod_adm = 0;
    strcpy(administrador1.nome, "administrador1");
    strcpy(administrador1.cpf, "01234567890");
    strcpy(administrador1.senha, "administrador123");
    administrador1.cargo = 0; // Funcionario 0 = adm
    administrador1.ativo = ' ';
    
    // Criar outro ADM.
    struct Administrador administrador2;
    administrador2.cod_adm = 0;
    administrador2.cargo = 1; // Funcionario 0 = adm
    administrador2.ativo = ' ';
    strcpy(administrador2.nome, "aaaa");
    strcpy(administrador2.cpf, "01234567890");
    strcpy(administrador2.senha, "administrador123");
    
    
    // Persistir os ADMs criados.
//        salvarRegistroAdministrador(administrador1);
//        salvarRegistroAdministrador(administrador2);
    printarAdministradorTopicos(administrador1);
    printarAdministradorTopicos(administrador2);
    // Mostrar todos ADMs.
    printarTodosPerfisAdministrador();
    */
    
    // BUSCA DE ADM
    //    struct Administrador adm3;
    //
    //    adm3 = buscarAdministradorPorCod(0);
    //
    //    printf("\n+++++++++++++++++++++\n");
    //    printf("NOME: %s", adm3.nome);
    //    printf("\n+++++++++++++++++++++\n\n");
    //
    //
    //
    //    printarAdministradorTopicos(adm3);
    //    printarAdministradorLista(adm3);
    
    struct Administrador administrador;
    char opcao = 'a';
    int codigo = 0;
    int registro = 0;
    
    if(DELETE_FILES == 1) {
        codigo = remove(BIN_ADM);
    }
    while(opcao != 'x' && opcao != 'X') {


        printf("\n");
        printf("a) INSERIR NOVO ADM\n");
        printf("b) ALTERAR ADM\n");
        printf("c) LISTAR ADMS\n");
        printf("X) SAIR\n");
        printf("OPCAO: ");
        scanf("%c", &opcao); fflush(stdin);

        switch(opcao) {
            case 'a':
            case 'A':
                lerDadosAdministrador(&administrador);
                salvarRegistroAdministrador(administrador);
                printarAdministradorLista(administrador);
                printarAdministradorTopicos(administrador);
                break;

            case 'b':
            case 'B':
                printarTodosPerfisAdministrador();

                printf("INFORME O CODIGO PARA ALTERAR: ");
                scanf("%d", &codigo);

                registro = buscarAdministradorPorCod(codigo);
                alterarAdministrador(registro);
                
                printarMensagemContinuar();
                break;

            case 'c':
            case 'C':
                printarTodosPerfisAdministrador();
                printarMensagemContinuar();
                break;

            case 'x':
            case 'X':
                printf("SAINDO!");
                break;

            default:
                printf("OPCAO INVALIDA!");
        }
    }
    int ultimoCod = acessarUltimoCodigoAdministrador();
    printf("\n\nULTIMO COD: %d\n\n", ultimoCod);
    system("pause");
    
    fclose(ponteiroArquivoADM);
    
    printf("\n\n\n");
    return 0;
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
void abrirArquivos() {
    
// ---------------------------------
// Abrir arquivo em de Administradores
    ponteiroArquivoADM = fopen(BIN_ADM, "r+b"); //tentar abrir
    
    if(ponteiroArquivoADM == NULL){
        ponteiroArquivoADM  = fopen(BIN_ADM, "w+b"); // criar o arquivo
        
        if(ponteiroArquivoADM == NULL){
            if(SHOW_DEBUG == 1) {
                printf("Erro fatal: impossível abrir/criar o arquivo '%s'\n", BIN_ADM);
            }
            
            // Se chegar ate aqui, quer dizer que não conseguiu abrir de jeito nehum...
            // ai encerra o programa 🍃
            exit(1);
        }
    }
    
    //    #define BIN_FUN "vibe_pet-persistencia_func.bin"
    //    #define BIN_CLI "vibe_pet-persistencia_cli.bin"
    //    #define BIN_SER "vibe_pet-persistencia_serv.bin"
    //    #define BIN_TEL "vibe_pet-persistencia_tel.bin"
    //    #define BIN_END "vibe_pet-persistencia_end.bin"
}

// #################################
// SALVAR DADOS DE ADMINISTRADOR
// RETORNO:
//  -    0: se nao houve erros;
//  - != 0: se houve erro(s);
int salvarRegistroAdministrador(struct Administrador administrador) {
    int resultado = 0;
    
    // Adicionar codigo, auto-incrementando,
    // pega o cod_adm do ultimo registro e incrementa.
    administrador.cod_adm = acessarUltimoCodigoAdministrador() + 1;
    
    // Poe o novo administrador no final do arquivo.
    fseek(ponteiroArquivoADM, 0L, SEEK_END);
    if(fwrite(&administrador, sizeof(administrador), 1, ponteiroArquivoADM)!= 1) {
        if(SHOW_DEBUG == 1) {
            printarMensagem("Adicionar administrador: Falhou a escrita do registro");
        }
        
        resultado = 1;
    }
    
    // Retornando o valor do resultado.
    return(resultado);
}


// #################################
// BUSCAR ADM POR CODIGO
// Uma função para retornar o registro (posicao no arquivo) procurando pelo código.
// RETORNO:
//  -  O numero do registro, caso encontre;
//  - -1 caso, nao encontre.
int buscarAdministradorPorCod(int cod) {
    struct Administrador adm;
    int cod_adm = -1;
    
    // Testando se o arquivo foi aberto com sucesso
    if (ponteiroArquivoADM != NULL) {
        if(SHOW_DEBUG == 1) {
            printf("\n\nArquivo %s foi aberto com sucesso\n\n", BIN_ADM);
        }
        
    } else {
        if(SHOW_DEBUG == 1) {
            printf("\n\nERRO: O arquivo %s não foi aberto e criado\n", BIN_ADM);
        }
        system ("pause");
        exit(1);
    }
    
    rewind(ponteiroArquivoADM);
    // Procura em todos os registros do documento.
    while(fread(&adm, sizeof(struct Administrador), 1, ponteiroArquivoADM)) {
        // Incrementa ++ porque comeca com -1.
        cod_adm += 1;
        
        // Compara o cod recebido.
        if(adm.cod_adm == cod) {
            // Se encontrar, retorna a poisicao(linha) do registro.
            return  cod_adm;
        }
    }
    
    // Se não achar o codigo, retorna -1 para indicar que nao achou.
    if(SHOW_DEBUG == 1) {
        printf("\n\nERRO: registro nao encontrado.");
    }
    cod_adm = -1;
    
    return cod_adm;
}

// #################################
// BUSCAR CODIGO DO ULTIMO REGISTRO
// Uma função para ir ate o ultimo registro, ultimo administrador cadastrado e
// retorna seu respectivo codigo.
// RETORNO:
//  - O int do cod_adm.
int acessarUltimoCodigoAdministrador() {
    struct Administrador administrador;
    
    fseek(ponteiroArquivoADM, -1 * sizeof(struct Administrador), SEEK_END);
    if(fread(&administrador, sizeof(struct Administrador), -1, ponteiroArquivoADM)!= 1){
        printarMensagem("Problemas na leitura do registro!!!");
        return -1;
    }
    
    if(administrador.cod_adm <= -1){
        return 0;
        
    } else {
        return administrador.cod_adm;
    }
}



// #################################
// PRINTAR UM PERFIL DE ADM:
// mostra na tela os dados existentes no registro
void printarAdministradorLista(struct Administrador administrador) {
    //TODO: criar View de perfil ADM.
    
    //    printf("-----------------------------------------------------------------------------------\n");
    printf("%05d|%-30s|%-15s|%-30s\n", administrador.cod_adm, administrador.nome, administrador.cpf, administrador.senha);
    //    printf("-----------------------------------------------------------------------------------\n");
}

void printarAdministradorTopicos(struct Administrador administrador) {
    
    if(administrador.ativo == ' ') {
        printf("%-6s: %d\n", "CODIGO", administrador.cod_adm);
        printf("%-6s: %s\n", "NOME", administrador.nome);
        printf("%-6s: %s\n", "CPF", administrador.cpf);
        printf("%-6s: %s\n", "SENHA", administrador.senha);
        if(administrador.cargo == 1) {
            printf("%-6s: %s\n", "CARGO", "Funcionario");
            
        } else if(administrador.cargo == 0) {
            printf("%-6s: %s\n", "CARGO", "Administrador");
        }
        
    } else {
        printf("\nFUNCIONARIO DELETADO!\n");
    }
}

// #################################
// LER TODOS PERFIS DE ADM
void printarTodosPerfisAdministrador() {
    struct Administrador administrador;
    int n_Linhas = 0;
    
    // Volta o ponteiro para o inicio.
    rewind(ponteiroArquivoADM);
    
    printf("ADMINISTRADORES\n");
    printf("-----------------------------------------------------------------------------------\n");
    printf("%-5s|%-30s|%-15s|%-30s\n", "COD", "NOME", "CPF", "SENHA");
    printf("-----------------------------------------------------------------------------------\n");
    
    while(1){
        if(fread(&administrador, sizeof(administrador), 1, ponteiroArquivoADM)!= 1)break; /*Sair do laço*/
        if(administrador.ativo == '*') continue; /*Passa ao próximo*/
        printarAdministradorLista(administrador);
//        printarAdministradorTopicos(administrador);
        n_Linhas++;
        if(n_Linhas%20 == 0)
            printarMensagem("Pressione <Enter> para continuar .  .  .");
    }
//    printf("\n\n\n");
    
}


//TODO: ⚠️ FALTA O RESTANTE DO CRUD ⚠️



// #################################
// ALTERAR UM PERFIL DE ADM
void alterarAdministrador(int registro) {
    struct Administrador administradorAux;
    
    if(fseek(ponteiroArquivoADM, (registro)*sizeof(administradorAux), SEEK_SET) != 0){
        printarMensagem("Registro inexistente ou problemas no posicionamento!!!");
        return;
    }
    
    if(fread(&administradorAux, sizeof(struct Administrador), 1, ponteiroArquivoADM)!= 1){
        printarMensagem("Problemas na leitura do registro!!!");
        return;
    }
   
    if(administradorAux.ativo == '*'){
        printarMensagem("Um registro apagado não pode ser alterado!!! \n\n");
        return;
    }
    
       
    printf("\n\n Dados Atuais \n\n");
    printarAdministradorTopicos(administradorAux);
    
    printf("\n\n Novos dados \n\n");
    lerDadosAdministrador(&administradorAux);
    
    // recuar um registro no arquivo
    fseek(ponteiroArquivoADM, -(int) sizeof(struct Administrador), SEEK_CUR);
    // reescrever o registro;
    fwrite(&administradorAux, sizeof(struct Administrador), 1, ponteiroArquivoADM);
    fflush(ponteiroArquivoADM); /*despejar os arquivos no disco rígido*/
}

// #################################
// DELETAR UM PERFIL DE ADM




// #############################################################################
// AUXILIARES
// printar adm





/* EXEMPLO DE GRAVAÇÃO DE ARQUIVO BIN
 
 char ch [15] = "Teste geral";
 int valor [15] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
 int i=0;
 FILE *ponteiroArquivoADM;
 
 ponteiroArquivoADM = fopen ("binario.bin", "wb"); //Se nao abriu, cria.
 
 if (ponteiroArquivoADM!=NULL)
 printf("\n\nArquivo binario.bin foi aberto com sucesso\n");
 else
 {
 printf("\n\nErro: O arquivo binario.bin nao foi aberto\n");
 system ("pause");
 exit (0);
 }
 
 //Gravando os dados no arquivo usando a funcao fwrite
 fwrite(ch, sizeof (char), 15, ponteiroArquivoADM);
 fwrite(valor, sizeof(int), 15, ponteiroArquivoADM);
 
 //fechando o arquivo
 fclose(ponteiroArquivoADM);
 */




/* EXEMPLO DE LEITURA DE ARQUIVO BIN
 
 char ch [15] = "Teste geral";
 int valor [15] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
 int i=0;
 FILE *ponteiroArquivoADM;
 
 
 
 //abertura do arquivo
 ponteiroArquivoADM = fopen("binario.bin","rb");
 
 //testando se o arquivo foi aberto com sucesso
 if (ponteiroArquivoADM != NULL) {
 printf("\n\nArquivo binario.bin foi aberto com sucesso\n\n");
 
 } else {
 printf("\n\nERRO: O arquivo binario.bin nao foi aberto e criado\n");
 system ("pause");
 exit (1);
 }
 
 //leitura do arquivo binario
 //Sintaxe: fread(&variavel, num_bytes, num_registros, arquivo);
 
 //retorna o conteudo contido em uma ocorrencia do tamanho da variavel ch.
 fread(ch, sizeof(ch),1,ponteiroArquivoADM);
 
 //retorna o conteudo contido em uma ocorrencia do tamanho da variavel valor->
 fread(valor,sizeof(valor),1,ponteiroArquivoADM);
 
 printf("Vetor de caracteres: \n");
 
 for(i = 0; i < 15; i++)
 {
 printf("%c",ch[i]);
 }
 
 printf("\nVetor de inteiros: ");
 
 for(i = 0; i < 15; i++)
 {
 printf("\n%d",valor[i]);
 }
 
 //fechando o arquivo
 fclose(ponteiroArquivoADM);
 
 */



// #############################################################################
// FUNCOES AUXILIARES


/*Colocar uma mensagem na tela*/
//TODO: COLOCAR ALINHAMENTO: esq, dir, centralizado.
void printarMensagem(char *msg){
    printf("%-80s", msg);
    getchar();
}

void printarMensagemContinuar() {
    printf("%-80s", "\n\n Pressione <Enter> para continuar . . .");
    getchar();
}

// #################################
// LER OS DADOS DE ADMINISTRADOR
void lerDadosAdministrador(struct Administrador *administrador) {
    
    fflush(stdin);
    printf("Nome : ");
    gets(administrador->nome);
    fflush(stdin);
    
    printf("CPF  : ");
    gets(administrador->cpf);
    fflush(stdin);
    
    printf("Senha: ");
    gets(administrador->senha);
    fflush(stdin);
    
    printf("Cargo: ");
    scanf("%d", &administrador->cargo); // Funcionario 0 = adm
    fflush(stdin);
    
    administrador->ativo = ' '; // Qualquer coisa menos '*' significa ativo
    administrador->cod_adm = 0;
}
