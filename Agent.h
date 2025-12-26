#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Neural_Network.h"

using namespace std;
using namespace sf;

class Agent
{
private:

	Vector2f pos, dir;
	float min_dist, min_dist_time;
	CircleShape body;
	Neural_Network brain;
	static constexpr float speed = 40.f, radius = 10.f;
	VertexArray nose;
	Clock passed_time;

public:

	bool dead;

	Agent();

	Agent(Agent& parent1, Agent& parent2);

	void decide();

	void move();

	void adjust_min_dist();

	float cur_dist();

	float get_min_dist();

	Vector2f get_position();

	float get_min_dist_time();

	void draw(RenderWindow& window);

};

