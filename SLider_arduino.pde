import processing.serial.*;
Serial port;
float x=100,y=245;
void setup(){
size(600,400);
port=new Serial(this,"COM5",9600);

}
void draw(){
clear();
background(180);
if(mouseX>100&&mouseX<=501&&mouseY>250&&mouseY<270&&mousePressed){
  
y=245;
x= mouseX;
float val =map(x,100,500,0,255);
port.write(byte (val));

}

else if(mousePressed){ port.write('0');}
fill(255);
rect(100,250,400,20);
fill(255,0,0);
rect(x,y,10,30);
textSize(50);
fill(255);
text("SLIDER",200,100);
}