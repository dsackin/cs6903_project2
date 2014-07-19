#ifndef COMMON_H_
#define COMMON_H_

#include <string>
#include <iostream>

#include <cryptopp/sha.h>
#include <cryptopp/hmac.h>

typedef unsigned char byte;

#define KEY_LENGTH_BYTES (CryptoPP::HMAC<CryptoPP::SHA512>::DIGESTSIZE / 8)

std::string key, filePath, fileName;

/**
 * Test if a file exists and is readable by attempting to open it. Leaves the
 * file closed.
 * @param filePath - string to be attempted as a file path
 * @return bool - true if the path was a file and could be opened.
 */
bool fileExists(std::string filePath) {

	std::filebuf file;
	file.open(filePath, std::ios::in | std::ios::binary);

	bool isOpen = false;

	if (file.is_open()) {
		isOpen = true;
		file.close();
	}

	return isOpen;
}

/**
 * Read a whole file into a string as bytes.
 * @param filePath - string path to the file
 * @return string - contents of file
 */
std::string readFileIntoString(std::string filePath) {
	std::string str;

	std::ifstream file(filePath, std::ifstream::binary);

	if (file) {
		// get length of file:
		file.seekg(0, file.end);
		int length = file.tellg();
		file.seekg(0, file.beg);

		std::string str;
		str.resize(length, ' '); // reserve space
		char* begin = &*str.begin();

		file.read(begin, length);
		file.close();
	}

	return str;
}

/**
 * Process an argument intended as a key. This may be either a path to a file
 * containing a key or the key value itself. If the path is reachable, read the
 * contents of the file and return them as the key. If the path is not
 * reachable, return that value as the key.
 * @param candidate - string that may be key or path to file containing key
 * @return string - value of key
 */
std::string processKey(std::string candidate) {

	// test to see if the value provided on the command line is a path to a file
	if (!fileExists(candidate)) {
		// not a path, so use the value itself
		return candidate;
	}

	return readFileIntoString(candidate);
}

/**
 * Process an argument intended as a filename. This may be either a path to a
 * file containing a filename or the filename itself. If the path is reachable,
 * read the contents of the file and return them as the filename. If the path is
 * not reachable, return that value as the filename.
 * @param candidate - string that may be filename or path to file containing name
 * @return string - value of filename
 */
std::string processFileName(std::string candidate) {

	// test to see if the value provided on the command line is a path to a file
	if (!fileExists(candidate)) {
		// not a path, so use the value itself
		return candidate;
	}

	return readFileIntoString(candidate);
}

/**
 * Process an argument intended as a path to a file. Ensure that it is reachable.
 * @param candidate - string that should be path to data file
 * @return string - path to file or empty string if file not found
 */
std::string processFile(std::string candidate) {

	// test to see if the value provided on the command line is a path to a file
	if (!fileExists(candidate)) {
		// not a path, so return empty string
		return std::string();
	}

	// file existed so return path to it
	return candidate;
}

/**
 * Process arguments passed to the command line of the program. These are passed
 * through directly from main(int argc, char** argv). Parse the options (short
 * options only) using the getopt.h library. Save argument values to global vars
 *
 * @param argc - count of arguments
 * @param argv - array of c-style strings
 * @param printUsage - function to print usage for the command calling the arg
 * processor
 */
void processArguments(int argc, char** argv,
		void (*printUsage)(std::ostream&)) {
	char c;

	while ((c = getopt(argc, argv, "hk:f:n:")) != -1)
		switch (c) {
		case 'h':									// print help
			printUsage(std::cout);
			abort();
		case 'k':
			key = processKey(optarg);
			break;
		case 'f':
			filePath = processFile(optarg);
			break;
		case 'n':
			fileName = processFileName(optarg);
			break;
		case '?':
			if (isprint(optopt))
				fprintf(stderr, "Unknown option `-%c'.\n", optopt);
			else
				fprintf(stderr, "Unknown option character `\\x%x'.\n", optopt);
			break;
		default:
			printUsage(std::cout);
			abort();
		}
}

/**
 * Calculate the HMAC of a buffer of data using HMAC<SHA512>. Result is
 * allocated on heap. Caller responsible for freeing.
 * @param keyData - unsigned char array of 512 (or more) bytes of data to serve
 * as the key for HMAC.
 * @param keySize - unsigned int size of key data
 * @param messageData - unsigned char array of data requiring HMAC.
 * @return unsigned char array of HMAC or NULL if error. Caller responsible for
 * freeing buffer when done.
 */
//bool buildSymmetricKey(byte *symmetricKey, unsigned int symKeyLength,
//		const byte *signingKey, const unsigned int signKeyLength,
//		const byte *messageData, unsigned long msgDataLength) {
//
//	if (symKeyLength < KEY_LENGTH_BYTES)
//		return false;
//
//	CryptoPP::HMAC<CryptoPP::SHA512> hmac(signingKey, signKeyLength);
//	hmac.CalculateDigest(symmetricKey, messageData, msgDataLength);
//
//	return hmac.Verify(symmetricKey);
//}

/**
 * Calculate the HMAC of a buffer of data using HMAC<SHA512> using SHA512 of
 * passphrase as key.
 *
 * Result is allocated on heap. Caller responsible for freeing.
 * @param passphrase - std::string of passphrase. Uses SHA512 hash of passphrase
 * as HMAC key.
 * @param messageData - unsigned char array of data requiring HMAC.
 * @return unsigned char array of HMAC or NULL if error. Caller responsible for
 * freeing buffer when done.
 */
//bool buildSymmetricKey(byte *passphrase, unsigned int phraseLength, const byte *messageData) {
//
//	unsigned char hashOfPhrase[KEY_LENGTH_BYTES];
//
//	CryptoPP::SHA512 sha;
//	sha.CalculateDigest(hashOfPhrase, passphrase, phraseLength);
//
//	if (sha.Verify(hashOfPhrase))
//		return buildSymmetricKey(hashOfPhrase, sizeof(hashOfPhrase), messageData);
//	else
//		return false;
//}

//void SaveSymmetricKey(const std::string& filename, const CryptoPP::PrivateKey& key)
//{
//    CryptoPP::ByteQueue queue;
//    key.Save(queue);
//
//    CryptoPP::FileSink file(filename.c_str());
//    queue.CopyTo(file);
//    file.MessageEnd();
//}
//
//void LoadSymmetricKey(const char &filename, CryptoPP::BufferedTransformation& bt)
//{
//	CryptoPP::FileSource file(filename, true /*pumpAll*/);
//
//    file.TransferTo(bt);
//    bt.MessageEnd();
//}
//
//void LoadPublicKey(const std::string& filename, CryptoPP::PublicKey& key)
//{
//	CryptoPP::ByteQueue queue;
//    Load(filename, queue);
//
//    key.Load(queue);
//}
//void LoadPrivateKey(const std::string& filename, CryptoPP::PrivateKey& key)
//{
//	CryptoPP::ByteQueue queue;
//    Load(filename, queue);
//
//    key.Load(queue);
//}

#endif /* COMMON_H_ */
