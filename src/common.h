#ifndef COMMON_H_
#define COMMON_H_

#include <string>
#include <iostream>

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
void processArguments(int argc, char** argv, void(*printUsage)(std::ostream&)) {
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

#endif /* COMMON_H_ */
