//
//  main.cpp
//  finalProject
//
//  Created by Anirudh Lath on 9/20/21.
//

#include <SFML/Graphics.hpp>
#include <math.h>
#include "circleClass.hpp"
#include <time.h>
#include "ship.hpp"
#include <iostream>
#include "asteroid.hpp"

using namespace std;

int main()
{
    srand((int) time(NULL));
    
    // Create the main program window.
    int windowWidth = 1920;
    int windowHeight = 1920;
    
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Space Visualizer");
    
    // Create a shape to draw
    ship theShip;
    theShip.initialize(window);
    int bulletX = 0;
    int bulletY = 0;
    
    bulletX = theShip.positionx() + 45;
    bulletY = theShip.positiony();
    asteroid asteroid1;
    asteroid1.initialize(window);
    asteroid asteroid2;
    asteroid2.initialize(window);
    asteroid asteroid3;
    asteroid3.initialize(window);
    asteroid asteroid4;
    asteroid4.initialize(window);
    asteroid asteroid5;
    asteroid5.initialize(window);
    asteroid asteroid6;
    asteroid6.initialize(window);
    bool game = false;


    
    window.setFramerateLimit(60);
    // Run the program as long as the main window is open.
    while (window.isOpen())
    {
        bullet bullets(bulletX, bulletY, window);
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
        
        if (game) {
            
            theShip.interact();
            if (bullets.checkCollisionWindow() or
                asteroid1.checkCollision(bullets, window) or
                asteroid2.checkCollision(bullets, window) or
                asteroid3.checkCollision(bullets, window) or
                asteroid4.checkCollision(bullets, window) or
                asteroid5.checkCollision(bullets, window) or
                asteroid6.checkCollision(bullets, window))
            {
                bulletX = theShip.positionx() + 45;
                bulletY = theShip.positiony();
                bullets.setBulletLocation(bulletX, bulletY);
            } else {
                bulletY -= 25;
                bullets.setBulletLocation(bulletX, bulletY);
            }
            
            // Asteroid Collisions
            if(asteroid1.checkCollision(bullets, window)) {
                asteroid1.reinit(window);
            } else {
                asteroid1.update();
            }
            if(asteroid2.checkCollision(bullets, window)) {
                asteroid2.reinit(window);
            } else {
                asteroid2.update();
            }
            if(asteroid3.checkCollision(bullets, window)) {
                asteroid3.reinit(window);
            } else {
                asteroid3.update();
            }
            if(asteroid4.checkCollision(bullets, window)) {
                asteroid4.reinit(window);
            } else {
                asteroid4.update();
            }
            if(asteroid5.checkCollision(bullets, window)) {
                asteroid5.reinit(window);
            } else {
                asteroid5.update();
            }
            if(asteroid6.checkCollision(bullets, window)) {
                asteroid6.reinit(window);
            } else {
                asteroid6.update();
            }
            
            
            
        }
        
        
        // clear the window with black color
        window.clear(sf::Color::Black);
        theShip.draw();
        bullets.draw();
        asteroid1.draw(window);
        asteroid2.draw(window);
        asteroid3.draw(window);
        asteroid4.draw(window);
        asteroid5.draw(window);
        asteroid6.draw(window);
        window.display();
    }
    
    return 0;
}

