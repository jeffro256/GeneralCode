import matplotlib.pyplot as plt
import numpy as np

minx = -10
maxx = 10
numx = 21
miny = -10
maxy = 10
numy = 21

arr_scale = 3

diffeq = lambda x, y: x / y

dx = (maxx - minx) / (numx - 1)
xvals = np.linspace(minx, maxx, numx)
yvals = np.linspace(miny, maxy, numy)
diff_data = [] # list of data points (x, y, u, v)

for x in xvals:
	for y in yvals:
		try:
			m = diffeq(x, y)
			data_pt = (x, y, dx * arr_scale, m * dx * arr_scale)
			diff_data.append(data_pt)
		except:
			pass

x, y, u, v = zip(*diff_data)

print(u)

plt.quiver(x, y, u, v,  units='x')
plt.show()




