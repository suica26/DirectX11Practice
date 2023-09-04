#pragma once

class GameSystem
{
public:
	void Initialize();
	void Execute();

private:
	static inline GameSystem* s_instance;
	GameSystem() {}

public:
	static void DeleteInstance()
	{
		if (s_instance != nullptr) {
			delete s_instance;
			s_instance = nullptr;
		}
	}

	static void CreateInstance()
	{
		DeleteInstance();

		s_instance = new GameSystem();
	}

	static GameSystem& GetInstance()
	{
		return *s_instance;
	}
};

#define GAMESYS GameSystem::GetInstance()