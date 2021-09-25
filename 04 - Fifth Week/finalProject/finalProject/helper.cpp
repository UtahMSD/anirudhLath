//
//  helper.cpp
//  finalProject
//
//  Created by Anirudh Lath on 9/24/21.
//

#include "helper.hpp"
#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>

using namespace std;

/// SHIP
ship::ship(sf::RenderWindow & win) {
    // Set the radius and create the shape
    radius = 50.f;
    theShip = sf::CircleShape(radius, 3);

    //Set the color
    red = rand() % 255;
    blue = rand() % 255;
    green = rand() % 255;
    theShip.setFillColor(sf::Color(red, blue, green));
    
    //Set the position
    dx = 25;
    dy = 1;
    x = (win.getSize().x / 2) - 50;
    y = (win.getSize().y - 100);
    xmax = x + (radius * 2.f);
    ymax = y + (radius * 2.f);
    theShip.setPosition(x, y);
} // Constructor


void ship::interact(sf::RenderWindow & win) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        if (x - dx > 10) {
            x -= dx;
            theShip.setPosition(x, y);
        } // Move Left
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        if (x + dx < win.getSize().x - 110) {
            x += dx;
            theShip.setPosition(x, y);
        } // Move Right
    }
    xmax = x + (radius * 2.f);
    ymax = y + (radius * 2.f);
} // User Interaction Logic

void ship::draw(sf::RenderWindow & win) {
    win.draw(theShip);
} // Draw the ship

sf::CircleShape ship::getShape() {
    return theShip;
} // Get the sf::Shape type from class.

/// BULLET

bullet::bullet(const ship & theShip) {
    
    sf::RectangleShape temp(sf::Vector2f(10.f,10.f));
    theBullet = temp;
    
    //Assign Color
    red = rand() % 255;
    blue = rand() % 255;
    green = rand() % 255;
    theBullet.setFillColor(sf::Color(red, blue, green));
    
    //Assign Position
    x = theShip.positionx() + theShip.getRadius() - 5.f;
    y = theShip.positiony() - 10.f;
    xmax = x + 10.f;
    ymax = y + 10.f;
    theBullet.setPosition(x, y);
    dx = 1.f;
    dy = 25.f;
}

void bullet::interact(sf::RenderWindow &win) {
    if (!checkCollisionWindow(win)) {
        y -= dy;
        ymax = y + 10.f;
        theBullet.setPosition(x, y);
    }
} // Move the bullet along the y axis when the user shoots.

void bullet::draw(sf::RenderWindow & win) {
    win.draw(theBullet);
} // Draw the bullets.

sf::RectangleShape bullet::getShape() {
    return theBullet;
} //Return sf::Shape of the bullet.

void bullet::setBulletLocation(const int & xpos, const int & ypos) {
    x = xpos;
    y = ypos;
    theBullet.setPosition(x, y);
} // Set the position in SFML library. Just a shortcut function.

bool bullet::checkCollisionWindow(sf::RenderWindow & win) {
    return (x >= win.getSize().x or
            y >= win.getSize().y or
            x <= 0 or
            y <= 0);
} // Check if the bullet hits the the top of the window.


/// ASTEROID
asteroid::asteroid(sf::RenderWindow & win) {
    // Set the radius and create the asteroid.
    radius = (rand() % (win.getSize().x / 15)) + 70.f;
    theAsteroid = sf::CircleShape(radius, 10.f);
    
    //Assign a color
    red = rand() % 255;
    blue = rand() % 255;
    green = rand() % 255;
    dx = 0;
    dy = rand() % 12;
    theAsteroid.setFillColor(sf::Color(red, blue, green));
    
    //Set the position
    x = (rand() % win.getSize().x ) - radius;
    y = radius * -2.f;
    xmax = x + (radius * 2.f);
    ymax = y + (radius * 2.f);
    theAsteroid.setPosition(x, y);
}


void asteroid::draw(sf::RenderWindow & win) {
    win.draw(theAsteroid);
} // Draw the asteroids.

void asteroid::update() {
    y += dy;
    ymax = y + (radius * 2) ;
    theAsteroid.setPosition(x, y);
} // Move the asteroids down

void asteroid::destructColor(sf::RenderWindow & win) {
    green = 0;
    theAsteroid.setFillColor(sf::Color(red, green, blue));
    draw(win);
    theAsteroid.setFillColor(sf::Color(0, 0, 0));
    
}

bool checkCollision(asteroid &theAsteroid, bullet &theBullet) {
    if (theBullet.y <= theAsteroid.ymax and theBullet.x >= theAsteroid.x and theBullet.x <= theAsteroid.xmax) {
        return true;
    }
    return false;
} // Check collision between the asteroid and the bullet.

bool checkCollision(asteroid &theAsteroid, ship &theShip) {
    if ((theAsteroid.ymax >= theShip.y and theAsteroid.y <= theShip.y) and
        (theAsteroid.x <= theShip.x and theAsteroid.xmax >= theShip.xmax)) {
        return true;
    }
    return false;
} // Check collision between the asteroid and the bullet.


