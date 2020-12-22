#pragma once
#include "TransformManager.h"
#include "CameraManager.h"
#include "Entity.h"
#include "SDL2_renderer.h"
#include "Mesh.h"
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

	int Init(uint32_t size)
	{
		srand(time(NULL));
		MakeRendData();
		if (renderer.Init(600, 400) != 0)
			return 1;
		camManager.Init(1);
		camManager.Reserve();
		tManager.Init(size);
		ReserveEntities();
		return 0;
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
	int movingObjects = 2;
	bool running = false;
	float timeSinceStart = 0.0f;
	std::mutex runningMutex;
	TransformManager tManager;
	CameraManager camManager;
	SDL2_renderer renderer;
	Entity* entities;
	RenderingData* cubeRendData;
	RenderingData* pyramidRendData;

	Mesh* cube;
	Mesh* pyramid;

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
		for (uint32_t i = 0; i < tManager._top; ++i)
		{
			tManager.Rotate(i, glm::vec3(1.0f + i % 4, 1.0f + i % 4, 1.0f + i % 4) * dt * 0.2f * (1.0f - 2*(i % 2)));
			float x = glm::cos(timeSinceStart) * 0.1f;
			float y = glm::sin(timeSinceStart) * 0.1f;
			float z = glm::sin(timeSinceStart) * 0.1f;
			tManager.Translate(i, x, y, z);
		}
		tManager.Execute(dt);

		float camPosScale = 50.0f;
		glm::vec3 camPos = glm::vec3(glm::cos(timeSinceStart) * camPosScale, 0.0f, glm::sin(timeSinceStart) * camPosScale);
		camManager.LookAt(0, camPos, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

		renderer.Render(camManager.GetCameraData(0));
	}

	void ReserveEntities()
	{
		int range = 15;
		uint32_t index = tManager.Reserve(true);
		cubeRendData->_modelViewData.push_back(tManager.GetOutData(index));
		index = tManager.Reserve(true);
		pyramidRendData->_modelViewData.push_back(tManager.GetOutData(index));
		//for (int i = 0; i < 1; ++i)
		//{
		//	uint32_t index = tManager.Reserve(true);
		//	cubeRendData->_modelViewData.push_back(tManager.GetOutData(index));
		//}
		for (uint32_t i = 0; i < tManager._top; ++i)
		{
			tManager.SetScale(i, 1.0f);
			tManager.SetPosition(i, rand() % range - range / 2.0f, rand() % range - range / 2.0f, -rand() % range - range / 2.0f);
		}
	}

	void MakeRendData()
	{
		cube = new Mesh();
		cube->_verticesLength = 8;
		cube->_trianglesLength = 12 * 3;
		cube->_vertices = new glm::vec3[]
		{
			glm::vec3(-1.0f, -1.0f, 1.0f),
			glm::vec3(1.0f, -1.0f, 1.0f),
			glm::vec3(1.0f, -1.0f, -1.0f),
			glm::vec3(-1.0f, -1.0f, -1.0f),

			glm::vec3(-1.0f, 1.0f, 1.0f),
			glm::vec3(1.0f, 1.0f, 1.0f),
			glm::vec3(1.0f, 1.0f, -1.0f),
			glm::vec3(-1.0f, 1.0f, -1.0f)
		};
		cube->_triangles = new int[]
		{
			0, 4, 5,
				0, 5, 1,
				1, 5, 6,
				1, 6, 2,
				2, 6, 7,
				2, 7, 3,
				3, 7, 4,
				3, 4, 0,

				4, 7, 6,
				4, 6, 5,
				3, 0, 1,
				3, 1, 2
		};

		pyramid = new Mesh();
		pyramid->_verticesLength = 4;
		pyramid->_trianglesLength = 4 * 3;
		pyramid->_vertices = new glm::vec3[]
		{
			glm::vec3(0.0f, -2.0f, 2.0f),
			glm::vec3(2.0f, -2.0f, -2.0f),
			glm::vec3(-2.0f, -2.0f, -2.0f),
			glm::vec3(0.0f, 2.0f, 0.0f),
		};
		pyramid->_triangles = new int[]
		{
			0, 3, 1,
				1, 3, 2,
				2, 3, 0,
				0, 2, 1
		};

		cubeRendData = renderer.AddRenderingData(*cube, Texture());
		pyramidRendData = renderer.AddRenderingData(*pyramid, Texture());
	}
};

