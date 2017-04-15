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

class SymmetricSandPile {
public:
	SandPileGrid(int width, int height):
		width(width),
		height(height),
		gridQuad(width * height),
		unstableCells(width * height)
	{}

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

	void writeToBMPFile(std::string file_name);

private:
	int width;
	int height;
	std::vector<int> gridQuad;
	std::vector<int> unstableCells;

	void refreshUnstable();
};
////////////////////////////////////////////////////////////////////////////////
#endif