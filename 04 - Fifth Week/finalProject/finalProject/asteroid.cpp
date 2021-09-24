//
//  asteroid.cpp
//  finalProject
//
//  Created by Anirudh Lath on 9/23/21.
//

#include "asteroid.hpp"
#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>
#include "bullet.hpp"

asteroid::asteroid() {
    radius = (rand() % 70) + 70;
    theAsteroid = sf::CircleShape(radius, 10);
    red = rand() % 255;
    blue = rand() % 255;
    green = rand() % 255;
    dx = 0;
    dy = rand() % 10;
    theAsteroid.setFillColor(sf::Color(red, blue, green));
}

void asteroid::initialize(sf::RenderWindow & win) {
    window = &win;
    x = (rand() % window -> getSize().x ) - radius;
    y = radius * -2;
    xmax = x + (radius * 2);
    ymax = y + (radius * 2);
    theAsteroid.setPosition(x, y);
}

void asteroid::draw(sf::RenderWindow & win) {

    win.draw(theAsteroid);
}

void asteroid::update() {
    y += dy;
    theAsteroid.setPosition(x, y);
}

bool asteroid::checkCollision(bullet theBullet) {
    if(theBullet.xposition() <= theAsteroid.getPosition().x + (radius * 2) and
       theBullet.xposition() >= theAsteroid.getPosition().x and
       theBullet.yposition() <= theAsteroid.getPosition().y) {
        reinit();
    }
        
    return false;
}

void asteroid::reinit() {
    radius = (rand() % 70) + 70;
    theAsteroid = sf::CircleShape(radius, 10);
    red = rand() % 255;
    blue = rand() % 255;
    green = rand() % 255;
    dy = rand() % 10;
    x = (rand() % window -> getSize().x ) - 50;
    y = radius * -2;
    xmax = x + (radius * 2);
    ymax = y + (radius * 2);
    theAsteroid.setPosition(x, y);
    theAsteroid.setFillColor(sf::Color(red, blue, green));
}
