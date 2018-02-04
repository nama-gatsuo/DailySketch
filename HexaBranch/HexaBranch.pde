int depth = 32;
float d = 12;
float theta = PI / 6.;
long seed = 1;

class Agent {
  int status;
  PVector pos, dir;
  
  Agent(PVector p, PVector d) {
    pos = p;
    dir = d;
  }
  
  void step(){
    PVector npos = pos.copy();
    npos.add(dir.copy().mult(d));
    line(pos.x, pos.y, npos.x, npos.y);
    pos = npos;
  }
  
  void left(){ dir.rotate(- theta); }
  void right(){ dir.rotate(theta); }
  void straight(){ }
  float getAngle() {
    if (dir.x == 0.) {
      return PI / 2.;
    } else if (dir.x < 0.) {
      return PI - atan(dir.y / - dir.x);
    } else {
      return atan(dir.y / dir.x);
    }
  }
  float getCos() {
    return dir.dot(new PVector(0, 1.));
  }
}


void setup(){
  size(800, 800);
  pixelDensity(displayDensity());
  blendMode(ADD);
  background(0);
  
  stroke(128, 198, 255, 124);
  translate(width/2, height/2);
  
  seed = (long)(100 * random(100));
  for (float i = 0; i < 6.; i+=1.) {
    randomSeed(seed);
    pushMatrix();
    rotate(TWO_PI / 6. * i);
    //translate(0., -400.);
    
    Agent start = new Agent(new PVector(0,0), new PVector(0, 1.)); 
    
    itr(start, 0);
    popMatrix();  
  }
  
  d = 12;
  seed = (long)(100 * random(100));
  
  stroke(198, 100, 120, 124);
  for (float i = 0; i < 6.; i+=1.) {
    randomSeed(seed);
    pushMatrix();
    rotate(TWO_PI / 6. * i);
    translate(0., -400.);
    
    Agent start = new Agent(new PVector(0,0), new PVector(0, 1.)); 
    
    itr(start, 0);
    popMatrix();  
  }
}

void itr(Agent a, int lev){
  lev++;
  if (lev > depth) return;
  
  float angle = a.getAngle() - PI / 2.;
  float cosine = a.getCos();
  
  // straigt
  if (random(1.) < 0.6) {
    Agent na = new Agent(a.pos.copy(), a.dir.copy());
    na.straight();
    na.step();
    itr(na, lev);
  }
  
  // right
  if (angle < 2. * theta && random(1.) < 0.3) {
    Agent na = new Agent(a.pos.copy(), a.dir.copy());
    na.right();
    na.step();
    itr(na, lev);
  }
  
  // right
  if (angle > -2. * theta && random(1.) < 0.3) {
    Agent na = new Agent(a.pos.copy(), a.dir.copy());
    na.left();
    na.step();
    itr(na, lev);
  }
  
}