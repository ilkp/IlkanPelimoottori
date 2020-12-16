#pragma once
#include "TransformManager.h"
#include "CameraManager.h"
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
		srand(time(NULL));
		int range = 15;
		camManager.Init(1);
		camManager.Reserve();
		tManager.Init(size);
		tManager.Reserve(uint32_t(5));
		for (uint32_t i = 1; i < tManager._top; ++i)
		{
			tManager.SetScale(i, 0.5f);
			tManager.SetPosition(i, rand() % range - range/2.0f, rand() % range - range / 2.0f, -rand() % range -range / 2.0f);
		}
		uint32_t statBoxes = tManager.Reserve(uint32_t(5));
		tManager.SetPosition(statBoxes, glm::vec3(0.0f, 0.0f, 0.0f));
		tManager.SetPosition(statBoxes + 1, glm::vec3(2.0f, 0.0f, 0.0f));
		tManager.SetPosition(statBoxes + 2, glm::vec3(-2.0f, 0.0f, 0.0f));
		tManager.SetPosition(statBoxes + 3, glm::vec3(0.0f, 2.0f, 0.0f));
		tManager.SetPosition(statBoxes + 4, glm::vec3(0.0f, -2.0f, 0.0f));
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
	CameraManager camManager;
	SDL2_renderer renderer;
	RendererInData renderInData;
	Entity* entities;

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
		for (uint32_t i = 1; i < 6; ++i)
		{
			tManager.Rotate(i, glm::vec3(1.0f + i % 4, 1.0f + i % 4, 1.0f + i % 4) * dt * 0.2f * (1.0f - 2*(i % 2)));
			float x = glm::cos(timeSinceStart) * 0.1f;
			float y = glm::sin(timeSinceStart) * 0.1f;
			float z = glm::sin(timeSinceStart) * 0.2f;
			tManager.Translate(i, x, y, z);
		}
		tManager.Execute(dt);

		float camPosScale = 50.0f;
		glm::vec3 camPos = glm::vec3(glm::cos(timeSinceStart) * camPosScale, 0.0f, glm::sin(timeSinceStart) * camPosScale);
		camManager.LookAt(1, camPos, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

		renderInData.transformOutData = tManager.GetOutData();
		renderInData.transformOutDataLength = tManager._top;
		renderInData.cameraData = camManager.GetCameraData(1);

		renderer.Render(&renderInData);
	}
};

