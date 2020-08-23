#include "stdafx.h"
#include "Console.h"
#include "Application.h"

Console::Console() {
}

Console::~Console() {
	fclose(fp);
	_fcloseall();
}
void Console::OpenConsole() {
	AllocConsole();

	freopen_s(&fp, "CONOUT$", "w", stdout);
	SetConsoleTitle();
}