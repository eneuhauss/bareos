/*
   BAREOS® - Backup Archiving REcovery Open Sourced

   Copyright (C) 2007-2010 Free Software Foundation Europe e.V.
   Copyright (C) 2011-2012 Planets Communications B.V.
   Copyright (C) 2013-2013 Bareos GmbH & Co. KG

   This program is Free Software; you can redistribute it and/or
   modify it under the terms of version three of the GNU Affero General Public
   License as published by the Free Software Foundation and included
   in the file LICENSE.

   This program is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
   Affero General Public License for more details.

   You should have received a copy of the GNU Affero General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
   02110-1301, USA.
*/

/*
 * Help Window class
 *
 * Kern Sibbald, May MMVII
 */

#include "bat.h"
#include "help.h"

/*
 * Note: HELPDIR is defined in src/host.h
 */

Help::Help(const QString &path, const QString &file, QWidget *parent) :
        QWidget(parent)
{
   setAttribute(Qt::WA_DeleteOnClose);     /* Make sure we go away */
   setAttribute(Qt::WA_GroupLeader);       /* allow calling from modal dialog */

   setupUi(this);                          /* create window */

   textBrowser->setSearchPaths(QStringList() << HELPDIR << path << ":/images");
   textBrowser->setSource(file);
   //textBrowser->setCurrentFont(mainWin->m_consoleHash.values()[0]->get_font());

   connect(textBrowser, SIGNAL(sourceChanged(const QUrl &)), this, SLOT(updateTitle()));
   connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));
   connect(homeButton, SIGNAL(clicked()), textBrowser, SLOT(home()));
   connect(backButton, SIGNAL(clicked()), textBrowser, SLOT(backward()));
   this->show();
}

void Help::updateTitle()
{
   setWindowTitle(tr("Help: %1").arg(textBrowser->documentTitle()));
}

void Help::displayFile(const QString &file)
{
   QRegExp rx;
   rx.setPattern("/\\.libs");
   QString path = QApplication::applicationDirPath();
   int pos = rx.indexIn(path);
   if (pos)
      path = path.remove(pos, 6);
   path += "/help";
   new Help(path, file);
}