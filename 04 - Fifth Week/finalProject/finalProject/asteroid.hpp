//
//  asteroid.hpp
//  finalProject
//
//  Created by Anirudh Lath on 9/23/21.
//

#ifndef asteroid_hpp
#define asteroid_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>
#include "bullet.hpp"

class asteroid {
private:
    sf::CircleShape theAsteroid;
    int radius;
    int red;
    int green;
    int blue;
    int x;
    int xmax;
    int y;
    int ymax;
    int dx;
    int dy;
    //sf::RenderWindow * window;
    
public:
    asteroid();
    void initialize(sf::RenderWindow & win);
    void draw(sf::RenderWindow & win);
    void update();
    bool checkCollision(bullet theBullet, sf::RenderWindow & win);
    void reinit(sf::RenderWindow & win);
};


#endif /* asteroid_hpp */
