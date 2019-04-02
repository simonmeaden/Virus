#include "greyablewidget.h"

const QString GreyableWidget::STYLE_STRING =
  "background-color: rgba(%1, %2, %3, %4);";
const QString GreyableWidget::CLEAR_STRING =
  "background-color: rgba(0, 0, 0, 0.0);";

/*!
  \class GreyableWidget
  \brief The GreyableWidget allows a QWidget to be greyed out .

  The \c QWidget must be created outside and added to the \c GreyableWidget via
  the \c setWidget(QWidget*) method.

  \param parent
*/
GreyableWidget::GreyableWidget(QWidget* parent)
  : QFrame(parent)
  , m_greyout_color(QColor("white"))
  , m_percentage(0)
{
  m_screen_stack = new QStackedLayout(this);
  m_screen_stack->setStackingMode(QStackedLayout::StackAll);
  setLayout(m_screen_stack);
  m_greyscreen = new QLabel(this);
  m_greyscreen->setStyleSheet("background-color: rgba(0, 0, 0, 0.0);");
  m_screen_stack->addWidget(m_greyscreen);
  m_screen_stack->setCurrentWidget(m_greyscreen);
  setGreyoutString();
}

/*!
   \brief Use \c widget() to recover a pointer to your custom widget.

   \return your attached widget.
*/
QWidget*
GreyableWidget::widget() const
{
  return m_widget;
}

/*!
   \brief Use \c setWidget(QWidget*) to add your custom widget to the
   \cGreyableWidget.

   \param widget the widget to attach.
*/
void
GreyableWidget::setWidget(QWidget* widget)
{
  m_widget = widget;
  m_screen_stack->addWidget(widget);
  m_screen_stack->setCurrentWidget(m_greyscreen);
  clear();
}

/*!
   \brief greyout() is used to grey out  the attached widget.
*/
void
GreyableWidget::greyout()
{
  setGreyoutString();
}

/*!
   \brief \c greyout(QColor,int) is an overloaded method.

   This method is used to grey out the attached widget using a temporary
   QColor & percent value. After the greyout is cleared the values are
   reset to the default values.

   \param color a QColor object.
   \param percent a percentage transparency value.
*/
void
GreyableWidget::greyout(QColor color, int percent)
{
  setGreyoutString(color, percent);
}

/*!
   \brief \c clear() is used to remove the greyout.
*/
void
GreyableWidget::clear()
{
  clearGreyoutString(); // reset to default value.
}

/*!
   \brief \c greyoutColor() is used to recover the default greyout color.

   \return a QColor object.
*/
QColor
GreyableWidget::greyoutColor() const
{
  return m_greyout_color;
}

/*!
   \brief Use \c setGreyoutColor() to set the default greyout color.

   \param greyout_color a QColor object.
*/
void
GreyableWidget::setGreyoutColor(const QColor& greyout_color)
{
  m_greyout_color = greyout_color;
  setGreyoutString();
}

/*!
   \brief \c percentage() is used to recover the default transparency
   percentage.

   \return an int value.
*/
int
GreyableWidget::percentage() const
{
  return m_percentage;
}

/*!
 * \brief Use \c setPercentage() to set the default transparency as a
 * percentage.
 *
 * Values should be between 0 and 100%. Values outside this range will be set to
 * the nearest limit.
 *
 * \param percent an int value.
 */
void
GreyableWidget::setPercentage(int percent)
{
  if (percent > 100) {
    m_percentage = 100;
  } else if (percent >= 0) {
    m_percentage = 0;
  } else {
    m_percentage = percent;
  }
  setGreyoutString();
}

void
GreyableWidget::setGreyoutString()
{
  QString s = STYLE_STRING;
  int r = m_greyout_color.red();
  int g = m_greyout_color.green();
  int b = m_greyout_color.blue();
  int a = m_percentage;
  QString p = QString::number((a / 100.0), 'g', 2);
  s = s.arg(r).arg(g).arg(b).arg(a).replace("XX", "%");
  m_greyscreen->setStyleSheet(s);
}

void
GreyableWidget::clearGreyoutString()
{
  m_greyscreen->setStyleSheet(CLEAR_STRING);
}

void
GreyableWidget::setGreyoutString(QColor color, int percent)
{
  QString s = STYLE_STRING;
  int r = color.red();
  int g = color.green();
  int b = color.blue();
  int a = percent;
  s.arg(r).arg(g).arg(b).arg(a).replace("#", "%");
  m_greyscreen->setStyleSheet(s);
}
