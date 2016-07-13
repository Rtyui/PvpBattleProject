#pragma once
#include "stdincl.h"

bool IsEqual(const char* s1, const char* s2);
Vector2f ParseVector2f(const char* s);
Vector3f ParseVector3f(const char* s);
bool StringStartsWith(const char* prefix, const char* word);
int MaxI(int a, int b);
int MinI(int a, int b);
uint MaxUI(uint a, uint b);
uint MinUI(uint a, uint b);
float MaxF(float a, float b);
float MinF(float a, float b);