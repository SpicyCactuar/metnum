from numpy import genfromtxt, uint8
from sys import argv
import png

my_data = genfromtxt(argv[1], delimiter=',')
my_data = my_data.astype(uint8)
png.from_array(my_data, 'L').save(argv[1]+'.png')
