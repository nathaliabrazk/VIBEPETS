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

    #include<stdio.h>
    #include<string.h>
    #include<stdlib.h>
    #include<conio.h>
    #define backSpace 8
    #define newLine 13

    int GetPassword(char *str);

    void main()
    {
        char senha[30], usuario[50];
        int usuarioDigitado, senhaDigitada;
        printf("Bem-vindo(a) ao VIBE Pets. Faça seu login para continuar.\n");
        printf("Digite seu usuário: ");
        scanf("%s",&usuario);
        printf("Digite sua senha: ");
        GetPassword(senha);
        usuarioDigitado = strcmp(usuario,"usuarioAqui");
        senhaDigitada = strcmp(senha,"senhaAqui");
        while(usuarioDigitado!=0){
            printf("\n\nUsuário ou senha incorretos! Tente novamente.\n");
            printf("Digite seu usuário: ");
            scanf("%s",&usuario);
            printf("Digite sua senha: ");
            GetPassword(senha);
            usuarioDigitado = strcmp(usuario,"usuarioAqui");
            senhaDigitada = strcmp(senha,"senhaAqui");
            while (senhaDigitada!=0){
                printf("\n\nUsuário ou senha incorretos! Tente novamente.\n");
                printf("Digite seu usuário: ");
                scanf("%s",&usuario);
                printf("Digite sua senha: ");
                GetPassword(senha);
                usuarioDigitado = strcmp(usuario,"usuarioAqui");
                senhaDigitada = strcmp(senha,"senhaAqui");
            };
        };

        printf("\n\nLogin aprovado! Seja bem-vindo(a).");
        scanf("%i",&usuarioDigitado);
    }
    int GetPassword(char *str)
    {
        int i = 0,end = 0;
        char ch;

        do
        {
            ch=_getch();
            switch (ch)
            {
                case backSpace:
                if (i > 0)
                {
                    i--;
                    str--;
                    printf("\b");
                    printf(" ");
                    printf("\b");
                }
                break;

                case newLine:
                *str = '\0';
                end = 1;
                break;

                default:
                *str = ch;
                str++ ;
                i++;
                printf("*");
                break;
            };
        }while (end==0);
        return(1);
    }

    
    // Processamento
    
    
    // Saida
    /*printf("O nome digitado e: %s", nome);
    printf("O email digitado e: %s", email);*/
    scanf("O dia digitado foi:  %d", &dia);


    return 0;
}
