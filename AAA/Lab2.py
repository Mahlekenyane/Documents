import numpy
import math
import random
import matplotlib.pyplot as plt
import copy
threshold = 0
sigmoid = 1


def read_input2(x, t, my_string):
    my_file = open(my_string)
    my_input = my_file.read().split('\n')
    for line in my_input:
        my_list = line.split(' ')
        x_line = []
        t_line = []
        for i in range(len(my_list)):
            if "." in my_list[i]:
                x_line.append(float(my_list[i]))
            else:
                if my_list[i] == 'A':
                    t_line.append(1)
                    t_line.append(0)
                    t_line.append(0)
                elif my_list[i] == 'B':
                    t_line.append(0)
                    t_line.append(1)
                    t_line.append(0)
                elif my_list[i] == 'C':
                    t_line.append(0)
                    t_line.append(0)
                    t_line.append(1)
        x_line.append(-1)
        x.append(x_line)
        t.append(t_line)
    return


def read_input(x, t, my_string):
    my_file = open(my_string)
    my_input = my_file.read().split('\n')
    for line in my_input:
        my_list = line.split(' ')
        x_line = []
        t_line = []
        for i in range(len(my_list)):
            if "." in my_list[i]:
                x_line.append(float(my_list[i]))
            else:
                t_line.append(int(my_list[i]))
        x_line.append(-1)
        x.append(x_line)
        t.append(t_line)
    return


def thr(h):
    if h > 0:
        return 1
    else:
        return 0


def g(h):
    return 1/(1 + math.exp(-1 * h))


def percept(x, w, u, a, fun):  # assume x is augmented
    h = numpy.dot(x, w)  # assume a is already augmented
    if len(a) != 0:
        for i in range(len(h)):
            a[i] = g(h[i])
    else:
        for i in range(len(h)):
            a.append(g(h[i]))
        a.append(-1)
    y1 = numpy.dot(a, u)
    y2 = []
    if fun == sigmoid:
        for i in y1:
            y2.append(g(i))
    else:
        for i in y1:
            y2.append(thr(i))
    return y2


def error(t, y):
    my_error = 0
    for i in range(len(t)):
        my_error += (t[i] - y[i]) ** 2
    return 0.5 * my_error


def set_error(t, y):
    total_error = 0
    for i in range(len(t)):
        total_error += error(t[i], y[i])
    return total_error


def delta_out(t, y):
    d0 = []
    for i in range(len(t)):
        d0.append(y[i] * (1 - y[i]) * (t[i] - y[i]))
    return d0


def delta_h(a, u, d0):  # assume a is augmented
    dh = []
    for i in range(len(a) - 1):  # length of augmented a == width of u == k+1, but dh is used for w, k
        my_sum = 0
        for j in range(len(d0)):
            my_sum += d0[j] * u[i][j]
        dh.append(a[i] * (1 - a[i]) * my_sum)
    return dh


def update_weight(u, w, d0, dh, a, x, n):
    for k in range(len(u)):
        for j in range(len(u[0])):
            u[k][j] += n * d0[j] * a[k]

    for i in range(len(w)):
        for k in range(len(w[0])):
            w[i][k] += n * dh[k] * x[i]


def back_propagation(x, w, u, t, n):
    my_list1 = list(range(len(t))) # list of random numbers
    my_list2 = list(range(3*len(t)/4)) # first 75% also random
    a = []
    final_t = len(t) * len(t[0])
    final_v = len(t) * len(t[0])
    my_error_t = []
    my_error_v = []
    best_w = []
    best_u = []
    x_axis = range(0, 8000)
    random.shuffle(my_list1) # shuffle once to keep v constant
    for d in range(8000):
        random.shuffle(my_list2) # pick random number between 0 and 75%
        total_error = 0
        if d == 4000:
            n = 0.001
        for j in my_list2:
            i = my_list1[j]
            y = percept(x[i], w, u, a, sigmoid)
            total_error += error(t[i], y)
            d0 = delta_out(t[i], y)
            dh = delta_h(a, u, d0)
            update_weight(u, w, d0, dh, a, x[i], n)
        error_t = total_error
        my_error_t.append(total_error)
        total_error = 0
        for k in range(3 * len(t)/4, len(t), 1):
            l = my_list1[k]
            y = percept(x[l], w, u, a, sigmoid)
            total_error += error(t[l], y)
        error_v = total_error
        my_error_v.append(total_error)
        if final_v + final_t > error_v + error_t:
            final_v = error_v
            final_t = error_t
            best_w = copy.deepcopy(w)
            best_u = copy.deepcopy(u)
    y3 = []
    for i1 in range(len(t)):
        y3.append(percept(x[i1], best_w, best_u, a, threshold))
    print set_error(t, y3)

    # fig = plt.figure()
    # ax = fig.add_subplot(111)

    # ax.scatter(x_axis, my_error_t, s=10, c='r', marker='o', label='Training Set')
    # ax.scatter(x_axis, my_error_v, s=10, c='b', marker='o', label='Validation Set')
    # ax.plot([0, 8000], [0, 0], 'k-', lw=2)

    # plt.ylabel("Error vs iteration")
    # plt.show()

    print "Weight W:"
    for w_row in best_w:
        print w_row
    print "\nWeight U:"
    for u_row in best_u:
        print u_row
    print "Final Training Error: "+str(final_t)
    print "Final Validation Error: "+str(final_v)


x1 = []
t1 = []
read_input(x1, t1, "H2Dataset1.txt")
k1 = 8
# w is k1 by len(x1)
w1 = []
u1 = []
for r in range(len(x1[0])):
    w1_row = []
    for s in range(k1):
        w1_row.append(numpy.random.uniform(-1.0, 1.0))
    w1.append(w1_row)
for v in range(k1 + 1):
    u1_row = []
    for z in range(len(t1[0])):
        u1_row.append(numpy.random.uniform(-1.0, 1.0))
    u1.append(u1_row)
back_propagation(x1, w1, u1, t1, 0.1)

t2 = []
x2 = []
read_input2(x2, t2, "H2Dataset2.txt")
k2 = 12
w2 = []
u2 = []
for r in range(len(x2[0])):
    w2_row = []
    for s in range(k2):
        w2_row.append(numpy.random.uniform(-1.0, 1.0))
    w2.append(w2_row)
for v in range(k2 + 1):
    u2_row = []
    for z in range(len(t2[0])):
        u2_row.append(numpy.random.uniform(-1.0, 1.0))
    u2.append(u2_row)
back_propagation(x2, w2, u2, t2, 0.1)
