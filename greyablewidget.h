#ifndef GREYABLEFRAME_H
#define GREYABLEFRAME_H

#include <QFrame>
#include <QLabel>
#include <QStackedLayout>

class GreyableWidget : public QFrame
{
public:
  GreyableWidget(QWidget* parent = nullptr);

  QWidget* widget() const;
  void setWidget(QWidget* widget);

  void greyout();
  void greyout(QColor color, int percent);
  void clear();

  void setGreyoutColor(const QColor& greyoutColor);
  QColor greyoutColor() const;

  int percentage() const;
  void setPercentage(int percent);

protected:
  QStackedLayout* m_screen_stack;
  QLabel* m_greyscreen;
  QWidget* m_widget;
  QColor m_greyout_color;
  int m_percentage;

  void setGreyoutString();
  void clearGreyoutString();
  void setGreyoutString(QColor color, int percent);

  static const QString STYLE_STRING;
  static const QString CLEAR_STRING;
};

#endif // GREYABLEFRAME_H
