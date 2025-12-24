#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Neural_Network.h"

using namespace std;
using namespace sf;

class Agent
{
public:

	Agent();

	Agent(Agent& parent1, Agent& parent2);

	void draw(RenderWindow& window);

	float get_min_dist();

	Vector2f get_position();

	bool did_finish();

private:

	Vector2f position, direction;
	float min_dist;
	bool finished;
	CircleShape body;
	Neural_Network brain;
	static constexpr float speed = 40.f, radius = 10.f;
	VertexArray nose;

};

