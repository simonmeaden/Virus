#ifndef GREYABLEFRAME_H
#define GREYABLEFRAME_H

#include <QDebug>
#include <QFrame>
#include <QLabel>
#include <QPainter>
#include <QStackedLayout>
#include <QStyleOption>
#include <QTimer>

class MessageWidget : public QLabel
{
  Q_OBJECT
public:
  MessageWidget(QWidget* parent = nullptr);
  ~MessageWidget();

  QString message() const;
  void setMessage(const QString& message);

  void enableMessage();
  void disableMessage();

protected:
  bool m_paint_message;
  QString m_message;

  void paintEvent(QPaintEvent*) override;
};

class GreyableWidget : public QFrame
{
  Q_OBJECT
public:
  GreyableWidget(QWidget* parent = nullptr);
  ~GreyableWidget();

  QWidget* widget() const;
  void setWidget(QWidget* widget);

  void greyout();
  void greyout(QColor color, int percent);
  void clearGreyout();

  void setGreyoutColor(const QColor& greyoutColor);
  QColor greyoutColor() const;

  int percentage() const;
  void setPercentage(int percent);

  void setMessage(QString message, int timeout);
  void clearMessage();

protected:
  QStackedLayout* m_screen_stack;
  QLabel* m_greyscreen;
  MessageWidget* m_messagescreen;
  QWidget* m_widget;
  QColor m_greyout_color;
  int m_percentage;

  void setGreyoutString();
  void clearGreyoutString();
  void setGreyoutString(QColor color, int percent);

  static const QString OPACITY_STRING;
  static const QString CLEAR_STRING;
};

#endif // GREYABLEFRAME_H
