#ifndef GAME_GAME_H_
#define GAME_GAME_H_

#include <QApplication>
#include <random>
#include <QKeyEvent>
#include <QPaintEvent>
#include <vector>
#include <QPainter>
#include <QPainterPath>
#include <QTimer>
#include <QWidget>
#include "falling_box.h"


class Game : public QWidget {
  Q_OBJECT

 public:
  Game(QWidget* parent = nullptr);
  bool collided();
  void make_rand_box();

 protected:
  void keyPressEvent(QKeyEvent* event) override;

  void keyReleaseEvent(QKeyEvent* event) override;

  void paintEvent(QPaintEvent* event) override;

 private slots:
   void showbox(QPainter& painter);


  void loop_slot();
  void difficulty_slot();

 private:
  bool key_up = false;
  bool key_down = false;
  bool key_left = false;
  bool key_right = false;
  int x = 10;
  int speed = 6;
  std::vector<Falling_box> box_vector;
  int score = 0;
  float difficulty = 0;
  std::mt19937 rng{std::random_device{}()};

};

#endif  // GAME_GAME_H_
