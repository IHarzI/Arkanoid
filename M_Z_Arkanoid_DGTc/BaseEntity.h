#pragma once

#include "Types.h"
#include "Window.h"

class BaseEntity
{
public:
	virtual void update(GameWorld* gameworld, double ts) = 0;
	virtual void draw() = 0;
	virtual bool init(GameWorld* gameworld) = 0;

	BaseEntity(int x, int y, int width, int height, EntityType type = NONE_ENTITY)
		: m_coord(x, y, width, height), m_type(type){}

	BaseEntity(Coord2D coord, EntityType type = NONE_ENTITY)
		: m_coord(coord), m_type(type){}

	virtual ~BaseEntity(){};

	const Coord2D& GetCoord() { return m_coord; }
	void SetCoord(Coord2D& coord) { m_coord = coord; }
	void SetCoord(int x = 0, int y = 0, int width = 0, int height = 0)
	{
		m_coord = Coord2D(x, y, width, height);
	};

	int2 GetUpBound() { return int2(m_coord.x_ + m_coord.width_ / 2, m_coord.y_); }
	int2 GetDownBound() { return int2(m_coord.x_ + m_coord.width_ / 2, m_coord.y_ + m_coord.height_); }
	int2 GetLeftBound() { return int2(m_coord.x_, m_coord.y_ + m_coord.height_ / 2); }
	int2 GetRightBound() { return int2(m_coord.x_ + m_coord.width_, m_coord.y_ + m_coord.height_ / 2); }
		 
	int2 GetULCorner() { return int2(m_coord.x_, m_coord.y_); }
	int2 GetURCorner() { return int2(m_coord.x_ + m_coord.width_, m_coord.y_); }
	int2 GetDRCorner() { return int2(m_coord.x_ + m_coord.width_, m_coord.y_ + m_coord.height_); }
	int2 GetDLCorner() { return int2(m_coord.x_, m_coord.y_ + m_coord.height_); }
		 
	int2 GetOrigin() { return int2(GetCoord().x_ + GetCoord().width_ / 2, GetCoord().y_ + GetCoord().height_ / 2); }
	int2 GetUOrigin() { return int2(GetCoord().x_ + GetCoord().width_ / 2, GetCoord().y_); }
	int2 GetDOrigin() { return int2(GetCoord().x_ + GetCoord().width_ / 2, GetCoord().y_ + GetCoord().height_); }

	Pair(bool, BaseEntity*) IsCollided(BaseEntity* entity);

	virtual bool IsEntityActive() { return true; }

	void SetTextureSize(int width =0, int height =0) { m_coord.width_ = width; m_coord.height_ = height; }

	const int2& GetTextureSize() { return int2(m_coord.width_, m_coord.height_); }

	void SetX(int x) { m_coord.x_ = x; }
	void SetY(int y) { m_coord.y_ = y; }

	EntityType GetType() { return m_type; }
	void SetType(EntityType type) { m_type = type; }

private:
	Coord2D m_coord;
	EntityType m_type;
};

