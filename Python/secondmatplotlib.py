import matplotlib.pyplot as plt
import numpy as np

#t = np.arange(0.0, 2.0, 0.01)
#s = 1 + np.sin(2*np.pi*t)
#plt.plot(t, s)

#a = { 0: 1, 1: 3, 2: 5, 3: 7, 4: 9 }
a = { 6: 2, 7: 6, 8: 9, 0: 1 }
print(a)
plt.plot(*zip(*sorted(zip(a.keys(), a.values()))))

plt.xlabel('time (s)')
plt.ylabel('voltage (mV)')
plt.title('Test ;)')
plt.grid(True)
plt.savefig("test.png")
plt.show()

