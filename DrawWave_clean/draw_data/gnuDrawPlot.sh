#
# $1 -> data file to plot
# $2 -> output type
# $3 -> output file
# $4 -> range for x-axis

gnuplot <<- EOF

set term $2
set xrange $4
set output "$3"
set size 1, 1
plot "$1" with lines lc "black"
q

EOF
