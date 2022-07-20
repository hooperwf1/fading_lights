#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

int count = 0, dir = 1;
ISR (TIMER0_OVF_vect){
    if(count++ < 512)
        return;

    count = 0;
    OCR0B += dir;
    if(OCR0B == 0xff || OCR0B == 0)
        dir *= -1;
}

void init_pwm(){
    // Use OC0B
    DDRD |= (1 << PD5);

    // Clar OC0B on compare match, then clean are bottom (non-inverting mode)
    // Set to Fast PWM
    TCCR0A = (1 << COM0B1) | (1 << WGM01) | (1 << WGM00);

    // Enable timer overflow interrupt
    TIMSK0 |= (1 << TOIE0);

    // Low initial PWM to prevent high voltages
    OCR0B = 20;

    // No prescaler
    TCCR0B = (1 << CS00);

    // Enable interrupts
    sei();
}

int main(void){
    init_pwm();

    while(1){
    }
}
