#pragma once

void themeChange(PAD& pad1, PAD& pad2, BALL& ball, Texture& backgT, RectangleShape& backg,
	SoundBuffer& pad, SoundBuffer& wall, SoundBuffer& score, SoundBuffer& background, char c,SoundBuffer& scor, SoundBuffer& background_bfr,int index)
{
	switch (index)
	{
	case 0:
		set_theme(pad1, pad2, ball, backgT, backg, pad, wall, scor, background_bfr, 'h');
		c = 'h';
		break;
		case 1:
			set_theme(pad1, pad2, ball, backgT, backg, pad, wall, scor, background_bfr, 'f');
			c = 'f';
			break;
		case 2:
			set_theme(pad1, pad2, ball, backgT, backg, pad, wall, scor, background_bfr, 'i');
			c = 'i';
			break;

	}
	done = true;
}


void menuReturn(bool& leader, bool& opt, bool& getPlayerName, bool& play, bool& men, bool& themePlaying, Sound& background, Music& theme, bool& pause, bool& p1win_detector, bool& p2win_detector, Sound& whenreturn_detector)
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

void nameInput(Event& event, string& playerName, bool& getPlayerName, Text& playerText, bool& play, int playNum, bool& save)
{


	////////////////////////////////////////////////////////////
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
		else if (event.text.unicode == '\r')
		{
			//DO NOTHING
		}
		else if (!(event.text.unicode == ' ' || playerName.size() > 10))
		{
			playerName += event.text.unicode;
			playerText.setString(playerName);
		}
	}
	else if (event.key.code == sf::Keyboard::Return && playerName.size() > 0)
	{
		addPlayers(playerName);
		playerText.setString("");
		save = true;
		if (playNum == 2)
		{
			getPlayerName = false;
			play = true;
		}
	}
}



//textinit function is overloaded 4 times , each one for different type of text intialization

//Initializes the scores texts
void textInit(Text& text, Font& font, ostringstream& ssScore, int player)
{

	text.setCharacterSize(30);
	if (player == 1)
	{
		text.setPosition(290, 5);
	}
	else
	{
		text.setPosition(440, 5);
	}

	text.setFont(font);
	text.setCharacterSize(50);
	text.setFillColor(sf::Color::White);
	text.setString(ssScore.str());

}

//Initializes the options text
void textInit(Text& option, Font& font)
{

	option.setFont(font);
	option.setCharacterSize(40);
	option.setPosition(200.f, 425.f);
	option.setFillColor(Color::White);
	option.setString("Press Backspace to return");
}

//Initializes the player name and prompt message
void textInit(Text& playerText, Text& messagePlayerText, Font& font, int playerNum)
{
	playerText.setFont(font);
	playerText.setCharacterSize(40);
	playerText.setPosition(200.f, 425.f);
	playerText.setFillColor(Color::White);

	messagePlayerText.setFont(font);
	messagePlayerText.setCharacterSize(40);
	messagePlayerText.setPosition(100.f, 100.f);
	messagePlayerText.setFillColor(Color::White);
	if (playerNum == 1)
	{
		messagePlayerText.setString("Please enter name of player 1!");
	}
	else if (playerNum == 2)
	{
		messagePlayerText.setString("Please enter name of player 2!");
	}

}

//Initializes win message

void textInit(Text& win, Font& font, char c)
{
	win.setCharacterSize(100);
	win.setPosition(GAMEHEIGHT / 2, 100);
	win.setFillColor(sf::Color::White);
	win.setFont(font);
}

//Pause Menu Events
void pauseEvents(Event& event, MENU& pauseMenu, Text pauseItems[], Sound& whenreturn_detector, Sound& whenpressed_detector, Sound& background, Music& theme, bool& pause, bool& opt, bool& getPlayerName, bool& play, bool& men, bool& musicSwitch)
{
	switch (event.key.code)
	{
	case Keyboard::Up:
		moveUp(pauseMenu, 3, pauseItems);
		whenreturn_detector.play();
		break;

	case Keyboard::Down:
		moveDown(pauseMenu, pauseItems, 3);
		whenreturn_detector.play();
		break;

	case Keyboard::Return:
		switch (pauseMenu.selectedItemIndex)
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

	case Mouse::Left:
		switch (pauseMenu.selectedItemIndex)
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

}

//Main Menu Events

void mainmenuEvents(MENU& mainMenu, Text mainItems[], bool& play, bool& musicSwitch, Music& theme, Sound& background, bool& getPlayerName, bool& men, Sound& whenpressed_detector, char& MODE, bool& opt, bool& leader, RenderWindow& window)
{
	switch (event.key.code)
	{
	case Keyboard::Up:
		moveUp(mainMenu, 5, mainItems);
		break;

	case Keyboard::Down:
		moveDown(mainMenu, mainItems, 5);
		break;

	case Keyboard::Return:
		//main menu orders....
		switch (mainMenu.selectedItemIndex)
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
				MODE = '2';
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

	case Mouse::Left:
		switch (mainMenu.selectedItemIndex)
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
				MODE = '2';
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



}