#ifndef SYSTEM_H
#define SYSTEM_H

#include "types.h"

void byteToPort(uint16 _port, uint8 _byte){ // outportb
    // converte um byte para uma IO Port para ser usado no mouse/teclado
    __asm__ __volatile__("outb %1,%0" : : "dN" (_port), "a" (_byte));
}

uint8 portToByte(uint16 _port){ // inportb
    // pega o byte correspondente ao valor de uma porta IO 
    uint8 byte;
    __asm__ __volatile__("inb %1,%0" : "=a" (byte) : "dN" (_port));
    return byte;
}

#endif