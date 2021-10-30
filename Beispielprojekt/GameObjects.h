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
	Gosu::Sample beep;

public:
	Player()
		:beep(Gosu::resource_prefix()+"Assets/Laser-Sound.wav")
};

class Projectile : public GameObject
{

};

class Enemy : public GameObject
{

};