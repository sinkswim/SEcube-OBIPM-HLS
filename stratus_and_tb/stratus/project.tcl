#
# BDW Project File
#

############################################################
# Project Parameters
############################################################
#
# Technology Libraries
#
set LIB_PATH "[get_install_path]/share/stratus/techlibs/GPDK045/gsclib045_svt_v4.4/gsclib045/timing"
set LIB_LEAF "slow_vdd1v2_basicCells.lib"

use_tech_lib	"$LIB_PATH/$LIB_LEAF"

#
# Global synthesis attributes.
#
set_attr clock_period           25.0
set_attr message_detail         3
set_attr default_input_delay    0.1
set_attr output_style_reset_all on

#
# Simulation Options
#
set_attr cc_options             " -DCLOCK_PERIOD=25.0 -g"
enable_waveform_logging -vcd
set_attr end_of_sim_command "make saySimPassed"

set_systemc_options -version 2.3 -gcc 4.1

# use_systemc_simulator incisive

#
# Testbench or System Level Modules
#
systemModule main.cpp
systemModule system.cpp
systemModule tb.cpp
systemModule wrapper.cpp
systemModule ip.cpp

#
# SC_MODULEs to be synthesized
#
define_hls_module obipm obipm.cpp

define_hls_config obipm BASIC

define_hls_config obipm DPA_1       --dpopt_auto=op
define_hls_config obipm DPA_2       --dpopt_auto=expr
define_hls_config obipm DPA_3       --dpopt_auto=array
define_hls_config obipm DPA_4       --dpopt_auto=op,expr
define_hls_config obipm DPA_5       --dpopt_auto=op,array
define_hls_config obipm DPA_6       --dpopt_auto=array,expr
define_hls_config obipm DPA_ALL       --dpopt_auto=all

define_hls_config obipm CSE         --comm_subexp_elim=on

define_hls_config obipm FLAT        --flatten_arrays=all

define_hls_config obipm ST_BIN      --global_state_encoding=binary
define_hls_config obipm ST_1HOT     --global_state_encoding=one_hot

define_hls_config obipm ME_1        --method_processing=translate
define_hls_config obipm ME_2        --method_processing=synthesize
define_hls_config obipm ME_3        --method_processing=dpopt

define_hls_config obipm PEFF_1      --parts_effort=low
define_hls_config obipm PEFF_2      --parts_effort=medium
define_hls_config obipm PEFF_3      --parts_effort=high

define_hls_config obipm POW_1        --power_fsm=on
define_hls_config obipm POW_2        --power_clock_gating=on
define_hls_config obipm POW_3        --power_memory=on
define_hls_config obipm POW_ALL      --power=on
define_hls_config obipm POW_NO       --power=off

define_hls_config obipm AGGR_1        --sched_aggressive_1=on
define_hls_config obipm AGGR_2        --sched_aggressive_2=on







define_sim_config B

######################################################################
# Simulation and Power Configurations
######################################################################
# The following rules are TCL code to create a simulation configuration
# for RTL_V for each hls_config defined.
# For each simulation configuration, create a JOULES power analysis
# configuration as well. NOTE: You must have waveform logging enabled
# for the power configurations to work.
#
foreach config [find -hls_config *] {
  set cname [get_attr name $config]
  define_sim_config ${cname}_V "obipm RTL_V $cname"
  define_power_config P_${cname} ${cname}_V -module obipm -command bdw_runjoules
}

######################################################################
# RC Logic Synthesis Configurations
######################################################################
define_logic_synthesis_config RC {obipm -all} \
    -command "bdw_runrc" \
    -options \
        [list BDW_LS_TECHLIB "$LIB_PATH/$LIB_LEAF"] \
        {BDW_LS_CLK_GATING normal} \
        {BDW_LS_NOGATES 1}




