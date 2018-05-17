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
  then # generate outputs (after manually checking every single output)
    ./build/apps/compiler -f "$filename" &> "$output"
  else
    echo "$filename"
    diff <(./build/apps/compiler -f "$filename" 2>&1) "$output" >> "$result"
  fi
done

if [[ $1 != "output" ]]
then
  for filename in ./test/translate_test/*.src; do
    c_file="${filename%.src}.c"
    c_output="${filename%.src}"
    output="${filename%.src}.out"
    echo "translate" "$filename" "and compare results"

    # translate the program into c file
    ./build/apps/compiler -f "$filename" -t "$c_file" > /dev/null
    # compile the C program
    gcc "$c_file" -o "$c_output" -w
    # Compare the differnece
    diff <(./"$c_output" 2>&1) "$output" >> "$result"
  done
fi

if [ ! -s "$result" ]
then
	exit 0
else
	printf "Tests failed. Check ./test/diff.txt for details.\n"
	exit 1
fi
