import processing.serial.*;
Serial port;




float x,y;
void setup(){
port=new Serial(this,"COM4",9600);
port.write();//function write


size(500,500);

}
void draw(){
ellipse(100,100,0,50);
if(dist(mouseX,mouseY,100,100)<25){port.write('F');
ellipse(100,100,0,50);}
else if(dist(mouseX,mouseY,200,100)<25){ellipse(300,100,50,50);}
else {port.write('s');
  
clear();
background(255,0,0);
fill(255,0,0);
ellipse(100,100,0,50);
ellipse(100,100,0,50);}
}
//if we want to color many ellipse define ellipse and make fill