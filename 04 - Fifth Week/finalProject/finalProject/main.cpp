//
//  main.cpp
//  finalProject
//
//  Created by Anirudh Lath on 9/20/21.
//

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Font.hpp>
#include <math.h>
#include "helper.hpp"
#include <time.h>
#include <iostream>


using namespace std;

int main()
{
    srand((int) time(NULL));
    
    // Create the main program window.
    int windowWidth = 1920;
    int windowHeight = 1080;
    
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Uteroids");
    
    ship theShip(window); // Create a shape to draw
    vector<bullet> bullets; // Create a vector of bullets
    vector<asteroid> asteroids; // Create a vector of asteroids
    int frameCount = 0; // Count frames
    bool game = false; // MainGame start check
    
    // Load the font from a file
    sf::Font MyFont;
    if (!MyFont.loadFromFile("space_invaders.ttf"))
    {
        cout << "Font Error" << endl;
        exit(1);
    }
    
    // Add text to the game screen
    sf::Text Text("Use Arrow Keys to Move\n     Use Space to Shoot\n  Press Enter to Start", MyFont, 50);
    sf::FloatRect textRect = Text.getLocalBounds();
    Text.setOrigin(textRect.left + textRect.width/2.0f,
                   textRect.top  + textRect.height/2.0f);
    Text.setPosition(sf::Vector2f(windowWidth/2.0f, windowHeight/2.0f));
    
    //Scoring
    int Score = 0;
    sf::Text score("Score: " + to_string(Score), MyFont, 20);
    score.setPosition(sf::Vector2f(10, 10));
    




    
    window.setFramerateLimit(60);
    // Run the program as long as the main window is open.
    while (window.isOpen())
    {
        
        frameCount++; // Record frameCount
        window.clear(sf::Color::Black); // Clear the screen
        if(!game){
            window.draw(Text);
            Text.setFillColor(sf::Color::Red);
        }
        
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
        } // Don't start the game until the user hits Enter.
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) and bullets.size() < 10 and frameCount % 3 == 0 and game) {
            bullet theBullet(theShip);
            bullets.push_back(theBullet);
        } // If Space is pressed add a bullet to vector bullets.
        
        if ((rand() % 12 == 0 and game) or asteroids.size() < 7 ) {
            asteroid theAsteroid(window);
            asteroids.push_back(theAsteroid);
        } // Add asteroids randomly.
        
        if (game) {
            
            theShip.interact(window); // Allow user to interact with the ship.
            theShip.draw(window); // Draw the ship.
            
            // Update every asteroid
            for(int i = 0; i < asteroids.size(); i++) {
                asteroids[i].update();
                asteroids[i].draw(window);
            }
            
            // Update every bullet
            for(int i = 0; i < bullets.size(); i++) {
                bullets[i].interact(window);
                bullets[i].draw(window);
                if (!bullets[i].checkCollisionWindow(window)) {
                } else {
                    bullets.erase(bullets.begin() + i); // Remove the bullet when it collides with the edge of the window.
                }
            }
            
            // Check collisions between asteroids and the bullets.
            for(int i = 0; i < bullets.size(); i++) {
                for (int j = 0; j < asteroids.size(); j++) {
                    if (checkCollision(asteroids[j], bullets[i])) {
                        asteroids[j].destructColor(window);
                        
                        bullets.erase(bullets.begin() + i);
                        asteroids.erase(asteroids.begin() + j);
                        Score++;
                        sf::Text temp("Score: " + to_string(Score), MyFont, 20);
                        score = temp;
                        score.setPosition(sf::Vector2f(10, 10));
                        break;
                    }
                }
            }
            
            for (int j = 0; j < asteroids.size(); j++) {
                if(checkCollision(asteroids[j], theShip)) {
                    sf::Text temp("GAME OVER", MyFont, 50);
                    Text = temp;
                    sf::FloatRect textRect = Text.getLocalBounds();
                    Text.setOrigin(textRect.left + textRect.width/2.0f,
                                   textRect.top  + textRect.height/2.0f);
                    Text.setPosition(sf::Vector2f(windowWidth/2.0f, windowHeight/2.0f));
                    game = false;
                }
            }
            window.draw(score);
            score.setFillColor(sf::Color::Red);
        }
        
        
        window.display();
    }
    
    return 0;
}

