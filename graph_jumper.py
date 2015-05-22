#!/usr/bin/python2
# -*- coding: utf-8 -*-
"""
	This software is implemented as part of the course Dynamic Algorithms 
	(Q4 2015) at Aarhus Univerity Denmark. 

	graph_jumper.py
	Creates J jumpers, each jumping a number of times around in a graph of size n,
	i.e. there are J*(number of jumps) inserts/deletes and J queries.
	
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
		If the current node contains a edge to any other node, then the jumper uses that
		edge (delete), otherwise a random jump to any other node is issued (insert)
		"""
		try:
			# Hide the tracks if possible
			next = self.current_node.edges.pop()
		except KeyError:
			# No paths from here, make a new one
			action = 'insert'
			# No track to hide, try jump to another node
			while True:
				# Choose a random node different from the current node
				next = choice(nodes)
				if next != self.current_node:
					break
				
			self.current_node.edges.add(next)
		else:
			# We could hide some tracks
			action = 'delete'
		# Print the action
		print "{:s}({:d},{:d})".format(action, self.current_node.index, next.index)
		self.current_node = next

# Create n nodes
nodes = [Node(i) for i in xrange(n)]
# Get num_jumpers jumpers all starting in different nodes
jumpers = [Jumper(s) for s in sample(nodes, num_jumpers)]

for i in xrange(num_jumps):
	for j in jumpers:
		j.jump()
	print 'transitive closure?'
