# Edwin Daniel Penalo
# Makefile to compile everything in the project

all:
	cd WaveGraph; \
	make

	cd GraphData; \
	make

	cd DrawWave; \
	make

	cp -f GraphData/graph_data DrawWave/draw_data

	cp -f WaveGraph/wave_graph DrawWave

	# Draw Wave Clean
	cp -f GraphData/graph_data DrawWave_clean/draw_data
	cp -f WaveGraph/wave_graph DrawWave_clean
	cp -f DrawWave/draw_wave DrawWave_clean
	cp -f DrawWave/draw_data/gnuDrawPlot.sh DrawWave_clean/draw_data
