# Imports
import sys
import matplotlib.pyplot as plt


# Varaibles

filePath = '' 		# Path of file (Relative to location)

plot = [[], []]
plot_x = []
plot_y = []

f   = None			# Files to read

# Get arguments

if (len(sys.argv) < 2):
	print("To few arguments")
	sys.exit(1)

filePath += sys.argv[1]


try:
	f = open(filePath, 'r')

except IOError as err:

	print("Error opening file: error({0}) {1}".format(err.errno, err.strerror))
	sys.exit(1)


data = f.readlines()
i = 0

for line in data:

	number_x = line.split('\t')[0]
	number_y = line.split('\t')[1]

	plot_x.append(float(number_x))
	plot_y.append(float(number_y))

	i += 1

plot[0] = plot_x
plot[1] = plot_y

plt.plot(plot, 'r--')

plt.show()












