#include "error_morse.h"
#include <util/crc16.h>

/*static bool isvalid(uint8_t byte){
  switch (byte) {
    case byte:
  }
}*/

static num byte2hex(uint8_t byte){
  num hexa;
  uint8_t high = byte>>4;
  uint8_t low = byte & 0x0F;
  if ( high >9 && high <= 0x0F ) {
    high+=55; // de 0 a 9
  }
  else{
    high+=48; //de A a Z
  }
  if (low >9 && low <=0x0F) {
    low += 55;
  }
  else {
    low+=48;
  }
  hexa.high=high;
  hexa.low=low;
  return hexa;
}

static uint8_t hex2byte(num hexa){
  uint8_t high, low=0;
  if (hexa.high>47 && hexa.high<=57){ // de 0 a 9
		hexa.high-=48;
	}
	else if (hexa.high>64 && hexa.high<=70){ //de A a Z
		hexa.high-=55;
	}
	if (hexa.low>47 && hexa.low<=57){
		hexa.low-=48;
	}
	else if (hexa.low>64 && hexa.low<=70){
		hexa.low-=55;
	}

	high=byte.high<<4; //bits mayor peso
	low=hexa.low & 0x0F; //bits menor peso
	return high|low; // y haces la or para devolver 1 byte
}

uint8_t add_check(uint8_t mensaje[]){
  uint16_t checksum=0;
  uint8_t carry=0;
  for (uint8_t i = 0; mensaje[i]!= '\0'; i++) {
    checksum+=mensaje[i];
  }
  while (checksum>0xFF) {
    carry=(checksum>>8);
    checksum &=0xFF;
    checksum += carry;
  }
  return byte2hex(~checksum); //complemento A1
}

static num get_redun(uint8_t mensaje_mas_redun[]){
	for(uint8_t i =0; mensaje_mas_redun[i]!= '\0'; i++){
		i -=2;
  }
	num result;
	result.high = mensaje_mas_redun[i];
	result.low = mensaje_mas_redun[i+1];
	mensaje_mas_redun[i] = '\0';
	return result;
}

bool check_is_ok(uint8_t mensaje[]){
  num check=get_redun(mensaje);
  num check_ok=add_check(mensaje);
  for(uint8_t i=0; mensaje[i]!= '\0'; i++);
		mensaje[i-2] = '\0';
	return (crc.high == crc_ok.high) && (crc.low == crc_ok.low);
}

num add_crc(uint8_t mensaje[]){
	for (uint8_t i=0; mensaje[i]!='\0'; i++){
		uint8_t crc=_crc_ibutton_update(crc, mensaje[i]); //calculo crc
	}
	num result = byte2hex(crc);
	result[i++] = result.high; //si sale del reves , se cambia high/low
	result[i] = result.low;
	return result;
}

bool crc_is_ok(uint8_t mensaje[]){
	num crc, crc_ok;
	crc = get_redun(mensaje);
	crc_ok = add_crc(mensaje);
	uint8_t num;
	for(uint8_t i=0; mensaje[i]!= '\0'; i++);
		mensaje[i-2] = '\0';
	return (crc.high == crc_ok.high) && (crc.low == crc_ok.low);

}
