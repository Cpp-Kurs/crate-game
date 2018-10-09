
class Falling_box {
 public:
  Falling_box(float x, float y)
      : posx_{x}, posy_{y}, speed_{1.0f}, acceleration_{0.0f}, dt_{1}, sizex_{20}, sizey_{20}{}

  Falling_box(float x, float y, float spd)
      : posx_{x}, posy_{y}, speed_{spd}, acceleration_{0.0f}, dt_{1/60}, sizex_{20}, sizey_{20} {}

  Falling_box(float x, float y, float spd, float acc)
      : posx_{x}, posy_{y}, speed_{spd}, acceleration_{acc}, dt_{0.05}, sizex_{20}, sizey_{20}{}

  void advance() {
    posy_ += speed_ * dt_;
    speed_ += acceleration_ * dt_;
    }




  float posx() { return posx_; }
  float posy() { return posy_; }
  float speed() { return speed_; }
  float sizey(){return sizey_; }
  float sizex(){return sizex_; }

 private:
  float dt_;
  float acceleration_;
  float posx_;
  float posy_;
  float speed_;
  int sizey_;
  int sizex_;
};
