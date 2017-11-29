#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <unistd.h>
#include "CBC.h"

int CBC::encrypt(std::string M, std::string C, int key)
{
	// generate rand IV
	int IV = std::rand() % sizeof(uint64_t);
	uint64_t C1, C2;
	uint32_t left, right;
	
	FILE * infile;
	FILE * outfile;
	
	// read from M 
	infile = fopen(M.c_str(), "rb");
	if(infile == NULL){
		std::cout << "Cannot open M file to encrypt" << std::endl;
		return 0;
	}
	outfile = fopen(C.c_str(), "wb");
	
	C1 = IV;
	
	while(!feof(infile)){
		// C0 use IV during XOR with C1
		memset(&C2, 0,sizeof(C2));
		fread(&C2, 1, sizeof(C2), infile);
		
		C2 = C1 ^ C2;
		left = (C2>>32) & 0xFFFFFFFF;
		right = C2 & 0xFFFFFFFF;
		C2 = enc(left, right, key);
		C1 = C2;
		
		fwrite(&C2, 1, sizeof(C2), outfile);			// append ciphertext to outfile
	}
	
	
	
	fclose(infile);
	fclose(outfile);
	
	return IV;
}

void CBC::decrypt(std::string M, std::string C, int key, int IV)
{
	uint64_t C1, C2, temp;
	uint32_t left, right;
	int first = 1;
	FILE * infile;
	FILE * outfile;
	
	
	// read from C 
	infile = fopen(C.c_str(), "rb");
	if(infile == NULL){
		std::cout << "Cannot open C file to decrypt" << std::endl;
		return;
	}
	outfile = fopen(M.c_str(), "wb");
	//outfile = fopen("temp.txt", "wb");
	
	while(!feof(infile)){
		memset(&C2, 0, sizeof(C2));
		fread(&C2, 1, sizeof(C2), infile);
		temp = C2;
		left = (C2>>32) & 0xFFFFFFFF;
		right = C2 & 0xFFFFFFFF;
		C2 = dec(left, right, key);
		if(first){
			C2 ^= IV;
			first = 0;
		}
		else{
			C2 ^= C1;
		}
		C1 = temp;
		fwrite(&C2, 1, sizeof(C2), outfile);	
	}
	
	fclose(infile);
	fclose(outfile);
	
	/*
	// unpad message
	std::ifstream padded("temp.txt");
	std::ofstream unpadded(M.c_str());
	char notnull;
	
	do{
		padded.get(notnull);
		if(notnull == NULL){
			// ignore null padding
		}
		else
			unpadded.put(notnull);
	}while(!padded.eof());
		
	padded.close();
	unpadded.close();
	*/
	/*
	FILE * fp;
	std::string command("cat temp.txt | tr -d '\\000'  > ");
	command.append(M);
	fp = popen(command.c_str(), "r");
	pclose(fp);
	*/
	
	return;
}

int CBC::get_IV()
{
	return IV;
}

uint64_t CBC::enc(uint32_t l, uint32_t r, int key)
{
	uint32_t i, left, right;
	uint32_t k = key % sizeof(uint32_t); 		// make sure key is right size
	
	for(i=0; i<16; i++){
		left = (l ^ k) ^ r;
		right = l;
		// last round of encryption
		if(i == 15){
			left = r;
			right = l;
		}
		else{
			left = l;
			right = r;
		}
	}
	return (uint64_t)left<<32 | right;
}

uint64_t CBC::dec(uint32_t l, uint32_t r, int key)
{
	uint32_t left, right, i;
	uint32_t k = key % sizeof(uint32_t);
	
	for(i=0; i<16; i++){
		left = (l ^ k) ^ r;
		right = l;
		if(i == 15){
			left = r;
			right = l;
		}
		else{
			left = l;
			right = r;
		}
	}
	return (uint64_t)left<<32 | right;
}