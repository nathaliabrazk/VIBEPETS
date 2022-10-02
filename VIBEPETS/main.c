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
    
	printf ("Escolha os produtos que deseja da linha para o dia de Spa do seu pet\n"); 
	printf ("Escolha o Shampoo para seu pet:\n");
	printf ("A- Shampoo Pré-Banho Pelôncio \nB- Shampoo Pelos Claros Pelôncio \nC- Shampoo Pelos Escuros Pelôncio \nFragrâncias:	Avelã - Melância - Dove - Morango\n"); 
	printf ("Opção:\n"); 
	scanf ("%s", &opcao); 
	fflush (stdin); 
	system ("cls"); 
	  
	switch (opcao) 
	
	{ 
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
	
	switch (opcao)
	
	{
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
	
	
	
	
	  
	    
	    return 0;
	    
	}
