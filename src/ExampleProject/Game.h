#pragma once
#include "TransformManager.h"
#include <mutex>
#include <thread>
#include <iostream>
#include <ctime>

class Game
{
public:
	std::thread gameThread;

	Game(uint32_t size)
	{
		tm = new TransformManager(size);
		tm->data[0].velocity.x = 2.0;
		tm->data[0].reserved = true;
	}

	~Game()
	{
		delete tm;
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
	TransformManager* tm;

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
				Update(deltaTime.count());
				start = std::chrono::system_clock::now();
			}
		}
	}

	void Update(double dt)
	{
		tm->Execute(dt);
		std::cout << tm->data[0].position.ToString(2);
	}
};

