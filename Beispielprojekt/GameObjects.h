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

public:
	Player()
		: beep(Gosu::resource_prefix() + "Assets/Laser-Sound.wav"),
		lose(Gosu::resource_prefix() + "Assets/Lose-Sound.wav"),
		earn(Gosu::resource_prefix() + "Assets/Earn-Sound.wav"),
		win(Gosu::resource_prefix() + "Assets/Winning-Sound.wav");
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
		: background1(Gosu : resource_prefix() + "Assets/Background-Space1.wav"),
		background2(Gosu : resource_prefix() + "Assets/Background-Space2.wav"),
		background3(Gosu : resource_prefix() + "Assets/Background-Space3.wav");

};