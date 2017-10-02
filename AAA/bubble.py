import random
import matplotlib.pyplot as plt
import matplotlib.patches as mpatches

def my_sort_key(my_list, n):
	ans = 0
	for i in range(n-1, 0, -1):
		for j in range(0, i):
			ans += 1
			if my_list[j] > my_list[j+1]:
				my_list[j], my_list[j+1] = my_list[j+1], my_list[j]
	return ans


def my_sort_swp(my_list, n):
	ans = 0
	for i in range(n-1, 0, -1):
		for j in range(0, i):
			if my_list[j] > my_list[j+1]:
				my_list[j], my_list[j+1] = my_list[j+1], my_list[j]
				ans += 1
	return ans

key = []
swp = []
x_axis = []
my_max = 10000

for j in range(1000, my_max, 1000):
	print j
	my_arr_1 = random.sample(range(0,10*j), j)
	key.append(my_sort_key(my_arr_1, j))
	my_arr_2 = random.sample(range(0,10*j), j)
	swp.append(my_sort_swp(my_arr_2, j))
	x_axis.append(j)

fig = plt.figure()
ax = fig.add_subplot(111)

ax.scatter(x_axis, key, s=20, c='#88ff00', marker='o')
ax.scatter(x_axis, swp, s=20, c='#0088ff', marker='o')
bl = mpatches.Patch(color='#88ff00', label='Key Comparison')
wl = mpatches.Patch(color='#0088ff', label='Swop Comparison')
plt.legend(handles=[bl, wl])
ax.plot([0, my_max], [0, 0], 'k-', lw=0)

plt.ylabel("algorithm complexity vs array size")
plt.show()
