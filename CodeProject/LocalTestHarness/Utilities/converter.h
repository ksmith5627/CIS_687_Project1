#pragma once

////////////////////////////////////////////////////////////////////////////
// Converter.h - A class exposes some conversion tools as static functions//
// ver 1.0																  //
////////////////////////////////////////////////////////////////////////////

/*
* Package Operations:
* -------------------
* This package contains static functions to convert various 
* data types to string and vice-versa
*
* This is largely based on Prof. Fawcett's example code.
*
*/

#ifndef CONVERTER_H
#define CONVERTER_H

#include <iostream>
#include <objbase.h>
#include <sstream>
#include <vector>

class Convert
{
public:
	template <typename T>
	inline static std::string ToString(T data)
	{
		std::ostringstream oss;
		oss << data;
		return oss.str();
	}

	template <typename T>
	inline static T FromString(std::string string)
	{
		T data;
		std::istringstream ss(string);
		ss >> data;
		return data;
	}	

	inline static std::string GuidToString(GUID& guid)
	{
		std::ostringstream oss;
		oss.width(8);
		oss << std::hex << guid.Data1 << "-";
		oss.width(4);
		oss << std::hex << guid.Data2 << "-";
		oss.width(4);
		oss << std::hex << guid.Data3 << "-";
		oss.width(2);
		oss << std::hex	<< (unsigned int)guid.Data4[0]
			<< std::hex << (unsigned int)guid.Data4[1]
			<< "-"
			<< std::hex << (unsigned int)guid.Data4[2]
			<< std::hex << (unsigned int)guid.Data4[3]
			<< std::hex << (unsigned int)guid.Data4[4]
			<< std::hex << (unsigned int)guid.Data4[5]
			<< std::hex << (unsigned int)guid.Data4[6]
			<< std::hex << (unsigned int)guid.Data4[7];

		return oss.str();
	}

	inline static std::vector<std::string> StringToList(const std::string& source)
	{
		std::vector<std::string> list;
		std::string temp;
		size_t index = 0;
		do
		{
			while ((source[index] == ',' || source[index] == '\n') && index < source.length())
			{
				++index;
				if (temp.size() > 0)
				{
					list.push_back(temp);
					temp.clear();
				}
			}
			if (source[index] != '\0')
				temp += source[index];
		} while (index++ < source.size());
		if (temp.size() > 0)
			list.push_back(temp);
		return list;
	}
};

#endif // !CONVERTER_H