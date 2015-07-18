/*
 * Global.cpp
 *
 *  Created on: 10 July 2015
 *      Author: Liron Bilya, Yaron Elhadad, Ran Amar
 */

#include "Global.h"

Global::Global() { }

Global::~Global() { }

int Global::angle_to_index(double angle)
{
	return (angle + 120) / 0.36;
}

double Global::index_to_angle(int index)
{
	return (index * 0.36 - 120);
}

string Global::trim(const std::string& str,const std::string& whitespace = " \t")
{
    const unsigned char strBegin = str.find_first_not_of(whitespace);
    if (strBegin == std::string::npos)
        return ""; // no content

    const unsigned char strEnd = str.find_last_not_of(whitespace);
    const unsigned char strRange = strEnd - strBegin + 1;

    return str.substr(strBegin, strRange);
}

int Global::str2int (string str)
{
	int num;
	istringstream ( str ) >> num;

	return num;
}

double Global::str2double (string str)
{
	double num;
	istringstream ( str ) >> num;

	return num;
}

int* Global::getValuesArray(string value)
{
	std::stringstream test(value);
	char delimiter =  ' ';
	string val = "";
	int count = 0;
	int* arr = NULL;
	int* temp = NULL;
	while (getline(test, val, delimiter))
	{
		temp = new int[count+1];
		for (int i=0;i<count;i++)
		{
			temp[i] = arr[i];
		}
		arr = temp;
		arr[count++] = Global::str2int(val);
	}

	return arr;
}

/*
int Global::getRotateDirection(double current, double end)
{
	if ((current + end) > 0)
	{
		return 1; // right rotation
	}

	return -1; // left rotation
}
*/
