//
//  interface.h
//  VIBEPETS
//
//  Created by Luiz Araujo on 14/10/22.
//

#ifndef interface_h
#define interface_h


void printarCabecalhoQuadroHorarios(void);
void printarDataFormatada(Data);
void printarHoraFormatada(Hora);
void printarMensagem(char *msg);
void printarMensagemContinuar(void);
void printarStringCentralizada(char*, int);


// #################################
// MOSTRAR HORARIOS POR ANO
// Mostra uma tabela com os horarios do mes selecionado, disponiveis ou nao.
void printarCabecalhoQuadroHorarios() {
    int indice, inicioExpediente = 8, fimExpediente = 18;
    printf("%-5s", "DATA");
    
    for(indice = inicioExpediente; indice < fimExpediente; indice++) {
        printf("|%02d:00|%02d:30", indice, indice);
    }
}

// #################################
// FORMATAR HORA E PRINTAR
// Por dois pontos. Ex.:
//    12:59:00
void printarHoraFormatada(Hora hora) {
    printf("%02d:%02d:%d", hora.hora, hora.minuto, hora.segundo);
}

// #################################
// FORMATAR DATA E PRINTAR
// Por barras. Ex.:
//    01/01/2001
void printarDataFormatada(Data data) {
    printf("%02d/%02d/%d", data.dia, data.mes, data.ano);
}

// #################################
// Colocar uma mensagem na tela
//TODO: COLOCAR ALINHAMENTO: esq, dir, centralizado.
void printarMensagem(char *msg){
    printf("%s", msg);
}

void printarMensagemContinuar() {
    printf("%s", "\n\n Pressione <Enter> para continuar . . .");
    getchar();
}

// #################################
// CENTRALIZAR TEXTO
// Pega um texto e poe mais ou menos no meio
// Obs. Levar em consideracao algum 'pipe' ou caracter que possa pegar um espaco
//       antes e depois(comeco e fim) da linha.
// PARAMETRO:
//   - Recebe uma String a ser printada
//   - O tamanho Int do espaco disponivel
void printarStringCentralizada(char *string, int tamanhoLinha) {
    int tamanhoString = (int) strlen(string);
    int indice = 0;
    
    int espacoVazio = tamanhoLinha - tamanhoString;
    float espacoDirEsq = espacoVazio / 2;
    
    for(indice = 0; indice <= espacoDirEsq; indice++) {
        printf(" ");
    }
    
    printf("%s", string);
    
    for(indice = 0; indice <= espacoDirEsq; indice++) {
        printf(" ");
    }
}






#endif /* interface_h */
