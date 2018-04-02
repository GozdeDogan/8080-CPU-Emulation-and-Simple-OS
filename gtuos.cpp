#include <iostream>
#include "8080emuCPP.h"
#include "gtuos.h"
#include <cstring>
#include <fstream>
#include <cmath>

using namespace std;

uint64_t GTUOS::handleCall(const CPU8080 & cpu){
    unsigned int myValue = 0;
    switch(cpu.state->a){
        case 1: // PRINT_B
            PRINT_B(cpu);
            break;
        case 2: // PRINT_MEM
            PRINT_MEM(cpu);
            break;
        case 3: // READ_B
            READ_B(cpu);
            break;
        case 4: // READ_MEM
            READ_MEM(cpu);
            break;
        case 5: // PRINT_STR
            PRINT_STR(cpu);
            break;
        case 6: // READ_STR
            READ_STR(cpu); 
            break;
        case 7:
        	GET_RND(cpu);
        	break;
        default:
            cout << "INVALID SYSTEM CALL" << endl;
    
    }
}

void GTUOS::PRINT_B(const CPU8080 & cpu){
    cout << "System Call: PRINT_B" << endl;
    cout << "Value of B " << (unsigned)(cpu.state->b) << endl;
}

void GTUOS::READ_B(const CPU8080 & cpu){
    unsigned int myValue;
    cout << "System Call: READ_B" << endl;
    cin >> myValue;
    cpu.state->b = myValue;

}

void GTUOS::PRINT_MEM(const CPU8080 & cpu){
    uint16_t wd;
    unsigned int myValue;
    cout << "System Call: PRINT_MEM" << endl;
    wd = ((uint16_t)cpu.state->b << 8) | cpu.state->c;
    myValue = cpu.memory->at(wd);
    cout << "Value of MEM " << myValue << endl;
}

void GTUOS::READ_MEM(const CPU8080 & cpu){
    unsigned int myValue;
    uint16_t wd;
    
    cout << "System Call: READ_MEM" << endl;
    cin >> hex >> myValue;
    wd = ((uint16_t)cpu.state->b << 8) | cpu.state->c;
    cpu.memory->at(wd) = myValue;
}

void GTUOS::PRINT_STR(const CPU8080 & cpu){
    uint16_t wd;
    cout << "System Call: PRINT_STR" << endl;
    wd = ((uint16_t)cpu.state->b << 8) | cpu.state->c;
    while(cpu.memory->at(wd) != '\0'){
        cout << cpu.memory->at(wd);
        wd++;
    } 
    cout << endl;   
}

void GTUOS::READ_STR(const CPU8080 & cpu){
    string s;
    int i=0;
    uint16_t wd;
    
    cout << "System Call: READ_STR" << endl;
    cin >> s;
    wd = ((uint16_t)cpu.state->b << 8) | cpu.state->c;
    i=0;
    while(s[i] != '\0'){
        cpu.memory->at(wd + i) = s[i];
        wd++;
        i++;
    }
    cpu.memory->at(wd + i) = s[i];
    cpu.memory->at(wd + i) = '\0';
}

void GTUOS::GET_RND(const CPU8080 & cpu){
	int randomValue;
    int temp;
    
	cout << "System Call: GET_RND" << endl;
	temp = pow(2, 8) - 1;
	randomValue = rand() % temp;
	cpu.state->b = randomValue;
}


int GTUOS::calculateCycle(const CPU8080 & cpu){
    int cycle = 0;
    switch(cpu.state->a){
        case 1: // PRINT_B
        case 2: // PRINT_MEM
        case 3: // READ_B
        case 4: // READ_MEM
            cycle = 10;
            break;
        case 5: // PRINT_STR 
        case 6: // READ_STR
            cycle = 100;
            break;
        case 7:
        	cycle = 5;
        	break;
    }
    return cycle;
}

void GTUOS::saveMemory(char *filename, const CPU8080& cpu){
	ofstream output;
	output.open(filename);

    if (!output.is_open()) {
        cerr << "Unable to open output file:" << filename << std::endl;
        exit(0);
    }

    for(int i=0;i<0x1000;++i){
        char str[5];
        sprintf(str,"%04x",i*16);
        output << str << " ";
        for(int j=0;j<0x10;++j) {
            sprintf(str,"%02x",cpu.memory->at(i*16+j));
            output << str << " ";
        }
        output << endl;
    }
}