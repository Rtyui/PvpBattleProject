#include "Helpers.h"

bool IsEqual(const char* s1, const char* s2)
{
	if (strcmp(s1, s2) == 0)
	{
		return true;
	}
	return false;
}

Vector2f ParseVector2f(const char* s)
{
	Vector2f v;
	char* myString = new char[strlen(s)];
	char* nextToken;
	strcpy_s(myString, _TRUNCATE, s);
	char* first = strtok_s(myString, ",", &nextToken);
	v.x = (float)(atof(first));
	v.y = (float)(atof(nextToken + 1));
	return v;
}

Vector3f ParseVector3f(const char* s)
{
	Vector3f v;
	char* myString = new char[strlen(s)];
	char* nextToken;
	strcpy_s(myString, _TRUNCATE, s);
	char* first = strtok_s(myString, ",", &nextToken);
	v.x = (float)(atof(first));
	v.y = (float)(atof(nextToken + 1));
	char* second = strtok_s(NULL, ",", &nextToken);
	v.z = (float)(atof(nextToken + 1));

	return v;
}

bool StringStartsWith(const char* prefix, const char* word)
{
	return strstr(word, prefix) == word;
}

int MaxI(int a, int b)
{
	return a > b ? a : b;
}

int MinI(int a, int b)
{
	return a < b ? a : b;
}

uint MaxUI(uint a, uint b)
{
	return a > b ? a : b;
}

uint MinUI(uint a, uint b)
{
	return a < b ? a : b;
}

float MaxF(float a, float b)
{
	return a > b ? a : b;
}

float MinF(float a, float b)
{
	return a < b ? a : b;
}