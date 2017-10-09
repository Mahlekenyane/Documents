import numpy as np
import matplotlib.pyplot as plt
import sys
num_points = input("Enter a number of points: ") # number of points in each cluster
num_clusters = input("Enter a number of clusters: ")
cluster_means = []
for i in range(num_clusters):
	c_i = raw_input("Enter cluster mean of cluster "+str(i)+": ")
	m_i = map(float, c_i.split())
	cluster_means.append(m_i)
print cluster_means
c_v = raw_input("Enter list of variance: ")
covarience = map(float, c_v.split())
print covarience
file = open("data2.txt","w")
mean = [25, 25]
cov = [[1, 0], [0, 1]]
x, y = np.random.multivariate_normal(mean, cov, 5000).T

for i in range(5000):
	x[i] = x[i]
	y[i] = y[i]
	file.write(str(x[i])+" "+str(y[i])+"\n")
	# print x[i],y[i]

mean = [0, 0]
cov = [[1, 0], [0, 1]]
x1, y1 = np.random.multivariate_normal(mean, cov, 5000).T

for i in range(5000):
	x1[i] = x1[i]
	y1[i] = y1[i]
	file.write(str(x1[i])+" "+str(y1[i])+"\n")
	# print x1[i],y1[i]
file.close()
plt.plot(x, y, 'x')
plt.axis('equal')
plt.show()
