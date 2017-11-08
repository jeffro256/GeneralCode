#ifndef _SYMMETRIC_SAND_PILE_HPP_
#define _SYMMETRIC_SAND_PILE_HPP_
////////////////////////////////////////////////////////////////////////////////
#include <string>
#include <vector>

/*
TODO: (URGENT)
Change width and height to size_t and pass grid as pointer to vector without
copying
*/

class SymmetricFastByteSandPile {
public:
	SymmetricFastByteSandPile(int width, int height);

	long topple();
	long step(long max_steps);
	void step();
	bool isStable();

	int getSand(int x, int y);
	void setSand(int sand, int x, int y);
	void place(int sand, int x, int y);
	long amountSand();
	void fill(int sand);
	void clear();

	int getWidth();
	int getHeight();
	void setWidth(int width);
	void setHeight(int height);
	void setSize(int width, int height);
private:
	int width;
	int height;
	std::vector<int> gridQuad;
	std::vector<int> unstableCells;

	void _refreshUnstable();
};
////////////////////////////////////////////////////////////////////////////////
#endif