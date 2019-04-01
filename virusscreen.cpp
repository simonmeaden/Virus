#include "virusscreen.h"

#include <QDebug>

VirusScreen::VirusScreen(QWidget* parent)
  : QFrame(parent)
  , m_antibody(new CellData(antibody_x, antibody_y))
  , m_finished(true)
  , m_fucked(true)
{
  setStyleSheet("background-color: black;");
  createEmptyBoard();
  connect(this, &VirusScreen::crashed, this, &VirusScreen::fucked);
}

int
VirusScreen::getMaxColumn()
{
  return max_column;
}

int
VirusScreen::getMaxRow()
{
  return max_row;
}

void
VirusScreen::createEmptyBoard()
{
  qWarning() << "createEmptyBoard()";

  for (int row = 0; row <= max_row; row++) {
    QList<Cell> list;
    for (int column = 0; column <= max_column; column++) {
      Cell cell = Cell(new VirusCell(int(column * block_width) + offset_x,
                                     int(row * block_height) + offset_y));
      list.append(cell);
    }
    m_board.append(list);
  }
  resetBoard();
  m_game_timer = new QTimer(this);
  m_game_timer->setInterval(1000);
  connect(m_game_timer, &QTimer::timeout, this, &VirusScreen::nextMove);
  connect(this,
          &VirusScreen::startGame,
          m_game_timer,
          qOverload<int>(&QTimer::start));
  connect(this, &VirusScreen::gameFinished, m_game_timer, &QTimer::stop);
  qWarning() << "createEmptyBoard() GAME STARTED";
}

void
VirusScreen::resetBoard()
{
  for (int row = 0; row <= max_row; row++) {
    for (int column = 0; column <= max_column; column++) {
      Cell cell = cellAt(column, row);
      if (!cell.isNull()) {
        if (row == 0 || row == max_row) {
          cell->setType(VirusCell::WALL);
        } else {
          if (column == 0 || column == max_column) {
            cell->setType(VirusCell::WALL);
          } else {
            cell->setType(VirusCell::EMPTY);
          }
        }
      }
    }
  }
  resetAntibody();
  resetVirus();
}

void
VirusScreen::resetAntibody()
{
  m_antibody->column = antibody_x;
  m_antibody->row = antibody_y;
  Cell cell = cellAt(m_antibody);
  cell->setType(VirusCell::ANTIBODY);
}

void
VirusScreen::setVirus(Data virus)
{
  Cell cell = cellAt(virus->column, virus->row);
  cell->setType(VirusCell::VIRUS);
  m_virus.append(virus);
}

void
VirusScreen::nextMove()
{
  qWarning() << "nextMove()";
  nextAntibodyMove();
  for (int i = 0; i < m_virus.size(); i++) {
    nextVirusMove(i);
  }
}

void
VirusScreen::nextAntibodyMove()
{
  if (m_finished)
    return;

  int x = m_antibody->column;
  int y = m_antibody->row;
  int next_x, next_y;

  Cell cell = cellAt(x, y);
  Cell next_cell;
  next_cell = nextCellInDirection(m_antibody->direction, x, y, next_x, next_y);
  if (isGoodAntibodyMove(next_cell)) {
    // direction unchanged.
    m_antibody->column = next_x;
    m_antibody->row = next_y;
  } else {
    m_finished = true;
    emit crashed(3);
    // TODO SOUNDS
  }
  update();
}

bool
VirusScreen::isGoodVirusMove(Cell next_cell)
{
  if (next_cell->type() == VirusCell::EMPTY) {
    // next cell is empty so the virus can move here.
    next_cell->setType(VirusCell::VIRUS);
    return true;
  }
  return false;
}

bool
VirusScreen::isGoodAntibodyMove(Cell next_cell)
{
  if (next_cell->type() == VirusCell::EMPTY) {
    // next cell is empty so the antibody can move here.
    next_cell->setType(VirusCell::ANTIBODY);
    return true;
  }
  return false;
}

void
VirusScreen::nextVirusMove(int index)
{
  if (m_finished)
    return;

  Data virus = m_virus.at(index);
  int x = virus->column;
  int y = virus->row;
  int next_x, next_y;

  Cell cell = cellAt(x, y);
  Cell next_cell;
  next_cell = nextCellInDirection(virus->direction, x, y, next_x, next_y);
  if (isGoodVirusMove(next_cell)) {
    // direction unchanged.
    virus->column = next_x;
    virus->row = next_y;
    m_virus.replace(index, virus);
  } else {
    QPair<CellData::Direction, CellData::Direction> possible_turns =
      virus->nextDirections();
    next_cell = nextCellInDirection(possible_turns.first, x, y, next_x, next_y);
    if (isGoodVirusMove(next_cell)) {
      virus->column = next_x;
      virus->row = next_y;
      virus->direction = possible_turns.first;
      m_virus.replace(index, virus);
    } else {
      next_cell =
        nextCellInDirection(possible_turns.second, x, y, next_x, next_y);
      if (isGoodVirusMove(next_cell)) {
        virus->column = next_x;
        virus->row = next_y;
        virus->direction = possible_turns.second;
        m_virus.replace(index, virus);
      } else {
        // this virus is trapped.
        if (m_virus.size() == 1) {
          // the last virus is trapped.
          m_finished = true;
          emit gameFinished();
        } else {
          m_virus.removeAt(index);
        }
      }
    }
  }
  update();
}

Cell
VirusScreen::nextCellInDirection(CellData::Direction direction,
                                 const int x,
                                 const int y,
                                 int& next_x,
                                 int& next_y)
{
  next_x = x;
  next_y = y;
  switch (direction) {
    case CellData::NORTH:
      next_y--;
      break;
    case CellData::SOUTH:
      next_y++;
      break;
    case CellData::EAST:
      next_x++;
      break;
    case CellData::WEST:
      next_x--;
      break;
  }
  return cellAt(next_x, next_y);
}

void
VirusScreen::resetVirus()
{
  m_virus.clear();
  Data virus(new CellData(virus_x, virus_y));
  setVirus(virus);
}

void
VirusScreen::resetGame()
{
  resetBoard();
  resetAntibody();
  resetVirus();
  emit startGame(TIMEOUT);
  m_finished = false;
  m_fucked = false;
  update();
}

bool
VirusScreen::isFinished() const
{
  return m_finished;
}

void
VirusScreen::keyNorth()
{
  m_antibody->direction = CellData::NORTH;
}

void
VirusScreen::keySouth()
{
  m_antibody->direction = CellData::SOUTH;
}

void
VirusScreen::keyEast()
{
  m_antibody->direction = CellData::EAST;
}

void
VirusScreen::keyWest()
{
  m_antibody->direction = CellData::WEST;
}

Cell
VirusScreen::cellAt(int column, int row)
{
  if (row < 0 || row >= m_board.size() || column < 0 ||
      column >= m_board.at(0).size())
    return Cell(nullptr);
  return m_board.at(row).at(column);
}

Cell
VirusScreen::cellAt(Data data)
{
  return cellAt(data->column, data->row);
}

void
VirusScreen::paintEvent(QPaintEvent* event)
{
  QFrame::paintEvent(event);
  QPainter painter(this);
  painter.setBrush(QColor("black"));
  if (!m_finished) {
    Cell cell;
    int x, y;
    for (int row = 0; row <= max_row; row++) {
      for (int column = 0; column <= max_column; column++) {
        cell = cellAt(column, row);
        if (!cell.isNull()) {
          x = cell->x();
          y = cell->y();
          painter.setPen(QColor("black"));
          painter.drawRect(x, y, block_width, block_height);
          painter.setPen(QColor("white"));
          painter.drawText(x, y + block_height, cell->text());
        }
      }
    }
  }
  if (m_fucked) {
  }
}

void
VirusScreen::fucked()
{
  m_fucked = true;
  emit switchToStart();
}
