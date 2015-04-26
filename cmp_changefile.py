from os import listdir
from os.path import isfile, join, abspath
from filecmp import cmp as diff
from itertools import combinations
from math import ceil

# Define path to output folder
OUTPUT_PATH = abspath(join(".", "output"))
# Holds the test cases, e.g. test_cases['changefile3'] = ('Lazy DFS', PATH)
test_cases = dict()

def get_test_case(basename):
	"""
	Extracts the changefile name and algorithm name
	from the basename of the file, e.g.
	changefile100Lazy Floyd-Warshall.out yields the output
	(changefile100, Lazy Floyd-Warshall)
	"""
	# Skip "changefile" in the search of an integer
	i = 10
	while True:
		try:
			# Check if we have reached the start
			# of the algorithm name
			int(basename[i])
		except ValueError:
			# We have reached the start of the
			# algorithm name
			break
		else:
			# We have not reached the start of
			# the algorithm name
			i += 1
	# e.g. return (changefile100, Lazy Floyd-Warshall)
	return (basename[:i], basename[i:-4])
	

# Categorize the test cases into:
#	1. changefile name
#	2. algorithm name
#   3. path to test file
for f in listdir(OUTPUT_PATH):
	path = join(OUTPUT_PATH, f)
	if isfile(path) and f.endswith('.out'):
		# Get the test_case and algorithm from basename
		test_case, algorithm = get_test_case(f)
		# Append (algorithm, path) into our test cases
		test_cases.setdefault(test_case, []).append((algorithm, path))

# Check if the files are the same for each changefile
for key in sorted(test_cases.keys(), key=lambda x: int(x[10:])):
	header = '=== Running on {:s} ==='.format(key)
	print header
	for x, y in combinations(test_cases[key], 2):
		if not diff(x[1], y[1]):
			print x[0], y[0], 'mismatch in', key
	print '='*int((len(header)-6.0)/2), 'DONE', '='*int(ceil((len(header)-6.0)/2)), '\n'
