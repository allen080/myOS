#include "include/screen.h"
#include "include/string.h"
#include "include/colors.h"
#include "include/keyboard.h"

void printToVMColor(char *msg, char cor, char *videoMem){
	// exibe msg na tela (pelo endereco da video memory)
	int i=0;

	while(*msg != '\0'){
		videoMem[i] = *msg++; // cada caractere da msg 
		videoMem[i+1] = cor; // cor da msg 
		i += 2;
	}
}

void printToVM(char *msg, char *videoMem){
	printToVMColor(msg, 0x5, videoMem);
}

void printNTimesToVM(char *msg, char cor, int times, char *videoMem){
	int i;
	for(i=0; i<times; i++){
		printToVMColor(msg, cor, videoMem);
		videoMem += 2;
	}
}

void miPrint(){
	printStrColor("\n\n                                           \n          ####                        ####        \n          ########  ############  ########        \n          ################################        \n          ##############################          \n            ############################          \n            ##########################            \n          ################################        \n        ####################################      \n        ####################################      \n          ########  ############  ########        \n        ##########    ########    ########        \n        ############  ########  ############      \n            ############################          \n                ####################              \n                  ################                \n                  ####      ####                  \n                    ####    ####                  \n                    ##########                    \n                        ##                 ", C_Vermelho);
	//printStrColor("\n\n  AUUUUUUUUUUUUU\n",C_Amarelo);
}

void showFlag(){
	char *videoMem = (char*)0xb8000; // inicio da memoria de video

	int tamanho = 30;

	printNTimesToVM(" ",0x55,tamanho,videoMem);
	printNTimesToVM(" ",0x55,tamanho,videoMem+160);
	printNTimesToVM(" ",0xdd,tamanho,videoMem+160*2);
	printNTimesToVM(" ",0x11,tamanho,videoMem+160*3);
	printNTimesToVM(" ",0x11,tamanho,videoMem+160*4);
}

void printByte(char byte){
	int contTam = countIntSize(byte);
	char str[contTam+1];
	strFromNum(byte,contTam,str);
	printStr(str);
}

void kmain(){ // kernel main
	clearScreen();

	printStrColor("Bem vindo ao Sistema Operacional MONOTASK\n\n", C_Amarelo);
	printStr("Idealizador: Daniel Furlan (2013)\nDesenvolvedor: allen08 (2023)\n");
	
	const string bash = "$ ";

	printChar('\n');
	
	char comando[400];

	while(1){
		printStrColor(bash, C_Ciano);
		byteToPort(0x64,0);
		readStr(comando); // le uma string digitada ate apertar Enter
		
		if(strStartsWith(comando,"echo")){
			printChar('\n');
			printlnStr(getStrStart(comando, 5));
		} else if(strEquals(comando,"lobo")){
			miPrint();
		} else if(strEquals(comando,"oi")){
			printStr("\nola :D\n");
		} else if(strEquals(comando,"clear")){
			clearScreen();
		} else if(strEquals(comando,"reset")){
			clearScreen();
			printStrColor("Bem vindo ao Sistema Operacional MONOTASK\n\n", C_Amarelo);
			printStr("Idealizador: Daniel Furlan (2013)\nDesenvolvedor: allen08 (2023)\n");
		} else {
			printStr("\n[!] Comando invalido\r\n");
		}
		printChar('\n');

	}