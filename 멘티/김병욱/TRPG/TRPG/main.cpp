#include <iostream>
#include <conio.h>
#include <Windows.h>

using namespace std;

void InputManager()
{
	while (1)
	{
		
		char c;
		c = _getch();
		SceneManager(c);
		
	}
	
}

void SceneManager(char c)
{
	int sceneNum = 0;
	switch (sceneNum)
	{
	case 1:

	}
}

void main()
{
	while (1)
	{
		InputManager();
	}

	return;
}