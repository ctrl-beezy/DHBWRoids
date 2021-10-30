#pragma once
class GameObject
{
	double x;
	double y;
	double dx;
	double dy;
	
	public:
		double get_position();
		void set_position(double x, double y);
		double get_velocity();
		void set_velocity(double v);
};

class PlayerCharacter : public GameObject
{

};

class Projectile : public GameObject
{

};

class asteroid : public GameObject
{

};