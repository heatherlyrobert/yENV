#include    "yENV_solo.h"



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
   /*---(header)-------------------------*/
   DEBUG_YENV  yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   --rce;  if (a_name     == NULL) {
      DEBUG_YENV  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (a_name [0] == '\0') {
      DEBUG_YENV  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(check existance)----------------*/
   rc = lstat (a_name, &s);
   DEBUG_YENV  yLOG_value   ("rc"        , rc);
   --rce;  if (rc < 0) {
      DEBUG_YENV  yLOG_note    ("file not found");
      DEBUG_YENV  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   if (S_ISREG  (s.st_mode)) {
      DEBUG_YENV  yLOG_note    ("found regular file");
      DEBUG_YENV  yLOG_exit    (__FUNCTION__);
      return 1;
   }
   DEBUG_YENV  yLOG_note    ("file not a regular file");
   /*---(complete)-----------------------*/
   DEBUG_YENV  yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yenv_uopen              (char a_name [LEN_HUND], char a_mode, FILE **r_file)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   FILE       *f           = NULL;
   char        x_mode      [LEN_TERSE] = "rt";
   /*---(header)-------------------------*/
   DEBUG_YENV  yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YENV  yLOG_point   ("a_name"    , a_name);
   --rce;  if (a_name     == NULL) {
      DEBUG_YENV  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YENV  yLOG_info    ("a_name"    , a_name);
   --rce;  if (a_name [0] == '\0') {
      DEBUG_YENV  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YENV  yLOG_point   ("r_file"    , r_file);
   --rce;  if (r_file  == NULL) {
      DEBUG_YENV  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YENV  yLOG_point   ("*r_file"   , *r_file);
   --rce;  if (*r_file != NULL) {
      DEBUG_YENV  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YENV  yLOG_char    ("a_mode"    , a_mode);
   --rce;  if (a_mode  == 0) {
      DEBUG_YENV  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YENV  yLOG_info    ("allowed"   , "rwa");
   --rce;  if (strchr ("rwa", a_mode) == NULL) {
      DEBUG_YENV  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(open)---------------------------*/
   sprintf (x_mode, "%ct", a_mode);
   DEBUG_YENV  yLOG_info    ("x_mode"    , x_mode);
   if      (strcmp (a_name, "stdin" ) == 0)  f = stdin;
   else if (strcmp (a_name, "stdout") == 0)  f = stdout;
   else if (strcmp (a_name, "stderr") == 0)  f = stderr;
   else                                      f = fopen (a_name, x_mode);
   DEBUG_YENV  yLOG_point   ("f"         , f);
   --rce;  if (f == NULL) {
      DEBUG_YENV  yLOG_complex ("error"     , "%d) %s", errno, strerror (errno));
      DEBUG_YENV  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(save-back)----------------------*/
   if (r_file  != NULL)  *r_file = f;
   /*---(complete)-----------------------*/
   DEBUG_YENV  yLOG_exit    (__FUNCTION__);
   return 1;
}

char
yenv_uclose             (FILE **r_file)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_YENV  yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YENV  yLOG_point   ("r_file"    , r_file);
   --rce;  if (r_file  == NULL) {
      DEBUG_YENV  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YENV  yLOG_point   ("*r_file"   , *r_file);
   --rce;  if (*r_file == NULL) {
      DEBUG_YENV  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(close)--------------------------*/
   if      (*r_file == stdin ) ;
   else if (*r_file == stdout) ;
   else if (*r_file == stderr) ;
   else    rc = fclose (*r_file);
   --rce;  if (rc != 0) {
      DEBUG_YENV  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(save-back)----------------------*/
   if (r_file  != NULL)  *r_file = NULL;
   /*---(complete)-----------------------*/
   DEBUG_YENV  yLOG_exit    (__FUNCTION__);
   return 1;
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
      DEBUG_YENV  yLOG_exitr   (__FUNCTION__, rce);
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
      DEBUG_YENV  yLOG_exitr   (__FUNCTION__, rce);
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
   DEBUG_YENV  yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YENV  yLOG_point   ("a_file"    , a_file);
   --rce;  if (a_file == NULL) {
      DEBUG_YENV  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   x_eof = feof (a_file);
   DEBUG_YENV  yLOG_value   ("x_eof"     , x_eof);
   --rce;  if (x_eof)  {
      DEBUG_YENV  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YENV  yLOG_value   ("a_max"     , a_max);
   --rce;  if (a_max < 1)      {
      DEBUG_YENV  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YENV  yLOG_point   ("r_recd"    , r_recd);
   if (r_recd   == NULL)       {
      DEBUG_YENV  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare)------------------------*/
   if (a_file == stdin)   x_stdin = 'y';
   DEBUG_YENV  yLOG_char    ("x_stdin"   , x_stdin);
   strcpy (r_recd, "");
   /*---(walk-records)-------------------*/
   while (1) {
      /*---(read)------------------------*/
      if (x_stdin == 'y') {
         rc = yenv_ucheck_stdin ();
         DEBUG_YENV  yLOG_value   ("ucheck"    , rc);
         if (rc == 0) {
            DEBUG_YENV  yLOG_note    ("nothing waiting in stdin");
            DEBUG_YENV  yLOG_exit    (__FUNCTION__);
            return 0;
         }
      }
      fgets (r_recd, a_max, a_file);
      if (feof (a_file)) {
         strcpy (r_recd, "");
         DEBUG_YENV  yLOG_note    ("hit end-of-file");
         DEBUG_YENV  yLOG_exit    (__FUNCTION__);
         return 0;
      }
      if (b_total  != NULL)  *b_total  += 1;
      /*---(fix)-------------------------*/
      l = strlen (r_recd);
      if (l > 0 && r_recd [l - 1] == '\n')  r_recd [--l] = '\0';
      DEBUG_YENV  yLOG_complex ("r_recd"    , "%3då%sæ", l, r_recd);
      /*---(filter)----------------------*/
      if (l < 1)  {
         DEBUG_YENV  yLOG_note    ("empty record, skipping");
         continue;
      }
      if (r_recd [0] == ' ') {
         DEBUG_YENV  yLOG_note    ("starts with a space, skipping");
         continue;
      }
      if (r_recd [0] == '#') {
         switch (r_recd [1]) {
         case '>' :
            DEBUG_YENV   yLOG_note    ("allowing koios-style saved comments");
            break;
         case '@' :
            DEBUG_YENV   yLOG_note    ("allowing gyges-style exim configuraton");
            break;
         default  :
            DEBUG_YENV   yLOG_note    ("non-critical comment line, skipping");
            continue;
            break;
         }
      }
      break;
      /*---(done)------------------------*/
   }
   /*---(accept)-------------------------*/
   DEBUG_YENV  yLOG_note    ("accepted, returning record");
   if (b_accept != NULL) {
      *b_accept += 1;
      DEBUG_YENV  yLOG_value   ("b_accept"  , b_accept);
   }
   /*---(complete)-----------------------*/
   DEBUG_YENV  yLOG_exit    (__FUNCTION__);
   return 1;
}


