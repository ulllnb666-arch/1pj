#include "STC32G.H"
#include "traffic.h"
#include "display.h"
#include "key.h"
#include "uart.h"

void main(void)
{
    WTST  = 0x00;
    EAXFR = 1;
    CKCON = 0x00;
    
    display_init();
    traffic_init();
    key_init();
    uart1_init();
    
    EA = 1;
    display_update();
    
    while (1)
    {
        if (b500ms) {
            b500ms = 0;
            traffic_tick();
            display_update();
        }
        
        {
            u8 key = key_scan();
            switch (key) {
            case KEY1_PRESS:
                if (traffic_mode == MODE_DAY)
                    traffic_set_mode(MODE_NIGHT);
                else
                    traffic_set_mode(MODE_DAY);
                display_update();
                break;
            case KEY2_PRESS:
                traffic_force_main();
                display_update();
                break;
            case KEY3_PRESS:
                traffic_force_side();
                display_update();
                break;
            case KEY4_PRESS:
                traffic_cancel_temp();
                display_update();
                break;
            }
        }
        
        uart1_process();
    }
}
