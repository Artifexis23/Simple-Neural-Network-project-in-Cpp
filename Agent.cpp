#include "Agent.h"
#include "Tools.h"

Agent::Agent() 
{
	position = { 20.f, (float)random(230, 1080) };
	float angle = (float)random(-90, 90);
	direction = { cos(angle * PI / 180.f), sin(angle * PI / 180.f) };
	nose.setPrimitiveType(PrimitiveType::Lines);
	nose.resize(2);
	nose[0].position = position;
	nose[0].color = Color::Green;
	nose[1].position = position + direction * 15.f;
	nose[1].color = Color::Green;
	finished = false;
	min_dist = 5000;
	body.setRadius(radius);
	body.setOrigin({ radius, radius });
	body.setPosition(position);
	body.setFillColor(Color::Green);
}

Agent::Agent(Agent& parent1, Agent& parent2) 
{
	position = { 20.f, (float)random(230, 1080) };
	float angle = (float)random(-90, 90);
	direction = { cos(angle * PI / 180.f), sin(angle * PI / 180.f) };
	nose.setPrimitiveType(PrimitiveType::Lines);
	nose.resize(2);
	nose[0].position = position;
	nose[0].color = Color::Green;
	nose[1].position = position + direction * 15.f;
	nose[1].color = Color::Green;
	finished = false;
	min_dist = 5000;
	body.setRadius(radius);
	body.setOrigin({ radius, radius });
	body.setPosition(position);
	body.setFillColor(Color::Green);
}

void Agent::draw(RenderWindow& window) 
{
	window.draw(body);
	window.draw(nose);
}

float Agent::get_min_dist() 
{
	return min_dist;
}

Vector2f Agent::get_position() 
{
	return position;
}

bool Agent::did_finish() 
{
	return finished;
}