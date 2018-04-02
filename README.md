/******************************************************************************/
/* Gozde DOGAN - 131044019
/* CSE312 - Homework1
/*
/* 30 Mart 2018
/*
/* Kisa odev aciklamasi
/*
/******************************************************************************/



Calistirirken make yapabilirsiniz.
(Verilen makefile kullaniliyor)


ONEMLI:
make yapildiginde memory.h da cstdlib kutuphanesi tanimlanmadigi icin malloc kullanimina hata veriyor.
Bu nedenle memory.h ve MemoryBase.h kutuphaneleri de dosyanin icinde gonderildi.
Eger bu sekilde calistirmak istemiyorsaniz elinizdeki memory.h kutuphanesine
	#include <cstdlib> 
seklinde C'nin standart kutuphanesini eklemelisiniz.
Bu sekilde duzeltme yaptiginizda calisacaktir.


PrintNumbers.asm, Sort.asm, BinarySearch.asm, test.asm yazildi.


PrintNumbers.asm -> 
		Sayilari 0 dan baslayip 50 ye kadar yaziyor. (50 dahil)
		PRINT_B kullanildi
		(510 cycle surecektir.)


Sort.asm ->
		dw ile tanimlanan arrayi siralamaya calisiyor.
		Array elemanlari random olarak uretildi. 
		Siralanmis arrayi PRINT_STR ile ekrana yaziyor.
		(Sort islemi 1250 cycle surecektir.)


BinarySearch.asm ->
		50 random sayi uretilir ve ardindan siralanir. 
		Klavyeden okunan sayi Search algoritmasi ile bu dizi de aranir. 
		Eleman bulunursa index'i, bulunamazsa hata mesaji ekrana yazilir.
		(NOT: index yazilirken index'in 2 kati seklinde yaziliyor)
		(Cycle sayisi eleman bulundugu zaman 1480 cikacaktir. 
		Bulunmadigi zaman ise 1470 cikacaktir.)


test.asm ->
		Burada yazilan system call lar test edildi.
		READ_B ile klavyeden deger aliyor.
		PRINT_B ile aldigi bu degeri ekrana yaziyor.
		READ_MEM ile klavyeden deger aliyor.
		PRINT_MEM ile aldigi bu degeri ekrana basiyor.
		READ_STR ile klavyeden string aliyor.
		PRINT_STR ile bu stringi ekrana basiyor.
		GET_RND ile random bir sayi uretiliyor. 
		Ve uretilen bu sayi B register'ina yaziliyor. 
		PRINT_B ile B register'i ekrana yazilarak bu deger goruluyor. 
		(cycle sayisi 255 cikacaktir.)
 

NOT ->
		Odev ile gelen printstr.asm, sum.asm ve sum2.asm icin de .com uzantili dosyalar olusturuldu.