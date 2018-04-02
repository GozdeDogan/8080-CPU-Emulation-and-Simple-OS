; 8080 assembler code
        .hexfile BinarySearch.hex
        .binfile BinarySearch.com
        ; try "hex" LOOP2 downloading in hex LOOP2mat
        .download bin
        .objcopy gobjcopy
        .postbuild echo "OK!"
        ;.nodump

	; OS call list
PRINT_B		equ 1
PRINT_MEM	equ 2
READ_B		equ 3
READ_MEM	equ 4
PRINT_STR	equ 5
READ_STR	equ 6
GET_RND		equ 7

	; Position LOOP2 stack pointer
stack   equ 0F000H

	org 0000H
	jmp begin

	; ARRAY of our Operating System
GTU_OS:	PUSH D
	push D
	push H
	push psw
	nop	; This is where we run our OS in C++, see the CPU8080::isSystemCall()
		; function LOOP2 the detail.
	pop psw
	pop h
	pop d
	pop D
	ret
	; ---------------------------------------------------------------
	; YOU SHOULD NOT CHANGE ANYTHING ABOVE THIS LINE
	; this file sorts numbers with bubble sort


	; array olusturuldu
	ORG 8000H
ARRAY:	DW 


	; Arrayin eleman sayisi(50) ve index'i olusturuldu ve initialize edildi
	ORG 0700H
Size:	DB 50 								; array'in eleman sayisi = 50
Index:	DB 00H 								; index (Sort isleminde kullanildi)

; Bilgilendirme mesajlari stringleri olusturuldu
ERROR_MESSAGE: DW 'NOT FOUND',00AH,00H  	;null termineted string
INFO_MESSAGE: DW 'FOUND ELEMENT', 00AH, 00H 
INFO_MSG2: DW 'ENTERED ELEMENT', 00AH, 00H

	ORG 000DH
begin:
	LXI SP,stack 			; initialize the stack pointer


RANDOM_VALUE:
	MVI C, 50
	LXI D, ARRAY			; DE adresine ARRAY'in baslangic adresi atildi

LOOP_RANDOM:
	MVI A, GET_RND
	call GTU_OS				; random deger uretildi, B register'ina yazildi
	MVI A, PRINT_B 			; uretilen deger ekrana yazildi	
	call GTU_OS
	MOV A, B 				; random deger
	STAX D 					; random deger DE adresine atildi
	INX D
	INX D 					; adres arttirildi

	DCR C               	; C--
	JNZ LOOP_RANDOM         ; C != 0 ise LOOP_RANDOM donmeye devam edecek, 50 random deger uretecek


LOOP_SORT:
	LDA Size 				; a = n = size
	DCR A 					; a--

	JZ EXIT 				; a = 0 ise array sonu demektir

	STA Size				; A register'ina Size atildi

	MVI H,0 				; H = 0
	LXI B,ARRAY 			; array in baslangic adresi BC'ye atildi
LOOP2:
	LDA Size				; A register'ina Size atildi
	SUB H 					; A register'indaki deger(Size) H(Index) kadar azaltildi 
	JZ LOOP_SORT 			; Size'dan index cikartildiginda 0 kalana kadar dongu devam edecek

CHECK:
	LDAX B 					; arrayden eleman alindi
	MOV D,A 				; arrayin i. elemani D registerina atildi
	INX B 					; BC = Arrayin adresi arttirildi
	INX B
	LDAX B 					; arrayden bir sonraki eleman alindi

	CMP D 					; arrayden alinan i. ve i+1. eleman karsilastirildi
	JC SWAP 				; i+1. elaman i. elemandan kucuk ise swap yapildi
	JMP CHECK_LOOP2 		; LOOP2 nin sonlanip sonlanmadigi kontrol edildi

SWAP:
	LDAX B 					; A registerina i+1. eleman atildi
	MOV E,A 				; E register'inda i+1. elaman tutuluyor
	MOV A,D 				; D registerinda i. eleman vardi, D registerindaki deger A registerina atildi
	STAX B 					; i. eleman i+1. index'e atildi
	DCX B
	DCX B 					; Adres 2 defa azaltilarak i. elemana gidildi
	MOV A,E 			
	STAX B 					; i+1. eleman i. indexe atildi (SWAP islemi gerceklesmis)
	INX B
	INX B 					; Adres 2 arttirilarak i+1. elemana geri donuldu


CHECK_LOOP2:
	INR H
	JMP LOOP2

EXIT:
	LXI D, ARRAY 			; D registerina ARRAY in ilk elemaninin adresi yuklendi

PRINT_ARRAY:
	LDAX D 					; A registerina D yuklenerek A ya arrayin ilk elemaninin adresi yuklenmis oldu
	MOV B,A
	MVI A, PRINT_B
	call GTU_OS

	INX D 				
	INX D 					; bir sonraki index e gidildi (Adres ilerletildigi icin iki defa arttirildi)
	LDA Index 				; yeni index yuklendi
	INR A 					; index arttiriliyor
	STA Index 				; store index
	SUI 50 
	JNZ PRINT_ARRAY 		; Index - 50 == 0 olana kadar sayilar ekrana yazilmaya devam edilir


SEARCH:
	MVI D, Size           	; Size olarak tutuldu, 50 sayi var
    MVI H, 0            	; index
    
    MVI A, READ_B	    	; store the OS call code to A, kullanicidan integer istendi
	call GTU_OS	        	; call the OS

	MOV E, B            	; E=searchNumber
	
	LXI B, INFO_MSG2		; Girilen eleman bilgisi
    MVI A, PRINT_STR
    call GTU_OS

    MOV B, E
	MVI A, PRINT_B      	; KEYBOARD'DAN GELEN DEGER
	call GTU_OS
	
	MOV E, B
    LXI B, ARRAY        	; arrayin baslangic adresi = BC

SEARCH_LOOP:
    LDAX B              	; A=ARRAY[0]
    CMP E               	; A-E; 0 ise devam eder, 0 degilse Continue label'ina atlar
    JNZ Continue        	; A-E 0 ise , B'ye bulundugu index yazilir ve B de ekrana yazilir
    
    LXI B, INFO_MESSAGE		; Eleman bulundu bilgisi verildi
    MVI A, PRINT_STR
    call GTU_OS

    ;MOV A, B 				; A = B, adres A ya atildi
    ;ADD H 					; A = A + H, adres + index degeri A ya atildi
    ;MOV B, A 				; Ekrana yazdirabilmek icin A degeri B registerina atildi

    MOV B, H 				; index degeri B registerina yazildi
    MVI A, PRINT_B	    	; store the OS call code to A  INDEX
    call GTU_OS	        	; call the OS 
    ; index 'i hep iki kati seklinde yaziyor !

    hlt                 	; end program
    
    
Continue:
    INX B               	; arrayin 1 sonraki elemaninin adresine gitmek icin
    INR H               	; index 1 artti
    DCR D               	; size 1 azaldi
    JNZ SEARCH_LOOP	        ; size != 0 ise SEARCH_LOOP'a gider, size == 0 ise EXIT'e gider 
        

    LXI B, ERROR_MESSAGE	; Array'in sonuna gelinip eleman bulunamadiysa hata mesaji ekrana yazdiriliyor
    MVI A, PRINT_STR
    call GTU_OS


	hlt		; end program