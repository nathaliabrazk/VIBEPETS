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
    fwrite (ch, sizeof (char), 15, ptrArq);
    fwrite (valor, sizeof(int), 15, ptrArq);
    
    //fechando o arquivo
    fclose(ptrArq);
    

    // Leitura
    
    
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
    
    
    
    system("pause");
    
    return 0;
}

//PERSISTENCIA EM XML

