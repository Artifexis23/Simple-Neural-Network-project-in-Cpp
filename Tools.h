#pragma once
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

extern float scale;

int random(int l, int r);

float distance(Vector2f a, Vector2f b);

Vector2f dirof(Angle angle);

float pix(float meter);

float meter(float pix);

b2Vec2 abvert(Vector2f vector);

Vector2f vert(b2Vec2 vector);

