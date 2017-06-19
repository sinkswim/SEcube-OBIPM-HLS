#ifndef WRAPPER_GUARD
#define WRAPPER_GUARD 0

//////////////////////////////////////////////////////////////////////////
// This module represent a wrapper to adapt the generic IP Manager to the
// IPs. NOTE that this is only needed for the SystemC simulation, since
// once it is synthesized it is possible to resort to the features of the
// HDL. For sake of portability across different HLS complilers, this
// represent the best choice. This module is composed by SC_METHOD only
// since it only map the generic singnals in input to a specified number
// of output ports. The following is designed for 2 IPs only.
//////////////////////////////////////////////////////////////////////////

#include "defines.h"
#include "stratus_hls.h"
#include <systemc.h>

SC_MODULE(wrapper) {
public:

  // INPUT PORTS
  // OBIPM -> WRAPPER
  // the following are output ports in OBIPM Interface
  sc_in<sc_bv<NUM_IP*16> >    data_ip_out_OBIPM;
  sc_in<sc_bv<NUM_IP> >       enable_ip_OBIPM;
  sc_in<sc_bv<NUM_IP> >       ack_ip_OBIPM;


  // WRAPPER <- IPs
  sc_in<sc_bv<16> >     data_ip_in_IP1;
  sc_in<sc_bv<16> >     data_ip_in_IP2;
  sc_in<sc_bv<6> >      address_ip_IP1;
  sc_in<sc_bv<6> >      address_ip_IP2;
  sc_in<sc_bv<1> >      w_enable_ip_IP1;
  sc_in<sc_bv<1> >      w_enable_ip_IP2;
  sc_in<sc_bv<1> >      r_enable_ip_IP1;
  sc_in<sc_bv<1> >      r_enable_ip_IP2;
  sc_in<sc_bv<1> >      generic_enable_ip_IP1;
  sc_in<sc_bv<1> >      generic_enable_ip_IP2;
  sc_in<sc_bv<1> >      interrupt_ip_IP1;
  sc_in<sc_bv<1> >      interrupt_ip_IP2;



  // OUTPUT PORTS
  // WRAPPER -> OBIPM
  sc_out<sc_bv<NUM_IP*16> >   data_ip_in_OBIPM;
  sc_out<sc_bv<NUM_IP*6> >    address_ip_OBIPM;
  sc_out<sc_bv<NUM_IP> >      w_enable_ip_OBIPM;
  sc_out<sc_bv<NUM_IP> >      r_enable_ip_OBIPM;
  sc_out<sc_bv<NUM_IP> >      generic_enable_ip_OBIPM;
  sc_out<sc_bv<NUM_IP> >      interrupt_ip_OBIPM;

  // WRAPPER -> IPs
  sc_out<sc_bv<16> >        data_ip_out_IP1;
  sc_out<sc_bv<16> >        data_ip_out_IP2;
  sc_out<sc_bv<1> >         enable_ip_IP1;
  sc_out<sc_bv<1> >         enable_ip_IP2;
  sc_out<sc_bv<1> >         ack_ip_IP1;
  sc_out<sc_bv<1> >         ack_ip_IP2;


  // Constructor
  SC_CTOR(wrapper) {

    SC_METHOD(wrapping_logic);
    sensitive << data_ip_out_OBIPM << enable_ip_OBIPM
              << ack_ip_OBIPM << data_ip_in_IP1 << data_ip_in_IP2
              << address_ip_IP1 << address_ip_IP2 << w_enable_ip_IP1
              << w_enable_ip_IP2 << r_enable_ip_IP1 << r_enable_ip_IP2
              << generic_enable_ip_IP1 << generic_enable_ip_IP2
              << interrupt_ip_IP1 << interrupt_ip_IP2;
  }

  // Methods and THREADS
  void wrapping_logic();

};
#endif
