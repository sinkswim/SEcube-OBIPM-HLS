//////////////////////////////////////////////////////////////////////////
// Implementation of methods defined in wrapper.h
// NOTE: variables with -i stands for "Internal"
/////////////////////////////////////////////////////////////////////////
#include "wrapper.h"

//////////////////////////////////////////////////////////////////////////
// WRAPPING LOGIC - begin
//////////////////////////////////////////////////////////////////////////
void wrapper::wrapping_logic(){

  // Internal variables
  sc_bv<NUM_IP*16>  data_ip_out_OBIPM_i;
  sc_bv<NUM_IP*16>  data_ip_in_OBIPM_i;
  sc_bv<NUM_IP>     enable_ip_IP_i;
  sc_bv<NUM_IP>     ack_ip_IP_i;
  sc_bv<NUM_IP*6>   address_ip_OBIPM_i;
  sc_bv<NUM_IP>     w_enable_ip_OBIPM_i;
  sc_bv<NUM_IP>     r_enable_ip_OBIPM_i;
  sc_bv<NUM_IP>     generic_enable_ip_OBIPM_i;
  sc_bv<NUM_IP>     interrupt_ip_OBIPM_i;


  // Body

  // Read all inputs ports
  // from OBIPM
  data_ip_out_OBIPM_i     = data_ip_out_OBIPM.read();
  enable_ip_IP_i          = enable_ip_OBIPM.read();
  ack_ip_IP_i             = ack_ip_OBIPM.read();
  // from IPs
  data_ip_in_OBIPM_i.range(15, 0)      = data_ip_in_IP1.read();
  data_ip_in_OBIPM_i.range(31, 16)     = data_ip_in_IP2.read();
  address_ip_OBIPM_i.range(5, 0)       = address_ip_IP1.read();
  address_ip_OBIPM_i.range(11, 6)      = address_ip_IP2.read();
  w_enable_ip_OBIPM_i.range(0,0)       = w_enable_ip_IP1.read();
  w_enable_ip_OBIPM_i.range(1,1)       = w_enable_ip_IP2.read();
  r_enable_ip_OBIPM_i.range(0,0)       = r_enable_ip_IP1.read();
  r_enable_ip_OBIPM_i.range(1,1)       = r_enable_ip_IP2.read();
  generic_enable_ip_OBIPM_i.range(0,0) = generic_enable_ip_IP1.read();
  generic_enable_ip_OBIPM_i.range(1,1) = generic_enable_ip_IP2.read();
  interrupt_ip_OBIPM_i.range(0,0)      = interrupt_ip_IP1.read();
  interrupt_ip_OBIPM_i.range(1,1)      = interrupt_ip_IP2.read();



  // Assign all the outputs
  // to the IPs
  data_ip_out_IP1.write(data_ip_out_OBIPM_i.range(15, 0));
  data_ip_out_IP2.write(data_ip_out_OBIPM_i.range(31, 16));
  enable_ip_IP1.write(enable_ip_IP_i.range(0,0));
  enable_ip_IP2.write(enable_ip_IP_i.range(1,1));
  ack_ip_IP1.write(ack_ip_IP_i.range(0,0));
  ack_ip_IP2.write(ack_ip_IP_i.range(1,1));
  // to the OBIPM
  data_ip_in_OBIPM.write(data_ip_in_OBIPM_i);
  address_ip_OBIPM.write(address_ip_OBIPM_i);
  w_enable_ip_OBIPM.write(w_enable_ip_OBIPM_i);
  r_enable_ip_OBIPM.write(r_enable_ip_OBIPM_i);
  generic_enable_ip_OBIPM.write(generic_enable_ip_OBIPM_i);
  interrupt_ip_OBIPM.write(interrupt_ip_OBIPM_i);

  return;

}
//////////////////////////////////////////////////////////////////////////
// WRAPPING LOGIC - end
//////////////////////////////////////////////////////////////////////////
