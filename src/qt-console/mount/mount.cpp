/*
   BAREOS® - Backup Archiving REcovery Open Sourced

   Copyright (C) 2007-2007 Free Software Foundation Europe e.V.
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
 * Label Dialog class
 *
 * Kern Sibbald, February MMVII
 */

#include "bat.h"
#include "mount/mount.h"
#include <QMessageBox>

/*
 * A constructor
 */
mountDialog::mountDialog(Console *console, QString &storageName) : QDialog()
{
   m_console = console;
   m_storageName = storageName;
   m_conn = m_console->notifyOff();
   setupUi(this);
   this->show();

   QString labelText( tr("Storage : %1").arg(storageName) );
   storageLabel->setText(labelText);
}

void mountDialog::accept()
{
   QString scmd;
   if (m_storageName == "") {
      QMessageBox::warning(this, tr("No Storage name"), tr("No Storage name given"),
                           QMessageBox::Ok, QMessageBox::Ok);
      return;
   }
   this->hide();
   scmd = QString("mount storage=\"%1\" slot=%2")
                  .arg(m_storageName)
                  .arg(slotSpin->value());
   if (mainWin->m_commandDebug) {
      Pmsg1(000, "sending command : %s\n",scmd.toUtf8().data());
   }

   m_console->display_text( tr("Context sensitive command :\n\n"));
   m_console->display_text("****    ");
   m_console->display_text(scmd + "    ****\n");
   m_console->display_text(tr("Director Response :\n\n"));

   m_console->write_dir(scmd.toUtf8().data());
   m_console->displayToPrompt(m_conn);
   m_console->notify(m_conn, true);
   delete this;
   mainWin->resetFocus();
}

void mountDialog::reject()
{
   this->hide();
   m_console->notify(m_conn, true);
   delete this;
   mainWin->resetFocus();
}
