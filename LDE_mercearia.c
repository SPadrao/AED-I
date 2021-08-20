#include <stdio.h>
#include <stdlib.h>
 
struct elemento{
    int ID;
    int qntd;
    float lucro;
    float preco;
    struct elemento *prox;
};
 
typedef struct elemento elemento;
 
struct listaDE{
    elemento *primeiro;
    elemento *ultimo;
    int tamanhoLista;
};
 
typedef struct listaDE listaDE;
 
void inicializaLista(listaDE *listaAux){
    listaAux->primeiro = NULL;
    listaAux->ultimo = NULL;
    listaAux->tamanhoLista = 0;
}
 
void insereElementoOrdenado(listaDE *listaAux, int id, int qntd, float preco){
 
    elemento *pEl;
    elemento *anterior = NULL;
 
    if (listaAux -> tamanhoLista == 0){
        elemento *novoElem = (elemento*)malloc(sizeof(elemento));
        /*if (novoElem == NULL){ //Verifica se a alocacao foi realizada
            printf("Erro de alocacao do novo elemento.\n");
            return;
        }*/
        novoElem -> ID = id;
        novoElem -> qntd = qntd;
        novoElem -> preco = preco;
        novoElem -> lucro = 0;
        novoElem -> prox = NULL;
        listaAux -> primeiro = novoElem;
        listaAux -> ultimo = novoElem;
        listaAux->tamanhoLista++;
 
    } else{
        pEl = listaAux -> primeiro;
        while(pEl != listaAux -> ultimo && pEl -> ID != id)
            pEl = pEl -> prox;
 
        if(pEl -> ID == id){
            printf ("ja existe\n");
        }else{
            elemento *novoElem = (elemento*)malloc(sizeof(elemento));
            /*if (novoElem == NULL){ //Verifica se a alocacao foi realizada
                printf("Erro de alocacao do novo elemento.\n");
                return;
            }*/
            novoElem -> ID = id;
            novoElem -> qntd = qntd;
            novoElem -> preco = preco;
            novoElem -> lucro = 0;
 
            //adicionar na posicao correta, ordenado do maior preco para o menor preco
            pEl = listaAux -> primeiro;
            while(pEl != NULL && pEl -> preco > preco){
                anterior = pEl;
                pEl = pEl -> prox;
            }
 
            if(pEl == listaAux -> primeiro){
                novoElem -> prox = pEl;
                listaAux -> primeiro = novoElem;
            }
            else if (pEl == NULL){
                anterior -> prox = novoElem;
                novoElem -> prox = NULL;
                listaAux -> ultimo = novoElem;
            }
            else{
                anterior -> prox = novoElem;
                novoElem -> prox = pEl;
            }
        listaAux->tamanhoLista++;
        }
    }
}
 
void retiraElemento(listaDE *listaAux, int id){
 
    elemento *pEl;
    elemento *anterior = NULL;
 
    if (listaAux -> tamanhoLista == 0){
        printf("nao existe\n");
    }else{
        pEl = listaAux->primeiro;
 
        while(pEl!= listaAux -> ultimo -> prox && pEl -> ID != id){
            anterior = pEl;
            pEl = pEl -> prox;
        }
 
        if (pEl == listaAux -> ultimo -> prox){
            printf("nao existe\n");
 
        }else{
            if (pEl == listaAux -> primeiro){
                listaAux -> primeiro = pEl -> prox;
                listaAux->tamanhoLista--;
                free(pEl);
                pEl = NULL;
            } else if (pEl == listaAux -> ultimo){
                listaAux -> ultimo = anterior;
                listaAux -> ultimo -> prox = NULL;
                listaAux->tamanhoLista--;
                free(pEl);
                pEl = NULL;
            }else{
                anterior -> prox = pEl -> prox;
                listaAux->tamanhoLista--;
                free(pEl);
                pEl = NULL;
            }
        }
    }
}
 
void aumentaQntd(listaDE *listaAux, int ID, int qntd){
    elemento *pEl;
 
    pEl = listaAux->primeiro;
    while(pEl != listaAux -> ultimo -> prox && pEl -> ID != ID)
        pEl = pEl->prox;
 
    if(pEl != listaAux -> ultimo -> prox){
        pEl -> qntd = pEl -> qntd + qntd;
    }
    else
        printf("nao existe\n");
}
 
void compra(listaDE *listaAux, int ID){
    elemento *pEl;
 
    pEl = listaAux -> primeiro;
    while(pEl != listaAux -> ultimo -> prox && pEl -> ID != ID)
        pEl = pEl -> prox;
 
    if(pEl != listaAux -> ultimo -> prox){
        if (pEl -> qntd > 0){
            pEl -> qntd = pEl -> qntd - 1;
            pEl -> lucro = pEl -> lucro + pEl -> preco;
        } else{
            printf("nao existe\n");
        }
    }
    else{
        printf("nao existe\n");
    }
}
 
/*void imprimir (listaDE *listaAux, int flagprint){
    elemento *p = NULL; //aqui
    if (flagprint == 1){
        p = listaAux -> primeiro;
        printf("\n");
        while(p != listaAux -> ultimo -> prox){
            printf("\nID: %d ", p -> ID);
            printf("\nqntd: %d ", p -> qntd);
            printf("\npreco: %f ", p -> preco);
            printf("\nlucro: %f", p -> lucro);
            printf("\ntamanho: %d\n\n", listaAux -> tamanhoLista);
            p = p -> prox;          
        }
    }
}*/
 
void imprimirLucro (listaDE *listaAux){
    elemento *p;
    p = listaAux->primeiro;
 
    p = listaAux -> primeiro;
    while(p != listaAux -> ultimo -> prox ){
        printf ("%d %f\n", p -> ID, p -> lucro);
        p = p -> prox;
    }
}
 
int main (){
 
    listaDE lista;
    inicializaLista (&lista);
    int L, ID, qntd, acao, i = 1, cont = 0;
    int flagprint;
    float preco;
 
    flagprint = 0; //1 se quiser imprimir a lista e 0 caso contrario
    scanf("%d", &L);
 
    while(i <= L && L <= 100){
        scanf("%d", &acao);
 
        if (acao == 1){
            scanf ("%d %d %f", &ID, &qntd, &preco);
            if(ID >= 0 && qntd >= 0 && preco > 0)
                insereElementoOrdenado(&lista, ID, qntd, preco);
            //imprimir(&lista, flagprint);
        }
        if (acao == 2){
            scanf ("%d %d", &ID, &qntd);
            if(ID >= 0 && qntd > 0)
                aumentaQntd(&lista, ID, qntd);
            else
                printf("nao existe");
            //imprimir(&lista, flagprint);
        }
        if (acao == 3){
            scanf ("%d", &ID);
            if(ID >= 0)
                compra(&lista, ID);
            else
                printf("nao existe");
            //imprimir(&lista, flagprint);
        }
        if (acao == 4){
            scanf ("%d", &ID);
            if(ID >= 0)
                retiraElemento(&lista, ID);
            else
                printf("nao existe");
            //imprimir(&lista, flagprint);
        }
        i++;
    }
    imprimirLucro(&lista);
    return 0;
}