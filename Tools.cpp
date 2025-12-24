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

random_device rd;
mt19937 gen(rd());

int random(int l, int r)
{
    uniform_int_distribution<> dist(l, r);
    return dist(gen);
}

float distance(Vector2f a, Vector2f b)
{
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

