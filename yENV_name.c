/*===[[ START ]]==============================================================*/
#include    "yENV.h"
#include    "yENV_priv.h"



char
yenv_name_quality       (char a_type, char a_dir [LEN_PATH], char a_file [LEN_PATH], char *r_style, char r_full [LEN_PATH], char c_naming)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         ld          =    0;
   int         lf          =    0;
   char        x_valid     [LEN_FULL]  = "";
   char        x_full      [LEN_PATH]  = "";
   int         l           =    0;
   char        x_style     =  '-';
   int         i           =    0;
   uchar      *p           = NULL;
   int         c           =    0;
   /*---(header)-------------------------*/
   DEBUG_YENV   yLOG_enter   (__FUNCTION__);
   /*---(default)------------------------*/
   if (r_style != NULL)  *r_style = '-';
   if (r_full  != NULL)  strcpy (r_full , "");
   /*---(defense : dir null)-------------*/
   g_score [MARK_EFULL] = '£';
   DEBUG_YENV   yLOG_point   ("a_dir"     , a_dir);
   --rce;  if (a_dir       == NULL) {
      yURG_err ('f', "directory name can not be null (blatant error)");
      g_score [MARK_REQUEST] = '°';
      g_score [MARK_FINAL  ] = '°';
      DEBUG_YENV   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YENV   yLOG_info    ("a_dir"     , a_dir);
   ld = strlen (a_dir);
   DEBUG_YENV   yLOG_value   ("ld"        , ld);
   yURG_msg ('-', "requested dir  %3då%sæ", ld, a_dir);
   /*---(defense : file null)------------*/
   DEBUG_YENV   yLOG_point   ("a_file"    , a_file);
   --rce;  if (a_file      == NULL) {
      yURG_err ('f', "file name can not be null (blatant error)");
      g_score [MARK_REQUEST] = '°';
      g_score [MARK_FINAL  ] = '°';
      DEBUG_YENV   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YENV   yLOG_info    ("a_file"    , a_file);
   lf = strlen (a_file);
   DEBUG_YENV   yLOG_value   ("lf"        , lf);
   yURG_msg ('-', "requested file %3då%sæ", lf, a_file);
   /*---(check for empty)----------------*/
   g_score [MARK_EFULL] = '-';
   --rce;  if (ld < 1) {
      yURG_err ('f', "directory name can not be empty (blatant error)");
      g_score [MARK_REQUEST] = '°';
      g_score [MARK_FINAL  ] = '°';
      DEBUG_YENV   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(check for empty)----------------*/
   g_score [MARK_EFULL] = '=';
   --rce;  if (a_type == YENV_DIR && lf > 0) {
      yURG_err ('f', "with DIR type, file name must be empty (blatant error)");
      g_score [MARK_REQUEST] = '°';
      g_score [MARK_FINAL  ] = '°';
      DEBUG_YENV   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(directory absolute)-------------*/
   g_score [MARK_EFULL] = '/';
   --rce;  if (a_dir  [0] != '/') {
      yURG_err ('f', "directory name must be absolute reference, i.e., start with '/'");
      DEBUG_YENV    yLOG_note    ("directory name must start with '/'");
      g_score [MARK_REQUEST] = '°';
      g_score [MARK_FINAL  ] = '°';
      DEBUG_YENV   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   } else {
      DEBUG_YENV    yLOG_note    ("directory name is absoulte reference");
   }
   /*---(file relative)------------------*/
   g_score [MARK_EFULL] = '›';
   --rce;  if (lf > 0 && a_file [0] == '/') {
      yURG_err ('f', "file name must be relative reference, i.e., no leading '/'");
      DEBUG_YENV    yLOG_note    ("file name must NOT start with '/'");
      g_score [MARK_REQUEST] = '°';
      g_score [MARK_FINAL  ] = '°';
      DEBUG_YENV   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   } else {
      DEBUG_YENV    yLOG_note    ("file name is relative reference");
   }
   /*---(hidden file)--------------------*/
   if (c_naming != '-') {
      g_score [MARK_EFULL] = '´';
      DEBUG_YENV    yLOG_char    ("first char", a_file [0]);
      --rce;  if (a_file [0] == '.') {
         yURG_err ('f', "file can not be hidden, lead period, in (%c) mode (security risk)", c_naming);
         DEBUG_YENV    yLOG_note    ("file can not be hidden");
         g_score [MARK_REQUEST] = '°';
         g_score [MARK_FINAL  ] = '°';
         DEBUG_YENV   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
   }
   /*---(create full)--------------------*/
   if (ld == 0)                    { x_style = 'f';  sprintf (x_full, "%s", a_file); }
   else if (lf == 0)               { x_style = 'd';  sprintf (x_full, "%s", a_dir);  }
   else {
      x_style = 'b';
      if (a_dir [ld - 1] != '/')    sprintf (x_full, "%s/%s", a_dir, a_file);
      else                          sprintf (x_full, "%s%s" , a_dir, a_file);
   }
   l = strlen (x_full);
   yURG_msg ('-', "full name      %3då%sæ", l, x_full);
   DEBUG_YENV    yLOG_complex ("x_full"    , "%3då%sæ", l, x_full);
   /*---(check name quality)-------------*/
   g_score [MARK_EFULL] = '¢';
   switch (c_naming) {
   case '-' :  strcpy (x_valid, YSTR_EXTEN);  break;
   default  :  strcpy (x_valid, YSTR_FILES);  break;
   }
   l = strlen (x_full);
   --rce;  for (i = 0; i < l; ++i) {
      if (strchr (x_valid, x_full [i]) == NULL) {
         yURG_err ('f', "full name has an illegal character (%c) at position %d in (%c) mode", x_full [i], i, c_naming);
         DEBUG_YENV    yLOG_complex ("bad char"  , "can not include %c at %d", x_full [i], i);
         g_score [MARK_REQUEST] = '°';
         g_score [MARK_FINAL  ] = '°';
         DEBUG_YENV    yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
   }
   /*---(success)------------------------*/
   g_score [MARK_EFULL] = 'n';
   switch (c_naming) {
   case '-' :  yURG_msg ('-', "name (%c/%c) is qualified and uses only legal characters", x_style, c_naming);                    break;
   default  :  yURG_msg ('-', "name (%c/%c) is qualified, not hidden/temp, and uses only legal characters", x_style, c_naming);  break;
   }
   /*---(save-back)----------------------*/
   if (r_style != NULL)  *r_style = x_style;
   if (r_full  != NULL)  strlcpy (r_full , x_full, LEN_PATH);
   /*---(complete)-----------------------*/
   DEBUG_YENV   yLOG_exit    (__FUNCTION__);
   return RC_POSITIVE;
}

char
yenv_name_standard      (char a_type, char a_dir [LEN_PATH], char a_file [LEN_PATH], char a_prefix [LEN_TERSE], char a_suffix [LEN_TERSE], char c_naming, char c_style)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_pre       [LEN_TERSE] = "";
   char        x_suf       [LEN_TERSE] = "";
   int         x_min       =    0;
   int         l           =    0;
   int         i           =    0;
   int         c           =    0;
   int         x_npre      =   -1;
   int         x_nsuf      =   -1;
   int         ll          =    0;
   char        t           [LEN_LABEL] = "";
   int         x_rem       =    0;
   char        x_pgood     =  '-';
   char        x_sgood     =  '-';
   /*---(header)-------------------------*/
   DEBUG_YENV   yLOG_enter   (__FUNCTION__);
   /*---(quick-out)----------------------*/
   DEBUG_YENV   yLOG_char    ("a_type"    , a_type);
   if (a_type   != YENV_REG) {
      DEBUG_YENV   yLOG_note    ("standards only for regular files");
      DEBUG_YENV   yLOG_exit    (__FUNCTION__);
      return RC_ACK;
   }
   DEBUG_YENV   yLOG_char    ("c_naming"  , c_naming);
   if (c_naming == 0 || strchr ("-n", c_naming) != NULL) {
      DEBUG_YENV   yLOG_note    ("not using standards naming check");
      DEBUG_YENV   yLOG_exit    (__FUNCTION__);
      return RC_ACK;
   }
   DEBUG_YENV   yLOG_char    ("c_style"   , c_style);
   if (c_style  != 'b') {
      DEBUG_YENV   yLOG_note    ("full name is not both dir and file");
      DEBUG_YENV   yLOG_exit    (__FUNCTION__);
      return RC_ACK;
   }
   /*---(prepare)------------------------*/
   g_score [MARK_EFULL] = '?';
   /*---(defense)------------------------*/
   DEBUG_YENV   yLOG_point   ("a_dir"     , a_dir);
   --rce;  if (a_dir  == NULL || a_dir  [0] == '\0') {
      yURG_err ('f', "directory name can not be null/empty (blatant error)");
      g_score [MARK_REQUEST] = '°';
      g_score [MARK_FINAL  ] = '°';
      DEBUG_YENV   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YENV   yLOG_info    ("a_dir"     , a_dir);
   DEBUG_YENV   yLOG_point   ("a_file"    , a_file);
   --rce;  if (a_file == NULL || a_file [0] == '\0') {
      yURG_err ('f', "file name can not be null/empty (blatant error)");
      g_score [MARK_REQUEST] = '°';
      g_score [MARK_FINAL  ] = '°';
      DEBUG_YENV   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YENV   yLOG_info    ("a_file"    , a_file);
   DEBUG_YENV   yLOG_point   ("a_prefix"  , a_prefix);
   --rce;  if (a_prefix == NULL) {
      yURG_err ('f', "prefix standard can not be null (blatant error)");
      g_score [MARK_REQUEST] = '°';
      g_score [MARK_FINAL  ] = '°';
      DEBUG_YENV   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YENV   yLOG_point   ("a_suffix"  , a_suffix);
   --rce;  if (a_suffix == NULL) {
      yURG_err ('f', "suffix standard can not be null (blatant error)");
      g_score [MARK_REQUEST] = '°';
      g_score [MARK_FINAL  ] = '°';
      DEBUG_YENV   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(check request)------------------*/
   if (a_prefix != NULL && strcmp (a_prefix, "") != 0)  { strlcpy (x_pre, a_prefix, LEN_TERSE);  ++x_min;  }
   if (a_suffix != NULL && strcmp (a_suffix, "") != 0)  { strlcpy (x_suf, a_suffix, LEN_TERSE);  ++x_min;  }
   DEBUG_YENV   yLOG_value   ("x_min"     , x_min);
   if (x_min == 0) {
      DEBUG_YENV   yLOG_note    ("no prefix/suffix provided, nothing to check");
      DEBUG_YENV   yLOG_exit    (__FUNCTION__);
      return RC_ACK;
   }
   /*---(check seperators)---------------*/
   l = strlen (a_file);
   DEBUG_YENV   yLOG_value   ("l"         , l);
   for (i = 0; i < l; ++i) {
      if (a_file [i] == '.')  ++c;
   }
   DEBUG_YENV   yLOG_value   ("c"         , c);
   --rce;  if (x_min > c) {
      yURG_err ('f', "only provided %d separators, but need %d (illegal name)", c, x_min);
      g_score [MARK_REQUEST] = '°';
      g_score [MARK_FINAL  ] = '°';
      DEBUG_YENV   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   x_rem = l;
   /*---(find prefix/suffix)-------------*/
   for (i = 0; i < l; ++i) {
      x_npre = i;
      if (a_file [i] == '.')  break;
   }
   DEBUG_YENV   yLOG_value   ("x_npre"    , x_npre);
   for (i = l - 1; i >= 0; --i) {
      x_nsuf = i;
      if (a_file [i] == '.')  break;
   }
   DEBUG_YENV   yLOG_value   ("x_nsuf"    , x_nsuf);
   /*---(check prefix)-------------------*/
   g_score [MARK_EFULL] = 'P';
   --rce;  if (a_prefix != NULL && strcmp (a_prefix, "") != 0)  {
      DEBUG_YENV    yLOG_info    ("a_prefix"  , a_prefix);
      strlcpy (t, a_file, x_npre + 2);
      DEBUG_YENV    yLOG_info    ("t"         , t);
      if (strcmp (t, a_prefix) != 0) {
         yURG_err ('f', "name prefix å%sæ does not match given standard å%sæ (illegal)", t, a_prefix);
         g_score [MARK_REQUEST] = '°';
         g_score [MARK_FINAL  ] = '°';
         DEBUG_YENV    yLOG_note    ("file prefix does not match given stanard");
         DEBUG_YENV    yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      x_pgood = 'y';
      x_rem  -= x_npre + 1;
      DEBUG_YENV   yLOG_value   ("x_rem"     , x_rem);
   }
   /*---(check suffix)-------------------*/
   g_score [MARK_EFULL] = 'S';
   --rce;  if (strcmp (a_suffix, "") != 0)  {
      DEBUG_YENV    yLOG_info    ("a_suffix"  , a_suffix);
      strlcpy (t, a_file + x_nsuf, LEN_TERSE);
      DEBUG_YENV    yLOG_info    ("t"         , t);
      if (strcmp (t, a_suffix) != 0) {
         yURG_err ('f', "name suffix å%sæ does not match given standard å%sæ (illegal)", t, a_suffix);
         g_score [MARK_REQUEST] = '°';
         g_score [MARK_FINAL  ] = '°';
         DEBUG_YENV    yLOG_note    ("file suffix does not match given stanard");
         DEBUG_YENV    yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      x_sgood = 'y';
      x_rem  -= l - x_nsuf;
      DEBUG_YENV   yLOG_value   ("x_rem"     , x_rem);
   }
   /*---(remaining description)----------*/
   g_score [MARK_EFULL] = 'R';
   DEBUG_YENV   yLOG_value   ("x_rem"     , x_rem);
   --rce;  if (x_rem < 3) {
      yURG_err ('f', "file description can not be shorter than 3 characters (lazy)");
      g_score [MARK_REQUEST] = '°';
      g_score [MARK_FINAL  ] = '°';
      DEBUG_YENV    yLOG_note    ("description too short (< 3 chars)");
      DEBUG_YENV    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(done)---------------------------*/
   g_score [MARK_EFULL] = 'N';
   if      (x_pgood == 'y' && x_sgood == 'y')     yURG_msg ('-', "prefix å%sæ and suffix å%sæ match given standard", a_prefix, a_suffix);
   else if (x_pgood == 'y')                       yURG_msg ('-', "prefix å%sæ matches given standard", a_prefix);
   else if (x_sgood == 'y')                       yURG_msg ('-', "suffix å%sæ matches given standard", a_suffix);
   /*---(complete)-----------------------*/
   DEBUG_YENV   yLOG_exit    (__FUNCTION__);
   return RC_POSITIVE;
}



