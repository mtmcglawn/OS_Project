#include <stdio.h> 
#include <stdbool.h>

static int SECTOR_SIZE = 3200;
static int FILE_SIZE = 64000;


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
	int position=SECTOR_SIZE%8;
	int mask=1<<position;

	return ;
}


int main(){       
return 0;   
}  
