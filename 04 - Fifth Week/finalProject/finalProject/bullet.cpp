//
//  bullet.cpp
//  finalProject
//
//  Created by Anirudh Lath on 9/23/21.
//

#include "bullet.hpp"
#include "ship.hpp"
#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>

bullet::bullet(int xposition, int yposition, sf::RenderWindow & win) {
    sf::RectangleShape temp(sf::Vector2f(10,10));
    theBullet = temp;
    red = rand() % 255;
    blue = rand() % 255;
    green = rand() % 255;
    x = xposition;
    y = yposition;
    theBullet.setPosition(x, y);
    dx = 1;
    dy = 1;
    theBullet.setFillColor(sf::Color(red, blue, green));
    window = &win;
}

//void bullet::initialize(int xposition, int yposition) {
//
//    window -> draw(theBullet);
//}


void bullet::draw() {
    //theBullet.rotate(1.f);
    
    window -> draw(theBullet);
}

sf::RectangleShape bullet::getShape() {
    return theBullet;
}

void bullet::setBulletLocation(const int & xpos, const int & ypos) {
    x = xpos;
    y = ypos;
    theBullet.setPosition(x, y);
}

bool bullet::checkCollisionWindow() {
    return (x >= window -> getSize().x or
            y >= window -> getSize().y or
            x <= 0 or
            y <= 0);
}

void bullet::reinit(int & bulletX, int & bulletY) {
    this -> setBulletLocation(bulletX, bulletY);
}

