#include "header.hpp"
//#include "characters.cpp"
#include "2d_item.cpp"

#define VERSION "Atomic Desert ver_0.03 USING ITEMS IN EQUIPEMENT"


int main()
{
	//SETTING CREATION
	sf::ContextSettings settings;
	settings.antialiasingLevel=2;
	//WINDOW CREATION
	sf::RenderWindow screen;
	screen.create(sf::VideoMode(RES_X, RES_Y),VERSION,sf::Style::Default,settings);
	//CLOCK CREATION
	sf::Clock Clock;
	int frame_time = 16; // ms

	sf::Event event;

	//CREATING CHARACTER OBJECT
	Character Player_1(100, 100, "./Textures/Player.png");	
	Player_1.set_texture();
	Player_1.set_position();

	/*
	//DEBUG, USE 50x50 pixel pictures for items
	Square_2D painkiller(50,50,"./Textures/painkiller.jpg");
	painkiller.set_texture();
	*/

	//CREATING ITEM OBJECT, inherited from Square_2D Class
	Item_medicine pain_killer(10,"./Textures/painkiller.jpg");
	Item_medicine small_poison(-10,"./Textures/poison.png");


	//CREATING INVENTORY OBJECT as for now it only displays objects "2D_square"
	Inventory Equipement_1;
	//FILLINg PLAYER'S INVENTORY WITH painkillers
	Equipement_1.add_item(pain_killer); //filling inventory with random stuff
	Equipement_1.add_item(small_poison);

	//DEBUG
		std::cout<<RES_X/5<<std::endl;
		std::cout<<RES_Y/5<<std::endl;
		


	//MAIN LOOP
	while(screen.isOpen())
	{
		Clock.restart();
		sf::Event event;	
		
		
		while(screen.pollEvent(event))
		{
			if(event.type==sf::Event::Closed) screen.close();
			//KEYBOARD HANDLING WORK IN PROGRESS
			if(event.type==sf::Event::KeyPressed)
			{
				switch(event.key.code)
				{ 
					case sf::Keyboard::Escape:
						screen.close();
					break;					
					case sf::Keyboard::I: //opening and closing EQ
						if(Equipement_1.get_open())
						{
							Equipement_1.set_open(false);
						}
						else Equipement_1.set_open(true);
					break;

				}
			}
			//HANDING MOUSE CLICKS
			if(event.type==sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{					
					//USING ITEMS IN EQ IF IT IS OPENED
					if(Equipement_1.get_open())
					{						
						Equipement_1.using_items(sf::Mouse::getPosition(),&Player_1);//Second argument decides who the item is used on
					}
				}
			}
		}

		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			Player_1.ver_acc = -1;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			Player_1.ver_acc = 1;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			Player_1.hor_acc = 1;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			Player_1.hor_acc = -1;
		}

		Player_1.gain_speed();
		Player_1.move();

		screen.clear(sf::Color::Yellow);
		screen.draw(Player_1.get_shape());
		Equipement_1.disp_eq(&screen);		

		//screen.draw()
		screen.display();


		//CONTROLING FPS
		sf::Time time = Clock.getElapsedTime();
		sf::Int32 passed = time.asMilliseconds();
		while (frame_time > passed)
		{ 
			time = Clock.getElapsedTime(); // looping while waiting for next frame
			passed = time.asMilliseconds();
		}
	}

	//DLA WINDOWSA
	// system("pause");
	return 0;
}