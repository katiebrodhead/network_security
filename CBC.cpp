#include <iostream>
#include <string.h>
#include <stdio.h>
#include <cstdlib>
#include <fstream>
#include <unistd.h>
#include "CBC.h"

int CBC::encrypt(std::string M, std::string C, int key)
{
	// generate rand IV
	int IV = std::rand() % sizeof(uint64_t);
	uint64_t C1, C2;
	uint32_t left, right;

	
	// read from M 
	std::ifstream infile(M, std::ifstream::binary);
	if(!infile){
		return 0;
	}
	std::ofstream outfile(C, std::ofstream::binary);
	
	
	
	while(!infile.eof()){
		// C0 use IV during XOR with C1
		memset(&C2, 0,sizeof(C2));
		infile.read(&C2, sizeof(C2));
		if(!C1){
			C2 = IV ^ C2;
			left = (C2>>32) & 0xFFFFFFFF;
			right = C2 & 0xFFFFFFFF;
			C2 = enc(left, right, key);
			C1 = C2;
		}
		// use C1 to XOR with C2 
		else{
			C2 = C1 ^ C2;
			left = (C2>>32) & 0xFFFFFFFF;
			right = C2 & 0xFFFFFFFF;
			C2 = enc(left, right, key);
			C1 = C2;
		}
		
		outfile.write(&C2, sizeof(C2));			// append ciphertext to outfile
	}
	
	infile.close();
	outfile.close();
	return IV;
}

void CBC::decrypt(std::string M, std::string C, int key, int IV)
{
	uint64_t C1, C2;
	uint32_t left, right, temp;
	int first = 1;
	
	// read from C 
	std::ifstream infile(C, std::ifstream::binary);
	if(!infile){
		return;
	}
	std::ofstream outfile(M, std::ofstream::binary);
	
	while(!infile.eof()){
		memset(&C2, 0, sizeof(C2));
		infile.read(&C2, sizeof(C2));
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
		outfile.write(&C2, sizeof(C2));	
	}
	
	infile.close();
	outfile.close();
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