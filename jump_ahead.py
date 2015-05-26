#!/usr/bin/python2
# -*- coding: utf-8 -*-
"""
	This software is implemented as part of the course Dynamic Algorithms 
	(Q4 2015) at Aarhus Univerity Denmark. 

	jump_ahead.py


	Author: Martin Storgaard and Konstantinos Mampentzidis
"""
import sys
from random import choice, sample, seed

try:
	n = int(sys.argv[1])
	num_inserts_before = int(sys.argv[2])
	num_inserts_after = int(sys.argv[3])
	assert num_inserts_before + num_inserts_after < n*n-n+1
	seed(sys.argv[4])
except:
	print 'Usage: TODO'
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

nodes = tuple(Node(i) for i in range(n))

before = 0

while before < num_inserts_before:
	while True:
		i = choice(nodes)
		if len(i.edges) < n-1:
			break
	while True:
		j = choice(nodes)
		if i != j and not j in i.edges:
			break
	i.edges.add(j)
	before += 1

matrix = [[False]*n for i in xrange(n)]
for node in nodes:
	for e in node.edges:
		matrix[node.index][e.index] = True
for i in xrange(n):
	matrix[i][i] = True
	
print 'jump'
for row in matrix:
	for entry in row:
		print '1' if entry else '0',
	print ''
print 'transitive closure?'
after = 0
while after < num_inserts_after:
	while True:
		i = choice(nodes)
		if len(i.edges) < n-1:
			break
	while True:
		j = choice(nodes)
		if i != j and not j in i.edges:
			break
	i.edges.add(j)
	after += 1
	print "insert({:d},{:d})".format(i.index, j.index)
	print 'transitive closure?'
