#include <stdio.h>
#include <stdlib.h>
#define tamanhoMAX 100

struct filaCircular {
    int primeiro;
    int ultimo;
    int tamanhofila;
    int elementos[tamanhoMAX];
};
typedef struct filaCircular tipoFC;

void inicializaFila (tipoFC *filaAux)
{
    // inicializa a fila
    int i;
    filaAux->primeiro = -1;
    filaAux->ultimo = -1;
    for (i=0; i<tamanhoMAX; i++)
    filaAux->elementos[i]=0;
    filaAux->tamanhofila = 0;
}

int filaVazia(tipoFC *filaAux){
    if ((filaAux->primeiro==filaAux->ultimo) &&
    (filaAux->ultimo==-1))
    return 1; // fila está vazia
    else return 0; // fila não está vazia
}

int filaCheia (tipoFC *filaAux){
    if (((filaAux->ultimo + 1) % tamanhoMAX) == filaAux->primeiro)
    return 1; // fila está cheia
    else return 0; // fila não está cheia
}

void insereElemento (tipoFC *filaAux, int info)
{ // se a fila estiver vazia insere o primeiro elemento
    if (filaVazia(filaAux)==1)
    { filaAux->primeiro = 0;
    filaAux->ultimo = 0;
    filaAux->elementos[0]=info;
    filaAux->tamanhofila++; 

    } else if (filaCheia(filaAux)==0){ // se a fila não estiver cheia podemos inserir
    int posicao = ((filaAux->ultimo + 1) % tamanhoMAX);
    filaAux->elementos[posicao] = info;
    filaAux->ultimo = posicao;
    filaAux->tamanhofila++;
    } 
      
}

void retiraElemento (tipoFC *filaAux){
    if (filaAux->tamanhofila == 1){ 
        inicializaFila(filaAux);
    }
    else{
        if(filaVazia(filaAux) == 0){ 
            filaAux->primeiro = (filaAux->primeiro + 1) % tamanhoMAX;
            filaAux->tamanhofila--;
        }
    }
}

void conclusao (tipoFC *filaAux){ 
    int p;
    if (filaAux->tamanhofila > 1){ 
        p = filaAux->elementos[filaAux->primeiro];
        filaAux->primeiro = (filaAux->primeiro + 1) % tamanhoMAX; 

        int posicao = ((filaAux->ultimo + 1) % tamanhoMAX);
        filaAux->elementos[posicao] = p;
        filaAux->ultimo = posicao;
    }
}

void imprimir (tipoFC *filaAux){
    int i, j = filaAux->ultimo;
    if (filaAux->tamanhofila > 0){
        for (i = filaAux->ultimo; i >= filaAux->primeiro; i--){
            printf ("%d ", filaAux->elementos[j]);
            j--;  
        }
        printf("\n");
    } 
}

int main (){

    int i = 0, L, id, acao;
    tipoFC fila;
    inicializaFila(&fila);

    scanf("%d", &L);
    
    while( i < L){

        scanf("%d", &acao);

        if (acao == 1){ 
            scanf("%d", &id);
            insereElemento(&fila, id); 
        }
        if (acao == 2){
            if(filaVazia(&fila) == 0)
                retiraElemento(&fila); 
            else
                printf("vazia\n");
        }
        if (acao == 3){
            if(filaVazia(&fila) == 0)
                conclusao(&fila); 
            else
                printf("vazia\n");
        }
    i++;
    }
    imprimir(&fila);
}