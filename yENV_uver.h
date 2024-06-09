#include  <yDLST_solo.h>

static char  s_peek  [LEN_RECD] = "";

char*
yENV_upeek              (char a_name [LEN_PATH], int n)
{
   /*---(locals)-----------+-----+-----+-*/
   char        t           [LEN_RECD]  = "";
   FILE       *f           = NULL;
   int         c           =    0;
   int         x_len       =    0;
   static int  x_last      =    0;
   int         x_curr      =    0;
   char        x_dir       =  '-';
   /*---(prepare)------------------------*/
   strcpy (s_peek, "(n/a)");
   /*---(open file)----------------------*/
   f = fopen (a_name, "rt");
   if (f == NULL)   return "(not found)";
   /*---(defense)------------------------*/
   if (n < 0)  return s_peek;
   /*---(check cursoring)----------------*/
   x_curr = x_last;
   switch (n) {
   case YDLST_HEAD : case YDLST_DHEAD :
      x_dir = n;
      n = x_curr = 0;
      break;
   case YDLST_PREV : case YDLST_DPREV :
      x_dir = n;
      if (x_curr > 0)  n = --x_curr;
      else             n = x_curr = 0;
      break;
   case YDLST_CURR : case YDLST_DCURR :
      x_dir = n;
      n = x_curr;
      break;
   case YDLST_NEXT : case YDLST_DNEXT : case '·' :  /* · means default */
      x_dir = n;
      n = ++x_curr;
      break;
   case YDLST_TAIL : case YDLST_DTAIL :
      x_dir = n;
      n = x_curr = 999;
      break;
   default :
      x_curr = n;
      break;
   }
   /*---(walk file)----------------------*/
   while (1) {
      fgets (t, LEN_RECD, f);
      if (feof (f))  break;
      if (c == x_curr)     strcpy (s_peek, t);
      if (x_curr == 999)   strcpy (s_peek, t);
      ++c;
   }
   /*---(fix cursor)---------------------*/
   if (x_dir == YDLST_TAIL)  x_curr = c - 1;
   if (x_dir == YDLST_NEXT && strcmp (s_peek, "(n/a)") == 0)  x_curr = x_last;
   x_last = x_curr;
   /*---(close)--------------------------*/
   fclose (f);
   /*---(fix end)------------------------*/
   x_len = strlen (s_peek);
   if (x_len > 0 && s_peek [x_len - 1] == '\n')  s_peek [--x_len] = '\0';
   /*---(complete)-----------------------*/
   return s_peek;
}

int
yENV_ulines             (char a_name [LEN_PATH])
{
   /*---(locals)-----------+-----+-----+-*/
   FILE       *f           = NULL;
   int         c           =    0;
   /*---(open file)----------------------*/
   f = fopen (a_name, "rt");
   if (f == NULL)   return "(not found)";
   /*---(walk file)----------------------*/
   while (1) {
      fgets (t, LEN_RECD, f);
      if (feof (f))  break;
      ++c;
   }
   /*---(close)--------------------------*/
   fclose (f);
   /*---(complete)-----------------------*/
   return c;
}
