#pragma once
struct SceneTitle;

class SceneManager
{
	int SceneNumber = 0;
	SceneTitle title;
	SceneDunGeon dungeon;
	SceneStore store;
	SceneForge forge;
public:

	void SceneInput(char c)
	{ 
		if (c == '0')
		{
			SceneNumber = 0;
		}
		else if (c == '1')
		{
			SceneNumber = 1; 
		}
		else if (c == '2')
		{
			SceneNumber = 2;
		}
		else if (c == '3')
		{
			SceneNumber = 3;
		}
		else
		{
			switch (SceneNumber)
			{
			case 0:// title
				title.GetInput(c);
				break;
			case 1:// dungeon
				dungeon.GetInput(c);
				break;
			case 2:// store
				store.GetInput(c);
				break;
			case 3: // forge
				forge.GetInput(c);
				break;
			}
		}
	}
};

struct SceneTitle
{

	void GetInput(char c)
	{

	}
};

struct SceneDunGeon
{

	void GetInput(char c)
	{

	}
};

struct SceneStore
{

	void GetInput(char c)
	{

	}
};

struct SceneForge
{

	void GetInput(char c)
	{

	}
};

