/*
   BAREOS® - Backup Archiving REcovery Open Sourced

   Copyright (C) 2000-2011 Free Software Foundation Europe e.V.
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
 * Define Message Types for BAREOS
 *
 * Kern Sibbald, 2000
 */
#include "bits.h"

#undef  M_DEBUG
#undef  M_ABORT
#undef  M_FATAL
#undef  M_ERROR
#undef  M_WARNING
#undef  M_INFO
#undef  M_MOUNT
#undef  M_ERROR_TERM
#undef  M_TERM
#undef  M_RESTORED
#undef  M_SECURITY
#undef  M_ALERT
#undef  M_VOLMGMT

/*
 * Most of these message levels are more or less obvious.
 * They have evolved somewhat during the development of BAREOS,
 * and here are some of the details of where I am trying to
 * head (in the process of changing the code) as of 15 June 2002.
 *
 *  M_ABORT       BAREOS immediately aborts and tries to produce a traceback
 *                  This is for really serious errors like segmentation fault.
 *  M_ERROR_TERM  BAREOS immediately terminates but no dump. This is for
 *                  "obvious" serious errors like daemon already running or
 *                   cannot open critical file, ... where a dump is not wanted.
 *  M_TERM        BAREOS daemon shutting down because of request (SIGTERM).
 *
 * The remaining apply to Jobs rather than the daemon.
 *
 *  M_FATAL       BAREOS detected a fatal Job error. The Job will be killed,
 *                  but BAREOS continues running.
 *  M_ERROR       BAREOS detected a Job error. The Job will continue running
 *                  but the termination status will be error.
 *  M_WARNING     Job warning message.
 *  M_INFO        Job information message.
 *
 *  M_RESTORED    An ls -l of each restored file.
 *
 *  M_SECURITY    For security viloations. This is equivalent to FATAL.
 *                (note, this is currently being implemented in 1.33).
 *
 *  M_ALERT       For Tape Alert messages.
 *
 *  M_VOLMGMT     Volume Management message
 */

enum {
   /* Keep M_ABORT=1 for dlist.h */
   M_ABORT = 1,                       /* MUST abort immediately */
   M_DEBUG,                           /* debug message */
   M_FATAL,                           /* Fatal error, stopping job */
   M_ERROR,                           /* Error, but recoverable */
   M_WARNING,                         /* Warning message */
   M_INFO,                            /* Informational message */
   M_SAVED,                           /* Info on saved file */
   M_NOTSAVED,                        /* Info on notsaved file */
   M_SKIPPED,                         /* File skipped during backup by option setting */
   M_MOUNT,                           /* Mount requests */
   M_ERROR_TERM,                      /* Error termination request (no dump) */
   M_TERM,                            /* Terminating daemon normally */
   M_RESTORED,                        /* ls -l of restored files */
   M_SECURITY,                        /* security violation */
   M_ALERT,                           /* tape alert messages */
   M_VOLMGMT                          /* Volume management messages */
};

#define M_MAX M_VOLMGMT               /* keep this updated ! */
#define NR_MSG_TYPES nbytes_for_bits(M_MAX + 1)

/* Define message destination structure */
/* *** FIXME **** where should be extended to handle multiple values */
typedef struct s_dest {
   struct s_dest *next;
   int dest_code;                     /* destination (one of the MD_ codes) */
   int max_len;                       /* max mail line length */
   FILE *fd;                          /* file descriptor */
   char msg_types[NR_MSG_TYPES];      /* message type mask */
   char *where;                       /* filename/program name */
   char *mail_cmd;                    /* mail command */
   POOLMEM *mail_filename;            /* unique mail filename */
} DEST;

/* Message Destination values for dest field of DEST */
enum {
   MD_SYSLOG = 1,                     /* send msg to syslog */
   MD_MAIL,                           /* email group of messages */
   MD_FILE,                           /* write messages to a file */
   MD_APPEND,                         /* append messages to a file */
   MD_STDOUT,                         /* print messages */
   MD_STDERR,                         /* print messages to stderr */
   MD_DIRECTOR,                       /* send message to the Director */
   MD_OPERATOR,                       /* email a single message to the operator */
   MD_CONSOLE,                        /* send msg to UserAgent or console */
   MD_MAIL_ON_ERROR,                  /* email messages if job errors */
   MD_MAIL_ON_SUCCESS,                /* email messages if job succeeds */
   MD_CATALOG                         /* sent to catalog Log table */
};

/* Queued message item */
struct MQUEUE_ITEM {
   dlink link;
   int type;
   utime_t mtime;
   char msg[1];
};

extern "C" {
   typedef char *(*job_code_callback_t)(JCR *, const char *);
}

void d_msg(const char *file, int line, int level, const char *fmt,...);
void e_msg(const char *file, int line, int type, int level, const char *fmt,...);
void Jmsg(JCR *jcr, int type, utime_t mtime, const char *fmt,...);
void Qmsg(JCR *jcr, int type, utime_t mtime, const char *fmt,...);
bool get_trace(void);
const char *get_basename(const char *pathname);

typedef bool (*db_log_insert_func)(JCR *jcr, utime_t mtime, char *msg);
extern DLL_IMP_EXP db_log_insert_func p_db_log_insert;

extern DLL_IMP_EXP int debug_level;
extern DLL_IMP_EXP bool dbg_timestamp; /* print timestamp in debug output */
extern DLL_IMP_EXP bool prt_kaboom;    /* Print kaboom output */
extern DLL_IMP_EXP int verbose;
extern DLL_IMP_EXP char my_name[];
extern DLL_IMP_EXP const char *assert_msg; /* Assert error message */
extern DLL_IMP_EXP const char *working_directory;
extern DLL_IMP_EXP utime_t daemon_start_time;

extern DLL_IMP_EXP int console_msg_pending;
extern DLL_IMP_EXP FILE *con_fd;       /* Console file descriptor */
extern DLL_IMP_EXP brwlock_t con_lock; /* Console lock structure */
