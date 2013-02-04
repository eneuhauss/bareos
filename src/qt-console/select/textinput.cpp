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
 * Select dialog class
 *
 * Kern Sibbald, March MMVII
 */

#include "bat.h"
#include "textinput.h"

/*
 * Read input text box
 */
textInputDialog::textInputDialog(Console *console, int conn)
{
   m_conn = conn;
   QDateTime dt;

   m_console = console;
   m_console->notify(m_conn, false);
   setupUi(this);
   setAttribute(Qt::WA_DeleteOnClose);
   m_console->read(m_conn);                 /* get title */
   labelWidget->setText(m_console->msg(m_conn));
   this->show();
}

void textInputDialog::accept()
{
   this->hide();
   m_console->write_dir(m_conn, lineEdit->text().toUtf8().data());
   /* Do not displayToPrompt because there may be another Text Input required */
   this->close();
   mainWin->resetFocus();
   m_console->notify(m_conn, true);
}


void textInputDialog::reject()
{
   this->hide();
   mainWin->set_status(tr(" Canceled"));
   m_console->write_dir(m_conn, ".");
   this->close();
   mainWin->resetFocus();
   m_console->beginNewCommand(m_conn);
   m_console->notify(m_conn, true);
}
