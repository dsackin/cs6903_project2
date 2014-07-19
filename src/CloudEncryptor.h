#ifndef CLOUDENCRYPTOR_H_
#define CLOUDENCRYPTOR_H_

#include <string>

#include <cryptopp/sha.h>
#include <cryptopp/hex.h>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem.hpp>


using namespace std;
using namespace CryptoPP;
using namespace boost::property_tree;
using namespace boost::filesystem;

typedef unsigned char byte;

template<class T> class CloudEncryptor {
public:

	static const unsigned int KEYSIZE = T::DIGESTSIZE;

	CloudEncryptor() {
	}
	~CloudEncryptor() {
	}

	bool GenerateKey(const byte *masterKey, unsigned int masterKeyLength,
			const string plainFileName) {

		this->plainFileName = plainFileName;
		this->cipherFileNameBase = GenerateObfuscatedBaseName(plainFileName);

		HMAC<T> hmac(masterKey, KEYSIZE);
		hmac.CalculateDigest(symmetricKey, (byte*) plainFileName.c_str(),
				plainFileName.size());

		isInitialized = true;

		return true;

	}

	bool GenerateKey(const string passphrase,
			const string plainFileName) {
		byte phraseHash[KEYSIZE];

		T hash;
		hash.CalculateDigest(phraseHash, (byte*) passphrase.c_str(),
				passphrase.size());

		return GenerateKey(phraseHash, KEYSIZE, plainFileName);
	}

	bool SaveKey(boost::filesystem::path outputPath) {
		//hash
		//name
		//key
		//signature of name+plain file

		if (!isInitialized)
			return false;

		try {
			ptree properties;

			properties.put("KeyedFile", cipherFileNameBase + dataFileExtension);

			string symmetricKeyString = BytesToHexString(symmetricKey, sizeof(symmetricKey));
			properties.put("Key", symmetricKeyString);

//			outputPath.append(cipherFileNameBase + keyFileExtension, codecvt<wchar_t, char, std::mbstate_t>());

			cout << outputPath.native();
			write_json(outputPath.native(), properties);
		} catch (ptree_error e) {
			return false;
		}
		return true;
	}

	bool LoadKey(boost::filesystem::path keyFilePath) {
		 cout << keyFilePath.native() << endl;

//		 if (!exists(keyFilePath))
//			 return false;

		 cout << "ok" << endl;

		 try {
			 ptree properties;
			 read_json(keyFilePath.native(), properties);

			 string keyHexString = properties.get<string>("Key");
			 if (keyHexString.size() / 2 != KEYSIZE)
				 return false;
			 cout << "ok" << endl;

			 HexStringToBytes(keyHexString, symmetricKey, KEYSIZE);
			 cout << "ok" << endl;

			 string keyedFileName = properties.get<string>("KeyedFile");
			 cipherFileNameBase = keyedFileName.substr(0, keyedFileName.find_last_of(dataFileExtension));
			 cout << "ok" << endl;

		 } catch (ptree_error e) {
			 return false;
		 }

		isInitialized = true;

		return true;
	}

	void EncryptFile(string plainFilePath, string outputPath) {

	}

	void DecryptFile(string cipherFilePath, string outputPath) {

	}

	static void EncryptFile(const byte *masterKey, string plainFilePath,
			string outputPath) {

	}

	static void DecryptFile(string keyFilePath, string cipherFilePath,
			string outputPath) {

	}

	static void ExportKey(const byte *masterKey, string plainFilePath,
			string outputPath) {

	}


	static string BytesToHexString(const byte* data,
			const unsigned int dataLength) {
		byte str[2 * dataLength + 1];
		HexEncoder encoder;
		encoder.Put(data, dataLength);
		encoder.MessageEnd();
		encoder.Get(str, 2 * dataLength);
		str[2 * dataLength] = 0;

		return string((char*)str);

	}

	static bool HexStringToBytes(string str, byte* data,
			const unsigned int dataLength) {

		if (dataLength < str.size() / 2)
			return false;

		HexDecoder decoder;
		decoder.Put((byte*) str.c_str(), str.size());
		decoder.MessageEnd();
		decoder.Get(data, str.size() / 2);

		return true;

	}

private:
	bool isInitialized = false;
	byte symmetricKey[KEYSIZE];

	string plainFileName;
	string cipherFileNameBase;

	const string keyFileExtension = ".key.cld";
	const string dataFileExtension = ".data.cld";

	string ExtractPlainName(const byte *data) {
		return string();
	}

	static string GenerateObfuscatedBaseName(const string plainFileName) {
		byte nameHash[KEYSIZE];

		T hash;
		hash.CalculateDigest(nameHash, (byte*) plainFileName.c_str(),
				plainFileName.size());

		string nameHashString = BytesToHexString(nameHash, KEYSIZE);

		cout << nameHashString << endl;

		string cipherFileName = nameHashString.substr(0, 4) + "-"
				+ nameHashString.substr(4, 4) + "-"
				+ nameHashString.substr(nameHashString.size() - 8, 4) + "-"
				+ nameHashString.substr(nameHashString.size() - 4, 4);

		cout << cipherFileName << endl;

		return cipherFileName;
	}



};

#endif // CLOUDENCRYPTOR_H_
