#include <iostream>
#include <string>

#pragma warning(disable : 4996)

using namespace std;

void rle_encode(const string& input, string& outputStr);
void rle_decode(const string& input, string& outputStr);

// Bytes!
size_t rle_encode(const char* input, size_t length, char* outputStr, size_t outlen);
size_t rle_decode(const char* input, size_t length, char* outputStr, size_t outlen);


int main(int argc, char* argv[])
{
	size_t streamLength = 22;
	char* inputStream = new char[streamLength];
	//strcpy(inputStream, "aaaaaaabbbbbbbaaaaaaa");
	//strcpy(inputStream, "abcdef");
	strcpy(inputStream, "aaaa");
	inputStream[4] = 5;
	inputStream[5] = '\0';
	strcat(inputStream, "bcdef");

	char* outputStream = new char[streamLength];
	strcpy(outputStream, "");
	size_t inlen = strlen(inputStream);

	rle_encode(inputStream, inlen, outputStream, streamLength);
	
	size_t outlen = 22;
	char* newOutputStream = new char[outlen];
	size_t len = strlen(outputStream);
	size_t neededLen = rle_decode(outputStream, len, newOutputStream, outlen);

	delete [] inputStream;
	delete [] outputStream;
	delete [] newOutputStream;

	return 0;
}

size_t rle_encode(const char* input, size_t length, char* output, size_t outlen)
{
	size_t bufferLen = outlen;
	char* buffer = new char[bufferLen];
	int charCount = 0;
	char prevChar = 0;
	char prevPrevChar = 0;
	char curChar = 0;
	size_t outIndex = 0;

	for (size_t i = 0; i < length; ++i)
	{
		if (input[i] != prevChar && prevChar != 0)
		{
			if (outIndex == outlen)
			{
				size_t oldLen = bufferLen;
				char* temp = new char[oldLen];
				strncpy(temp, buffer, oldLen);
				delete [] buffer;
				bufferLen *= 2;
				buffer = new char[bufferLen];
				strncpy(buffer, temp, oldLen);
				delete [] temp;
			}

			if (charCount == 1) // No compression needed!
			{
				buffer[outIndex++] = prevChar;
			}
			else
			{
				buffer[outIndex++] = prevChar;
				buffer[outIndex++] = prevChar;
				buffer[outIndex++] = charCount - 1;
				charCount = 1; // Count the current char.
			}
		}
		else
		{
			++charCount;
		}

		if (charCount == 255) // 255 is the max... we'll need to start the count over to fit the number in 1 byte.
		{
			buffer[outIndex++] = prevChar;
			buffer[outIndex++] = prevChar;
			buffer[outIndex++] = charCount - 1;
			charCount = 0;
		}

		prevPrevChar = prevChar;
		prevChar = input[i];
	}

	if (charCount != 0)
	{
		if (charCount == 1)
		{
			buffer[outIndex++] = prevChar;
		}
		else
		{
			buffer[outIndex++] = prevPrevChar;
			buffer[outIndex++] = prevPrevChar;
			buffer[outIndex++] = charCount - 1;
		}
	}

	buffer[outIndex++] = '\0';

	if (outlen >= outIndex)
	{
		strncpy(output, buffer, outIndex);
	}

	delete [] buffer;

	return outIndex;
}

size_t rle_decode(const char* input, size_t length, char* output, size_t outlen)
{
	size_t bufferLen = outlen;
	char* buffer = new char[bufferLen];
	size_t outIndex = 0;
	size_t i = 0;

	while (i < length)
	{
		if (i + 1 < length && input[i] == input[i + 1]) // Compressed
		{
			int charCount = input[i + 2];

			for (int j = 0; j <= charCount; ++j) // Account for the extra char
			{
				if (outIndex == bufferLen)
				{
					size_t oldLen = bufferLen;
					char* temp = new char[oldLen];
					strncpy(temp, buffer, oldLen);
					delete [] buffer;
					bufferLen *= 2;
					buffer = new char[bufferLen];
					strncpy(buffer, temp, oldLen);
					delete [] temp;
				}

				buffer[outIndex++] = input[i];
			}

			i += 3;
		}
		else
		{
			buffer[outIndex++] = input[i];
			++i;
		}
	}

	buffer[outIndex++] = '\0';

	if (outlen >= outIndex)
	{
		strncpy(output, buffer, outIndex);
	}

	delete [] buffer;

	return outIndex;
}


// string version
void rle_encode(const string& input, string& outputStr)
{
	string output = "";
	size_t inputSize = input.size();
	output.resize(inputSize);
	int charCount = 0;
	char prevChar = 0;
	char prevPrevChar = 0;
	char curChar = 0;
	size_t outIndex = 0;

	for (size_t i = 0; i < inputSize; ++i)
	{
		if (input[i] != prevChar && prevChar != 0)
		{
			if (charCount == 1) // No compression needed!
			{
				output[outIndex++] = prevChar;
			}
			else
			{
				output[outIndex++] = prevChar;
				output[outIndex++] = prevChar;
				output[outIndex++] = charCount - 1;
				charCount = 1; // Count the current char.
			}
		}
		else
		{
			++charCount;
		}

		prevPrevChar = prevChar;
		prevChar = input[i];
	}

	if (charCount != 0)
	{
		if (charCount == 1)
		{
			output[outIndex++] = prevChar;
		}
		else
		{
			output[outIndex++] = prevPrevChar;
			output[outIndex++] = prevPrevChar;
			output[outIndex++] = charCount - 1;
		}
	}

	outputStr.assign(output.c_str());
}

void rle_decode(const string& input, string& outputStr)
{
	size_t inputSize = input.length();
	size_t maxSize = input.size() * 2;
	string output = "";
	output.resize(maxSize);
	size_t outIndex = 0;
	size_t i = 0;

	while (i <= inputSize)
	{
		if (i + 1 <= inputSize && input[i] == input[i + 1]) // Compressed
		{
			int charCount = input[i + 2];

			for (int j = 0; j <= charCount; ++j) // Account for the extra char
			{
				if (outIndex >= maxSize)
				{
					maxSize *= 2;
					output.resize(maxSize);
				}

				output[outIndex++] = input[i];
			}

			i += 3;
		}
		else
		{
			output[outIndex++] = input[i];
			++i;
		}
	}

	outputStr.assign(output);
}