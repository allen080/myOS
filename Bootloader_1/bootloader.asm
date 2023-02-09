[bits 16]
[ORG 0x7c00] ; inicio do bootloader

start:
    xor ax,ax
    mov sp,0x7c00 ; inicio da Stack Pointer
    call testarDiskExtension
    ;call loaderReadDisk
    call printOI

loaderReadDisk:
    mov dl,[driverID] ; pega a ID do driver guardado no testarDiskExt
    mov ah,0x42 ; 0x42 = ler setor do disco, 0x43 = escrever no disco
    mov si,[packetStruct]
    mov WORD [si],16  ; parametro 1: tamanho da struct (packetStruct) que vai ler
    mov WORD [si+2],5 ; parametro 2: numero de setores
    mov WORD [si+4],0x7e00 ; parametro 3: setor para ler (do loader)
    mov WORD [si+6],0x0000 ; parametro 4: começo do setor (0x7e00:0000)
    mov DWORD [si+8],1 ; parametro 5: endereço logico do setor (4 bytes, +significativo)
    mov DWORD [si+12],0 ; parametro 5: endereço logico do setor (4 bytes, -signifativo)
    int 0x13
    jc fim
    ret

testarDiskExtension:
    mov [driverID],dl ; guarda a ID do driver (0x0 floppy e 0x80 hd)
    xor ah,ah
    int 0x13 ; testa a extensao, se der errado vai setar a carry flag que significa que ouve um overflow
    jc fim ; pula pro final se n suportar a disk extension
    cmp ah,0 ; compara se deu certo
    jne fim ; vai pro fim se n tiver dado
    ret

printOI:
    mov ah, 0x13 ; imprimir msg
    mov al, 1 ; stdout (?)
    mov dh, 0 ; linha pra exibir
    mov dl, 0; coluna pra exibir (ou dx=0 para linha e coluna 0)
    mov bp, oiMsg
    mov bx,[oiCor] ; cor da string
    mov cx,[oiTam] ; tamanho
    int 0x10 ; printa a msg
    ret

fim: ; loopa infinitamente
    hlt
    jmp fim

oiMsg: db "Leu td direito"
oiCor: dw 0xf ; cor branca
oiTam: dw 14

driverID db 0 ; ID do driver (0x0 floppy e 0x80 hd)
packetStruct: times 16 db 0 ; parametros pro ler do setor no loader 

times (510-($-$$)) db 0
dw 0xaa55
