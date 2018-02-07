#!/bin/bash

# # set up diff.txt
test_result="./test/diff.txt"
rm -f "$test_result"
touch "$test_result"
chmod 755 "$test_result"

# set up result.txt
result="./test/result.txt"
rm -f "$result"
touch "$result"
chmod 755 "$result"

expected_result="./test/expected.out"

# find each test file ending with .in
for filename in ./test/*.in; do
  # read each line from the file
  while IFS='' read -r line || [[ -n "$line" ]]; do
    echo "$line" | ./build/apps/compiler >> "$result"
  done < "$filename"
done

diff "$result" "$expected_result" >> "$test_result"
