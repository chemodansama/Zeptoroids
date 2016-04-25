/*
 * Game.h
 *
 *  Created on: 10.08.2013
 *      Author: NullPointer
 */

#ifndef GAME_H_
#define GAME_H_

#include <GLES/gl.h>
#include <vector>
#include <list>
#include <memory>

#include "VertexBuffer.h"
#include "AsteroidTemplate.h"
#include "Asteroid.h"
#include "Ui.h"
#include "Spaceship.h"
#include "Bullets.h"
#include "Explosions.h"

namespace zeptoroids {

class Game {
public:
	Game();

	void Render();
	void Resize(int w, int h);

	void HandlePointerDown(int pointerId, float sX, float sY);
	void HandlePointerUp(int pointerId);
	void HandlePointerDone();
private:
	std::vector<GLfloat> vertices;

	int sWidth;
	int sHeight;
	long initTime;
	long lastFrame;

	VertexBuffer buffer;

	int score;
	int lives;
	int wave;

	std::vector<std::unique_ptr<AsteroidTemplate>> templates;
	std::list<std::unique_ptr<Asteroid>> asteroids;

	Ui ui;
	std::unique_ptr<Spaceship> ship;

	Bullets bullets;
	Explosions explosions;

	void SpawnAsteroids(int count);
	void CreateTemplates();

	void Update();
	void Step();
	void Draw();

	void DrawNumber(int num);
	void DrawScore(float w);
	void DrawLives(float w);
	void DrawGameOver(float w);

	void UpdateShip(float w);
	void UpdateBullets(float w);
};

} /* namespace zeptoroids */
#endif /* GAME_H_ */
