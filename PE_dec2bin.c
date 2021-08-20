#include <stdio.h>
#include <stdlib.h>
#define tamanhoMax 1000
 
struct pilha {
    int elementos[tamanhoMax];
    int topo;
};
typedef struct pilha tipoPilha;
 
void inicializaPilha(tipoPilha *pilhaAux) {
    int i;
    for (i=0; i<=tamanhoMax-1; i++)
        pilhaAux->elementos[i] = 0;
    pilhaAux->topo = -1;
}
 
int empilhar (tipoPilha *pilhaAux, int val){
    if (pilhaAux->topo >= tamanhoMax-1) // pilha cheia
        return -1; // aborta a funcao
 
    else {
        pilhaAux->topo++;
        pilhaAux->elementos[pilhaAux->topo] = val;
        return 0; // sucesso
    }
}
 
int desempilhar (tipoPilha *p){
    int aux;
    if(p->topo == 0){
        return -1;
    }else{
        aux = p->elementos[p->topo];
        p->topo --;
        return aux;
    }
}
 
void imprimir (tipoPilha *p){
    int i;
    //if (p->topo != NULL){
        for (i = p->topo; i >= 0; i--){
            printf("%d", p->elementos[i]);
        }
    //}
    /*else
        printf("pilha vazia");*/
}
 
void troca (tipoPilha *p){
    int i;
    for (i = p->topo; i >= 0; i--){
        if (p->elementos[i] == 0)
            p->elementos[i] = 1;
        else
            p->elementos[i] = 0;
    }
}
 
void binPdec (tipoPilha *p, int cont){
    int i, dec, vet[1000], soma = 0;
    for(i = 0; i < cont; i++){
        dec = pow(2, i) * (p->elementos[i]);
        vet[i] = dec;
        soma = soma + vet[i];
    }
    printf("%d", soma);
}
 
int main (){
 
    tipoPilha pilha;
    inicializaPilha(&pilha);
 
    int v, L, i = 1, cont = 0;
 
    scanf("%d", &L);
 
    while(i <= L && L <= 100){
 
        scanf("%d", &v);
 
        printf("%d ", v);
 
        while(v > 0){
            empilhar(&pilha, v % 2);
            v = v / 2;
            cont++; 
        }
        imprimir(&pilha);
 
        troca(&pilha);
        
        printf(" ");
        imprimir(&pilha);
 
        printf(" ");
        binPdec(&pilha, cont);
 
        inicializaPilha(&pilha);
 
        printf("\n");
        
        i++;
    }
}