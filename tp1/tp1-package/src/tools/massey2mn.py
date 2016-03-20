import csv
from sets import Set

input_path = '../../data/nba_2016_scores.csv'
output_path = '../../data/nba_2016_scores.dat'

with open(input_path,'rb') as csvfile,open(output_path,'w') as outfile:
	score_reader = csv.reader(csvfile,delimiter=',',skipinitialspace=True)

	teams = Set()
	n_games = 0
	# String with info of the games.
	out_str = ''
	for row in score_reader:
		teams.add(row[2])
		teams.add(row[5])
		n_games = n_games+1
		out_str = out_str + row[1] + ' ' + row[2] + ' ' + row[4] + ' ' + row[5] + ' ' + row[7] + '\n'
	# Write number of teams and games
	outfile.write(str(len(teams)) + ' ' + str(n_games) + '\n')
	# Write games details
	outfile.write(out_str)

