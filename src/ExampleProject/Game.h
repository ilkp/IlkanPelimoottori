#pragma once
#include "TransformManager.h"
#include "ConsoleRenderer.h"
#include "Entity.h"
#include <mutex>
#include <thread>
#include <ctime>
#include <iostream>

class Game
{
public:
	std::thread gameThread;

	Game(uint32_t size)
	{
		transformManager.Init(size);
		entity.SetEntityIndex(&transformManager, transformManager.Reserve());
		transformManager.GetEntityData(entity.GetEntityIndex(&transformManager))->_velocity.x = 2.0;
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
	Entity entity;

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

