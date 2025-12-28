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
    float best_fitness = INF;
    int generation_count = 0;

    RectangleShape goal({ 30.f, 50.f });
    goal.setOrigin({ 15.f, 25.f });
    goal.setPosition({ 1905.f, (float)random(230, 1080) });
    goal.setFillColor(Color::Red);
    Vector2f goal_dir = { 0, -1 };
    float goal_speed = 100.f;

    //lines
    VertexArray line(PrimitiveType::Lines, 6);
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
        
        while (optional event = window.pollEvent())
        {
            if (event->is<Event::Closed>())
                window.close();


        }

        //movement of population
        int dead_count = 0;
        for (Agent& agent : population)
        {
            if (agent.dead)
            {
                dead_count++;
                continue;
            }

            agent.decide(goal);
            agent.move();
            agent.adjust_min_dist(goal);
        }

        //creation of next generation
        if (60 - passedtime.getElapsedTime().asSeconds() <= 0 or dead_count == 20)
        {
            generation_count++;
            vector<pair<float, int>>sorted_fitness;

            for (int i = 0; i < population.size(); i++)
            {
                float fitness = population[i].get_min_dist() + population[i].get_min_dist_time();
                sorted_fitness.push_back({ fitness, i });
            }
            sort(sorted_fitness.begin(), sorted_fitness.end());
            reverse(sorted_fitness.begin(), sorted_fitness.end());
            best_fitness = min(best_fitness, sorted_fitness[19].first);

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
            next_generation.push_back(Agent (population[sorted_fitness[18].second].get_brain()));
            next_generation.push_back(Agent (population[sorted_fitness[19].second].get_brain()));

            int needed_children = 18;
            while (needed_children--)
            {
                Agent child(chance[random(0, 209)], chance[random(0, 209)]);
                next_generation.push_back(child);
            }

            
            population = next_generation;
            passedtime.restart();
        }

        //movement of goal
        {
            if (goal.getPosition().y < 255 or goal.getPosition().y > 1065)
                goal_dir = -goal_dir;

            Vector2f goal_new_pos = goal.getPosition() + goal_speed * goal_dir * deltatime;
            goal.setPosition(goal_new_pos);
        }

        //timer
        {
            stringstream time;
            time << "00:" << (int)(60 - passedtime.getElapsedTime().asSeconds()) << "\n";
            Text leftime(font, time.str(), 180);
            leftime.setPosition({ 700, 0 });
            leftime.setFillColor(Color::White);
            window.draw(leftime);
        }

        //statistics
        {
            stringstream statistics;
            statistics << "Generation: " << generation_count << "\n";
            statistics << "Best fitness: " << best_fitness << "\n";
            Text stats(font, statistics.str(), 24);
            stats.setPosition({ 1250, 10 });
            stats.setFillColor(Color::White);
            window.draw(stats);
        }

        //drawing
        for (Agent agent : population) 
        {
            if (not agent.dead)
                agent.draw(window);
        }
        window.draw(goal);
        window.draw(line);
        window.display();
    }
}