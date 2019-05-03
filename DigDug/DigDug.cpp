#include "pch.h"

#pragma comment(lib,"xinput.lib")

#include <vld.h>
#include "SDL.h"
#include "Minigin.h"


#pragma warning( push )  
#pragma warning( disable : 4100 )  
int main(int argc, char* argv[])
{
#pragma warning( pop )

	dae::Minigin* engine = new dae::Minigin();
	engine->Run();
	delete engine;

	return 0;
}