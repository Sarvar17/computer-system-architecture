echo "\nRun test #0"
time task-1/code/out/homework_2 -f task-1/tests/test00.txt task-1/tests/out00_1.txt task-1/tests/out00_2.txt

echo "\nRun test #1"
time task-1/code/out/homework_2 -f task-1/tests/test01.txt task-1/tests/out01_1.txt task-1/tests/out01_2.txt

echo "\nRun test #2"
time task-1/code/out/homework_2 -f task-1/tests/test02.txt task-1/tests/out02_1.txt task-1/tests/out02_2.txt

echo "\nRun test #3"
time task-1/code/out/homework_2 -f task-1/tests/test03.txt task-1/tests/out03_1.txt task-1/tests/out03_2.txt

echo "\nRun test #4"
time task-1/code/out/homework_2 -f task-1/tests/test04.txt task-1/tests/out04_1.txt task-1/tests/out04_2.txt

echo "\nRun test #5"
time task-1/code/out/homework_2 -f task-1/tests/test05.txt task-1/tests/out05_1.txt task-1/tests/out05_2.txt

echo "\nRun test #6 (random)"
time task-1/code/out/homework_2 -n 10000 task-1/tests/outrnd_1.txt task-1/tests/outrnd_2.txt
