#include "cell.h"

VirusCell::VirusCell(int x, int y)
  : m_type(EMPTY)
  , m_x(x)
  , m_y(y)
  , m_text("")
{}

VirusCell::Type
VirusCell::type() const
{
  return m_type;
}

void
VirusCell::setType(const VirusCell::Type& type)
{
  m_type = type;
  switch (m_type) {
    case WALL:
      m_text = "X";
      break;
    case VIRUS:
      m_text = "*";
      break;
    case ANTIBODY:
      m_text = "o";
      break;
    default:
      m_text = "";
  }
}

int
VirusCell::x() const
{
  return m_x;
}

int
VirusCell::y() const
{
  return m_y;
}

QString
VirusCell::text() const
{
  return m_text;
}

/* CellData
 *****************************************************************************/

CellData::CellData(QPoint pt)
{
  point = pt;
}

CellData::CellData(int x, int y)
{
  point = QPoint(x, y);
  direction = randomDirection();
}

CellData::Direction
CellData::randomDirection()
{
  qsrand(QDateTime::currentDateTime().toTime_t());
  int val = qrand() % 4;
  switch (val) {
    case 0:
      return NORTH;
    case 1:
      return EAST;
    case 2:
      return SOUTH;
    case 3:
      return WEST;
  }
  return NORTH;
}

QPair<CellData::Direction, CellData::Direction>
CellData::nextDirections()
{
  switch (direction) {
    case NORTH:
      return qMakePair<CellData::Direction, CellData::Direction>(EAST, WEST);
    case SOUTH:
      return qMakePair<CellData::Direction, CellData::Direction>(WEST, EAST);
    case EAST:
      return qMakePair<CellData::Direction, CellData::Direction>(SOUTH, NORTH);
    case WEST:
      return qMakePair<CellData::Direction, CellData::Direction>(NORTH, SOUTH);
  }
}
