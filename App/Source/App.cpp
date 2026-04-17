#include "pchApp.h"
#include "BitEngine.h"

int main()
{
	Engine::BitEngine::Get().Init();
	Engine::BitEngine::Get().Close();
}