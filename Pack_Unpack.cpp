#include<stdio.h>
#include<stdint.h>
int main()
{
    uint16_t speed= 60;
    uint16_t rpm= 120;
    uint8_t can_data[8] = {0};
   can_data[0] = speed & 0xff ;
   can_data[1] = (speed>>8) & 0xff ;
   can_data[2] = rpm & 0xff ;
   can_data[3] = (rpm>>8) & 0xff ;
     printf( "Packed CAN Bytes : \n");
     for (int i=0; i<=3; i++){
         printf("Byte %d = %u\n", i, can_data[i]);}
   uint16_t rx_speed;
   uint16_t rx_rpm;
   rx_speed = can_data[0] | (can_data[1] << 8);
   rx_rpm = can_data[2] | (can_data[3] <<8);
     printf( "Unpacked Values : \n");
     printf("Speed = %u Km/h \n", rx_speed);
    printf("rpm = %u \n", rx_rpm);
return 0;
}
