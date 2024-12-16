# Set terminal and output file
set terminal pngcairo size 1000,600 enhanced font "Arial,12"
set output 'daily_totals.png'

# Title and labels
set title "Daily Total Orders" font ",14" textcolor rgb "blue"
set xlabel "Date (Days)" font ",12" textcolor rgb "black"
set ylabel "Total Price (DH)" font ",12" textcolor rgb "black"

# Grid and axis styling
set grid lw 1 lt 0 lc rgb "#d3d3d3"  # Light gray grid
set border linewidth 1.5 lc rgb "black"
set tics font ",10" textcolor rgb "black"

# X-axis: Time formatting
set xdata time
set timefmt "%Y-%m-%d"   # Input date format
set format x "%d"        # Display only the day
set xtics rotate by -45 font ",10" textcolor rgb "black"

# Y-axis: Format for prices
set format y "%.2f"      # Format Y values with 2 decimal places
set yrange [0:7000]      # Set Y-axis range explicitly from 0 to 7000
set ytics 1000           # Add Y-axis ticks at intervals of 1000

# Custom line and point styles
set style line 1 lt 1 lw 2 pt 7 ps 1.5 lc rgb "#FF5733"  # Orange line, circles

# Plot the data
plot 'C:\\Users\\Pc\\Desktop\\newcproject\\RESTAU\\menu\\daily_totals.dat' using 1:2 with linespoints ls 1 title "Total Price (DH)"

