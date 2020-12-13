#pragma once
#include "TransformManager.h"
#include "ConsoleRenderer.h"
#include <mutex>
#include <thread>
#include <ctime>

class Game
{
public:
	std::thread gameThread;

	Game(uint32_t size)
	{
		transformManager.Init(size);
		uint32_t index = transformManager.Reserve();
		transformManager._entities[index]._data._velocity.x = 2.0;
		transformManager._entities[index]._reserved = true;
		renderer.Init(&transformManager);
	}

	void Start()
	{
		SetRunning(true);
		gameThread = std::thread(&Game::Running, this);
	}

	void SetRunning(bool value)
	{
		const std::lock_guard<std::mutex> guard(runningMutex);
		running = value;
	}

	bool IsRunning()
	{
		const std::lock_guard<std::mutex> guard(runningMutex);
		return running;
	}

private:
	bool running = false;
	std::mutex runningMutex;
	TransformManager transformManager;
	ConsoleRenderer renderer;

	void Running()
	{
		auto start = std::chrono::system_clock::now();
		auto now = std::chrono::system_clock::now();
		std::chrono::duration<float> elapsedTime;
		while (IsRunning())
		{
			now = std::chrono::system_clock::now();
			elapsedTime = now - start;
			if (elapsedTime.count() >= 0.1f)
			{
				start = std::chrono::system_clock::now();
				Update((float)elapsedTime.count());
			}
		}
	}

	void Update(float dt)
	{
		transformManager.Execute(dt);
		renderer.Render();
	}
};

