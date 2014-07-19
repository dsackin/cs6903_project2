/**
 *  common_main.h
 *
 *
 *  Created on: Jun 18, 2014
 *      Author: Douglas Sackin, NYU CS6903, Summer 2014
 */

#include <getopt.h>

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cryptopp/rsa.h>
#include <cryptopp/osrng.h>
#include <cryptopp/asn.h>
#include <cryptopp/queue.h>
#include <cryptopp/files.h>
#include <cryptopp/hmac.h>
#include <cryptopp/sha.h>
#include <cryptopp/hex.h>

#include <boost/filesystem/path.hpp>

#include "CloudEncryptor.h"


#include "common.h"
#include "prettyprint/prettyprint.hpp"




/**
 * Print a simple message describing the usage of this program
 * @param os - Reference to an output stream to which to write the usage message
 */
void printUsage(std::ostream &os) {
	os << "Usage: decrypt [-d <dictionaryPath>] [-c <cipherPath>] [-t <keyLength>]" << std::endl;
	os << "Attempts to decrypt a cipher text and identify the originating plain text from " << std::endl;
	os << "a dictionary of plain texts. " << std::endl;
	os << std::endl;
	os << std::endl;
	os << "This program requires the dictionary, cipher text, and key length as inputs. " << std::endl;
	os << "You may specify any or none of these on the command line. If no dictionary " << std::endl;
	os << "path is provided, the default dictionary embedded in the program will be " << std::endl;
	os << "assumed. The rest will be collected from stdin." << std::endl;
	os << std::endl;
	os << "-h - print this help message" << std::endl;
	os << "-k <key> or <keyFilePath> - key value or path to a file containing the key" << std::endl;
	os << "   candidate per line" << std::endl;
	os << "-f <cipherPath> - optional path to a text file containing a single line of " << std::endl;
	os << "   cipher text for the decryption attempt. If not provided as an argument, " << std::endl;
	os << "   this will be requested via stdin" << std::endl;
	os << "-n <keyLength> - optional integer length of a key phrase believed to be used " << std::endl;
	os << "   in the encryption. If not provided as an argument, this will be requested " << std::endl;
	os << "   via stdin" << std::endl;
	os << std::endl;
}





/**
 * Main program to execute the decrypt functionality using a provided cipher
 * text and plain text dictionary.
 *
 * @param argc - count of arguments
 * @param argv - array of c-style strings
 * @return
 */
int main(int argc, char **argv) {

	// process command line arguments
	processArguments(argc, argv, printUsage);

	std::cout << "hello preprocess" << std::endl;
	std::cout << key << std::endl;
	std::cout << filePath << std::endl;
	std::cout << fileName << std::endl;

//	unsigned char hashOfKey[CryptoPP::SHA512::DIGESTSIZE];
//	char key[] = "something secret";
//
//	CryptoPP::SHA512 sha;
//	sha.CalculateDigest(hashOfKey, (unsigned char*)key, strlen(key));
//
//	char hexHash[2 * sizeof(hashOfKey) + 1];
//	CryptoPP::HexEncoder hexEncoder;
//	hexEncoder.Put(hashOfKey, sizeof(hashOfKey));
//	hexEncoder.MessageEnd();
//	hexEncoder.Get((unsigned char*)hexHash, 2 * sizeof(hashOfKey));
//	hexHash[2 * sizeof(hashOfKey)] = 0;
//
//	std::cout << hexHash << std::endl;
//
//	unsigned char fn1[] = "name of my file.txt";
//
//	byte fk1[64], fk2[64];
//	buildSymmetricKey(fk1, 64, hashOfKey, 64, fn1, strlen((char*)fn1));
//
//	byte hexFK[2 * 64 + 1];
//	CryptoPP::HexEncoder hexEncoder2;
//	hexEncoder2.Put(fk1, 64);
//	hexEncoder2.MessageEnd();
//	hexEncoder2.Get(hexFK, 2 * 64);
//	hexFK[2 * 512] = 0;
//
//	printf("%s\n", hexFK);
//
//
//
//	CryptoPP::HMAC<CryptoPP::SHA512> hmac(hashOfKey, sizeof(hashOfKey));
//
//	hmac.CalculateDigest(fk2, fn1, strlen((char*)fn1));
//
//	char hexFK2[2 * sizeof(fk2) + 1];
//	CryptoPP::HexEncoder hexEncoder3;
//	hexEncoder3.Put(fk2, sizeof(fk2));
//	hexEncoder3.MessageEnd();
//	hexEncoder3.Get((unsigned char*)hexFK2, 2 * sizeof(fk2));
//	hexFK2[2 * sizeof(fk2)] = 0;
//
//	printf("%s\n", hexFK2);
//

	std::string s1 = CloudEncryptor<CryptoPP::SHA512>::GenerateObfuscatedName("something else.txt");

	std::cout << s1 << std::endl;


}
