import matplotlib.pyplot as pl
# from mpl_toolkits.mplot3d import axes3d, Axes3D 
# import numpy as np

data = []
x = []
y = []
z = []

def histogram():
	with open('data.txt', 'r') as f:
		read_data = f.read()
		data = read_data.split()
	i = 0
	while i<len(data):
		x.append(int(data[i]))
		i += 1
		y.append(int(data[i]))
		i += 1
	pl.plot(x,y)
	pl.show()


def neighborPix():
	with open('neighborPix.txt', 'r') as f:
		read_data = f.read()
		data = read_data.split()
	i = 0
	while i<len(data):
		x.append(int(data[i]))
		i += 1
		y.append(int(data[i]))
		i += 1
	pl.scatter(x, y, marker = '.', color = 'k', label='1', s = 3)
	pl.axis([0, 255, 0, 255])  
	pl.show()


def histogram3D():
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
	fig = pl.figure()
	ax = fig.add_subplot(111, projection='3d')
	ax.scatter(x, y, z, s=0.5)
	ax.set_zlabel('Z')
	ax.set_ylabel('Y')
	ax.set_xlabel('X')
	ax.view_init(elev=10., azim=11)
	pl.show()

if __name__ == "__main__":
	# choice = input('neighborPix = 1 And histogram = 2 And histogram3D = 3: ')
	choice = 2
	if choice == 1:
		histogram()		
	elif choice == 2:
		neighborPix()
	elif choice == 3:
		histogram3D()

	# set view