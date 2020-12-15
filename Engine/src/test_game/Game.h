#pragma once
#include "TransformManager.h"
#include "Entity.h"
#include "SDL2_renderer.h"
#include <mutex>
#include <thread>
#include <ctime>
#include <iostream>
#include <random>
#include <string>

class Game
{
public:
	std::thread gameThread;

	Game(uint32_t size)
	{
		_randomT = new float[size];
		for (int i = 0; i < size; ++i)
		{
			_randomT[i] = rand() % 100;
		}
		srand(time(NULL));
		int range = 15;
		int zrange = 30;
		tManager.Init(size);
		entities = new Entity[size];
		for (uint32_t i = 0; i < size; ++i)
		{
			entities[i].SetEntityIndex(&tManager, tManager.Reserve());
			tManager.SetScale(i, 0.5f);
			tManager.SetPosition(i, rand() % range - range/2.0f, rand() % range - range / 2.0f, rand() % zrange + 10);
		}
		renderer.Init();
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
	float timeSinceStart = 0.0f;
	std::mutex runningMutex;
	TransformManager tManager;
	SDL2_renderer renderer;
	RendererInData renderInData;
	Entity* entities;

	float* _randomT;

	void Running()
	{
		auto start = std::chrono::system_clock::now();
		auto now = std::chrono::system_clock::now();
		std::chrono::duration<float> elapsedTime;
		while (IsRunning())
		{
			now = std::chrono::system_clock::now();
			elapsedTime = now - start;
			timeSinceStart += elapsedTime.count();
			start = std::chrono::system_clock::now();
			Update((float)elapsedTime.count());
		}
	}

	void Update(float dt)
	{
		for (uint32_t i = 0; i < tManager._size; ++i)
		{
			tManager.Rotate(i, glm::vec3(1.0f + i % 4, 1.0f + i % 4, 1.0f + i % 4) * dt * 0.2f * (1.0f - 2*(i % 2)));
			float x = glm::cos(timeSinceStart) * 0.1f;
			float y = glm::sin(timeSinceStart) * 0.1f;
			float z = glm::sin(timeSinceStart) * 0.2f;
			tManager.Translate(i, x, y, z);
		}
		tManager.Execute(dt);

		renderInData.projectionMatrix = tManager.GetProjectionMatrix();
		renderInData.transformOutData = tManager.GetOutData();
		renderInData.transformOutDataLength = tManager._size;
		renderInData.viewMatrix = tManager.GetViewMatrix();

		renderer.Render(&renderInData);
	}
};

