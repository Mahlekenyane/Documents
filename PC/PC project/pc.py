import numpy as np
import matplotlib.pyplot as plt
file = open("data2.txt","w")
mean = [0, 0]
cov = [[100, 0], [0, 100]]
x, y = np.random.multivariate_normal(mean, cov, 5000).T

for i in range(5000):
	x[i] = x[i]+25;
	y[i] = y[i]+25;
	file.write(str(x[i])+" "+str(y[i])+"\n")
	print x[i],y[i]

mean = [0, 0]
cov = [[100, 0], [0, 100]]
x1, y1 = np.random.multivariate_normal(mean, cov, 5000).T

for i in range(5000):
	x1[i] = x1[i]-25;
	y1[i] = y1[i]-25;
	file.write(str(x1[i])+" "+str(y1[i])+"\n")
	print x1[i],y1[i]
file.close()
plt.plot(x, y, 'x')
plt.axis('equal')
plt.show()
