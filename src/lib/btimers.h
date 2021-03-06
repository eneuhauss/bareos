/*
   BAREOS® - Backup Archiving REcovery Open Sourced

   Copyright (C) 2003-2007 Free Software Foundation Europe e.V.
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
 * Process and thread timer routines, built on top of watchdogs.
 *
 * Nic Bellamy <nic@bellamy.co.nz>, October 2003.
 *
*/

#ifndef __BTIMERS_H_
#define __BTIMERS_H_

struct btimer_t {
   watchdog_t *wd;                    /* Parent watchdog */
   int type;
   bool killed;
   pid_t pid;                         /* process id if TYPE_CHILD */
   pthread_t tid;                     /* thread id if TYPE_PTHREAD */
   BSOCK *bsock;                      /* Pointer to BSOCK */
   JCR *jcr;                          /* Pointer to job control record */
};

#endif /* __BTIMERS_H_ */
