#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define maxtam 50

typedef struct {
    float item [maxtam];
    int topo;
}TPilha;

void TPilha_Inicia (TPilha *p){
    p->topo = - 1;
}

float TPilha_Vazia(TPilha *p){
    if(p->topo == - 1){
        return 1;
    }else {
        return 0;
    }
}

float TPilha_Cheia (TPilha *p){
    if (p->topo == maxtam - 1){
        return 1;
    }else{
        return 0;
    }
}

void TPilha_Insere(TPilha *p, float n){
    if(TPilha_Cheia(p) == 1) {
        printf("ERRO: Pilha Cheia\n");
        printf("Progama finalizado");
        exit(0);
    }else {
        p->topo ++;
        p->item[p->topo] = n;
    }
}

float TPilha_Remove (TPilha *p){
    float aux;
    if(TPilha_Vazia(p) == 1){
        printf("ERRO: Pilha vazia\n");
        printf("Progama finalizado");
        exit(0);
    }else{
        aux = p->item[p->topo];
        p->topo --;
        return aux;
    }
}

float Operacao(char aux, float dado1, float dado2) {
    switch(aux) {
        case '+':
            return dado2 + dado1;
            break;
        case '-':
            return dado2 - dado1;
            break;
        case '*':
            return dado2 * dado1;
            break;
        case '/':
            if(dado1 == 0){
                printf("divisao por 0\n");
                printf("Programa finalizado");
                exit(0);
            }else{
            return dado2 / dado1;
            break;}
    }
    printf("Caracter nao e um operador\n");
    printf("Programa finalizado");
    exit(0);
}
void Ler_Alfabetica (TPilha *p, char expressao[maxtam]) {

    int pos_vetor;
    int conv_ASCII;
    float letra_valor[52];
    int i;
    int b;
    char expressao_num [maxtam];
    gets(expressao);
    for(i = 0; i < strlen(expressao); i++) {
        if ((expressao[i] >= 'a' && expressao[i] <= 'z') || (expressao[i] >= 'A' && expressao[i] <= 'Z')){
            conv_ASCII = expressao[i];
            if (conv_ASCII >= 65 && conv_ASCII <=90){
                pos_vetor = conv_ASCII - 65;
            }
            if (conv_ASCII >= 97 && conv_ASCII <=122){
                pos_vetor = conv_ASCII - 71;
            }
            
            scanf("%f", &letra_valor[pos_vetor]);
        } 
    }
    char aux [2];
    for(i = 0; i < strlen(expressao); i++) {
        if ((expressao[i] >= 'a' && expressao[i] <= 'z') || (expressao[i] >= 'A' && expressao[i] <= 'Z')){
            conv_ASCII = expressao[i];
            if (conv_ASCII >= 65 && conv_ASCII <=90){
                pos_vetor = conv_ASCII - 65;
            }
            if (conv_ASCII >= 97 && conv_ASCII <=122){
                pos_vetor = conv_ASCII - 71;
            }
            TPilha_Insere(p, letra_valor[pos_vetor]);
        }

        else{
            float dado1, dado2;
            dado1 = TPilha_Remove(p);
            dado2 = TPilha_Remove(p);
            float res = Operacao(expressao[i], dado1, dado2);
            
            TPilha_Insere(p, res);
        }
    }
}

int main(){
    TPilha *p = (TPilha*)malloc(sizeof(TPilha));
    TPilha_Inicia(p);
    

    char expressao [maxtam];
    Ler_Alfabetica (p, expressao);
    float res = TPilha_Remove(p);
    printf("%f", res);
   


    return 0;
}