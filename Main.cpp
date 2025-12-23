#include <iostream>
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include <cmath>
#include <optional>
#include <random>
#include <vector>
#include "Tool.h"

using namespace std;
using namespace sf;



int main()
{
    RenderWindow window(VideoMode({ 1920, 1080 }), "Alan");
    window.setFramerateLimit(60);
    float deltatime = 1.f / 60.f;


    

    while (window.isOpen())
    {
        window.clear();

        
        while (optional event = window.pollEvent())
        {
            if (event->is<Event::Closed>())
                window.close();


        }

        
        window.display();
    }
}