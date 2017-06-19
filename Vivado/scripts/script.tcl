############################################################
## This file is generated automatically by Vivado HLS.
## Please DO NOT edit it.
## Copyright (C) 1986-2017 Xilinx, Inc. All Rights Reserved.
############################################################
open_project SysC_try
set_top obipm
add_files Documents/AtlasRep/stratus/defines.h
add_files Documents/AtlasRep/stratus/obipm.cpp
add_files Documents/AtlasRep/stratus/obipm.h
open_solution "solution1"
set_part {xa7z030fbg484-1i} -tool vivado
create_clock -period 10 -name default
source "./SysC_try/solution1/directives.tcl"
#csim_design
csynth_design
#cosim_design
export_design -format ip_catalog
