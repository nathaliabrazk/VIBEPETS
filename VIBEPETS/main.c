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
    
printf ("Escolha um dos nossos servicos!\n "); 
	printf ("OBSERVA��O (S� PODE SER ESCOLHIDO UM COMBO DE SERVI�O POR DIA E POR PET)\n");
	printf ("A)------------------------------------------------------------------\n-Tosa e banho\n-Shampoo Banho de Carinho Petz\n-Condicionador Chegou o Brincalh�o Petz\n-Col�nia Hydra Groomers Forevers\n-Creme Hidratante de Patinhas\n-Vela Arom�tica Perfumada | Lavanda\n|VALOR: 100,00|\nB)------------------------------------------------------------------\n-Tosa e banho\n-Shampoo Pet Society Neutro\n-Condicionador Pet Society\n-Col�nia Pet Society Lovely\n-Creme hidrantante Pet Society Lovely\n-Vela Arom�tica Perfumada| Canela\n|VALOR: 90,00|\nC)------------------------------------------------------------------\n-Tosa e banho\n-Shampoo Matacura Sarnicida e Anti-Pulgas\n-Condicionador Matacura Sarnicida e Anti-Pulgas\n-Perfume Ibasa de Col�nia Affection para C�es e Gatos\n-Creme Hidratante Equil�brio Hidrapet\nVela Arom�tica Perfumada | Baunilha\n|VALOR: 80,00|\n"); 
	printf ("OPCAO:\n"); 
	scanf ("%s", &opcao); 
	fflush (stdin); 
	system ("cls"); 
	  
	switch (opcao) 
	
	{ 
	case 'A':  
	case 'a': 
	printf ("Voce escolheu o combo (A)\n-Tosa e banho\n-Shampoo Banho de Carinho Petz\n-Condicionador Chegou o Brincalh�o Petz\n-Col�nia Hydra Groomers Forevers\n-Creme Hidratante de Patinhas\n-Vela Arom�tica Perfumada | Lavanda\n|VALOR: 100,00|\n"); 
	break; 
	case 'B': 
	case 'b': 
	printf ("Voce escolheu o combo (B)\n-Tosa e banho\n-Shampoo Pet Society Neutro\n-Condicionador Pet Society\n-Col�nia Pet Society Lovely\n-Creme hidrantante Pet Society Lovely\n-Vela Arom�tica Perfumada| Canela\n|VALOR: 90,00|\n"); 
	break;
	case 'C':  
	case 'c': 
	printf ("Voce escolheu o combo (C)\n-Tosa e banho\n-Shampoo Matacura Sarnicida e Anti-Pulgas\n-Condicionador Matacura Sarnicida e Anti-Pulgas\n-Perfume Ibasa de Col�nia Affection para C�es e Gatos\n-Creme Hidratante Equil�brio Hidrapet\nVela Arom�tica Perfumada | Baunilha\n|VALOR: 80,00|\n"); 
	break; 
	default: 
	printf ("OPCAO INVALIDA"); 
	}

	
	  
	    
	    return 0;
	    
	}
