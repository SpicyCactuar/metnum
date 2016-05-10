from numpy import genfromtxt, uint8
import png

my_data = genfromtxt('img.csv', delimiter=',')
my_data = my_data.astype(uint8)
png.from_array(my_data, 'L').save('img.png')
