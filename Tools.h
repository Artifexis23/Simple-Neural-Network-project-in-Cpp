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

extern float PI;
extern float deltatime;
extern float INF;
extern RectangleShape goal;
extern Clock passedtime;

int random(int l, int r);

float distance(Vector2f a, Vector2f b);


