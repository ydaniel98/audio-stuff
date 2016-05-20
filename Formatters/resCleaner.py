# Edwin Daniel Penalo Colon
# This file formats the data in for the grapher and future code
# regarding the sythetic voice (NSE) project

# Imports
import sys


# Varaibles

filePath = '' 		# Path of file (Relative to location)
outName  = ''		# Name for output file 

samples  = 0		# Samples reference for filtering
samplesCount = 0	# Count to act upon matching amount of samples
		 
avrg_y = []		
num_x = 0		

f   = None			# Files to read
out = None			# Output file


# Get arguments

if (len(sys.argv) < 4):
	print("To few arguments")
	sys.exit(1)

filePath += sys.argv[1]
outName  += sys.argv[2]
samples  += int(sys.argv[3])

print filePath
print outName


# Open file
try:
	f = open(filePath, 'r')

except IOError as err:

	print("Error opening file: error({0}) {1}".format(err.errno, err.strerror))
	sys.exit(1)


# Creat output file
try:

	out = open(outName, 'w')

except IOError as err:

	print("Error creating output: error({0}) {1}".format(err.errno, err.strerror))
	sys.exit(1)

# Format file

data = f.readlines()

for line in data:

	samplesCount += 1

	avrg_y.append(float(line.split('\t')[1]))

	if samplesCount >= samples:

		num_y = 0.0

		for num in avrg_y:
			num_y += num

		num_y = float(num_y / len(avrg_y))

		avrg_y = []

		out.write(str(num_x))
		out.write('\t')
		out.write(str(num_y))
		out.write('\n')

		num_x += 1


# Finish up
f.close()
out.close()

print(outName + " formatted")

sys.exit(0)