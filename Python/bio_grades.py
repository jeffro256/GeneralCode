grades = [[8, 8],
[0, 5],
[0, 10],
[9, 10],
[10, 10],
[8, 8],
[24, 30],
[0, 7],
[0, 3],
[5, 5],
[95, 100],
[0, 8],
[17, 20],
[0, 8],
[75, 75],
[6, 12],
[5, 10],
[9, 9],
[14.5, 20],
[85, 85],
[0, 8],
[0, 14],
[10, 10],
[0, 11],
[0, 10],
[96, 100],
[8, 10],
[0, 15],
[0, 12],
[0, 10],
[3, 3],
[94, 100]
]

max_grade = 0
max_grade_index = -1

for i in range(len(grades)):
	ndum = 0
	dsum = 0
	for j in range(len(grades)):
		if j != i:
			ndum += grades[j][0]
			dsum += grades[j][1]

	new_grade = ndum / dsum

	if (new_grade > max_grade):
		max_grade = new_grade
		max_grade_index = i

print(max_grade_index, grades[max_grade_index])
