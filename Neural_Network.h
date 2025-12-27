#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Neural_Network
{
private:

	struct Layer
	{
		int node_count;
		int prev_node_count;
		vector<float> biases;
		vector<vector<float>> weights;

		Layer(int prev_nodes, int nodes)
		{
			node_count = nodes;
			prev_node_count = prev_nodes;
			biases = vector<float>(node_count, 0);
			weights = vector<vector<float>>(prev_node_count, vector<float>(node_count));
		}
	};

	vector<Layer>layers{ {6, 8}, {8, 2} };

public:
	
	Neural_Network();

	Neural_Network(Neural_Network& parent1_brain, Neural_Network& parent2_brain);

	vector<float> think(vector<float> input);

	vector<float> process_layer(vector<float> input, Layer layer);

};

