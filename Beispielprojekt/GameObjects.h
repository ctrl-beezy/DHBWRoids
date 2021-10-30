#pragma once
class GameObject
{
	double positionX;
	double positionY;
	double velocity;
	
	public:
		double get_position();
		void set_position(double x, double y);
		double get_velocity();
		void set_velocity(double v);
};

class PlayerCharacter : public GameObject
{
	Gosu::Sample beep, lose, earn, win;
	Gosu::Image Rakete1, Rakete2, Rakete3, Rakete4;

public:
	Player()
		: beep(Gosu::resource_prefix() + "Assets/Sounds/Laser-Sound.wav"),
		lose(Gosu::resource_prefix() + "Assets/Sounds/Lose-Sound.wav"),
		earn(Gosu::resource_prefix() + "Assets/Sounds/Earn-Sound.wav"),
		win(Gosu::resource_prefix() + "Assets/Sounds/Winning-Sound.wav");

		Rakete1("Assets/Bilder/Rakete1.png"), 
		Rakete2("Assets/Bilder/Rakete2.png"), 
		Rakete3("Assets/Bilder/Rakete3.png"), 
		Rakete4("Assets/Bilder/Rakete4.png");
};

class Projectile : public GameObject
{

};

class Enemy : public GameObject
{

};

class Background_music
{
	Gosu::Sample background1, background2, background3;

public:
	Sound()
		: background1(Gosu : resource_prefix() + "Assets/Sounds/Background-Space1.wav"),
		background2(Gosu : resource_prefix() + "Assets/Sounds/Background-Space2.wav"),
		background3(Gosu : resource_prefix() + "Assets/Sounds/Background-Space3.wav");

};