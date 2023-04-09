import processing.serial.*;
Serial port;
void setup() {
  port = new Serial(this, "COM4", 9600); o
  size(1000, 1000);
  background(255);
}
void draw() {  
  clear();
  background(255);
  ellipse(100, 100, 50, 50);
  ellipse(100, 200, 50, 50);
  ellipse(100, 300, 50, 50);
  ellipse(100, 400, 50, 50);
  ellipse(100, 500, 50, 50);
  ellipse(200, 100, 50, 50);
  ellipse(200, 200, 50, 50);
  ellipse(200, 300, 50, 50);
  ellipse(200, 400, 50, 50);
  ellipse(200, 500, 50, 50);
  ellipse(300, 100, 50, 50);
  ellipse(300, 200, 50, 50);
  ellipse(300, 300, 50, 50);
  ellipse(300, 400, 50, 50);
  ellipse(300, 500, 50, 50);
  ellipse(400, 100, 50, 50);
  ellipse(400, 200, 50, 50);
  ellipse(400, 300, 50, 50);
  ellipse(400, 400, 50, 50);
  ellipse(400, 500, 50, 50);
  if ( dist( mouseX, mouseY, 100, 100 ) < 25&& mousePressed ) {
    ellipse(100, 100, 50, 50);
    text("ON", 10, 30);
    fill(50,56,050);
  } 
   else if ( dist( mouseX, mouseY, 100, 200 ) < 25 && mousePressed) {


    ellipse(100, 200, 50, 50);
    text("ON", 10, 30);
  } 
  else  if ( dist( mouseX, mouseY, 100, 300 ) < 25&& mousePressed ) {

   
      ellipse(100, 300, 50, 50);
    text("ON", 10, 30);
  } 
  else  if ( dist( mouseX, mouseY, 100, 400 ) < 25&& mousePressed ) {

 
    text("ON", 10, 30);
  }
    else if ( dist( mouseX, mouseY, 100, 500 ) < 25&& mousePressed ) {

    text("ON", 10, 30);
  } 
else{  fill(255);   text("OFF", 10, 30);}
 
}