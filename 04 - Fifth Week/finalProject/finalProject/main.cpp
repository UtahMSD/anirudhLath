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
    int windowWidth = 1080;
    int windowHeight = 1920;
    
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "My window");
    
    // Create a shape to draw
    ship theShip;
    theShip.initialize(window);
    int bulletX = 0;
    int bulletY = 0;
    bulletX = theShip.positionx() + 45;
    bulletY = theShip.positiony();
    bullet bullets(bulletX, bulletY, window);
    asteroid asteroid1;
    asteroid1.initialize(window);
    asteroid asteroid2;
    asteroid1.initialize(window);
    asteroid asteroid3;
    asteroid1.initialize(window);
    
    bool game = false;
    
    int frameCount = 0;
    
    window.setFramerateLimit(60);
    // Run the program as long as the main window is open.
    while (window.isOpen())
    {
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
            if (bullets.checkCollisionWindow()) {
                bulletX = theShip.positionx() + 45;
                bulletY = theShip.positiony();
                bullets.setBulletLocation(bulletX, bulletY);
            } else {
                bulletY -= 50;
                bullets.setBulletLocation(bulletX, bulletY);
            }
            if(asteroid1.checkCollision(bullets)) {
                asteroid1.reinit();
            } else {
                asteroid1.update();
            }
            
            
        }
        
        frameCount++;
        if (frameCount > 100) {
            asteroid2.draw(window);
        }
        
        if (frameCount > 300) {
            //asteroid3.draw();
        }
        
        
        
        // clear the window with black color
        window.clear(sf::Color::Black);
        theShip.draw();
        bullets.draw();
        asteroid1.draw(window);
        window.display();
    }
    
    return 0;
}

