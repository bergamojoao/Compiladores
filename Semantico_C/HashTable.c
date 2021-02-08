#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"HashTable.h"


//vetor de primos
int p[21];

typedef struct{
    Lista lista;
}Item;

typedef struct{
    Item *table;
    int tamanho;
    char* (*getChave)(Elem);    
}HashTableImpl;

int getPrimo(int indice){
    return p[indice];
}

int hashFunction(Elem e,char* (*getChave)(Elem),int tamanho){
    int k=0;
    char chave[21];
    strcpy(chave,getChave(e));

    for(int i=0;i<strlen(chave);i++){
        k=k+(chave[i]*getPrimo(i));
    }
    return k%(tamanho-1);
}


int strToKey(char* chave,int tamanho){
    int k=0;
    int i=0;
    
    while(chave[i]!='\0'){
        k+=(chave[i]*p[i]);
        i++;
    }
    return k%(tamanho-1);
}

HashTable criaHashTable(int tamanho ,char* (*getChave)(Elem)){
    HashTableImpl *new = malloc(sizeof(HashTableImpl));
    new->table = malloc(sizeof(Item)*tamanho);
    new->tamanho=tamanho;
    new->getChave=getChave;
    for (int i = 0; i < tamanho; i++){
        new->table[i].lista=NULL;
    }
    int a=0,b,c,n,d; 
    d=-20;
    int i=0;
    do{
        a++;         
        c=0;
        for(b=1;b<a;b++)
            if(a%b==0)
                c++;
        if(c==1){
            p[i]=a; 
            i++;
            d++;
        }
    }while(d);


    return new;
}

void insertHashTable(HashTable h,Elem e){
    HashTableImpl *hash = h;
    int pos = hashFunction(e,hash->getChave,hash->tamanho);
    hash->table[pos].lista=inserir(hash->table[pos].lista,e);
}

void removerHashTable(HashTable h,char* chave){
    HashTableImpl *hash = h;
    Elem e = getElemHash(h,chave);
    int pos=strToKey(hash->getChave(e),hash->tamanho);
    hash->table[pos].lista=remover(hash->table[pos].lista,e); 
}

Elem getElemHash(HashTable H,char* chave){
    HashTableImpl *hash=H;
    int pos=strToKey(chave,hash->tamanho);
    Lista posic=hash->table[pos].lista;
    if(posic!=NULL){
        while(posic!=NULL){     
            Elem k=get(posic);  
            if(strcmp(hash->getChave(k),chave)==0){
                return k;
            }
            posic=getProx(posic);
        }
    }
    return NULL;
}

void desalocaHash(HashTable h){
    HashTableImpl * hash = h;
    for (int i = 0; i < hash->tamanho; i++){
        finalizar(hash->table[i].lista);
    }
}

int getSizeHash(HashTable H){
    HashTableImpl *hash=H;
    return hash->tamanho;
}

Lista getLista(HashTable H, int index){
    HashTableImpl *hash=H;
    return hash->table[index].lista;
}
    