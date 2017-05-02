#include "gpio.h"
#include "system_timer.h"
#include "uart.h"
#include "bcm2835.h"

#define PIN RPI_GPIO_P1_11
//this is actually GPIO pin 17
//PI refers to the 26 or 40 pin expansion header. P1-11 refers to pin 11 of that header which is GPIO 17.
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

void play_game(){ //not sure if this will be void or not
	//while current_time != timer || (button not pressed) (timer is the amount of time offset we allow them)
	//poll the switches
	//when a user presses a switch break out of while loop
	//check if the switch was right 
	//can bounce out or do everything in this function
	
	
	//set up the 3 pins to be inputs, add pullups, and enable lows
	int switch_pressed = 0;
	//get timer and add offset
	uint32_t currentCount = sys_timer[SYS_TIMER_CLO];
	uint32_t wait = 3000000;
	uint32_t targetTime = currentCount + wait; //This gives them three seconds
	uint8_t pin_number = currentCount & 0x00000ff;	//not sure of this is right
	//randomly choose switch
	char button_string = currentCount | 0x30;	
	//make the character printable
	char temp[10] = {"Switch: ", button_string};
	put_string(temp);
	//put string of switch chosen
	while (switch_pressed != 1){
		//poll the switches here
		
	}
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
	
//	gpio[GPFSEL2] = 0x208000;	//want bits 21-23 and 15-17 to both be 001
//	gpio[GPFSEL1] = 0x0000000; //set all the bits on gpio select 1 to be inputs
	//these are pins 10 through 19

	const int buffer_size = 80;
	int num = 0; //The number of the switch
	uint32_t timer = 0x00000000 //the lower 32 of the timer
	char buffer [buffer_size];
	get_string(buffer, buffer_size);
	while (1){

		put_string("Welcome, please input a 1\r\n");
		get_string(buffer, buffer_size);
		char ch = buffer[0];
		if (ch == '1'){
			//begin the game logic
			play_game();  
		}
		else{
			put_string("Invalid input, please re-try\r\n\0");
		}
		//do the game end logic stuff here???
	}
    return 0;
}
