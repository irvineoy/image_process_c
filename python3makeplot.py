from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
from matplotlib import cm
from matplotlib.ticker import LinearLocator, FormatStrFormatter
import numpy as np


fig = plt.figure()
ax = fig.gca(projection='3d')

# Make data.
x=[]
y=[]
z=[]
with open('neighborPix3D.txt', 'r') as f:
	data = f.read().split()
	i = 0
	while i<len(data):
		x.append(int(data[i]))
		i+=1
		y.append(int(data[i]))
		i+=1
		z.append(int(data[i]))
		i+=1
ax.view_init(elev=0, azim=90)

# X, Y = np.meshgrid(X, Y)
# R = np.sqrt(X**2 + Y**2)
# Z = np.sin(R)

# Plot the surface.
# surf = ax.plot_surface(x, y, z, cmap=cm.coolwarm,
#                        linewidth=0, antialiased=False)
ax.scatter(x, y, z, s=0.5)

# Customize the z axis.
ax.set_zlim(0, 255)
ax.zaxis.set_major_locator(LinearLocator(10))
ax.zaxis.set_major_formatter(FormatStrFormatter('%.02f'))
ax.set_zlabel('z(Brigntness value)')
# ax.set_ylabel('y(Brigntness value)')
ax.set_xlabel('x(Brigntness value)')
plt.title('Proximity pixels')
# Add a color bar which maps values to colors.
# fig.colorbar(surf, shrink=0.5, aspect=5)

plt.show()