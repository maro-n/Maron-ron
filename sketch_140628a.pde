float cx, cy, r, dx, dy;
float pressedX, pressedY;
float releasedX, releasedY;
float draggedX, draggedY;
float originX, originY;

void setup() {
  size(300, 300);
  cx = width/2;
  cy = height/2;
  r = 100;
}
void draw() {
  background(255);
  noFill();
  ellipse(cx, cy, 2*r, 2*r);
  fill(255,0,0);
  ellipse(pressedX, pressedY, 10, 10);
  fill(0,255,0);
  ellipse(draggedX, draggedY, 10, 10);
  fill(0,0,255);
  ellipse(releasedX, releasedY, 10, 10);
}
void mousePressed(){
  dx = mouseX - cx;
  dy = mouseY - cy;
  pressedX = mouseX;
  pressedY = mouseY;
  originX = cx;
  originY = cy;
}
void mouseDragged(){
  draggedX = mouseX;
  draggedY = mouseY;
  if(dx*dx + dy*dy < r*r){
    cx = originX + (mouseX - pressedX);
    cy = originY + (mouseY - pressedY);
  }
}
void mouseReleased(){
  releasedX = mouseX;
  releasedY = mouseY;
}
