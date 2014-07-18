#ifndef CLOUDENCRYPTOR_H_
#define CLOUDENCRYPTOR_H_

#include <string>

#include <sha.h>
#include <hex.h>

typedef unsigned char byte;

template <class T> class CloudEncryptor {
public:

	static const unsigned int KEYSIZE = CryptoPP::SHA512::DIGESTSIZE / 8;

	CloudEncryptor() {}
	~CloudEncryptor() {}

	bool GenerateKey(const byte *masterKey, unsigned int masterKeyLength, const std::string plainFileName) {

		CryptoPP::HMAC<CryptoPP::SHA512> hmac(masterKey, KEYSIZE);
		hmac.CalculateDigest(symmetricKey, (byte*)plainFileName.c_str(), plainFileName.size());

		return hmac.Verify(symmetricKey);


		isInitialized = true;
	}

	bool GenerateKey(const std::string passphrase, const std::string plainFileName) {
		byte phraseHash[KEYSIZE];

		CryptoPP::SHA512 hash;
		hash.CalculateDigest(phraseHash, (byte*)passphrase.c_str(), passphrase.size());

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

	static void EncryptFile(const byte *masterKey, std::string plainFilePath, std::string outputPath) {

	}

	static void DecryptFile(std::string keyFilePath, std::string cipherFilePath, std::string outputPath) {

	}

	static void ExportKey(const byte *masterKey, std::string plainFilePath, std::string outputPath) {

	}

private:
	bool isInitialized = false;
	byte symmetricKey[KEYSIZE];





	std::string ExtractPlainName(const byte *data) {

	}

	static std::string GenerateObfuscatedName(const std::string plainFileName) {
		byte nameHash[KEYSIZE];

		CryptoPP::SHA512 hash;
		hash.CalculateDigest(nameHash, (byte*)plainFileName.c_str(), plainFileName.size());

		if (!hash.Verify(nameHash))
			return "";


		std::string cipherFileName =



	}

	static std::string BytesToHexString(const byte* data, const unsigned int dataLength) {
		byte str[2 * dataLength + 1];
		CryptoPP::HexEncoder encoder;
		encoder.Put(data, dataLength);
		encoder.MessageEnd();
		encoder.Get(str, 2 * dataLength);
		str[2 * dataLength] = 0;

		return std::string(str);

	}

	static bool HexStringToBytes(std::string str, byte* data, const unsigned int dataLength) {

		if (dataLength < str.size() / 2)
			return false;

		CryptoPP::HexDecoder decoder;
		decoder.Put((byte*)str.c_str(), str.size());
		decoder.MessageEnd();
		decoder.Get(*data);

		return true;

	}





};



#endif // CLOUDENCRYPTOR_H_
