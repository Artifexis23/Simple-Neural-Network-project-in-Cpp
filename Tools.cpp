#include <iostream>
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include <optional>
#include <random>
#include <vector>
#include <cmath>
#include <sstream>
#include <tuple>
#include "Tools.h"

using namespace std;
using namespace sf;

float PI = 3.14159265f;
float deltatime = 1.f / 60.f;
float INF = INT_MAX;
Clock passedtime;

random_device rd;
mt19937 gen(rd());

int random(int l, int r)
{
    uniform_int_distribution<> dist(l, r);
    return dist(gen);
}

float random(float l, float r) 
{
    uniform_real_distribution<float> dist(l, r);
    return dist(gen);
}

float distance(Vector2f a, Vector2f b)
{
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

Vector2f normalize(Vector2f vector, Vector2f prev_vector) 
{
    if (vector.x == 0.f and vector.y == 0.f) return prev_vector;
    return vector / sqrt(vector.x * vector.x + vector.y * vector.y);
}

float xavier(int prev_nodes, int nodes) 
{
    return sqrt(6.f) / sqrt((float) (prev_nodes + nodes));
}
