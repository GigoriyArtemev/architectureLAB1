unsigned int flag;
#define OVERFLOW 0
#define FAIL_TO_DEVISION_ZERO 1
#define OUT_OF_MEMORY 2
#define IGNORE_IMP 3
#define WRONG_COMMAND 4

#include "mySimpleComputer.h"
#include <iostream>
#include <stdlib.h>
#include <io.h>
#include <fcntl.h>
#include <stdio.h>
int A[100];
using namespace std;

int sc_memoryInit() {
	cout << "memory was init" << endl;
	
		for (int i = 0; i < 100; i++) {
			A[i] = 0; 
		} 
		return *A;
}
int sc_memorySet(int address, int value) {
	if (address <= 99 && address >= 0) {
		A[address] = value;
		cout << endl;
		return *A;
	}
	else
	{
		flag = flag | (1 << OUT_OF_MEMORY);
		return -1;
	}
}
int sc_memoryGet(int address, int* value) {
	if (address <= 99 && address >= 0) {
		*value = A[address];
		cout << *value << endl;
	}
	else
	{
		flag = flag | (1 << OUT_OF_MEMORY);
		return -1;
	}
}
int sc_memorySave(char* filename) {
	FILE* file = NULL;  //указатель
	int len = 100;      //число элементов массива
	file = fopen("filename.bin", "wb"); 

	if (file == NULL) { //если нельз€ создать или открыть
		printf("Error");
		return 1;
	}
	fwrite(&len, sizeof(int), 1, file);
	fwrite(A, sizeof(int), len, file); 
	printf("save: %d\n", len);
	fclose(file); 
}
int sc_memoryLoad(char* filename) {
	FILE* Read = fopen("filename.bin", "rb");

	if (Read == NULL) { //если нельз€ открыть
		printf("Error");
		return 1;
	}
	int lenRead;    //здесь будет хранитьс€ число элементов дл€ чтени€ в файле
	fread(&lenRead, sizeof(int), 1, Read);
	//выдел€ем пам€ть под массив дл€ чтени€
	int* ArrIn = (int*)malloc(lenRead * sizeof(int));
	//читаем данные
	fread(ArrIn, sizeof(int), lenRead, Read);

	fclose(Read);   //закрываем файл

	printf("read: %d \n", lenRead);
	printf("load. ");
	for (int i = 0; i < lenRead; i++)
		A[i]= ArrIn[i];
	free(ArrIn);    //освобождаем пам€ть
	return 0;
}
void ShowBin(int a)
{
	for (int i = 0; i < 8; i++)
	{
		//ѕровер€ем старший бит)
		if (a & 0x80)
			cout << "1";
		else
			cout << "0";
		//—двигаем влево на 1 бит
		a = a << 1;
	}
	cout << endl;
}
int sc_regInit(void) {
	flag = 0;
	//ShowBin(flag);
	return 0;
}
int sc_regSet(int Register, int value) {
	if (Register < 0 || Register > 5) {
		return 1;
	}
	if (value == 1) {
		flag |= (1 << (Register -1));
	}
	else {
		flag &= (~(1 << (Register - 1)));

	}
	return 0;
}

int sc_regGet(int Register, int* value) {
	if (Register < 0 || Register > 4) {
		return -1;
	}
	if (flag & (1 << Register))
		*value = 1;
	else
		*value = 0;
	cout << *value << endl;
	return 0;
}
int sc_commandEncode(int command, int operand, int* value) {
	if ((command > 128) || (operand > 128) || (command < 0) || (operand < 0)) {
		return -1;
	}
	*value = ((command << 7) | operand);
	ShowBin(*value);
	cout << *value << endl;

	return 0;
}

int sc_commandDecode(int value, int* command, int* operand) {
	if ((value > 256) || (value < 0)) {
		flag |= WRONG_COMMAND;
		return -1;
	}
	*command = (value >> 7) & 0x7F;
	*operand = value & 0x7F;
	cout << *command <<" " << *operand;
	return 0;
}
