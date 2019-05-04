#include <stdio.h>
#include <stdlib.h>

typedef struct aux {
    int chave;
    struct aux *esquerda, *direita;
    int h;
} NO, *PONT;

PONT criaNo(int ch) {
    PONT novoNo = (PONT) malloc(sizeof(NO));
    novoNo->esquerda = NULL;
    novoNo->direita = NULL;
    novoNo->chave = ch;
    novoNo->h = 0;
    return novoNo;
}


/*PONT inicializa() {
    return NULL;
}*/

PONT direita(PONT r) {
    PONT aux;
    aux = r->esquerda;
    r->esquerda = aux->direita;
    aux->direita = r;

    r->h = max(altura(r->direita), altura(r->esquerda)) + 1;
    aux->h = max(altura(aux->esquerda), r->h) + 1;
    return aux;
}

PONT esquerda(PONT r) {
    PONT aux;
    aux = r->direita;
    r->direita = aux->esquerda;
    aux->esquerda = r;
    r->h = max(altura(r->direita), altura(r->esquerda)) + 1;
    aux->h = max(altura(aux->direita), r->h) + 1;
    return aux;
}

/* Função que, dado dois valores, retorna o maior deles */
int max(int a, int b) {
    if (a > b) {
        return a;
    }
    else {
        return b;
    }
}

/* Função que retorna a altura de um nó na árvore */
int altura (PONT raiz) {
    if (!raiz) {
        return -1;
    }
    else {
        return raiz->h;
    }
}

PONT esquerdaDireita(PONT r) {
    r->esquerda = esquerda(r->esquerda);
    return direita(r);
}

PONT direitaEsquerda(PONT r) {
    r->direita = direita(r->direita);
    return esquerda(r);
}


/* Insere um novo nó na árvore */
PONT insere(PONT raiz, int ch) {
    if (!raiz) {
        return criaNo(ch);
    }
    if (ch < raiz->chave) {
        raiz->esquerda = insere(raiz->esquerda, ch);
        if ((altura(raiz->esquerda) - altura(raiz->direita)) == 2) {
            if (ch < raiz->esquerda->chave) {
                raiz = direita(raiz);
            }
            else {
                raiz = esquerdaDireita(raiz);
            }
        }
    }
    else {
        if (ch > raiz->chave) {
            raiz->direita = insere(raiz->direita, ch);
            if ((altura(raiz->direita) - altura(raiz->esquerda)) == 2) {
                if (ch > raiz->direita->chave) {
                    raiz = esquerda(raiz);
                }
                else {
                    raiz = direitaEsquerda(raiz);
                }
            }
        }
        else{
        	return NULL;
		}
    }
    raiz->h = max(altura(raiz->esquerda), altura(raiz->direita)) + 1;
    return raiz;
}

/* Verifica se determinado valor está contido na árvore */
PONT contem(int ch, PONT raiz) {
    if (raiz == NULL) {
        return NULL;
    }
    if (raiz->chave == ch) {
        return raiz;
    }
    if (raiz->chave > ch) {
        return contem(ch, raiz->esquerda);
    }
    return contem(ch, raiz->direita);
}


int numeroNos(PONT raiz) {
    if (!raiz) {
        return 0;
    }
    return numeroNos(raiz->esquerda) + 1 + numeroNos(raiz->direita);
}

void preOrdem(PONT raiz) {
    if (raiz != NULL) {
        printf("%d ", raiz->chave);
        preOrdem(raiz->esquerda);
        preOrdem(raiz->direita);
    }
}

void emOrdem(PONT raiz) {
    if (raiz != NULL) {
        emOrdem(raiz->esquerda);
        printf("%d ", raiz->chave);
        emOrdem(raiz->direita);
    }
}

void posOrdem(PONT raiz) {
    if (raiz != NULL) {
        posOrdem(raiz->esquerda);
        posOrdem(raiz->direita);
        printf("%d ", raiz->chave);
    }
}


void exibeArvore (PONT raiz) {
    if (raiz != NULL) {
        printf("%d", raiz->chave);
        printf("(");
        exibeArvore(raiz->esquerda);
        exibeArvore(raiz->direita);
        printf(")");
    }
}



PONT menor(PONT raiz){
	PONT no1,no2;
	no1=raiz;
	no2=raiz->esquerda;
	while(no2 !=NULL){
		no1=no2;
		no2=no2->esquerda;
	}
	return no1;
}

PONT remove_no(PONT raiz, int v){
	if(raiz==NULL){
		printf("Valor não pertence a árvore");
		return NULL;
	}
	if(v < raiz->chave){
		raiz->esquerda = remove_no(raiz->esquerda,v);
		if ((altura(raiz->esquerda) - altura(raiz->direita)) == 2) {
            if (v < raiz->esquerda->chave) {
                raiz = direita(raiz);
            }
            else {
                raiz = esquerdaDireita(raiz);
            }
        }
	}
	if(raiz->chave < v){
		raiz->direita = remove_no(raiz->direita,v);
		if ((altura(raiz->direita) - altura(raiz->esquerda)) == 2) {
            if (v > raiz->direita->chave) {
                raiz = esquerda(raiz);
            }
            else {
                raiz = direitaEsquerda(raiz);
            }
        }
    }    
	raiz->h = max(altura(raiz->esquerda), altura(raiz->direita)) + 1;
	
	if(raiz->chave == v){
		if((raiz->esquerda == NULL || raiz->direita == NULL)){
			PONT oldnode = raiz;
			if(raiz->esquerda != NULL){
				raiz = raiz->esquerda;
			}
			else{
				raiz = raiz->direita;
			}
			free(oldnode);
		}
		else{
			PONT temp = menor(raiz->direita);
			raiz->chave = temp->chave;
			remove_no(raiz->direita,raiz->chave);
			if(balanceamento_no(raiz)>=2){
				if(altura(raiz->esquerda->direita) <= altura(raiz->esquerda->esquerda)){
					raiz = direita(raiz);
				}
				else{
					raiz = esquerdaDireita(raiz);
				}
			}
		}
		
	}
	
	return raiz;
}

int balanceamento_no(PONT raiz){
	return labs(altura(raiz->esquerda) - altura(raiz->direita));
}

int main()
{
    //PONT r = inicializa();
    //r = criaNo(5);
    PONT r = NULL;
    r = insere(r, 5);
    insere(r, 2);
    insere(r, 10);
    insere(r, 3);
    insere(r, 4);
    insere(r, 7);
    preOrdem(r);
    printf("\n");
    emOrdem(r);
    printf("\n");
    posOrdem(r);
    printf("\n");
    exibeArvore(r);
    printf("\n");
    remove_no(r,2);
    remove_no(r,3);
    printf("\n");
    exibeArvore(r);
    return 0;
}
