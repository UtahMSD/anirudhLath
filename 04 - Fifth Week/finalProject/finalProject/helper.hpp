//
//  helper.hpp
//  finalProject
//
//  Created by Anirudh Lath on 9/24/21.
//

#ifndef helper_hpp
#define helper_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>

class ship {
private:
    sf::CircleShape theShip;
    int radius;
    int red;
    int green;
    int blue;
    int x;
    int y;
    int dx;
    int dy;
    sf::RenderWindow * window;
    
public:
    ship(sf::RenderWindow & win);
    //void initialize(sf::RenderWindow & win);
    void interact(sf::RenderWindow & win);
    void draw(sf::RenderWindow & win);
    sf::CircleShape getShape();
    int positionx() const { return x;}
    int positiony() const { return y;}
    int getRadius() const { return radius;}
    
    
};

class bullet {
private:
    sf::RectangleShape theBullet;
    int red;
    int green;
    int blue;
    int dx;
    int dy;
    bool isShot;
    sf::RenderWindow * window;
    
public:
    int x;
    int y;
    int xmax;
    int ymax;
    
    bullet(ship theShip);
    void interact(sf::RenderWindow & win);
    void draw(sf::RenderWindow & win);
    sf::RectangleShape getShape();
    void setBulletLocation(const int & xpos, const int & ypos);
    bool checkCollisionWindow(sf::RenderWindow & win);
    int xposition() const { return x;}
    int yposition() const { return y;}
    void reinit(ship theShip);
    //~bullet() {delete this;}
    
    
    
};

class asteroid {
private:
    sf::CircleShape theAsteroid;
    int radius;
    int red;
    int green;
    int blue;
    int dx;
    int dy;
    //sf::RenderWindow * window;
    
public:
    int x;
    int xmax;
    int y;
    int ymax;
    
    asteroid(sf::RenderWindow & win);
    void initialize(sf::RenderWindow & win);
    void draw(sf::RenderWindow & win);
    void update();
    bool checkCollision(bullet theBullet, sf::RenderWindow & win);
    void reinit(sf::RenderWindow & win);
    sf::CircleShape getShape() const { return theAsteroid;}
};

bool checkCollision(asteroid &theAsteroid, bullet &theBullet);

#endif /* helper_hpp */
