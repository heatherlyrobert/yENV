/*===[[ START ]]==============================================================*/
#include    "yENV.h"
#include    "yENV_priv.h"

char
yenv_name_fatal         (char a_msg [LEN_HUND])
{
   DEBUG_YENV    yLOG_note    (a_msg);
   yURG_err ('f', a_msg);
   yenv_score_mark ("NAME"    , '°');
   yenv_score_mark ("FINAL"   , '°');
   return 0;
}

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
   --rce;  if (a_full == NULL)  return rce;
   /*---(prepare)------------------------*/
   strlcpy (x_full, a_full, LEN_PATH);
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
   /*---(config mark(--------------------*/
   --rce;  if (c_naming == 0 || strchr (YENV_NAMING, c_naming) == NULL) {
      DEBUG_YENV   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   yenv_score_mark ("NCONF"   , c_naming);
   /*---(default)------------------------*/
   if (r_style != NULL)  *r_style = '-';
   if (r_full  != NULL)  strcpy (r_full , "");
   /*---(defense : dir null)-------------*/
   yenv_score_mark ("NFULL"   , '£');
   DEBUG_YENV   yLOG_point   ("a_dir"     , a_dir);
   --rce;  if (a_dir       == NULL) {
      yenv_name_fatal ("directory name can not be null (blatant error)");
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
      yenv_name_fatal ("file name can not be null (blatant error)");
      DEBUG_YENV   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YENV   yLOG_info    ("a_file"    , a_file);
   lf = strlen (a_file);
   DEBUG_YENV   yLOG_value   ("lf"        , lf);
   yURG_msg ('-', "requested file %3då%sæ", lf, a_file);
   /*---(check for empty)----------------*/
   yenv_score_mark ("NFULL"   , '-');
   --rce;  if (ld < 1) {
      yenv_name_fatal ("directory name can not be empty (blatant error)");
      DEBUG_YENV   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(check for empty)----------------*/
   yenv_score_mark ("NFULL"   , '=');
   --rce;  if (a_type == YENV_DIR && lf > 0) {
      yenv_name_fatal ("with DIR type, file name must be empty (blatant error)");
      DEBUG_YENV   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(directory absolute)-------------*/
   yenv_score_mark ("NFULL"   , '/');
   --rce;  if (a_dir  [0] != '/') {
      yenv_name_fatal ("directory name must be absolute reference, i.e., start with '/'");
      DEBUG_YENV   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   } else {
      DEBUG_YENV    yLOG_note    ("directory name is absoulte reference");
   }
   /*---(file relative)------------------*/
   yenv_score_mark ("NFULL"   , '›');
   --rce;  if (lf > 0 && a_file [0] == '/') {
      yenv_name_fatal ("file name must be relative reference, i.e., no leading '/'");
      DEBUG_YENV   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   } else {
      DEBUG_YENV    yLOG_note    ("file name is relative reference");
   }
   /*---(hidden file)--------------------*/
   if (c_naming != '-') {
      yenv_score_mark ("NFULL"   , '´');
      DEBUG_YENV    yLOG_char    ("first char", a_file [0]);
      --rce;  if (a_file [0] == '.') {
         sprintf (x_msg, "file can not be hidden, lead period, in (%c) mode (security risk)", c_naming);
         yenv_name_fatal (x_msg);
         DEBUG_YENV   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
   }
   /*---(create full)--------------------*/
   rc = yENV_name_full (a_dir, a_file, &x_style, x_full);
   DEBUG_YENV   yLOG_value   ("full"      , rc);
   l = strlen (x_full);
   yURG_msg ('-', "full name      %3då%sæ", l, x_full);
   DEBUG_YENV    yLOG_complex ("x_full"    , "%3då%sæ", l, x_full);
   /*---(check name quality)-------------*/
   yenv_score_mark ("NFULL"   , '¢');
   switch (c_naming) {
   case '-' :  strcpy (x_valid, YSTR_EXTEN);  break;
   default  :  strcpy (x_valid, YSTR_FILES);  break;
   }
   l = strlen (x_full);
   --rce;  for (i = 0; i < l; ++i) {
      if (strchr (x_valid, x_full [i]) == NULL) {
         sprintf (x_msg, "full name has an illegal character (%c) at position %d in (%c) mode", x_full [i], i, c_naming);
         yenv_name_fatal (x_msg);
         DEBUG_YENV    yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
   }
   /*---(success)------------------------*/
   yenv_score_mark ("NFULL"   , 'n');
   switch (c_naming) {
   case '-' :  yURG_msg ('-', "name (%c/%c) is fully qualified and uses only legal characters", x_style, c_naming);                    break;
   default  :  yURG_msg ('-', "name (%c/%c) is fully qualified, not hidden/temp, and uses only legal characters", x_style, c_naming);  break;
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
yenv_name_standard      (char a_type, char c_naming, char c_style, char a_dir [LEN_PATH], char a_file [LEN_PATH], char a_prefix [LEN_TERSE], char a_suffix [LEN_TERSE])
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
   char        x_save_pre  [LEN_TERSE] = "";
   char        x_save_suf  [LEN_TERSE] = "";
   char        x_msg       [LEN_HUND]  = "";
   /*---(header)-------------------------*/
   DEBUG_YENV   yLOG_enter   (__FUNCTION__);
   /*---(config mark(--------------------*/
   --rce;  if (c_naming == 0 || strchr (YENV_NAMING, c_naming) == NULL) {
      DEBUG_YENV   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   yenv_score_mark ("NCONF"   , c_naming);
   yenv_score_mark ("NFIXES"  , '-');
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
   /*---(prepare)------------------------*/
   yenv_score_mark ("NFIXES"  , '¢');
   /*---(defense)------------------------*/
   DEBUG_YENV   yLOG_point   ("a_dir"     , a_dir);
   --rce;  if (a_dir  == NULL || a_dir  [0] == '\0') {
      yenv_name_fatal ("directory name can not be null/empty (blatant error)");
      DEBUG_YENV   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YENV   yLOG_info    ("a_dir"     , a_dir);
   DEBUG_YENV   yLOG_point   ("a_file"    , a_file);
   --rce;  if (a_file == NULL || a_file [0] == '\0') {
      yenv_name_fatal ("file name can not be null/empty (blatant error)");
      DEBUG_YENV   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YENV   yLOG_info    ("a_file"    , a_file);
   DEBUG_YENV   yLOG_point   ("a_prefix"  , a_prefix);
   --rce;  if (a_prefix == NULL) {
      yenv_name_fatal ("prefix standard can not be null (blatant error)");
      DEBUG_YENV   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YENV   yLOG_point   ("a_suffix"  , a_suffix);
   --rce;  if (a_suffix == NULL) {
      yenv_name_fatal ("suffix standard can not be null (blatant error)");
      DEBUG_YENV   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(check request)------------------*/
   yenv_score_mark ("NFIXES"  , '#');
   if (a_prefix != NULL && strcmp (a_prefix, "") != 0)  { strlcpy (x_pre, a_prefix, LEN_TERSE);  ++x_min;  }
   if (a_suffix != NULL && strcmp (a_suffix, "") != 0)  { strlcpy (x_suf, a_suffix, LEN_TERSE);  ++x_min;  }
   if (c_naming == 'c')  x_min -= 1;
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
      if      (x_min == 2)                     sprintf (x_msg, "need both prefix and suffix, i.e., at least 2 dot (.) separators, but only provided %d (illegal name)", c);
      else if (x_min == 1 && c_naming == 'c')  sprintf (x_msg, "need both prefix and suffix, i.e., at least 1 dot (.) separator, but only provided %d (illegal name)", c);
      else if (strcmp (x_pre, "") != 0)        sprintf (x_msg, "need prefix, i.e. at least 1 dot (.) separator, but provided none (illegal name)");
      else                                     sprintf (x_msg, "need suffix, i.e. at least 1 dot (.) separator, but provided none (illegal name)");
      yenv_name_fatal (x_msg);
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
   yenv_score_mark ("NFIXES"  , 'P');
   --rce;  if (a_prefix != NULL && strcmp (a_prefix, "") != 0)  {
      DEBUG_YENV    yLOG_info    ("a_prefix"  , a_prefix);
      if (strcmp (a_prefix, "(USER).") == 0) {
         DEBUG_YENV    yLOG_note    ("using user name prefix handler");
         strlcpy (t, a_file, x_npre + 1);
         DEBUG_YENV    yLOG_info    ("t"         , t);
         rc = yENV_user_data ('n', t, NULL, NULL, NULL, NULL);
         if (rc < 0) {
            sprintf (x_msg, "name prefix å%sæ does not match any system user (illegal)", t);
            yenv_name_fatal (x_msg);
            DEBUG_YENV    yLOG_exitr   (__FUNCTION__, rce);
            return rce;
         }
         strlcpy (t, a_file, x_npre + 2);
      } else {
         DEBUG_YENV    yLOG_note    ("using normal prefix handler");
         strlcpy (t, a_file, x_npre + 2);
         DEBUG_YENV    yLOG_info    ("t"         , t);
         if (strcmp (t, a_prefix) != 0) {
            sprintf (x_msg, "name prefix å%sæ does not match given standard å%sæ (illegal)", t, a_prefix);
            yenv_name_fatal (x_msg);
            DEBUG_YENV    yLOG_exitr   (__FUNCTION__, rce);
            return rce;
         }
      }
      strlcpy (x_save_pre, t, LEN_TERSE);
      x_pgood = 'y';
      x_rem  -= x_npre + 1;
      DEBUG_YENV   yLOG_value   ("x_rem"     , x_rem);
   }
   /*---(check suffix)-------------------*/
   yenv_score_mark ("NFIXES"  , 'S');
   --rce;  if (strcmp (a_suffix, "") != 0)  {
      DEBUG_YENV    yLOG_info    ("a_suffix"  , a_suffix);
      strlcpy (t, a_file + x_nsuf, LEN_TERSE);
      DEBUG_YENV    yLOG_info    ("t"         , t);
      if (strcmp (t, a_suffix) != 0) {
         sprintf (x_msg, "name suffix å%sæ does not match given standard å%sæ (illegal)", t, a_suffix);
         yenv_name_fatal (x_msg);
         DEBUG_YENV    yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      strlcpy (x_save_suf, t, LEN_TERSE);
      x_sgood = 'y';
      x_rem  -= l - x_nsuf;
      DEBUG_YENV   yLOG_value   ("x_rem"     , x_rem);
   }
   /*---(remaining description)----------*/
   yenv_score_mark ("NFIXES"  , 'R');
   DEBUG_YENV   yLOG_value   ("x_rem"     , x_rem);
   --rce;  if (x_rem < 3 && c_naming == 'l') {
      yenv_name_fatal ("file description can not be shorter than 3 characters (lazy)");
      DEBUG_YENV    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(done)---------------------------*/
   yenv_score_mark ("NFIXES"  , 'N');
   if      (x_pgood == 'y' && x_sgood == 'y')     yURG_msg ('-', "prefix å%sæ and suffix å%sæ match given standard", x_save_pre, x_save_suf);
   else if (x_pgood == 'y')                       yURG_msg ('-', "prefix å%sæ matches given standard", x_save_pre);
   else if (x_sgood == 'y')                       yURG_msg ('-', "suffix å%sæ matches given standard", x_save_suf);
   /*---(complete)-----------------------*/
   DEBUG_YENV   yLOG_exit    (__FUNCTION__);
   return RC_POSITIVE;
}

char
yenv_name_local         (char c_naming, int a_ruid, char a_ruser [LEN_USER], char a_full [LEN_PATH], char b_owner [LEN_USER], char b_group [LEN_USER], char b_perms [LEN_TERSE])
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
      DEBUG_YENV   yLOG_note    ("file located under root");
      if (a_ruid != 0) {
         sprintf (x_msg, "running as å%sæ, uid (%d); BUT, file in å%sæ (illegal)", a_ruser, a_ruid, x_root);
         yenv_name_fatal (x_msg);
         DEBUG_YENV    yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      yURG_msg ('-', "good, running as å%sæ, uid (%d) and file is located in or below å%sæ", a_ruser, a_ruid, x_root);
      yenv_score_mark ("NLOC"    , 'R');
      strcpy (t, "root");
      /*---(done)------------------------*/
   }
   /*---(check home)---------------------*/
   else if (strncmp (a_full, x_home, strlen (x_home)) == 0) {
      yenv_score_mark ("NLOC"    , 'h');
      strcpy (t, a_full + strlen (x_home));
      DEBUG_YENV   yLOG_info    ("t"         , t);
      p = strchr (t, '/');
      DEBUG_YENV   yLOG_point   ("p"         , p);
      if (p != NULL)  p [0] = '\0';
      else            strcpy (t, "");
      DEBUG_YENV   yLOG_info    ("t"         , t);
      rc = yENV_user_data ('n', t, &x_fuid, NULL, NULL, NULL);
      if (rc < 0) {
         sprintf (x_msg, "could not find å%sæ as a legal user subdirectory under å%sæ (illegal)", t, x_home);
         yenv_name_fatal (x_msg);
         DEBUG_YENV    yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      if      (a_ruid == 0) ;
      else if (strcmp (a_ruser, t) == 0) ;
      else {
         sprintf (x_msg, "running as å%sæ, uid (%d); BUT, file in å%sæ (illegal)", a_ruser, a_ruid, t);
         yenv_name_fatal (x_msg);
         DEBUG_YENV    yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      yURG_msg ('-', "good, running as å%sæ, uid (%d) and file is located in or below å%sæ", a_ruser, a_ruid, t);
      yenv_score_mark ("NLOC"    , 'H');
      /*---(done)------------------------*/
   }
   /*---(elsewhere)----------------------*/
   else {
      yenv_score_mark ("NLOC"    , '°');
      sprintf (x_msg, "file not in å%sæ or under å%sæ and so can not be handled", x_root, x_home);
      yenv_name_fatal (x_msg);
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
yenv_name_central       (char c_naming, int a_ruid, char a_ruser [LEN_USER], char a_full [LEN_PATH], char b_owner [LEN_USER], char b_group [LEN_USER], char b_perms [LEN_TERSE])
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
      DEBUG_YENV   yLOG_note    ("file located under root");
      if (a_ruid != 0) {
         sprintf (x_msg, "running as å%sæ, uid (%d); BUT, file in å%sæ (illegal)", a_ruser, a_ruid, x_etc);
         yenv_name_fatal (x_msg);
         DEBUG_YENV    yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      yURG_msg ('-', "good, running as å%sæ, uid (%d) and file is located in or below å%sæ", a_ruser, a_ruid, x_etc);
      yenv_score_mark ("NLOC"    , 'E');
   }
   /*---(check spool)--------------------*/
   else if (strncmp (a_full, x_spool, strlen (x_spool)) == 0) {
      yenv_score_mark ("NLOC"    , 's');
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
         sprintf (x_msg, "could not find å%sæ as a legal user (illegal)", t, x_spool);
         yenv_name_fatal (x_msg);
         DEBUG_YENV    yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      if (a_ruid == 0 || strcmp (a_ruser, t) == 0) {
         yURG_msg ('-', "good, running as å%sæ, uid (%d) so can handle file prefixed as å%sæ", a_ruser, a_ruid, t);
         yenv_score_mark ("NLOC"    , 'S');
      } else {
         sprintf (x_msg, "running as å%sæ, uid (%d); BUT, file prefixed as å%sæ (illegal)", a_ruser, a_ruid, t);
         yenv_name_fatal (x_msg);
         DEBUG_YENV    yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
   }
   /*---(elsewhere)----------------------*/
   else {
      yenv_score_mark ("NLOC"    , '°');
      sprintf (x_msg, "file not in å%sæ or under å%sæ and so can not be handled", x_etc, x_spool);
      yenv_name_fatal (x_msg);
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
   char        x_msg       [LEN_HUND]  = "";
   /*---(header)-------------------------*/
   DEBUG_YENV   yLOG_enter   (__FUNCTION__);
   /*---(config mark(--------------------*/
   --rce;  if (c_naming == 0 || strchr (YENV_NAMING, c_naming) == NULL) {
      DEBUG_YENV   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   yenv_score_mark ("NCONF"   , c_naming);
   yenv_score_mark ("NLOC"    , '-');
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
      yenv_name_fatal ("could not identify current user  (scary)");
      DEBUG_YENV    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YENV   yLOG_info    ("x_ruser"   , x_ruser);
   /*---(handle locals)------------------*/
   if (c_naming == YENV_LOCAL) {
      DEBUG_YENV   yLOG_note    ("handling local");
      rc = yenv_name_local   (c_naming, x_ruid, x_ruser, a_full, b_owner, b_group, b_perms);
      if (rc < 0) {
         DEBUG_YENV    yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
   }
   /*---(check centrals)-----------------*/
   if (c_naming == YENV_CENTRAL) {
      DEBUG_YENV   yLOG_note    ("handling central");
      rc = yenv_name_central (c_naming, x_ruid, x_ruser, a_full, b_owner, b_group, b_perms);
      if (rc < 0) {
         DEBUG_YENV    yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
   }
   /*---(complete)-----------------------*/
   DEBUG_YENV   yLOG_exit    (__FUNCTION__);
   return RC_POSITIVE;
}




