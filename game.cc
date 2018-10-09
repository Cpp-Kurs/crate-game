#include "game.h"


  Game::Game(QWidget* parent) : QWidget(parent) {
    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);

    QTimer* timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(loop_slot()));
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(1000.0f / 60.0f);

    QTimer* difficulty_timer = new QTimer(this);
    connect(difficulty_timer, SIGNAL(timeout()), this, SLOT(difficulty_slot()));
    difficulty_timer->start(1000.0f);
  }

  void Game::make_rand_box(){
    std::uniform_real_distribution<float> distribution{0, 1.0f * (width() - 10)};
    std::uniform_real_distribution<float> distribution_vel_acc{difficulty, difficulty + 10};
    float rand_pos = distribution(rng);
    float rand_vel = distribution_vel_acc(rng);
    float rand_acc = distribution_vel_acc(rng);
    Falling_box box1{rand_pos, 1.0f * (0), 10, 100};
    box_vector.push_back(box1);

  }
  bool Game::collided(){
    for(int i=0; i < box_vector.size(); i++){
      if (box_vector[i].posy() > height() - box_vector[i].sizey() - 15){
        if (box_vector[i].posx() > x - box_vector[i].sizex()){
          if (box_vector[i].posx() < x + 40){
            return true;
          }
        }
      }
    }
    return false;
  }

  void Game::keyPressEvent(QKeyEvent* event){
    if (event->key() == Qt::Key_Escape) {
      QApplication::quit();
    } else if (event->key() == Qt::Key_Right) {
      key_right = true;
    } else if (event->key() == Qt::Key_Left) {
      key_left = true;
    } else if (event->key() == Qt::Key_Down) {
      key_down = true;
    } else if (event->key() == Qt::Key_Up) {
      key_up = true;
    }
  }

  void Game::keyReleaseEvent(QKeyEvent* event) {
    if (event->key() == Qt::Key_Right) {
      key_right = false;
    } else if (event->key() == Qt::Key_Left) {
      key_left = false;
    } else if (event->key() == Qt::Key_Down) {
      key_down = false;
    } else if (event->key() == Qt::Key_Up) {
      key_up = false;
    }
  }

  void Game::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    QPen pen(Qt::blue, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    painter.setPen(pen);
    painter.setRenderHint(QPainter::Antialiasing, true);

    painter.setBrush(Qt::SolidPattern);
    painter.drawRect(QRect(0, 0, width(), height()));


    QPen pen2(Qt::red, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    painter.setBrush(Qt::red);
    painter.setPen(pen2);
    QRect player = {x, height() - 10, 40, 20};
    painter.drawRect(player);
    if (box_vector.size() <= static_cast<int>(difficulty/10)){
      make_rand_box();
    }

    Game::showbox (painter);

    if (Game::collided()){
      QApplication::quit();
    }



  }

  void Game::showbox( QPainter& painter){
     QPen pen2(Qt::red, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
     painter.setBrush(Qt::red);
     painter.setPen(pen2);
     for (int i=0; i<box_vector.size(); i++){
       QRect rect = {static_cast<int> (box_vector[i].posx()), static_cast<int> (box_vector[i].posy()), 20, 20};
       painter.drawRect(rect);
       if (box_vector[i].posy() > height()){
         box_vector.erase(box_vector.begin()+i);
         score += 1;
       }
       box_vector[i].advance();

     }



   }
  void Game::loop_slot() {

    if (key_left){
      if(x >= 0){
        x -= speed;
      }
    }
    if (key_right){
      if(x <= width()){
        x += speed;
      }
    }
  }
  void Game::difficulty_slot(){
    difficulty +=1;
  }
