#include <iostream>
#include "8080emuCPP.h"
#include "gtuos.h"
#include "memory.h"
#include <cstring>
#include <fstream>

using namespace std;

int DebugZero(CPU8080 &theCPU, GTUOS theOS, int DEBUG);
int DebugOne(CPU8080 &theCPU, GTUOS theOS, int DEBUG);
int DebugTwo(CPU8080 &theCPU, GTUOS theOS, int DEBUG);
char *findFileName(char *fileName);
void saveMemory(memory mem, string fileName);



int main (int argc, char**argv){

	if (argc != 3){
		std::cerr << "Usage: prog exeFile debugOption\n";
		exit(1); 
	}

	int DEBUG = atoi(argv[2]);
	int cycle = 0;
	
	memory mem;
	CPU8080 theCPU(&mem);
	GTUOS	theOS;

	theCPU.ReadFileIntoMemoryAt(argv[1], 0x0000);	

	switch(DEBUG){
		case 0:
			cout << "DEBUG MODE 0" << endl;
			cycle = DebugZero(theCPU, theOS, DEBUG);
			break;
		case 1:
			cout << "DEBUG MODE 1" << endl;
			cycle = DebugOne(theCPU, theOS, DEBUG);
			break;
		case 2:
			cout << "DEBUG MODE 2" << endl;
			cycle = DebugTwo(theCPU, theOS, DEBUG);
			break;
		default:
			break;

	}

	char *fileName = findFileName(argv[1]);
	theOS.saveMemory(fileName, theCPU);
	cout << "Total number of cycles " << cycle << endl;

	return 0;
}


int DebugZero(CPU8080 &theCPU, GTUOS	theOS, int DEBUG){
	int cycle = 0;
	while (!theCPU.isHalted())
	{
		theCPU.Emulate8080p(DEBUG);
		if(theCPU.isSystemCall()){
			theOS.handleCall(theCPU);
	    	cycle += theOS.calculateCycle(theCPU);
			cout << "Cycles " << cycle << endl;
		}
    }

    return cycle;
}


int DebugOne(CPU8080 &theCPU, GTUOS	theOS, int DEBUG){
	int cycle = 0;

	while (!theCPU.isHalted())
	{
		theCPU.Emulate8080p(DEBUG);
		if(theCPU.isSystemCall()){
			theOS.handleCall(theCPU);
			cycle += theOS.calculateCycle(theCPU);
			cout << "Cycles " << cycle << endl;
		}
    }

    return cycle;
}

int DebugTwo(CPU8080 &theCPU, GTUOS	theOS, int DEBUG){
	int cycle = 0;

	while (!theCPU.isHalted())
	{
		theCPU.Emulate8080p(DEBUG);
		if(theCPU.isSystemCall()){
			theOS.handleCall(theCPU);
		    cycle += theOS.calculateCycle(theCPU);
			cout << "Cycles " << cycle << endl;
		}
		cin.get(); /*enter girilmesini bekliyor*/
    }

    return cycle;
}

char *findFileName(char *fileName){
	char *token;
	token = strtok(fileName, ".");

	sprintf(fileName, "%s.mem", token);

	return fileName;
}

