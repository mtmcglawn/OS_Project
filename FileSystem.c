#include <stdio.h> 
#include <stdbool.h>
FILE *fptr;

//Erase All Sectors sets all bits in simlates memory to value 1
// if necessary, creates the file simulating the medium
bool EraseAllSectors() {
	fptr = fopen("memory.bin","wb+");
	for(int i= 0; i<20; i++){
		EraseSector(i); 
	}
	return 1;
}

//Read Word: Reads a word (2 bytes) from specific address
ReadWord (nAddress) {

}
//Write Word: Writes a WORD (2bytes) to spefic address
WriteWord (nAddress, nWord) {
	
}


int main(){ 
EraseAllSectors();      
return 0;   
}  
