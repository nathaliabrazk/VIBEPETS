//
//  main.c
//  VIBEPETS
//
//  Created by Nathália Braz on 24/09/22.
//

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <locale.h>

int main(int argc, char *argv[]) {
    // Propriedades
    char nome[50], email[50];
    int  dia, mes, ano, endereco, cpf, tel;
    
    //Entradas do sistema de login
    setlocale(LC_ALL, "Portuguese");

    char usuario[75], senha[50], c;
    int i=10, j=0, v=0;
    while (v==0){
        printf("Digite o seu login: ");
        gets(usuario);
        printf("Digite sua senha: ");
        while((c=getch())!=13){
            senha[j] = c;
            j++;
            printf("*");
        }
        senha[j]='\0';
        j=0;
        system("cls");
        i = strcmp(senha,"josafa");
        if(i==0){
            printf("Login autorizado! Seja bem vindo(a).");
            v=1;
        } else{
            printf("Login não autorizado! Usuário ou senha estão incorretos!");
            printf("\nTente novamente.\n");
        }

    }
    
    // Processamento
    
    
    // Saida
    /*printf("O nome digitado e: %s", nome);
    printf("O email digitado e: %s", email);*/
    scanf("O dia digitado foi:  %d", &dia);


    return 0;
}
