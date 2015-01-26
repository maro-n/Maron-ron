  PImage img;
  PImage img2;
void setup(){
  size(500, 500);
  img = loadImage("Invador.png");
  img2 = loadImage("Invador2.png");
}
  float anime = 0.5 * 90;
  int x = 0, y = 0;
  int sign = 0;
  float move_x = 0;

void draw(){
  anime--;
  background(0);
  if(anime == 0){
    anime = 0.5 * 90;
  }
  for (int i = 0; i < 8; ++i){
    if(anime > 0.5 * 45){
        rect(50 * i + move_x, y, 50, 40);
        image(img, 50 * i + move_x, y, 50, 40);
    }
    if(anime <= 0.5 * 45){ 
      rect(50 * i + move_x, y, 50, 40);
      image(img2, 50 * i + move_x, y, 50, 40);
    }
  }
  if(move_x == 100){
    sign = 1;
    y += 40;
  }
  if(move_x == 0 && sign == 1){
    sign = 0;
    y += 40;
  }
  if(sign == 1){
    move_x--;
  }
  else{
    move_x++;
  }
  if(y == 400){
    y = 0;
  }
}

