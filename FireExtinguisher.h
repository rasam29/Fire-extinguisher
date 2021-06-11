#include "Adc_Reader.h"
#include "Alert.h"
#include <mega16.h>

#define HEAT_SENSOR  PINA
#define Stepper_MOTOR PORTC
#define Button PINA.1


int simple_temp_milestone = 30;
int causion_temp_milestone = 40;
int fire_temp_milstone = 50;




int readTemprature();



int isSimple(float temp);
int isCaution(float temp);
int isFire(float temp);


int isWaterOpen = 0;

void openWaterValve();
void closeWaterValve();



int onFire = 0;


void start(){
       
    closeWaterValve();
   
    DDRA.1 = 0;
    PORTA.1 = 1;  
    DDRD.0 = 1; 
    DDRD.0 = 1; 
    DDRA.0 = 1;  

    
    while (1)
    {    
       
           int temp = readTemprature();
      
           if(Button ==1)
           {
                if (isFire(temp))
                 {
                     onFire = 1;
                    openWaterValve();
                     alarm_fire();
         
                }else if (isCaution(temp))
                {
                     if (onFire)
                      {
                            alarm_fire();
                            openWaterValve();
                      }else{
                            closeWaterValve();
                            causion();
                      }
            
           
                 }else if (isSimple(temp))
                 {
                        onFire = 0;
                        closeWaterValve();
                        alert();
           
                }else{
                    onFire = 0;
                    off();  
                    closeWaterValve();
                    
            
                }
             }else{
           
                    off();
                    closeWaterValve();
           }
        

    
    }
}    



int isFire(float temp){
   return temp >=fire_temp_milstone;
}

int isCaution(float temp){
   return (causion_temp_milestone-2)<temp && temp <fire_temp_milstone;

}

int isSimple(float temp){
   
   return (simple_temp_milestone-2)<temp && temp <(causion_temp_milestone-2);
    
}

void openWaterValve(){
    if (isWaterOpen == 0)
    {
       Stepper_MOTOR = 0x0C;//open stepper motor to 180 degrees
       isWaterOpen = 1;
    }
    
}

void closeWaterValve(){
    if (isWaterOpen == 1)
    {
        Stepper_MOTOR = 0x0A;//revert to 0
        isWaterOpen = 0;

    }
    
}

int readTemprature(){
      int temp =  read_adc(0);
      return temp/2.054;
}


