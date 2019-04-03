#include "mainwindow.h"

#include "greyablewidget.h"
#include "helpscreen.h"
#include "startscreen.h"
#include "virusscreen.h"

#define HIDE_SOUNDS

/*! \mainpage Virus game

   \section intro_sec A simple Snake like game based on the BBC Micro Virus
   game.

   The Virus game is similar to snake but involves the blocking of virus. The
   Virus, denoted by a *, is an auto created snake like figure which wanders
   around the screen leaving a 'tail' of virus cells. You control the
   antibodies, denoted by the 'o' character which behaves in a similar way but
   controlled by you via the direction keys on the keyboard. If your antibody
   hits a virus cell, the wall or your own tail you are eliminated. If you
   succeed in limiting the virus' movement so that it has nowhere to go you win
   this level. At which point a second virus is created and you start again with
   two virus to fight, then three and so on.

   \section install_sec TODO

*/

MainWindow::MainWindow(QWidget* parent)
  : QMainWindow(parent) //,
{
  setWindowTitle("Virus");
  QFontDatabase::addApplicationFont(":/fonts/beeb");
  QGuiApplication::setFont(QFont("Beeb", 10, QFont::Normal));
  QScreen* screen = QGuiApplication::primaryScreen();
  QSize size = screen->availableSize();
  int w = size.width() - WIDTH;
  int h = size.height() - HEIGHT;
  int x = int(w / 2.0);
  int y = int(h / 2.0);

  setGeometry(x, y, WIDTH, HEIGHT);
  initGui();

  m_woop = new QSound(":/sound/woop", this);
}

MainWindow::~MainWindow() {}

void
MainWindow::initGui()
{
  QFrame* stack_frame = new QFrame(this);
  main_layout = new QStackedLayout;
  stack_frame->setLayout(main_layout);
  setCentralWidget(stack_frame);

  setContentsMargins(0, 0, 0, 0);

  StartScreen* start = new StartScreen(this);
  m_start_id = main_layout->addWidget(start);

  m_screen = new VirusScreen(this);
  connect(m_screen, &VirusScreen::gameFinished, this, &MainWindow::setToStart);
  connect(m_screen, &VirusScreen::crashed, this, &MainWindow::woop);
  connect(m_screen, &VirusScreen::switchToStart, this, &MainWindow::setToStart);
  m_screen_id = main_layout->addWidget(m_screen);

  //  HelpScreen* help = new HelpScreen(this);
  //  m_help_id = main_layout->addWidget(help);

  setToStart();

  installEventFilter(this);
  update();
}

bool
MainWindow::eventFilter(QObject* /*object*/, QEvent* event)
{
  if (event->type() == QEvent::KeyPress) {
    QKeyEvent* key_event = static_cast<QKeyEvent*>(event);

    if (key_event->key() == Qt::Key_Up) {
      m_screen->keyNorth();
      return true;

    } else if (key_event->key() == Qt::Key_Down) {
      m_screen->keySouth();
      return true;

    } else if (key_event->key() == Qt::Key_Left) {
      m_screen->keyWest();
      return true;

    } else if (key_event->key() == Qt::Key_Right) {
      m_screen->keyEast();
      return true;

    } else if (key_event->key() == Qt::Key_Space) {
      if (key_event->modifiers().testFlag(Qt::ControlModifier)) {
        main_layout->setCurrentIndex(m_screen_id);
        m_screen->resetGame();

      } else {
        main_layout->setCurrentIndex(m_screen_id);
        m_screen->resetGame();
      }

      return true;

    } else {
      return false;
    }
  }

  return false;
}

void
MainWindow::setToScreen()
{
  main_layout->setCurrentIndex(m_screen_id);
}

void
MainWindow::setToHelp()
{
  main_layout->setCurrentIndex(m_help_id);
}

void
MainWindow::setToStart()
{
  main_layout->setCurrentIndex(m_start_id);
}

void
MainWindow::woop(int count)
{
#ifndef HIDE_SOUNDS
  m_woop->setLoops(count);
  m_woop->play();
#endif
}
