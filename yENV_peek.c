/*===[[ START ]]==============================================================*/
#include    "yENV.h"
#include    "yENV_priv.h"



static char  s_peek    [LEN_RECD] = "";
static char  s_pprint  [LEN_RECD] = "";




/*====================------------------------------------====================*/
/*===----                      file contents                           ----===*/
/*====================------------------------------------====================*/
static void      o___CONTENT____________o (void) {;}

char*
yENV_peekier            (char a_style, char a_name [LEN_PATH], int n, int *a_count)
{
   /*---(locals)-----------+-----+-----+-*/
   char        t           [LEN_RECD]  = "";
   FILE       *f           = NULL;
   int         c           =    0;
   int         x_len       =    0;
   int         i           =    0;
   static int  x_last      =    0;
   char        x_dir       =  '-';
   int         x_curr      =    0;
   /*---(default)------------------------*/
   if (a_count != NULL)  *a_count = -1;
   /*---(defense)------------------------*/
   if (a_name == NULL)            return "(null name)";
   if (strcmp (a_name, "") == 0)  return "(empty name)";
   /*---(prepare)------------------------*/
   if (a_count != NULL)  *a_count = 0;
   strcpy (s_peek, "(n/a)");
   /*---(open file)----------------------*/
   f = fopen (a_name, "rt");
   if (f == NULL) {
      if (a_count != NULL)  *a_count = -1;
      return "(not found)";
   }
   /*---(set target)---------------------*/
   x_curr = x_last;
   switch (n) {
   case -1 :
      fclose (f);
      return "(found)";
      break;
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
   if (n < 0)  n = x_curr = 0;
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
   /*---(clean)--------------------------*/
   if (strchr ("vf", a_style) != NULL) {
      for (i = 0; i < x_len; ++i) {
         switch (s_peek [i]) {
         case  G_KEY_RETURN :  s_peek [i] = G_CHAR_RETURN;   break;
         case  G_KEY_ENTER  :  s_peek [i] = G_CHAR_RETURN;   break;
         case  G_KEY_ESCAPE :  s_peek [i] = G_CHAR_ESCAPE;   break;
         case  G_KEY_GROUP  :  s_peek [i] = G_CHAR_GROUP;    break;
         case  G_KEY_FIELD  :  s_peek [i] = G_CHAR_FIELD;    break;
         case  G_KEY_TAB    :  s_peek [i] = G_CHAR_FALSE;    break;
         }
         if (a_style == 'v' && s_peek [i] == G_KEY_SPACE) s_peek [i] = G_CHAR_STORAGE;
      }
   }
   /*---(save-back)----------------------*/
   if (a_count != NULL)  *a_count = c;
   /*---(complete)-----------------------*/
   return s_peek;
}

char* yENV_peek         (char a_name [LEN_PATH], int n) { return yENV_peekier ('-', a_name, n, NULL); }
char* yENV_peek_vis     (char a_name [LEN_PATH], int n) { return yENV_peekier ('v', a_name, n, NULL); }
char* yENV_peek_field   (char a_name [LEN_PATH], int n) { return yENV_peekier ('f', a_name, n, NULL); }
int   yENV_lines        (char a_name [LEN_PATH])        { int c = 0; yENV_peekier ('-', a_name, 0, &c); return c; }


/*> char*                                                                             <* 
 *> yENV_peek_clear         (char *a_name, int n)                                    <* 
 *> {                                                                                 <* 
 *>    int         l           =    0;                                                <* 
 *>    int         i           =    0;                                                <* 
 *>    yENV_peekier (a_name, n, NULL);                                                <* 
 *>    l = strlen (s_peek);                                                           <* 
 *>    for (i = 0; i < l; ++i) {                                                      <* 
 *>       switch (s_peek [i]) {                                                       <* 
 *>       case  G_KEY_RETURN :  s_peek [i] = G_CHAR_RETURN;   break;                  <* 
 *>       case  G_KEY_ENTER  :  s_peek [i] = G_CHAR_RETURN;   break;                  <* 
 *>       case  G_KEY_ESCAPE :  s_peek [i] = G_CHAR_ESCAPE;   break;                  <* 
 *>       case  G_KEY_GROUP  :  s_peek [i] = G_CHAR_GROUP;    break;                  <* 
 *>       case  G_KEY_FIELD  :  s_peek [i] = G_CHAR_FIELD;    break;                  <* 
 *>       case  G_KEY_SPACE  :  s_peek [i] = G_CHAR_STORAGE;  break;                  <* 
 *>       }                                                                           <* 
 *>    }                                                                              <* 
 *>    return s_peek;                                                                 <* 
 *> }                                                                                 <*/

/*> char*                                                                             <* 
 *> yENV_peek_fill          (char *a_name, int n)                                    <* 
 *> {                                                                                 <* 
 *>    int         i           =    0;                                                <* 
 *>    int         l           =    0;                                                <* 
 *>    strcpy (s_pprint, yENV_peekier (a_name, n, NULL));                             <* 
 *>    l = strlen (s_pprint);                                                         <* 
 *>    if (l == 0)  return "n/a";                                                     <* 
 *>    for (i = 0; i < l; ++i) {                                                      <* 
 *>       if (s_pprint [i] == ' ')   s_pprint [i] = '²';                              <* 
 *>       if (s_pprint [i] == '')  s_pprint [i] = '§';                               <* 
 *>       if (s_pprint [i] == '\t')  s_pprint [i] = 'Ú';                              <* 
 *>    }                                                                              <* 
 *>    return s_pprint;                                                               <* 
 *> }                                                                                 <*/

/*> char*                                                                             <* 
 *> yENV_peek_field         (char *a_name, int n)                                    <* 
 *> {                                                                                 <* 
 *>    int         i           =    0;                                                <* 
 *>    int         l           =    0;                                                <* 
 *>    strcpy (s_pprint, yENV_peekier (a_name, n, NULL));                             <* 
 *>    l = strlen (s_pprint);                                                         <* 
 *>    for (i = 0; i < l; ++i) {                                                      <* 
 *>       if (s_pprint [i] == '')  s_pprint [i] = '§';                               <* 
 *>    }                                                                              <* 
 *>    return s_pprint;                                                               <* 
 *> }                                                                                 <*/




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


