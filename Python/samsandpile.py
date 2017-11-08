grid = [[0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0], 
	[0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
	[0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
	[0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
	[0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
	[0, 0, 0, 0, 0,32, 0, 0, 0, 0, 0],
	[0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0], 
	[0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
	[0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
	[0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
	[0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]]

def topple(grid):
	new_grid = []
	for r in grid:
		nr = []
		for c in r:
			nr.append(c)
		new_grid.append(nr)

	for y in range(len(grid)):
		for x in range(len(grid[0])):
			sand = grid[y][x]

			if sand >= 4:
				new_grid[y][x] = sand - 4
				new_grid[y+1][x] = grid[y+1][x] + 1
				new_grid[y-1][x] = grid[y-1][x] + 1
				new_grid[y][x+1] = grid[y][x+1] + 1
				new_grid[y][x-1] = grid[y][x-1] + 1
	
	return new_grid

while any([any([c >= 4 for c in r]) for r in grid]):
	print()
	for r in grid: print(r)
	grid = topple(grid)

print()
for r in grid: print(r)

