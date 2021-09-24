//
//  main.cpp
//  finalProject
//
//  Created by Anirudh Lath on 9/20/21.
//

#include <SFML/Graphics.hpp>
#include <math.h>
#include "helper.hpp"
#include <time.h>
#include <iostream>


using namespace std;

int main()
{
    srand((int) time(NULL));
    
    // Create the main program window.
    int windowWidth = 2000;
    int windowHeight = 1000;
    
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Space Visualizer");
    
    // Create a shape to draw
    ship theShip(window);
    vector<bullet> bullets;
    vector<asteroid> asteroids;
    int frameCount = 0;
    bool game = false;


    
    window.setFramerateLimit(60);
    // Run the program as long as the main window is open.
    while (window.isOpen())
    {
        frameCount++;
        window.clear(sf::Color::Black);
        // Check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
            game = true;
        }
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) and bullets.size() < 10 and frameCount % 3 == 0) {
            bullet theBullet(theShip);
            bullets.push_back(theBullet);
        }
        
        if (rand() % 10 == 0) {
            asteroid theAsteroid(window);
            asteroids.push_back(theAsteroid);
        }
        
        if (game) {
            theShip.interact(window);
            theShip.draw(window);
            for(int i = 0; i < asteroids.size(); i++) {//bullet & b: bullets){
                asteroids[i].update();
                asteroids[i].draw(window);
            }
            for(int i = 0; i < bullets.size(); i++) {
                bullets[i].interact(window);
                bullets[i].draw(window);
                if (!bullets[i].checkCollisionWindow(window)) {
                } else {
                    bullets.erase(bullets.begin() + i);
                }
            }
            
//            for(asteroid i: asteroids) {
//                i.draw(window);
//            }
//            for(bullet i: bullets) {
//                i.draw(window);
//            }
            

            for(int i = 0; i < bullets.size(); i++) {
                for (int j = 0; j < asteroids.size(); j++) {
                    if (checkCollision(asteroids[j], bullets[i])) {
                        bullets.erase(bullets.begin() + i);
                        asteroids.erase(asteroids.begin() + j);
                        break;
                    }
                }
            }
            
                
            
        
        }
        
        window.display();
    }
    
    return 0;
}

