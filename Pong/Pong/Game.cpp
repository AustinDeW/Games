#include "Game.h"

//TODO: Add AI for Single Player
Game::Game(sf::VideoMode vm, std::string title)
	: window(vm, title), centerLine(sf::Vector2f(1, GetWindow()->getSize().x))
{
	window.setFramerateLimit(60);

	font.loadFromFile("Data/arial.ttf");

	centerLine.setFillColor(sf::Color::Green);
	centerLine.setPosition(401, 0);

	score.setFont(font);
	score.setCharacterSize(48);
	score.setFillColor(sf::Color::White);
	sf::FloatRect scoreRect = score.getLocalBounds();
	score.setOrigin(scoreRect.left + scoreRect.width / 2.0f, scoreRect.top + scoreRect.height / 2.0f);
	score.setPosition(sf::Vector2f(window.getSize().x / 2 - 45, 20));
	score.setString("0   0");

	player1.SetPosition(sf::Vector2f(20, 300 - player1.GetSize()->y / 2));
	player2.SetPosition(sf::Vector2f(760, 300 - player2.GetSize()->y / 2));

	ball.SetPosition(sf::Vector2f(window.getSize().x / 2 - 15, window.getSize().y / 2 - 15));
}

sf::RenderWindow* Game::GetWindow()
{
	return &window;
}

void Game::HandleInput()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			window.close();
		}

		else if (event.type == sf::Event::KeyPressed)
		{
			if (players == 1)
			{
				switch (event.key.code)
				{
					case sf::Keyboard::Escape:
						BackToMainMenu();
						break;
					case sf::Keyboard::Up:
						player1_key_up = true;
						break;
					case sf::Keyboard::Down:
						player1_key_down = true;
						break;
				}
			}
			else
			{
				switch (event.key.code)
				{
					case sf::Keyboard::Escape:
						BackToMainMenu();
						break;
					case sf::Keyboard::W:
						player1_key_up = true;
						break;
					case sf::Keyboard::S:
						player1_key_down = true;
						break;
					case sf::Keyboard::Up:
						player2_key_up = true;
						break;
					case sf::Keyboard::Down:
						player2_key_down = true;
						break;
				}
			}

		}

		else if (event.type == sf::Event::KeyReleased)
		{
			if (players == 1)
			{
				switch (event.key.code)
				{
					case sf::Keyboard::Up:
						player1_key_up = false;
						break;
					case sf::Keyboard::Down:
						player1_key_down = false;
						break;
				}
			}
			else
			{
				switch (event.key.code)
				{
					case sf::Keyboard::W:
						player1_key_up = false;
						break;
					case sf::Keyboard::S:
						player1_key_down = false;
						break;
					case sf::Keyboard::Up:
						player2_key_up = false;
						break;
					case sf::Keyboard::Down:
						player2_key_down = false;
						break;
				}
			}
		}
	}
}

void Game::Update()
{
	if (player1_key_up) player1_yPos = -5;
	else if (player1_key_down) player1_yPos = 5;
	else if (player1_key_up && player1_key_down) player1_yPos = 0;
	else if (!player1_key_up && !player1_key_down) player1_yPos = 0;

	player1.Move(sf::Vector2f(0, player1_yPos));

	if (player1.GetPosition()->y < 0) player1.SetPosition(sf::Vector2f(20, 0));
	else if (player1.GetPosition()->y > 600 - player1.GetSize()->y) player1.SetPosition(sf::Vector2f(20, 500));

	if (players == 2)
	{
		if (player2_key_up) player2_yPos = -5;
		else if (player2_key_down) player2_yPos = 5;
		else if (player2_key_up && player2_key_down) player2_yPos = 0;
		else if (!player2_key_up && !player2_key_down) player2_yPos = 0;

		player2.Move(sf::Vector2f(0, player2_yPos));

		if (player2.GetPosition()->y < 0) player2.SetPosition(sf::Vector2f(760, 0));
		else if (player2.GetPosition()->y > 600 - player2.GetSize()->y)player2.SetPosition(sf::Vector2f(760, 500));
	}
	else
	{
		//AI here
		if (ballDirection_LR == 1)
		{
			if (ball_xPos == 3 && ball_yPos == 3)
			{
				ballDirection_UD = false;
			}
			else if (ball_xPos == 3 && ball_yPos == -3)
			{
				ballDirection_UD = true;
			}
			if (ballDirection_UD && ball.GetPosition()->y > window.getSize().y / 4)
			{
				player2_yPos = -3;
			}
			else if (ballDirection_UD) // up
			{
				player2_yPos = -7;
			}
			else if (!ballDirection_UD && ball.GetPosition()->y < window.getSize().y / 3)
			{
				player2_yPos = -7;
			}
			else if(!ballDirection_UD) // down
			{
				player2_yPos = 7;
			}

			player2.Move(sf::Vector2f(0, player2_yPos));

			if (player2.GetPosition()->y < 0) player2.SetPosition(sf::Vector2f(760, 0));
			else if (player2.GetPosition()->y > 600 - player2.GetSize()->y)player2.SetPosition(sf::Vector2f(760, 500));
		}
	}

	

	ball.Move(sf::Vector2f(ball_xPos, ball_yPos));

	if (ball.GetPosition()->y < 0) ball_yPos = -ball_yPos;
	else if (ball.GetPosition()->y > window.getSize().y - ball.GetRadius() * 2) ball_yPos = -ball_yPos;

	if (ball.GetGlobalBounds().intersects(player1.GetGlobalBounds()))
	{
		ball_xPos = -ball_xPos;
		ballDirection_LR = true;
	}
	else if (ball.GetGlobalBounds().intersects(player2.GetGlobalBounds()))
	{
		ball_xPos = -ball_xPos;
		ballDirection_LR = false;
	}

	if (ball.GetPosition()->x > window.getSize().x)
	{
		player1_score++;
		ResetBall();
	}
	else if (ball.GetPosition()->x < 0)
	{
		player2_score++;
		ResetBall();
	}
}

void Game::Render()
{
	window.clear(sf::Color::Black);

	std::stringstream ssScore; ssScore << player1_score << "   " << player2_score;
	score.setString(ssScore.str());
	window.draw(score);
	window.draw(centerLine);
	window.draw(*player1.GetDrawable());
	window.draw(*player2.GetDrawable());
	window.draw(*ball.GetDrawable());
	window.display();
}

void Game::ResetBall()
{
	ball.SetPosition(sf::Vector2f(window.getSize().x / 2 - 15, window.getSize().y / 2 - 15));
}

void Game::BackToMainMenu()
{
	score.setString("0   0");
	player1_score = 0;
	player2_score = 0;
	ResetBall();
	MainMenu();
}

Game::~Game()
{
}

void Game::MainMenu()
{
	bool highlight_twoPlayer = false;
	bool highlight_singlePlayer = true;
	bool highlight_exit = false;
	mainMenuOpen = true;

	sf::Text title;
	title.setFont(font);
	title.setCharacterSize(72);
	title.setFillColor(sf::Color::Green);
	title.setString("PONG");
	sf::FloatRect titleRect = title.getLocalBounds();
	title.setOrigin(titleRect.left + titleRect.width / 2.0f, titleRect.top + titleRect.height / 2.0f);
	title.setPosition(sf::Vector2f(window.getSize().x / 2, 100));

	sf::Texture txtr_singlePlayer;
	txtr_singlePlayer.loadFromFile("Data/MainMenuSinglePlayerOption.png");
	sf::Texture txtr_twoPlayer;
	txtr_twoPlayer.loadFromFile("Data/MainMenuTwoPlayerOption.png");
	sf::Texture txtr_exit;
	txtr_exit.loadFromFile("Data/MainMenuExitOption.png");

	sf::RectangleShape menu_singlePlayer(sf::Vector2f(208,38));
	menu_singlePlayer.setTexture(&txtr_singlePlayer);
	menu_singlePlayer.setPosition(window.getSize().x / 2 - menu_singlePlayer.getSize().x / 2, 180);
	menu_singlePlayer.setOutlineColor(sf::Color::Green);

	sf::RectangleShape menu_twoPlayer(sf::Vector2f(178, 37));
	menu_twoPlayer.setTexture(&txtr_twoPlayer);
	menu_twoPlayer.setPosition(window.getSize().x / 2 - menu_twoPlayer.getSize().x / 2, 180 + 60);
	menu_twoPlayer.setOutlineColor(sf::Color::Green);

	sf::RectangleShape menu_exit(sf::Vector2f(62, 33));
	menu_exit.setTexture(&txtr_exit);
	menu_exit.setPosition(window.getSize().x / 2 - menu_exit.getSize().x / 2, 180 + 120);
	menu_exit.setOutlineColor(sf::Color::Green);

	while (mainMenuOpen)
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
				mainMenuOpen = false;
			}
			else if (event.type == sf::Event::KeyPressed)
			{
				switch (event.key.code)
				{
					case sf::Keyboard::Escape:
						window.close();
						mainMenuOpen = false;
						break;
				}
			}
			else if (event.type == sf::Event::KeyReleased)
			{

			}
			else if (event.type == sf::Event::MouseButtonPressed)
			{
				if (menu_singlePlayer.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
				{
					players = 1;
					window.clear(sf::Color::Black);
					window.display();
					mainMenuOpen = false;
				}
				else if (menu_twoPlayer.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
				{
					players = 2;
					window.clear(sf::Color::Black);
					window.display();
					mainMenuOpen = false;
				}
				else if (menu_exit.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
				{
					window.close();
					mainMenuOpen = false;
				}
			}
			else if (event.type == sf::Event::MouseMoved)
			{
				if (menu_twoPlayer.getGlobalBounds().contains(event.mouseMove.x, event.mouseMove.y))
				{
					highlight_twoPlayer = true;	
					highlight_exit = false;
					highlight_singlePlayer = false;
				}
				else if (menu_singlePlayer.getGlobalBounds().contains(event.mouseMove.x, event.mouseMove.y))
				{
					highlight_twoPlayer = false;
					highlight_exit = false;
					highlight_singlePlayer = true;
				}
				else if (menu_exit.getGlobalBounds().contains(event.mouseMove.x, event.mouseMove.y))
				{
					highlight_twoPlayer = false;
					highlight_exit = true;
					highlight_singlePlayer = false;
				}				
			}
		}

		if (highlight_twoPlayer) menu_twoPlayer.setOutlineThickness(1);
		else menu_twoPlayer.setOutlineThickness(0);
		if (highlight_singlePlayer) menu_singlePlayer.setOutlineThickness(1);
		else menu_singlePlayer.setOutlineThickness(0);
		if (highlight_exit) menu_exit.setOutlineThickness(1);
		else menu_exit.setOutlineThickness(0);

		window.clear(sf::Color::Black);

		window.draw(title);
		window.draw(menu_singlePlayer);
		window.draw(menu_twoPlayer);
		window.draw(menu_exit);

		window.display();
	}
}