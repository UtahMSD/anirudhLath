//
//  ship.hpp
//  finalProject
//
//  Created by Anirudh Lath on 9/23/21.
//

#ifndef ship_hpp
#define ship_hpp

#include "bullet.hpp"
#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>

class ship {
private:
    sf::CircleShape theShip;
    int red;
    int green;
    int blue;
    int x;
    int y;
    int dx;
    int dy;
    sf::RenderWindow * window;
    
public:
    ship();
    void initialize(sf::RenderWindow & win);
    void interact();
    void draw();
    sf::CircleShape getShape();
    int positionx() const { return x;}
    int positiony() const { return y;}
    
    
};
#endif /* ship_hpp */
