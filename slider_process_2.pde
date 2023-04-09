import processing.serial.*;
Serial port;
float x=100;
float y;
void setup (){
  port=new Serial(this,"COM4",9600);// this sketch talk with com of arduino
  size(600,400);}
  void draw(){
    clear();
    background(255);
    fill(0,255,0);
    rect(100,250,400,20);//big rect
    fill(255,0,0);
    if(mouseY>250&&mouseY<270&&mousePressed&&mouseX>100&&mouseX<500){
    x=mouseX;
    rect(x,245,10,30);}
    else{rect(x,245,10,30);}
    y=map(x,100,500,0,255);
    port.write(byte(y));
  }
    
    
    