#!/usr/bin/python
# -*- coding: utf-8 -*-
"""
	This software is implemented as part of the course Dynamic Algorithms 
	(Q4 2015) at Aarhus Univerity Denmark. 

	graph_jumper.py
	Creates J jumpers, each jumping a number of times around in a graph of size n
	
	If a jumper jumps between two nodes without an edge, a new edge is inserted,
	otherwise the existing edge is deleted. After all jumpers have jumped, then
	we ask how many transitive closures we currently have.

	Author: Martin Storgaard and Konstantinos Mampentzidis
"""
import sys
from random import choice, sample, seed

try:
	n = int(sys.argv[1])
	num_jumpers = int(sys.argv[2])
	num_jumps = int(sys.argv[3])
	assert num_jumpers < n
	seed(sys.argv[4])
except:
	print 'Usage: ./graph_jumper.py n num_jumper num_jumps seed\nAll arguments must be integers'
	sys.exit()
else:
	print 'init({:d})'.format(n)
	
class Node:
	"""
	A node containins an adjacency list and the index of it self
	"""
	def __init__(self, index):
		self.index = index
		self.edges = set()

# Create n nodes
nodes = [Node(i) for i in xrange(n)]

class Jumper:
	"""
	A jumper knowing where it currently are
	"""
	def __init__(self, start):
		"""
		Simply start at some node
		"""
		self.current_node = start
	
	def jump(self):
		"""
		Jumps to a random node (except for the current node). If there already was
		a path between the current node and the next node, a delete is issued,
		otherwise a insert is issued.
		"""
		while True:
			# Choose a random node different from the current node
			next = choice(nodes)
			if next != self.current_node:
				break
				
		if next in self.current_node.edges:
			print 'delete({:d},{:d})'.format(self.current_node.index, next.index)
			self.current_node.edges.remove(next)
		else:
			print 'insert({:d},{:d})'.format(self.current_node.index, next.index)
			self.current_node.edges.add(next)
		self.current_node = next

# Get num_jumpers jumpers all starting in different nodes
jumpers = [Jumper(s) for s in sample(nodes, num_jumpers)]

for i in xrange(num_jumps):
	for j in jumpers:
		j.jump()
	print 'transitive closure?'
