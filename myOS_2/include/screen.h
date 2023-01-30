#ifndef SCREEN_H
#define SCREEN_H

#include "types.h"
#include "system.h"
#include "string.h"

int cursorX = 0, cursorY = 0;

// Informacoes da Tela:

// 80 colunas cada uma dividida em 2 bytes (depth), 1 pro char e outro pra cor
const uint8 widthS = 80; 
// quantidade de linhas na tela
const uint8 heightS = 25;
//const uint8 heightS = 27;
// profundidade (2 colunas)
const uint8 depthS = 2;

void clearLines(uint8 start, uint8 end){
    // limpa x linhas da tela (start ate end)

    // inicio da memoria de video
    string videoMemory = (string)0xb8000; 
    // calculo do inicio de onde iniciara o clear
    uint16 cont = widthS * start * depthS;

    // percorre toda a tela ate a ultima linha a ser limpa
    for(cont; cont < widthS*(end+1)*depthS; cont++){
        videoMemory[cont] = 0x0; // caractere em branco
    }
}

void updateCursor(){
    // atualiza a posicao do cursor na tela,
    // com base nos valores atuais de cursorX e Y
    unsigned portaIO = cursorY * widthS + cursorX;

    uint16 byteVGA = 0x3D4; // porta VGA especifica

    byteToPort(byteVGA, 14);
    byteToPort(byteVGA+1, portaIO >> 8);
    byteToPort(byteVGA, 15);
    byteToPort(byteVGA+1, portaIO);

}

void updateCursorByVal(int newX, int newY){
    // atualiza o cursor com os valores especificos
    cursorX = newX;
    cursorY = newY;
    updateCursor();
}

void clearScreen(){
    clearLines(0, heightS-1); // limpa tds as 25 linhas
    updateCursorByVal(0,0); // coloca o cursor no comeco
}

void scrollUp(uint8 n_linha){
    string videoMemory = (string)0xb8000;

    for(uint16 i=0; i < widthS*(heightS-1)*depthS; i++){
        // percorre as linhas e substitui a linha atual pela proxima
        videoMemory[i] = videoMemory[i + widthS*depthS*n_linha]; 
    }
    clearLines(heightS-1-n_linha, heightS-1); // limpa as linhas inferiores que nao foram copiadas

    // ajustar o cursor
    if(cursorY-n_linha < 0){ // ajusta pro começo da linha
        updateCursorByVal(0,0);
    } else { // sobe a quantidade de vezes que foi removido
        cursorY -= n_linha;
        updateCursor();
    }
}

void checkEndScreen(){
    // checa se o cursor esta no final da tela e se tiver, desce as informacoes
    if(cursorY >= heightS-1){
        scrollUp(1);
    }
}

void printCharColor(char caractere, uint8 cor){
    // printa um caractere por uma cor informada
    string vidMem = (string)0xb8000;
    uint32 charPos;
    uint8 tabSize = 4; // tamanho de espacos do TAB

    switch(caractere){
        case 0x8: // backspace/apagar char
            if(cursorX > 0){ // garantir que o cursor n saia pra esquerda
                cursorX--; // volta o cursor
                vidMem[(cursorY*widthS+cursorX)*depthS] = 0x0; // apaga o caractere
            }
            break;
        case 0x9: // tab
            cursorX = (cursorX+tabSize) & -tabSize;
            break;
        case '\r':
            cursorX = 0;
            break;
        case '\n':
            cursorY++;
            cursorX = 0;
            break;
        default: // printa outros chars
            charPos = (cursorY*widthS+cursorX)*depthS;
            vidMem[charPos] = caractere;
            vidMem[charPos+1] = cor; // cor do caractere
            cursorX++;
            break;
    }

    if(cursorX >= widthS){ // chegou ao final de uma linha da tela
        // vai pra linha debaixo
        cursorY++;
        cursorX = 0;
    }

    checkEndScreen();
    updateCursor();
}

void printChar(char caractere){
    // printa um caractere da cor branca
    printCharColor(caractere, 0xf);
}

void printStrColor(string msg, uint8 cor){
    // printa todos caracteres de uma string com uma cor informada
    uint16 msgLength = strSize(msg);

    if(msgLength < 1) return; // checa se a str n eh vazia

    for(uint16 c=0; c<msgLength; c++){ // printa cada char
        printCharColor(msg[c], cor);
    }
}

void printStr(string msg){
    // printa um conjunto de caracteres na tela em cor branca
    printStrColor(msg, 0xf);
}

void printlnStr(string msg){
    // printa uma string com quebra de linha (\n)
    printStr(msg);
    printChar('\n');
}

void paintScreen(char cor){
    // muda a cor de fundo da tela inteira
    updateCursorByVal(0,0);

    int quantChars = widthS*heightS;
    cor = cor<<4;

    for(int i=0; i<quantChars; i++){
        printCharColor(' ',cor);
    }

    updateCursorByVal(0,0);
}

#endif