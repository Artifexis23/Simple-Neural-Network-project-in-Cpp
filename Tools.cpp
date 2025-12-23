#include <iostream>
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include <optional>
#include <random>
#include <vector>
#include <cmath>
#include <sstream>
#include <tuple>

using namespace std;
using namespace sf;

float scale = 30.f;

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

Vector2f dirof(Angle angle)
{
    return { cos(angle.asRadians()), sin(angle.asRadians()) };
}

float pix(float meter) 
{
    return meter * scale;
}

float meter(float pix) 
{
    return pix / scale;
}

b2Vec2 abvert(Vector2f vector) 
{
    return { meter(vector.x), meter(vector.y) };
}

Vector2f vert(b2Vec2 vector)
{
    return { pix(vector.x), pix(vector.y) };
}

