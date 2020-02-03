#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++#
#| code for implementing tsp																	   |
#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++#

# Some important notes:
import sys
import copy # copy module for copying nested lists
import random
import math
import numpy
from scipy.special import expit
import statistics

def process_input(input_file):
	f = open(input_file, "r+")
	i = 0
	mode = next(f)
	n = int(next(f)) 
	cities = []
	adjacency_matrix = []
	for rows in f:
		coordinates = []
		distances = []
		rows = rows.split()
		for cols in rows:
			if i<n:
				coordinates.append(float(cols))
			else:
				distances.append(float(cols))
		if i<n:
			cities.append(coordinates)
		else:
			adjacency_matrix.append(distances)
		i+=1
	return mode, n ,cities, adjacency_matrix
def swap_elements(cycle, index):
	temp = cycle[index]
	cycle[index]=cycle[index+1]
	cycle[index+1]=temp
def generate_neighbours(cycle, n):
	neighbours = []
	for index in range(0,n-1):
		cycle_copy = copy.deepcopy(cycle)
		swap_elements(cycle_copy, index)
		neighbours.append(cycle_copy)
	return neighbours
def create_cycle(n):
	cyc = numpy.random.permutation(n)
	# print(cyc)
	# return list(range(0, n))
	return cyc
def cost_of_cycle(cycle, n, adjacency_matrix):
	cost = 0
	for i in range(0, n-1):
		cost = cost + adjacency_matrix[cycle[i]][cycle[i+1]]
	cost = cost + adjacency_matrix[cycle[n-1]][cycle[0]]
	return cost
def cost_of_neighbours(neighbours, n, adjacency_matrix):
	neighbour_cost = []
	for i in neighbours:
		neighbour_cost.append(cost_of_cycle(i, n, adjacency_matrix))
	return neighbour_cost

def find_fitness(neighbours, n, adjacency_matrix):
	fitness_matrix = []
	total_fitness = 0
	for i in neighbours:
		fitness_matrix.append(cost_of_cycle(i, n, adjacency_matrix))
		total_fitness = total_fitness + cost_of_cycle(i, n, adjacency_matrix)
	for i in range(0, len(fitness_matrix)):
		fitness_matrix[i] = fitness_matrix[i]/total_fitness
	for i in range(1, len(fitness_matrix)):
		fitness_matrix[i]=fitness_matrix[i]+fitness_matrix[i-1]
	fitness_matrix[0]=0
	return fitness_matrix

def select_parents(fitness_matrix):
	new_population = []
	index_matrix = []
	for k in range(0, int(len(fitness_matrix)/2)):
		rand_num = random.random()
		for i in range(0, len(fitness_matrix)-1):
			if rand_num>=fitness_matrix[i] and rand_num<fitness_matrix[i+1]:
				parent1=i
				parent2=i+1
				break
		new_population.append(parent1)
		new_population.append(parent2)
		index_matrix.append(i)
	return new_population, index_matrix

def do_crossover(new_population, index_matrix, n):
	l = 0
	m = 0
	for k in range(0,len(new_population)):
		if m==n:
			break
		rand1 = int(random.random()*n)
		rand2 = int(random.random()*n)
		child1 = []
		child2 = []
		part1 = []
		count1 = n-index_matrix[l]
		count2 = n-index_matrix[l]+1
		if count1>n:
			count1 = n
		if count2>n:
			count2 = n
		if count1<0:
			count1 = 0
		if count2<n:
			count2 = 0
		for i in range(0, n):
			if count1 == n:
				count1=0
			if count2 == n:
				count2=0
			temp1 = new_population[k]
			temp2 = new_population[k+1]
			child1.append(temp1[count1])
			child2.append(temp2[count2])
			count1+=1
			count2+=1
		new_population[k]=child1
		new_population[k+1]=child2
		m+=2
		l+=1
	return new_population

def mutate(new_population, n):
	for i in range(0, len(new_population)):
		for k in range(0,int(n/10)):
			rand1 = int(random.random()*n)
			rand2 = int(random.random()*n)
			temp1 = new_population[i][rand1]
			new_population[i][rand1] = new_population[i][rand2]
			new_population[i][rand2] = temp1
	return new_population

def genetic_algorithm(cycle, neighbours, n, adjacency_matrix):
	neighbours.append(cycle)
	generation = 0
	while generation<100:
		# print("Generation: ", generation)
		fitness_matrix = find_fitness(neighbours, n, adjacency_matrix)
		min_path = neighbours[0]
		min_path_cost = cost_of_cycle(neighbours[0], n, adjacency_matrix)
		for i in range(0, len(neighbours)):
			if cost_of_cycle(neighbours[i], n, adjacency_matrix)<cost_of_cycle(min_path, n, adjacency_matrix):
				min_path = neighbours[i]
				min_path_cost = cost_of_cycle(neighbours[i], n, adjacency_matrix)
		new_population, index_matrix = select_parents(fitness_matrix)
		for i in range(0,len(new_population)):
			new_population[i]=neighbours[new_population[i]]
		new_population = do_crossover(new_population, index_matrix, n)
		mutated_population = mutate(new_population, n)
		neighbours = mutated_population
		generation+=1
	return min_path, min_path_cost

def do_simulated_annealing(cycle, adjacency_matrix, n):
	t = 10000
	# t=0.0001
	coolingRate1 = 0.005
	coolingRate2 = 0.025
	coolingRate3 = 0.050
	best_path = copy.deepcopy(cycle)
	while t>0.01:
	# while t<10000:
		# print(t, cost_of_cycle(cycle, n, adjacency_matrix), cost_of_cycle(best_path, n, adjacency_matrix))
		if cost_of_cycle(cycle, n, adjacency_matrix) <= cost_of_cycle(best_path, n, adjacency_matrix):
			best_path = cycle
			# cost_of_cycle(best_path, n, adjacency_matrix)
		rand_neighbour = int(n*random.random())%(n-1)
		# if rand_neighbour > n-2:
		# 	rand_neighbour = n-2
		new_neighbour = copy.deepcopy(cycle)
		swap_elements(new_neighbour, rand_neighbour)
		# print(new_neighbour)
		delta_e = cost_of_cycle(cycle, n, adjacency_matrix) - cost_of_cycle(new_neighbour, n, adjacency_matrix)
		probability = expit(delta_e)
		# probability = 1/(1+(numpy.float128(math.exp(-delta_e/t))))
		# print(probability)
		if probability >= random.random():
			cycle = new_neighbour
		t=t-1 #scheme1
		# t=t*(1-coolingRate1) #scheme2
		# t=t*(1-coolingRate2) #scheme3
		# t=t*(1-coolingRate3) #scheme4
		# t=t/2 #scheme5
	return best_path
def main():
	mode, n, cities, adjacency_matrix = process_input(sys.argv[1])
	cycle = create_cycle(n)
	cycle2 = copy.deepcopy(cycle)
	neighbours = generate_neighbours(cycle,n)
	neighbours2 = copy.deepcopy(neighbours)
	# simulated annealing
	neighbour_cost = cost_of_neighbours(neighbours, n, adjacency_matrix)
	min_cost_path = do_simulated_annealing(cycle, adjacency_matrix, n) #
	print("Simulated Annealing")
	print(cost_of_cycle(min_cost_path, n, adjacency_matrix)) #
	for i in min_cost_path: #
		print(cities[i]) #
	# print(min_cost_path)
	print("\n")
	###################################
	# genetic algorithm
	gen_path, gen_cost = genetic_algorithm(cycle2, neighbours2, n, adjacency_matrix)
	print("Genetic Algorithm")
	print(gen_cost)
	for i in gen_path: #
		print(cities[i]) #
	###################################

main()
