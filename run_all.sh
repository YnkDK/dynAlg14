#!/bin/bash
INPUT=input/*
OUTPUT=output/*

rm $OUTPUT
for f in $INPUT
do
	echo "Running ./bin/main $f"
	./bin/main $f
done

echo "Running correctness"
./cmp_changefile.py

echo "Generating boxplots"
for reading in ins del query
do
	./stat.py $reading &
done
