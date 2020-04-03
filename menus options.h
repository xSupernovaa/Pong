#pragma once
#include "Optionmenu.h"

//vol switch

void volChange(Optionmenu& Level_of_volume, Music& theme, Sound& background)
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

void themeChange(Optionmenu& change_the_theme, PAD& pad1, PAD& pad2, BALL& ball, Texture& backgT, RectangleShape& backg,
	SoundBuffer& pad, SoundBuffer& wall, SoundBuffer& score, SoundBuffer& background, char c,SoundBuffer& scor, SoundBuffer& background_bfr)
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

void pauseEvents(Event& event, pauseMenu& pMenu, Sound& whenreturn_detector, Sound& whenpressed_detector, Sound& background, Music& theme, bool& pause, bool& opt, bool& getPlayerName, bool& play, bool& men, bool& musicSwitch)
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

}


void menuNav(Event& event,bool& switcher,Optionmenu& Level_of_volume,Optionmenu& change_the_theme)
{
	switch (event.key.code)
	{
	case Keyboard::Right:
		if (switcher)
			Level_of_volume.MoveRight();
		else
			change_the_theme.MoveRight();
		break;

	case Keyboard::Left:
		if (switcher)
			Level_of_volume.MoveLeft();
		else
			change_the_theme.MoveLeft();

		break;

	case Keyboard::Up:
		Level_of_volume.MoveUp();
		change_the_theme.MoveUp();
		switcher = true;
		break;

	case Keyboard::Down:
		Level_of_volume.MoveDown();
		change_the_theme.MoveDown();
		switcher = false;
		break;
	}
}

void mainmenuEvents(Menu& menu,bool& play,bool& musicSwitch,Music& theme,Sound& background,bool& getPlayerName,bool& men,Sound& whenpressed_detector,char& MODE,bool& opt,bool& leader,RenderWindow& window)
{
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

void nameInput(Event& event, string& playerName, bool& getPlayerName, Text& playerText, bool& play)
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
void textInit(Text& playerText, Text& messagePlayerText, Font& font)
{
	playerText.setFont(font);
	playerText.setCharacterSize(40);
	playerText.setPosition(200.f, 425.f);
	playerText.setFillColor(Color::White);

	messagePlayerText.setFont(font);
	messagePlayerText.setCharacterSize(40);
	messagePlayerText.setPosition(100.f, 100.f);
	messagePlayerText.setFillColor(Color::White);
	messagePlayerText.setString("Please enter thy name!");

}

//Initializes win message

void textInit(Text& win, Font& font, char c)
{
	win.setCharacterSize(100);
	win.setPosition(GAMEHEIGHT / 2, 100);
	win.setFillColor(sf::Color::White);
	win.setFont(font);
}
