// Headers
#include <stdlib.h>
#include<iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
using namespace std;

// Defined here to be easily accessed by functions 
sf::Event event;

// Structures

struct PAD
{
	// Width is constant
	const int width = 30;

	// Length will vary
	int length;

	sf::RectangleShape rect;

	sf::Texture texture;

	int velocity;

};


struct BALL
{
	sf::CircleShape circle;
	sf::Texture texture;

	// Set default ball speed
	int xVelocity = -5,
		yVelocity = -5;


};


// Functions

	// takes a key code, returns true if its pressed, false if not
bool isPressed(int button)
{
	if (event.type == sf::Event::KeyPressed && event.key.code == button)
	{
		return true;
	}
	return false;
}




// takes a key code, returns true if its released, false if not
bool isReleased(int button)
{
	if (event.type == sf::Event::KeyReleased && event.key.code == button)
	{
		return true;
	}
	return false;

}

// takes a reference to a BALL, positions it in a random position in the middle
void RandomPos(BALL& ball)
{
	// Random x  300 -> 500
	int x = 300 + rand() % 200;

	// Random y  100 ->300
	int y = 100 + rand() % 200;

	// Random direction
	if (x % 2 == 0)
		ball.xVelocity *= -1;

	ball.circle.setPosition(x, y);
}


// Takes states of buttons and returns a key representing how the pad should move
// 0 = Don't move, 1 = Move up, -1 = Move down
int Get_Movement(bool W, bool S)
{
	// Both or neither keys are pressed
	if ((W && S) || (!W && !S))
	{
		return 0;
	}

	if (W)
	{
		return 1;
	}

	if (S)
	{
		return -1;
	}

	return 0;
}

// Takes a reference to a RectangleShape, prevents it from getting out of bounds
void boundcheck(sf::RectangleShape& rect)
{
	if (rect.getPosition().y < 0)
	{
		rect.setPosition(rect.getPosition().x, 0);
		return;
	}

	if (rect.getPosition().y > 450)
	{
		rect.setPosition(rect.getPosition().x, 450);
	}

}


// Takes a reference to the ball, reverses velocity in the y direction when it hits a wall
// and brings it back to a random position in the middle when out of horizontal bounds
void boundcheck_ball(BALL& ball)
{
	// horizonal bounding
	if (ball.circle.getPosition().x < 40 || ball.circle.getPosition().x > 760)
	{
		RandomPos(ball);
	}

	//vertical bounding
	if (ball.circle.getPosition().y < 0 || ball.circle.getPosition().y > 580)
	{
		ball.yVelocity *= -1;
	}
}


// Takes references to all three components (no idea why references to pads but we might need it) and reverses velocity in the x direction
// if colliding with either of the pads
void isColliding(BALL& ball, PAD& pad1, PAD& pad2)
{
	if (ball.circle.getGlobalBounds().intersects(pad1.rect.getGlobalBounds()) || ball.circle.getGlobalBounds().intersects(pad2.rect.getGlobalBounds()))
	{
		ball.xVelocity *= -1;
	}
}