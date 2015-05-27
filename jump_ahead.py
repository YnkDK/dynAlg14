#!/usr/bin/python2
# -*- coding: utf-8 -*-
"""
	This software is implemented as part of the course Dynamic Algorithms 
	(Q4 2015) at Aarhus Univerity Denmark. 

	jump_ahead.py n num_inserts_before num_inserts_after seed
	Generates a changefile using the following pattern: init, jump, insert.
	For example ./jump_ahead 3 3 3 42 yields:
	init(3)
	jump
	1 0 0 
	1 1 0 
	1 1 1 
	transitive closure?
	insert(0,1)
	transitive closure?
	insert(0,2)
	transitive closure?
	insert(1,2)
	transitive closure?

	Author: Martin Storgaard and Konstantinos Mampentzidis
"""
import sys
from random import seed, randint

def main():
	try:
		# Parse input parameters and throw appropriate error
		n = int(sys.argv[1])
		num_inserts_before = int(eval(sys.argv[2]))
		num_inserts_after = int(eval(sys.argv[3]))
	
		assert num_inserts_before + num_inserts_after < n*n-n+1,\
		'The total number of inserts must be smaller than n*n-n+1 = {:d}'.format(n*n-n+1)
	
		seed(sys.argv[4])
	except IndexError:
		print 'Usage: ./jump_ahead n num_inserts_before num_inserts_after seed'
		sys.exit()
	except AssertionError as e:
		print e
		sys.exit()
	except ValueError as e:
		print 'Argument 1,2 and 3 must be integers.', e.message.split(' ')[-1], 'is not an integer'
		sys.exit()
	else:
		print 'init({:d})'.format(n)
	
	before = 0

	matrix = [[False]*n for i in xrange(n)]
	for i in xrange(n):
		# Always have en edge between (i, i)
		matrix[i][i] = True
	
	while before < num_inserts_before:
		i, j = randint(0,n-1), randint(0,n-1)
		if matrix[i][j]:
			# We already have an edge between (i, j)
			continue
		# Set an edge between (i, j)
		matrix[i][j] = True
		before += 1

	# Print the jump command
	print 'jump'
	for row in matrix:
		for entry in row:
			print '1' if entry else '0',
		print ''
	print 'transitive closure?'

	after = 0
	while after < num_inserts_after:
		i, j = randint(0,n-1), randint(0,n-1)
		if matrix[i][j]:
			# We already have an edge between (i, j)
			continue
		# Set an edge between (i, j)
		matrix[i][j] = True
		after += 1
		# Print the insert command
		print "insert({:d},{:d})".format(i, j)
		print 'transitive closure?'
		
if __name__ == '__main__':
	if '-OO' not in sys.argv and not '--debug' in sys.argv:
		import os
		sys.argv.append('-OO')
		os.execl(sys.executable, sys.executable, '-OO', *sys.argv)
	else:
		main()
