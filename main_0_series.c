#include <avr/io.h>
#include <avr/interrupt.h>

int count = 0, dir = 1, val = 0x3;
ISR(TCA0_OVF_vect){
    if(count++ < 4)
            return;
            
    count = 0;
    val += dir;
    
    char val_low = val & 0xff;
    char val_high = (val & 0xff00) >> 8;
    TCA0.SINGLE.CMP0BUFH = val_high;
    TCA0.SINGLE.CMP0BUFL = val_low;
    
    if(val == 0xffff || val <= 0x03)
            dir *= -1;
}

void init_pwm(){
    // WO0 is on PA0, make it an output
    PORTA.DIRSET = (1 << 0);
    
    // Output PWM on WO0, Single slope PWM
    TCA0.SINGLE.CTRLB = (1 << 4) | (0x3 << 0);

    // 255 is the Compare switch
    TCA0.SINGLE.CMP0BUFL = 10;
    TCA0.SINGLE.CMP0BUFH = 0;
    
    // Overflow interrupt
    TCA0.SINGLE.INTCTRL = (1 << 0);
            
    // Enable timer with no prescaler
    TCA0.SINGLE.CTRLA = (1 << 0);
}

int main(void)
{
    init_pwm();
    sei();
	
    while (1) 
    {
    }
}

