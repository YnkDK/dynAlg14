#!/usr/bin/python
# -*- coding: utf-8 -*-
from os.path import abspath, join
from filecmp import cmp as diff
from itertools import combinations
from math import ceil
from utils import get_test_cases, get_test_case_and_alg
# Define path to output folder
OUTPUT_PATH = abspath(join(".", "output"))
# Holds the test cases, e.g. test_cases['changefile3'] = ('Lazy DFS', PATH)
test_cases = get_test_cases(OUTPUT_PATH, '.out', get_test_case_and_alg)
print ''


	

# Categorize the test cases into:
#	1. changefile name
#	2. algorithm name
#   3. path to test file


# Check if the files are the same for each changefile
for key in sorted(test_cases.keys(), key=lambda x: int(x[10:])):
	body = []
	for x, y in combinations(test_cases[key], 2):
		if not diff(x[1], y[1]):
			body.append("{:s} and {:s} mismatches".format(x[0], y[0]))
			
	if len(body) > 0:
		width = len(max(body, key=len))
		# Prepare header to be printed
		hwidth = (width-11-len(key))/2.0
		left = "="*int(hwidth)
		right = "="*int(ceil(hwidth))
		print '{:s} ERROR IN {:s} {:s}'.format(left, key, right)
		# Print body
		print "\n".join(body)
		# Prepare footer
		print "="*width, "\n"
		
		
print "All output files have been compared!"
