import csv
import sys
read = sys.argv[1]
# removes csv extension
write = read[:-3] + 'BetterRead.csv'
with open(read, 'rb') as f:
	reader = csv.reader(f)
	data = []
	for x in xrange(0,20):
		data.append([])
	count = 0
	for row in reader:
		index = count % 34
		if count < 20:
			data[index].append(row[0])
		if index < 20:
			data[index].append(row[1])
		count += 1
with open(write, 'wb') as f:
    writer = csv.writer(f)
    writer.writerows(data)
