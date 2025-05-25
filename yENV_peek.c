/*===[[ START ]]==============================================================*/
#include    "yENV.h"
#include    "yENV_priv.h"



static char  myenv_peek    [LEN_RECD]  = "";
static int   myenv_last    =    0;
static char  myenv_save    [LEN_PATH]  = "";

static char  myenv_over    [LEN_LABEL] = "(n/a)";
static char  myenv_under   [LEN_LABEL] = "(n/a)";


char yenv_unit     (void) { strcpy (myenv_under, "(under)"); strcpy (myenv_over , "(over)"); return 0; }
char yenv_normal   (void) { strcpy (myenv_under, "(n/a)"  ); strcpy (myenv_over , "(n/a)" ); return 0; }



/*====================------------------------------------====================*/
/*===----                      file contents                           ----===*/
/*====================------------------------------------====================*/
static void      o___CONTENT____________o (void) {;}

char*
yENV_peekier            (char a_style, char a_name [LEN_PATH], char a_dir, int n, int *a_count)
{
   /*---(locals)-----------+-----+-----+-*/
   char        t           [LEN_RECD]  = "";
   FILE       *f           = NULL;
   int         c           =    0;
   int         x_len       =    0;
   int         i           =    0;
   char        x_dir       =  '-';
   int         x_curr      =    0;
   /*---(default)------------------------*/
   if (a_count != NULL)  *a_count = -1;
   /*---(defense)------------------------*/
   if (a_name     == NULL)               { strcpy  (myenv_save, "");  myenv_last = -1;  return "(null name)";  }
   if (a_name [0] == '\0')               { strcpy  (myenv_save, "");  myenv_last = -1;  return "(empty name)"; }
   /*---(prepare)------------------------*/
   if (strcmp (myenv_save, a_name) != 0) { strlcpy (myenv_save, a_name, LEN_PATH); myenv_last = -1; }
   strcpy (myenv_peek, "(n/a)");
   /*---(set target)---------------------*/
   x_curr = myenv_last;
   switch (a_dir) {
   case YDLST_HEAD  : case YDLST_DHEAD :
      x_curr = 0;
      break;
   case YDLST_PREV  : case YDLST_DPREV :
      if (x_curr <= 0) return myenv_under;
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
      myenv_last = -1;
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
   if (x_curr < 0)  { myenv_last = -1; return myenv_under;  }
   /*---(open file)----------------------*/
   f = fopen (a_name, "rt");
   if (f == NULL)  { strcpy (myenv_save, "");  myenv_last = -1;  return "(missing file)"; }
   /*---(walk file)----------------------*/
   while (1) {
      fgets (t, LEN_RECD, f);
      if (feof (f))  break;
      if (c      == x_curr)  strcpy (myenv_peek, t);
      if (x_curr == 999   )  strcpy (myenv_peek, t);
      ++c;
   }
   /*---(close)--------------------------*/
   fclose (f);
   /*---(save-back)----------------------*/
   if (a_count != NULL)  *a_count = c;
   /*---(handle count)-------------------*/
   if (a_dir == YDLST_COUNT)  return "(count-only)";
   /*---(fix cursor)---------------------*/
   if      (x_curr == 999)  x_curr = c - 1;
   else if (x_curr >= c)    return myenv_over;
   myenv_last = x_curr;
   /*---(fix end)------------------------*/
   x_len = strlen (myenv_peek);
   if (x_len > 0 && myenv_peek [x_len - 1] == '\n')  myenv_peek [--x_len] = '\0';
   /*---(clean)--------------------------*/
   if (strchr ("vf", a_style) != NULL) {
      for (i = 0; i < x_len; ++i) {
         switch (myenv_peek [i]) {
         case  G_KEY_RETURN :  myenv_peek [i] = G_CHAR_RETURN;   break;
         case  G_KEY_ENTER  :  myenv_peek [i] = G_CHAR_RETURN;   break;
         case  G_KEY_ESCAPE :  myenv_peek [i] = G_CHAR_ESCAPE;   break;
         case  G_KEY_GROUP  :  myenv_peek [i] = G_CHAR_GROUP;    break;
         case  G_KEY_FIELD  :  myenv_peek [i] = G_CHAR_FIELD;    break;
         case  G_KEY_TAB    :  myenv_peek [i] = G_CHAR_FALSE;    break;
         }
         if (a_style == 'v' && myenv_peek [i] == G_KEY_SPACE) myenv_peek [i] = G_CHAR_STORAGE;
      }
   }
   /*---(complete)-----------------------*/
   return myenv_peek;
}

int   yENV_lines        (char a_name [LEN_PATH])             { int c = 0; yENV_peekier ('-', a_name, 0, 0, &c); return c; }

char* yENV_peek         (char a_name [LEN_PATH], char a_dir) { return yENV_peekier ('-', a_name, a_dir, 0, NULL); }
char* yENV_index        (char a_name [LEN_PATH], int n)      { return yENV_peekier ('-', a_name, 0    , n, NULL); }
char* yENV_peek_vis     (char a_name [LEN_PATH], int n)      { return yENV_peekier ('v', a_name, 0    , n, NULL); }
char* yENV_peek_field   (char a_name [LEN_PATH], int n)      { return yENV_peekier ('f', a_name, 0    , n, NULL); }

char  yENV_reset        (char a_name [LEN_PATH])             { yENV_peekier ('-', a_name, YDLST_RESET, 0, NULL); return 0; }

char* yENV_where        (void)                               { return myenv_save; }
int   yENV_which        (void)                               { return myenv_last; }



/*====================------------------------------------====================*/
/*===----                      file comparision                        ----===*/
/*====================------------------------------------====================*/
static void      o___COMPLEX____________o (void) {;}

char
yENV_diff               (char *a_actual, char *a_expect)
{
   char        rce         =  -10;
   char        rc          =    0;
   char       *x_diff      = "/tmp/yurg_diff.txt";
   char        x_cmd       [LEN_RECD]  = "";
   int         c           =    0;
   rc = yENV_exists (a_actual);
   --rce;  if (rc < 0)  return rce;
   rc = yENV_exists (a_expect);
   --rce;  if (rc < 0)  return rce;
   sprintf (x_cmd, "diff %s %s > %s", a_actual, a_expect, x_diff);
   system  (x_cmd);
   rc = yENV_exists (x_diff);
   --rce;  if (rc < 0 || rc == '-')  return rce;
   c = yENV_lines (x_diff);
   if (c > 0)  return 0;
   return 1;
}


