#=============================================================================
# run.tcl
#=============================================================================
# @brief: A Tcl script for C simulation of the face-detection design

# Open/reset the project
open_project hls.prj -reset

# Top function of the design is "haar"
set_top detectFaces

# Add design and testbench files
add_files haar.cpp

add_files -tb main.cpp
add_files -tb image.cpp

open_solution solution
 
# Use Zynq device
# zc-706
set_part xc7z045ffg900-2

config_rtl -reset state

# Simulate the C++ design
csim_design

# Co-simulate the design
# cosim_design

exit
