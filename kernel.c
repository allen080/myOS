void printToVM(char *msg, char *videoMem){
	// exibe msg na tela (pelo endereco da video memory)
	int i=0;

	while(*msg != '\0'){
		videoMem[i] = *msg++; // cada caractere da msg 
		videoMem[i+1] = 0x5; // cor da msg 
		i += 2;
	}
}

void kmain(){ // kernel main
	char *videoMem = (char*)0xb8000; // inicio da memoria de video
	printToVM("eh na sola da bota eh na palma da bota",videoMem);
}