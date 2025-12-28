#include "Agent.h"
#include "Tools.h"
#include <iostream>

Agent::Agent() 
{
	pos = { 20.f, random(230.f, 1080.f) };
	float angle = random(-90.f, 90.f);
	dir = { cos(angle * PI / 180.f), sin(angle * PI / 180.f) };
	nose.setPrimitiveType(PrimitiveType::Lines);
	nose.resize(2);
	nose[0].position = pos;
	nose[0].color = Color::Green;
	nose[1].position = pos + dir * 15.f;
	nose[1].color = Color::Green;
	dead = false;
	body.setRadius(radius);
	body.setOrigin({ radius, radius });
	body.setPosition(pos);
	body.setFillColor(Color::Green);
	min_dist = INF;
	min_dist_time = 60;
}

Agent::Agent(Neural_Network parent_brain)
{
	pos = { 20.f, random(230.f, 1080.f) };
	float angle = random(-90.f, 90.f);
	dir = { cos(angle * PI / 180.f), sin(angle * PI / 180.f) };
	nose.setPrimitiveType(PrimitiveType::Lines);
	nose.resize(2);
	nose[0].position = pos;
	nose[0].color = Color::Green;
	nose[1].position = pos + dir * 15.f;
	nose[1].color = Color::Green;
	dead = false;
	brain = parent_brain;
	body.setRadius(radius);
	body.setOrigin({ radius, radius });
	body.setPosition(pos);
	body.setFillColor(Color::Green);
	min_dist = INF;
	min_dist_time = 60;
}

Agent::Agent(Agent& parent1, Agent& parent2) 
{
	pos = { 20.f, random(230.f, 1080.f) };
	float angle = random(-90.f, 90.f);
	dir = { cos(angle * PI / 180.f), sin(angle * PI / 180.f) };
	nose.setPrimitiveType(PrimitiveType::Lines);
	nose.resize(2);
	nose[0].position = pos;
	nose[0].color = Color::Green;
	nose[1].position = pos + dir * 15.f;
	nose[1].color = Color::Green;
	dead = false;
	brain = Neural_Network (parent1.brain, parent2.brain);
	body.setRadius(radius);
	body.setOrigin({ radius, radius });
	body.setPosition(pos);
	body.setFillColor(Color::Green);
	min_dist = INF;
	min_dist_time = 60;
}

void Agent::decide(const RectangleShape& goal) 
{
	vector<float> input{ dir.x, dir.y, pos.x, pos.y, goal.getPosition().x, goal.getPosition().y};
	vector<float> output = brain.think(input);
	Vector2f delta_dir = { output[0], output[1] };
	dir = normalize(dir + delta_dir, dir);
}

void Agent::move() 
{
	pos += dir * speed * deltatime;
	if (pos.x - radius < 0 or pos.x + radius > 1920 or 
		pos.y - radius < 230 or pos.y + radius > 1080) 
	{
		dead = true;
	}
	nose[0].position = pos;
	nose[1].position = pos + dir * 15.f;
	body.setPosition(pos);
}

void Agent::adjust_min_dist(const RectangleShape& goal) 
{
	float dist = cur_dist(goal);
	if (dist <= min_dist) 
	{
		min_dist = dist;
		min_dist_time = passedtime.getElapsedTime().asSeconds();
	}

	if (min_dist == 0)
		dead = true;
}

float Agent::cur_dist(const RectangleShape& goal) 
{
	float min_x = goal.getPosition().x - goal.getSize().x / 2,
		  max_x = goal.getPosition().x + goal.getSize().x / 2,
		  min_y = goal.getPosition().y - goal.getSize().y / 2,
		  max_y = goal.getPosition().y + goal.getSize().y / 2;

	Vector2f nearest_point = { clamp(body.getPosition().x, min_x, max_x), clamp(body.getPosition().y, min_y, max_y) };

	return max(0.f, distance(body.getPosition(), nearest_point) - radius);
}

float Agent::get_min_dist() 
{
	return min_dist;
}

Vector2f Agent::get_position() 
{
	return pos;
}

Neural_Network Agent::get_brain()
{
	return brain;
}

float Agent::get_min_dist_time() 
{
	return min_dist_time;
}

void Agent::draw(RenderWindow& window)
{
	window.draw(body);
	window.draw(nose);
}