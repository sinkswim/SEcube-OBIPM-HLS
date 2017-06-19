#ifndef IC_DEFINE_H
#define IC_DEFINE_H 0

#include <systemc.h>
#define NUM_IP 8
//#define DEBUG 0


SC_MODULE(ic) {

  //Input ports
  sc_in<bool>               clk;
  sc_in < bool >          rst;
  sc_in<sc_bv<1> >        transaction;
  sc_in<sc_bv<NUM_IP> >   interrupt_ip;
  sc_in<sc_bv<1> >        irq;
  sc_in<sc_bv<1> >        acked;

  //Output ports
  sc_out<sc_bv<1> >       interrupt_internal;
  sc_out<unsigned int>    index_interrupt;

  // Constructor
  SC_CTOR(ic): clk("clk"), rst("rst") {

    SC_CTHREAD(interrupt_controller, clk.pos());
    reset_signal_is(rst, false);

  }


  //Methods and Threads
  void interrupt_controller();


};



#endif  // IC_DEFINE_H
