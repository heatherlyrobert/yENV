#include    "yENV_solo.h"



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



typedef struct stat      tSTAT;
/*
 *  half this code is only to make unit testing tighter and
 *  more conclusive, as well as debugging faster.
 *
 *  yENV_uwhich, yENV_uwhere are data access
 *
 *  yenv_uunit, yenv_unormal are just to get more
 *  specific error messages while testing.
 *
 *  specific messages for null, empty, and missing file
 *  help me understand errors while testing other programs.
 *
 *  i didn't start this way, but every second saved debugging
 *  under pressure is worth hours of code improvements.
 *
 */


static char  myenv_upeek  [LEN_RECD] = "";
static int   myenv_ulast  = -1;
static char  myenv_usave  [LEN_PATH] = "";

static char  myenv_overrun  [LEN_LABEL] = "(n/a)";
static char  myenv_underrun [LEN_LABEL] = "(n/a)";

static char  myenv_debug  = '-';
#define    DEBUG_MENV  if (myenv_debug == 'y') 

char  yenv_udebugging (void)  { myenv_debug = 'y'; return myenv_debug; }

char yenv_uunit     (void) { strcpy (myenv_underrun, "(under)"); strcpy (myenv_overrun, "(over)"); return 0; }
char yenv_unormal   (void) { strcpy (myenv_underrun, "(n/a)"  ); strcpy (myenv_overrun, "(n/a)" ); return 0; }



char*
yenv_upeekier           (char a_name [LEN_PATH], char a_dir, int n, int *r_count)
{
   /*---(locals)-----------+-----+-----+-*/
   int         x_curr      =    0;
   FILE       *f           = NULL;
   char        t           [LEN_RECD]  = "";
   int         c           =    0;
   int         x_len       =    0;
   /*---(default)------------------------*/
   if (r_count != NULL)  *r_count = -1;
   /*---(defense)------------------------*/
   if (a_name     == NULL)                { strcpy (myenv_usave, "");  myenv_ulast = -1;  return "(null name)";  }
   if (a_name [0] == '\0')                { strcpy (myenv_usave, "");  myenv_ulast = -1;  return "(empty name)"; }
   /*---(prepare)------------------------*/
   if (strcmp (myenv_usave, a_name) != 0) { strlcpy (myenv_usave, a_name, LEN_PATH); myenv_ulast = -1; }
   strcpy (myenv_upeek, "(n/a)");
   /*---(check cursoring)----------------*/
   x_curr = myenv_ulast;
   switch (a_dir) {
   case YDLST_HEAD  : case YDLST_DHEAD :
      x_curr = 0;
      break;
   case YDLST_PREV  : case YDLST_DPREV :
      if (x_curr <= 0) return myenv_underrun;
      else             --x_curr;
      break;
   case YDLST_CURR  : case YDLST_DCURR :
      break;
   case YDLST_NEXT  : case YDLST_DNEXT : case '·' :  /* · means default */
      ++x_curr;
      break;
   case YDLST_TAIL  : case YDLST_DTAIL :
      x_curr = 999;
      break;
   case YDLST_RESET :
      myenv_ulast = -1;
      return "(reset)";
      break;
   case YDLST_COUNT :
      x_curr = 666;
      break;
   default :
      x_curr = n;
      break;
   }
   /*---(check underrun)-----------------*/
   if (x_curr < 0)  { myenv_ulast = -1; return myenv_underrun;  }
   /*---(open file)----------------------*/
   f = fopen (a_name, "rt");
   if (f == NULL)  { strcpy (myenv_usave, "");  myenv_ulast = -1;  return "(missing)"; }
   /*---(walk file)----------------------*/
   while (1) {
      fgets (t, LEN_RECD, f);
      if (feof (f))  break;
      if (c == x_curr)     strcpy (myenv_upeek, t);
      if (x_curr == 999)   strcpy (myenv_upeek, t);
      ++c;
   }
   /*---(close)--------------------------*/
   fclose (f);
   /*---(save-back)----------------------*/
   if (r_count != NULL)  *r_count = c;
   /*---(handle count)-------------------*/
   if (a_dir == YDLST_COUNT)  return "(count-only)";
   /*---(fix cursor)---------------------*/
   if      (x_curr == 999)  x_curr = c - 1;
   else if (x_curr >= c)    return myenv_overrun;
   /*---(save-position)------------------*/
   myenv_ulast = x_curr;
   /*---(fix end)------------------------*/
   x_len = strlen (myenv_upeek);
   if (x_len > 0 && myenv_upeek [x_len - 1] == '\n')  myenv_upeek [--x_len] = '\0';
   /*---(complete)-----------------------*/
   return myenv_upeek;
}

int    yenv_ulines  (char a_name [LEN_PATH])        { int c = 0;  yenv_upeekier (a_name, YDLST_COUNT, 0, &c); return c; }

char*  yenv_upeek   (char a_name [LEN_PATH], char a_dir) { return yenv_upeekier (a_name, a_dir      , 0, NULL); }
char*  yenv_uindex  (char a_name [LEN_PATH], int  n    ) { return yenv_upeekier (a_name, 0          , n, NULL); }

char*  yenv_uwhich   (void)  { return myenv_usave; }
int    yenv_uwhere   (void)  { return myenv_ulast; }

char
yenv_uexists         (char a_name [LEN_PATH])
{
   char        rce         =  -10;
   char        rc          =    0;
   tSTAT       s;
   char        x_type      =  '-';
   /*---(header)-------------------------*/
   DEBUG_MENV  yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   --rce;  if (a_name     == NULL) {
      DEBUG_MENV  yLOG_exitr   (__FUNCTION__, rce);
      return '°';
   }
   --rce;  if (a_name [0] == '\0') {
      DEBUG_MENV  yLOG_exitr   (__FUNCTION__, rce);
      return '°';
   }
   /*---(check existance)----------------*/
   rc = lstat (a_name, &s);
   DEBUG_MENV  yLOG_value   ("rc"        , rc);
   --rce;  if (rc < 0) {
      DEBUG_MENV  yLOG_note    ("file not found");
      DEBUG_MENV  yLOG_exitr   (__FUNCTION__, rce);
      return '-';
   }
   /*---(normal types)-------------------*/
   if      (S_ISBLK  (s.st_mode))   x_type = 'b';
   else if (S_ISCHR  (s.st_mode))   x_type = 'c';
   else if (S_ISDIR  (s.st_mode))   x_type = 'd';
   else if (S_ISREG  (s.st_mode))   x_type = 'r';
   else if (S_ISSOCK (s.st_mode))   x_type = 'i';
   else if (S_ISFIFO (s.st_mode))   x_type = 'p';
   else if (S_ISLNK  (s.st_mode))   x_type = 's';
   else                             x_type = '?';
   DEBUG_MENV  yLOG_char    ("x_type"    , x_type);
   /*---(complete)-----------------------*/
   DEBUG_MENV  yLOG_exit    (__FUNCTION__);
   return x_type;
}

char*
yenv_uprefix            (char a_dfile [LEN_TITLE], char a_dfunc [LEN_TITLE], int a_dline)
{
   /*---(locals)-----------+-----+-----+-*/
   static char x_prefix    [LEN_HUND]  = "";
   char        x_line      [LEN_TERSE]  = "";
   /*---(header)-------------------------*/
   DEBUG_MENV  yLOG_enter   (__FUNCTION__);
   /*---(create prefix)------------------*/
   if (a_dfile != NULL && a_dfile [0] != '\0')  strlcpy (x_prefix, a_dfile, LEN_HUND);
   else                                         strlcpy (x_prefix, "(n/a)", LEN_HUND);
   strlcat (x_prefix, "/", LEN_HUND);
   if (a_dfunc != NULL && a_dfunc [0] != '\0')  strlcat (x_prefix, a_dfunc, LEN_HUND);
   else                                         strlcat (x_prefix, "(n/a)", LEN_HUND);
   strlcat (x_prefix, ":", LEN_HUND);
   sprintf (x_line, "%d", a_dline);
   if (a_dline >  0)                            strlcat (x_prefix, x_line , LEN_HUND);
   else                                         strlcat (x_prefix, "0"    , LEN_HUND);
   strlcat (x_prefix, ":0", LEN_HUND);
   DEBUG_MENV  yLOG_info    ("x_prefix"  , x_prefix);
   /*---(complete)-----------------------*/
   DEBUG_MENV  yLOG_exit    (__FUNCTION__);
   return x_prefix;
}

char
yenv_uopen_detail       (char a_dfile [LEN_TITLE], char a_dfunc [LEN_TITLE], int a_dline, char a_name [LEN_FULL], char a_mode, FILE **b_file)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   FILE       *f           = NULL;
   char        x_mode      [LEN_TERSE] = "rt";
   char        x_prefix    [LEN_HUND]  = "";
   /*---(header)-------------------------*/
   DEBUG_MENV  yLOG_enter   (__FUNCTION__);
   /*---(create prefix)------------------*/
   strlcpy (x_prefix, yenv_uprefix (a_dfile, a_dfunc, a_dline), LEN_HUND);
   DEBUG_MENV  yLOG_info    ("x_prefix"  , x_prefix);
   /*---(defense)------------------------*/
   DEBUG_MENV  yLOG_point   ("a_name"    , a_name);
   --rce;  if (a_name == NULL || a_name [0] == '\0') {
      yerr_uerror ("%s: error: file name passed to %s is null/empty", x_prefix, __FUNCTION__);
      DEBUG_MENV  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_MENV  yLOG_info    ("a_name"    , a_name);
   DEBUG_MENV  yLOG_point   ("b_file"    , b_file);
   --rce;  if (b_file  == NULL) {
      yerr_uerror ("%s: error: file å%sæ passed to %s with null file return pointer", x_prefix, a_name, __FUNCTION__);
      DEBUG_MENV  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_MENV  yLOG_point   ("*b_file"   , *b_file);
   --rce;  if (*b_file != NULL) {
      yerr_uerror ("%s: error: file å%sæ passed to %s with already open file return pointer", x_prefix, a_name, __FUNCTION__);
      DEBUG_MENV  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_MENV  yLOG_char    ("a_mode"    , a_mode);
   DEBUG_MENV  yLOG_info    ("allowed"   , "rwa");
   --rce;  if (a_mode  == 0 || strchr ("rwa", a_mode) == NULL) {
      if (a_mode == 0)  a_mode = '0';
      yerr_uerror ("%s: error: file å%sæ passed to %s with mode (%c) when the only valid are årwaæ", x_prefix, a_name, __FUNCTION__, a_mode);
      DEBUG_MENV  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(open)---------------------------*/
   sprintf (x_mode, "%ct", a_mode);
   DEBUG_MENV  yLOG_info    ("x_mode"    , x_mode);
   if      (strcmp (a_name, "(stdin)" ) == 0)  f = stdin;
   else if (strcmp (a_name, "(stdout)") == 0)  f = stdout;
   else if (strcmp (a_name, "(stderr)") == 0)  f = stderr;
   else                                      f = fopen (a_name, x_mode);
   DEBUG_MENV  yLOG_point   ("f"         , f);
   --rce;  if (f == NULL) {
      yerr_uerror ("%s: error: file å%sæ fopen in %s returned (%d) %s", x_prefix, a_name, __FUNCTION__, errno, strerror (errno));
      DEBUG_MENV  yLOG_complex ("error"     , "%d) %s", errno, strerror (errno));
      DEBUG_MENV  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(save-back)----------------------*/
   if (b_file  != NULL)  *b_file = f;
   /*---(complete)-----------------------*/
   DEBUG_MENV  yLOG_exit    (__FUNCTION__);
   return 1;
}

char
yenv_uopen              (char a_name [LEN_FULL], char a_mode, FILE **b_file)
{
   return yenv_uopen_detail ("n/a", "n/a", 0, a_name, a_mode, b_file);
}

char
yenv_uclose_detail      (char a_dfile [LEN_TITLE], char a_dfunc [LEN_TITLE], int a_dline, char a_name [LEN_FULL], FILE **b_file)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_prefix    [LEN_HUND]  = "";
   /*---(header)-------------------------*/
   DEBUG_MENV  yLOG_enter   (__FUNCTION__);
   /*---(create prefix)------------------*/
   strlcpy (x_prefix, yenv_uprefix (a_dfile, a_dfunc, a_dline), LEN_HUND);
   DEBUG_MENV  yLOG_info    ("x_prefix"  , x_prefix);
   /*---(defense)------------------------*/
   DEBUG_MENV  yLOG_point   ("a_name"    , a_name);
   --rce;  if (a_name == NULL || a_name [0] == '\0') {
      yerr_uerror ("%s: error: file name passed to %s is null/empty", x_prefix, __FUNCTION__);
      DEBUG_MENV  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_MENV  yLOG_info    ("a_name"    , a_name);
   DEBUG_MENV  yLOG_point   ("b_file"    , b_file);
   --rce;  if (b_file  == NULL) {
      yerr_uerror ("%s: error: file å%sæ passed to %s with null file return pointer", x_prefix, a_name, __FUNCTION__);
      DEBUG_MENV  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_MENV  yLOG_point   ("*b_file"   , *b_file);
   --rce;  if (*b_file == NULL) {
      yerr_uerror ("%s: error: file å%sæ passed to %s with already grounded file return pointer", x_prefix, a_name, __FUNCTION__);
      DEBUG_MENV  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(close)--------------------------*/
   if      (*b_file == stdin ) ;
   else if (*b_file == stdout) ;
   else if (*b_file == stderr) ;
   else { fflush (*b_file); rc = fclose (*b_file); }
   --rce;  if (rc != 0) {
      yerr_uerror ("%s: error: file å%sæ fclose in %s returned (%d) %s", __FUNCTION__, x_prefix, a_name, errno, strerror (errno));
      DEBUG_MENV  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(save-back)----------------------*/
   *b_file = NULL;
   /*---(complete)-----------------------*/
   DEBUG_MENV  yLOG_exit    (__FUNCTION__);
   return 1;
}

char
yenv_uclose             (char a_name [LEN_FULL], FILE **b_file)
{
   return yenv_uclose_detail ("n/a", "n/a", 0, a_name, b_file);
}

char
yenv__ustdin            (char a_clear)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        rc_final    =    0;
   int         x_flags     =    0;
   int         x_ch        =  ' ';
   /*---(set stdin to non-blocking)------*/
   x_flags = fcntl (0, F_GETFL, 0);
   rc = fcntl (0, F_SETFL, x_flags | O_NONBLOCK);
   --rce;  if (rc < 0) {
      DEBUG_MENV  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(test stdin for input)-----------*/
   x_ch = getc (stdin);
   if   (x_ch == -1)    rc_final = 0;
   else               { rc_final = 1; ungetc (x_ch, stdin); }
   /*---(check clear)--------------------*/
   if (a_clear == 'y') {
      while (x_ch = getc (stdin)) {
         if (x_ch < 0)  break;
      }
      rc_final = 0;
   }
   /*---(put stdin back to normal)-------*/
   rc = fcntl  (0, F_SETFL, x_flags);
   --rce;  if (rc < 0) {
      DEBUG_MENV  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   return rc_final;
}

char yenv_ucheck_stdin  (void) { return yenv__ustdin ('-'); }
char yenv_upurge_stdin  (void) { return yenv__ustdin ('y'); }

char
yenv_uload_stdin        (char a_recd [LEN_RECD])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         l           =    0;
   char        x_recd      [LEN_RECD]  = "";
   int         i           =    0;
   /*---(defense)------------------------*/
   if (a_recd   == NULL)                            return rce;
   if (a_recd [0] == '\0')                          return 0;
   strlcpy (x_recd, a_recd, LEN_RECD);
   /*---(fix record)-------------------*/
   l = strlen (x_recd) - 1;
   if (x_recd [l] == '¦') x_recd [l] = '\n';
   /*---(normal stdin)-----------------*/
   for (i = l; i >= 0; --i) {
      ungetc (x_recd [i], stdin);
   }
   /*---(complete)---------------------*/
   return 1;
}

char
yenv_uread              (FILE *a_file, short a_max, char r_recd [LEN_RECD], short *b_total, short *b_accept)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_eof       =    0;
   char        x_stdin     =    0;
   int         l           =    0;
   /*---(header)-------------------------*/
   DEBUG_MENV  yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_MENV  yLOG_point   ("a_file"    , a_file);
   --rce;  if (a_file == NULL) {
      DEBUG_MENV  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   x_eof = feof (a_file);
   DEBUG_MENV  yLOG_value   ("x_eof"     , x_eof);
   --rce;  if (x_eof)  {
      DEBUG_MENV  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_MENV  yLOG_value   ("a_max"     , a_max);
   --rce;  if (a_max < 1)      {
      DEBUG_MENV  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_MENV  yLOG_point   ("r_recd"    , r_recd);
   if (r_recd   == NULL)       {
      DEBUG_MENV  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare)------------------------*/
   if (a_file == stdin)   x_stdin = 'y';
   DEBUG_MENV  yLOG_char    ("x_stdin"   , x_stdin);
   strcpy (r_recd, "");
   /*---(walk-records)-------------------*/
   while (1) {
      /*---(read)------------------------*/
      if (x_stdin == 'y') {
         rc = yenv_ucheck_stdin ();
         DEBUG_MENV  yLOG_value   ("ucheck"    , rc);
         if (rc == 0) {
            DEBUG_MENV  yLOG_note    ("nothing waiting in stdin");
            DEBUG_MENV  yLOG_exit    (__FUNCTION__);
            return 0;
         }
      }
      fgets (r_recd, a_max, a_file);
      if (feof (a_file)) {
         strcpy (r_recd, "");
         DEBUG_MENV  yLOG_note    ("hit end-of-file");
         DEBUG_MENV  yLOG_exit    (__FUNCTION__);
         return 0;
      }
      if (b_total  != NULL)  *b_total  += 1;
      /*---(fix)-------------------------*/
      l = strlen (r_recd);
      if (l > 0 && r_recd [l - 1] == '\n')  r_recd [--l] = '\0';
      DEBUG_MENV  yLOG_complex ("r_recd"    , "%3då%sæ", l, r_recd);
      /*---(filter)----------------------*/
      if (l < 1)  {
         DEBUG_MENV  yLOG_note    ("empty record, skipping");
         continue;
      }
      if (r_recd [0] == ' ') {
         DEBUG_MENV  yLOG_note    ("starts with a space, skipping");
         continue;
      }
      if (r_recd [0] == '#') {
         switch (r_recd [1]) {
         case '>' :
            DEBUG_MENV   yLOG_note    ("allowing koios-style saved comments");
            break;
         case '@' :
            DEBUG_MENV   yLOG_note    ("allowing gyges-style exim configuraton");
            break;
         default  :
            DEBUG_MENV   yLOG_note    ("non-critical comment line, skipping");
            continue;
            break;
         }
      }
      break;
      /*---(done)------------------------*/
   }
   /*---(accept)-------------------------*/
   DEBUG_MENV  yLOG_note    ("accepted, returning record");
   if (b_accept != NULL) {
      *b_accept += 1;
      DEBUG_MENV  yLOG_value   ("b_accept"  , b_accept);
   }
   /*---(complete)-----------------------*/
   DEBUG_MENV  yLOG_exit    (__FUNCTION__);
   return 1;
}

char
yenv_uname              (char a_dir [LEN_PATH], char a_file [LEN_PATH], char *r_style, char r_full [LEN_PATH])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         ld          =    0;
   int         lf          =    0;
   char        x_style     =  '-';
   char        x_full      [LEN_PATH]  = "";
   /*---(default)------------------------*/
   if (r_style != NULL)  *r_style = '-';
   if (r_full  != NULL)  strcpy (r_full , "");
   /*---(defense)------------------------*/
   --rce;  if (a_dir  == NULL)  return rce;
   --rce;  if (a_file == NULL)  return rce;
   /*---(prepare)------------------------*/
   ld = strlen (a_dir);
   lf = strlen (a_file);
   /*---(more defense)-------------------*/
   --rce;  if (ld > 0 && a_dir  [0] != '/')  return rce;
   --rce;  if (lf > 0 && a_file [0] == '/')  return rce;
   /*---(concatenate)--------------------*/
   if      (ld == 0 && lf == 0)           x_style = '-';
   else if (ld == 0)                    { x_style = 'f';  sprintf (x_full, "%s", a_file); }
   else if (lf == 0) {
      x_style = 'd';
      if (a_dir [ld - 1] != '/')    sprintf (x_full, "%s/", a_dir);
      else                          sprintf (x_full, "%s" , a_dir);
   } else {
      x_style = 'b';
      if (a_dir [ld - 1] != '/')    sprintf (x_full, "%s/%s", a_dir, a_file);
      else                          sprintf (x_full, "%s%s" , a_dir, a_file);
   }
   /*---(re-check)-----------------------*/
   if (x_style == 'f' && x_full [0] == '/')  x_style = 'b';
   /*---(save-back)----------------------*/
   if (r_style != NULL)  *r_style = x_style;
   if (r_full  != NULL)  strlcpy (r_full , x_full, LEN_PATH);
   /*---(complete)-----------------------*/
   return 1;
}

char
yenv_udetail            (char a_full [LEN_PATH], char *r_style, char r_dir [LEN_PATH], char r_file [LEN_FULL], char r_proj [LEN_LABEL], char r_base [LEN_HUND], char r_ext [LEN_TERSE], char *r_level, char *r_quality)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_type      =  '-';
   char        x_style     =  '-';
   char        x_work      [LEN_PATH]  = "";
   char        x_dir       [LEN_PATH]  = "";
   char        x_file      [LEN_HUND]  = "";
   char        x_proj      [LEN_LABEL] = "";
   char        x_base      [LEN_HUND]  = "";
   char        x_ext       [LEN_TERSE] = "";
   char        x_level     =    0;
   char        x_quality   =  '-';
   int         i           =    0;
   char       *p           = NULL;
   char       *q           = NULL;
   int         x_len, ld, lf, l;
   char        x_flag      =   '-';
   /*---(header)-------------------------*/
   DEBUG_YSTR   yLOG_enter   (__FUNCTION__);
   /*---(default)------------------------*/
   if (r_style   != NULL)  *r_style   = x_style;
   if (r_dir     != NULL)  strcpy (r_dir , "");
   if (r_file    != NULL)  strcpy (r_file, "");
   if (r_proj    != NULL)  strcpy (r_proj, "");
   if (r_base    != NULL)  strcpy (r_base, "");
   if (r_ext     != NULL)  strcpy (r_ext , "");
   if (r_level   != NULL)  *r_level   = 0;
   if (r_quality != NULL)  *r_quality = x_quality;
   /*---(defense)------------------------*/
   DEBUG_YSTR   yLOG_point   ("a_full"    , a_full);
   --rce;  if (a_full == NULL || a_full [0] == '\0') {
      DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YSTR   yLOG_info    ("a_full"    , a_full);
   x_len = strlen (a_full);
   DEBUG_YSTR   yLOG_value   ("x_len"     , x_len);
   --rce;  if (x_len <= 0) {
      DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(check real file)----------------*/
   x_type = yenv_uexists (a_full);
   DEBUG_YSTR   yLOG_char    ("x_type"    , x_type);
   --rce;  if (x_type == '-') {
      DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare)------------------------*/
   strlcpy (x_work, a_full, LEN_PATH);
   if (x_len > 1 && x_work [x_len - 1] == '/')  x_work [--x_len] = '\0';
   DEBUG_YSTR   yLOG_info    ("x_work"    , x_work);
   /*---(calculate level)----------------*/
   for (i = 0; i < x_len; ++i)  if (x_work [i] == '/') ++x_level;
   DEBUG_YSTR   yLOG_value   ("x_level"   , x_level);
   /*---(check quality)------------------*/
   for (i = 0; i < x_len; ++i) {
      if (strchr (YSTR_FILES, x_work [i]) == NULL) { if (x_quality != '#')  x_quality = '!'; }
      if (strchr (YSTR_EXTEN, x_work [i]) == NULL) { x_quality = '#'; }
   }
   DEBUG_YSTR   yLOG_char    ("x_quality" , x_quality);
   /*---(parse)--------------------------*/
   p = strrchr (x_work, '/');
   DEBUG_YSTR   yLOG_point   ("p"         , p);
   if (x_type == 'd') {
      DEBUG_YSTR   yLOG_note    ("found directory only");
      strlcpy (x_dir , x_work, LEN_PATH);
   } else if (p != NULL) {
      DEBUG_YSTR   yLOG_note    ("found directory/file combo");
      p [0] = '\0';
      strlcpy (x_dir , x_work, LEN_PATH);
      strlcpy (x_file, p + 1 , LEN_HUND);
   } else {
      DEBUG_YSTR   yLOG_note    ("found file only");
      strlcpy (x_file, x_work, LEN_HUND);
   }
   ld = strlen (x_dir);
   lf = strlen (x_file);
   DEBUG_YSTR   yLOG_complex ("lengths"   , "ld=%3d, lf=%3d", ld, lf);
   /*---(concatenate)--------------------*/
   if      (ld == 0 && lf == 0)     x_style = '-';
   else if (ld == 0)                x_style = 'f';
   else if (lf == 0)                x_style = 'd';
   else                             x_style = 'b';
   DEBUG_YSTR   yLOG_char    ("x_style"   , x_style);
   /*---(extract project)----------------*/
   if      (ld > 16 && strncmp ("/home/system/"         , x_dir, 13) == 0)  x_flag = 'y';
   else if (ld > 19 && strncmp ("/home/keepsake/"       , x_dir, 15) == 0)  x_flag = 'y';
   else if (ld >  8 && strncmp ("/tmp/"                 , x_dir,  5) == 0)  x_flag = 'y';
   DEBUG_YSTR   yLOG_char    ("x_flag"    , x_flag);
   if (x_flag == 'y') {
      /*---(parse)-----------------------*/
      p = strrchr (x_dir, '/');
      DEBUG_YSTR   yLOG_point   ("p"         , p);
      if (p == NULL)  p = x_dir;
      else            ++p;
      q = strrchr (p, '.');
      DEBUG_YSTR   yLOG_point   ("q"         , q);
      if (q != NULL)  ++q;
      /*---(parse)-----------------------*/
      if (q == NULL)  l = LEN_LABEL;
      else            l = q - p;
      if (l > LEN_LABEL)  l = LEN_LABEL;
      DEBUG_YSTR   yLOG_value   ("l"         , l);
      strlcpy (x_proj, p, l);
   }
   DEBUG_YSTR   yLOG_info    ("x_proj"    , x_proj);
   /*---(extension)----------------------*/
   strlcpy (x_work, x_file, LEN_HUND);
   q = strrchr (x_work, '.');
   DEBUG_YSTR   yLOG_point   ("q"         , q);
   if (q != NULL && q != x_work) {
      l = q - x_file;
      DEBUG_YSTR   yLOG_value   ("l"         , l);
      strlcpy (x_ext, q, l);
      q [0] = '\0';
   }
   DEBUG_YSTR   yLOG_info    ("x_ext"     , x_ext);
   /*---(base)---------------------------*/
   strlcpy (x_base, x_work, LEN_HUND);
   DEBUG_YSTR   yLOG_info    ("x_base"    , x_base);
   /*---(fixes)--------------------------*/
   if (ld > 0)  strlcat (x_dir, "/", LEN_PATH);
   if (x_quality == '-' && x_base [0] == '.')  x_quality = '.';
   /*---(save-back)----------------------*/
   if (r_style   != NULL)  *r_style   = x_style;
   if (r_dir     != NULL)  strlcpy (r_dir , x_dir , LEN_PATH);
   if (r_file    != NULL)  strlcpy (r_file, x_file, LEN_HUND);
   if (r_proj    != NULL)  strlcpy (r_proj, x_proj, LEN_LABEL);
   if (r_base    != NULL)  strlcpy (r_base, x_base, LEN_HUND);
   if (r_ext     != NULL)  strlcpy (r_ext , x_ext , LEN_TERSE);
   if (r_level   != NULL)  *r_level   = x_level;
   if (r_quality != NULL)  *r_quality = x_quality;
   /*---(complete)-----------------------*/
   DEBUG_YSTR   yLOG_exit    (__FUNCTION__);
   return 1;
}


