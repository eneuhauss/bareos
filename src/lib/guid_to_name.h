/*
   BAREOS® - Backup Archiving REcovery Open Sourced

   Copyright (C) 2007 Kern Sibbald
   Copyright (C) 2011-2012 Planets Communications B.V.
   Copyright (C) 2013-2013 Bareos GmbH & Co. KG

   This program is Free Software; you can redistribute it and/or
   modify it under the terms of version three of the GNU Affero General Public
   License as published by the Free Software Foundation, which is
   listed in the file LICENSE.

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
 * Written by Kern Sibbald, July 2007 to replace idcache.c
 *
 * Program to convert uid and gid into names, and cache the results
 * for preformance reasons.
 */

class guid_list {
public:
   dlist *uid_list;
   dlist *gid_list;

   char *uid_to_name(uid_t uid, char *name, int maxlen);
   char *gid_to_name(gid_t gid, char *name, int maxlen);
};

guid_list *new_guid_list();
void free_guid_list(guid_list *list);
