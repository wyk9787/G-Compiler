#!/bin/bash

# # set up diff.txt
result="./test/diff.txt"
rm -f "$result"
touch "$result"
chmod 755 "$result"

# files=find . -name "*.src"

# find each test file ending with .in
for filename in ./test/**/*.src; do
  parse_output="${filename%.src}.parse.out"
  output="${filename%.src}.out"
  if [[ $1 = "output" ]]
  then
    ./build/apps/compiler -f "$filename" -p > "$parse_output"
    ./build/apps/compiler -f "$filename" &> "$output"
  else
    echo "$filename"
    diff <(./build/apps/compiler -f "$filename" -p) "$parse_output" >> "$result"
    diff <(./build/apps/compiler -f "$filename" 2>&1) "$output" >> "$result"
  fi
done

if [ ! -s "$result" ]
then
	exit 0
else
	printf "Tests failed. Check ./test/diff.txt for details.\n"
	exit 1
fi
