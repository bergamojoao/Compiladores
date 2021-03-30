#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"ListaDinamica.h"
#include"Grafo.h"
#include"Vertice.h"
#include"Pilha.h"


void alocacao(Grafo g){
    int K = getGrafoSize(g);
    int kAnt = K;
    bool* resultados = malloc(sizeof(bool)*K-2);
    int graphId = getGrafoId(g);
    bool* cores = malloc(sizeof(bool)*K);

    printf("Graph %d -> Physical Registers: %d\n",graphId, K);
    printf("----------------------------------------\n");
    printf("----------------------------------------\n");

    while (K>=2){
        printf("K = %d\n\n", K);
        Lista vertices = getGrafoVertices(g);
        Lista inicio = vertices;

        Lista copiaVertices = NULL;
        while (vertices != NULL){
            copiaVertices = inserir(copiaVertices, get(vertices));
            vertices = getProx(vertices);
        }

        vertices = inicio;
        
        Pilha pilha = iniciarPilha();
        
        while(getListaSize(vertices) != 0){
            Lista listaVerticesAux = vertices;
            Vertice menorVertice = NULL;
            while (listaVerticesAux != NULL){ // Simplify
                Vertice v = get(listaVerticesAux);
                int qtdAdjacentes = getVerticeQtdAdjacentes(v);
                if(qtdAdjacentes<K){
                    if(menorVertice == NULL || getVerticeQtdAdjacentes(menorVertice)>getVerticeQtdAdjacentes(v)
                        || ( getVerticeQtdAdjacentes(menorVertice) == getVerticeQtdAdjacentes(v) && getVerticeId(menorVertice)>getVerticeId(v) ) ){
                        menorVertice = v;
                    }
                }
                listaVerticesAux = getProx(listaVerticesAux);
            }
            bool spill = false;
            if(menorVertice == NULL){ // Potencial Spill
                listaVerticesAux = vertices;
                while (listaVerticesAux != NULL){
                    Vertice v = get(listaVerticesAux);
                    int qtdAdjacentes = getVerticeQtdAdjacentes(v);

                    if(menorVertice == NULL || getVerticeQtdAdjacentes(menorVertice)<getVerticeQtdAdjacentes(v)
                        || ( getVerticeQtdAdjacentes(menorVertice) == getVerticeQtdAdjacentes(v) && getVerticeId(menorVertice)>getVerticeId(v) ) ){
                        menorVertice = v;
                        spill = true;
                    }

                    listaVerticesAux = getProx(listaVerticesAux);
                }
            }

            listaVerticesAux = vertices;
            while (listaVerticesAux != NULL){ // Remove dos adjacentes de outro nó
                Vertice v = get(listaVerticesAux);
                if(getVerticeId(v)!=getVerticeId(menorVertice)){
                    Lista adjts = getVerticeAdjacentes(v);
                    while (adjts != NULL){
                        Vertice adj = get(adjts);
                        if(getVerticeId(menorVertice)==getVerticeId(adj)){
                            setVerticeQtdAdjacentes(v, getVerticeQtdAdjacentes(v)-1);
                            break;
                        }
                        adjts = getProx(adjts);
                    }    
                }
                listaVerticesAux = getProx(listaVerticesAux);
            }

            vertices = removerSemFree(vertices, menorVertice); // Remove do grafo
            push(pilha, menorVertice); // Empilha o vertice escolhido
            printf("Push: %d%s\n", getVerticeId(menorVertice), spill?" *":"");
        }

        Vertice v = pop(pilha);
        while (v != NULL){
            Lista adjcts = getVerticeAdjacentes(v);
            int i;
            for(i=0; i<K ; i++) cores[i] = false;
            while (adjcts != NULL){
                int idAdj = getVerticeId(get(adjcts));
                if(idAdj<K){
                    cores[idAdj] = true;
                }else{
                    vertices = copiaVertices;
                    while (vertices != NULL){
                        int idV2 = getVerticeId(get(vertices));
                        int cor =  getVerticeCor(get(vertices));
                        if(idAdj == idV2 && cor != -1){
                            cores[cor] = true;
                        }
                        vertices = getProx(vertices);
                    }
                }
                adjcts = getProx(adjcts);
            }
            bool spill = true;
            for(i=0; i<K ; i++){
                if(!cores[i]){
                    setVerticeCor(v, i);
                    printf("Pop: %d -> %d\n",getVerticeId(v), i);
                    spill = false;
                    break;
                }
            }
            if(spill){
                printf("Pop: %d -> NO COLOR AVAILABLE\n",getVerticeId(v));
                resultados[K-2] = true;
                break;
            }

            v = pop(pilha);
        }

        printf("----------------------------------------\n");

        K--;
    }
    
    printf("----------------------------------------\n");
    while (kAnt>=2){
        printf("Graph %d -> K = %2d: %s%s",graphId, kAnt, resultados[kAnt-2] ? "SPILL":"Successful Allocation",kAnt==2?"":"\n");
        kAnt--;
    }
    
}