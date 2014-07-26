float cx, cy, cx2, cy2, r, r2, dx, dy, dx2, dy2;

void setup() {
  size(300, 300);
}
void draw() {
  cx = width/2;
  cy = height/2;
  cx2 = mouseX;
  cy2 = mouseY;
  dx = cx2 - cx;
  dy = cy2 - cy;
  dx2 = dx - (dx-cx2);
  dy2 = dy - (dy-cy2);
  r = 100;
  r2 = 30;
  background(255);
  noFill();
  ellipse(cx2, cy2, r2*2, r2*2);
  ellipse(cx, cy, 2*r, 2*r);
  if(dx*dx + dy*dy > (r2-r)*(r2-r)){
  fill(255, 0, 0);
  ellipse(cx2, cy2, r2*2, r2*2);
  }
}

