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
    radius = 50.f;
    theShip = sf::CircleShape(radius, 3);

    red = rand() % 255;
    blue = rand() % 255;
    green = rand() % 255;
    theShip.setFillColor(sf::Color(red, blue, green));
    
    dx = 25;
    dy = 1;
    x = (win.getSize().x / 2) - 50;
    y = (win.getSize().y - 100);
    theShip.setPosition(x, y);
}

//void ship::initialize(sf::RenderWindow & win) {
//    window = &win;
//    x = (window -> getSize().x / 2) - 50;
//    y = (window -> getSize().y - 100);
//    theShip.setPosition(x, y);
//    window -> draw(theShip);
//}

void ship::interact(sf::RenderWindow & win) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        if (x - dx > 10) {
            x -= dx;
            theShip.setPosition(x, y);
        }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        if (x + dx < win.getSize().x - 110) {
            x += dx;
            theShip.setPosition(x, y);
        }
    }
}

void ship::draw(sf::RenderWindow & win) {
    win.draw(theShip);
}

sf::CircleShape ship::getShape() {
    return theShip;
}

/// BULLET

bullet::bullet(ship theShip) {
    sf::RectangleShape temp(sf::Vector2f(10.f,10.f));
    
    theBullet = temp;
    red = rand() % 255;
    blue = rand() % 255;
    green = rand() % 255;
    theBullet.setFillColor(sf::Color(red, blue, green));
    
    x = theShip.positionx() + theShip.getRadius() - 5.f;
    y = theShip.positiony() - 10.f;
    xmax = x + 10.f;
    ymax = y + 10.f;
    theBullet.setPosition(x, y);
    dx = 1.f;
    dy = 25.f;
    
    isShot = false;
}

void bullet::interact(sf::RenderWindow &win) {
    if (!checkCollisionWindow(win)) {
        y -= dy;
        ymax = y + 10.f;
        theBullet.setPosition(x, y);
    }
}

void bullet::draw(sf::RenderWindow & win) {
    win.draw(theBullet);
}

sf::RectangleShape bullet::getShape() {
    return theBullet;
}

void bullet::setBulletLocation(const int & xpos, const int & ypos) {
    x = xpos;
    y = ypos;
    theBullet.setPosition(x, y);
}

bool bullet::checkCollisionWindow(sf::RenderWindow & win) {
    return (x >= win.getSize().x or
            y >= win.getSize().y or
            x <= 0 or
            y <= 0);
}

void bullet::reinit(ship theShip) {
    this -> setBulletLocation(theShip.positionx() + theShip.getRadius(), theShip.positiony() + theShip.getRadius());
}

/// ASTEROID

asteroid::asteroid(sf::RenderWindow & win) {
    radius = (rand() % (win.getSize().x / 15)) + 70.f;
    theAsteroid = sf::CircleShape(radius, 10.f);
    red = rand() % 255;
    blue = rand() % 255;
    green = rand() % 255;
    dx = 0;
    dy = rand() % 12;
    theAsteroid.setFillColor(sf::Color(red, blue, green));
    x = (rand() % win.getSize().x ) - radius;
    y = radius * -2.f;
    xmax = x + (radius * 2.f);
    ymax = y + (radius * 2.f);
    theAsteroid.setPosition(x, y);
}

void asteroid::initialize(sf::RenderWindow & win) {
    //window = &win;
    
}

void asteroid::draw(sf::RenderWindow & win) {

    win.draw(theAsteroid);
}

void asteroid::update() {
    y += dy;
    ymax = y + (radius * 2) ;
    theAsteroid.setPosition(x, y);
}

bool asteroid::checkCollision(bullet theBullet, sf::RenderWindow & win) {
    return (theBullet.xposition() <= theAsteroid.getPosition().x + (radius * 2) and
            theBullet.xposition() >= theAsteroid.getPosition().x and
            theBullet.yposition() <= theAsteroid.getPosition().y) or (theAsteroid.getPosition().x > win.getSize().x or theAsteroid.getPosition().y > win.getSize().y);
}

void asteroid::reinit(sf::RenderWindow & win) {
    radius = (rand() % 70) + 70;
    theAsteroid = sf::CircleShape(radius, 10);
    red = rand() % 255;
    blue = rand() % 255;
    green = rand() % 255;
    dy = rand() % 10;
    x = (rand() % win.getSize().x ) - (radius + 10);
    y = radius * -2;
    xmax = x + (radius * 2);
    ymax = y + (radius * 2);
    theAsteroid.setPosition(x, y);
    theAsteroid.setFillColor(sf::Color(red, blue, green));
}

bool checkCollision(asteroid &theAsteroid, bullet &theBullet) {
    if (theBullet.y <= theAsteroid.ymax and theBullet.x >= theAsteroid.x and theBullet.x <= theAsteroid.xmax) {
        return true;
    }
    return false;
}


