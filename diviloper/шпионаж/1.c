unsigned char U_WRF(unsigned char mode)
{ unsigned char i;
  if (mode)
  {WRITE_USB ('W');
   WRITE_USB ('R');
   WRITE_USB ('F');
   WRITE_USB (0x20);
   WRITE_USB (0x00);
   WRITE_USB (0x00);
  WRITE_USB (0x00);
  WRITE_USB (0x0f);
  WRITE_USB (0x0d);
  WRITE_USB ('$');
  for (i=0;i<=3;i++) WRITE_USB(gpstime[i]);
  for (i=0;i<=3;i++) WRITE_USB(gpswide[i]);
  WRITE_USB('.');
  for (i=4;i<=8;i++) WRITE_USB(gpswide[i]);
  READ_PROMT();  
  WRITE_USB ('W');
  WRITE_USB ('R');
  WRITE_USB ('F');
  WRITE_USB (0x20);
  WRITE_USB (0x00);
  WRITE_USB (0x00);
  WRITE_USB (0x00);
  WRITE_USB (0x0f);
  WRITE_USB (0x0d); 
  WRITE_USB (gpswide[9]); 
  WRITE_USB (gpsns);
    for (i=0;i<=4;i++) WRITE_USB(gpslong[i]);
  WRITE_USB('.');
  for (i=5;i<=10;i++) WRITE_USB(gpslong[i]);
  WRITE_USB (gpswe);
  READ_PROMT(); 
  WRITE_USB ('W');
  WRITE_USB ('R');
  WRITE_USB ('F');
  WRITE_USB (0x20);
  WRITE_USB (0x00);
  WRITE_USB (0x00);
  WRITE_USB (0x00);
  WRITE_USB (0x07);
   WRITE_USB (0x0d); 
   for (i=0;i<=3;i++) WRITE_USB(gpsheight[i]);
   WRITE_USB(antenna[0]);
   WRITE_USB(antenna[1]);
   WRITE_USB(0x35);  
  }
  else
  {
   WRITE_USB ('W');
   WRITE_USB ('R');
   WRITE_USB ('F');
   WRITE_USB (0x20);
   WRITE_USB (0x00);
   WRITE_USB (0x00);
   WRITE_USB (0x00);
   WRITE_USB (0x03);
   WRITE_USB (0x0d);
   WRITE_USB ('#');
   WRITE_USB(antenna[0]);
   WRITE_USB(antenna[1]);
  }
  return(READ_PROMT()); 
}