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
   char        x_dir       [LEN_PATH]  = "";
   char        x_file      [LEN_PATH]  = "";
   /*---(default)------------------------*/
   if (r_style != NULL)  *r_style = '-';
   if (r_full  != NULL)  strcpy (r_full , "");
   /*---(defense)------------------------*/
   --rce;  if (a_dir  == NULL)  return rce;
   --rce;  if (a_file == NULL)  return rce;
   /*---(prepare)------------------------*/
   ld = strlen (a_dir);
   lf = strlen (a_file);
   /*---(check for single field)---------*/
   if (ld == 0 && lf == 0) {
      ;
   } else if (ld == 0) {
      yENV_name_split (a_file, &x_style, x_dir, x_file);
   } else if (lf == 0) {
      yENV_name_split (a_dir , &x_style, x_dir, x_file);
   } else {
      strlcpy (x_dir , a_dir , LEN_PATH);
      strlcpy (x_file, a_file, LEN_PATH);
   }
   /*---(prepare)------------------------*/
   ld = strlen (x_dir);
   lf = strlen (x_file);
   /*---(more defense)-------------------*/
   --rce;  if (ld > 0 && x_dir  [0] != '/')  return rce;
   --rce;  if (lf > 0 && x_file [0] == '/')  return rce;
   /*---(check special)------------------*/
   if      (strcmp (x_file, "dir"    ) == 0)  lf = 0;
   else if (strcmp (x_file, "code"   ) == 0)  lf = 0;
   else if (strcmp (x_file, "source" ) == 0)  lf = 0;
   else if (strcmp (x_file, "sources") == 0)  lf = 0;
   /*---(concatenate)--------------------*/
   if      (ld == 0 && lf == 0)           x_style = '-';
   else if (ld == 0)                    { x_style = 'f';  sprintf (x_full, "%s", x_file); }
   else if (lf == 0) {
      x_style = 'd';
      if (x_dir [ld - 1] != '/')    sprintf (x_full, "%s/", x_dir);
      else                          sprintf (x_full, "%s" , x_dir);
   } else {
      x_style = 'b';
      if (x_dir [ld - 1] != '/')    sprintf (x_full, "%s/%s", x_dir, x_file);
      else                          sprintf (x_full, "%s%s" , x_dir, x_file);
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
   /*> int         l           =    0;                                                <*/
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
   /*> l = strlen (x_full);                                                           <*/
   /*> --rce;  if (l > 0 && a_full [0] != '/')  return rce;                           <*/
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
yENV_name_detail        (char a_full [LEN_PATH], char *r_style, char r_dir [LEN_PATH], char r_file [LEN_FULL], char r_proj [LEN_LABEL], char r_base [LEN_HUND], char r_ext [LEN_TERSE], char *r_level, char *r_quality)
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
   x_type = yENV_exists (a_full);
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



