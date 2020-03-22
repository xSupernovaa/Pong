// Header containing custom functions, includes, structs definitons, and the Event object
#include "functions.h"
#include "leaderboard.h"
#include "Menu.h"
#include "volumemenu.h"
#include "thememenu.h"
#include "pauseMenu.h"
#include <sstream>

using namespace sf;
int main(void)
{
	bool themePlaying = true;

	//MODE(t for training, 2 for 2 player , a for ai)
	char MODE ;

	// THEMES //

	bool hell = false, ice = false, forest = false; //still no use but could be helpful when switching ingame
	char c = 'h'; //indicate theme
	Texture backgT; //background
	RectangleShape backg; 
	backg.setSize(Vector2f(800.0, 600.0));
	
	// Sounds

	// Set to true/false to activate or mute
	
	bool sfxSwitch = true;
	bool musicSwitch = true;

	//sounds of main menu 

	// Theme music
	Music theme;
	theme.openFromFile("resources/sfx/main_menu/theme.ogg");
	theme.setLoop(true);
	if (musicSwitch)
	{
		theme.play();
	}

	//sound of when you press enter.....
	SoundBuffer whenpressed;
	whenpressed.loadFromFile("resources/sfx/main_menu/choose_button.wav");
	Sound whenpressed_detector;
	whenpressed_detector.setBuffer(whenpressed);

	//when return sound....(when you press backspace)
	SoundBuffer whenreturn;
	whenreturn.loadFromFile("resources/sfx/main_menu/switch.wav");
	Sound whenreturn_detector;
	whenreturn_detector.setBuffer(whenreturn);




	// Ball sounds

	// Score
	SoundBuffer scor;
	Sound score_sound;
	score_sound.setBuffer(scor);

	// Wall hit
	SoundBuffer wall;
	Sound wall_hit;
	wall_hit.setBuffer(wall);

	// Pad hit
	SoundBuffer pad;
	Sound pad_hit;
	pad_hit.setBuffer(pad);


	// Background
	SoundBuffer background_bfr;
	Sound background;
	background.setBuffer(background_bfr);
	background.setLoop(true);


	// Powerups

	// Elongate
	SoundBuffer Elon_bfr;
	Elon_bfr.loadFromFile("resources/sfx/powerups/elongate.wav");
	Sound elongate_sound;
	elongate_sound.setBuffer(Elon_bfr);

	// Freeze
	SoundBuffer frz_bfr;
	frz_bfr.loadFromFile("resources/sfx/powerups/freeze.wav");
	Sound freeze_sound;
	freeze_sound.setBuffer(frz_bfr);

	// Slow
	SoundBuffer slow_bfr;
	slow_bfr.loadFromFile("resources/sfx/powerups/slow.wav");
	Sound slow_sound;
	slow_sound.setBuffer(slow_bfr);

	// Dissapear
	SoundBuffer dspr_bfr;
	dspr_bfr.loadFromFile("resources/sfx/powerups/dissapear.wav");
	Sound dissapear_sound;
	dissapear_sound.setBuffer(dspr_bfr);






	// Create the main window 
	RenderWindow window(VideoMode(GAMEWIDTH, GAMEHEIGHT), "Pong");

	// Limit FPS to 60
	window.setFramerateLimit(60);


	// Game loop bool
	bool play = false;


	//option selection 
	bool opt = false;
	//option font 
	Font font;
	if (!font.loadFromFile("resources/fonts/Pacifico.ttf"))
		return EXIT_FAILURE;

	//option message 
	Text option;
	option.setFont(font);
	option.setCharacterSize(40);
	option.setPosition(200.f, 425.f);
	option.setFillColor(Color::White);
	option.setString("Press Backspace to return");


	// Pads
	PAD pad1;
	// Set length of pad
	pad1.length = 125;

	// Create the rectangle shape with given length and width
	pad1.rect.setSize(Vector2f(pad1.width, pad1.length));
	// Set the orgin
	pad1.rect.setOrigin(pad1.width / 2.f, pad1.length / 2.f);
	// Set the position
	pad1.rect.setPosition(pad1.width + /*the needed distance*/ 30, 400);
	// texture
	//pad1.texture.loadFromFile("resources/test.png");
	//pad1.rect.setTexture(&pad1.texture);

	PAD pad2;
	// Set length of pad
	pad2.length = 125;

	// Create the rectangle shape with given length and width
	pad2.rect.setSize(Vector2f(pad2.width, pad2.length));
	// Set the orgin
	pad2.rect.setOrigin(pad2.width / 2.f, pad2.length / 2.f);
	// Set the position
	pad2.rect.setPosition(GAMEWIDTH - pad2.width -  /*the needed distance*/ 30, 350);

	// Ball
	BALL ball;

	// Set radius
	ball.circle.setRadius(ballRadius);

	// Set the positon and orgin
	ball.circle.setPosition(400, 300);
	ball.circle.setOrigin(ballRadius, ballRadius);


	//////powerUps///////

		//longate

	pUp longate; //struct containing powerup attributes
	Clock longC; //clock decleration to work a timer later for how long the powerup stays
	longate.isSpawned = false;
	longate.isActive = false;
	longate.circle.setFillColor(Color::Red); //pUp color
	longate.circle.setRadius(10); //pUp size


//freeze 

	pUp freeze;
	Clock freezeC;
	freeze.isSpawned = false;
	freeze.isActive = false;
	freeze.circle.setFillColor(Color::Blue); //pUp color
	freeze.circle.setRadius(10); //pUp size	

//slow

	pUp slow;
	Clock slowC;
	slow.isSpawned = false;
	slow.isActive = false;
	slow.circle.setFillColor(Color::Green); //pUp color
	slow.circle.setRadius(10); //pUp size

//Invisibility

	pUp invis;
	Clock invisC;
	invis.isSpawned = false;
	invis.isActive = false;
	invis.circle.setFillColor(Color::Magenta); //pUp color
	invis.circle.setRadius(10); //pUp size

	bool frozen1 = 0, frozen2 = 0, slow1 = 0, slow2 = 0, invis1 = 0, invis2 = 0;  //could be changed later



	// States
	//font of score 
	sf::Font scorefont;
	scorefont.loadFromFile("resources/fonts/Pacifico.ttf");

	// score of player 1  // 3dad score 1 
	float scorep1 = 0;
	std::ostringstream ssScorep1;
	ssScorep1 << scorep1;
	sf::Text lblscorep1;
	lblscorep1.setCharacterSize(30);
	lblscorep1.setPosition(290, 5);
	lblscorep1.setFont(scorefont);
	lblscorep1.setCharacterSize(50);
	lblscorep1.setFillColor(sf::Color::White);
	lblscorep1.setString(ssScorep1.str());


	float scorep2 = 0;
	std::ostringstream ssScorep2;
	ssScorep2 << scorep2;
	//label of score of player 2 
	sf::Text lblscorep2;
	lblscorep2.setCharacterSize(30);
	lblscorep2.setPosition(440, 5);
	lblscorep2.setFont(scorefont);
	lblscorep2.setCharacterSize(50);
	lblscorep2.setFillColor(sf::Color::White);
	lblscorep2.setString(ssScorep1.str());




	// States

		// Keyboard buttons  
	bool W = false, S = false;
	bool Up = false, Down = false;


	// main menu 
	Menu menu(window.getSize().x, window.getSize().y);
	bool men = true;
	//lvl of volume in game 
	volumemenu Level_of_volume(window.getSize().x, window.getSize().y);
	//theme changer/////////
    thememenu change_the_theme(window.getSize().x, window.getSize().y);

	//pause menu
	bool pause = false;
	pauseMenu pMenu(window.getSize().x, window.getSize().y);


	//losing/wining message 
	//lw_font 
	Font lw_font;
	lw_font.loadFromFile("resources/fonts/Youmurdererbb-pwoK.otf");
	//p1 winning message 
	Text p1win;
	p1win.setCharacterSize(100);
	p1win.setPosition(GAMEWIDTH / 2 - 125, GAMEHEIGHT / 2 - 100);
	p1win.setFillColor(sf::Color::White);
	p1win.setString("p1..Wins");
	p1win.setFont(lw_font);
	//p2 wining message 
	Text p2win;
	p2win.setCharacterSize(100);
	p2win.setPosition(GAMEWIDTH / 2 - 125, GAMEHEIGHT / 2 - 100);
	p2win.setFillColor(sf::Color::White);
	p2win.setString("p2..Wins");
	p2win.setFont(lw_font);
	//in losing/wining bools 
	bool p1win_detector = 0;
	bool p2win_detector = 0;

	//////////Player Info and Leaderboard///////////
	sf::Text playerText;
	bool getPlayerName = false;
	string playerName;
	string playerUser1;
	playerText.setFont(font);
	playerText.setCharacterSize(40);
	playerText.setPosition(200.f, 425.f);
	playerText.setFillColor(Color::White);
	sf::Text messagePlayerText;
	messagePlayerText.setFont(font);
	messagePlayerText.setCharacterSize(40);
	messagePlayerText.setPosition(100.f, 100.f);
	messagePlayerText.setFillColor(Color::White);
	messagePlayerText.setString("Please enter thy name!");
	bool leader = false;


	////theme test
	set_theme(pad1, pad2, ball, backgT, backg, pad, wall, scor, background_bfr, c);




	////////////////////////////////////////////////// GAME LOOP ///////////////////////////////////////////////////////////////////////////
	
	// Variable used to determine wether the user's Enter press in options is to change themes or to change volume
	// '0' means nothing happend yet
	// 'v' means enter should change volume
	// 't' means enter should change theme
	char Indecator = '0';

	while (window.isOpen())
	{

		// EVENTS
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed || isPressed(Keyboard::Escape))
			{
				play = false;
				window.close();
				return 0;
			}

			//pause menu events
			if (pause)
			{
				if (event.type == Event::KeyReleased)
				{
					switch (event.key.code)
					{
						case Keyboard::Up:
							pMenu.moveUp();
							whenreturn_detector.play();
							break;

						case Keyboard::Down:
							pMenu.moveDown();
							whenreturn_detector.play();
							break;

						case Keyboard::Return:
							switch (pMenu.getPresseditem())
							{
								//resume
							case 0:
								if (pause)
								{
									pause = false;
									whenpressed_detector.play();
									break;
								}
								//open option menu
							case 1:
								opt = true;
								pause = false;
								whenpressed_detector.play();
								break;
								//exit
							case 2:
								whenpressed_detector.play();
								getPlayerName = false;
								play = false;
								pause = false;
								men = true;
								if (musicSwitch)
								{
									background.stop();
									theme.play();

								}
								break;
							}
					
						break;
					}
					break;
					
				}
			}
	

			/////volume changer ///////
			////volume change event //////////
			if (opt) {
				
				if (event.type == Event::KeyReleased) {
					switch (event.key.code)
					{
					case Keyboard::Right:
						Level_of_volume.MoveRight();
						Indecator = 'v';
						break;

					case Keyboard::Left:
						Level_of_volume.MoveLeft();
						Indecator = 'v';
						break;
					case Keyboard::A :
						change_the_theme.Move_A(); ///move to left using A key //////////// 
						Indecator = 't';
						break;
					case Keyboard::D:
						change_the_theme.Move_D();////move to right using D key ///////////////
						Indecator = 't';
						break;

					case sf::Keyboard::Return:

						///volume changer /////////
						if (Indecator == 'v')	// See line 323 for explaination
						{
							switch (Level_of_volume.GetVolumechange())
							{
							case 0:
								theme.setVolume(0);
								background.setVolume(0);

								break;
							case 1:
								theme.setVolume(25);
								background.setVolume(25);

								break;

							case 2:
								theme.setVolume(50);
								background.setVolume(50);
								break;

							case 3:
								theme.setVolume(75);
								background.setVolume(75);

								break;

							case 4:
								theme.setVolume(100);
								background.setVolume(100);
								break;
							}

						}

						// theme changer
						
						if (Indecator == 't') // See line 323 for explaination
						{
							switch (change_the_theme.GetThemechange())
							{
							case 0:

								set_theme(pad1, pad2, ball, backgT, backg, pad, wall, scor, background_bfr, 'h');
								c = 'h';
								break;
							case 1:
								set_theme(pad1, pad2, ball, backgT, backg, pad, wall, scor, background_bfr, 'i');
								c = 'i';
								break;

							case 2:
								set_theme(pad1, pad2, ball, backgT, backg, pad, wall, scor, background_bfr, 'f');
								c = 'f';
								break;

							}

						}

						break;
					}
                     break;
				}
			}

			if (men) {

				
				if (event.type == Event::KeyReleased) {
					switch (event.key.code)
					{
					case Keyboard::Up:
						menu.MoveUp();
						break;

					case Keyboard::Down:
						menu.MoveDown();
						break;

					case sf::Keyboard::Return:
						//main menu orders....
						switch (menu.GetPresseditem())
						{
						case 0:
							if (!play)
							{
								if (musicSwitch)
								{
									theme.pause();
									background.play();
								}
								getPlayerName = true;
								play = false;
								men = false;
								whenpressed_detector.play();
								MODE = 'a';

							}
							break;
						case 1:

							if (!opt) {
								opt = true;
								men = false;
								whenpressed_detector.play();

							}
							break;

						case 2:
							if (!leader)
							{
								leader = true;
								men = false;
								whenpressed_detector.play();
							}
							break;

						case 3:
							whenpressed_detector.play();
							play = true;
							if (musicSwitch)
							{
								theme.pause();
								background.play();
							}
							MODE = 't';
							break;

						case 4:
							whenpressed_detector.play();
							window.close();
							break;
						}
						break;
					}
					break;
				}

		
			}
			if (getPlayerName)
			{
				if (event.type == sf::Event::TextEntered)
				{
					if (event.text.unicode == '\b')
					{
						if (!playerName.empty())
						{
							playerName.erase(playerName.size() - 1);
							playerText.setString(playerName);
						}
					}
					else
					{
						playerName += event.text.unicode;
						playerText.setString(playerName);
					}
				}
				else if (event.key.code == sf::Keyboard::Return)
				{
					addPlayers(playerName);
					getPlayerName = false;
					playerText.setString("");
					play = true;
				}
			}
			//the way that leads to main menu (dos backspace htrg3 llmenu mn ay 7eta)
			if (isPressed(Keyboard::BackSpace) && !getPlayerName)
			{
				leader = false;
				opt = false;
				getPlayerName = false;
				if (!play)
				{
					men = true;
					if (!themePlaying)
					{
						background.stop();
						theme.play();
						themePlaying = true;
					}
				}
				else
					pause = true;

				p1win_detector = 0;
				p2win_detector = 0;
				
				//when you press return sound......
				whenreturn_detector.play();
			}

			//pause
			if (isPressed(Keyboard::P)) {
				pause = true;
			}
		}


		// LOGIC

		// pad1 Movement
		if (isPressed(Keyboard::W))
			W = true;
		else
			W = false;

		if (isPressed(Keyboard::S))
			S = true;
		else
			S = false;

		// pad2 Movement
		if (isPressed(Keyboard::Up))
			Up = true;
		else
			Up = false;

		if (isPressed(Keyboard::Down))
			Down = true;
		else
			Down = false;

		/////reset the game after close /////////////////////
		if (men ) {
			if (!playerName.empty())
			{
				playerName.erase();
				playerText.setString("");

			}
		}
		if (!play) {
			RandomPos(ball);
			//  rectangle shape with given length and width
			pad1.rect.setSize(Vector2f(20, 125));
			// Set the orgin
			pad1.rect.setOrigin(pad2.width / 2.f, pad2.length / 2.f);
			// Set the position
			pad1.rect.setPosition(pad1.width + /*the needed distance*/ 30, 400);

			//  rectangle shape with given length and width
			pad2.rect.setSize(Vector2f(20, 125));
			// Set the orgin
			pad2.rect.setOrigin(pad2.width / 2.f, pad2.length / 2.f);
			// Set the position
			pad2.rect.setPosition(GAMEWIDTH - pad2.width -  /*the needed distance*/ 30, 350);


			////reseting power ups /////////////
			longate.isSpawned = 0; longate.isActive == 1;
			freeze.isSpawned = 0;  freeze.isActive == 1;
			slow.isSpawned = 0;    slow.isActive == 1;
			invis.isActive = 0;    invis.isActive == 1;

			// Disable active powerups
			invis1 = false;    slow1 = false;   
			invis2 = false;    slow2 = false;

			pad1.rect.setFillColor(Color::White);
			pad2.rect.setFillColor(Color :: White);
			


			
		}

		if (play && !pause && !opt) {


			// Movement

			// Pad1 Movement
			//depends on the mode
			Modes(pad1, ball, MODE, frozen1, slow1, W, S);


			// Pad2 Movement
			if (!frozen2)
			{

				if (slow2)
				{
					
					pad2.velocity = Get_Movement(Down, Up) * 3;
				}
				else
					pad2.velocity = Get_Movement(Down, Up) * 10;

				pad2.rect.move(0, pad2.velocity);
				boundcheck(pad2);
			}

			// Ball Movement
			ball.circle.move(ball.xVelocity, ball.yVelocity);
			// sound_key is a number refering to which sound should be played


			if (boundcheck_ball(ball))
			{
				if (sfxSwitch)
				{
					wall_hit.play();
				}
			}

			// Ball hit pad sound
			if (isCollidingFromLeft(ball, pad2.rect) || isCollidingFromRight(ball, pad1.rect))
			{
				if (sfxSwitch)
				{
					pad_hit.play();
				}
			}



			//PowerUPS

					//spawn

					// spawns only if no player has the pUp ,
					//it's not yet spawned (prevent multi spawn) and depends on a random number generated (controls spawn rate)

			if (longate.isActive == false && longate.isSpawned == false && rand() % 100 > 96 && MODE != 't')
			{
				longate.circle.setPosition(rand() % 600, rand() % 400); //random position for spawn
				longate.isSpawned = 1; //change spawned state
			}

			if (freeze.isActive == false && freeze.isSpawned == false && rand() % 1000 > 998 && MODE != 't')
			{
				freeze.circle.setPosition(rand() % 600, rand() % 400); //random position for spawn
				freeze.isSpawned = 1; //change spawned state
			}

			if (slow.isActive == false && slow.isSpawned == false && rand() % 1000 > 900 && MODE != 't')
			{
				slow.circle.setPosition(rand() % 500, rand() % 300); //random position for spawn
				slow.isSpawned = 1; //change spawned state
			}

			if (invis.isActive == false && invis.isSpawned == false && rand() % 1000 > 998 && MODE != 't')
			{
				invis.circle.setPosition(rand() % 500, rand() % 300); //random position for spawn
				invis.isSpawned = 1; //change spawned state
			}

			//Deactivate the effect of pUP after it's time is up by tracing how long it has been activated

				//ELONGATE
			if (longate.isActive == true && longC.getElapsedTime() > seconds(6))
			{
				elongate(pad1, pad2, false,'1');
				longate.isActive = 0; //pUp is no longer active
			}

			//FREEZE
			if (freeze.isActive == true && freezeC.getElapsedTime() > seconds(2))
			{

				if (frozen1) //if the player that has the pUp is p1  (logic could be changed later)
				{
					frozen1 = 0;
					pad1.rect.setFillColor(Color::White);
				}
				else  //if the player that has the pUp is p2  (logic could be changed later)
				{
					frozen2 = 0;
					pad2.rect.setFillColor(Color::White);
				}

				freeze.isActive = 0; //pUp is no longer active
			}

			//SLOW
			if (slow.isActive == true && slowC.getElapsedTime() > seconds(3))
			{

				if (slow1) //if the player that has the pUp is p1  (logic could be changed later)
				{
					slow1 = 0;
					pad1.rect.setFillColor(Color::White);
				}
				else  //if the player that has the pUp is p2  (logic could be changed later)
				{
					slow2 = 0;
					pad2.rect.setFillColor(Color::White);
				}


				slow.isActive = 0; //pUp is no longer active
			}

			//INVIS
			if (invis.isActive == true && invisC.getElapsedTime() > seconds(1))
			{

				if (invis1) //if the player that has the pUp is p1  (logic could be changed later)
				{
					invis1 = 0;

				}
				else  //if the player that has the pUp is p2  (logic could be changed later)
				{
					invis2 = 0;

				}

				invis.isActive = 0; //pUp is no longer active
			}


			// Check collisions between the ball and the screen with x axis // score of player 1
				/*
						USE THE BALL RADIUS DON'T USE OTHER VALUES
				*/
			if (ball.circle.getPosition().x - ballRadius < 0.f)
			{
				if (sfxSwitch)
				{
					score_sound.play();
				}
				scorep2++;
				ssScorep2.str("");
				ssScorep2 << scorep2;
				lblscorep2.setString(ssScorep2.str());
				// handles the bug of counting more than one point
				RandomPos(ball);
			}


			if (ball.circle.getPosition().x + ballRadius > GAMEWIDTH)
			{
				if (sfxSwitch)
				{
					score_sound.play();
				}
				scorep1++;
				ssScorep1.str("");
				ssScorep1 << scorep1;
				lblscorep1.setString(ssScorep1.str());
				// handle the bug of counting more than one point
				RandomPos(ball);
			}
		}


		//check for collision with ball and pUp and only do so if it's already spawned on screen

		//elongate
		if (longate.isSpawned == 1 && ball.circle.getGlobalBounds().intersects(longate.circle.getGlobalBounds()))
		{
			if (sfxSwitch)
			{
				elongate_sound.play();
			}
			longC.restart(); //reset pUP timer
			longate.isSpawned = 0; //prevent multi spawn
			longate.isActive = 1;

			//if player1 is the one who took the pUP
			if (ball.xVelocity > 0)
			{
				elongate(pad1, pad2, true, '1');
			}
			//if player2 is the one who took the pUP
			else
			{
				elongate(pad1, pad2, true, '2');
			}
		}

		//Freeze
		if (freeze.isSpawned == 1 && ball.circle.getGlobalBounds().intersects(freeze.circle.getGlobalBounds()))
		{
			if (sfxSwitch)
			{
				freeze_sound.play();
			}
			freezeC.restart(); //reset pUP timer
			freeze.isSpawned = 0; //prevent multi spawn
			freeze.isActive = 1;

			//if player1 is the one who took the pUP
			if (ball.xVelocity > 0)
			{
				frozen2 = 1; //make p2 frozen
				pad2.rect.setFillColor(Color::Blue);
			}
			//if player2 is the one who took the pUP
			else
			{
				frozen1 = 1; //make p2 frozen
				pad1.rect.setFillColor(Color::White);
				pad1.rect.setFillColor(Color::Blue);
			}
		}

		//Slow
		if (slow.isSpawned == 1 && ball.circle.getGlobalBounds().intersects(slow.circle.getGlobalBounds()))
		{
			if (sfxSwitch)
			{
				slow_sound.play();
			}
			slowC.restart(); //reset pUP timer
			slow.isSpawned = 0; //prevent multi spawn
			slow.isActive = 1;

			//if player1 is the one who took the pUP
			if (ball.xVelocity > 0)
			{
				slow2 = 1; //make p2 frozen
				pad2.rect.setFillColor(Color::Red);

			}
			//if player2 is the one who took the pUP
			else
			{
				slow1 = 1; //make p2 longer
				pad1.rect.setFillColor(Color::Red);
			}
		}

		//Invis 
		if (invis.isSpawned == 1 && ball.circle.getGlobalBounds().intersects(invis.circle.getGlobalBounds()))
		{
			if (sfxSwitch)
			{
				dissapear_sound.play();
			}
			invisC.restart(); //reset pUP timer
			invis.isSpawned = 0; //prevent multi spawn
			invis.isActive = 1;

			//if player1 is the one who took the pUP
			if (ball.xVelocity > 0)
			{
				invis2 = 1; //make p2 frozen


			}
			//if player2 is the one who took the pUP
			else
			{
				invis1 = 1; //make p2 longer

			}
		}

		//Determing the end point of game
		if (scorep1 == 1)
		{
			p2win_detector = 1;
			play = false;
			themePlaying = false;

		}
		else if (scorep2 == 1)
		{
			p1win_detector = 1;
			gameOver(playerName);
			playerName.clear();
			play = false;
			themePlaying = false;

		}

		// reset the score of p1 and p2 
		if (!play) {
			scorep1 = 0;
			ssScorep1.str("");
			ssScorep1 << scorep1;
			lblscorep1.setString(ssScorep1.str());


			scorep2 = 0;
			ssScorep2.str("");
			ssScorep2 << scorep2;
			lblscorep2.setString(ssScorep2.str());


		}

		// RENDERING

		window.clear(Color::Black);

		if (getPlayerName)
		{
			window.draw(messagePlayerText);
			window.draw(playerText);
		}

		 if (play) {
			//
			window.draw(backg);
			// Draw pads and ball
			
			
			window.draw(ball.circle);
			if (!invis1)
				window.draw(pad1.rect);
			if (!invis2)
				window.draw(pad2.rect);

			//only draw pUP if it's spawned

					//elongate
			if (longate.isSpawned == true)
			{
				window.draw(longate.circle);
			}
			//freeze
			if (freeze.isSpawned == true)
			{
				window.draw(freeze.circle);
			}
			//slow
			if (slow.isSpawned == true)
			{
				window.draw(slow.circle);
			}
			//invis
			if (invis.isSpawned == true)
			{
				window.draw(invis.circle);
			}
			//draw score of player 1 
			window.draw(lblscorep1);

			//draw score of player 2
			window.draw(lblscorep2);
			men = false;

			//rendering pause window(draw pause window if option window is not opened)
			if (pause && !opt)
				pMenu.DRAW(window);

			if (opt) {
				window.draw(option);
				men = false;
				Level_of_volume.drawvolume(window);
				change_the_theme.drawtheme(window);
			}
		}


		else {
			//rendering p1 winning message 
			if (p1win_detector) {

				window.draw(p1win);
				window.draw(option);
			}

			//rendering p2 winning message 
			if (p2win_detector) {

				window.draw(p2win);
				window.draw(option);
			}

			//render option window 
			if (opt) {
				window.draw(option);
				men = false;
				Level_of_volume.drawvolume(window);
				change_the_theme.drawtheme(window);
			}
			// Rendering main menu 
			if (men) {
				menu.Draw(window);

			}
			if (leader)
			{
				viewLeaderboard(window);
			}

		}

		window.display();

	}

	// Clean up
	window.close();
	return 0;


}
