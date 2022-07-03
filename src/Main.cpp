#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

int setActiveCulture(int activeCulture)
{
	if(activeCulture == 0)
		return activeCulture = 1;
	else
		return activeCulture = 0;
}

int main()
{
	const int WIDTH = 1920;
	const int HEIGHT = 1080;

	bool isMousePressed = false;
	bool isKeyboardPressed = false;

	int x;
	int y;
	int activeCulture = 0;

    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Game of Life");

	std::vector<std::vector<std::vector< bool> > > Culture(2, std::vector<std::vector<bool>>(WIDTH/32, std::vector<bool>(HEIGHT/32)));

	for(int k = 0; k < 2; k++)
		for(int i = 0; i < WIDTH / 32; i++)
			for(int j = 0; j < HEIGHT / 32; j++)
			{
				Culture[k][i][j] = false;
			}

	std::vector<std::vector< sf::RectangleShape> > Cellus(WIDTH/32, std::vector<sf::RectangleShape>(HEIGHT/32));

	for(int i = 0; i < WIDTH / 32; i++)
		for(int j = 0; j < HEIGHT / 32; j++)
		{
			Cellus[i][j].setSize(sf::Vector2f(32,32));
			Cellus[i][j].setPosition(i*32,j*32);
			Cellus[i][j].setFillColor(sf::Color(i*10, j*13, i*2));
		}

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
		
		if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && isMousePressed == false)
		{
			x = sf::Mouse::getPosition(window).x / 32;
			y = sf::Mouse::getPosition(window).y / 32;

			for(int i = 0; i < 2; i++)
			{
				if(Culture[i][x][y] == false)
					Culture[i][x][y] = true;
				else
					Culture[i][x][y] = false;
			}

			isMousePressed = true;
		}

		if(!sf::Mouse::isButtonPressed(sf::Mouse::Left) || x != sf::Mouse::getPosition(window).x/32 || y != sf::Mouse::getPosition(window).y/32)
			isMousePressed = false;

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) && isKeyboardPressed == false)
		{

			for(int i = 1; i < WIDTH / 32 -1; i++)
				for(int j = 1; j < HEIGHT / 32 -1; j++)
				{
					int counter = 0;

					for(int k = i - 1; k < i + 2; k++)
						for(int l = j - 1; l < j + 2; l++)
						{
							if(Culture[activeCulture][k][l] == true && (k != i || l != j))
							{
								 counter++;
							}
						}

						activeCulture = setActiveCulture(activeCulture);

						switch(counter)
						{
							case 0: 
								Culture[activeCulture][i][j] = false;
								break;
							case 1: 
								Culture[activeCulture][i][j] = false;
								break;
							case 3: 
								Culture[activeCulture][i][j] = true;
								break;
							case 4: 
								Culture[activeCulture][i][j] = false;
								break;
							case 5: 
								Culture[activeCulture][i][j] = false;
								break;
							case 6: 
								Culture[activeCulture][i][j] = false;
								break;
							case 7: 
								Culture[activeCulture][i][j] = false;
								break;
							case 32: 
								Culture[activeCulture][i][j] = false;
								break;
						}

						activeCulture = setActiveCulture(activeCulture);
				}

				for(int i = 0; i < WIDTH / 32; i++)
					for(int j = 0; j < HEIGHT / 32; j++)
					{
						Culture[activeCulture][i][j] = Culture[setActiveCulture(activeCulture)][i][j];
					}

				setActiveCulture(activeCulture);
		}

		if(!sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			isKeyboardPressed = false;

		window.clear(sf::Color(0,0,0));

		for(int i = 0; i < WIDTH / 32; i++)
			for(int j = 0; j < HEIGHT / 32; j++)
			{
				if(Culture[activeCulture][i][j] == true)
				{
					window.draw(Cellus[i][j]);
				}
			}

        window.display();
    }

    return 0;
}
