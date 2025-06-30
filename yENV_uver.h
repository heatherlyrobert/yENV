#include    <stdio.h>
#include    <stdarg.h>                   /* va_arg                              */
#include    <unistd.h>                   /* unlink                              */
#include    <sys/stat.h>          /* fstat, umask                                */

#include  <yDLST_solo.h>

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

int    yenv_ulines  (char a_name [LEN_PATH])        { int c = 0;  yenv_upeekier (a_name, 0    , 0, &c); return c; }

char*  yenv_upeek   (char a_name [LEN_PATH], char a_dir) { return yenv_upeekier (a_name, a_dir, 0, NULL); }
char*  yenv_uindex  (char a_name [LEN_PATH], int  n    ) { return yenv_upeekier (a_name, 0    , n, NULL); }

char*  yenv_uwhich   (void)  { return myenv_usave; }
int    yenv_uwhere   (void)  { return myenv_ulast; }

char
yenv_uexists         (char a_name [LEN_PATH])
{
   char        rce         =  -10;
   char        rc          =    0;
   tSTAT       s;
   /*---(defense)------------------------*/
   --rce;  if (a_name     == NULL)   return 0;
   --rce;  if (a_name [0] == '\0')   return 0;
   /*---(check existance)----------------*/
   rc = lstat (a_name, &s);
   --rce;  if (rc < 0)               return 0;
   if (S_ISREG  (s.st_mode))         return 1;
   return 0;
}

