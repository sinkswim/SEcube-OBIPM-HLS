#include "tb.h"

void tb::resetter(void) {

  tb_rst.write(0);
  wait(3);
  tb_rst.write(1);
  wait();


}


void tb::trace(void) {

  std::cout << "------------------------------------------------------" << '\n';
  std::cout << "@" << sc_time_stamp() << " interrupt_internal "
            << tb_interrupt_internal.read() << '\n';

  std::cout << "@" << sc_time_stamp() << " index_interrupt "
            << tb_index_interrupt.read() << '\n';

  std::cout << "@" << sc_time_stamp() << " clk "
            << clk.read() << '\n';

  std::cout << "@" << sc_time_stamp() << " tb_transaction "
            << tb_transaction.read() << '\n';

  std::cout << "@" << sc_time_stamp() << " tb_interrupt_ip "
            << tb_interrupt_ip.read() << '\n';

  std::cout << "@" << sc_time_stamp() << " tb_irq "
            << tb_irq.read() << '\n';

  std::cout << "@" << sc_time_stamp() << " tb_acked "
            << tb_acked.read() << '\n';

  std::cout << "@" << sc_time_stamp() << " tb_rst "
            << tb_rst.read() << '\n';



  return;
}


void tb::mc(void) {

  //Reset Phase

  tb_transaction.write("0");
  tb_acked.write("0");
  tb_interrupt_ip.write((sc_bv<NUM_IP>) 0);
  tb_irq.write("0");
  wait();
  // raise two interrupt at the same time

  tb_interrupt_ip.write((sc_bv<NUM_IP>) 3);   //0....11
  tb_irq.write("1");

  while(tb_interrupt_internal.read() == "0") wait();
  tb_acked.write("1");
  wait();
  tb_acked.write("0");
  tb_interrupt_ip.write((sc_bv<NUM_IP>) 2);   //0....10
  tb_irq.write("1");
  while(tb_interrupt_internal.read() == "0") wait();
  tb_acked.write("1");
  wait();
  tb_acked.write("0");
  wait();
  sc_stop();


}
