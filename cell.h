#ifndef CELL_H
#define CELL_H

#include <QDateTime>
#include <QSharedPointer>
#include <QWidget>

class VirusCell;
typedef QSharedPointer<VirusCell> Cell;
class VirusCell
{
public:
  enum Type
  {
    WALL,
    ANTIBODY,
    VIRUS,
    EMPTY,
  };

  explicit VirusCell(int x, int y);

  //  static int blockWidth();
  //  static int blockHeight();

  Type type() const;
  void setType(const Type& type);
  int x() const;
  int y() const;
  QString text() const;

signals:

public slots:

protected:
  Type m_type;
  int m_x, m_y;
  QString m_text;
};

struct CellData
{
  enum Direction
  {
    NORTH,
    SOUTH,
    EAST,
    WEST,
  };
  CellData(QPoint pt);
  CellData(int x, int y);
  static Direction randomDirection();
  QPair<Direction, Direction> nextDirections();

  Direction direction;
  QPoint point;
};
typedef QSharedPointer<CellData> Data;

#endif // CELL_H
