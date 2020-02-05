#include <stdio.h> 
#include <stdbool.h>

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

int toggle_bit() {
	//Toggle a set number of bits
	int element=block/8;
	int position=block%8;
	int mask=1<<position;

	bitmap[element]^=mask;

	return bitmap[element]&mask;
}


int main(){       
return 0;   
}  
