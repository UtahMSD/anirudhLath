//
//  circleClass.cpp
//  finalProject
//
//  Created by Anirudh Lath on 9/20/21.
//

#include "circleClass.hpp"
#include <SFML/Graphics.hpp>
#include <math.h>
#include <stdio.h>
#include <iostream>
#include <vector>

using namespace sf;

circle::circle() {
    myCircle = CircleShape(50.f);
    
    radius = 50.f;
    
    red = rand() % 255;
    blue = rand() % 255;
    green = rand() % 255;
    myCircle.setFillColor(sf::Color(red, blue, green));
    
    xPos = 50;
    yPos = 50;
    myCircle.setPosition( xPos, yPos );                     /// CLASS: circle
}                                                           // Default Constructor

circle::circle(float userRadius) {
    myCircle = CircleShape(userRadius);
    radius = userRadius;
    
    red = rand() % 255;
    blue = rand() % 255;
    green = rand() % 255;
    myCircle.setFillColor(sf::Color(red, blue, green));
    
    xPos = 50;
    yPos = 50;
    myCircle.setPosition( xPos, yPos );
}                                                           // Constructor with radius input

circle::circle(float userRadius, int r, int g, int b) {
    myCircle = CircleShape(userRadius);
    radius = userRadius;
    red = r;
    blue = b;
    green = g;
    myCircle.setFillColor(sf::Color(red, blue, green));
    
    xPos = 50;
    yPos = 50;
    myCircle.setPosition( xPos, yPos );
}                                                           // Constructor with radius and color

circle::circle(float userRadius, int x, int y) {
    myCircle = CircleShape(userRadius);
    radius = userRadius;
    
    red = rand() % 255;
    blue = rand() % 255;
    green = rand() % 255;
    myCircle.setFillColor(sf::Color(red, blue, green));
    
    xPos = x;
    yPos = y;
    myCircle.setPosition( xPos, yPos );
    
}                                                           // Constructor with radius and position

void circle::draw(RenderWindow & win) {
    win.draw(myCircle);
}                                                           // Draw Method

void circle::setColor(int r, int g, int b) {
    red = r;
    green = g;
    blue = b;
    myCircle.setFillColor(sf::Color(red, blue, green));
}                                                           // Sets a color

circles::circles() {
    count = 10;
    for (int i = 0; i < count; i++) {
        circle circle1;
        myCircles.push_back(circle1);
    }                                                       /// CLASS: circles
}                                                           // Default Constructor

circles::circles(float radius, int n) {
    count = n;
    for (int i = 0; i < count; i++) {
        circle circle1(radius);
        myCircles.push_back(circle1);
    }
    
}                                                           // Constructor that allows the user to generate n number of circles of the same radius

circles::circles(float maxRadius, int n, bool randomOrNot) {
    count = n;
    for (int i = 0; i < count; i++) {
        circle circle1(rand() % (int) maxRadius);
        myCircles.push_back(circle1);
    }
}                                                           // Constructor that allows the user to generate n numbers of circles with a random radius between 0 to maxRadius

void circles::draw(RenderWindow & win) {
    for(int i = 0; i < count; i++) {
        win.draw(myCircles[i].getCircle());
    }
}                                                           // Draws all the circles

void circles::setPosition(int x, int y, int index) {
    myCircles[index].setPosition(x, y);
}
