#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Neural_Network
{
public:
	
	Neural_Network();

	Neural_Network(Neural_Network& parent1_brain, Neural_Network& parent2_brain);

	Vector2f think(Vector2f pos, Vector2f goal_pos, Vector2f dir);

};

