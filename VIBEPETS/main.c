//
//  main.c
//  VIBEPETS
//
//  Created by Nath�lia Braz on 24/09/22.
//

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

// #############################################################################
// DECLARACAO DE TIPOS

struct Administrador {
    int cod_adm;
    char nome[50];
    char cpf[12];
    char senha[25];
    int cargo;      // 0 = admin || 1 = funcionario
    int ativo;      // 0 = inativo/deletado || 1 = ativo / funcionando
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
};


// #############################################################################
// CONSTANTES
#define BIN_ADM "vibe_pet-persistencia_adm.bin"
#define BIN_FUN "vibe_pet-persistencia_func.bin"
#define BIN_CLI "vibe_pet-persistencia_cli.bin"
#define BIN_SER "vibe_pet-persistencia_serv.bin"
#define BIN_TEL "vibe_pet-persistencia_tel.bin"
#define BIN_END "vibe_pet-persistencia_end.bin"

// 1 = Mostra || 0 = Esconde => Printa ou nao coisas na tela, msg de erro e etc.
#define SHOW_DEBUG 1


// #############################################################################
// PROTOTIPOS
int salvarPerfilAdministrador(struct Administrador);
void printarTodosPerfisAdministrador(void);
void printarAdministradorLista(struct Administrador);
void printarAdministradorTopicos(struct Administrador);
struct Administrador buscarAdministradorPorCod(int);
int alterarAdministrador(struct Administrador administrador);


int main(int argc, char *argv[]) {
    setlocale (LC_ALL, "");
    
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
    
    
    
    // Criar um ADM.
    struct Administrador administrador1;
    administrador1.cod_adm = 0;
    strcpy(administrador1.nome, "administrador1");
    strcpy(administrador1.cpf, "01234567890");
    strcpy(administrador1.senha, "administrador123");
    administrador1.cargo = 0; // Funcionario 0 = adm
    administrador1.ativo = 1;
    
    // Criar outro ADM.
    struct Administrador administrador2;
    administrador2.cod_adm = 0;
    administrador2.cargo = 1; // Funcionario 0 = adm
    administrador2.ativo = 1;
    strcpy(administrador2.nome, "Carlos2");
    strcpy(administrador2.cpf, "01234567890");
    strcpy(administrador2.senha, "administrador123");
    
    
    
    // Persistir os ADMs criados.
//        salvarPerfilAdministrador(administrador1);
//        salvarPerfilAdministrador(administrador2);
    printarAdministradorTopicos(administrador1);
    printarAdministradorTopicos(administrador2);
    // Mostrar todos ADMs.
    printarTodosPerfisAdministrador();
    
    
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
    
    
    system("pause");
    
    return 0;
}


// #############################################################################
// PERSISTENCIA EM BIN

// #################################
// SALVAR PERFIL DE ADMINISTRADOR
// RETORNO:
//  - 0 : se nao houve erros;
//  - !=: se houve erro(s);
int salvarPerfilAdministrador(struct Administrador administrador) {
    int resultado = 0;
    
    // Ponteiro para encontrar o arquivo a ser manipulado.
    FILE *ponteiroArquivo;
    
    //Se não abriu, cria.
    ponteiroArquivo = fopen (BIN_ADM, "ab");
    
    // Verifica se o arquivo abriu.
    if (ponteiroArquivo != NULL) {
        if(SHOW_DEBUG == 1) {
            printf("\n\nArquivo %s foi aberto com sucesso\n", BIN_ADM);
        }
        
    } else {
        // Se nao abriu, troca para 1 que significa erro.
        resultado = 1;
        
        // Mostra a mensagem de erro.
        if(SHOW_DEBUG == 1) {
            printf("\n\nErro: O arquivo %s nao foi aberto\n", BIN_ADM);
            system ("pause");
        }
        // Retorna o erro.
        return(resultado);
    }
    
    //Gravando os dados no arquivo usando a funcao fwrite
    fwrite(&administrador, sizeof(struct Administrador), 1, ponteiroArquivo);
    
    // Fechando o arquivo
    fclose(ponteiroArquivo);
    
    // Retornando o valor do resultado.
    return(resultado);
}

// #################################
// LER TODOS PERFIS DE ADM
void printarTodosPerfisAdministrador() {
    struct Administrador administrador;
    
    // Ponteiro para encontrar o arquivo a ser manipulado.
    FILE *ponteiroArquivo;
    
    //abertura do arquivo
    ponteiroArquivo = fopen(BIN_ADM,"rb");
    
    // Testando se o arquivo foi aberto com sucesso
    if (ponteiroArquivo != NULL) {
        if(SHOW_DEBUG == 1) {
            printf("\n\nArquivo %s foi aberto com sucesso\n\n", BIN_ADM);
        }
        
    } else {
        if(SHOW_DEBUG == 1) {
            printf("\n\nERRO: O arquivo %s nao foi aberto e criado\n", BIN_ADM);
        }
        system ("pause");
        exit (1);
    }
    
    // Leitura do arquivo binario
    // Sintaxe: fread(&variavel, num_bytes, num_registros, arquivo);
    printf("ADMINISTRADORES\n");
    printf("-----------------------------------------------------------------------------------\n");
    printf("%-5s|%-30s|%-15s|%-30s\n", "COD", "NOME", "CPF", "SENHA");
    printf("-----------------------------------------------------------------------------------\n");
    
    while(fread(&administrador, sizeof(struct Administrador), 1, ponteiroArquivo))
        printarAdministradorLista(administrador);
    
    printf("\n\n\n");
    
    // Fechando o arquivo
    fclose(ponteiroArquivo);
}


//TODO: ⚠️ FALTA O RESTANTE DO CRUD ⚠️



// #################################
// BUSCAR ADM POR CODIGO
// Uma função para retornar Administrador procurando pelo código.
// RETORNO:
//  - encontrado: instancia com dados encontrados;
//  - não encontrado: instancia com cod = -1;
struct Administrador buscarAdministradorPorCod(int cod) {
    struct Administrador adm;
    adm.cod_adm = -1;
    adm.ativo = 0;
    
    // Ponteiro para encontrar o arquivo a ser manipulado.
    FILE *ptrArq;
    
    //abertura do arquivo
    ptrArq = fopen(BIN_ADM, "rb");
    
    // Testando se o arquivo foi aberto com sucesso
    if (ptrArq != NULL) {
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
    
    // Procura em todos os registros do documento.
    while(fread(&adm, sizeof(struct Administrador), 1, ptrArq)) {
        // Compara o cod recebido.
        if(adm.cod_adm == cod) {
            if(SHOW_DEBUG == 1) {
                printf("\n\nAdministrador encontrado com sucesso.\n\n");
            }
            adm.ativo = 1;
            return adm;
        }
    }
    
    // Fechando o arquivo
    fclose(ptrArq);
    
    return adm;
}

// #################################
// PRINTAR UM PERFIL DE ADM
void printarAdministradorLista(struct Administrador administrador) {
    //TODO: criar View de perfil ADM.
    
    //    printf("-----------------------------------------------------------------------------------\n");
    printf("%05d|%-30s|%-15s|%-30s\n", administrador.cod_adm, administrador.nome, administrador.cpf, administrador.senha);
    //    printf("-----------------------------------------------------------------------------------\n");
}

void printarAdministradorTopicos(struct Administrador administrador) {
    if(administrador.ativo == 1) {
        printf("%-6d: %d\n", "CODIGO", administrador.cod_adm);
        printf("%-6s: %s\n", "NOME", administrador.nome);
        printf("%-6s: %s\n", "CPF", administrador.cpf);
        printf("%-6s: %s\n", "SENHA", administrador.senha);
        if(administrador.cargo == 1) {
            printf("%-6s: %s\n", "CARGO", "Funcionário");
            
        } else if(administrador.cargo == 0) {
            printf("%-6s: %s\n", "CARGO", "Administrador");
        }
        
    } else {
        printf("\nFUNCIONÁRIO DELETADO!\n");
    }
}
// #################################
// ALTERAR UM PERFIL DE ADM
int alterarAdministrador(struct Administrador administrador) {
    struct Administrador administradorAux;
    int count = 0;
    // Ponteiro para encontrar o arquivo a ser manipulado.
    FILE *ptrArq;
    
    //abertura do arquivo
    ptrArq = fopen(BIN_ADM, "rb");
    
    while(!feof(ptrArq)){
        fread(&administradorAux, sizeof(struct Administrador), 1, ptrArq);
        if(administradorAux.cod_adm != administrador.cod_adm) {
            count += 1;
        }
    }
    
    fclose(ptrArq);
    
    
    
    
    
    
    // Ponteiro para encontrar o arquivo a ser manipulado.
    FILE *ponteiroArquivo;
    
    //Se não abriu, cria.
    ponteiroArquivo = fopen (BIN_ADM, "ab");
    
    // Verifica se o arquivo abriu.
    if (ponteiroArquivo != NULL) {
        if(SHOW_DEBUG == 1) {
            printf("\n\nArquivo %s foi aberto com sucesso\n", BIN_ADM);
        }
        
    } else {
        
        // Mostra a mensagem de erro.
        if(SHOW_DEBUG == 1) {
            printf("\n\nErro: O arquivo %s nao foi aberto\n", BIN_ADM);
            system ("pause");
        }
    }
    
    //Gravando os dados no arquivo usando a funcao fwrite
    fwrite(&administrador, sizeof(struct Administrador), count, ponteiroArquivo);
    
    // Fechando o arquivo
    fclose(ponteiroArquivo);
    
    return 1;
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
 FILE *ponteiroArquivo;
 
 ponteiroArquivo = fopen ("binario.bin", "wb"); //Se nao abriu, cria.
 
 if (ponteiroArquivo!=NULL)
 printf("\n\nArquivo binario.bin foi aberto com sucesso\n");
 else
 {
 printf("\n\nErro: O arquivo binario.bin nao foi aberto\n");
 system ("pause");
 exit (0);
 }
 
 //Gravando os dados no arquivo usando a funcao fwrite
 fwrite(ch, sizeof (char), 15, ponteiroArquivo);
 fwrite(valor, sizeof(int), 15, ponteiroArquivo);
 
 //fechando o arquivo
 fclose(ponteiroArquivo);
 */




/* EXEMPLO DE LEITURA DE ARQUIVO BIN
 
 char ch [15] = "Teste geral";
 int valor [15] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
 int i=0;
 FILE *ponteiroArquivo;
 
 
 
 //abertura do arquivo
 ponteiroArquivo = fopen("binario.bin","rb");
 
 //testando se o arquivo foi aberto com sucesso
 if (ponteiroArquivo != NULL) {
 printf("\n\nArquivo binario.bin foi aberto com sucesso\n\n");
 
 } else {
 printf("\n\nERRO: O arquivo binario.bin nao foi aberto e criado\n");
 system ("pause");
 exit (1);
 }
 
 //leitura do arquivo binario
 //Sintaxe: fread(&variavel, num_bytes, num_registros, arquivo);
 
 //retorna o conteudo contido em uma ocorrencia do tamanho da variavel ch.
 fread(ch, sizeof(ch),1,ponteiroArquivo);
 
 //retorna o conteudo contido em uma ocorrencia do tamanho da variavel valor.
 fread(valor,sizeof(valor),1,ponteiroArquivo);
 
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
 fclose(ponteiroArquivo);
 
 */

