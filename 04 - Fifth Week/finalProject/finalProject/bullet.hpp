//
//  bullet.hpp
//  finalProject
//
//  Created by Anirudh Lath on 9/23/21.
//

#ifndef bullet_hpp
#define bullet_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>
#include "ship.hpp"

class bullet {
private:
    sf::RectangleShape theBullet;
    int red;
    int green;
    int blue;
    int x;
    int y;
    int dx;
    int dy;
    sf::RenderWindow * window;
    
public:
    bullet(int xposition, int yposition, sf::RenderWindow & win);
    void interact();
    void draw();
    sf::RectangleShape getShape();
    void setBulletLocation(const int & xpos, const int & ypos);
    bool checkCollisionWindow();
    int xposition() const { return x;}
    int yposition() const { return y;}
    void reinit(int & bulletX, int & bulletY);
    
    
};

#endif /* bullet_hpp */
