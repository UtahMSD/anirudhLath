//
//  helper.hpp
//  finalProject
//
//  Created by Anirudh Lath on 9/24/21.
//

#ifndef helper_hpp
#define helper_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>

// Refer to header.cpp for detailed comments

class ship {
private:
    sf::CircleShape theShip;
    int radius; // Radius of the ship
    
    // Color values
    int red;
    int green;
    int blue;
    
    
    
    // Velocity
    int dx;
    int dy;
    
public:
    // Positions
    int x;
    int y;
    int xmax;
    int ymax;
    
    ship(sf::RenderWindow & win); // Constructor
    
    // main functions
    void interact(sf::RenderWindow & win);
    void draw(sf::RenderWindow & win);
    
    // Helper functions
    sf::CircleShape getShape();
    int positionx() const { return x;}
    int positiony() const { return y;}
    int getRadius() const { return radius;}
    
    
};

class bullet {
private:
    sf::RectangleShape theBullet; // The shape data
    
    // Color Data
    int red;
    int green;
    int blue;
    
    // Velocity
    int dx;
    int dy;

    
public:
    // Positional Data
    int x;
    int y;
    int xmax;
    int ymax;
    
    bullet(const ship & theShip); // Constructor
    
    //Main functions
    void interact(sf::RenderWindow & win);
    void draw(sf::RenderWindow & win);
    
    // Helper functions
    sf::RectangleShape getShape();
    void setBulletLocation(const int & xpos, const int & ypos);
    bool checkCollisionWindow(sf::RenderWindow & win);
    int xposition() const { return x;}
    int yposition() const { return y;}
};

class asteroid {
private:
    sf::CircleShape theAsteroid; // Shape data
    int radius; // Radius of the asteroid
    
    // Color Data
    int red;
    int green;
    int blue;
    
    // Velocity
    int dx;
    int dy;

public:
    // Public variables to check collisions
    int x;
    int xmax;
    int y;
    int ymax;
    asteroid(sf::RenderWindow & win); // Constructor
    
    // Main functions
    void draw(sf::RenderWindow & win);
    void update();
    void destructColor(sf::RenderWindow & win);
    
    //Helper functions
    sf::CircleShape getShape() const { return theAsteroid;}
};

bool checkCollision(asteroid &theAsteroid, bullet &theBullet); // Check collisions declarations
bool checkCollision(asteroid &theAsteroid, ship &theShip); // Check collisions declarations

#endif /* helper_hpp */
