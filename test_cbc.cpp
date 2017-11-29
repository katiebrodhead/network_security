#include <string>
#include <iostream>
#include "CBC.h"
#include <stdlib.h>

int main(){
	
	CBC encrypt_test;
	std::string plaintxt("agrippa_test.txt");
	//  std::string plaintxt("1041.txt");
	std::string ciphertxt("ctxt.txt");
	std::string decryptedtxt("plaintxt.txt");
	int IV, key;
	
	key = rand() % sizeof(uint64_t);
	
	IV = encrypt_test.encrypt(plaintxt, ciphertxt, key);
	encrypt_test.decrypt(decryptedtxt, ciphertxt, key, IV);	
	
	
	return 0;
} 