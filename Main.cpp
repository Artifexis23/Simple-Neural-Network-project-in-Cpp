#include <iostream>
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include <cmath>
#include <optional>
#include <sstream>
#include <random>
#include <vector>
#include <map>
#include <set>
#include "Agent.h"
#include "Tools.h"

using namespace std;
using namespace sf;



int main()
{
    RenderWindow window(VideoMode({ 1920, 1080 }), "Alan");
    window.setFramerateLimit(60);
    float deltatime = 1.f / 60.f;
    Clock passedtime;

    RectangleShape goal({ 30.f, 40.f });
    goal.setOrigin({ 15.f, 20.f });
    goal.setPosition({ 1905.f, (float)random(230, 1080) });
    goal.setFillColor(Color::Red);

    //lines
    VertexArray line(PrimitiveType::Lines, 6);
    if (1) 
    {
        line[0].position = { 0, 230 };
        line[0].color = Color::White;
        line[1].position = { 1920, 230 };
        line[1].color = Color::White;
        line[2].position = { 690, 0 };
        line[2].color = Color::White;
        line[3].position = { 690, 230 };
        line[3].color = Color::White;
        line[4].position = { 1240, 0 };
        line[4].color = Color::White;
        line[5].position = { 1240, 230 };
        line[5].color = Color::White;
    }
    
    Font font;
    font.openFromFile("C:\\Users\\ACER\\Documents\\Oyun deneme\\Neural network deneme\\Jet.ttf");
    
    vector<Agent> population(20);

    while (window.isOpen())
    {
        window.clear();
        
        if (60 - passedtime.getElapsedTime().asSeconds() <= 0) 
        {
            vector<pair<float, int>>sorted_fitness;

            for (int i = 0; i < population.size(); i++) 
            {
                float fitness = population[i].get_min_dist();
                sorted_fitness.push_back({ fitness, i });
            }
            sort(sorted_fitness.begin(), sorted_fitness.end());
            reverse(sorted_fitness.begin(), sorted_fitness.end());

            vector<Agent> chance;
            for (int i = 0; i < 20; i++) 
            {
                int number = i + 1;
                while (number--)
                {
                    chance.push_back(population[sorted_fitness[i].second]);
                }
            }

            vector<Agent> next_generation;
            next_generation.push_back(population[sorted_fitness[18].second]);
            next_generation.push_back(population[sorted_fitness[19].second]);

            int needed_children = 18;
            while (needed_children--) 
            {
                Agent child(chance[random(0, 209)], chance[random(0, 209)]);
                next_generation.push_back(child);
            }

            population = next_generation;
        }
        
        while (optional event = window.pollEvent())
        {
            if (event->is<Event::Closed>())
                window.close();


        }

        //time
        if (1) 
        {
            stringstream time;
            time << "00:" << (int)(60 - passedtime.getElapsedTime().asSeconds()) << "\n";
            Text leftime(font, time.str(), 180);
            leftime.setPosition({ 700, 0 });
            leftime.setFillColor(Color::White);
            window.draw(leftime);
        }

        for (int i = 0; i < population.size(); i++) 
        {
            population[i].draw(window);
        }
        window.draw(goal);
        window.draw(line);
        window.display();
    }
}