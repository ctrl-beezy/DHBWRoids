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
	Gosu::Image Rakete1, Rakete2, Rakete3, Rakete4, Rakete5;
	Gosu::Image Hitmarker1, Hitmarker2, Hitmarker3, Hitmarker4;

public:
	Player()
		: beep(Gosu::resource_prefix() + "Assets/Sounds/Laser-Sound.wav"),
		lose(Gosu::resource_prefix() + "Assets/Sounds/Lose-Sound.wav"),
		earn(Gosu::resource_prefix() + "Assets/Sounds/Earn-Sound.wav"),
		win(Gosu::resource_prefix() + "Assets/Sounds/Winning-Sound.wav");

	Player()
		:Rakete1("Assets/Bilder/Rakete1.bmp"),
		Rakete2("Assets/Bilder/Rakete2.bmp"),
		Rakete3("Assets/Bilder/Rakete3.bmp"),
		Rakete4("Assets/Bilder/Rakete4.bmp"),
		Rakete5("Assets/Bilder/Rakete5.bmp");

	Player()
		:Hitmarker1("Assets/Bilder/Hitmarker1.bmp"),
		Hitmarker2("Assets/Bilder/Hitmarker2.bmp"),
		Hitmarker3("Assets/Bilder/Hitmarker3.bmp"),
		Hitmarker4("Assets/Bilder/Hitmarker4.bmp");
};

class Projectile : public GameObject
{
	Gosu::Image Projektil1, Projektil2;

	Projectile()
		:Projektil1("Assets/Bilder/Projektil1.bmp"),
		Projektil2("Assets/Bilder/Projektil2.bmp");
};

class Enemy : public GameObject
{
	Gosu::Image Asterioid_ganz, Asterioid_viertel, Asterioid_sechzehntel;

	Enemy()
		:Asterioid_ganz("Assets/Bilder/Asterioid_ganz.bmp"),
		Asterioid_viertel("Assets/Bilder/Asterioid_viertel.bmp"),
		Asterioid_sechzehntel("Assets/Bilder/Asterioid_sechzehntel.bmp");
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