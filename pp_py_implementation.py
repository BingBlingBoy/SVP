import math

lattice_basis = [[1.0, 2.0, 3.0], [3.0, 2.0, 1.0], [2.0, 1.0, 3.0]]
A = 100000

list_of_coeff = []
basis_norms_squared = []
list_of_vectors_v = []
v = None
u = None


def dot_product(vector_V, vector_U):
    result = 0

    for i in range(0, len(vector_V)):
        result = result + (vector_V[i] * vector_U[i])
    return result


def mu_calculation(vector_V, vector_U, i):
    dp = dot_product(vector_V, vector_U)
    norm = dot_product(vector_V, vector_V)

    if len(basis_norms_squared) <= i:
        basis_norms_squared.append(norm)
    return dp/(norm)


def scalar_vector_multiplication(scalar, vector):
    result = []

    for i in vector:
        result.append(scalar * float(i))

    return result


def vector_subtraction(vector1, vector2):
    result = []

    for i in range(0, len(vector1)):
        value = vector1[i] - vector2[i]
        result.append(value)

    return result


def vector_addition(vector1, vector2):
    result = []

    for i in range(0, len(vector1)):
        value = vector1[i] + vector2[i]
        result.append(value)

    return result


def mu_index_swap(list_of_coeff, i, j):
    for mu_swap in list_of_coeff:
        if mu_swap[0] == [j, i]:
            return mu_swap


def sum_of_mu(list_of_coeff, x):
    result = 0

    for mu in list_of_coeff:
        i = mu[0][0]
        j = mu[0][1]

        if j > i:
            mu_swapped = mu_index_swap(list_of_coeff, i, j)
            result = x[j-1] * mu_swapped

    return result


def sum_of_coeff(lower, upper):
    result = 0
    mu = 1

    while lower <= upper:
        for i in list_of_coeff:
            if i[0] == [lower+1, lower]:
                mu = i[1]
                break
        result += v[lower-1] * mu

        lower += 1

    return result


# Gram-Schmidt bit
for i in range(0, len(lattice_basis)):
    if i == 0:
        v = lattice_basis[i]
        list_of_vectors_v.append(v)
        continue

    u = lattice_basis[i]
    overall_proj = 0
    for j in range(0, len(list_of_vectors_v)):
        mu = mu_calculation(list_of_vectors_v[j], u, i)

        list_of_coeff.append(([i+1, j+1], mu))

        proj_u = scalar_vector_multiplication(mu, list_of_vectors_v[j])

        if overall_proj == 0:
            overall_proj = proj_u
        else:
            overall_proj = vector_addition(overall_proj, proj_u)

    v = vector_subtraction(u, overall_proj)

    list_of_vectors_v.append(v)


#norm = dot_product(lattice_basis[-1], lattice_basis[-1])
#basis_norms_squared.append(norm)

print(list_of_vectors_v)
print(list_of_coeff)
print(basis_norms_squared)


# SLP Enumeration
# x = [0 for i in range(0, len(lattice_basis))]
# l = 0
# s = []
# i = 1


# while i <= len(lattice_basis):
#     temp = x[i-1] + sum_of_mu(list_of_coeff, x)
#     l = (temp * temp) * basis_norms_squared[i-1]
#
#     if i == 1 and sum_of_ints(l, 1, len(lattice_basis)) <= A:
#         s.append(sum_of_ints(, 1, len(lattice_basis)))

# SE Enumeration
v = [1.0 if i == 0.0 else 0.0 for i in range(len(lattice_basis))]
l = [0.0 for i in range(len(lattice_basis))]
c = [0.0 for i in range(len(lattice_basis))]
Delta = [0.0 for i in range(len(lattice_basis))]
delta = [0.0 for i in range(len(lattice_basis))]
u = [0.0 for i in range(len(lattice_basis))]
s = 1.0
v_min = [1.0 if i == 0.0 else 0.0 for i in range(len(lattice_basis))]

k = 1
n = list_of_coeff[-1][0][0]
while k <= n-1:
    first_part = (v[k-1] + c[k-1])**2

    l[k-1] = l[k] + (first_part * (basis_norms_squared[k-1]**2))
    if l[k-1] < A:
        if k > 1:
            k -= 1
            c[k-1] = sum_of_coeff(k, n-1)
            v[k-1], u[k-1] = -(math.ceil(c[k-1])), -(math.ceil(c[k-1]))
            Delta[k-1] = 0.0

            if v[k-1] > -c[k-1]:
                delta[k-1] = -1
            else:
                delta[k-1] = 1
        else:
            A = l[k-1]
            v_min = v[k-1]
    else:
        k += 1
        s = max(s, k)
        if k < s:
            Delta[k-1] = -Delta[k-1]
        if Delta[k-1] * delta[k-1] >= 0:
            v[k-1] = u[k-1] + delta[k-1]

print(v_min)
