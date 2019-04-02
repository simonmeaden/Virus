#include "startscreen.h"

/*!
  \class StartScreen
  \brief The StartScreen is where you start and where you end up at the end of
  the game.
*/

const QString StartScreen::VIRUS_NAME = QStringLiteral("VIRUS");
const QString StartScreen::GAME_MESSAGE_1 =
  QStringLiteral("YOU CONTROL AN ANTIBODY o THAT MUST");
const QString StartScreen::GAME_MESSAGE_2 =
  QStringLiteral("TRAP A VIRUS. YOU START OFF WITH ONE &");
const QString StartScreen::GAME_MESSAGE_3 =
  QStringLiteral("AS YOU ELIMINATE THEM THE STRAIN GROWS.");
const QString StartScreen::GAME_MESSAGE_4 =
  QStringLiteral("CONTROL IS BY THE CURSOR KEYS.");
const QString StartScreen::FUCKED_MESSAGE =
  QStringLiteral("You are Fucked, Fucked, Fucked!");
const QString StartScreen::SPACE_MESSAGE =
  QStringLiteral("PRESS SPACE TO START");

StartScreen::StartScreen(QWidget* parent)
  : QFrame(parent)
{
  QFontDatabase db;
  setFont(db.font("Beeb", "Regular", 25));
}

void
StartScreen::paintEvent(QPaintEvent* event)
{
  QFrame::paintEvent(event);

  QPainter painter(this);
  //  QFont font("Beeb", 25, QFont::Normal);
  QFont font = painter.font();
  painter.setFont(font);
  painter.setBrush(QColor("black"));
  painter.drawRect(0, 0, width(), height());
  int w = painter.fontMetrics().width(VIRUS_NAME);
  int x = int((width() - w) / 2.0);

  QPen pen = painter.pen(); // store original pen
  painter.setPen(QColor("red"));
  painter.drawText(x, 50, VIRUS_NAME);

  painter.setPen(
    QPen(Qt::blue, 8, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
  painter.drawLine(x - 20, 70, x + w + 20, 70);

  painter.setPen(pen);
  font.setPixelSize(15);
  painter.setFont(font);
  painter.setPen(QColor("lime"));
  painter.drawText(90, 150, GAME_MESSAGE_1);
  painter.drawText(90, 170, GAME_MESSAGE_2);
  painter.drawText(90, 190, GAME_MESSAGE_3);
  painter.setPen(QColor("yellow"));
  painter.drawText(90, 210, GAME_MESSAGE_4);

  w = painter.fontMetrics().width(SPACE_MESSAGE);
  x = int((width() - w) / 2.0);
  int h = painter.fontMetrics().height() + 6;
  painter.setPen(QColor("blue"));
  painter.setBrush(QColor("white"));
  painter.drawRect(x - 20, 240 - h - 4, w + 40, h + 6);
  painter.drawText(x, 240, SPACE_MESSAGE);
}
