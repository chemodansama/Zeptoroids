/*
 * Game.cpp
 *
 *  Created on: 10.08.2013
 *      Author: NullPointer
 */

#include "Game.h"

#include <cstdlib>
#include <ctime>
#include <math.h>

#include "Utils.h"

namespace {

constexpr float HEIGHT = 10;
constexpr int DEFAULT_LIVES_COUNT = 3;
constexpr int DEFAULT_ASTEROIDS_COUNT = 3;

constexpr float SHIP_SCALE = 0.125f;

const int STEPS_PER_SEC = 50;
const long MILLI_PER_STEP = 1000 / STEPS_PER_SEC;

const std::vector<GLushort> SPACESHIP_INDICES = { 0, 1, 1, 2, 3, 4 };
const std::vector<GLushort> SPACESHIP_FLAME = { 5, 6, 6, 7 };
const std::vector<std::vector<GLushort>> GAMEOVER =
{
    { 18, 19, 19, 16, 16, 14, 14, 20, 20, 22 },
    { 14, 20, 20, 22, 22, 16, 16, 19, 19, 17 },
    { 14, 20, 20, 18, 18, 22, 22, 16 },
    { 22, 20, 20, 17, 17, 19, 19, 17, 17, 14, 14, 16 },
    { 20, 22, 22, 16, 16, 14, 14, 20 },
    { 20, 15, 15, 22 },
    { 22, 20, 20, 17, 17, 19, 19, 17, 17, 14, 14, 16 },
    { 14, 20, 20, 22, 22, 19, 19, 17, 17, 18, 18, 16 }
};

const std::vector<std::vector<GLushort>> NUMBERS =
{
     { 8, 9, 9, 13, 13, 12, 12, 8 },
     { 9, 13 },
     { 9, 8, 8, 10, 10, 11, 11, 13, 13, 12 },
     { 8, 9, 9, 11, 11, 10, 10, 11, 11, 13, 13, 12 },
     { 12, 10, 10, 11, 11, 13, 13, 9 },
     { 13, 12, 12, 10, 10, 11, 11, 9, 9, 8 },
     { 13, 10, 10, 11, 11, 9, 9, 8, 8, 10 },
     { 12, 13, 13, 9 },
     { 12, 13, 13, 9, 9, 8, 8, 12, 12, 10, 10, 11 },
     { 8, 9, 9, 13, 13, 12, 12, 10, 10, 11 },
};

}

namespace zeptoroids {

void Game::SpawnAsteroids(int count) {
	LOGI("Creating asteroids");
	float vlim = HEIGHT / 4 / STEPS_PER_SEC;
	for (int i = 0; i < count; i++) {
		float x = Utils::Randf(-HEIGHT, HEIGHT);
		float y = Utils::Randf(-HEIGHT, HEIGHT);
		float vx = Utils::Randf(-vlim, vlim);
		float vy = Utils::Randf(-vlim, vlim);
		auto t = templates[rand() % templates.size()].get();
		asteroids.emplace_back(new Asteroid(*t, x, y, 0.5f, 2, vx, vy));
	}
	LOGI("Asteroids created");
}

void Game::CreateTemplates() {
	LOGI("Creating templates");
	int index = vertices.size() / 2;
	for (int i = 0; i < 10; i++) {
		float angle = 0;

		std::vector<GLushort> indices;
		std::vector<GLushort> renderIndices;

		vertices.push_back(0);
		vertices.push_back(0);
		indices.push_back(index++);

		for (int j = 0; j < 10; j++) {
			angle += Utils::Randf(36, 72);
			if (angle > 360) {
				break;
			}

			float radius = Utils::Randf(1, 5);
			float radians = angle * M_PI / 180;
			GLfloat x = radius * cos(radians);
			GLfloat y = radius * sin(radians);
			vertices.push_back(x);
			vertices.push_back(y);

			indices.push_back(index);
			renderIndices.push_back(index++);
		}

		templates.emplace_back(
				new AsteroidTemplate(vertices, indices, renderIndices));
	}
	LOGI("Templates created");
}

Game::Game() :
		vertices(
		{
			// A - ship
			4, -6, 0, 6, -4, -6, 3, -3, -3, -3,
			// v - flame
			1, -3, 0, -5, -1, -3,

			0, 0, 1, 0, 0, 1, 1, 1, 0, 2, 1, 2,

			0, 0, 1, 0, 2, 0,
			0, 1, 1, 1, 2, 1,
			0, 3, 1, 3, 2, 3
		}),
		sWidth(480), sHeight(320), initTime(0), lastFrame(-1), score(0),
		lives(DEFAULT_LIVES_COUNT), wave(0),
		ship(new Spaceship(vertices, SPACESHIP_INDICES,
				SPACESHIP_FLAME, SHIP_SCALE)),
		explosions(STEPS_PER_SEC),
		bullets() {
	initTime = zeptoroids::Utils::GetTime();
	srand(time(0));

	CreateTemplates();
	SpawnAsteroids(DEFAULT_ASTEROIDS_COUNT);
	glClearColor(1, 0, 0, 1);

	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glDisable(GL_LIGHTING);
	glDisable(GL_BLEND);

	glEnableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_ELEMENT_ARRAY_BUFFER);

	buffer.Init(GL_ARRAY_BUFFER, vertices);
}

void Game::Update() {
	if (lastFrame == -1) {
		lastFrame = Utils::GetTime();
		return;
	}

	long t = Utils::GetTime();
	while (t - lastFrame > MILLI_PER_STEP) {
		Step();
		lastFrame += MILLI_PER_STEP;
	}
}

void Game::UpdateShip(float w) {
    if (!ship) {
        return;
    }

    ship->Update(STEPS_PER_SEC, w, HEIGHT);

    if (ship->HasInvulnerability()) {
        return;
    }

    bool hasCollision = false;
    for (auto &asteroid : asteroids) {
        if (ship->HasCollision(asteroid.get())) {
            hasCollision = true;
        }
    }

    if (hasCollision) {
        ship.reset();
        lives--;

        if (lives >= 0) {
            ship.reset(new Spaceship(vertices, SPACESHIP_INDICES, SPACESHIP_FLAME, SHIP_SCALE));
            if (ui.IsAccel()) {
                ship->Forward();
            }
            if (ui.IsLeft()) {
                ship->TurnLeft();
            }
            if (ui.IsRight()) {
                ship->TurnRight();
            }
        } else {
            wave = 0;
        }
    }
}

void Game::UpdateBullets(float w) {

    bullets.Update(w, HEIGHT);

    for (const auto &bullet : bullets) {
        bool collided = false;
        for (auto it = asteroids.begin(); it != asteroids.end();) {
            const auto &a = *it;
            auto bx = bullet->GetX();
            auto by = bullet->GetY();
            if (a->IsInside(bx, by)) {
                explosions.AddExplosion(bx, by);

                score += a->GetScore();

                for (int i = 0; i < 2; i++) {
                    auto t = templates[rand() % templates.size()].get();
                    if (auto part = a->Spawn(*t)) {
                        asteroids.push_back(std::move(part));
                    }
                }

                it = asteroids.erase(it);
                collided = true;
                break;
            } else {
                ++it;
            }
        }

        if (collided) {
            bullets.Remove(bullet.get());
        }
    }
}

void Game::Step() {
	float w = HEIGHT * sWidth / sHeight;

	for (auto &a : asteroids) {
	    a->Update(w, HEIGHT);
	}

	UpdateShip(w);

	if (asteroids.empty()) {
		wave++;
		SpawnAsteroids(DEFAULT_ASTEROIDS_COUNT + wave);
	}

	UpdateBullets(w);

	explosions.Update();
}

void Game::HandlePointerDown(int pointerId, float sX, float sY) {
	if (ship) {
		switch (ui.HandlePointerDown(pointerId, sX, sHeight - sY)) {
		case TURN_LEFT:
			ship->TurnLeft();
			break;
		case TURN_RIGHT:
			ship->TurnRight();
			break;
		case FORWARD:
			ship->Forward();
			break;
		case SHOOT:
			bullets.Add(ship->GetX(), ship->GetY(), ship->GetAngle(), STEPS_PER_SEC);
			break;
		}
	} else {
		ship.reset(new Spaceship(vertices, SPACESHIP_INDICES, SPACESHIP_FLAME, SHIP_SCALE));
		score = 0;
		lives = DEFAULT_LIVES_COUNT;
		asteroids.clear();

		SpawnAsteroids(DEFAULT_ASTEROIDS_COUNT);
	}
}

void Game::HandlePointerUp(int pointerId) {
	if (ship) {
		switch (ui.HandlePointerUp(pointerId)){
		case TURN_LEFT_DONE:
			ship->TurnStopLeft();
			break;
		case TURN_RIGHT_DONE:
			ship->TurnStopRight();
			break;
		case FORWARD_DONE:
			ship->Stop();
			break;
		}
	}
}

void Game::HandlePointerDone() {
	ui.HandlePointerDone();
	if (ship) {
		ship->TurnStopLeft();
		ship->TurnStopRight();
		ship->Stop();
	}
}

void Game::DrawScore(float w) {
	int s = score;
	glPushMatrix();
	glTranslatef(w - 1, HEIGHT - 1, 0);
	int i = 0;
	while (s > 0 || i == 0) {
		glPushMatrix();
		glTranslatef(-0.5f * i, 0, 0);
		glScalef(0.25f, 0.25f, 1);
		DrawNumber(s % 10);
		glPopMatrix();
		s /= 10;
		i++;
	}
	glPopMatrix();
}

void Game::DrawLives(float w) {
	glPushMatrix();
	glTranslatef(w - 1, HEIGHT - 2, 0);
	glScalef(SHIP_SCALE, SHIP_SCALE, 1);
	for (int i = 0; i < lives; i++) {
		glDrawElements(GL_LINES, SPACESHIP_INDICES.size(), GL_UNSIGNED_SHORT, &SPACESHIP_INDICES[0]);
		glTranslatef(-10, 0, 0);
	}
	glPopMatrix();
}

void Game::DrawGameOver(float w) {
	if (ship) {
		return;
	}

	glPushMatrix();
	glTranslatef(w / 2, 0, 0);
	glTranslatef(-12, 0, 0);
	glScalef(0.25f, 0.25f, 1);
	for (int i = 0; i < GAMEOVER.size(); i++) {
		glDrawElements(GL_LINES, GAMEOVER[i].size(), GL_UNSIGNED_SHORT, &GAMEOVER[i][0]);
		glTranslatef(3, 0, 0);
	}
	glPopMatrix();
}

void Game::Draw() {
	glViewport(0, 0, sWidth, sHeight);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	float w = HEIGHT * sWidth / sHeight;
	glOrthof(-w, w, -HEIGHT, HEIGHT, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glColor4f(1, 1, 1, 1);

	//=====

	VertexBuffer::Unbind(GL_ARRAY_BUFFER);
	bullets.Draw();
	explosions.Draw();

	buffer.Bind(GL_ARRAY_BUFFER);
	glVertexPointer(2, GL_FLOAT, 0, 0);

	for (const auto &a : asteroids) {
		a->Render(w, HEIGHT);
	}

	if (ship) {
		ship->Draw(w, HEIGHT);
	}

	DrawScore(w);
	DrawLives(w);
	DrawGameOver(w);
	ui.Draw();
}

void Game::Render() {
	Update();
	Draw();
}

void Game::Resize(int w, int h) {
	sWidth = w;
	sHeight = h;
	ui.Resize(w, h);
}

void Game::DrawNumber(int num) {
	glDrawElements(GL_LINES, NUMBERS[num].size(), GL_UNSIGNED_SHORT, &NUMBERS[num][0]);
}

} /* namespace zeptoroids */
