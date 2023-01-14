#pragma once
using namespace std;
#include <string>
string getString(char x);
string GetStringForCharArray(char const* string);
string GetStringFromVoid(const void* value);
bool CompareVoidTypeString(const void* value, const void* valueToCompare);
void SetTheNBitTo1(int* num, int position);
