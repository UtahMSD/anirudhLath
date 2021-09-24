//
//  ship.cpp
//  finalProject
//
//  Created by Anirudh Lath on 9/23/21.
//

#include "ship.hpp"
#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>

ship::ship() {
    theShip = sf::CircleShape(50.f, 3);
    red = rand() % 255;
    blue = rand() % 255;
    green = rand() % 255;
    dx = 25;
    dy = 1;
    theShip.setFillColor(sf::Color(red, blue, green));
}

void ship::initialize(sf::RenderWindow & win) {
    window = &win;
    x = (window -> getSize().x / 2) - 50;
    y = (window -> getSize().y - 100);
    theShip.setPosition(x, y);
    window -> draw(theShip);
}

void ship::interact() {
//    while (window -> pollEvent(event)) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        if (x - dx > 10) {
            x -= dx;
            theShip.setPosition(x, y);
        }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        if (x + dx < window -> getSize().x - 110) {
            x += dx;
            theShip.setPosition(x, y);
        }
    }
//    }
}

void ship::draw() {
    window -> draw(theShip);
}

sf::CircleShape ship::getShape() {
    return theShip;
}

