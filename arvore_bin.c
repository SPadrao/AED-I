#include <stdio.h>
#include <stdlib.h>

struct noArvoreBB {
    int chave;
    struct noArvoreBB* esq;
    struct noArvoreBB* dir;
};
typedef struct noArvoreBB tipoABB;

tipoABB *inicializa() {
    return NULL;
}

tipoABB *insereABB(tipoABB *Aux, int chave) {
    if(Aux == NULL){ 
        Aux = malloc(sizeof(tipoABB));
        Aux->chave = chave;
        Aux->esq = NULL;
        Aux->dir = NULL;
    }
    
    else if(chave < Aux->chave)
        Aux->esq = insereABB(Aux->esq, chave); 
    
    
    else if(chave > Aux->chave)
        Aux->dir = insereABB(Aux->dir, chave); 
    
    return Aux;
}

tipoABB* MenorValor(tipoABB* Aux){ 
    while(Aux->esq != NULL)
        Aux = Aux->esq;
    return Aux;
}

tipoABB* removeABB(tipoABB* Aux, int chave){ 
    if(Aux == NULL) 
        return Aux;
    
    if(chave < Aux->chave)
        Aux->esq = removeABB(Aux->esq, chave);
    else
        if(chave > Aux->chave)
            Aux->dir = removeABB(Aux->dir, chave);
        else{
            if(Aux->esq == NULL)
                return Aux->dir;
            
            else
                if(Aux->dir == NULL)
                    return Aux->esq;
            
            tipoABB* temp = MenorValor(Aux->dir);
            Aux->chave = temp->chave;
            Aux->dir = removeABB(Aux->dir, temp->chave);
        }
    return Aux;
}

tipoABB *busca(tipoABB *Aux, int chave){
    
    tipoABB *a;
    
    if(Aux == NULL) 
        return NULL;
    
    else if(Aux->chave == chave) 
        return Aux;
    
    else if(Aux->chave > chave) 
        a = busca(Aux->esq, chave);
    
    else 
        a = busca(Aux->dir, chave); 
}

void imprimirEmOrdem (tipoABB *aux){
    if (aux != NULL){
        imprimirEmOrdem (aux->esq);
        printf("%d ", aux->chave);
        imprimirEmOrdem(aux->dir);
    }
}

int main() {
    
    tipoABB *arvore;
    arvore = inicializa();
    int i, n, chave;
    char acao;

    scanf("%d", &n);

    for(i = 0; i < n; i++){

        scanf(" %c %d", &acao, &chave);

        if (acao == 'i' || acao == 'I')
            arvore = insereABB(arvore, chave);

        else if (acao == 'b' || acao == 'B'){
            if (busca (arvore, chave))
                printf("S\n");
            else
                printf("N\n");
        }
        else if (acao == 'm' || acao == 'M'){
            imprimirEmOrdem (arvore);
            printf("\n");
        }
        else if (acao =='r' || acao == 'R')
            arvore = removeABB (arvore, chave);  
    }   
}