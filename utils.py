from os import listdir
from os.path import isfile, join

def get_test_case(basename):
	"""
	Extracts the changefile name 
	from the basename of the file, e.g.
	changefile100Lazy Floyd-Warshall.out yields the output
	(changefile100, None)
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
	return (basename[:i], None)	

def get_test_case_and_alg(basename):
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

def get_test_cases(output_path, suffix, test_case_splitter):
	test_cases = dict()	
	for f in listdir(output_path):
		path = join(output_path, f)
		if isfile(path) and f.endswith(suffix):
			# Get the test_case and algorithm from basename
			test_case, algorithm = test_case_splitter(f)
			# Append (algorithm, path) into our test cases
			if algorithm is None:
				test_cases[test_case] = path
			else:
				test_cases.setdefault(test_case, []).append((algorithm, path))
	return test_cases
