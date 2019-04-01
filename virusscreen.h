#ifndef VIRUSSCREEN_H
#define VIRUSSCREEN_H

#include <QEvent>
#include <QFrame>
#include <QKeyEvent>
#include <QLabel>
#include <QPainter>
#include <QTimer>

#include "cell.h"

class VirusScreen : public QFrame
{
  Q_OBJECT
public:
  explicit VirusScreen(QWidget* parent = nullptr);

  static int getMaxColumn();
  static int getMaxRow();
  void createEmptyBoard();
  void resetGame();
  bool isFinished() const;
  void keyNorth();
  void keySouth();
  void keyEast();
  void keyWest();
  void fucked();

  static const int max_column = 40;
  static const int max_row = 25;
  static const int offset_x = 92; // 50;
  static const int offset_y = 30;
  static const int block_width = 12;
  static const int block_height = 15;

signals:
  void gameFinished();
  void crashed(int);
  void startGame(int timeout);
  void switchToStart();

public slots:

protected:
  QList<QList<Cell>> m_board;
  QList<Data> m_virus;
  Data m_antibody;

  bool m_finished;
  bool m_fucked;
  QTimer* m_game_timer;

  static const int antibody_x = 21;
  static const int antibody_y = 13;
  static const int virus_x = 6;
  static const int virus_y = 6;
  static const int TIMEOUT = 1000;
  Cell cellAt(int column, int row);
  Cell cellAt(Data data);
  void paintEvent(QPaintEvent* event) override;
  void resetAntibody();
  void resetBoard();
  void resetVirus();
  void setVirus(Data virus);
  void nextMove();
  void nextAntibodyMove();
  void nextVirusMove(int index);
  Cell nextCellInDirection(CellData::Direction direction,
                           const int x,
                           const int y,
                           int& next_x,
                           int& next_y);

  bool isGoodVirusMove(Cell next_cell);
  bool isGoodAntibodyMove(Cell next_cell);
};

#endif // VIRUSSCREEN_H
