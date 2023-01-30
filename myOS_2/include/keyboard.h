#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "types.h"
#include "defs.h"
#include "system.h"

const char KeyDownCode = -112;

const char ScanCode[] = {
  0,  27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',   
  '\t', /* <-- Tab */
  'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',     
    0, /* <-- control key */
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',  '"', '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/',   0,
  '*',
    0,  /* Alt */
  ' ',  /* Space bar */
    0,  /* Caps lock */
    0,  /* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,  /* < ... F10 */
    0,  /* 69 - Num lock*/
    0,  /* Scroll Lock */
    0,  /* Home key */
    0,  /* Up Arrow */
    0,  /* Page Up */
  '-',
    0,  /* Left Arrow */
    0,
    0,  /* Right Arrow */
  '+',
    0,  /* 79 - End key*/
    0,  /* Down Arrow */
    0,  /* Page Down */
    0,  /* Insert Key */
    0,  /* Delete Key */
    0,   0,   0,
    0,  /* F11 Key */
    0,  /* F12 Key */
    0xff,  /* All other keys are undefined */
};

uint8 getScanCodeIndex(char key){
  uint8 index = 0;
  do {
    if(ScanCode[index] == key){
      return index;
    }

    index++;
  } while(ScanCode[index] != 0xff);

  return FALSE;
}

char readChar(){
  char charRead = '\0';

  if(portToByte(0x60)&1){
    charRead = portToByte(0x60);

    if(charRead == KeyDownCode || charRead == 0){
      charRead = '\0';
    } else {
      charRead = ScanCode[charRead];
    }
  }

  return charRead;
}

string OLD_readStr(){
  char *strTyped;
  uint8 isReading = TRUE;
  uint16 countKeys = 0;

  while(isReading){
    uint8 pressed = portToByte(0x60)&1;

    if(pressed){
      uint8 keyCode = portToByte(0x60);
      printChar('a');

      if(keyCode == KeyDownCode){
        pressed = FALSE;
        continue;
      }

      char keyValue = ScanCode[keyCode];

      if(keyValue == 'z')
        isReading = FALSE; // para a leitura

      //strTyped[countKeys++] = keyValue;
    }
  }

  strTyped[countKeys] = '\0';
  return strTyped;
}

string readStr(string buffstr){
    // Leitura de uma string no teclado ate apertar Enter
    //string buffstr;
    uint8 countKey = 0;
    uint8 reading = TRUE;
    uint8 ch = 0;

    while(reading){
        if(portToByte(0x64) & 0x1){ // checa se uma tecla foi apertada
            ch = portToByte(0x60); // pega o valor da tecla

            switch(ch){
              case 28: // 'Enter' -> para a leitura
                reading = 0;
                break;

              case 57: // 'Espaco'
                printChar(' ');
                buffstr[countKey++] = ScanCode[ch];
                break;
              
              default:
                if(ScanCode[ch] == ' ' || ScanCode[ch] == '#') continue; // (Key Released)

                printChar(ScanCode[ch]);
                buffstr[countKey++] = ScanCode[ch];
                break;
              /*
      /*case 1:
                printChar('(char)27);           Escape button
                buffstr[i] = (char)27;
                i++;
                break;
        case 2:
                printChar('1');
                buffstr[i] = '1';
                i++;
                break;
        case 3:
                printChar('2');
                buffstr[i] = '2';
                i++;
                break;
        case 4:
                printChar('3');
                buffstr[i] = '3';
                i++;
                break;
        case 5:
                printChar('4');
                buffstr[i] = '4';
                i++;
                break;
        case 6:
                printChar('5');
                buffstr[i] = '5';
                i++;
                break;
        case 7:
                printChar('6');
                buffstr[i] = '6';
                i++;
                break;
        case 8:
                printChar('7');
                buffstr[i] = '7';
                i++;
                break;
        case 9:
                printChar('8');
                buffstr[i] = '8';
                i++;
                break;
        case 10:
                printChar('9');
                buffstr[i] = '9';
                i++;
                break;
        case 11:
                printChar('0');
                buffstr[i] = '0';
                i++;
                break;
        case 12:
                printChar('-');
                buffstr[i] = '-';
                i++;
                break;
        case 13:
                printChar('=');
                buffstr[i] = '=';
                i++;
                break;
        case 14:
                printChar('\b');
                i--;
                buffstr[i] = 0;
                break;
       /* case 15:
                printChar('\t');          Tab button
                buffstr[i] = '\t';
                i++;
                break;
        case 16:
                printChar('q');
                buffstr[i] = 'q';
                i++;
                break;
        case 17:
                printChar('w');
                buffstr[i] = 'w';
                i++;
                break;
        case 18:
                printChar('e');
                buffstr[i] = 'e';
                i++;
                break;
        case 19:
                printChar('r');
                buffstr[i] = 'r';
                i++;
                break;
        case 20:
                printChar('t');
                buffstr[i] = 't';
                i++;
                break;
        case 21:
                printChar('y');
                buffstr[i] = 'y';
                i++;
                break;
        case 22:
                printChar('u');
                buffstr[i] = 'u';
                i++;
                break;
        case 23:
                printChar('i');
                buffstr[i] = 'i';
                i++;
                break;
        case 24:
                printChar('o');
                buffstr[i] = 'o';
                i++;
                break;
        case 25:
                printChar('p');
                buffstr[i] = 'p';
                i++;
                break;
        case 26:
                printChar('[');
                buffstr[i] = '[';
                i++;
                break;
        case 27:
                printChar(']');
                buffstr[i] = ']';
                i++;
                break;
        case 28:
               // printChar('\n');
               // buffstr[i] = '\n';
                  i++;
               reading = 0;
                break;
      /*  case 29:
                printChar('q');           Left Control
                buffstr[i] = 'q';
                i++;
                break;
        case 30:
                printChar('a');
                buffstr[i] = 'a';
                i++;
                break;
        case 31:
                printChar('s');
                buffstr[i] = 's';
                i++;
                break;
        case 32:
                printChar('d');
                buffstr[i] = 'd';
                i++;
                break;
        case 33:
                printChar('f');
                buffstr[i] = 'f';
                i++;
                break;
        case 34:
                printChar('g');
                buffstr[i] = 'g';
                i++;
                break;
        case 35:
                printChar('h');
                buffstr[i] = 'h';
                i++;
                break;
        case 36:
                printChar('j');
                buffstr[i] = 'j';
                i++;
                break;
        case 37:
                printChar('k');
                buffstr[i] = 'k';
                i++;
                break;
        case 38:
                printChar('l');
                buffstr[i] = 'l';
                i++;
                break;
        case 39:
                printChar(';');
                buffstr[i] = ';';
                i++;
                break;
        case 40:
                printChar((char)44);               //   Single quote (')
                buffstr[i] = (char)44;
                i++;
                break;
        case 41:
                printChar((char)44);               // Back tick (`)
                buffstr[i] = (char)44;
                i++;
                break;
     /* case 42:                                 Left shift 
                printChar('q');
                buffstr[i] = 'q';
                i++;
                break;
        case 43:                                 \ (< for somekeyboards)   
                printChar((char)92);
                buffstr[i] = 'q';
                i++;
                break;
        case 44:
                printChar('z');
                buffstr[i] = 'z';
                i++;
                break;
        case 45:
                printChar('x');
                buffstr[i] = 'x';
                i++;
                break;
        case 46:
                printChar('c');
                buffstr[i] = 'c';
                i++;
                break;
        case 47:
                printChar('v');
                buffstr[i] = 'v';
                i++;
                break;                
        case 48:
                printChar('b');
                buffstr[i] = 'b';
                i++;
                break;               
        case 49:
                printChar('n');
                buffstr[i] = 'n';
                i++;
                break;                
        case 50:
                printChar('m');
                buffstr[i] = 'm';
                i++;
                break;               
        case 51:
                printChar(',');
                buffstr[i] = ',';
                i++;
                break;                
        case 52:
                printChar('.');
                buffstr[i] = '.';
                i++;
                break;            
        case 53:
                printChar('/');
                buffstr[i] = '/';
                i++;
                break;            
        case 54:
                printChar('.');
                buffstr[i] = '.';
                i++;
                break;            
        case 55:
                printChar('/');
                buffstr[i] = '/';
                i++;
                break;            
      /*case 56:
                printChar(' ');           Right shift
                buffstr[i] = ' ';
                i++;
                break;         
        case 57:
                printChar(' ');
                buffstr[i] = ' ';
                i++;
                break;
        */
            }
        }
    }
    buffstr[countKey] = '\0';                   
    return buffstr;
}

#endif