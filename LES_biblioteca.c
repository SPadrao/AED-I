#include <stdio.h>
#define N 10
 
struct listaES {
int ultimo;
int tamanhoLista;
int lista[N];
};
typedef struct listaES tipoListaES;
 
void inicializaLista (tipoListaES *listaAux){
    // zera a lista
    listaAux->tamanhoLista = 0;
 
    int i;
 
    for (i = 0; i < N; i++)
        listaAux->lista[i] = 0;
 
    // inicializa o último
    listaAux->ultimo = 0;
}
 
void insereElemento (tipoListaES *listaAux, int livro){
 
    if(listaAux->tamanhoLista == N)
        printf("Lista de reserva cheia\n");
 
    else{        
        // insere elemento ao final da lista       
        listaAux->lista[listaAux->tamanhoLista] = livro;
 
        // atualiza o último
        listaAux->ultimo = listaAux->tamanhoLista;
        listaAux->tamanhoLista++;
 
        printf("Sua reserva foi realizada\n");       
    }
}
 
int retiraElemento (tipoListaES *listaAux, int livro){
 
    int i = 0, j;
 
    while (i < listaAux->tamanhoLista && listaAux->lista[i] != livro)
        i++;
    
    if(listaAux->tamanhoLista == 0 || listaAux->lista[i] != livro)
        return 1;
 
    else{
        
        // percorre a lista em busca do livro selecionado
        while (i < listaAux->tamanhoLista && listaAux->lista[i] != livro)
            i++;
 
        // desloca a posição dos livros
        for (j = i; j < listaAux->tamanhoLista - 1; j++)
            listaAux->lista[j] = listaAux->lista[j + 1];
 
        listaAux->lista[listaAux->ultimo--] = 0;
 
        // atualiza a lista
        listaAux->tamanhoLista--;
 
        return 0;      
    }
}
 
void imprimeLista(tipoListaES *listaAux){ 
    int i;
    printf("\n");
    for (i = 0; i < N; i++)  
        printf("reserva [%d] = %d ", i, listaAux->lista[i]);
    
}
 
int main(){
 
    tipoListaES o;
    inicializaLista (&o);
    tipoListaES *listaAux;
 
    //printf("\nBem vindo(a) a biblioteca virtual!!\n");
 
    int L, i = 1, reserva = 0, retirada = 0;
 
    //printf("Quantas acoes deseja realizar?\n");
    scanf("%d", &L);
 
        while(i <= L && L <= 100){
            
            int acao, livro;
            scanf("%d %d", &acao, &livro);
 
            if (livro <= 100 && livro > 0){
 
                if (acao == 1){        
                    insereElemento(&o, livro);
                    if(reserva < N)
                        reserva++;
                }
                if (acao == 2){
                    if (retiraElemento(&o, livro) == 0){
                        printf ("O livro foi retirado com sucesso\n");
                        retirada++; 
                    }               
                    else
                        printf("Voce nao possui reserva desse livro\n");              
                }   
                i++;
            }
            else
                i++;
        }
    printf("Voce realizou %d reservas e %d retiradas\n", reserva, retirada);
    //imprimeLista(&o);
    return 0;
}