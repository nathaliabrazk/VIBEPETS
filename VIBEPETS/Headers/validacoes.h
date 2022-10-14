//
//  validacoes.h
//  VIBEPETS
//
//  Created by Luiz Araujo on 14/10/22.
//

#ifndef validacoes_h
#define validacoes_h


// #################################
// VALIDACOES
void receberValidarCPF(char*);
int  receberValidarOpcaoNumero(int, int);
char receberValidarOpcaoLetra(char*);
Data receberValidarData(void);
Hora receberValidarHora(void);
void receberValidarEmail(char*);


// #############################################################################
// VALIDACOES

// #################################
// VALIDAR OPCOES PARA MENUS NUMERICOS
// PARAMETRO:
//    - min: o valor minimo que e aceito
//    - max: o valor maximo que e aceito
int receberValidarOpcaoNumero(int min, int max) {
    int opcao = min - 1;
    int contadorErros = 0;
    
    while(opcao < min || opcao > max) {
        if(contadorErros > 2) {
            printarMensagem("\nNumero invalido, informe de ");
            printf("%d a %d\n", min, max);
        }
        printf("OPCAO: ");
        scanf("%d", &opcao);
        
        contadorErros++;
    }
    
    return opcao;
}

// #################################
// VALIDAR OPCOES PARA MENUS DE LETRAS
// PARAMETRO:
//    - opcoes: 'string' com as possibilidades, as opcoes.
char receberValidarOpcaoLetra(char *opcoes) {
    int contadorErros = 0;
    int indice;
    char opcao = ' ', entradaValida = 'n';
    
    // Pegar a quantidade de caracteres digitado.
    int contadorCaracteres = (int) strlen(opcoes);
    
    while(entradaValida == 'n') {
        if(contadorErros > 2) {
            printarMensagem("\nOpcao invalida.\n");
        }
        
        printf("OPCAO: ");
        opcao = getchar(); fflush(stdin);
        
        // Passar pra minuscula.
        opcao = tolower(opcao);
        
        for(indice = 0; indice < contadorCaracteres; indice++) {
            
            if(tolower(opcoes[indice]) == opcao) {
                entradaValida = 's';
            }
        }
        
        contadorErros++;
    }
    
    return opcao;
}

// #################################
// VALIDAR CPF
// Recebe e valida a entrada de CPF.
// RETORNOS:
//    - O cpf se a entrada for valida;
//    - '*' se erro, ou entrada invalida
void receberValidarCPF(char *cpf) {
    char entradaValida = 'n';
    int indice = 0;
    int contadorErros = 0;
    
    char entrada[15];
    
    while(entradaValida == 'n') {
        
        printf("CPF: ");
        gets(entrada); fflush(stdin);
        
        // Pegar a quantidade de caracteres digitado.
        int contadorCaracteres = (int) strlen(entrada);
        
        // Checar quantidade inserida.
        if(contadorCaracteres == 11) {
            entradaValida = 's';
            
        } else {
            if(contadorErros >= 2) {
                printarMensagem("\nQuantidade de numeros incorreta.\n");
            }
            entradaValida = 'n';
        }
        
        
        // Checar se tem somente numeros.
        if(entradaValida == 's') {
            for(indice = 0; indice < contadorCaracteres; indice++){
                if(entrada[indice] < '0' || entrada[indice] > '9'){
                    if(contadorErros >= 2) {
                        printarMensagem("\nInforme apenas valores numericos.\n");
                    }
                    entradaValida = 'n';
                    break;
                }
            }
        }
        
        contadorErros++;
    }
    
    // Passar a entrada por parametro.
    if(entradaValida == 's') {
        strcpy(cpf, entrada);
    }
}

// #################################
// VALIDAR EMAIL
// Recebe e valida a entrada de EMAIL.
// RETORNOS:
//    - O email validado;
void receberValidarEmail(char *email) {
    char entradaValida = 'n';
    int indice = 0, contadorErros = 0;
    int contadorArroba = 0, contadorPonto = 0;
    char entrada[30];
    
    while(entradaValida == 'n') {
        
        printf("Email: ");
        gets(entrada); fflush(stdin);
        
        //----------------------------------
        // Pegar a quantidade de caracteres digitado.
        int contadorCaracteres = (int) strlen(entrada);
        
        //----------------------------------
        // Checar quantidade inserida.
        if(contadorCaracteres >= 5) {
            entradaValida = 's';
            
        } else {
            entradaValida = 'n';
        }
        
        //----------------------------------
        // Checar se tem '@' e '.'.
        if(entradaValida == 's') {
            contadorPonto = contadorArroba = 0;
            
            for(indice = 0; indice < contadorCaracteres; indice++){
                if(email[indice] == '@'){
                    contadorArroba++;
                }
                
                if(email[indice] == '.'){
                    contadorPonto++;
                }
            }
            
            if(contadorArroba != 1) {
                entradaValida = 'n';
            }
            
            if(contadorPonto <= 0) {
                entradaValida = 'n';
            }
        }
        
        if(contadorErros >= 2) {
            printarMensagem("\nEmail invalido.\n");
        }
        
        contadorErros++;
    }
    
    // Passar a entrada por parametro.
    if(entradaValida == 's') {
        strcpy(email, entrada);
    }
}

// #################################
// VALIDAR DATA
Data receberValidarData() {
    Data data;
    int contadorErros = 0, maxDias = 31;
    char entradaValida =  'n';
    
    data.dia = 00;
    data.mes = 00;
    data.ano = 0000;
    
    while(entradaValida != 's') {
        if(contadorErros > 2) {
            printarMensagem("\nData invalida");
        }
        
        printf("Data (dd/mm/aaaa): \n");
        scanf("%d", &data.dia);
        printf("/");
        scanf("%d", &data.mes);
        printf("/");
        scanf("%d", &data.ano);
        
        if((data.mes < 1) || (data.mes > 12)) {
            entradaValida = 'n';
            
        } else {
            entradaValida = 's';
            
            if(data.mes == 1 || data.mes == 3 || data.mes == 5 || data.mes == 7 || data.mes == 8 || data.mes == 10 || data.mes == 12) {
                maxDias = 31;
                
            } else if(data.mes == 4 || data.mes == 6 || data.mes == 9 || data.mes == 11) {
                maxDias = 30;
                
            } else {
                maxDias = 28;
                
                //TODO: Tratar ano bissexto!
            }
            
        }
        
        //        if((agendamento.data. < 1) || (agendamento.data. > maxDias)) {
        //            entradaValida = 'n';
        //
        //        }
        contadorErros++;
    }
    
    return data;
}

#endif /* validacoes_h */
