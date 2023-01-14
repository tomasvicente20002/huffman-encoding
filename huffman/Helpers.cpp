#include "Helpers.h"

/// <summary>
/// Converts a char to string
/// </summary>
/// <param name="x">Char to be converted</param>
/// <returns>Converted string</returns>
string getString(char x)
{
	return string(1,x);
}

/// <summary>
/// Returns a string from a char array
/// </summary>
/// <param name="string">char array</param>
/// <returns>String with the value of the char array</returns>
string GetStringForCharArray(char const* string)
{
	int length = static_cast<int>(strlen(string));
	return std::string(string, string + length);
}

//Converts the void pointer to a string
string GetStringFromVoid(const void* value)
{
	return *static_cast<const std::string*>(value);
}

/// <summary>
/// Compare two string true if they are equal else false
/// </summary>
/// <param name="value">value</param>
/// <param name="valueToCompare">valueToCompare</param>
/// <returns>true if they are equal else false</returns>
bool CompareVoidTypeString(const void* value, const void* valueToCompare)
{
	bool result = GetStringFromVoid(value).compare(GetStringFromVoid(valueToCompare)) == 0;
	return result;
}

/// <summary>
/// Set the n bit to 1
/// </summary>
/// <param name="num">Number to be changed</param>
/// <param name="position">Bit position</param>
void SetTheNBitTo1(int* num, int position)
{
	*num = (1 << position) | *num;
}