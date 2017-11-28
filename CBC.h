#include <iostream>
#include <string.h>
#include <stdio.h>



class CBC{
	
	public:

		int encrypt(std::string M, std::string C, int key);		// returns IV generated so that data can be decrypted
		void decrypt(std::string M, std::string C, int key, int IV);
		int get_IV();
		
	private:
		uint64_t enc(uint32_t l, uint32_t r, int key);			// helper fiestel functions both run for 16 rounds
		uint64_t dec(uint32_t l, uint32_t r, int key);
		int key;
		int IV;				// either rand generated int or user input if decrypting
		std::string M;			// name of plaintext file 
		std::string C;			// name of ciphertext file 
	
};
	
	