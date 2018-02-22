#!/bin/bash

########### TEST PLAN ###########
# test1: a comprehensive test1
# test2: a comprehensive test2
# test3: if then else
# test4: arithmetic operation
# test5: integer math
# test6: floating math
# test7: integer & floating
# test8: math with NaN
#################################

# # set up diff.txt
result="./test/diff.txt"
rm -f "$result"
touch "$result"
chmod 755 "$result"

# find each test file ending with .in
for filename in ./test/*.src; do
  parse_output="${filename%.src}.parse.out"
  output="${filename%.src}.out"
  diff <(./build/compiler -f "$filename" -p) "$parse_output" >> "$result"
  diff <(./build/compiler -f "$filename") "$output" >> "$result"
done
