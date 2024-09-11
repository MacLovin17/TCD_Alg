#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <locale.h>
#include <string.h>
#define TAM 3
#define MAX 100

void limpar_terminal(){
#ifdef _WIN32
    system("cls");
#endif
}

/*
identificador único (um código inteiro), nome, local, data da realização, custos de organização, quantidade máxima de ingressos colocados à venda e valor da entrada.

50% devem ser entradas do tipo básica, 30% entradas do tipo normal e 20% entradas do tipo especial.

valor da entrada básica = custo de organização / pela quantidade máxima de ingressos colocados à venda.

Para eventos open bar, deverá ser acrescentado um valor que corresponde a 175% do valor unitário de cada bebida que será servida.

O valor da entrada normal = ao valor da entrada básica mais 10% desse mesmo valor.

Já o valor da entrada especial é = valor da entrada normal mais 15% desse mesmo valor.
*/

typedef struct {
    char nome[MAX];
    float t_alcool;
    float v_unit;
}Bebida;

typedef struct {
    int C_I;
    char nome[MAX];
    char local[MAX];
    char data[MAX];
    int cap_max;
    float c_org;
    float v_normal, v_basico, v_especial, v_total;
    int i_vend_basic, i_vend_normal, i_vend_espec;
    Bebida bebidas[3];
    int op_bar;
}Evento;

Evento eventos[MAX];
int tot_event = 0;

void cadastro(){
        if (tot_event >=MAX){
            printf("Limite de eventos atigindos.\n");
            return;
        }
    Evento e;
    printf("Identificador unico (0 para terminar):\n");
    scanf("%d", &e.C_I);
        if(e.C_I == 0) return;

        printf("Informe o nome do evento:\n");
        getchar();
            if (fgets(e.nome, sizeof(e.nome), stdin) != NULL) {
                size_t len = strlen(e.nome);
                if (len > 0 && e.nome[len - 1] == '\n') {
                    e.nome[len - 1] = '\0';
                }
            }
        printf("Informe o local do evento:\n");
        getchar();
            if (fgets(e.local, sizeof(e.local), stdin) != NULL) {
                size_t len = strlen(e.local);
                if (len > 0 && e.local[len - 1] == '\n') {
                    e.local[len - 1] = '\0';
                }
            }
        printf("Informe a data do evento:\n");
        getchar();
            if (fgets(e.data, sizeof(e.data), stdin) != NULL) {
                size_t len = strlen(e.data);
                if (len > 0 && e.data[len - 1] == '\n') {
                    e.data[len - 1] = '\0';
                }
            }
        printf("Capacidade maxima: ");
            scanf("%d", &e.cap_max);
        printf("Custo de organizacao: ");
            scanf("%f", &e.c_org);

        e.v_basico = e.c_org / e.cap_max;
        e.v_normal = e.v_basico * 1.10;
        e.v_especial = e.v_normal * 1.15;

        e.i_vend_basic = 0;
        e.i_vend_normal = 0;
        e.i_vend_espec = 0;
        getchar();
        printf("Esse evento e open bar? (1-Sim | 0-Nao): \n");
        scanf("%d", &e.op_bar);
        if(e.op_bar == 1){
            for(int i=0; i<3; i++){
                getchar();
                printf("Nome da bebida %d: ", i + 1);
                
                if (fgets(e.bebidas[i].nome, sizeof(e.bebidas[i].nome), stdin) != NULL) {
                    size_t len = strlen(e.bebidas[i].nome);
                    if (len > 0 && e.bebidas[i].nome[len - 1] == '\n') {
                        e.bebidas[i].nome[len - 1] = '\0';
                    }
                }
                
                printf("Teor alcoolico da bebida %d: ", i + 1);
                scanf("%f", &e.bebidas[i].t_alcool);
                printf("Valor unitario da bebida %d: ", i + 1);
                scanf("%f", &e.bebidas[i].v_unit);
                e.bebidas[i].v_unit += e.bebidas[i].v_unit *1.75;
            }
            e.v_normal = e.v_basico * 1.10;
            e.v_especial = e.v_normal * 1.15;
        }
        eventos[tot_event++] = e;
        printf("Evento cadastrado com sucesso!\n");
}

void pesquisa(){
    int aux_CI;

    printf("Informe seu identificador unico: (0) para sair.\n");
    scanf("%d", &aux_CI);
    if (aux_CI == 0){
        return;
    }
    
    for (int i = 0; i < tot_event; i++){
        if (eventos[i].C_I == aux_CI){
            printf("Nome do evento %s: \n", eventos[i].nome);
            printf("Local: %s\n", eventos[i].local);
            printf("Data: %s\n", eventos[i].data);
            printf("Capacidade Máxima: %d\n", eventos[i].cap_max);
            printf("Custo de Organização: %.2f\n", eventos[i].c_org);
            printf("Valor da Entrada Básica: %.2f\n", eventos[i].v_basico);
            printf("Valor da Entrada Normal: %.2f\n", eventos[i].v_normal);
            printf("Valor da Entrada Especial: %.2f\n", eventos[i].v_especial);

            for (int j = 0; j < 3; j++){
                printf("Bebida %d: %s\n", j+1, eventos[i].bebidas[j].nome);
            }
        }
        else{
            printf("Evento nao cadastrado. \n");
        } 
    }
    return pesquisa();
}

void ingressos(){
    int aux_CI;

    printf("Informe seu identificador unico: (0) para sair.\n");
    scanf("%d", &aux_CI);
    if (aux_CI == 0){
        return;
    }

    for (int i = 0; i < tot_event; i++){
        if (eventos[i].C_I == aux_CI){
            printf("Nome do evento %s: \n", eventos[i].nome);

            eventos[i].i_vend_basic =  (eventos[i].cap_max * 0.5) * eventos[i].v_basico;
            eventos[i].i_vend_normal = (eventos[i].cap_max * 0.3) * eventos[i].v_normal;
            eventos[i].i_vend_espec =  (eventos[i].cap_max * 0.2) * eventos[i].v_especial;

            eventos[i].v_total = (eventos[i].i_vend_basic+eventos[i].i_vend_normal+eventos[i].i_vend_espec);

            printf("Quantidade vendida do ingresso basico: %.2f\n", (eventos[i].cap_max * 0.5));
            printf("Quantidade vendida do ingresso basico: %.2f\n", (eventos[i].cap_max * 0.3));
            printf("Quantidade vendida do ingresso basico: %.2f\n", (eventos[i].cap_max * 0.2));

            

        }
        else{
            printf("Evento nao cadastrado. \n");
        } 
    }
    return ingressos();
}

void resultado(){
    int aux_CI;

    printf("Informe seu identificador unico: (0) para sair.\n");
    scanf("%d", &aux_CI);
    if (aux_CI == 0){
        return;
    }

    for (int i = 0; i < tot_event; i++){
        if (eventos[i].C_I == aux_CI){
            if (eventos[i].v_total > eventos[i].c_org){
                        printf("O Evento obteve um lucro de R$%.2f\n", eventos[i].v_total - eventos[i].c_org);
                    }
                    else{
                        printf("O evento obteve um prejuízo de R$%.2f\n",eventos[i].v_total - eventos[i].c_org);
                    }
        }
        else{
            printf("Evento nao cadastrado. \n");
        } 
    }
    return resultado();
}




int main(){

    setlocale(LC_ALL,"portuguese");
    int opc;
    char cond='S';

    do
    {
    printf ("*************************************************************************************************************************\n");
    printf ("                                       INSTITUTO FEDERAL DO TRIANGULO MINEIRO - IFTM");
    printf ("\n                                                      CAMPUS PARACATU");
    printf ("\n                                           ANALISE E DESENVOLVIMENTO DE SISTEMAS\n");
    printf (" PROFESSOR: Gustavo ALexandre.\n");
    printf (" ALUNO: Eriky Gomes.\n");
    printf ("*************************************************************************************************************************\n\n");
    printf ("                                              Trabalho de Conclusao da Disciplina (TCD) \n\n");
    printf ("=========================================================================================================================\n\n");
    printf ("                                                           Menu de Opcoes: \n");
    printf ("Selecione o opcao de acordo com seu numero:\n");
    printf ("=========================================================================================================================\n");
    printf ("\t(1) Cadastrar evento\n");
    printf ("\t(2) Pesquisar evento\n");
    printf ("\t(3) Ingressos vendidos\n");
    printf ("\t(4) Exibir resultado por evento\n");
    printf ("\t(5) Exibir resultado geral\n");
    printf ("\t(6) Sair\n");
    printf ("=========================================================================================================================\n");

    scanf("%d", &opc);

    if (opc < 0 || opc>6){
        do{
            printf("Informe um opcao valida:\n");
            scanf("%d", &opc);
        }while(opc < 0 || opc>6);
    }
    
    switch (opc){
        case 1:
            limpar_terminal();
            printf("\t(1) Cadastrar evento\n");
            cadastro();
            printf("Deseja voltar ao menu? (S) para sim, (N) para nao\n");
            getchar();
            scanf("%c", &cond);
        break;

        case 2:
            limpar_terminal();
            printf("\t(2) Pesquisar evento\n");
            pesquisa();
            printf("Deseja voltar ao menu? (S) para sim, (N) para nao\n");
            getchar();
            scanf("%c", &cond);
        break;

        case 3:
            limpar_terminal();
            printf("\t(3) Ingressos vendidos\n");
            ingressos();
            printf("Deseja voltar ao menu? (S) para sim, (N) para nao\n");
            getchar();
            scanf("%c", &cond);
        break;

        case 4:
            limpar_terminal();
            printf("\t(4) Exibir resultado por evento\n");
            resultado();
            printf("Deseja voltar ao menu? (S) para sim, (N) para nao\n");
            getchar();
            scanf("%c", &cond);
        break;
        
        
    }

    limpar_terminal();
    } while (cond =='S' || cond == 's');




    return 0 ;
}
