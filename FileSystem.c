#include <stdio.h> 
#include <stdbool.h>

/*
Program to create and manipulate a .bin file that represents
	memory.

@author James Barr
@author Chris Flodstrom
@author Eliza Hall
@author Matthew McGlawn
@author	Wesley Monnette
@author Alexa Monroe

@version 2020-02-16
*/

FILE *fptr;

static int SECTORS = 20;
static long int SECTOR_SIZE = 64000; //In bytes
static long int FILE_SIZE = 1280000; //In bytes

struct word {
	unsigned char byte1;
	unsigned char byte2;
};

bool EraseAllSectors();
struct word ReadWord(long nAddress);
bool WriteWord(long nAddress, struct word nWord);
bool EraseSector(int Sect);

/*
Erase All Sectors sets all bits in simlates memory to value 1
if necessary, creates the file simulating the medium.

@return bool value upon proper completion.
*/
bool EraseAllSectors(){

	//Opens or creates file
	fptr = fopen("memory.bin","wb+");

	//Loops through all sectors and Erases them
	for(int i = 0; i < SECTORS; i++){
		EraseSector(i); 
	}
	return 1;
}

/*
Reads a WORD (2 bytes) from the specified address. Address should
be on the WORD boundary, i.e., addresses 0, 2, …, 2n are valid, 
addresses 1, 3, …, 2n-1 are not. If specified address is not WORD
aligned or is outside the size of the simulated medium, this
operation should fail.

@param nAddress – address of the WORD to be read. Address is the
	offset from the beginning of the simulated memory (i.e., byte 
	0 in Sector 0) and not from the particular sector.
@return struct that contains the Word at the address.
*/
struct word ReadWord(long nAddress){

	struct word result;
	unsigned char storage[2];

	//Checks that address is on WORD boundary
	if((nAddress % 2) != 0){
		printf("Address must be on WORD boundary.(i.e. even index)");
		return result;
	}

	//Makes sure file can be opened
	fptr = fopen("memory.bin","rb");
	if(fptr == NULL){
		EraseAllSectors();
		fclose(fptr);
		fptr = fopen("memory.bin", "rb");
	}

	//Compares the Address to the file size
	if((FILE_SIZE < nAddress) || nAddress < 0){
		printf("Address out of file size bounds.");
		return result;
	}

	//Goes to the location and retrieves the WORD
	fseek(fptr, nAddress, SEEK_SET);//Goes to address
	fgets(storage, 3, fptr);//Changes value
	fclose(fptr);//Closes file

	//Puts specified bytes into word structure
	result.byte1 = storage[0];
	result.byte2 = storage[1];

	return result;
}

/*
Writes a WORD (2 bytes) to the specified address. If specified
address is not WORD aligned or is outside the size of the simulated
memory, this operation should fail, i.e., no information should be
written in the simulated memory. If address is valid, the value
written in the specified address should be equal to nWord AND (bitwise)
ReadWord (nAddress) Whether this function returns value or not and
what is the meaning of the returned value is a decision you should
make.

@param nAddress – address in which the WORD should be written.
@param nWord – WORD to be written in the specified address.
@return bool value discerning between proper completion or failure.
*/
bool WriteWord(long nAddress, struct word nWord){

	//Checking for WORD boundary
	if((nAddress % 2) != 0){
		printf("Address must be on WORD boundary.(i.e. even index)");
		return 0;
	}

	struct word rWord = ReadWord(nAddress);//Gets the current value
	
	//Opening the file to manipulate
	fptr = fopen("memory.bin", "rb+");
	if (fptr == NULL){
		EraseAllSectors();
		fclose(fptr);
		fptr = fopen("memory.bin", "rb");
	}

	//Bitwise AND to calculate the new value
	unsigned char byteOne = rWord.byte1 & nWord.byte1;
	unsigned char byteTwo = rWord.byte2 & nWord.byte2;

	struct word finalWord = {byteOne, byteTwo};//word creation

	//Replacing the current WORD value with the new WORD
	fseek(fptr, nAddress, SEEK_SET);//Goes to address
	fwrite(&finalWord, sizeof(struct word), 1, fptr);//Changes value
	fclose(fptr);//Closes file

	return 1;
}

/*
Sets all bits in the specified sector to 1. Sector numbers are 
0-19. If file simulating simulated memory is not present,
EraseAllSectors() is executed first.

@param nSectorNr - int containing the sector to erase.
@return bool representing successful completion.
*/
bool EraseSector(int nSectorNr){

	static struct word allOnes = {0xFF, 0xFF};//"Erased" word

	//Program calls EraseAllSectors if NULL to create new file
	fptr = fopen("memory.bin","rb+");
	if(fptr == NULL){
		EraseAllSectors();
	}

	//Moves file pointer to selected sector
	fseek(fptr, (nSectorNr * SECTOR_SIZE), SEEK_SET);

	//Wites the word allOnes to each word in the sector filling it
	for(int i = 0; i < 32000; i++){
		fwrite(&allOnes, sizeof(struct word), 1, fptr);
	}
	fclose(fptr);//Closes file

	return 0;
}

/*
Function used for testing purposes
*/
int main(){
	long placement = 4;//place to write
	unsigned char testA = 0xAA;//AA = 1010 1010
	unsigned char testB = 0xAA;//AA = 1010 1010
	unsigned char inFileA = 0xFF;//FF = 1111 1111
	unsigned char inFileB = 0xFF;//FF = 1111 1111

	//ensures the file has been created
	//EraseAllSectors();//Makes file All "FF"

	//Gets original value to compare against
	struct word test = ReadWord(placement);
	
	//Writes the word
	struct word test1 = {testA, testB};//word to be written
	WriteWord(placement, test1);

	//Gets new value to compare against
	struct word test2 = ReadWord(placement);

	//shows original value 
	printf("%X%X\n", inFileA, inFileB);//Actual
	printf("%X%X\n", test.byte1, test.byte2);//Actual

	//shows value to be written
	printf("%X%X\n", testA, testB);//Expected
	printf("%X%X\n", test1.byte1, test1.byte2);//Actual

	//shows returned value
	printf("%X%X\n", testA & inFileA, testB & inFileB);//Expected
	printf("%X%X\n", test2.byte1, test2.byte2);//Actual
	
	return 0;
}  
