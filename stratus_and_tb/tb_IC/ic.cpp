#include "ic.h"

void ic::interrupt_controller(){
    sc_bv<NUM_IP> intr_ip_v = (sc_bv<NUM_IP>)0;

        intr_ip_v = (sc_bv<NUM_IP>)0;
        // MV begin
        // outpus signals should be set to 0
        index_interrupt.write(0);
        interrupt_internal.write("0");
        // MV end
        //wait();   here not needed

    while(true){
        wait();

        while(transaction.read() == '1'){
#ifdef DEBUG
            std::cout << "@ " << sc_time_stamp() << " OBIPM: filtering interrupts \n";
#endif
            wait();
        }
        intr_ip_v = interrupt_ip.read();
#ifdef DEBUG
        std::cout << "@ " << sc_time_stamp() << " OBIPM: accepting interrupts \n";
        #endif
        if(irq.read() == '1'){

            for(int i = 0; i < NUM_IP; i++){

                if(intr_ip_v.range(i,i) == "1"){          // NOTE: on g++ linux compiler "" gave problems.... check on stratus. > Update: No problem with stratus simulation (still unix compiler). Might wanna compared systemc library versions.

                    index_interrupt.write(i+1);
                    while(transaction.read() == "1")    // Re-check if the CPU has required a transaction. Remember: CPU is the master.
                        wait();
                    interrupt_internal.write("1");
                    wait();
                    while(acked.read() == '0')
                        wait();
                    interrupt_internal.write('0');
                    break;
                }
            }
        }
    }
}
