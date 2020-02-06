#include <stdio.h> 
#include <stdbool.h>

static int SECTOR_SIZE = 3200; //In bytes
static int FILE_SIZE = 64000; //In bytes



struct word {
	char byte1;
	char byte2;
}




//Erase All Sectors (sets all bits in simlates memory to value 1)
// if necessary, creates the file simulating the medium
bool EraseAllSectors() {
	if () { //if file does not 
		//create file
	}
	for(int i= 0; i<20; i++){
		EraseSector(i);
	}
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
return 0;   
}  
