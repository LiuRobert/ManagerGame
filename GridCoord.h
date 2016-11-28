#pragma once
struct GridCoord
{
	GridCoord() {}
	GridCoord(const int& x, const int& y) : x(x), y(y) {}
	bool operator==(const GridCoord& rhs) const
	{
		return x == rhs.x && y == rhs.y;
	}
	int x;
	int y;
};
