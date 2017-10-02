import numpy


def read_iris(x, t, my_string):
    my_file = open(my_string)
    my_input = my_file.read().split('\n')
    for l in range(150):
        line = my_input[l]
        my_list = line.split(',')
        x_line = []
        for i in range(len(my_list)):
            if "." in my_list[i]:
                x_line.append(float(my_list[i]))
            else:
                t.append(my_list[i])
        x.append(x_line)
    normalize_input(x)
    return


def read_input(x, my_string):
    my_file = open(my_string)
    my_input = my_file.read().split('\n')
    for l in range(200):
        line = my_input[l]
        my_list = line.split(' ')
        x_line = []
        for i in range(len(my_list)):
            if "." in my_list[i]:
                x_line.append(float(my_list[i]))
        x.append(x_line)
    normalize_input(x)
    return


def populate_u(my_u, my_m, my_k):
    for p1 in range(my_k):
        u_line = []
        for p2 in range(my_m):
            u_line.append(numpy.random.uniform(0.0, 1.0))
        my_u.append(u_line)
    return


def normalize_input(data_set):
    for n1 in range(len(data_set[0])):
        my_min = data_set[0][n1]
        my_max = data_set[0][n1]
        for n2 in range(len(data_set)):
            if my_min < data_set[n2][n1]:
                my_min = data_set[n2][n1]
            if my_max > data_set[n2][n1]:
                my_max = data_set[n2][n1]
        for n3 in range(len(data_set)):
            data_set[n3][n1] = (data_set[n3][n1] - my_min) / (my_max - my_min)
    return


def euclid_diff(a, b):
    d = 0
    for i in range(len(a)):
        d += (a[i] - b[i]) ** 2
    return d


def k_means(x, my_u):
    my_error = 0
    for n in range(1000):
        u_sizes = [0] * len(my_u)   # list to store size
        u_update = []
        for _ in range(len(my_u)):
            u_update.append([0] * len(my_u[0]))  # list to store sum
        my_error = 0
        for j in range(len(x)):
            indx = 0
            euclid_d = euclid_diff(x[j], my_u[0])
            for i in range(len(my_u)):
                euclid_n = euclid_diff(x[j], my_u[i])
                if euclid_d > euclid_n:
                    euclid_d = euclid_n
                    indx = i
            u_sizes[indx] += 1
            my_error += euclid_d
            for f in range(len(x[0])):
                u_update[indx][f] += x[j][f]
        for j1 in range(len(my_u)):
            if u_sizes[j1] > 0:
                for j2 in range(len(my_u[0])):
                    my_u[j1][j2] = u_update[j1][j2]/u_sizes[j1]
    print my_error
    return


def online_k_means(x, my_u):
    # my_error = 0
    for n in range(1000):
        # my_error = 0
        nu = 0.2/(n+2)
        for j in range(len(x)):
            indx = 0
            euclid_d = euclid_diff(x[j], my_u[0])
            for i in range(len(my_u)):
                euclid_n = euclid_diff(x[j], my_u[i])
                if euclid_d > euclid_n:
                    euclid_d = euclid_n
                    indx = i
            # my_error += euclid_d
            for f in range(len(x[0])):
                my_u[indx][f] += nu*(x[j][f] - my_u[indx][f])
    print sum_of_squares(x, my_u)
    return


def print_results(my_matrix, k_val):
    my_colors = [["\033[1;31m","\033[0m"],["\033[1;33m","\033[0m"],["\033[1;36m","\033[0m"],["\033[1;34m","\033[0m"],["\033[1;35m","\033[0m"]]
    for my_list1 in my_matrix:
        print my_colors[k_val-2][0]+str(my_list1)+my_colors[k_val-2][1]
    return


def h3_dataset_1():
    input1 = []
    read_input(input1, "H3DataSet1.txt")
    m = len(input1[0])
    for k in range(2, 7, 1):
        u = []
        populate_u(u, m, k)
        k_means(input1, u)
        print_results(u, k)
    print "____________________________________________________________________"
    return


def iris():
    input2 = []
    target = []
    read_iris(input2, target, "iris.data")
    m2 = len(input2[0])
    for k2 in range(2, 7, 1):
        u2 = []
        populate_u(u2, m2, k2)
        k_means(input2, u2)
        print_results(u2, k2)
    return


def sum_of_squares(x, my_u):
    my_error = 0
    for j in range(len(x)):
        euclid_d = euclid_diff(x[j], my_u[0])
        for i in range(len(my_u)):
            euclid_n = euclid_diff(x[j], my_u[i])
            if euclid_d > euclid_n:
                euclid_d = euclid_n
        my_error += euclid_d
    return my_error


h3_dataset_1()
iris()
