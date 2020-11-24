# csv
set datafile separator ","

# use the first line as title
set key autotitle columnhead noenhanced

# move key to top left of graph
set key left top

# title
set title "Read times for strings (15 bytes)"

# axis labels
set ylabel "Time (ms)"
set xlabel "Number of keys"

# font style
set tics font "Helvetica,10"

# line styles
set style line 1 \
    linecolor rgb '#25283d' \
    linetype 1 linewidth 3

set style line 2 \
    linecolor rgb '#8f3985' \
    linetype 1 linewidth 3

set style line 3 \
    linecolor rgb '#98DFEA' \
    linetype 1 linewidth 3

set style line 4 \
    linecolor rgb '#ADE25D' \
    linetype 1 linewidth 3

set style line 5 \
    linecolor rgb '#EFD9CE' \
    linetype 1 linewidth 3

set rmargin 5

plot "data/read_small_string" using 2:xtic(1) with lines ls 1, \
    "data/read_small_string" using 3:xtic(1) with lines ls 2, \
    "data/read_small_string" using 4:xtic(1) with lines ls 3, \
    "data/read_small_string" using 5:xtic(1) with lines ls 4, \
    "data/read_small_string" using 6:xtic(1) with lines ls 5
