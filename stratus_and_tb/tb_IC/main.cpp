#include "tb.h"
#include <systemc.h>
#include <iostream>


int sc_main(int argc, char *argv[]) {

  sc_clock clock("system clock", sc_time(10, SC_NS));
  tb tb0("tb0");

  tb0.clk(clock);

  sc_start();

  return 0;


}
