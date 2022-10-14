//
//  utilidades.h
//  VIBEPETS
//
//  Created by Luiz Araujo on 14/10/22.
//

#ifndef utilidades_h
#define utilidades_h

#include "tipos.h"
#include "interface.h"


// #############################################################################
// FUNCOES AUXILIARES

// #################################
// PROTOTIPOS

char* formatarCPF(char[], int);
char* intParaString(int, int);
void limparTela(int);
void listarCaracteresASCII(void);
Data pegarDataDoSistema(int);
Hora pegarHoraDoSistema(int);
int quantidadeDiaMes(int);
char* stringDataFormatada(Data);
char* stringHoraFormatada(Hora);
char verificarHoraDentroExpediente(Hora);
int verificarTempoAteData(Data, int);


// #################################
// FUNCOES

// #################################
// FORMATAR CPF
// Por pontos e hifen. Ex.:
//    123.456.789-10
char *formatarCPF(char *cpf, int mostrar_debug) {
    int i, j = 0;
    
    //Aloca o espaço necessário
    char *cpfFormatado = (char*) malloc(15 * sizeof(char));
    
    if(!cpfFormatado) {
        //Se malloc retornar nulo e porque nao há memoria suficiente para alocar o espaço necessário
        if(mostrar_debug == 1) {
            printarMensagem("Nao ha espaco suficiente na memoria.");
        }
        return cpfFormatado;
    }
    
    // Uma forma de acrescentar os '.' e o '-'
    //    cpfFormatado[0] = cpf[0];
    //    cpfFormatado[1] = cpf[1];
    //    cpfFormatado[2] = cpf[2];
    //    cpfFormatado[3] = '.';
    //    cpfFormatado[4] = cpf[3];
    //    cpfFormatado[5] = cpf[4];
    //    cpfFormatado[6] = cpf[5];
    //    cpfFormatado[7] = '.';
    //    cpfFormatado[8] = cpf[6];
    //    cpfFormatado[9] = cpf[7];
    //    cpfFormatado[10] = cpf[8];
    //    cpfFormatado[11] = '-';
    //    cpfFormatado[12] = cpf[9];
    //    cpfFormatado[13] = cpf[10];
    
    // Outra forma de acrescentar
    for(i = 0; i < 15; i++) {
        
        if(i == 3 || i == 7) {
            cpfFormatado[i] = '.';
            i++;
            
        } else if(i == 11) {
            cpfFormatado[i] = '-';
            i++;
        }
        
        cpfFormatado[i] = cpf[j];
        j++;
    }
    
    return cpfFormatado;
}

// #################################
// PEGA INT E TRANSFORMA EM STRING
char* intParaString(int val, int base){
    static char buf[32] = {0};
    int i = 30;
    
    for(; val && i ; --i, val /= base)
        buf[i] = "0123456789abcdef"[val % base];
    
    return &buf[i+1];
    
}

// #################################
// Dá um system cls, limpa a tela.
void limparTela(int limpar_tela) {
    if(limpar_tela == 1) {
        system("cls");
    }
}

// #################################
// Dá um system cls, limpa a tela.
void listarCaracteresASCII() {
    int indice;
    
//    printf("%c\n\n\n\n", 187);
    
    for(indice = 0; indice <= 255; indice++) {
        printf("CHAR %3d: %-3c\t", indice, indice);
        
        if(indice % 10 == 0) {
            printf("\n");
        }
    }
}

// #################################
// PEGA STRING E TRANSFORMA EM INT
//char* stringParaInt(int val, int base){
//}

// #################################
// PEGA A DATA ATUAL DO SISTEMA
Data pegarDataDoSistema(int mostrar_debug) {
    Data dataAtual;
    struct tm *p;
    time_t seconds;

    time(&seconds);
    p = localtime(&seconds);

    if(mostrar_debug == 1) {
        printf("Dia do ano: %d\n", p->tm_yday);
        printf("Data: %d/%02d/%d\n", p->tm_mday, p->tm_mon + 1, p->tm_year + 1900);
        
        printf("\nGeral: %s\n", ctime(&seconds));
    }
    
    dataAtual.dia = p->tm_mday;
    dataAtual.mes = p->tm_mon + 1;
    dataAtual.ano = p->tm_year + 1900;
    
    return dataAtual;
}

// #################################
// PEGA A HORA ATUAL DO SISTEMA
Hora pegarHoraDoSistema(int mostrar_debug) {
    Hora horaAtual;
    struct tm *p;
    time_t seconds;

    time(&seconds);
    p = localtime(&seconds);

    if(mostrar_debug == 1) {
        printf("Dia do ano: %d\n", p->tm_yday);
        printf("Hora: %02d:%02d:%d\n", p->tm_hour, p->tm_min, p->tm_sec);
        
        printf("\nGeral: %s\n", ctime(&seconds));
    }
    
    horaAtual.segundo = p->tm_sec;
    horaAtual.minuto  = p->tm_min;
    horaAtual.hora    = p->tm_hour;
    
    return horaAtual;
}

// #################################
// QUANTIDADE DE DIAS NO MES
// RETORNO:
//   - Retorna a quantidade de dias no mes/ultimo dia
//   - -1 caso o mes seja invalido
/*
     Quantos dias tem cada mes
     Num     Mes         Dias
     2       Fevereiro   28 dias (29 dias nos anos bissextos)
     
     4       Abril       30 dias
     6       Junho       30 dias
     9       Setembro    30 dias
     11      Novembro    30 dias
     
     1       Janeiro     31 dias
     3       Março       31 dias
     5       Maio        31 dias
     7       Julho       31 dias
     8       Agosto      31 dias
     10      Outubro     31 dias
     12      Dezembro    31 dias
 */
int quantidadeDiaMes(int mes) {
    switch(mes) {
        case 2:
            return 28;
            
        case 4:
        case 6:
        case 9:
        case 11:
            return 30;
            
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            return 31;
            
        default:
            return -1;
    }
}

// #################################
// FORMATAR DATA E RETORNAR A STRING
// Por barras. Ex.:
//    01/01/2001
char* stringDataFormatada(Data data) {
    char* resultado = (char*)calloc(11,sizeof(char));
    char diaAux[3];
    char mesAux[3];
    char anoAux[5];
    
    strcpy(resultado, "00-00-0000");
    
    strcpy(diaAux, intParaString(data.dia, 10));
    strcpy(mesAux, intParaString(data.mes, 10));
    strcpy(anoAux, intParaString(data.ano, 10));
    
    if(data.dia <= 9) {
        resultado[0] = '0';
        resultado[1] = diaAux[0];
    } else {
        resultado[0] = diaAux[0];
        resultado[1] = diaAux[1];
    }
    resultado[2] = '/';
    
    if(data.mes <= 9) {
        resultado[3] = '0';
        resultado[4] = mesAux[0];
    } else {
        resultado[3] = mesAux[0];
        resultado[4] = mesAux[1];
    }
    
    resultado[5] = '/';
    
    if(data.ano <= 9) {
        resultado[6] = '0';
        resultado[7] = mesAux[0];
        resultado[8] = mesAux[1];
        resultado[9] = mesAux[2];
    } else {
        resultado[6] = anoAux[0];
        resultado[7] = anoAux[1];
        resultado[8] = anoAux[2];
        resultado[9] = anoAux[3];
    }
    //    resultado[6] = anoAux[0];
    //    resultado[7] = anoAux[1];
    //    resultado[8] = anoAux[2];
    //    resultado[9] = anoAux[3];
    
    return resultado;
}

// #################################
// FORMATAR HORA E RETORNAR A STRING
// Por dois pontos. Ex.:
//    12:59:00
char* stringHoraFormatada(Hora hora) {
    char* resultado = (char*)calloc(6,sizeof(char));
    char horaAux[3];
    char minutoAux[3];
    //    char segundoAux[3];
    
    strcpy(resultado, "00:00:00");
    
    //    strcpy(segundoAux, itoa(hora.segundo, 10));
    strcpy(minutoAux, intParaString(hora.minuto, 10));
    strcpy(horaAux, intParaString(hora.hora, 10));
    
    resultado[0] = horaAux[0];
    resultado[1] = horaAux[1];
    resultado[2] = ':';
    resultado[3] = minutoAux[0];
    resultado[4] = minutoAux[1];
    resultado[5] = '\0';
    //    resultado[6] = segundoAux[0];
    //    resultado[7] = segundoAux[1];
    
    return resultado;
}

// #################################
// VERIFICAR SE A HORA RECEBIDA ESTA DENTRO DO EXPEDIENTE DA LOJA
// PARAMETRO:
//   - Uma instancia de Hora
// RETORNO:
//   - 'n': caso esteja fora do expediente;
//   - 's': tah safe.
char verificarHoraDentroExpediente(Hora horaEscolhida) {
    char dentroExpediente = 's';
    int inicioExpediente = 8, fimExpediente = 18;
    
    if((horaEscolhida.hora < inicioExpediente) || (horaEscolhida.hora > fimExpediente)) {
        printarMensagem("\nFora do horario de funcionamento!(8h as 18h)\n");
        return 'n';
    }
    
    return dentroExpediente;
}

// #################################
// VERIFICAR QUANTOS DIAS FALTAM PARA A DATA RECEBIDA
// PARAMETRO:
//   - Uma instancia de Data
// RETORNO:
//   - -1: data passada;
//   -  0: é hoje!;
//   -  1: é amanha;
//   -  2: falta dois ou mais dias.
int verificarTempoAteData(Data dataEscolhida, int mostrar_debug) {
    Data dataAtual, resultado;
    
    //----------------------------------
    // Pegar a data atual.
    dataAtual = pegarDataDoSistema(mostrar_debug);
    
    //----------------------------------
    // Comparar ano.
    if(dataEscolhida.ano < dataAtual.ano) {
        return -1;
        
    } else if(dataEscolhida.ano == dataAtual.ano) {
        resultado.ano = 0;
        
    } else if(dataEscolhida.ano > dataAtual.ano) {
        resultado.ano = 1;
    }
    
    //----------------------------------
    // Comparar mes.
    if(dataEscolhida.mes < dataAtual.mes) {
        resultado.mes = -1;
        
    } else if(dataEscolhida.mes == dataAtual.mes) {
        resultado.mes = 0;
        
    } else if(dataEscolhida.mes > dataAtual.mes) {
        resultado.mes = 1;
    }
    
    //----------------------------------
    // Comparar dia.
    if(dataEscolhida.dia < dataAtual.dia) {
        resultado.dia = -1;
        
    } else if(dataEscolhida.dia == dataAtual.dia) {
        resultado.dia = 0;
        
    } else if(dataEscolhida.dia > dataAtual.dia) {
        resultado.dia = 1;
    }
    
    
    //----------------------------------
    // Se ano atual
    if(resultado.ano == 0) {
        //------------------------------
        // Se mes passado.
        if(resultado.mes == -1) {
            return -1;
        }
        
        //------------------------------
        // Se mesmo ano e mes.
        if(resultado.mes == 0) {
            // Dia passado.
            if(resultado.dia == -1) {
                return  -1;
            }
            
            //--------------------------
            // Se mesmo dia, mes, ano.
            // HOJE!
            if(resultado.dia == 0) {
                return 0;
            }
            
            //--------------------------
            // Se mesmo mes e ano, mas dia superior.
            if(resultado.dia == 1) {
                //----------------------
                // Ver se é amanha.
                if(dataEscolhida.dia == dataAtual.dia + 1) {
                    return  1;
                }
                
                //----------------------
                // 2 dias ou mais
                if(dataEscolhida.dia > dataAtual.dia + 1) {
                    return  2;
                }
            }
        }
        
        //------------------------------
        // Se mesmo ano, mas mes seguinte.
        if(resultado.mes == 1) {
            //--------------------------
            // Se dia 2 ou mais
            if(dataEscolhida.dia >= 2) {
                return 2;
            }
            
            if(dataEscolhida.dia == 1) {
                return 1;
            }
        }
    }
    
    //----------------------------------
    // Se ano seguinte
    if(resultado.ano == 1) {
        //------------------------------
        // Se pula 1 ano.
        if(dataEscolhida.ano > dataAtual.ano + 1) {
            return 2;
        }
        
        //------------------------------
        // Se ano seguinte.
        if(dataEscolhida.ano == dataAtual.ano + 1) {
            //--------------------------
            // Se primeiro dia do ano.
            if(dataEscolhida.dia == 1) {
                return 1;
            }
            
            //--------------------------
            // Se primeiro dia do ano.
            if(dataEscolhida.dia > 1) {
                return 2;
            }
        }
    }

    printarMensagem("\n\nERRO (func verificarTempoAteData): CHEGOU ONDE NAO DEVERIA\n\n");
    printf("\nDATA RESULTADO");
    printf("\nDIA: %d", resultado.dia);
    printf("\nMES: %d", resultado.mes);
    printf("\nANO: %d", resultado.ano);
    printf("\nDATA ATUAL");
    printf("\nDIA: %d", dataAtual.dia);
    printf("\nMES: %d", dataAtual.mes);
    printf("\nANO: %d", dataAtual.ano);
    printf("\nDATA ESCOLHIDA");
    printf("\nDIA: %d", dataEscolhida.dia);
    printf("\nMES: %d", dataEscolhida.mes);
    printf("\nANO: %d", dataEscolhida.ano);
    
    return -404;
}

#endif /* utilidades_h */
