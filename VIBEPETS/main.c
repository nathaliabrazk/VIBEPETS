//
//  main.c
//  VIBEPETS
//
//  Created by Nathália Braz on 24/09/22.
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



// #############################################################################
// CONSTANTES
#define BIN_ADM "vibe_pet-persistencia_adm.bin"
#define BIN_FUN "vibe_pet-persistencia_func.bin"
#define BIN_CLI "vibe_pet-persistencia_cli.bin"
#define BIN_SER "vibe_pet-persistencia_serv.bin"
#define BIN_TEL "vibe_pet-persistencia_tel.bin"
#define BIN_END "vibe_pet-persistencia_end.bin"

// 1 = Mostra || 0 = Esconde => Printa ou não coisas na tela, msg de erro e etc.
#define SHOW_DEBUG 0


// #############################################################################
// PROTOTIPOS
int salvarPerfilAdministrador(struct Administrador);
void printarTodosPerfisAdministrador(void);
struct Administrador buscarAdministradorPorCod(int);

int main(int argc, char *argv[]) {
    setlocale (LC_ALL, "");
    // Propriedades
    /*
     char nome[50], email[50], opcao;
     int  dia, mes, ano, endereco, cpf, tel;
     
     // Entradas
     
     printf("Digite o nome: ");
     scanf("%s", nome);
     printf("Digite email: ");
     scanf("%s", email);
     printf("Digite o dia: ");
     scanf("%d", &dia);
     
     
     // Processamento
     
     
     // Saida
     printf("O nome digitado e: %s", nome);
     printf("O email digitado e: %s", email);
     
     scanf("O dia digitado foi:  %d", &dia);
     
     printf ("Escolha os produtos que deseja da linha para o dia de Spa do seu pet\n");
     printf ("Escolha o Shampoo para seu pet:\n");
     printf ("A- Shampoo Pré-Banho Pelôncio \nB- Shampoo Pelos Claros Pelôncio \nC- Shampoo Pelos Escuros Pelôncio \nFragrâncias:	Avelã - Melância - Dove - Morango\n");
     printf ("Opção:\n");
     scanf ("%s", &opcao);
     fflush (stdin);
     system ("cls");
     
     switch (opcao) {
     case 'A':
     case 'a':
     printf ("Você escolheu  Shampoo Pré-Banho Pelôncio\n");
     break;
     case 'B':
     case 'b':
     printf ("Você escolheu Shampoo Pelos Claros Pelôncio\n");
     break;
     case 'C':
     case 'c':
     printf ("Você escolheu Shampoo Pelos Escuros Pelôncio\n");
     break;
     default:
     printf ("Opção inválida");
     }
     
     printf ("Escolha a fragrância do Condicionador para seu pet:\n");
     printf ("A-Avelã \nB- Melância \nC- Morango\n");
     printf ("Opção:\n");
     scanf ("%c", &opcao);
     fflush (stdin);
     system ("cls");
     
     switch (opcao) {
     case 'A':
     case 'a':
     printf ("Você escolheu Avelã\n");
     break;
     case 'B':
     case 'b':
     printf ("Você escolheu Melância\n");
     break;
     case 'C':
     case 'c':
     printf ("Você escolheu Morango\n");
     break;
     default:
     
     printf ("Opção inválida");
     }
     printf ("Escolha a colônia Perfume Pet Clean Max para seu pet:\n");
     printf ("A-  Amêndoas e Ameixa \nB- Avelã e Cereja \nC- Melancia\n");
     printf ("Opção:\n");
     scanf ("%c", &opcao);
     fflush (stdin);
     system ("cls");
     
     switch (opcao)
     {
     case 'A':
     case 'a':
     printf ("Você escolheu Amêndoas e Ameixa\n");
     break;
     case 'B':
     case 'b':
     printf ("Você escolheu Avelã e Cereja\n");
     break;
     case 'C':
     case 'c':
     printf ("Você escolheu Melância\n");
     break;
     default:
     printf ("Opção inválida");
     }
     */
    
    char nome[50] = "Luiz";
    

    
    // Criar um ADM.
    struct Administrador adm1;
    adm1.cod_adm = 0;
    strcpy(adm1.nome, "admin");
    strcpy(adm1.cpf, "01234567890");
    strcpy(adm1.senha, "admin123");
    
    // Criar outro ADM.
    struct Administrador adm2;
    adm2.cod_adm = 1;
    adm2.cargo = 1; // Funcionario 0 = adm
    adm2.ativo = 1;
    strcpy(adm2.nome, "Carlos");
    strcpy(adm2.cpf, "01234567890");
    strcpy(adm2.senha, "admin123");
    
    
    // Persistir os ADMs criados.
//    salvarPerfilAdministrador(adm1);
//    salvarPerfilAdministrador(adm2);

    // Mostrar todos ADMs.
//    printarTodosPerfisAdministrador();
    
    
    // BUSCA DE ADM
    struct Administrador adm3;
    
    adm3 = buscarAdministradorPorCod(0);
    
    printf("\n+++++++++++++++++++++\n");
    printf("NOME: %s", adm3.nome);
    printf("\n+++++++++++++++++++++\n\n");
    
    
    
    
    
    system("pause");
    
    return 0;
}


// #############################################################################
// PERSISTENCIA EM BIN

// #################################
// SALVAR PERFIL DE ADMINISTRADOR
// RETORNO:
//  - 0    : se não houve erros;
//  - != 0 : se houve erro(s);
int salvarPerfilAdministrador(struct Administrador adm) {
    int resultado = 0;
    
    // Ponteiro para encontrar o arquivo a ser manipulado.
    FILE *ptrArq;
    
    //Se não abriu, cria.
    ptrArq = fopen (BIN_ADM, "ab");
    
    // Verifica se o arquivo abriu.
    if (ptrArq != NULL) {
        if(SHOW_DEBUG == 1) {
            printf ("\n\nArquivo %s foi aberto com sucesso\n", BIN_ADM);
        }
        
    } else {
        // Se não abriu, troca para 1 que significa erro.
        resultado = 1;
        
        // Mostra a mensagem de erro.
        if(SHOW_DEBUG == 1) {
            printf ("\n\nErro: O arquivo %s não foi aberto\n", BIN_ADM);
            system ("pause");
        }
        // Retorna o erro.
        return(resultado);
    }
    
    //Gravando os dados no arquivo usando a função fwrite
    fwrite(&adm, sizeof(struct Administrador), 1, ptrArq);
    
    // Fechando o arquivo
    fclose(ptrArq);
    
    // Retornando o valor do resultado.
    return(resultado);
}

// #################################
// LER TODOS PERFIS DE ADM
void printarTodosPerfisAdministrador() {
    struct Administrador adm;
    
    // Ponteiro para encontrar o arquivo a ser manipulado.
    FILE *ptrArq;
    
    //abertura do arquivo
    ptrArq = fopen(BIN_ADM,"rb");
    
    // Testando se o arquivo foi aberto com sucesso
    if (ptrArq != NULL) {
        if(SHOW_DEBUG == 1) {
            printf ("\n\nArquivo %s foi aberto com sucesso\n\n", BIN_ADM);
        }
        
    } else {
        if(SHOW_DEBUG == 1) {
            printf ("\n\nERRO: O arquivo %s não foi aberto e criado\n", BIN_ADM);
        }
        system ("pause");
        exit (1);
    }
    
    // Leitura do arquivo binário
    // Sintaxe: fread(&variavel, num_bytes, num_registros, arquivo);
    printf("ADMINISTRADORES\n");
    printf("-----------------------------------------------------------------------------------\n");
    printf ("%-5s|%-30s|%-15s|%-30s\n", "COD", "NOME", "CPF", "SENHA");
    printf("-----------------------------------------------------------------------------------\n");

    while(fread(&adm, sizeof(struct Administrador), 1, ptrArq)) {
        printf ("%05d|%-30s|%-15s|%-30s\n", adm.cod_adm, adm.nome, adm.cpf, adm.senha);
    }

    // Fechando o arquivo
    fclose(ptrArq);
}


//TODO: ⚠️ FALTA O RESTANTE DO CRUD ⚠️


// #################################
// BUSCAR ADM POR CODIGO
// RETORNO:
//  - struct Administrador
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
            printf ("\n\nArquivo %s foi aberto com sucesso\n\n", BIN_ADM);
        }
        
    } else {
        if(SHOW_DEBUG == 1) {
            printf ("\n\nERRO: O arquivo %s não foi aberto e criado\n", BIN_ADM);
        }
        system ("pause");
        exit(1);
    }
    
    // Procura em todos os registros do documento.
    while(fread(&adm, sizeof(struct Administrador), 1, ptrArq)) {
        // Compara o cod recebido.
        if(adm.cod_adm == cod) {
            if(SHOW_DEBUG == 1) {
                printf ("\n\nAdministrador encontrado com sucesso.\n\n");
            }
            return adm;
        }
    }

    // Fechando o arquivo
    fclose(ptrArq);
    
    return adm;
}

// #################################
// PRINTAR UM PERFIL DE ADM
void printarAdministrador(struct Administrador adm) {
    //TODO: criar View de perfil ADM.
}

// #################################
// ALTERAR UM PERFIL DE ADM

// #################################
// DELETAR UM PERFIL DE ADM






// #############################################################################
// AUXILIARES
// printar adm





/* EXEMPLO DE GRAVAÇÃO DE ARQUIVO BIN
 
 char ch [15] = "Teste geral";
 int valor [15] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
 int i=0;
 FILE *ptrArq;
 
 ptrArq = fopen ("binario.bin", "wb"); //Se não abriu, cria.
 
 if (ptrArq!=NULL)
     printf ("\n\nArquivo binario.bin foi aberto com sucesso\n");
 else
 {
     printf ("\n\nErro: O arquivo binario.bin não foi aberto\n");
     system ("pause");
     exit (0);
 }
 
 //Gravando os dados no arquivo usando a função fwrite
 fwrite(ch, sizeof (char), 15, ptrArq);
 fwrite(valor, sizeof(int), 15, ptrArq);
 
 //fechando o arquivo
 fclose(ptrArq);
 */




/* EXEMPLO DE LEITURA DE ARQUIVO BIN
 
 char ch [15] = "Teste geral";
 int valor [15] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
 int i=0;
 FILE *ptrArq;
 
 
 
 //abertura do arquivo
 ptrArq = fopen("binario.bin","rb");
 
 //testando se o arquivo foi aberto com sucesso
 if (ptrArq != NULL) {
 printf ("\n\nArquivo binario.bin foi aberto com sucesso\n\n");
 
 } else {
 printf ("\n\nERRO: O arquivo binario.bin não foi aberto e criado\n");
 system ("pause");
 exit (1);
 }
 
 //leitura do arquivo binário
 //Sintaxe: fread(&variavel, num_bytes, num_registros, arquivo);
 
 //retorna o conteúdo contido em uma ocorrência do tamanho da variável ch.
 fread(ch, sizeof(ch),1,ptrArq);
 
 //retorna o conteúdo contido em uma ocorrência do tamanho da variável valor.
 fread(valor,sizeof(valor),1,ptrArq);
 
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
 fclose(ptrArq);
 
 */
