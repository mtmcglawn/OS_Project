#include <stdio.h> 
#include <stdbool.h>
FILE *fptr;

static int SECTOR_SIZE = 64000; //In bytes
static int FILE_SIZE = 1280000; //In bytes

struct word {
	unsigned char byte1;
	unsigned char byte2;
};

bool EraseAllSectors();
struct word ReadWord(long nAddress);
bool WriteWord(long nAddress, struct word nWord);
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
struct word ReadWord (long nAddress) {
	struct word result;
	unsigned char storage[2];
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
	long size = SECTOR_SIZE * FILE_SIZE;
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
bool WriteWord(long nAddress, struct word nWord){
	if ((nAddress % 2) != 0) {
		printf("Address must be on WORD boundary.(i.e. even index)");
		return 0;
	}

	if (fptr == NULL){
		printf("Unable to open file!");
		return 0;
	}

	FILE *fptr = fopen("memory.bin", "wb");
	struct word rWord = ReadWord(nAddress);

	unsigned char byteOne = rWord.byte1 & nWord.byte1;
	unsigned char byteTwo = rWord.byte2 & nWord.byte2;
   printf("%X %X\n",byteOne, byteTwo);//THIS IS WHAT WILL GO INTO FWRITE AND IS WRONG
 

	struct word finalWord = {byteOne, byteTwo};
   //COMMENTED OUT FSEEK SINCE I WANT TO DO FIRST WORD ANYWAYS FOR TEST
	//fseek(fptr, nAddress, SEEK_SET);
	fwrite(&finalWord, sizeof(struct word), 1, fptr);
   //fwrite(&finalWord.byte1, sizeof(char), 1, fptr);
   //fwrite(&finalWord.byte2, sizeof(char), 1, fptr);
	fclose(fptr);
	return 1;
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
	for(int i = 0; i < 32000; i++){
		fwrite(&allOnes, sizeof(struct word), 1, fptr);
	}
	//Closes file
	fclose(fptr);

	return 0;
}

int main(){
	EraseAllSectors();
	//struct word test = ReadWord(998);
	struct word test1 = {0x66, 0xAA};//AA=10101010
   //WriteWord(998, test1);
	WriteWord(0, test1);
	printf("%X %X %X\n", ReadWord(0),ReadWord(0).byte1,ReadWord(0).byte2 ); 
	return 0;
}  
