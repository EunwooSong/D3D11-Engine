#pragma once
#include <io.h>
#include <fcntl.h>

class Console
{

	FILE* fp;

public:
	Console();
	~Console();

	void OpenConsole();
};