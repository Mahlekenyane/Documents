import time
import random
import matplotlib.pyplot as plt
import matplotlib.patches as mpatches
def lin_search(arr, k):
	found = False
	indx = 0
	while indx < len(arr) and not found:
		if arr[indx] == k:
			found = True
		indx+=1
	return indx-1

def time_elapsed(arr, k):
	t_0 = time.time()
	lin_search(arr, k)
	t_1 = time.time()
	return t_1 - t_0

worst = []
best = []
average = []
x_axis = []
for j in range(1000, 1000000, 1000):
	print j
	my_arr = random.sample(range(0,10*j), j)
	my_average = 0
	for i in range(0, j, j/10):
		my_average += time_elapsed(my_arr, my_arr[i])
	worst.append(time_elapsed(my_arr, my_arr[-1]))
	best.append(time_elapsed(my_arr, my_arr[0]))
	average.append(my_average/10)
	x_axis.append(j)

fig = plt.figure()
ax = fig.add_subplot(111)

ax.scatter(x_axis, best, s=20, c='#88ff00', marker='o')
ax.scatter(x_axis, worst, s=20, c='#0088ff', marker='o', label='Worst Case')
ax.scatter(x_axis, average, s=20, c='#ff0099', marker='o', label='Average Case')
bl = mpatches.Patch(color='#88ff00', label='Best Case')
wl = mpatches.Patch(color='#0088ff', label='Worst Case')
al = mpatches.Patch(color='#ff0099', label='Average Case')
plt.legend(handles=[bl, wl, al])
ax.plot([0, 1000000], [0, 0], 'k-', lw=0)

plt.ylabel("time elapsed vs array size")
plt.show()
