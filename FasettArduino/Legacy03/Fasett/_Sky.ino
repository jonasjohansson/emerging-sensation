void skySetup(){  
}

void skyLoop(){
  for (uint8_t i = 0; i < NUM_PARTS; i++){
    blink(i,2,20);
  }
}
