#include "mainwindow.h"

#include "helpframe.h"
#include "startscreen.h"
#include "virusscreen.h"

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

  QFrame* screen_frame = new QFrame(this);

  m_screen_stack = new QStackedLayout(this);
  m_screen_stack->setStackingMode(QStackedLayout::StackAll);

  screen_frame->setLayout(m_screen_stack);

  m_screen = new VirusScreen(this);
  connect(m_screen, &VirusScreen::gameFinished, this, &MainWindow::setToStart);
  connect(m_screen, &VirusScreen::crashed, this, &MainWindow::woop);
  connect(m_screen, &VirusScreen::crashed, this, &MainWindow::setToStart);
  connect(m_screen, &VirusScreen::crashed, this, &MainWindow::greyout);

  m_greyscreen = new QLabel(this);
  //  m_greyscreen->setSizePolicy(QSizePolicy::Expanding,
  //    QSizePolicy::Expanding);
  m_greyscreen->setStyleSheet("background-color: rgba(0, 0, 0, 0.7);");
  //  m_greyscreen->setVisible(false);
  m_screen_stack->addWidget(m_greyscreen);
  m_screen_stack->addWidget(m_screen);
  m_screen_stack->setCurrentWidget(m_screen);

  m_screen_id = main_layout->addWidget(screen_frame);

  HelpScreen* help = new HelpScreen(this);
  m_help_id = main_layout->addWidget(help);

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
    } else
      return false;
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
  m_woop->setLoops(count);
  m_woop->play();
}

void
MainWindow::greyout(bool value)
{
  if (value) {
    m_screen_stack->setCurrentWidget(m_greyscreen);
  }
}
