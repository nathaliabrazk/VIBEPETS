//
//  main.c
//  VIBEPETS
//
//  Created by Nathália Braz on 24/09/22.
//

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
//#include <curses.h>

// PROTOTIPOS

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
    // Criando a variável ponteiro para o arquivo
    FILE *pont_arq;
    char palavra[20]; // variável do tipo string
    char c;
    int r;
    char texto_str[20];

    // Abrindo o arquivo
    pont_arq = fopen("arquivo.txt", "a");
    
    //testando se o arquivo foi realmente criado
    if(pont_arq == NULL) {
        printf("Erro na abertura do arquivo!");
        return 1;
    }
    
    printf("Escreva uma palavra para testar gravacao de arquivo: ");
    scanf("%s", palavra);
    
    //usando fprintf para armazenar a string no arquivo
    fprintf(pont_arq, "%s", palavra);
    
    
    //Gravando strings no arquivo
//    r = fputs("Programando em Linguagem C.", pont_arq);
    
    //Verificando se os dados foram gravados com sucesso
    if( r == EOF) {
        printf("Erro ao tentar gravar os dados! \n");
    } else {
        printf("Dados gravados com sucesso!\n\n");
    }
    
    
    //usando fclose para fechar o arquivo
    fclose(pont_arq);
    
    pont_arq = fopen("arquivo.txt","r");
    
    while(fgets(texto_str, 20, pont_arq) != NULL)
    printf("%s", texto_str);
    
    
    
    
    
    
    //usando fclose para fechar o arquivo
    fclose(pont_arq);
    
    system("pause");
    
    return 0;
}

//PERSISTENCIA EM XML

