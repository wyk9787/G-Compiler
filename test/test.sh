#!/bin/bash

# # set up diff.txt
result="./test/diff.txt"
rm -f result
touch "$result"
chmod 755 "$result"
result2="./test/result.txt"
test_result="./test/test_result.txt"
#
# # find each test file ending with .in
# for filename in ./test/*.in; do
#   # read each line from the file
#   while IFS='' read -r line || [[ -n "$line" ]]; do
#     # parsing the line by space and store them in options
#     while IFS=' ' read -ra options; do
#         # the output filename, eg: test1_o.out
#         new_filename=${filename/.in/_o.out}
#
#         # the expected_filename, eg: test1.out
#         expected_filename=${filename/.in/.out}
#
#         # create the output file if not existed
#         touch "$new_filename"
#         chmod 755 "$new_filename"
#
#         #run the compiler with argument from array options and redirect the output to the output file
#         ./build/apps/compiler "${options[@]}" > "$new_filename"
#
#         #diff the output file and the expected file
#         diff $new_filename $expected_filename > "$result"
#
#         # if the test fails, prints the filename to the diff.txt
#         # otherwise, remove the output file
#         if [ -s $"result" ]
#         then
#           printf "%s\n" $filename > "$result"
#         else
#           rm "$new_filename"
#         fi
#     done <<< "$line"
#   done < "$filename"
# done

echo "(* (+ 1 (- 3 2)) (* 10 3))" | ./build/apps/compiler > "$result2"
diff "$test_result" "$result2" > "$result"
