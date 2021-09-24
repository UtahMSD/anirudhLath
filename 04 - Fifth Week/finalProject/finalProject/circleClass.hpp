//
//  circleClass.hpp
//  finalProject
//
//  Created by Anirudh Lath on 9/20/21.
//

#ifndef circleClass_hpp
#define circleClass_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>

class circle {
    
private:
    sf::CircleShape myCircle; // Circle Object
    float radius; // Radius of that circle
    int red;
    int green;
    int blue;
    
    
public:
    int xPos;
    int yPos;
    
    circle(); // Default Constructor
    circle(float userRadius); // Constructor with radius input
    circle(float userRadius, int r, int g, int b); // Constructor with radius and color
    circle(float userRadius, int x, int y); // Constructor with radius and position
    
    // Member Methods
    void draw(sf::RenderWindow & win); // BUGGED: Draw Method
    void setColor(int r, int g, int b); // Sets a color
    sf::CircleShape getCircle() const { return myCircle; } // Get the circle variable from the class circle.
    void setPosition(int x, int y) { xPos = x; yPos = y; myCircle.setPosition(xPos, yPos); } // Sets position of the circle.
    void addPosition(int x, int y) { myCircle.setPosition(xPos + x, yPos + y); } // Sets position of the circle.
    int getXPosition(int x, int y) { return xPos; } // Sets position of the circle.
    int getYPosition(int x, int y) { return yPos; } // Sets position of the circle.

    
};

class circles { // Partially BUGGED
    
private:
    std::vector<circle> myCircles; // Vector of circles
    int count;
    
public:
    circles(); // Default Constructor
    circles(float radius, int n); // Constructor that allows the user to generate n number of circles of the same radius
    circles(float maxRadius, int n, bool randomOrNot); // Constructor that allows the user to generate n numbers of circles with a random radius between 0 to maxRadius
    
    //Member Methods
    void draw(sf::RenderWindow & win); // Draws all the circles
    circle getCircles(int index){ return myCircles[index]; } // Get the circle variable from the class circle.
    int getCount() const {return count;} // Returns count of the circles.
    void setPosition(int x, int y, int index); // Sets position of each circle.

};

#endif /* circleClass_hpp */
