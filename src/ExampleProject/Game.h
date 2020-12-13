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
		tm.Init(size);
		tm._data[0].velocity.x = 2.0;
		tm._data[0].reserved = true;
		renderer.Init(&tm);
	}

	~Game()
	{
		tm.Clean();
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
	TransformManager tm;
	ConsoleRenderer renderer;

	void Running()
	{
		auto start = std::chrono::system_clock::now();
		auto end = std::chrono::system_clock::now();
		std::chrono::duration<double> deltaTime;
		while (IsRunning())
		{
			end = std::chrono::system_clock::now();
			deltaTime = end - start;
			if (deltaTime.count() >= 0.1)
			{
				start = std::chrono::system_clock::now();
				Update((float)deltaTime.count());
			}
		}
	}

	void Update(float dt)
	{
		tm.Execute(dt);
		renderer.Render();
	}
};

