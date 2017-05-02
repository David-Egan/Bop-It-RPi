#include "gpio.h"
#include "system_timer.h"
#include "uart.h"
#include "bcm2835.h"

#define PIN RPI_GPIO_P1_15

void f_blink_once()
{
    // Turn on GPIO 27
    gpio[GPSET0] |= 1 << 27;

    timer_delay_ms(1000);

    // Turn off GPIO 27
    gpio[GPCLR0] |= 1 << 27;

    timer_delay_ms(1000);
}

void g_blink_once()
{
    // Turn on GPIO 25
    gpio[GPSET0] |= 1 << 25;

    timer_delay_ms(1000);

    // Turn off GPIO 25
    gpio[GPCLR0] |= 1 << 25;

    timer_delay_ms(1000);
}

void both_blink()
{	
	gpio[GPSET0] |= 1 << 25;
	gpio[GPSET0] |= 1 << 27;
	timer_delay_ms(1000);
	gpio[GPCLR0] |= 1 << 27;
	gpio[GPCLR0] |= 1 << 25;
	timer_delay_ms(1000);
	
}

void blink_code(uint32_t err)
{
    for(int i = 0; i < err; ++i)
    {
        f_blink_once();
    }

    // Only delay 4 seconds, since we delay for 1 additional
    // second in blink_once().
    timer_delay_ms(4500);
}

void check_switches(int num, uint32_t timer){ //not sure if this will be void or not
	//while current_time != timer || (button not pressed) (timer is the amount of time offset we allow them)
	//poll the switches
	//when a user presses a switch break out of while loop
	//check if the switch was right 
	//can bounce out or do everything in this function

}

void test_switch(){
	if (!bcm2835_init())
        return 1;

    // Set PIN to be an input
    bcm2835_gpio_fsel(PIN, BCM2835_GPIO_FSEL_INPT);
    //  add a pullup
    bcm2835_gpio_set_pud(PIN, BCM2835_GPIO_PUD_UP);
    // and enble low
    bcm2835_gpio_len(PIN);

    while (1)
    {
        if (bcm2835_gpio_eds(PIN))
        {
            // Now clear the eds flag by setting it to 1
            bcm2835_gpio_set_eds(PIN);
            put_string("Button Pressed!\r\n");
        }
        delay(500);
    }
    bcm2835_close();
    return 0;
	
}


int main()
{
    test_switch();
	
	// Implement Lab 4 as described in the lab manual
	gpio[GPFSEL2] = 0x208000;	//want bits 21-23 and 15-17 to both be 001
	gpio[GPFSEL1] = 0x0000000; //set all the bits on gpio select 1 to be inputs
	//these are pins 10 through 19

	const int buffer_size = 80;
	int num = 0; //The number of the switch
	uint32_t timer = 0x00000000 //the lower 32 of the timer
	char buffer [buffer_size];
	get_string(buffer, buffer_size);
	while (1){
		//randomly choose the switch here
		put_string("Welcome, please input a 1\r\n");
		get_string(buffer, buffer_size);
		char ch = buffer[0];
		if (ch == '1'){
			//begin the game logic
			check_switches(num, timer)  //pass game_over variable as well??
		}
		else if (ch == '2'){
		//do the other function

		}
		else{
			put_string("Invalid input, please re-try\r\n\0");
		}
	}
    return 0;
}
