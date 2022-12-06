#pragma once

#include <iostream>
#define AbilitysLifeTime 9000
#include <memory>
#include <list>
#include <utility>
#include <unordered_map>
#include <stdlib.h>  
#define Scope(x) std::shared_ptr<x>
#define CreateScope(x) Scope(x)(new x)
#define CreateScope(x,a) Scope(x)(new x(a))
#define List(x) std::list<x>
#define Map(x,a) std::unordered_map<x,a>
#define Pair(x,a) std::pair<x,a>
#define MakePair(x,a) std::make_pair(x,a)
class GameWorld;
struct Window;
struct TextureManager;
// redefine key enums from framework
enum Key
{
	
	RIGHT_KEY= 0,
	LEFT_KEY,
	DOWN_KEY,
	UP_KEY,
	NONE_KEY
};
// redefine mouse buttons from framework
enum MouseButton
{
	MOUSE_LEFT = 0, MOUSE_MIDDLE, MOUSE_RIGHT, NONE_MOUSEKEY
};
// entiti types objects
enum EntityType
{
	NONE_ENTITY = -1, PLAYER, BALL, POSITIVE_ABILITY, NEGATIVE_ABILITY, SIMPLE_BRICK, SPECIAL_BRICK
};

struct HandledAbility
{
	HandledAbility(EntityType type)
	{
		type_ = type;
	}
	void update(double ts) { lifetime_ -= ts; }

	EntityType type_ = NONE_ENTITY;
	double lifetime_ = AbilitysLifeTime;
};

struct int2
{

	int2(int x = 0, int y = 0)
		: x_(x), y_(y) {}

	int x_, y_;

	int2(int2&& other)
	{
		x_ = other.x_;
		y_ = other.y_;
		other.x_ = 0;
		other.y_ = 0;
	}

	int2(int2& other)
	{
		x_ = other.x_;
		y_ = other.y_;
	}



	bool operator> (int2 first)
	{
		return (first.x_ > x_ && first.y_ > y_);
	}

	bool operator>= (int2 first)
	{
		return (first.x_ >= x_ && first.y_ >= y_);
	}

	bool operator< (int2 first)
	{
		return (first.x_ < x_ && first.y_ < y_);
	}
	bool operator<= (int2 first)
	{
		return (first.x_ <= x_ && first.y_ <= y_);
	}
};


struct Coord2D
{
public:

	Coord2D(int x = 0, int y= 0, int width= 0, int height = 0)
		: x_(x), y_(y), width_(width), height_(height){}

	int x_, y_, width_, height_;

};


struct vec2
{
	vec2(float x = 0, float y = 0)
		: x_(x),y_(y) {}
	float x_, y_;

	void SetValue(float x, float y) { x_ = x; y_ = y; }
};
