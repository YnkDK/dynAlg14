#!/usr/bin/python
# -*- coding: utf-8 -*-
"""
	This software is implemented as part of the course Dynamic Algorithms 
	(Q4 2015) at Aarhus Univerity Denmark. 

	stat.py
	Used to create plots of execution times.
	
	Stronly inspired by http://stackoverflow.com/a/16598291/4620080

	Author: Martin Storgaard and Konstantinos Mampentzidis
"""
from pylab import plot, show, savefig, xlim, figure, \
                hold, ylim, legend, boxplot, setp, axes, \
                title, ylabel, xlabel, subplots_adjust, suptitle

from utils import get_test_cases, get_test_case
from sys import argv
import numpy as np
# Built-in colors: Blue, Green, Red,
# Cyan, Magenta, Yellow and Black
colors = "bgrcmyk"
# Number of algorithms to be plotted
num_algs = 2
#
if len(argv) != 2:
	print "Use ./stat.py [query | del | ins] to generate graphs"
	exit()
	
reading = argv[1]
plural = ""
if reading == "query":
	plural = "queries"
elif reading == "del":
	plural = "deletions"
elif reading == "ins":
	plural = "insertions"
else:
	print "Unknown reading. Must be either 'query', 'del' or 'ins'"
	exit()

suffix = "-{:s}.stat".format(reading)

# Get a dict of all test cases
test_cases = get_test_cases('./output/', suffix, get_test_case)

# function for setting the colors of the box plots pairs
def setBoxColors(bp):
	for i in xrange(num_algs):
		setp(bp['boxes'][i], color=colors[i])
		setp(bp['medians'][i], color=colors[i])
		
	c = 0
	for i in xrange(0, num_algs*2, 2):
		setp(bp['caps'][i], color=colors[c])
		setp(bp['caps'][i+1], color=colors[c])
		setp(bp['whiskers'][i], color=colors[c])
		setp(bp['whiskers'][i+1], color=colors[c])
		setp(bp['fliers'][i], color=colors[c])
		setp(bp['fliers'][i+1], color=colors[c])
		c += 1

summery = dict()
for key in sorted(test_cases.keys(), key=lambda x: int(x[10:])):
	##
	# Configure figure
	##
	fig = figure()
	ax = axes()
	hold(True)
	##
	# Configure loop variables
	##
	n = key[10:]
	data = []
	algs = []
	current_alg = ''
	max_time = -1
	min_time = float("inf")
	with open(test_cases[key], 'rb') as f:
		for line in f:
			alg, time = line.split(',')

			if alg != current_alg:
				current_alg = alg
				data.append([])
				algs.append(alg)
			# Convert from nanoseconds to milliseconds
			time = float(time.strip())/1000000
			# Keep track of min/max times
			# to scale the y-axis
			if time > max_time:
				max_time = time
			if time < min_time:
				min_time = time
			# Add data to current algorithm
			data[-1].append(time)
	
	# Count the number of algorithm
	num_algs = len(algs)
	##
	# Handle box plot
	##
	bp = boxplot(data, positions = range(1,num_algs+1), widths = 0.6)
	setBoxColors(bp)
	
	##
	# Handle axis
	##
	xlim(0,num_algs+1)
	ylim(min_time,max_time)
	mean_xticks = sum(range(1,num_algs+1)) / float(num_algs)
	xticks = [mean_xticks]
	
	ax.set_xticklabels(algs, rotation=45, fontsize=8)
	ax.set_xticks(range(1,len(algs)+1))

	##
	# Handle legends
	##
	ylabel("Time (milliseconds)")
	suptitle(
		"Execution time for {:d} {:s}/algorithm".format(len(data[0]), plural),
		fontsize=18
	)
	title("File: {:s}.txt".format(key), fontsize=10)
	subplots_adjust(bottom=0.2)
	
	
	for i in xrange(1, len(algs)+1):
		avg = np.average(data[i-1])
		plot([i], [avg],
			   color='w', marker='*', markeredgecolor='k')
		summery.setdefault(algs[i-1], []).append((int(n), avg))
           
	savefig('output/{:s}-{:s}.png'.format(n, reading), dpi=250)

##
# Handle summery
##
fig = figure()
ax = axes()
hold(True)
plots = []
i = 0
keys = summery.keys()
for key in keys:
	xs, ys = zip(*summery[key])
	tmp, = plot(xs, ys,
		   color=colors[i], marker='*', markeredgecolor='k')
	i += 1
	plots.append(tmp)
ylabel("Time (milliseconds)")
xlabel("n")
suptitle(
	"Avg. execution time for {:s}".format(plural),
	fontsize=18
)
legend(plots, keys, loc=2, fontsize=8)
savefig('output/summery-{:s}.png'.format(reading), dpi=250)
#show() # Uncomment to show all plots (or see in the output/ dir
