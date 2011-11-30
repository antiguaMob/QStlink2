/*
This file is part of QSTLink2.

    QSTLink2 is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    QSTLink2 is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with QSTLink2.  If not, see <http://www.gnu.org/licenses/>.
*/
#include <QtGui/QApplication>
#include "mainwindow.h"
#include <QStringList>

quint8 verbose_level = 2;
QStringList args;

void myMessageOutput(QtMsgType type, const char *msg)
{
    if (verbose_level) {
        switch (type) {
        case QtFatalMsg:
                fprintf(stderr, "Fatal: %s\n", msg);
                abort();
        case QtCriticalMsg:
            if (verbose_level >= 2)
                fprintf(stderr, "Error: %s\n", msg);
            break;
        case QtWarningMsg:
            if (verbose_level >= 3)
                fprintf(stderr, "Warning: %s\n", msg);
            break;
        case QtDebugMsg:
            if (verbose_level >= 4)
                fprintf(stderr, "Debug: %s\n", msg);
            break;
        }
    }
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    args = QCoreApplication::arguments();
    foreach (const QString &str, args) {
             if (str.contains("quiet"))
                 verbose_level = 0;
             if (str.contains("error"))
                 verbose_level = 2;
             if (str.contains("warn"))
                 verbose_level = 3;
             if (str.contains("debug"))
                 verbose_level = 4;
         }

    qDebug() << "Verbose level:" << verbose_level;
    qInstallMsgHandler(myMessageOutput);
    MainWindow w;
    w.show();

    return a.exec();
}