float cx, cy, cx2, cy2, r, r2, dr, dx, dy, dx2, dy2;

void setup() {
  size(300, 300);
  cx = width/2;
  cy = height/2;
  r = 100;
  r2 = 30;
}

void draw() {
  dx = mouseX - cx;
  dy = mouseY - cy;
  
  background(255);
  fill(255);
  ellipse(cx, cy, 2*r, 2*r);
  
  if(dx*dx + dy*dy > (r2-r)*(r2-r)){
    fill(255, 0, 0);
    dr = (dx*dx + dy*dy) / (r2-r)*(r2-r);
    
  }
  else{
    fill(0, 0, 255);
    cx2 = mouseX;
    cy2 = mouseY;
  }
  
  ellipse(cx2, cy2, r2*2, r2*2);
  
  line(cx, cy, mouseX, mouseY);
  line(cx, cy, mouseX, cy);
  line(cx2, cy, cx2, cy2);
  line(mouseX, cy, mouseX, mouseY);
}

