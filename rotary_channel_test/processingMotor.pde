
PImage mobil;
color fontColor = color(50, 119, 253);
color bgColor = color(3, 12, 26);

void setup(){
  size(700, 420);
  mobil = loadImage("iconMobil.png");
  
}

void draw(){
  background(bgColor);
  textSize(24);
  fill(255,255,255);
  text("Speed", 30, 50);
  
  textSize(28);
  fill(fontColor);
  text("30km/h", 30, 90);
  
  textSize(24);
  fill(255,255,255);
  text("Objects passed", width-185, 50);
  
  textSize(28);
  fill(fontColor);
  text("9", width-50, 90);
  
  image(mobil, width/2.5, height/5);
  
  textSize(24);
  fill(255,255,255);
  text("Sudut rotasi terhadap objek", width/3.25, height-90);
  
  textSize(28);
  fill(fontColor);
  text("56.767° ke kiri", width/2.5, height-45);
}
