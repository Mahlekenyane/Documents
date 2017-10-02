import random
import matplotlib.pyplot as plt
import matplotlib.patches as mpatches

def sample(a, n, m):
	b = range(n)
	c = range(m)
	ans = 0
	for i_1 in range(0, m):
		c[i_1] = 0
		ans += 1
	for i_2 in range(0, n):
		c[a[i_2]] += 1
		ans += 1
	for i_3 in range(1, m):
		c[i_3] += c[i_3-1]
		ans += 1
	for i_4 in range(n-1, -1, -1):
		indx = c[a[i_4]]
		if(indx > 0):
			b[indx-1] = a[i_4]
		c[a[i_4]] -= 1
		ans += 1
	return ans

key = [[],[],[],[],[],[],[],[],[],[]]
x_axis = []
my_max = 1000

for j in range(10, my_max, 10):
	print j
	for m in range(0, 10):
		my_arr_1 = random.sample(range(0, j*(m+1)), j)
		key[m].append(sample(my_arr_1, j, j*(m+1)))
	x_axis.append(j*10)

fig = plt.figure()
ax = fig.add_subplot(111)

ax.scatter(x_axis, key[0], s=20, c='#000000', marker='o')
ax.scatter(x_axis, key[1], s=20, c='#ff0000', marker='o')
ax.scatter(x_axis, key[2], s=20, c='#ff8800', marker='o')
ax.scatter(x_axis, key[3], s=20, c='#ffff00', marker='o')
ax.scatter(x_axis, key[4], s=20, c='#88ff00', marker='o')
ax.scatter(x_axis, key[5], s=20, c='#00ff00', marker='o')
ax.scatter(x_axis, key[6], s=20, c='#00ffff', marker='o')
ax.scatter(x_axis, key[7], s=20, c='#0000ff', marker='o')
ax.scatter(x_axis, key[8], s=20, c='#8800ff', marker='o')
ax.scatter(x_axis, key[9], s=20, c='#ff0088', marker='o')

b1 = mpatches.Patch(color='#000000', label='n == m')
b2 = mpatches.Patch(color='#ff0000', label='n == m/2')
b3 = mpatches.Patch(color='#ff8800', label='n == m/3')
b4 = mpatches.Patch(color='#ffff00', label='n == m/4')
b5 = mpatches.Patch(color='#88ff00', label='n == m/5')
b6 = mpatches.Patch(color='#00ff00', label='n == m/6')
b7 = mpatches.Patch(color='#00ffff', label='n == m/7')
b8 = mpatches.Patch(color='#0000ff', label='n == m/8')
b9 = mpatches.Patch(color='#8800ff', label='n == m/9')
b10 = mpatches.Patch(color='#ff0088', label='n == m/10')

plt.legend(handles=[b1,b2,b3,b4,b5,b6,b7,b8,b9,b10])
ax.plot([0, my_max], [0, 0], 'k-', lw=0)

plt.ylabel("Empirical complexity using array update as basic operation")
plt.xlabel("array range (m)")
plt.title("Empirical analysis on Algorithm 1")
plt.show()
