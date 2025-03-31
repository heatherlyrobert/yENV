/*===[[ START ]]==============================================================*/
#include    "yENV.h"
#include    "yENV_priv.h"



char
yENV_name_full          (char a_dir [LEN_PATH], char a_file [LEN_PATH], char *r_style, char r_full [LEN_PATH])
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
   /*---(check special)------------------*/
   if      (strcmp (a_file, "dir"    ) == 0)  lf = 0;
   else if (strcmp (a_file, "code"   ) == 0)  lf = 0;
   else if (strcmp (a_file, "source" ) == 0)  lf = 0;
   else if (strcmp (a_file, "sources") == 0)  lf = 0;
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
   return RC_POSITIVE;
}

char
yENV_name_split         (char a_full [LEN_PATH], char *r_style, char r_dir [LEN_PATH], char r_file [LEN_PATH])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         l           =    0;
   char       *p           = NULL;
   char        x_full      [LEN_PATH]  = "";
   char        x_dir       [LEN_PATH]  = "";
   char        x_file      [LEN_PATH]  = "";
   int         ld          =    0;
   int         lf          =    0;
   char        x_style     =  '-';
   /*---(default)------------------------*/
   if (r_style != NULL)  *r_style = '-';
   if (r_dir   != NULL)  strcpy (r_dir  , "");
   if (r_file  != NULL)  strcpy (r_file , "");
   /*---(defense)------------------------*/
   --rce;  if (a_full == NULL)     return rce;
   /*---(prepare)------------------------*/
   strlcpy (x_full, a_full, LEN_PATH);
   /*---(defense)------------------------*/
   l = strlen (x_full);
   --rce;  if (l > 0 && a_full [0] != '/')  return rce;
   /*---(parse)--------------------------*/
   p = strrchr (x_full, '/');
   if (p != NULL) {
      strlcpy (x_file, p + 1 , LEN_PATH);
      p [0] = '\0';
      strlcpy (x_dir , x_full, LEN_PATH);
   } else {
      strlcpy (x_file, x_full, LEN_PATH);
   }
   ld = strlen (x_dir);
   lf = strlen (x_file);
   /*---(fixes)--------------------------*/
   if (ld > 0)  strlcat (x_dir, "/", LEN_PATH);
   /*---(concatenate)--------------------*/
   if      (ld == 0 && lf == 0)     x_style = '-';
   else if (ld == 0)                x_style = 'f';
   else if (lf == 0)                x_style = 'd';
   else                             x_style = 'b';
   /*---(save-back)----------------------*/
   if (r_style != NULL)  *r_style = x_style;
   if (r_dir   != NULL)  strlcpy (r_dir  , x_dir , LEN_PATH);
   if (r_file  != NULL)  strlcpy (r_file , x_file, LEN_PATH);
   /*---(complete)-----------------------*/
   return RC_POSITIVE;
}

char
yenv_name_quality       (char a_type, char c_naming, char a_dir [LEN_PATH], char a_file [LEN_PATH], char *r_style, char r_full [LEN_PATH])
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
   char        x_msg       [LEN_HUND]  = "";
   /*---(header)-------------------------*/
   DEBUG_YENV   yLOG_enter   (__FUNCTION__);
   /*---(default)------------------------*/
   if (r_style != NULL)  *r_style = '-';
   if (r_full  != NULL)  strcpy (r_full , "");
   yenv_score_mark ("NFULL"   , '�');
   /*---(create full)--------------------*/
   rc = yENV_name_full (a_dir, a_file, &x_style, x_full);
   DEBUG_YENV   yLOG_value   ("full"      , rc);
   --rce;  if (rc < 0)  {
      yenv_audit_fatal ("NAME"    , "trouble with creating full name");
      DEBUG_YENV   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   l = strlen (x_full);
   yURG_msg ('-', "full name      %3d�%s�", l, x_full);
   DEBUG_YENV    yLOG_complex ("x_full"    , "%3d�%s�", l, x_full);
   /*---(hidden file)--------------------*/
   if (c_naming != YENV_WILD) {
      yenv_score_mark ("NFULL"   , '�');
      DEBUG_YENV    yLOG_char    ("first char", a_file [0]);
      --rce;  if (a_file [0] == '.') {
         sprintf (x_msg, "file can not be hidden, lead period, in (%c) mode (security risk)", c_naming);
         yenv_audit_fatal ("NAME"    , x_msg);
         DEBUG_YENV   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
   }
   /*---(check name quality)-------------*/
   yenv_score_mark ("NFULL"   , '�');
   switch (c_naming) {
   case YENV_WILD :  strcpy (x_valid, YSTR_EXTEN);  break;
   default        :  strcpy (x_valid, YSTR_FILES);  break;
   }
   l = strlen (x_full);
   --rce;  for (i = 0; i < l; ++i) {
      if (strchr (x_valid, x_full [i]) == NULL) {
         sprintf (x_msg, "full name has an illegal character (%c) at position %d in (%c) mode", x_full [i], i, c_naming);
         yenv_audit_fatal ("NAME"    , x_msg);
         DEBUG_YENV    yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
   }
   /*---(success)------------------------*/
   yenv_score_mark ("NFULL"   , 'n');
   switch (c_naming) {
   case YENV_WILD :  yURG_msg ('-', "name (%c/%c) is fully qualified and uses only legal characters", x_style, c_naming);                    break;
   default        :  yURG_msg ('-', "name (%c/%c) is fully qualified, not hidden/temp, and uses only legal characters", x_style, c_naming);  break;
   }
   yenv_score_mark ("NSTYLE"  , x_style);
   /*---(save-back)----------------------*/
   if (r_style != NULL)  *r_style = x_style;
   if (r_full  != NULL)  strlcpy (r_full , x_full, LEN_PATH);
   /*---(complete)-----------------------*/
   DEBUG_YENV   yLOG_exit    (__FUNCTION__);
   return RC_POSITIVE;
}

char
yenv_name__dots         (char c_naming, char a_file [LEN_PATH], char a_prefix [LEN_TERSE], char a_suffix [LEN_TERSE], short *r_beg, short *r_end)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         x_min       =    0;
   int         i           =    0;
   int         c           =    0;
   int         l           =    0;
   char        x_msg       [LEN_HUND]  = "";
   int         x_beg       =   -1;
   int         x_end       =   -1;
   /*---(header)-------------------------*/
   DEBUG_YENV   yLOG_enter   (__FUNCTION__);
   /*---(default)------------------------*/
   if (r_beg != NULL)  *r_beg = -1;
   if (r_end != NULL)  *r_end = -1;
   /*---(defense)------------------------*/
   DEBUG_YENV   yLOG_point   ("a_prefix"  , a_prefix);
   --rce;  if (a_prefix == NULL) {
      yenv_score_mark ("NPREFIX" , '�');
      yenv_audit_fatal ("NAME"    , "prefix standard can not be null (blatant error)");
      DEBUG_YENV   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YENV   yLOG_info    ("a_prefix"  , a_prefix);
   DEBUG_YENV   yLOG_point   ("a_suffix"  , a_suffix);
   --rce;  if (a_suffix == NULL) {
      yenv_score_mark ("NSUFFIX" , '�');
      yenv_audit_fatal ("NAME"    , "suffix standard can not be null (blatant error)");
      DEBUG_YENV   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YENV   yLOG_info    ("a_suffix"  , a_suffix);
   /*---(initial score)------------------*/
   yenv_score_mark ("NDOTS"   , '�');
   /*---(figure minimum)-----------------*/
   if (strcmp (a_prefix, "") != 0)    ++x_min;
   if (strcmp (a_suffix, "") != 0)    ++x_min;
   if (c_naming == 'c' && x_min > 0)  x_min -= 1;
   DEBUG_YENV   yLOG_value   ("x_min"     , x_min);
   /*---(check request)------------------*/
   if (x_min == 0) {
      yenv_score_mark ("NDOTS"   , '�');
      DEBUG_YENV   yLOG_note    ("no prefix/suffix provided, nothing to check");
      DEBUG_YENV   yLOG_exit    (__FUNCTION__);
      return RC_ACK;
   }
   /*---(count separators)---------------*/
   l = strlen (a_file);
   DEBUG_YENV   yLOG_value   ("l"         , l);
   for (i = 0; i < l; ++i) {
      if (a_file [i] == '.') {
         if (x_beg < 0)  x_beg = i;
         x_end = i;
         ++c;
      }
   }
   if (strcmp (a_prefix, "") == 0)  x_beg = -1;
   if (strcmp (a_suffix, "") == 0)  x_end = -1;
   DEBUG_YENV   yLOG_complex ("counts"    , "%3db, %3de, %3d#", x_beg, x_end, c);
   /*---(check seperators)---------------*/
   --rce;  if (x_min > c) {
      if      (x_min == 2)                     sprintf (x_msg, "need both prefix and suffix, i.e., at least 2 dot (.) separators, but only provided %d (illegal name)", c);
      else if (x_min == 1 && c_naming == 'c')  sprintf (x_msg, "need both prefix and suffix, i.e., at least 1 dot (.) separator, but only provided %d (illegal name)", c);
      else if (strcmp (a_prefix, "") != 0)     sprintf (x_msg, "need prefix, i.e. at least 1 dot (.) separator, but provided none (illegal name)");
      else                                     sprintf (x_msg, "need suffix, i.e. at least 1 dot (.) separator, but provided none (illegal name)");
      yenv_score_mark ("NDOTS"   , '#');
      yenv_audit_fatal ("NAME"    , x_msg);
      DEBUG_YENV   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(scoring)------------------------*/
   yenv_score_mark ("NDOTS"   , 'n');
   /*---(save-back)----------------------*/
   if (r_beg != NULL)  *r_beg = x_beg;
   if (r_end != NULL)  *r_end = x_end;
   /*---(complete)-----------------------*/
   DEBUG_YENV   yLOG_exit    (__FUNCTION__);
   return RC_POSITIVE;
}

char
yenv_name__prefix       (char a_file [LEN_PATH], short a_beg, char a_prefix [LEN_TERSE], char r_pre [LEN_TERSE])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        t           [LEN_LABEL] = "";
   char        x_msg       [LEN_HUND]  = "";
   /*---(header)-------------------------*/
   DEBUG_YENV   yLOG_enter   (__FUNCTION__);
   /*---(default)------------------------*/
   if (r_pre != NULL)  strlcpy (r_pre, "", LEN_TERSE);
   /*---(defense)------------------------*/
   DEBUG_YENV    yLOG_value   ("a_beg"     , a_beg);
   --rce;  if (a_beg <= 0) {
      DEBUG_YENV   yLOG_exit    (__FUNCTION__);
      return RC_ACK;
   }
   /*---(scoring)------------------------*/
   yenv_score_mark ("NPREFIX" , '�');
   /*---(save-back)----------------------*/
   strlcpy (t, a_file, a_beg + 2);
   if (r_pre != NULL)  strlcpy (r_pre, t, LEN_TERSE);
   /*---(user name option)---------------*/
   DEBUG_YENV    yLOG_info    ("a_prefix"  , a_prefix);
   if (strcmp (a_prefix, "(USER).") == 0) {
      DEBUG_YENV    yLOG_note    ("using user name prefix handler");
      strlcpy (t, a_file, a_beg + 1);
      DEBUG_YENV    yLOG_info    ("t"         , t);
      rc = yENV_user_data ('n', t, NULL, NULL, NULL, NULL);
      if (rc < 0) {
         sprintf (x_msg, "name prefix �%s� does not match any system user (illegal)", t);
         yenv_audit_fatal ("NAME"    , x_msg);
         DEBUG_YENV    yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      yenv_score_mark ("NPREFIX" , 'u');
   }
   /*---(normal option)------------------*/
   else {
      DEBUG_YENV    yLOG_note    ("using normal prefix handler");
      strlcpy (t, a_file, a_beg + 2);
      DEBUG_YENV    yLOG_info    ("t"         , t);
      if (strcmp (t, a_prefix) != 0) {
         sprintf (x_msg, "name prefix �%s� does not match given standard �%s� (illegal)", t, a_prefix);
         yenv_audit_fatal ("NAME"    , x_msg);
         DEBUG_YENV    yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      yenv_score_mark ("NPREFIX" , 'p');
   }
   /*---(complete)-----------------------*/
   DEBUG_YENV   yLOG_exit    (__FUNCTION__);
   return RC_POSITIVE;
}

char
yenv_name__suffix       (char a_file [LEN_PATH], short a_end, char a_suffix [LEN_TERSE])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        t           [LEN_LABEL] = "";
   char        x_msg       [LEN_HUND]  = "";
   /*---(header)-------------------------*/
   DEBUG_YENV   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YENV    yLOG_value   ("a_end"     , a_end);
   --rce;  if (a_end < 0) {
      DEBUG_YENV   yLOG_exit    (__FUNCTION__);
      return RC_ACK;
   }
   /*---(scoring)------------------------*/
   yenv_score_mark ("NSUFFIX" , '�');
   /*---(normal option)------------------*/
   DEBUG_YENV    yLOG_info    ("a_suffix"  , a_suffix);
   strlcpy (t, a_file + a_end, LEN_TERSE);
   DEBUG_YENV    yLOG_info    ("t"         , t);
   if (strcmp (t, a_suffix) != 0) {
      sprintf (x_msg, "name suffix �%s� does not match given standard �%s� (illegal)", t, a_suffix);
      yenv_audit_fatal ("NAME"    , x_msg);
      DEBUG_YENV    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(scoring)------------------------*/
   yenv_score_mark ("NSUFFIX" , 's');
   /*---(complete)-----------------------*/
   DEBUG_YENV   yLOG_exit    (__FUNCTION__);
   return RC_POSITIVE;
}

char
yenv_name_standard      (char a_type, char c_naming, char c_style, char a_dir [LEN_PATH], char a_file [LEN_PATH], char a_prefix [LEN_TERSE], char a_suffix [LEN_TERSE])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   short       x_beg       =   -1;
   short       x_end       =   -1;
   int         l           =    0;
   char        x_pre       [LEN_TERSE] = "";
   short       x_rem       =    0;
   char        x_msg       [LEN_HUND]  = "";
   char        x_type      =  '-';
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
   if (c_naming == 0 || strchr ("cl", c_naming) == NULL) {
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
   /*---(handle dots)--------------------*/
   rc = yenv_name__dots   (c_naming, a_file, a_prefix, a_suffix, &x_beg, &x_end);
   DEBUG_YENV   yLOG_value   ("dots"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_YENV   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(handle prefix)------------------*/
   rc = yenv_name__prefix (a_file, x_beg, a_prefix, x_pre);
   DEBUG_YENV   yLOG_value   ("prefix"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_YENV   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(handle suffix)------------------*/
   rc = yenv_name__suffix (a_file, x_end, a_suffix);
   DEBUG_YENV   yLOG_value   ("suffix"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_YENV   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(set type)-----------------------*/
   if      (x_beg > 0 && x_end > 0)  x_type = 'b';
   else if (x_beg > 0)               x_type = 'p';
   else if (x_end > 0)               x_type = 's';
   else                              x_type = '-';
   DEBUG_YENV   yLOG_char    ("x_type"    , x_type);
   if (x_type  == '-') {
      DEBUG_YENV   yLOG_exit    (__FUNCTION__);
      return RC_ACK;
   }
   /*---(remaining description)----------*/
   yenv_score_mark ("NDESC"   , '�');
   l = strlen (a_file);
   switch (x_type) {
   case 'b' :  x_rem = x_end - x_beg - 1;  break;
   case 'p' :  x_rem = l - x_beg - 1;      break;
   case 's' :  x_rem = x_end - 1;          break;
   }
   DEBUG_YENV   yLOG_value   ("x_rem"     , x_rem);
   --rce;  if (c_naming == YENV_LOCAL && x_rem < 3) {
      yenv_audit_fatal ("NAME"    , "file description less than 3 chars (lazy)");
      DEBUG_YENV    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   yenv_score_mark ("NDESC"   , 'd');
   /*---(done)---------------------------*/
   switch (x_type) {
   case 'b' :  yURG_msg ('-', "prefix �%s� and suffix �%s� match given standard", x_pre, a_suffix);  break;
   case 'p' :  yURG_msg ('-', "prefix �%s� matches given standard", x_pre);                          break;
   case 's' :  yURG_msg ('-', "suffix �%s� matches given standard", a_suffix);                       break;
   }
   /*---(complete)-----------------------*/
   DEBUG_YENV   yLOG_exit    (__FUNCTION__);
   return RC_POSITIVE;
}

char
yenv_name_local         (int a_ruid, char a_ruser [LEN_USER], char a_full [LEN_PATH], char b_owner [LEN_USER], char b_group [LEN_USER], char b_perms [LEN_TERSE])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_root      [LEN_LABEL] = "";
   char        x_home      [LEN_LABEL] = "";
   char        t           [LEN_PATH]  = "";
   char       *p           = NULL;
   int         x_fuid      =   -1;
   char        x_msg       [LEN_HUND]  = "";
   /*---(header)-------------------------*/
   DEBUG_YENV   yLOG_enter   (__FUNCTION__);
   /*---(scoring)------------------------*/
   yenv_score_mark ("NLOC"    , '�');
   /*---(set location)-------------------*/
   if (strncmp (a_full, "/tmp", 4) == 0) {
      strcpy (x_root , "/tmp/root/");
      strcpy (x_home , "/tmp/home/");
   } else {
      strcpy (x_root , "/root/");
      strcpy (x_home , "/home/");
   }
   DEBUG_YENV   yLOG_info    ("x_root"    , x_root);
   DEBUG_YENV   yLOG_info    ("x_home"    , x_home);
   /*---(check root)---------------------*/
   if (strncmp (a_full, x_root, strlen (x_root)) == 0) {
      yenv_score_mark ("NLOC"    , 'r');
      yenv_score_mark ("NUSE"    , '�');
      DEBUG_YENV   yLOG_note    ("file located under root");
      if (a_ruid != 0) {
         sprintf (x_msg, "running as �%s�, uid (%d); BUT, file in �%s� (illegal)", a_ruser, a_ruid, x_root);
         yenv_audit_fatal ("NAME"    , x_msg);
         DEBUG_YENV    yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      yURG_msg ('-', "good, running as �%s�, uid (%d) and file is located in or below �%s�", a_ruser, a_ruid, x_root);
      yenv_score_mark ("NUSE"    , 'R');
      strcpy (t, "root");
      /*---(done)------------------------*/
   }
   /*---(check home)---------------------*/
   else if (strncmp (a_full, x_home, strlen (x_home)) == 0) {
      yenv_score_mark ("NLOC"    , 'h');
      strcpy (t, a_full + strlen (x_home));
      yenv_score_mark ("NUSE"    , '�');
      DEBUG_YENV   yLOG_info    ("t"         , t);
      p = strchr (t, '/');
      DEBUG_YENV   yLOG_point   ("p"         , p);
      if (p != NULL)  p [0] = '\0';
      else            strcpy (t, "");
      DEBUG_YENV   yLOG_info    ("t"         , t);
      rc = yENV_user_data ('n', t, &x_fuid, NULL, NULL, NULL);
      if (rc < 0) {
         sprintf (x_msg, "could not find �%s� as a legal user subdirectory under �%s� (illegal)", t, x_home);
         yenv_audit_fatal ("NAME"    , x_msg);
         DEBUG_YENV    yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      if      (a_ruid == 0) ;
      else if (strcmp (a_ruser, t) == 0) ;
      else {
         sprintf (x_msg, "running as �%s�, uid (%d); BUT, file in �%s� (illegal)", a_ruser, a_ruid, t);
         yenv_audit_fatal ("NAME"    , x_msg);
         DEBUG_YENV    yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      yURG_msg ('-', "good, running as �%s�, uid (%d) and file is located in or below �%s�", a_ruser, a_ruid, t);
      yenv_score_mark ("NUSE"    , 'H');
      /*---(done)------------------------*/
   }
   /*---(elsewhere)----------------------*/
   else {
      sprintf (x_msg, "file not in �%s� or under �%s� and so can not be handled", x_root, x_home);
      yenv_audit_fatal ("NAME"    , x_msg);
      DEBUG_YENV    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(save-back)----------------------*/
   if (b_owner != NULL)   strlcpy (b_owner, t        , LEN_USER);
   if (b_group != NULL)   strlcpy (b_group, t        , LEN_USER);
   if (b_perms != NULL)   strlcpy (b_perms, "f_tight", LEN_TERSE);
   /*---(complete)-----------------------*/
   DEBUG_YENV   yLOG_exit    (__FUNCTION__);
   return RC_POSITIVE;
}

char
yenv_name_central       (int a_ruid, char a_ruser [LEN_USER], char a_full [LEN_PATH], char b_owner [LEN_USER], char b_group [LEN_USER], char b_perms [LEN_TERSE])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_etc       [LEN_LABEL] = "";
   char        x_spool     [LEN_LABEL] = "";
   char        t           [LEN_PATH]  = "";
   char       *p           = NULL;
   char        x_msg       [LEN_HUND]  = "";
   /*---(header)-------------------------*/
   DEBUG_YENV   yLOG_enter   (__FUNCTION__);
   /*---(scoring)------------------------*/
   yenv_score_mark ("NLOC"    , '�');
   /*---(set location)-------------------*/
   if (strncmp (a_full, "/tmp", 4) == 0) {
      strcpy (x_etc  , "/tmp/etc/");
      strcpy (x_spool, "/tmp/spool/");
   } else {
      strcpy (x_etc  , "/etc/");
      strcpy (x_spool, "/var/spool/");
   }
   DEBUG_YENV   yLOG_info    ("x_spool"   , x_spool);
   DEBUG_YENV   yLOG_info    ("x_etc"     , x_etc);
   /*---(check etc)----------------------*/
   if (strncmp (a_full, x_etc, strlen (x_etc)) == 0) {
      yenv_score_mark ("NLOC"    , 'e');
      yenv_score_mark ("NUSE"    , '�');
      DEBUG_YENV   yLOG_note    ("file located under root");
      if (a_ruid != 0) {
         sprintf (x_msg, "running as �%s�, uid (%d); BUT, file in �%s� (illegal)", a_ruser, a_ruid, x_etc);
         yenv_audit_fatal ("NAME"    , x_msg);
         DEBUG_YENV    yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      yURG_msg ('-', "good, running as �%s�, uid (%d) and file is located in or below �%s�", a_ruser, a_ruid, x_etc);
      yenv_score_mark ("NUSE"    , 'E');
   }
   /*---(check spool)--------------------*/
   else if (strncmp (a_full, x_spool, strlen (x_spool)) == 0) {
      yenv_score_mark ("NLOC"    , 's');
      yenv_score_mark ("NUSE"    , '�');
      p = strrchr (a_full, '/');
      DEBUG_YENV   yLOG_point   ("p"         , p);
      if (p != NULL)  strcpy (t, p + 1);
      else            strcpy (t, "");
      DEBUG_YENV   yLOG_info    ("t"         , t);
      p = strchr  (t, '.');
      if (p != NULL)  p [0] = '\0';
      else            strcpy (t, "");
      DEBUG_YENV   yLOG_info    ("t"         , t);
      rc = yENV_user_data ('n', t, NULL, NULL, NULL, NULL);
      if (rc < 0) {
         sprintf (x_msg, "could not find �%s� as a legal user (illegal)", t, x_spool);
         yenv_audit_fatal ("NAME"    , x_msg);
         DEBUG_YENV    yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      if (a_ruid == 0 || strcmp (a_ruser, t) == 0) {
         yURG_msg ('-', "good, running as �%s�, uid (%d) so can handle file prefixed as �%s�", a_ruser, a_ruid, t);
      } else {
         sprintf (x_msg, "running as �%s�, uid (%d); BUT, file prefixed as �%s� (illegal)", a_ruser, a_ruid, t);
         yenv_audit_fatal ("NAME"    , x_msg);
         DEBUG_YENV    yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      yenv_score_mark ("NUSE"    , 'S');
   }
   /*---(elsewhere)----------------------*/
   else {
      sprintf (x_msg, "file not in �%s� or under �%s� and so can not be handled", x_etc, x_spool);
      yenv_audit_fatal ("NAME"    , x_msg);
      DEBUG_YENV    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(save-back)----------------------*/
   if (b_owner != NULL)   strlcpy (b_owner, "root"   , LEN_USER);
   if (b_group != NULL)   strlcpy (b_group, "root"   , LEN_USER);
   if (b_perms != NULL)   strlcpy (b_perms, "f_tight", LEN_TERSE);
   /*---(complete)-----------------------*/
   DEBUG_YENV   yLOG_exit    (__FUNCTION__);
   return RC_POSITIVE;
}

char
yenv_name_location      (char a_type, char c_naming, char a_full [LEN_PATH], char b_owner [LEN_USER], char b_group [LEN_USER], char b_perms [LEN_TERSE])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         x_ruid      =   -1;
   char        x_ruser     [LEN_USER]  = "";
   /*---(header)-------------------------*/
   DEBUG_YENV   yLOG_enter   (__FUNCTION__);
   /*---(config mark(--------------------*/
   --rce;  if (c_naming == 0 || strchr (YENV_NAMING, c_naming) == NULL) {
      DEBUG_YENV   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(quick-out)----------------------*/
   DEBUG_YENV   yLOG_char    ("a_type"    , a_type);
   if (a_type   != YENV_REG) {
      DEBUG_YENV   yLOG_note    ("standards only for regular files");
      DEBUG_YENV   yLOG_exit    (__FUNCTION__);
      return RC_ACK;
   }
   DEBUG_YENV   yLOG_char    ("c_naming"  , c_naming);
   if (c_naming != 0 && strchr ("cl", c_naming) == NULL) {
      DEBUG_YENV   yLOG_note    ("not using yjods central/local standards, skipping");
      DEBUG_YENV   yLOG_exit    (__FUNCTION__);
      return RC_ACK;
   }
   /*---(set uid)------------------------*/
   yenv_score_mark ("NLOC"    , 'I');
   rc = yENV_whoami (NULL, NULL, &x_ruid, NULL, NULL, x_ruser, NULL, NULL, NULL, NULL);
   DEBUG_YENV   yLOG_value   ("whoami"    , rc);
   --rce;  if (rc < 0) {
      yenv_score_mark ("NLOC"    , '�');
      yenv_audit_fatal ("NAME"    , "could not identify current user  (scary)");
      DEBUG_YENV    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YENV   yLOG_info    ("x_ruser"   , x_ruser);
   /*---(handle locals)------------------*/
   if (c_naming == YENV_LOCAL) {
      DEBUG_YENV   yLOG_note    ("handling local");
      rc = yenv_name_local   (x_ruid, x_ruser, a_full, b_owner, b_group, b_perms);
      if (rc < 0) {
         DEBUG_YENV    yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
   }
   /*---(check centrals)-----------------*/
   if (c_naming == YENV_CENTRAL) {
      DEBUG_YENV   yLOG_note    ("handling central");
      rc = yenv_name_central (x_ruid, x_ruser, a_full, b_owner, b_group, b_perms);
      if (rc < 0) {
         DEBUG_YENV    yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
   }
   /*---(complete)-----------------------*/
   DEBUG_YENV   yLOG_exit    (__FUNCTION__);
   return RC_POSITIVE;
}




