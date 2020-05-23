#include <thread>
#include <iostream>
#include <fstream>

struct data {
  float x;
  float y;
  float z;
  float rx;
  float ry;
  float rz;
  bool forward;
};

void write_data(const data& d) {
  std::ofstream f;
  f.open("S:\\datadetrack.json");
  f << "{"
      << "\"x\":" << d.x << ","
      << "\"y\":" << d.y << ","
      << "\"z\":" << d.z << ","
      << "\"rx\":" << d.rx << ","
      << "\"ry\":" << d.ry << ","
      << "\"rz\":" << d.rz
    << "}";
  f.close();
}

bool should_add(data& d)
{
  if(d.x > -300) d.forward = false;
  else if(d.x < -400) d.forward = true;
  return d.forward;
}


int msPerFrame = 33;
int animationSeconds = 5;
float frames = animationSeconds * (1000 / msPerFrame);

float dx = 500.0 / frames;
float dy = 800.0 / frames;
float dz = 60.0 / frames;
float dry = 30.0 / frames;

void update_data(data& d) {
  if(should_add(d)) {
    d.x += dx;
    d.y += dy;
    d.z += dz;
    d.ry += dry;
  } else {
    d.x -= dx;
    d.y -= dy;
    d.z -= dz;
    d.ry -= dry;
  }
}

void readSettings() {
  std::ifstream settings;
  char skip[100];
  settings.open("jsonconfig.txt");
  settings
    >> skip >> msPerFrame
    >> skip >> animationSeconds;
  settings.close();
}

int main(int argc, char** argv)
{
  readSettings();
  std::cout << msPerFrame << " " << animationSeconds;

  frames = animationSeconds * (1000 / msPerFrame);
  dx = 500.0 / frames;
  dy = 800.0 / frames;
  dz = 60.0 / frames;
  dry = 30.0 / frames;

  data d;
  d.x = -400;
  d.y = 1600;
  d.z = 2400;
  d.rx = 100;
  d.ry = 0;
  d.rz = 0;
  d.forward = true;
  while (true)
  {
    write_data(d);
    update_data(d);
    std::this_thread::sleep_for(std::chrono::milliseconds(msPerFrame));
  }
}