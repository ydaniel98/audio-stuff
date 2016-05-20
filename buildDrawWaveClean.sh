cd DrawWave
make

cd ../GraphData
make

cd ../WaveGraph
make

cd ../

mkdir -p DrawWave_clean
mkdir -p DrawWave_clean/draw_data

cd DrawWave_clean

cp ../DrawWave/draw_wave ./draw_wave
cp ../GraphData/graph_data ./draw_data/graph_data
cp ../wave_graph ./wave_graph
cp ../DrawWave/draw_data/gnuDrawPlot.sh ./draw_data/gnuDrawPlot.sh
