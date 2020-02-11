#include <stdio.h> 
#include <stdbool.h>
FILE *fptr;

static int SECTOR_SIZE = 3200; //In bytes
static int FILE_SIZE = 64000; //In bytes

struct word {
	char byte1;
	char byte2;
}


//Erase All Sectors sets all bits in simlates memory to value 1
// if necessary, creates the file simulating the medium

bool EraseAllSectors() {
	fptr = fopen("memory.bin","wb+");
	for(int i= 0; i<20; i++){
		EraseSector(i); 
	}
	return 1;

//Read Word: Reads a WORD (2 bytes) from specific address
char * ReadWord (int nAddress) {
	static char word[2];
	//checks that address is on boundary
	if ((nAddress % 2) != 0) {
		printf("Address must be on WORD boundary.(i.e. even index)");
		return word;
	}
	//makes sure file can be opened
	fptr = fopen("memory.bin","rb");
	if (fptr == NULL) {
		printf("Unable to open file.");
		return word;
	}
	fseek(fptr, 0, SEEK_END);
	long int size = ftell(fptr);
	if (size < nAddress) {
		printf("Address must be less than file size.");
		return word;
	}
	fseek(fptr, nAddress, SEEK_SET);
	fgets(word, 3, fptr);
	return word;

}

//Write Word: Writes a WORD (2bytes) to spefic address
WriteWord (nAddress, nWord) {
	
}

//Given a Sect from 0-19 toggle all bits in that sector to 1
bool EraseSector(int Sect) {
	FILE *fptr;
	struct word allOnes = {0xFF, 0xFF};

	//Program exits if the file pointer returns NULL.
	fopen(&fptr, "memory.bin","wb");
	if(fptr == NULL){
		printf("Unable to open file!");
		return 1;
	}

	//Moves file pointer to selected sector
	fseek(fptr, (Sect * SECTOR_SIZE), SEEK_SET);
	//Wites the word allOnes to each word in the sector filling it with 1s.
	fwrite(&allOnes, sizeof(allOnes), 1600, fptr);
	//Closes file
	fclose(fptr);

	return 0;
}

int main(){ 
EraseAllSectors();      
return 0;   
}  
