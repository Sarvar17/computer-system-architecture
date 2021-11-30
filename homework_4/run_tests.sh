echo "\nRun test #0"
time -p ./program -f tests/test_0/input.txt tests/test_0/output_1.txt tests/test_0/output_2.txt

echo "\nRun test #1"
time -p ./program -f tests/test_1/input.txt tests/test_1/output_1.txt tests/test_1/output_2.txt

echo "\nRun test #2"
time -p ./program -f tests/test_2/input.txt tests/test_2/output_1.txt tests/test_2/output_2.txt

echo "\nRun test #3"
time -p ./program -f tests/test_3/input.txt tests/test_3/output_1.txt tests/test_3/output_2.txt

echo "\nRun test #4"
time -p ./program -f tests/test_4/input.txt tests/test_4/output_1.txt tests/test_4/output_2.txt

echo "\nRun test #5"
time -p ./program -f tests/test_5/input.txt tests/test_5/output_1.txt tests/test_5/output_2.txt

echo "\nRun test #6 (random test with 10000 elements)"	
time -p ./program -n 10000 tests/test_10000/output_1.txt tests/test_10000/output_2.txt
