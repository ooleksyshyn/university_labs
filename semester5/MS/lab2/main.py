import numpy as np
from PIL import Image


def get_images():
    input_image = Image.open('x2.bmp')
    output_image = Image.open('y2.bmp')
    return input_image, output_image


def get_matrix(input_image, output_image):
    input_array = np.array(input_image)
    output_array = np.array(output_image)
    return input_array, output_array


def modulo(matrix):
    res = 0.0
    for arr in matrix:
        for x in arr:
            res += x ** 2

    return res


def mur_penrouse_formula(A, delta, size):
    return np.matmul(A.transpose(), np.linalg.inv(np.add(np.matmul(A, A.transpose()), (delta ** 2) * np.eye(size))))


def get_inverse_myr_penrouze(A, size):
    delta = 1
    current = mur_penrouse_formula(A, delta, size)
    epsilon = 0.001
    while True:
        prev = current
        delta /= 2
        current = mur_penrouse_formula(A, delta, size)
        if np.linalg.norm(np.subtract(current, prev)) < epsilon:
            break

    return current


def Z(A, A_plus):
    return np.subtract(np.eye(A[0].size), np.matmul(A_plus, A))


def R(A):
    return np.matmul(A, A.transpose())


def greviule(A, A_plus, a):
    curr_z = Z(A, A_plus)
    res = a.transpose() @ curr_z @ a
    if res[0] > 0.0001:
        divider = res
        result = A_plus - (curr_z @ a @ a.transpose() @ A_plus) / divider
        result = np.append(result, np.matmul(curr_z, a) / divider, axis=1)

    else:
        curr_r = R(A_plus)
        divider = 1 + a.transpose() @ curr_r @ a
        result = A_plus - (curr_r @ a @ a.transpose() @ A_plus) / divider
        result = np.append(result, np.matmul(curr_r, a) / divider, axis=1)

    return result


def get_inverse_grevile(A, size):
    matrix = np.array([A[0]])
    pseudo = A[1][np.newaxis, :].T
    a = A[1]
    for index in range(1, size):
        a = A[index]
        pseudo = greviule(matrix, pseudo, a[np.newaxis, :].T)
        matrix = np.vstack([matrix, a])

    return pseudo


def check_pseudo(A, A_plus):
    temp = np.linalg.pinv(A.transpose() @ A) @ A.transpose()
    if modulo(A_plus - temp) > 0.01:
        print("Error: pseudo is incorrect!")
    else:
        print("Pseudo matrix is correct!")


# def calculate_Z():
#    return np.subtract(np.ones((input_size_y, input_size_y)), np.matmul(input_array, pseudo_inverse))


def get_image(input_array, output_array, pseudo_inverse):
    operator = np.matmul(output_array, pseudo_inverse)
    result = np.matmul(operator, input_array)
    return Image.fromarray(np.uint8(result)).convert('RGB')


if __name__ == '__main__':
    print('LAB_2')
    input_image, output_image = get_images()
    input_matrix, output_matrix = get_matrix(input_image, output_image)
    input_size_x, input_size_y = input_image.size

    input_matrix = np.vstack([input_matrix, np.ones(input_size_x)])  # Додаємо рядок одиничок
    input_size_y += 1

    inverse_moore_penrose = get_inverse_myr_penrouze(input_matrix, input_size_y)
    check_pseudo(input_matrix, inverse_moore_penrose)
    image_moore_penrose = get_image(input_matrix, output_matrix, inverse_moore_penrose)
    image_moore_penrose.save('yy2.bmp')

    inverse_moore_grevile = get_inverse_grevile(input_matrix, input_size_y)
    check_pseudo(input_matrix, inverse_moore_grevile)
    image_moore_grevile = get_image(input_matrix, output_matrix, inverse_moore_grevile)
    image_moore_penrose.save('yyy2.bmp')
