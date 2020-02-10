#include <stdio.h> 
#include <stdbool.h>
FILE *fptr;

//Erase All Sectors sets all bits in simlates memory to value 1
// if necessary, creates the file simulating the medium
/*bool EraseAllSectors() {
	fptr = fopen("memory.bin","wb+");
	for(int i= 0; i<20; i++){
		EraseSector(i); 
	}
	return 1;
}*/

//Read Word: Reads a WORD (2 bytes) from specific address
void ReadWord (int nAddress) {
	char result[2];
	//checks that address is on boundary
	if ((nAddress % 2) != 0) {
		printf("Address must be on WORD boundary.(i.e. even index)");
		return;
	}
	//makes sure file can be opened
	fptr = fopen("memory.bin","rb");
	if (fptr == NULL) {
		printf("Unable to open file.");
		return;
	}
	fseek(fptr, 0, SEEK_END);
	long int size = ftell(fptr);
	if (size < nAddress) {
		printf("Address must be less than file size.");
		return;
	}
	fseek(fptr, nAddress, SEEK_SET);
	fgets(result, 3, fptr);
	printf("Word located at index %d", nAddress);
	printf(" is: %s", result);

}
//Write Word: Writes a WORD (2bytes) to specific address
void WriteWord (int nAddress, int nWord) {
	
}

int main(){ 
ReadWord(4); 
return 0;   
}  
