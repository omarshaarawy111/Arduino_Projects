import processing.serial.*;
Serial port;
void setup() {
  port = new Serial(this, "COM4", 9600); 
  size(200, 200);
  background(255);
}
void draw() {    
  background(255);
  ellipse(100, 100, 50, 50);
  if ( dist( mouseX, mouseY, 100, 100 ) < 25 ) {
    port.write('1');
    fill( 0, 255, 0 );
    text("ON", 10, 30);
  } else {
    port.write('0');
    fill( 255, 0, 0 );
    text("OFF", 10, 30);
  }
  delay(50);
}