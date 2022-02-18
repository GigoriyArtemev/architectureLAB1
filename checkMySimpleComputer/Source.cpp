#include <iostream>
#include "mySimpleComputer.h"
using namespace std;
char* filename = new char;
int main() {
	int *value = new int;
	int *command = new int;
	int *operand = new int;
	sc_memoryInit();
	sc_regInit();
   
	sc_memorySet(100, 75);	
	
	sc_memoryGet(10,value);
	sc_memorySave(filename);
	sc_memoryLoad(filename);
	sc_regSet(3, 1);
	sc_regGet(3, value);
	sc_regSet(4, 1);
	sc_regSet(3, 0);
	sc_regGet(3, value);
	sc_regGet(4, value);
	sc_commandEncode(7, 8, value);
	sc_commandDecode(255, command, operand);
	}
