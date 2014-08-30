int switch_s = 0;
int switch_w = 0;
int switch_n = 0;
int switch_e = 0;
int point = 0;
int t_limit = 1200;
int logo_limit = 180;
void setup()
{
    size(500, 500);
}

void draw()
{
    background (255, 255, 255);
    fill(0, 0, 255);
    textSize(100);
    if(logo_limit > -1){
      logo_limit -= 1;
    }
    if(logo_limit >= 120 && logo_limit < 180){
      text("3", width / 2 - 30, height / 2 + 120);
    }
    if(logo_limit >= 60 && logo_limit < 120){
      text("2", width / 2 - 30, height / 2 + 120);
    }
    if(logo_limit > 0 && logo_limit < 60){
      text("1", width / 2 - 30, height / 2 + 120);
    }
    if(logo_limit == 0){
      text("GO!!", width / 2 - 100, height / 2 + 120);
    }
    if(logo_limit <= 0){
      t_limit -= 1;
    }
    textSize(20);
    fill(0);
    text("point", 350, 480);
    //text(switch_s, 0, 50);
    //text(switch_w, 0, 100);
    //text(switch_e, 0, 150);
    //text(switch_n, 0, 200);
    ellipse(250, 250, 50, 50);
    if(mouseX >= 220 && mouseX <= 280 && mouseY > 275 && logo_limit == -1 && switch_s == 0){
      switch_s = 1;
    }
    if(mouseX < 225 && mouseY >= 220 && mouseY <= 280 && logo_limit == -1
                    && switch_w == 0 && switch_s == 1){
      switch_w = 1;
    }
    if(mouseX >= 220 && mouseX <= 280 && mouseY < 225 && logo_limit == -1
                     && switch_n == 0 && switch_w == 1){
      switch_n = 1;
    }
    if(mouseX > 275 && mouseY >= 220 && mouseY <= 280 && logo_limit == -1 
                    && switch_e == 0 && switch_n == 1){
      switch_e = 1;
    }
    if(switch_s == 1 && switch_w == 1 &&  switch_n == 1 && switch_e == 1){
      point += 1;
      switch_s = 0;
      switch_w = 0;
      switch_n = 0;
      switch_e = 0;
    }
    if(t_limit == 0){
      textSize(100);
      fill(255, 0, 0);
      text("end", (width / 2) - 90, (height / 2) + 100);
      textSize(50);
      fill(255, 0, 0);
      text(point, 420, 480);
      noLoop();
    }
    else{
      text(point, 420, 480);
      textSize(100);
      text("roll!!", (width / 2) - 100, (height / 2) - 90);
    }
}
