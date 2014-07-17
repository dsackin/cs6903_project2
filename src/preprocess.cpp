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
#include <rsa.h>
#include <osrng.h>
#include <asn.h>
#include <queue.h>
#include <files.h>

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

void SavePrivateKey(const std::string& filename, const CryptoPP::PrivateKey& key)
{
    CryptoPP::ByteQueue queue;
    key.Save(queue);

    CryptoPP::FileSink file(filename.c_str());
    queue.CopyTo(file);
    file.MessageEnd();
}

void Load(const std::string& filename, CryptoPP::BufferedTransformation& bt)
{
	CryptoPP::FileSource file(filename.c_str(), true /*pumpAll*/);

    file.TransferTo(bt);
    bt.MessageEnd();
}

void LoadPublicKey(const std::string& filename, CryptoPP::PublicKey& key)
{
	CryptoPP::ByteQueue queue;
    Load(filename, queue);

    key.Load(queue);
}
void LoadPrivateKey(const std::string& filename, CryptoPP::PrivateKey& key)
{
	CryptoPP::ByteQueue queue;
    Load(filename, queue);

    key.Load(queue);
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

	CryptoPP::AutoSeededRandomPool rnd;

	CryptoPP::RSA::PrivateKey key1, key2;
	key1.GenerateRandomWithKeySize(rnd, 3072);

	SavePrivateKey("rsa-roundtrip.key", key1);
	LoadPrivateKey("rsa-roundtrip.key", key2);

	if(key1.GetModulus() != key2.GetModulus() ||
	   key1.GetPublicExponent() != key2.GetPublicExponent() ||
	   key1.GetPrivateExponent() != key2.GetPrivateExponent())
	{
	    std::cout << "key data did not round trip";
	}

}
