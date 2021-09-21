//
//  main.cpp
//  finalProject
//
//  Created by Anirudh Lath on 9/20/21.
//

#include <SFML/Graphics.hpp>
#include <math.h>
#include "circleClass.hpp"
#include <time.h>

int main()
{
    srand((int) time(NULL));
    
    // Create the main program window.
    int windowWidth = 800;
    int windowHeight = 600;
    
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "My window");
    
    // Create a shape to draw
//    sf::CircleShape myCircle(50.f);
//
//    myCircle.setFillColor(sf::Color(100, 250, 50)); // set the shape color to green
    
    circle circle1;
    circles vectorCircles; // Still in development, bugs in it.
    
    float angle = 0.0;
    
    // Run the program as long as the main window is open.
    while (window.isOpen())
    {
        // Check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        
        // clear the window with black color
        window.clear(sf::Color::Black);
        
        int x = 100 + cos( angle ) * 100;
        int y = 100 + sin( angle ) * 100;
        angle += 0.001;
        circle1.setPosition(x, y);
        window.draw(circle1.getCircle());
        //window.draw(circle1.getCircle());
//        vectorCircles.getCircles(1).getCircle().setPosition(x, y);
//        window.draw( vectorCircles.getCircles(1).getCircle());
//        std::cout << vectorCircles.getCircles(1).xPos << ", " << vectorCircles.getCircles(1).yPos << "\n";
//        for(int i = 0; i < vectorCircles.getCount(); i++) {
//            vectorCircles.getCircles(i).setPosition(x, y);
//            window.draw( vectorCircles.getCircles(i).getCircle());
//        }
        
        //vectorCircles.draw(window);
        //window.draw(vectorCircles.getCircle(i))
        // end the current frame
        window.display();
    }
    
    return 0;
}

