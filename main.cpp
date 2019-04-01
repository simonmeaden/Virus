#include "mainwindow.h"
#include <QApplication>

#include <QLoggingCategory>

#include "log4qt/consoleappender.h"
//#include "log4qt/loggerobject.h"
#include "log4qt/logger.h"
#include "log4qt/logmanager.h"
#include "log4qt/ttcclayout.h"

int
main(int argc, char* argv[])
{
  QApplication a(argc, argv);

  //  auto* object = new LoggerObject(&a);
  QLoggingCategory::setFilterRules("*.debug=false\n"
                                   "virus.debug=true");

  auto logger = Log4Qt::Logger::rootLogger();
  auto* layout = new Log4Qt::TTCCLayout();
  layout->setName(QStringLiteral("My Layout"));
  layout->activateOptions();
  // Create a console appender
  Log4Qt::ConsoleAppender* consoleAppender =
    new Log4Qt::ConsoleAppender(layout, Log4Qt::ConsoleAppender::STDOUT_TARGET);
  consoleAppender->setName(QStringLiteral("Virus2 Appender"));
  consoleAppender->activateOptions();
  // Add appender on root logger
  logger->addAppender(consoleAppender);
  // Set level to info
  logger->setLevel(Log4Qt::Level::INFO_INT);
  // Enable handling of Qt messages
  Log4Qt::LogManager::setHandleQtMessages(true);
  qWarning("Handling Qt messages is enabled");

  MainWindow w;
  w.show();

  return a.exec();
}
