#include "pch.h"

#pragma comment(lib,"xinput.lib")

#include <vld.h>
#include "SDL.h"
#include "DigDug.h"

#pragma warning( push )  
#pragma warning( disable : 4100 )  
int main(int argc, char* argv[])
{
#pragma warning( pop )

	DigDug* pGame = new DigDug();
	pGame->Run(dae::GameSettings("DigDug", 224, 288, 2.f, 2.f));
	delete pGame;

	return 0;
}