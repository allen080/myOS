#include <stdio.h>

int countIntSize(int num){
    // Conta o tamanho de um numero
    int contTam = 1;
    for(int dezenas=10; num>dezenas-1; dezenas*=10){
        contTam++;
    }
    return contTam;  
}

void num2Str(char num, int contTam, char *strNum){
    // Converte um inteiro para string
    int dezenas, contChar=0;
    for(dezenas=1; num>dezenas-1; dezenas*=10){
        
    }

    for(int i=0;i<contTam;i++){//num=23
        dezenas/=10;
        strNum[contChar++] = num/dezenas + '0'; // pega cada caractere do numero e converte em ascii
        num %= dezenas;
    }

    strNum[contTam] = '\0'; // coloca o byte nulo no final para o print
}

int main(){
    int cor = 0xe;
    cor = cor<<4;
    
    printf("%d\n",++cor);
    return 0;
}


/*
    //char c;
    //short s;
    //__asm__ __volatile__("outb %0,%1" : "=a" (c) : "dN" (s));

    int x=1,y=2;

    x = y = 3;
    x=4;
    printf("%d %d\n",x,y);
    */