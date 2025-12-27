#include "Neural_Network.h"
#include "Tools.h"
#include <SFML/Graphics.hpp>

Neural_Network::Neural_Network() 
{
	for (Layer& layer : layers) 
	{
		for (int from = 0; from < layer.weights.size(); from++)
		{
			for (int to = 0; to < layer.weights[from].size(); to++) 
			{
				int prev_nodes = layer.weights.size();
				int nodes = layer.weights[from].size();
				layer.weights[from][to] = random(-xavier(prev_nodes, nodes), xavier(prev_nodes, nodes));
			}
		}
	}
}

Neural_Network::Neural_Network(Neural_Network& parent1_brain, Neural_Network& parent2_brain) 
{
	for (int layer = 0; layer < layers.size(); layer++) 
	{
		for (int from = 0; from < layers[layer].weights.size(); from++) 
		{
			for (int to = 0; to < layers[layer].weights[from].size(); to++) 
			{
				float rand = random(0.f, 1.f);
				layers[layer].weights[from][to] = parent1_brain.layers[layer].weights[from][to] * rand + 
												  parent2_brain.layers[layer].weights[from][to] * (1 - rand);

				if (random(0, 9) == 0)
					layers[layer].weights[from][to] += random(-0.05f, 0.05f);
			}
		}

		for (int node = 0; node < layers[layer].biases.size(); node++) 
		{
			float rand = random(0.f, 1.f);
			layers[layer].biases[node] = parent1_brain.layers[layer].biases[node] * rand + 
										 parent2_brain.layers[layer].biases[node] * (1 - rand);

			if (random(0, 9) == 0)
				layers[layer].biases[node] += random(-0.05f, 0.05f);
		}
	}
}

vector<float> Neural_Network::think(vector<float> input) 
{
	vector<float> output;

	for (Layer layer : layers) 
	{
		output = process_layer(input, layer);
		input = output;
	}
	return output;
}

vector<float> Neural_Network::process_layer(vector<float> input, Layer layer) 
{
	vector<float> value(layer.node_count, 0);

	for (int node = 0; node < layer.node_count; node++)
	{
		for (int prev_node = 0; prev_node < layer.prev_node_count; prev_node++) 
		{
			value[node] += input[prev_node] * layer.weights[prev_node][node];
		}
		value[node] += layer.biases[node];
		value[node] = sigmoid(value[node]);
	}
	return value;
}