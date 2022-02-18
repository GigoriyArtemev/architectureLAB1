#pragma once
#ifndef mySimpleComputer_H
#define mySimpleComputer_H
void ShowBin(int a);
int sc_memoryInit();
int sc_memorySet(int address, int value);
int sc_memoryGet(int address, int* value);
int sc_memorySave(char* filename);
int sc_memoryLoad(char* filename);
int sc_regInit(void);
int sc_regSet(int Register, int value);
int sc_regGet(int Register, int* value);
int sc_commandEncode(int command, int operand, int* value);
int sc_commandDecode(int value, int* command, int* operand);
#endif // !mySimpleComputer_H
