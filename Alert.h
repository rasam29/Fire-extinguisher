
#include <delay.h>
#include <mega16.h>

#define Buzzer_Pin PORTD.0
#define Led_pin PORTD.1




long simple_alert_delay = 1700;
long causion_alert_delay = 850;
long fire_detected_delay = 500;


void alert(){
    Led_pin = !Led_pin;
    delay_ms(simple_alert_delay);
}

void causion(){
    Led_pin = !Led_pin;
    delay_ms(causion_alert_delay);
}

void alarm_fire(){
    Buzzer_Pin = !Buzzer_Pin; 
    Led_pin = !Led_pin;
    delay_ms(fire_detected_delay);
}

void off(){
    Buzzer_Pin = 0;
     Led_pin = 0;
}