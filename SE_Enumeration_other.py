import math

lattice_basis = [[1.0, 2.0, 3.0], [3.0, 2.0, 1.0], [2.0, 1.0, 3.0]]
A = 10

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

def sum_of_coeff(lower, upper):
    result = 0


    while lower <= upper:
        if result == 0:
            result = scalar_vector_multiplication(v[lower-1], lattice_basis[lower-1])
        else:
            x = scalar_vector_multiplication(v[lower-1], lattice_basis[lower-1])
            result = vector_addition(result, x)
        
        lower += 1

    return result

def sum_of_mu(lower, upper):
    result = 0
    mu = 1

    while lower <= upper:
        for i in list_of_coeff:
            if i[0] == [lower, lower-1]:
                mu = i[1]
                break
        result += v[lower-1] * mu

        lower += 1

    return result




# Gram-Schmidt bit
def gram_schmidt(lattice_basis):
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
    v_list = []
    for i in range(0, len(list_of_vectors_v)):
        result = dot_product(list_of_vectors_v[i], list_of_vectors_v[i])
        v_list.append(result)

    print(v_list)

gram_schmidt(lattice_basis)

# LLL
delta = 0.75
k = 2
while k <= len(lattice_basis):
    for j in range(k-1, 1, -1):
        x = 0
        for i in list_of_coeff:
            if i[0] == [k, j]:
                x = i[1]
                break
        if abs(x) > 0.5:
            lattice_basis[k-1] = lattice_basis[k-1] - scalar_vector_multiplication(round(x), lattice_basis[j-1])
            gram_schmidt(lattice_basis)







v = [1.0 if i == 0.0 else 0.0 for i in range(len(lattice_basis))]
p = [0.0 for i in range(len(lattice_basis) + 1)]
c = [0.0 for i in range(len(lattice_basis))]
w = [0.0 for i in range(len(lattice_basis))]
k = 1 
last_nonzero = 1
R = A**2
while True:
    print((v[k-1] - c[k-1])**2)
    p[k-1] = p[k] + ((v[k-1] - c[k-1])**2 * v_list[k-1])
    
    if p[k-1] < R:
        if k == 1:
            R = p[k-1]
            s = sum_of_coeff(1,len(lattice_basis))
        else:
            k -= 1
            c[k-1] = -(sum_of_mu(k+1, len(lattice_basis)))
            v[k-1] = round(c[k-1])# nearest integer
            w[k-1] = 1
    else:
        k += 1
        if k == len(lattice_basis) + 1:
            print(s)
            break
        if k >= last_nonzero:
            last_nonzero = k
            v[k-1] = v[k-1] + 1
        else:
            if v[k-1] > c[k-1]:
                v[k-1] = v[k-1] - w[k-1]
            else:
                v[k-1] = v[k-1] + w[k-1]
            w[k-1] = w[k-1] + 1

