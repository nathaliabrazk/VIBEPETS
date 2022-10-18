//
//  Horario.h
//  VIBEPETS
//
//  Created by Luiz Araujo on 16/10/22.
//

// #############################################################################
// HORARIO

#ifndef Horario_h
#define Horario_h

#include "utilidades.h"
#include "Agendamento.h"

#define INICIO_EXPEDIENTE 8
#define FINAL_EXPEDIENTE 18

// #################################
// CONSTANTES
FILE *ponteiroArquivoHORARIO;
FILE *ponteiroArquivoHorarioMes;
//FILE *ponteiroArquivoHorarioMesSeguinte;


// #################################
// PROTOTIPOS
//void menuHorario(void);
//void menuHorarioListarTodos(void);
//void menuHorarioInserir(void);
//void menuHorarioAlterar(void);
//void menuHorarioDeletar(void);
void mostrarQuadroHorarios(int, int);


//int  salvarRegistroHorario(struct Horario, int);
int  salvarRegistroHorarioMes(struct Horario, int);
//void printarTodosRegistrosHorario(void);
void printarHorarioLista(struct Horario, int);
void printarHorarioTopicos(struct Horario, int);
//struct Horario buscarHorarioPorCod(int);
//int  buscarRegistroHorarioPorCod(int);
//void alterarHorario(int);
//int  acessarUltimoCodigoHorario(void);
//void deletarHorario(int);
void lerDadosHorario(struct Horario*);
void abrirArquivoHorario(int);
void fecharArquivoHorario(void);
void criarTodosHorariosMesAtualSeguinte(int, int);
void fecharArquivoHorarioPorNome(void);
struct Horario criarHorarioDeAgendamento(struct Agendamento, int);

void abrirArquivoHorario(int mostrar_debug) {
    ponteiroArquivoHORARIO = fopen(BIN_AGE, "r+b"); //tentar abrir
    
    if(ponteiroArquivoHORARIO == NULL){
        ponteiroArquivoHORARIO  = fopen(BIN_AGE, "w+b"); // criar o arquivo
        
        if(ponteiroArquivoHORARIO == NULL){
            if(mostrar_debug == 1) {
                printf("Erro fatal: impossivel abrir/criar o arquivo '%s'\n", BIN_AGE);
            }
            
            // Se chegar ate aqui, quer dizer que nao conseguiu abrir de jeito neNhum...
            // ai encerra o programa 🍃
            exit(1);
        }
    }
}

void abrirArquivoHorarioPorNome(char nome[], int mostrar_debug) {
    ponteiroArquivoHorarioMes = fopen(nome, "r+b"); //tentar abrir
    
    if(ponteiroArquivoHorarioMes == NULL){
        ponteiroArquivoHorarioMes  = fopen(nome, "w+b"); // criar o arquivo
        
        if(ponteiroArquivoHorarioMes == NULL){
            if(mostrar_debug == 1) {
                printf("Erro fatal: impossivel abrir/criar o arquivo '%s'\n", nome);
            }
            
            // Se chegar ate aqui, quer dizer que nao conseguiu abrir de jeito neNhum...
            // ai encerra o programa 🍃
            exit(1);
        }
    }
}

void fecharArquivoHorario() {
    // Atualizar o arquivo.
    fflush(ponteiroArquivoHORARIO);
    
    // Fechar o arquivo.
    fclose(ponteiroArquivoHORARIO);
}

void fecharArquivoHorarioPorNome() {
    // Atualizar o arquivo.
    fflush(ponteiroArquivoHorarioMes);
    
    // Fechar o arquivo.
    fclose(ponteiroArquivoHorarioMes);
}


// #################################
// MOSTRAR HORARIOS POR ANO
// Mostra uma tabela com os horarios do mes selecionado, disponiveis ou nao.
//void mostrarQuadroHorarios(int tema) {
//    int larguraDaTabela = 125;
//    int indiceAno = 2022, indiceMes = 1, indiceDia = 1;
//    char anoString[5] = "2022";//, mesString[3] = "12";
//
//    int indice, inicioExpediente = 8, fimExpediente = 18;
//
//    Data dataEscolhida;
//    dataEscolhida.dia = 1;
//    dataEscolhida.mes = 10;
//    dataEscolhida.ano = 2022;
//
////    char stringMesAno;
//
//    for(indiceAno = 2022; indiceAno <= 2023; indiceAno++){
//        sprintf(anoString, "%d", indiceAno);
//        interfaceLinhaSeparadora(larguraDaTabela, tema);
//        printarStringCentralizada(anoString, larguraDaTabela);
//        interfaceLinhaSeparadora(larguraDaTabela, tema);
//
//        printarCabecalhoQuadroHorarios(); printf("\n");
//        interfaceLinhaSeparadoraSemQuebraDeLinha(larguraDaTabela, tema);
//
//        for(indiceMes = 1; indiceMes <= 12; indiceMes++){
//
//            for(indiceDia = 1; indiceDia <= quantidadeDiaMes(indiceMes); indiceDia++){
//                printf("\n%02d/%02d", indiceDia, indiceMes);
//
//                for(indice = inicioExpediente; indice < fimExpediente; indice++) {
//                    printf("|%5s|%5s", " ", " ");
//                }
//                printf("\n");
//                interfaceLinhaSeparadoraSemQuebraDeLinha(larguraDaTabela, tema);
////                printf("\n");
//            }
//        }
//
//    }
//}
void mostrarQuadroHorarios(int mostrar_debug, int tema) {
    criarTodosHorariosMesAtualSeguinte(mostrar_debug, tema);
    
    int larguraDaTabela = 125;
    int indiceAno = 2022, indiceMes = 1, indiceDia = 1;
    char anoString[5] = "2022", diaString[3], mesString[3];//, mesString[3] = "12";
    
    int indice, inicioExpediente = 8, fimExpediente = 18;
    
    char nomeArquivoMesAtual[40]    = "vibe_pet-persistencia_agend-"; //2022_10.bin"; // "vibe_pet-persistencia_agend-2022_10.bin";
    
    struct Horario horario;
    int n_Linhas = 0;
    
    
    Data dataEscolhida;
    dataEscolhida = pegarDataDoSistema(mostrar_debug);
    //        dataEscolhida.dia = 1;
    //        dataEscolhida.mes = 10;
    //        dataEscolhida.ano = 2022;
    
    //    char stringMesAno;
    
    //        for(indiceAno = 2022; indiceAno <= 2023; indiceAno++){
    sprintf(anoString, "%d", dataEscolhida.ano);
    interfaceLinhaSeparadora(larguraDaTabela, tema);
    printarStringCentralizada(anoString, larguraDaTabela);
    interfaceLinhaSeparadora(larguraDaTabela, tema);
    
    printarCabecalhoQuadroHorarios(); printf("\n");
    interfaceLinhaSeparadoraSemQuebraDeLinha(larguraDaTabela, tema);
    
    //    for(indiceMes = 1; indiceMes <= 12; indiceMes++){
    //
    //        for(indiceDia = 1; indiceDia <= quantidadeDiaMes(indiceMes); indiceDia++){
    //            printf("\n%02d/%02d", indiceDia, indiceMes);
    //
    //            for(indice = inicioExpediente; indice < fimExpediente; indice++) {
    //                printf("|%5s|%5s", " ", " ");
    //            }
    //            printf("\n");
    //            interfaceLinhaSeparadoraSemQuebraDeLinha(larguraDaTabela, tema);
    //            //                printf("\n");
    //        }
    //    }
    
    //        }
    
    
    sprintf(anoString, "%d", dataEscolhida.ano);
    sprintf(mesString, "%d", dataEscolhida.mes);
    sprintf(diaString, "%d", dataEscolhida.dia);
    
    
    nomeArquivoMesAtual[28] = anoString[0];
    nomeArquivoMesAtual[29] = anoString[1];
    nomeArquivoMesAtual[30] = anoString[2];
    nomeArquivoMesAtual[31] = anoString[3];
    nomeArquivoMesAtual[32] = '_';
    nomeArquivoMesAtual[33] = mesString[0];
    nomeArquivoMesAtual[34] = mesString[1];
    nomeArquivoMesAtual[35] = '.';
    nomeArquivoMesAtual[36] = 'b';
    nomeArquivoMesAtual[37] = 'i';
    nomeArquivoMesAtual[38] = 'n';
    nomeArquivoMesAtual[39] = '\0';
    
    if(mostrar_debug == 1) {
        printf("\nNOME DO ARQUIVO nomeArquivoMesAtual: %s", nomeArquivoMesAtual);
    }
    
    // Checar se o arquivo existe e abri-lo.
    abrirArquivoHorarioPorNome(nomeArquivoMesAtual, mostrar_debug);
    
    
    
    // Volta o ponteiro para o inicio.
    rewind(ponteiroArquivoHorarioMes);
    printf("\n");
    
    int ultimaHora = 0;
    struct Agendamento agendamentoAuxiliar;
    
    while(1){
        if(fread(&horario, sizeof(horario), 1, ponteiroArquivoHorarioMes)!= 1)break; /*Sair do laço*/
        agendamentoAuxiliar = buscarAgendamentoPorCodigo(horario.codigoAgendamento, mostrar_debug);// buscarAgendamentoPorCod(horario.codigoAgendamento, mostrar_debug);
        
        if(ultimaHora != agendamentoAuxiliar.hora.hora) {
            ultimaHora = agendamentoAuxiliar.hora.hora;
            printf("\n");
        }
        //        if(horario.ativo == '*') continue; /*Passa ao proximo*/
        printarHorarioLista(horario, mostrar_debug);
        //        printarServicoTopicos(servico);
        n_Linhas++;
        if(n_Linhas%20 == 0)
            printarMensagem("Pressione <Enter> para continuar .  .  .");
    }
}

// Criar horarios
void criarTodosHorariosMesAtualSeguinte(int mostrar_debug, int tema) {
    struct Agendamento agendamentoAuxiliar;
    struct Horario horarioAuxiliar;
    Data dataAtual;
    char diaString[3], mesString[3], anoString[5];
    char nomeArquivoMesAtual[40]    = "vibe_pet-persistencia_agend-"; //2022_10.bin"; // "vibe_pet-persistencia_agend-2022_10.bin";
    char nomeArquivoMesSeguinte[40] = "vibe_pet-persistencia_agend-"; //2022_11.bin"; // "vibe_pet-persistencia_agend-2022_11.bin";
    
    int indiceSalvamento = 0;
    
    //    int larguraDaTabela = 125;
    //    int indiceAno = 2022, indiceMes = 1, indiceDia = 1;
    //    char anoAux[5] = "2022";//, mesString[3] = "12";
    
    //    int indice, inicioExpediente = 8, fimExpediente = 18;
    
    Data dataEscolhida;
    dataEscolhida.dia = 1;
    dataEscolhida.mes = 10;
    dataEscolhida.ano = 2022;
    
    horarioAuxiliar.ocupado = ' ';
    
    // Pegar a data do Agendamento e transformar no codigo do Horario
    dataAtual     = pegarDataDoSistema(mostrar_debug);
    dataEscolhida = pegarDataDoSistema(mostrar_debug);
    
    sprintf(anoString, "%d", dataAtual.ano);
    sprintf(mesString, "%d", dataAtual.mes);
    sprintf(diaString, "%d", dataAtual.dia);
    
    
    nomeArquivoMesAtual[28] = anoString[0];
    nomeArquivoMesAtual[29] = anoString[1];
    nomeArquivoMesAtual[30] = anoString[2];
    nomeArquivoMesAtual[31] = anoString[3];
    nomeArquivoMesAtual[32] = '_';
    nomeArquivoMesAtual[33] = mesString[0];
    nomeArquivoMesAtual[34] = mesString[1];
    nomeArquivoMesAtual[35] = '.';
    nomeArquivoMesAtual[36] = 'b';
    nomeArquivoMesAtual[37] = 'i';
    nomeArquivoMesAtual[38] = 'n';
    nomeArquivoMesAtual[39] = '\0';
    
    if(mostrar_debug == 1) {
        printf("\nNOME DO ARQUIVO nomeArquivoMesAtual: %s", nomeArquivoMesAtual);
    }
    
    // Checar se o arquivo existe e abri-lo.
    abrirArquivoHorarioPorNome(nomeArquivoMesAtual, mostrar_debug);
    
    // Criar todos os dias para o mes atual.
    for(dataEscolhida.dia = 1; dataEscolhida.dia <= quantidadeDiaMes(dataAtual.mes); dataEscolhida.dia++) {
        agendamentoAuxiliar.data = dataEscolhida;
        
        horarioAuxiliar = criarHorarioDeAgendamento(agendamentoAuxiliar, mostrar_debug);
        
        // Salvar o agendamento do primeiro horario da hora escolhida.
        agendamentoAuxiliar.hora.minuto = 10;
        salvarRegistroHorarioMes(horarioAuxiliar, mostrar_debug);
        
        // Salvar o agendamento do segundo horario da hora escolhida.
        agendamentoAuxiliar.hora.minuto = 40;
        salvarRegistroHorarioMes(horarioAuxiliar, mostrar_debug);
        
        
    }
    
    
    
    // Mes seguinte
    dataAtual = pegarDataDoSistema(mostrar_debug);
    if(dataAtual.mes == 12) {
        dataAtual.ano++;
        dataAtual.mes = 1;
    } else {
        dataAtual.mes++;
    }
    
    
    sprintf(anoString, "%d", dataAtual.ano);
    sprintf(mesString, "%d", dataAtual.mes);
    sprintf(diaString, "%d", dataAtual.dia);
    
    
    nomeArquivoMesSeguinte[28] = anoString[0];
    nomeArquivoMesSeguinte[29] = anoString[1];
    nomeArquivoMesSeguinte[30] = anoString[2];
    nomeArquivoMesSeguinte[31] = anoString[3];
    nomeArquivoMesSeguinte[32] = '_';
    nomeArquivoMesSeguinte[33] = mesString[0];
    nomeArquivoMesSeguinte[34] = mesString[1];
    nomeArquivoMesSeguinte[35] = '.';
    nomeArquivoMesSeguinte[36] = 'b';
    nomeArquivoMesSeguinte[37] = 'i';
    nomeArquivoMesSeguinte[38] = 'n';
    nomeArquivoMesSeguinte[39] = '\0';
    
    if(mostrar_debug == 1) {
        printf("\nNOME DO ARQUIVO nomeArquivoMesSeguinte: %s", nomeArquivoMesSeguinte);
    }
    
    
    // Checar se o arquivo existe e abri-lo.
    abrirArquivoHorarioPorNome(nomeArquivoMesSeguinte, mostrar_debug);
    
    // Criar todos os dias para o mes seguinte.
    for(dataEscolhida.dia = 1; dataEscolhida.dia <= quantidadeDiaMes(dataAtual.mes); dataEscolhida.dia++) {
        agendamentoAuxiliar.data = dataEscolhida;
        
        // Criar os horarios para cada dia.
        for(indiceSalvamento = INICIO_EXPEDIENTE; indiceSalvamento < FINAL_EXPEDIENTE; indiceSalvamento++) {
            agendamentoAuxiliar.hora.hora = indiceSalvamento;
            horarioAuxiliar = criarHorarioDeAgendamento(agendamentoAuxiliar, mostrar_debug);
            
            // Salvar o agendamento do primeiro horario da hora escolhida.
            agendamentoAuxiliar.hora.minuto = 10;
            salvarRegistroHorarioMes(horarioAuxiliar, mostrar_debug);
            
            // Salvar o agendamento do segundo horario da hora escolhida.
            agendamentoAuxiliar.hora.minuto = 40;
            salvarRegistroHorarioMes(horarioAuxiliar, mostrar_debug);
            
        }
        
        
    }
    
    
    fecharArquivoHorarioPorNome();
}


// #################################
// PASSAR DE AGENDAMENTO PARA HORARIO
// RETORNO:
//  - O horario. Ex.:
//      2022-01-01-1
struct Horario criarHorarioDeAgendamento(struct Agendamento agendamento, int mostrar_debug) {
    struct Horario horario;
    char diaString[3], mesString[3], anoString[5];
    
    // Pegar a data do Agendamento e transformar no codigo do Horario
    sprintf(anoString, "%d", agendamento.data.ano);
    sprintf(mesString, "%d", agendamento.data.mes);
    sprintf(diaString, "%d", agendamento.data.dia);
    
    horario.codigo[0]  = anoString[1];
    horario.codigo[1]  = anoString[0];
    horario.codigo[2]  = anoString[2];
    horario.codigo[3]  = anoString[3];
    horario.codigo[4]  = '-';
    horario.codigo[5]  = mesString[0];
    horario.codigo[6]  = anoString[1];
    horario.codigo[7]  = '-';
    horario.codigo[8]  = anoString[0];
    horario.codigo[9]  = anoString[1];
    horario.codigo[10] = '-';
    
    // O '1' quer dizer que o horario ocupa os min. de 00 a 29 da hora esolhida.
    if(agendamento.hora.minuto < 30) {
        horario.codigo[11] = '1';
        
    } else {
        // '2' quer dizer que o horario ocupa os min. de 30 a 59 da hora esolhida.
        horario.codigo[11] = '2';
    }
    
    return horario;
}

// #################################
// SALVAR DADOS DE HORARIO
// RETORNO:
//  -    0: se nao houve erros;
//  - != 0: se houve erro(s);
//int salvarRegistroHorario(struct Horario horario, int mostrar_debug) {
//    int resultado = 0;
//
//    // Poe o novo agendamento no final do arquivo.
//    fseek(ponteiroArquivoHORARIO, 0L, SEEK_END);
//    if(fwrite(&horario, sizeof(horario), 1, ponteiroArquivoHORARIO)!= 1) {
//        if(mostrar_debug == 1) {
//            printarMensagem("Adicionar agendamento: Falhou a escrita do registro");
//        }
//
//        resultado = 1;
//    }
//
//    // Retornando o valor do resultado.
//    return(resultado);
//}
int salvarRegistroHorarioMes(struct Horario horario, int mostrar_debug) {
    int resultado = 0;
    
    // Poe o novo agendamento no final do arquivo.
    fseek(ponteiroArquivoHorarioMes, 0L, SEEK_END);
    if(fwrite(&horario, sizeof(horario), 1, ponteiroArquivoHorarioMes)!= 1) {
        if(mostrar_debug == 1) {
            printarMensagem("Adicionar agendamento: Falhou a escrita do registro");
        }
        
        resultado = 1;
    }
    
    // Retornando o valor do resultado.
    return(resultado);
}

//void mostrarQuadroHorarios(int mostrar_debug) {
//    abrirArquivoHorario(mostrar_debug);
//    
//    printf("sadsdfdsfadc");
//    
//    fecharArquivoHorario();
//}

// receber agendamento e salvar no horario

//void


// Verificar se o horario está agendado/reservado














//



//// #############################################################################
//// PROTOTIPOS
//void abrirArquivoHorario(int);
//void fecharArquivoHorario(void);
//
//void menuHorario(int, int);
//void menuHorarioListarTodos(int, int);
//void menuHorarioInserir(int);
//void menuHorarioAlterar(int, int);
//void menuHorarioDeletar(int, int);
//
//int   salvarRegistroHorario(struct Horario, int);
//void  printarTodosRegistrosHorario(int, int);
//void  printarHorarioLista(struct Horario, int);
//void  printarHorarioTopicos(struct Horario, int);
//struct Horario buscarHorarioPorCod(int, int);
//int   buscarRegistroHorarioPorCod(char[], int);
//void  alterarHorario(int, int);
//char* acessarUltimoCodigoHorario(int);
//void  deletarHorario(int, int);
//void  lerDadosHorario(struct Horario*);
//struct Horario buscarHorarioPorCPF(char[], int);




// #################################
// ALTERAR UM PERFIL DE HORARIO
// Encontra a posicao do registro pelo numero que representa a linha na qual está
// e mostra como está momento antes da alteracao, apos isso rece novos dados e atualiza.
// PARAMETRO:
//   - registro: int da 'linha' que está o referido registro.
void alterarHorario(int registro, int mostrar_debug) {
    struct Horario horarioAux;
    
    if(fseek(ponteiroArquivoHORARIO, (registro)*sizeof(horarioAux), SEEK_SET) != 0){
        printarMensagem("Registro inexistente ou problemas no posicionamento!!!");
        return;
    }
    
    if(fread(&horarioAux, sizeof(struct Horario), 1, ponteiroArquivoHORARIO)!= 1){
        printarMensagem("11 - Problemas na leitura do registro!!!");
        return;
    }
    
    if(horarioAux.ocupado == '*'){
        printarMensagem("Um registro apagado nao pode ser alterado!!! \n\n");
        return;
    }
    
    printf("\n\n Dados Atuais \n\n");
    printarHorarioTopicos(horarioAux, mostrar_debug);
    
    printf("\n\n Novos dados \n\n");
    lerDadosHorario(&horarioAux);
    
    // recuar um registro no arquivo
    fseek(ponteiroArquivoHORARIO, -(int) sizeof(struct Horario), SEEK_CUR);
    // reescrever o registro;
    fwrite(&horarioAux, sizeof(struct Horario), 1, ponteiroArquivoHORARIO);
    fflush(ponteiroArquivoHORARIO); /*despejar os arquivos no disco rígido*/
}



// #################################
// ALTERAR A RESERVA DE UM HORARIO
// Se desocupa se está ocupado e vice-versa.
void toggleOcuparHorario(int registro, int mostrar_debug) {
    struct Horario horarioAux;
    
    if(fseek(ponteiroArquivoHORARIO, (registro)*sizeof(horarioAux), SEEK_SET) != 0){
        printarMensagem("Registro inexistente ou problemas no posicionamento!!!");
        return;
    }
    
    if(fread(&horarioAux, sizeof(struct Horario), 1, ponteiroArquivoHORARIO)!= 1){
        printarMensagem("11 - Problemas na leitura do registro!!!");
        return;
    }
    
    if(horarioAux.ocupado == ' '){
        horarioAux.ocupado = '*';
        
    } else {
        horarioAux.ocupado = ' ';
    }
    
    // recuar um registro no arquivo
    fseek(ponteiroArquivoHORARIO, -(int) sizeof(struct Horario), SEEK_CUR);
    // reescrever o registro;
    fwrite(&horarioAux, sizeof(struct Horario), 1, ponteiroArquivoHORARIO);
    fflush(ponteiroArquivoHORARIO); /*despejar os arquivos no disco rígido*/
}

// #################################
// BUSCAR CODIGO DO ULTIMO REGISTRO
// Uma funçao para ir ate o ultimo registro, ultimo horario cadastrado e
// retorna seu respectivo codigo.
// RETORNO:
//  - O int do codigo.
//char* acessarUltimoCodigoHorario(int mostrar_debug) {
//    struct Horario horario;
//
//    fseek(ponteiroArquivoHORARIO, -1 * sizeof(struct Horario), SEEK_END);
//    if(fread(&horario, sizeof(struct Horario), -1, ponteiroArquivoHORARIO)!= 1){
//        if(mostrar_debug == 1) {
//            printarMensagem("10 - Problemas na leitura do registro!!!");
//        }
//        horario.codigo[0] = '0';
//        return "0000-00-00-0";
//    }
//
//    int tamanhoCodigo = (int) strlen(horario.codigo);
//
//    if(tamanhoCodigo <= 0){
//        return "0000-00-00-0";
//
//    } else {
//        return horario.codigo;
//    }
//}

// #################################
// BUSCAR REGISTRO DE HORARIO POR CODIGO
// Uma funçao para retornar o registro (posicao no arquivo) procurando pelo codigo.
// RETORNO:
//  -  O numero do registro, caso encontre;
//  - -1 caso, nao encontre.
int buscarRegistroHorarioPorCod(char codigo[], int mostrar_debug) {
    struct Horario horario;
    int contadorCodigo = -1;
    
    // Testando se o arquivo foi aberto com sucesso
    if(ponteiroArquivoHORARIO != NULL) {
        if(mostrar_debug == 1) {
            printf("\n\nArquivo %s foi aberto com sucesso\n\n", BIN_FUN);
        }
        
    } else {
        if(mostrar_debug == 1) {
            printf("\n\nERRO: O arquivo %s nao foi aberto e criado\n", BIN_FUN);
        }
        system ("pause");
        exit(1);
    }
    
    rewind(ponteiroArquivoHORARIO);
    // Procura em todos os registros do documento.
    while(fread(&horario, sizeof(struct Horario), 1, ponteiroArquivoHORARIO)) {
        // Incrementa ++ porque comeca com -1.
        contadorCodigo += 1;
        
        // Compara o cod recebido.
        // A funcao strcmp() compara duas 'Strings', tem tres tipos de retorno:
        // - -1 = se a primeira 'String' ocorre primeiro que a segunda;
        // - 0  = se as duas 'Strings' sao iguais;
        // - 1  = se a segunda string ocorre primeiro que a primeira.
        if(strcmp(horario.codigo, codigo) == 0) {
            // Se encontrar, retorna a poisicao(linha) do registro.
            return  contadorCodigo;
        }
    }
    
    // Se nao achar o codigo, retorna -1 para indicar que nao achou.
    if(mostrar_debug == 1) {
        printf("\n\nERRO: registro nao encontrado.");
    }
    contadorCodigo = -1;
    
    return contadorCodigo;
}

// #################################
// BUSCAR HORARIO POR CODIGO
// Uma funçao para retornar o horario procurando pelo codigo.
// RETORNO:
//  - A instancia com os dados encontrados.
//  - A instancia de Agendamento com os dados encontrados;
//  - 'horario.codigo = -1' caso nao encontre.
struct Horario buscarHorarioPorCod(int codigo, int mostrar_debug) {
    struct Horario horario;
    int contadorCodigo = -1, indice = 0;
    
    for(indice = 0; indice < 13; indice++) {
        if((indice == 4) || (indice == 7) || (indice == 10)) {
            horario.codigo[indice] = '-';
            
        }
        horario.codigo[indice] = '0';
    }
    
    
    // Testando se o arquivo foi aberto com sucesso
    if(ponteiroArquivoHORARIO != NULL) {
        if(mostrar_debug == 1) {
            printf("\n\nArquivo %s foi aberto com sucesso\n\n", BIN_FUN);
        }
        
    } else {
        if(mostrar_debug == 1) {
            printf("\n\nERRO: O arquivo %s nao foi aberto e criado\n", BIN_FUN);
        }
        system ("pause");
        exit(1);
    }
    
    rewind(ponteiroArquivoHORARIO);
    // Procura em todos os registros do documento.
    while(fread(&horario, sizeof(struct Horario), 1, ponteiroArquivoHORARIO)) {
        // Incrementa ++ porque comeca com -1.
        contadorCodigo += 1;
        
        // Compara o cod recebido.
        // A funcao strcmp() compara duas 'Strings', tem tres tipos de retorno:
        // - -1 = se a primeira 'String' ocorre primeiro que a segunda;
        // - 0  = se as duas 'Strings' sao iguais;
        // - 1  = se a segunda string ocorre primeiro que a primeira.
        if(strcmp(horario.codigo, intParaString(codigo, 10)) == 0) {
            // Se encontrar, retorna a poisicao(linha) do registro.
            return horario;
        }
    }
    
    // Se nao achar o codigo, retorna -1 para indicar que nao achou.
    if(mostrar_debug == 1) {
        printf("\n\nERRO: registro nao encontrado.");
    }
    
    return horario;
}

//// #################################
//// BUSCAR HORARIO POR CODIGO
//// Uma funçao para retornar o horario procurando pelo codigo.
//// RETORNO:
////  - A instancia com os dados encontrados.
////  - A instancia de Agendamento com os dados encontrados;
////  - 'horario.codigo = -1' caso nao encontre.
//struct Horario buscarHorarioPorAno(char cpf[12], int mostrar_debug) {
//    struct Horario horario;
//    int contadorCodigo = -1;
//
//    horario.codigo = -1;
//
//    // Testando se o arquivo foi aberto com sucesso
//    if(ponteiroArquivoHORARIO != NULL) {
//        if(mostrar_debug == 1) {
//            printf("\n\nArquivo %s foi aberto com sucesso\n\n", BIN_FUN);
//        }
//
//    } else {
//        if(mostrar_debug == 1) {
//            printf("\n\nERRO: O arquivo %s nao foi aberto e criado\n", BIN_FUN);
//        }
//        system ("pause");
//        exit(1);
//    }
//
//    rewind(ponteiroArquivoHORARIO);
//    // Procura em todos os registros do documento.
//    while(fread(&horario, sizeof(struct Horario), 1, ponteiroArquivoHORARIO)) {
//        // Incrementa ++ porque comeca com -1.
//        contadorCodigo += 1;
//
//        // Compara o cod recebido.
//        if(horario.cpf == cpf) {
//            // Se encontrar, retorna a poisicao(linha) do registro.
//            return horario;
//        }
//    }
//
//    // Se nao achar o codigo, retorna -1 para indicar que nao achou.
//    if(mostrar_debug == 1) {
//        printf("\n\nERRO: registro nao encontrado.");
//    }
//
//    return horario;
//}

// #################################
// DESOCUPAR UM HORARIO
// Encontra a posicao do registro pelo numero que representa a linha na qual está
// e deixa-o 'livre';
// PARAMETRO:
//   - registro: int da 'linha' que está o referido registro.
void ocuparHorario(int registro, int mostrar_debug) {
    struct Horario horarioAux;
    
    if(fseek(ponteiroArquivoHORARIO, (registro)*sizeof(horarioAux), SEEK_SET) != 0){
        printarMensagem("Registro inexistente ou problemas no posicionamento!!!");
        return;
    }
    
    if(fread(&horarioAux, sizeof(struct Horario), 1, ponteiroArquivoHORARIO)!= 1){
        printarMensagem("12 - Problemas na leitura do registro!!!");
        return;
    }
    
    if(horarioAux.ocupado == '*'){
        printarMensagem("Registro já está ocupado!!!\n\n");
        return;
    }
    
    horarioAux.ocupado = '*';
    
    // recuar um registro no arquivo
    fseek(ponteiroArquivoHORARIO, -(int) sizeof(struct Horario), SEEK_CUR);
    // reescrever o registro;
    fwrite(&horarioAux, sizeof(struct Horario), 1, ponteiroArquivoHORARIO);
    fflush(ponteiroArquivoHORARIO); /*despejar os arquivos no disco rígido*/
}

// #################################
// DESOCUPAR UM HORARIO
// Encontra a posicao do registro pelo numero que representa a linha na qual está
// e deixa-o 'livre';
// PARAMETRO:
//   - registro: int da 'linha' que está o referido registro.
void desocuparHorario(int registro, int mostrar_debug) {
    struct Horario horarioAux;
    
    if(fseek(ponteiroArquivoHORARIO, (registro)*sizeof(horarioAux), SEEK_SET) != 0){
        printarMensagem("Registro inexistente ou problemas no posicionamento!!!");
        return;
    }
    
    if(fread(&horarioAux, sizeof(struct Horario), 1, ponteiroArquivoHORARIO)!= 1){
        printarMensagem("12 - Problemas na leitura do registro!!!");
        return;
    }
    
    if(horarioAux.ocupado == ' '){
        printarMensagem("Registro já está livre!!!\n\n");
        return;
    }
    
    horarioAux.ocupado = ' ';
    
    // recuar um registro no arquivo
    fseek(ponteiroArquivoHORARIO, -(int) sizeof(struct Horario), SEEK_CUR);
    fseek(ponteiroArquivoHORARIO, -(int) sizeof(struct Horario), SEEK_CUR);
    // reescrever o registro;
    fwrite(&horarioAux, sizeof(struct Horario), 1, ponteiroArquivoHORARIO);
    fflush(ponteiroArquivoHORARIO); /*despejar os arquivos no disco rígido*/
}

// #################################
// LER OS DADOS DE HORARIO
void lerDadosHorario(struct Horario *horario) {
    
    //    fflush(stdin);
    //    printf("Nome : ");
    //    gets(horario->nome); fflush(stdin);
    //
    //    //    printf("CPF  : ");
    //    //    gets(horario->cpf); fflush(stdin);
    //    //TODO: Testar depois
    //    receberValidarCPF(horario->cpf);
    //
    //    printf("Senha: ");
    //    gets(horario->senha); fflush(stdin);
    //
    //    printf("Cargo: ");
    //    scanf("%d", &horario->cargo); // Horario 0 = adm
    //    fflush(stdin);
    //
    //    horario->ativo = ' '; // Qualquer coisa menos '*' significa ativo
}

// #################################
// PRINTAR UM PERFIL DE HORARIO:
// mostra na tela os dados existentes no registro
void printarHorarioLista(struct Horario horario, int mostrar_debug) {
    //TODO: criar View de perfil HORARIO.
    
    if(horario.ocupado == ' ') {
        printf("%-5s", " ");
        
    } else {
        printf("%-5s", "XXXXX\n");
    }
    //    printf("%05d|%-30s|%-15s|%-30s\n", horario.codigo, horario.nome, formatarCPF(horario.cpf, mostrar_debug), horario.senha);
}

void printarHorarioTopicos(struct Horario horario, int mostrar_debug) {
    
    if(horario.ocupado == ' ') {
        printf("%-6s", " ");
        
    } else {
        printf("%-6s", "XXX");
    }
}

// #################################
// LER TODOS PERFIS DE HORARIO
void printarTodosRegistrosHorario(int mostrar_debug, int tema) {
    struct Horario horario;
    int n_Linhas = 0;
    
    // Volta o ponteiro para o inicio.
    rewind(ponteiroArquivoHORARIO);
    
    printf("HORARIOS\n");
    interfaceLinhaSeparadora(150, tema);
    printf("%-5s|%-30s|%-15s|%-30s\n", "COD", "NOME", "CPF", "SENHA");
    interfaceLinhaSeparadora(150, tema);
    
    while(1){
        if(fread(&horario, sizeof(horario), 1, ponteiroArquivoHORARIO)!= 1)break; /*Sair do laço*/
        //        if(horario.ocupado == '*') continue; /*Passa ao proximo*/
        printarHorarioLista(horario, mostrar_debug);
        //        printarHorarioTopicos(horario, mostrar_debug);
        n_Linhas++;
        if(n_Linhas%20 == 0)
            printarMensagem("Pressione <Enter> para continuar .  .  .");
    }
}

//// #################################
//// SALVAR DADOS DE HORARIO
//// RETORNO:
////  -    0: se nao houve erros;
////  - != 0: se houve erro(s);
//int salvarRegistroHorario(struct Horario horario, int mostrar_debug) {
//    int resultado = 0;
//
//    // Adicionar codigo, auto-incrementando,
//    // pega o codigo do ultimo registro e incrementa.
//    int numeroRegistro = acessarUltimoCodigoHorario(mostrar_debug) + 1;
//
//    // Poe o novo horario no final do arquivo.
//    fseek(ponteiroArquivoHORARIO, 0L, SEEK_END);
//    if(fwrite(&horario, sizeof(horario), 1, ponteiroArquivoHORARIO)!= 1) {
//        if(mostrar_debug == 1) {
//            printarMensagem("Adicionar horario: Falhou a escrita do registro");
//        }
//
//        resultado = 1;
//    }
//
//    // Retornando o valor do resultado.
//    return(resultado);
//}


#endif /* Horario_h */
