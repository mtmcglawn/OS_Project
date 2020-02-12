#include <stdio.h> 
#include <stdbool.h>
FILE *fptr;

static int SECTOR_SIZE = 32000; //In bytes
static int FILE_SIZE = 640000; //In bytes

struct word {
	char byte1;
	char byte2;
};

bool EraseAllSectors();
struct word ReadWord(int nAddress);
void WriteWord(int nAddress, struct word nWord);
bool EraseSector(int Sect);

//Erase All Sectors sets all bits in simlates memory to value 1
// if necessary, creates the file simulating the medium

bool EraseAllSectors() {
	fptr = fopen("memory.bin","wb+");
	for(int i= 0; i<20; i++){
		EraseSector(i); 
	}
	return 1;
}

//Read Word: Reads a WORD (2 bytes) from specific address
struct word ReadWord (int nAddress) {
	struct word result;
	char storage[2];
	//checks that address is on boundary
	if ((nAddress % 2) != 0) {
		printf("Address must be on WORD boundary.(i.e. even index)");
		return result;
	}
	//makes sure file can be opened
	fptr = fopen("memory.bin","rb");
	if (fptr == NULL) {
		printf("Unable to open file.");
		return result;
	}
	//calculates size of file 
	long int size = SECTOR_SIZE * FILE_SIZE;
	if ((size < nAddress) || nAddress < 0)  {
		printf("Address out of file size bounds.");
		return result;
	}
	fseek(fptr, nAddress, SEEK_SET);
	fgets(storage, 3, fptr);
	fclose(fptr);
	//puts specified bytes into word structure
	result.byte1 = storage[0];
	result.byte2 = storage[1];
	return result;
}

//Write Word: Writes a WORD (2bytes) to spefic address
void WriteWord (int nAddress, struct word nWord) {
	
}

//Given a Sect from 0-19 toggle all bits in that sector to 1
bool EraseSector(int Sect) {
	FILE *fptr;
	struct word allOnes = {0xFF, 0xFF};

	//Program exits if the file pointer returns NULL.
	fptr = fopen("memory.bin","wb");
	if(fptr == NULL){
		printf("Unable to open file!");
		return 1;
	}

	//Moves file pointer to selected sector
	fseek(fptr, (Sect * SECTOR_SIZE), SEEK_SET);
	//Wites the word allOnes to each word in the sector filling it with 1s.
	fwrite(&allOnes, sizeof(allOnes), (SECTOR_SIZE / 2), fptr);
	//Closes file
	fclose(fptr);

	return 0;
}

int main(){ 
	EraseAllSectors();      
	return 0;   
}  
