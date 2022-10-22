//
//  main.c
//  VIBEPETS
//
//  Created by NathÃ¡lia Braz on 24/09/22.
//

#include <stdio.h>
#include <stdlib.h>
#include <locale.h> 


int main(int argc, char *argv[]) {
    setlocale (LC_ALL, "");
    // Propriedades
    char nome[50], email[50], opcao;
    int  dia, mes, ano, endereco, cpf, tel;
    
    // Entradas
    
    /*printf("Digite o nome: ");
     scanf("%s", nome);
     printf("Digite email: ");
     scanf("%s", email);*/
    printf("Digite o dia: ");
    scanf("%d", &dia);
    
    
    // Processamento
    
    
    // Saida
    /*printf("O nome digitado e: %s", nome);
     printf("O email digitado e: %s", email);*/
    scanf("O dia digitado foi:  %d", &dia);
    
    printf("Escolha um dos nossos servicos!\n ");
    printf("OBSERVACO (SO PODE SER ESCOLHIDO UM COMBO DE SERVICO POR DIA E POR PET)\n");
    printf("A)------------------------------------------------------------------\n");
    printf("\t- Tosa e banho\n");
    printf("\t- Shampoo Banho de Carinho Petz\n");
    printf("\t- Condicionador Chegou o Brincalhao Petz\n");
    printf("\t- Colonia Hydra Groomers Forevers\n");
    printf("\t- Creme Hidratante de Patinhas\n");
    printf("\t- Vela Aromatica Perfumada | Lavanda\n");
    printf("|VALOR: 100,00|\n");
    
    printf("B)------------------------------------------------------------------\n");
    printf("\t-Tosa e banho\n");
    printf("\t-Shampoo Pet Society Neutro\n");
    printf("\t-Condicionador Pet Society\n");
    printf("\t-Colonia Pet Society Lovely\n");
    printf("\t-Creme hidrantante Pet Society Lovely\n");
    printf("\t-Vela Aromatica Perfumada| Canela\n");
    printf("|VALOR: 90,00|\n");
   printf("C)------------------------------------------------------------------\n");
    printf("\t-Tosa e banho\n");
    printf("\t-Shampoo Matacura Sarnicida e Anti-Pulgas\n");
    printf("\t-Condicionador Matacura Sarnicida e Anti-Pulgas\n");
    printf("\t-Perfume Ibasa de Colonia Affection para Caes e Gatos\n");
    printf("\t-Creme Hidratante Equilibrio Hidrapet\n");
    printf("Vela Aromatica Perfumada | Baunilha\n");
    printf("|VALOR: 80,00|\n");
    printf ("OPCAO: ");
    scanf ("%c", &opcao);
    fflush (stdin);
    system ("cls");
    
    switch (opcao) {
        case 'A':
        case 'a':
            printf ("Voce escolheu o combo (A)\n");
            printf("\t-Tosa e banho\n");
            printf("\t-Shampoo Banho de Carinho Petz\n");
            printf("\t-Condicionador Chegou o Brincalhao Petz\n");
            printf("\t-Colonia Hydra Groomers Forevers\n");
            printf("\t-Creme Hidratante de Patinhas\n");
            printf("\t-Vela Aromatica Perfumada | Lavanda\n");
            printf("|VALOR: 100,00|\n");
            break;
        case 'B':
        case 'b':
            printf("Voce escolheu o combo (B)\n");
            printf("\t-Tosa e banho\n-Shampoo Pet Society Neutro\n");
            printf("\t-Condicionador Pet Society\n-Colonia Pet Society Lovely\n");
            printf("\t-Creme hidrantante Pet Society Lovely\n");
            printf("\t-Vela Aromatica Perfumada| Canela\n");
            printf("|VALOR: 90,00|\n");
            break;
        case 'C':
        case 'c':
            printf("Voce escolheu o combo (C)\n");
            printf("\t-Tosa e banho\n");
            printf("\t-Shampoo Matacura Sarnicida e Anti-Pulgas\n");
            printf("\t-Condicionador Matacura Sarnicida e Anti-Pulgas\n");
            printf("\t-Perfume Ibasa de Colonia Affection para Caes e Gatos\n");
            printf("\t-Creme Hidratante Equilibrio Hidrapet\n");
            printf("\tVela Aromatica Perfumada | Baunilha\n");
            printf("|VALOR: 80,00|\n");
            break;
        default:
            printf ("OPCAO INVALIDA");
    }
    
    return 0;
}
