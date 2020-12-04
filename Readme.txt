Readme

Question 1

Compile the 3 source files
	1. ci_q1.c
	2. ta_q1.c
	3. student_q1.c

using the commands
	gcc ci_q1.c -o ./ci
	ta_q1.c -o ./ta
	student_q1.c -o ./st

Run each executable file in separate terminal windows 
	./ci
	./ta
	./st

In the terminal running ci_q1.c, when prompted enter the marks of five students (0-50)

Using Message Queues, data will be communicated.
Appropriate outputs will be displayed.

Each student receives their marks from CI.
TA will calculate grades of each student and the class average and sent the data to CI.
CI will print the class average and grades of each student.

---------

Question 2

Compile the source file q2.c using the command
	gcc q2.c -o ./q2

Run the executable file 
	./q2

Input is read from the file 'sample_input' provided in the folder Q2.

Format for input in the file (linewise) :
number of processeses n
number of resources m
AllocTable
MaxTable
Total number of instances per resource type

Query format :
'a' : Output a safe sequence
'b' : Check if the given sequence is safe
'c' : Check if the request of resources can be granted
't' : terminate program

Example Query :
5
3
10 5 7
0 1 0
2 0 0
3 0 2
2 1 1
0 0 2
7 5 3
3 2 2
9 0 2
4 2 2
5 3 3
a
b
1 2 3 4 5
b
2 3 1 4 5
c
7 7 7
c
1 0 2
t

------

Question 3

Compile the source file q3.c using the command
	gcc q3.c -o ./q3

Run the executable file 
	./q3

Appropriate Logs indicating Philosopher's Activity - THINKING, HUNGRY, EATING, PICKING FORKS etc.

Enter Control+C to exit program



