#include <stdio.h> 
#include <stdbool.h>
FILE *fptr;

static int SECTOR_SIZE = 64000; //In bytes
static int FILE_SIZE = 1280000; //In bytes

struct word {
	char byte1;
	char byte2;
};

bool EraseAllSectors();
char* ReadWord(int nAddress);
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
char* ReadWord (int nAddress) {
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
void WriteWord (int nAddress, struct word nWord) {
	static char word[2];

	if ((nAddress % 2) != 0) {
		printf("Address must be on WORD boundary.(i.e. even index)");
		return word;FILE * fptr
	}

	if(fptr == NULL){
		printf("Unable to open file!");
		return 1;
	}

	FILE *fptr = fopen("memory.bin","wb");
	fseek(fptr, nAddress, SEEK_SET);
	fwrite(word, sizeof(writeFile), SEEK_SET;
	fclose(fptr);

	
}

//Given a Sect from 0-19 toggle all bits in that sector to 1
bool EraseSector(int Sect) {
	FILE *fptr;
	static struct word allOnes = {0xFF, 0xFF};

	//Program exits if the file pointer returns NULL.
	fptr = fopen("memory.bin","rb+");
	if(fptr == NULL){
		EraseAllSectors();
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
