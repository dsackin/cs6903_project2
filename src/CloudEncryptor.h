#ifndef CLOUDENCRYPTOR_H_
#define CLOUDENCRYPTOR_H_

#include <string>

#include <cryptopp/sha.h>
#include <cryptopp/hex.h>

typedef unsigned char byte;

template<class T> class CloudEncryptor {
public:

	static const unsigned int KEYSIZE = T::DIGESTSIZE;

	CloudEncryptor() {
	}
	~CloudEncryptor() {
	}

	bool GenerateKey(const byte *masterKey, unsigned int masterKeyLength,
			const std::string plainFileName) {

		CryptoPP::HMAC<T> hmac(masterKey, KEYSIZE);
		hmac.CalculateDigest(symmetricKey, (byte*) plainFileName.c_str(),
				plainFileName.size());

		isInitialized = true;

		return hmac.Verify(symmetricKey);

	}

	bool GenerateKey(const std::string passphrase,
			const std::string plainFileName) {
		byte phraseHash[KEYSIZE];

		T hash;
		hash.CalculateDigest(phraseHash, (byte*) passphrase.c_str(),
				passphrase.size());

		if (hash.Verify(phraseHash))
			return GenerateKey(phraseHash, KEYSIZE, plainFileName);
		else
			return false;
	}

	void SaveKey(std::string keyFilePath) {

	}

	void LoadKey(std::string keyFilePath) {

		isInitialized = true;
	}

	void EncryptFile(std::string plainFilePath, std::string outputPath) {

	}

	void DecryptFile(std::string cipherFilePath, std::string outputPath) {

	}

	static void EncryptFile(const byte *masterKey, std::string plainFilePath,
			std::string outputPath) {

	}

	static void DecryptFile(std::string keyFilePath, std::string cipherFilePath,
			std::string outputPath) {

	}

	static void ExportKey(const byte *masterKey, std::string plainFilePath,
			std::string outputPath) {

	}


	static std::string BytesToHexString(const byte* data,
			const unsigned int dataLength) {
		byte str[2 * dataLength + 1];
		CryptoPP::HexEncoder encoder;
		encoder.Put(data, dataLength);
		encoder.MessageEnd();
		encoder.Get(str, 2 * dataLength);
		str[2 * dataLength] = 0;

		return std::string((char*)str);

	}

	static bool HexStringToBytes(std::string str, byte* data,
			const unsigned int dataLength) {

		if (dataLength < str.size() / 2)
			return false;

		CryptoPP::HexDecoder decoder;
		decoder.Put((byte*) str.c_str(), str.size());
		decoder.MessageEnd();
		decoder.Get(*data);

		return true;

	}

private:
	bool isInitialized = false;
	byte symmetricKey[KEYSIZE];

	std::string ExtractPlainName(const byte *data) {
		return std::string();
	}

	static std::string GenerateObfuscatedBaseName(const std::string plainFileName) {
		byte nameHash[KEYSIZE];

		T hash;
		hash.CalculateDigest(nameHash, (byte*) plainFileName.c_str(),
				plainFileName.size());

		std::string nameHashString = BytesToHexString(nameHash, KEYSIZE);

		std::cout << nameHashString << std::endl;

		std::string cipherFileName = nameHashString.substr(0, 4) + "-"
				+ nameHashString.substr(4, 4) + "-"
				+ nameHashString.substr(nameHashString.size() - 8, 4) + "-"
				+ nameHashString.substr(nameHashString.size() - 4, 4);

		std::cout << cipherFileName << std::endl;

		return cipherFileName;
	}



};

#endif // CLOUDENCRYPTOR_H_
