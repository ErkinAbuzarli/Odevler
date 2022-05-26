from xmlrpc.client import MAXINT
from copy import deepcopy  



def min_of_row(matrix, index):
    return min(matrix[index])

def min_of_column(matrix, index):
    minimum = MAXINT
    for row in matrix:
        if row[index] < minimum:
            minimum = row[index]
    return minimum

def substract_min_from_row_elements(matrix, index, minimum):
    for i in range(len(matrix[index])):
        matrix[index][i] -= minimum
    return matrix

def substract_min_from_column_elements(matrix, index, minimum):
    for row in matrix:
        row[index] -= minimum
    return matrix

def is_all_elements_0(arr):
    for element in arr:
        if element != 0:
            return False
    return True

def is_all_elements_minus_1(matrix):
    for row in matrix:
        for element in row:
            if element != -1:
                return False
    
    return True

def is_matrix_optimized(matrix):   
    zeros_array = []
    start_len = len(matrix)
    operations = []

    while 1:
        l = len(matrix[0])
        for i in range(l):
            zeros_array.append(number_of_zeros_in_column(matrix, i))

        l = len(matrix)

        for i in range(l):
            zeros_array.append(number_of_zeros_in_row(matrix, i))

        if is_all_elements_0(zeros_array):
            break
        
        max_element_index = zeros_array.index(max(zeros_array))
        
        len_of_columns = len(zeros_array) - l
        if max_element_index >= len_of_columns:
            operations.append(("r", max_element_index - len_of_columns))
            delete_row(matrix, max_element_index - len_of_columns) 
        else:
            operations.append(("c", max_element_index))
            delete_column(matrix, max_element_index)

        zeros_array = []

    
    if len(operations) == start_len:
        return True, -1
    
    return matrix, operations

def number_of_zeros_in_row(matrix, index):
    zeros = 0
    for element in matrix[index]:
        if element == 0:
            zeros += 1
    return zeros
    
def number_of_zeros_in_column(matrix, index):
    zeros = 0
    for row in matrix:
        if row[index] == 0:
            zeros += 1
    return zeros

def delete_row(matrix, index):
    del matrix[index]
    return matrix

def delete_column(matrix, index):
    for row in matrix:
        del row[index]
    return matrix

def create_zeros(matrix):
    l = len(matrix)

    for i in range(l):
        m = min_of_row(matrix, i)
        matrix = substract_min_from_row_elements(matrix, i, m)

    
    l = len(matrix[0])

    for i in range(l):
        m = min_of_column(matrix, i)
        matrix = substract_min_from_column_elements(matrix, i, m)
        
    return matrix

def min_of_rest(matrix):
    all_elements = []
    for row in matrix:
        for element in row:
            if element >= 0:
                all_elements.append(element)

    return min(all_elements)

def seperate_operations(operations):
    row_operations = []
    column_operations = []

    for operation in operations:
        if operation[0] == "r":
            row_operations.append(operation[1])
        column_operations.append(operation[1])

    return row_operations, column_operations

def optimize_matrix(matrix, minimum, operations):
    
    row_operations, column_operations = seperate_operations(operations)

    for i, row in enumerate(matrix):
        if i in row_operations:
            continue
        for j, element in enumerate(row):
            if j in column_operations:
                continue
            if matrix[i][j] >= 0:
                matrix[i][j] -= minimum
    return matrix


def get_fully_optimized_matrix(matrix):
    optimized_matrix = create_zeros(deepcopy(matrix))

    rest_of_matrix, operations = is_matrix_optimized(deepcopy(optimized_matrix))

    while operations != -1:
        optimized_matrix = optimize_matrix(deepcopy(optimized_matrix), min_of_rest(rest_of_matrix), operations)
        rest_of_matrix, operations = is_matrix_optimized(deepcopy(optimized_matrix))

    return optimized_matrix

def except_column(matrix, index):
    for row in matrix:
        row[index] = -1

def except_row(matrix, index):
    for i in range(len(matrix[index])):
        matrix[index][i] = -1


def meet_demand_as_supply_can(matrix, demand, supply, demand_index, supply_index):
    transport = ()
    diff = demand[demand_index] - supply[supply_index]

    if diff < 0:
        supply[supply_index] = -1 * diff
        transport = (supply_index, demand_index, demand[demand_index])
        except_column(matrix, demand_index)
        demand[demand_index] = 0
    else:
        demand[demand_index] = diff
        transport = (supply_index, demand_index, supply[supply_index])
        except_row(matrix, supply_index)
        supply[supply_index] = 0
    
    return demand, supply, transport
    

def find_transportations(optimized_matrix, demand, supply, transports):
    max_demand = -1
    max_demand_index = -1

    for i, row in enumerate(optimized_matrix):

        for j, element in enumerate(row):
            if element == 0 and demand[j] > max_demand:
                max_demand = demand[j]
                max_demand_index = j
        if max_demand_index != -1:
            demand, supply, transport = meet_demand_as_supply_can(optimized_matrix, demand, supply,max_demand_index,i)
            transports.append(transport)
        max_demand = -1
        max_demand_index = -1

    return demand, supply, transports


def get_all_transports(optimized_matrix, demand, supply):
    transports = []

    while not is_all_elements_minus_1(optimized_matrix):
        optimized_matrix = optimize_matrix(deepcopy(optimized_matrix), min_of_rest(optimized_matrix), [])
        demand, supply, transports = find_transportations(optimized_matrix, demand, supply, transports)

    return transports

def total_cost(matrix, transports):
    cost = 0
    for transport in transports:
        cost += matrix[transport[0]][transport[1]] * transport[2]

    return cost

##############################################################3



# Örnek 1 (dersde işlenen)

matrix = [[6, 8, 10], [7, 11, 11], [4, 5, 12]]
demand = [200, 100, 300]
supply = [150, 175, 275]

# Örnek 2

#matrix = [[5,15,16,40],[35,10,25,18],[20,30,6,45],[40,20,46,7]]
#demand = [10, 12, 15, 9]
#supply = [15, 6, 14, 11]

optimized_matrix = get_fully_optimized_matrix(deepcopy(matrix))
transports = get_all_transports(optimized_matrix, demand, supply)

print(transports)
print(total_cost(matrix, transports))
