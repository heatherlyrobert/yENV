/*===[[ START ]]==============================================================*/
#include    "yENV.h"
#include    "yENV_priv.h"



/*===[[ GNU GENERAL PUBLIC LICENSE (GPL) ]]===================================*/
/*´´·········1·········2·········3·········4·········5·········6·········7·········8  */

#define  P_COPYRIGHT   \
   "copyright (c) 2020 robert.s.heatherly at balsashrike at gmail dot com"

#define  P_LICENSE     \
   "the only place you could have gotten this code is my github, my website,¦"   \
   "or illegal sharing. given that, you should be aware that this is GPL licensed."

#define  P_COPYLEFT    \
   "the GPL COPYLEFT REQUIREMENT means any modifications or derivative works¦"   \
   "must be released under the same GPL license, i.e, must be free and open."

#define  P_INCLUDE     \
   "the GPL DOCUMENTATION REQUIREMENT means that you must include the original¦" \
   "copyright notice and the full licence text with any resulting anything."

#define  P_AS_IS       \
   "the GPL NO WARRANTY CLAUSE means the software is provided without any¦"      \
   "warranty and the author cannot be held liable for damages."

#define  P_THEFT    \
   "if you knowingly violate the spirit of these ideas, i suspect you might "    \
   "find any number of freedom-minded hackers may take it quite personally ;)"

/*´´·········1·········2·········3·········4·········5·········6·········7·········8  */
/*===[[ GNU GENERAL PUBLIC LICENSE (GPL) ]]===================================*/

/*
 *
 *  stdin is a queue (not a stack) so data would appear to be backwards if
 *  viewed in a conventional way.
 *
 *     åsample·text¦æ                 therefore yUNIT "load" reverses any
 *       (source)                     text added, i.e., loads backwards.
 *                  1   s
 *                  2   as
 *                  3   mas
 *        queue     4   pmas
 *        while     5   lpmas
 *       adding     6   elpmas
 *                  7   ·elpmas
 *                  8   t·elpmas
 *                  9   et·elpmas
 *                 10   xet·elpmas
 *                 11   txet·elpmas
 *                 12   ¦txet·elpmas
 *
 *                  1   ¦txet·elpma   s
 *                  2   ¦txet·elpm    sa
 *        queue     3   ¦txet·elp     sam
 *        while     4   ¦txet·el      samp
 *   retrieving     5   ¦txet·e       sampl             string array
 *                  6   ¦txet·        sample            built while
 *                  7   ¦txet         sample·           removing
 *                  8   ¦txe          sample·t
 *                  9   ¦tx           sample·te
 *                 10   ¦t            sample·tex
 *                 11   ¦             sample·text
 *                 12                åsample·text¦æ
 *
 *
 *  unit-testing example
 *
 *     åfirst·record¦sample·text¦partialæ
 *
 *                 creates
 *
 *     ålaitrap¦txet·elpmas¦drocer·tsrifæ
 *
 *  result    characters   32   (including carriage returns)
 *            full lines   2    (number of carriage returns)
 *            current      åfirst·record¦æ
 *            length       13
 *            overrun      12 characters
 *
 *
 *  capabilities       status (like just above)
 *                     peek at entries (cursor and index)
 *                     retrieve first character
 *                     retrieve first line
 *                     clear first character
 *                     clear first line
 *                     clear everything
 *             
 *  use a LEN_HUGE for buffer to accomodate big build-ups only for
 *  diagnostics as this is a little extensive.
 *
 */


static int    S_flags     =   -1;

static char   S_blocked   =  '-';
static char   S_any       =  '-';                /* are there any characters     */
static char   S_full      =  '-';                /* is there a full line to read */
static uchar  S_queue     [LEN_HUGE]  = "";      /* full queue in stdin          */
static int    S_nchar     =    0;                /* length of full queue         */
static uchar  S_curr      [LEN_RECD]  = "";      /* current line content         */
static int    S_ncurr     =    0;                /* length of current line       */
static int    S_cr        =    0;                /* count of returns             */
static int    S_over      =    0;                /* chars past last return       */
static int    S_bad       =    0;                /* count of bad characters      */


char
yENV_stdin_unblock      (void)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;          /* return code for errors         */
   int         rc          =    0;
   int         x_flags     =    0;
   /*---(header)-------------------------*/
   DEBUG_YENV   yLOG_senter  (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YENV   yLOG_sint    (S_flags);
   --rce;  if (S_flags != -1) {
      DEBUG_YENV   yLOG_snote   ("flags already set, can not open");
      DEBUG_YENV   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(get current status)-------------*/
   DEBUG_YENV   yLOG_snote   ("make stdin non-blocking");
   S_flags = fcntl (0, F_GETFL, 0);
   DEBUG_YENV   yLOG_sint    (S_flags);
   x_flags = S_flags | O_NONBLOCK;
   DEBUG_YENV   yLOG_sint    (x_flags);
   if (S_flags == x_flags) {
      DEBUG_YENV   yLOG_snote   ("already unblocked");
      S_blocked = '-';
      DEBUG_YENV   yLOG_sexit   (__FUNCTION__);
      return RC_ACK;
   }
   S_blocked = 'y';
   /*---(set stdin to non-blocking)------*/
   rc = fcntl (0, F_SETFL, x_flags);
   DEBUG_YENV   yLOG_sint    (rc);
   --rce;  if (rc < 0) {
      DEBUG_YENV   yLOG_snote   ("can not set to non-blocking");
      S_flags = -1;
      DEBUG_YENV   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(report)-------------------------*/
   DEBUG_YENV   yLOG_snote   ("success");
   /*---(complete)-----------------------*/
   DEBUG_YENV   yLOG_sexit   (__FUNCTION__);
   return RC_POSITIVE;
}

char
yENV_stdin_block        (void)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;          /* return code for errors         */
   int         rc          =    0;
   int         x_flags     =    0;
   /*---(header)-------------------------*/
   DEBUG_YENV   yLOG_senter  (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YENV   yLOG_sint    (S_flags);
   --rce;  if (S_flags == -1) {
      DEBUG_YENV   yLOG_snote   ("flags not set, call not close");
      DEBUG_YENV   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(get current status)-------------*/
   DEBUG_YENV   yLOG_snote   ("make stdin non-blocking");
   x_flags = fcntl (0, F_GETFL, 0);
   DEBUG_YENV   yLOG_sint    (x_flags);
   DEBUG_YENV   yLOG_sint    (S_flags);
   if (S_flags == x_flags) {
      DEBUG_YENV   yLOG_snote   ("was unblocked before, leave alone");
      DEBUG_YENV   yLOG_sexit   (__FUNCTION__);
      return RC_ACK;
   }
   /*---(put stdin back to normal)-------*/
   DEBUG_YENV   yLOG_snote   ("put stdin back to blocked");
   rc = fcntl  (0, F_SETFL, S_flags);
   DEBUG_YENV   yLOG_sint    (rc);
   --rce;  if (rc < 0) {
      DEBUG_YENV   yLOG_snote   ("can not set to back to normal");
      DEBUG_YENV   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(report)-------------------------*/
   DEBUG_YENV   yLOG_snote   ("success");
   S_flags = -1;
   DEBUG_YENV   yLOG_sint    (S_flags);
   /*---(complete)-----------------------*/
   DEBUG_YENV   yLOG_sexit   (__FUNCTION__);
   return RC_POSITIVE;
}

char
yenv_stdin__clear       (void)
{
   /*---(status)-------------------------*/
   S_any      =  '-';
   S_full     =  '-';
   /*---(queue)--------------------------*/
   strcpy (S_queue, "");
   S_nchar    =    0;
   /*---(current)------------------------*/
   strcpy (S_curr , "");
   S_ncurr    =    0;
   /*---(stats)--------------------------*/
   S_cr       =    0;
   S_over     =    0;
   S_bad      =    0;
   /*---(complete)-----------------------*/
   return 0;
}

char
yenv_stdin__collect     (char a_action)
{  /*---(design notes)-------------------*/
   /*
    *  x = purge stdin
    *  e = check for eof
    *  - = collect data
    *
    */
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;
   char        x_temp      =  '-';
   int         rc          =    0;
   uchar       x_ch        =    0;
   uchar       x_vis       =    0;
   int         i           =    0;
   char        x_1st_cr    =  '-';
   char        x_eof       =  '-';
   /*---(header)-------------------------*/
   DEBUG_YENV   yLOG_enter   (__FUNCTION__);
   /*---(prepare)------------------------*/
   yenv_stdin__clear ();
   /*---(defense)------------------------*/
   DEBUG_YENV   yLOG_char    ("a_action"  , a_action);
   --rce;  if (a_action == 0 || strchr ("xe-", a_action) == NULL) {
      DEBUG_YENV   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(check for unblocked)------------*/
   DEBUG_YENV   yLOG_value   ("S_flags"   , S_flags);
   --rce;  if (S_flags == -1) {
      DEBUG_YENV   yLOG_note    ("must unblock stdin temporarily");
      x_temp = 'y';
      rc = yENV_stdin_unblock ();
      DEBUG_YENV   yLOG_value   ("unblock"   , rc);
      if (rc < 0) {
         DEBUG_YENV   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
   }
   /*---(prepare)------------------------*/
   rc = getc (stdin);
   DEBUG_YENV   yLOG_value   ("getc"      , rc);
   if (a_action == 'e')  {
      if (rc >= 0)  ungetc (rc, stdin);
      else          x_eof = 'y';
   }
   /*---(quick eof end)------------------*/
   else if (rc == -1) {
      x_eof = 'y';
   }
   /*---(collect statistics)-------------*/
   else while (rc != -1) {
      /*---(flags)--------------------*/
      S_any  = 'y';
      x_vis  = rc;
      if (x_vis <   32)  x_vis = 'Ï';
      if (x_vis == 127)  x_vis = 'Ï';
      /*---(defense)------------------*/
      if (x_ch >= 0 && x_ch <= 255) {
         DEBUG_YENV   yLOG_complex ("loop"      , "%4d  %4d/%c", S_nchar, x_ch, x_vis);
         x_ch = rc;
      } else {
         DEBUG_YENV   yLOG_complex ("BOOM"      , "%4d  %4d/%c out-of-bounds", S_nchar, x_ch, x_vis);
         x_ch = (uchar) '°';
         ++S_bad;
      }
      /*---(add to queue)-------------*/
      S_queue [S_nchar]   = x_ch;
      S_queue [++S_nchar] = '\0';
      /*---(add to current)-----------*/
      if (x_1st_cr == '-') {
         DEBUG_YENV   yLOG_note    ("still working on current");
         S_curr  [S_ncurr]   = x_ch;
         S_curr  [++S_ncurr] = '\0';
      }
      /*---(count overrun)------------*/
      ++S_over;
      /*---(handle returns)-----------*/
      if (x_ch == '\n') {
         DEBUG_YENV   yLOG_note    ("found return/new line");
         S_full   = 'y';
         x_1st_cr = 'y';
         ++S_cr;
         S_over   = 0;
      }
      /*---(stats)--------------------*/
      DEBUG_YENV   yLOG_complex ("queue"     , "%4då%sæ", S_nchar, S_queue);
      DEBUG_YENV   yLOG_complex ("current"   , "%4då%sæ", S_ncurr, S_curr);
      DEBUG_YENV   yLOG_complex ("stats"     , "cr   = %4d, over = %4d, bad  = %4d", S_cr, S_over, S_bad);
      /*---(get next)-----------------*/
      rc = getc (stdin);
      DEBUG_YENV   yLOG_value   ("rc"        , rc);
      /*---(done)---------------------*/
   }
   /*---(put it back)--------------------*/
   switch (a_action) {
   case 'x' :  yenv_stdin__clear ();   x_eof = 'y';  break;
   case '-' :  for (i = S_nchar - 1; i >= 0; --i)   ungetc (S_queue [i], stdin);   break;
   }
   /*---(check for re-blocking)----------*/
   DEBUG_YENV   yLOG_char    ("x_temp"    , x_temp);
   --rce;  if (x_temp == 'y') {
      DEBUG_YENV   yLOG_note    ("must now re-block stdin (temporary use)");
      rc = yENV_stdin_block ();
      DEBUG_YENV   yLOG_value   ("block"   , rc);
      if (rc < 0) {
         DEBUG_YENV   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
   }
   /*---(complete)-----------------------*/
   DEBUG_YENV   yLOG_exit    (__FUNCTION__);
   if (x_eof == 'y')  return RC_DONE;
   return RC_POSITIVE;
}

char yENV_stdin_purge  (void)  { return yenv_stdin__collect ('x'); }
char yENV_stdin_eof    (void)  { return yenv_stdin__collect ('e'); }

char
yENV_stdin_fgets        (char r_recd [LEN_RECD])
{
   char        rc          =    0;
   int         i           =    0;
   if (r_recd != NULL)  strcpy (r_recd, "");
   rc = yenv_stdin__collect ('-');
   if (rc == RC_DONE)   return RC_DONE;
   if (S_full == 'y') {
      if (r_recd != NULL)  strlcpy (r_recd, S_curr, LEN_RECD);
      for (i = 0; i < S_ncurr; ++i)  getc (stdin);
      return RC_POSITIVE;
   }
   return RC_ACK;
}

/*  --block---  A  -state-  F  -len ---queue----------------------------------------------------  -len ---current------------------------------  -cr  ovr  bad  Ï  */
/*  ´·········  -  ·······  -  ···- ´···························································  ···- ´·······································  ··-  ··-  ··-  Ï  */

char*
yENV_stdin_status       (void)
{
   char        x_block     [LEN_LABEL] = "unblocked·";
   char        x_state     [LEN_LABEL] = "avail·";
   char        x_queue     [LEN_HUND]  = "´···························································";
   char        x_curr      [LEN_HUND]  = "´·······································";
   int         i           =    0;
   /*---(collect)------------------------*/
   yenv_stdin__collect ('-');
   /*---(prepare)------------------------*/
   if (S_blocked == 'y')  strcpy  (x_block, "BLOCKING··");
   if (S_any     == '-')  strcpy  (x_state, "EOF···");
   if (S_nchar   >   0 )  sprintf (x_queue, "%.60s····························································", S_queue);
   if (S_nchar   >= 60 )  x_queue [60] = '>';
   for (i = 0; i < LEN_HUND; ++i)  { if (x_queue [i] == '\n')  x_queue [i] = (uchar) '¦';  if (x_queue [i] == ' ')  x_queue [i] = (uchar) '·'; }
   if (S_ncurr   >   0 )  sprintf (x_curr , "%.40s····························································", S_curr);
   if (S_ncurr   >= 60 )  x_curr  [40] = '>';
   for (i = 0; i < LEN_HUND; ++i)  { if (x_curr  [i] == '\n')  x_curr  [i] = (uchar) '¦';  if (x_curr  [i] == ' ')  x_curr  [i] = (uchar) '·'; }
   /*---(check eof)----------------------*/
   sprintf (g_print, "%-10.10s  %c  %-6.6s  %c  %4d %-60.60s  %4d %-40.40s  %3d  %3d  %3d  Ï",
         x_block, S_any, x_state, S_full,
         S_nchar, x_queue, S_ncurr, x_curr,
         S_cr, S_over, S_bad);
   return g_print;
}


