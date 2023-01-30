#ifndef STRING_H
#define STRING_H

#include "types.h"
#include "defs.h"

uint16 strSize(string str){
    uint16 cont = 1;
    while(str[cont++]);
    return cont-1;
}

uint8 strEquals(string str1, string str2){
    // compara se 2 strings sao iguais
    uint16 str1Size = strSize(str1), str2Size = strSize(str2); // tamanho das strs

    if(str1Size != str2Size){ // checa se sao iguais em tamanho
        return FALSE;
    }

    for(uint8 c=0; c<str1Size; c++){ // se n forem iguais, compara cada caractere
        if(str1[c] != str2[c]){
            return FALSE;
        }
    }
    
    return TRUE; // strings iguais
}

int countIntSize(char num){
    // Conta o tamanho de um numero
    int contTam = 1;

    for(int dezenas=10; num>dezenas-1; dezenas*=10){
        contTam++;
    }
    return contTam;  
}

void strFromNum(char num, int contTam, char *strNum){
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

string strCopy(string str){
    // copia o conteudo de uma string
    string copy;
    for(int i=0; i<=strSize(str); i++){
        copy[i] = str[i];
    }
    return copy;
}

string getStrStart(string str, uint32 ini){
    // pega um pedaço de uma string apartir de um valor
    string subStr = strCopy(str);
    subStr += ini;

    return subStr;
}

uint8 strStartsWith(string str, string strStartCheck){
    // checa se uma string comeca com uma determinada subString
    for(uint8 i=0; i<strSize(strStartCheck); i++){
        if(strStartCheck[i] != str[i]){
            return FALSE;
        }
    }
    return TRUE;
}

#endif