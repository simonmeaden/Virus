#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFontDatabase>
#include <QFrame>
#include <QGuiApplication>
//#include <QApplication>
#include <QHBoxLayout>
#include <QLabel>
#include <QMainWindow>
#include <QScreen>
#include <QSound>
#include <QStackedLayout>

class VirusScreen;

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget* parent = nullptr);
  ~MainWindow() override;

protected:
  QStackedLayout* main_layout;
  VirusScreen* m_screen;
  QLabel* m_greyscreen;
  int m_start_id, m_screen_id, m_help_id;
  QSound* m_woop;

  void initGui();
  bool eventFilter(QObject*, QEvent* event) override;
  void setToScreen();
  void setToHelp();
  void setToStart();
  void woop(int count = 1);

  static const int WIDTH = 700; // 616;
  static const int HEIGHT = 480;

private:
};

#endif // MAINWINDOW_H
