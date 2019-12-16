#pragma once

/*
Team Members:		Julia Thee, Derek Janzen, Jess Lembke and Kenneth Smith
Course:				CIS 687 -  Object Oriented Design
Assignment:			CIS 687 Homework 4
Instructor:			Professor Scott Roueche

					College of Engineering & Computer Science
					Syracuse University
*/
//////////////////////////////////////////////////////////////////////////////////////////
// File.h - A class that exposes file helper functions such as reading and storing files//
//////////////////////////////////////////////////////////////////////////////////////////

/*
* Package Operations:
* -------------------
* This package contains static functions to fetch the contents
* of a file as a base64 encoded string, or to decode a base64 
* encoded string and then store it to disk.
*
*/

#ifndef FILE_H
#define FILE_H

#include <iostream>
#include <fstream>

#include "Converter.h"

namespace Utilities
{
	const size_t BLOCK_SIZE = 1048576;
	class File
	{
	public:
		inline static size_t GetFileSize(std::string filename)
		{
			std::ifstream file(filename, std::ifstream::ate | std::ifstream::binary);
			if (!file.is_open())
				return 0;
			size_t filesize = (size_t)file.tellg();
			file.close();
			return filesize;
		}

		inline static std::string GetFileContents(std::string filename)
		{
			size_t filesize = GetFileSize(filename);
			if (filesize == 0)
				return "";
			std::ifstream file(filename, std::ios::binary);
			if (!file.good())
				return "";

			char buffer[BLOCK_SIZE];
			file.read(buffer, filesize);
			file.close();
			return Convert::Base64Encode(const_cast<char*>(buffer), filesize);
		}

		inline static bool WriteContentsToFile(std::string filename, std::string encodedContent)
		{
			if (encodedContent.length() == 0)
				return false;
			std::ofstream outstream(filename, std::ios::binary);
			if (!outstream.good())
			{
				return false;
			}

			std::string decodedContent = Convert::Base64Decode(encodedContent);
			outstream.write(decodedContent.c_str(), decodedContent.length());
			outstream.flush();
			outstream.close();
			return true;
		}
	};
}

#endif // !FILE_H