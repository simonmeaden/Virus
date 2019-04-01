#ifndef STARTSCREEN_H
#define STARTSCREEN_H

#include <QFont>
#include <QFontDatabase>
#include <QFrame>
#include <QPainter>

class StartScreen : public QFrame
{
  Q_OBJECT
public:
  explicit StartScreen(QWidget* parent = nullptr);

signals:

public slots:
protected:
  void paintEvent(QPaintEvent* event) override;

  static const QString VIRUS_NAME;
  static const QString GAME_MESSAGE_1;
  static const QString GAME_MESSAGE_2;
  static const QString GAME_MESSAGE_3;
  static const QString GAME_MESSAGE_4;
  static const QString FUCKED_MESSAGE;
  static const QString SPACE_MESSAGE;
};

#endif // STARTSCREEN_H
