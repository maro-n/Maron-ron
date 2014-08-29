int switch_s = 0;
int switch_w = 0;
int switch_n = 0;
int switch_e = 0;
int point = 0;

void setup()
{
    size(500, 500);
}

void draw()
{
    background (255, 255, 255);
    fill(0);
    textSize(20);
    text("point", 350, 480);
    text(point, 420, 480);
    //text(switch_s, 0, 50);
    //text(switch_w, 0, 100);
    //text(switch_e, 0, 150);
    //text(switch_n, 0, 200);
    ellipse(250, 250, 50, 50);
    if(mouseX >= 220 && mouseX <= 280 && mouseY > 275 && switch_s == 0){
      switch_s = 1;
    }
    if(mouseX < 225 && mouseY >= 220 && mouseY <= 280 && switch_w == 0){
      switch_w = 1;
    }
    if(mouseX >= 220 && mouseX <= 280 && mouseY < 225 && switch_n == 0){
      switch_n = 1;
    }
    if(mouseX > 275 && mouseY >= 220 && mouseY <= 280 && switch_e == 0){
      switch_e = 1;
    }
    if(switch_s == 1 && switch_w == 1 &&  switch_n == 1 && switch_e == 1){
      point += 1;
      switch_s = 0;
      switch_w = 0;
      switch_n = 0;
      switch_e = 0;
    }
}
