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
yENV_dir_open           (char a_label [LEN_LABEL], char a_path [LEN_PATH], void **b_dir)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_path      [LEN_PATH]  = "";
   char       *p           = NULL;
   DIR        *x_dir       = NULL;
   /*---(header)-------------------------*/
   DEBUG_YENV   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YENV   yLOG_point   ("a_label"   , a_label);
   --rce;  if (a_label     == NULL) {
      DEBUG_YENV   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YENV   yLOG_info    ("a_label"   , a_label);
   DEBUG_YENV   yLOG_point   ("a_path"    , a_path);
   --rce;  if (a_path      == NULL) {
      DEBUG_YENV   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YENV   yLOG_info    ("a_path"    , a_path);
   DEBUG_YENV   yLOG_point   ("b_dir"     , b_dir);
   --rce;  if (b_dir      == NULL) {
      DEBUG_YENV   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YENV   yLOG_point   ("*b_dir"    , *b_dir);
   --rce;  if (*b_dir != NULL) {
      DEBUG_YENV   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(ground)-------------------------*/
   *b_dir = NULL;
   /*---(update path)--------------------*/
   --rce;  if (strcmp (a_path, ".") == 0) {
      p = getcwd (x_path, LEN_PATH);
      DEBUG_DATA   yLOG_point   ("p"         , p);
      --rce;  if (p == NULL) {
         DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
   } else {
      strlcpy (x_path, a_path, LEN_PATH);
   }
   DEBUG_DATA   yLOG_info    ("x_path"    , x_path);
   /*---(open)---------------------------*/
   x_dir = opendir (x_path);
   DEBUG_DATA   yLOG_point   ("open"      , x_dir);
   --rce;  if (x_dir == NULL) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(save-back)----------------------*/
   if (b_dir  != NULL)  *b_dir  = x_dir;
   /*---(message)------------------------*/
   yURG_msg ('-', "%s openned successfully", a_label);
   /*---(complete)-----------------------*/
   DEBUG_YENV   yLOG_exit    (__FUNCTION__);
   return RC_POSITIVE;
}

char
yENV_dir_close          (char a_label [LEN_LABEL], void **b_dir)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_YENV    yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YENV   yLOG_point   ("a_label"   , a_label);
   --rce;  if (a_label     == NULL) {
      DEBUG_YENV   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YENV   yLOG_info    ("a_label"   , a_label);
   DEBUG_YENV   yLOG_point   ("b_dir"     , b_dir);
   --rce;  if (b_dir      == NULL) {
      DEBUG_YENV   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YENV   yLOG_point   ("*b_dir"    , *b_dir);
   --rce;  if (*b_dir == NULL) {
      DEBUG_YENV   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(close)--------------------------*/
   rc = closedir (*b_dir);
   DEBUG_DATA   yLOG_value   ("close"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(ground)-------------------------*/
   *b_dir = NULL;
   DEBUG_YENV   yLOG_point   ("*b_dir"    , *b_dir);
   /*---(message)------------------------*/
   yURG_msg ('-', "%s closed successfully", a_label);
   /*---(complete)-----------------------*/
   DEBUG_YENV    yLOG_exit    (__FUNCTION__);
   return RC_POSITIVE;
}

char
yENV_dir_read           (void *a_dir, char c_self, char c_hide, char c_temp, char a_white [LEN_FULL], char a_black [LEN_FULL], int *b_read, int *b_accept, char r_name [LEN_HUND])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   DIR        *x_dir       = NULL;
   char        x_name      [LEN_HUND]  = "";
   int         x_len       =    0;
   int         x_line      =    0;
   int         x_accept    =    0;
   tDENTRY    *x_entry     = NULL;           /* contains very little other than inode and name */
   char        x_ext       [LEN_TERSE] = "";
   char        t           [LEN_LABEL] = "";
   char       *p           = NULL;
   /*---(header)-------------------------*/
   DEBUG_YENV   yLOG_enter   (__FUNCTION__);
   /*---(default)------------------------*/
   if (b_read   != NULL)  x_line   = *b_read;
   if (b_accept != NULL)  x_accept = *b_accept;
   if (r_name   != NULL)  strcpy (r_name, "");
   /*---(defense)------------------------*/
   DEBUG_YENV   yLOG_point   ("a_dir"     , a_dir);
   --rce;  if (a_dir == NULL) {
      DEBUG_YENV   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(read)------------------------*/
   x_dir = (DIR*) a_dir;
   /*---(read)------------------------*/
   --rce;  while (1) {
      /*---(initialize)------------------*/
      strcpy (x_name, "");
      /*---(read)------------------------*/
      x_entry = readdir (x_dir);
      DEBUG_DATA   yLOG_point   ("x_entry"   , x_entry);
      if (x_entry == NULL)  {
         DEBUG_YENV   yLOG_note    ("hit end-of-dir");
         break;
      }
      /*---(handle)----------------------*/
      ++x_line;
      strlcpy (x_name, x_entry->d_name, LEN_HUND);
      x_len = strlen (x_name);
      DEBUG_YENV   yLOG_complex ("x_recd"    , "%3d, %3då%sæ", x_line, x_len, x_name);
      /*---(filter self)-----------------*/
      DEBUG_DATA   yLOG_char    ("c_self"    , c_self);
      if (c_self != 'y') {
         if      (strcmp (x_name, "." ) == 0) {
            DEBUG_YENV   yLOG_note    ("self-referent directory entry");
            continue;
         }
         else if (strcmp (x_name, "..") == 0) {
            DEBUG_YENV   yLOG_note    ("parent directory entry");
            continue;
         }
      }
      /*---(filter hidden)---------------*/
      DEBUG_DATA   yLOG_char    ("c_hide"    , c_hide);
      if (c_hide != 'y') {
         if      (strcmp (x_name, "." ) == 0) ;
         else if (strcmp (x_name, "..") == 0) ;
         else if (x_name [0] == '.') {
            DEBUG_YENV   yLOG_note    ("hidden entry, dot (.) prefix");
            continue;
         }
      }
      /*---(filter temp)-----------------*/
      DEBUG_DATA   yLOG_char    ("c_temp"    , c_temp);
      if (c_temp != 'y') {
         if      (x_len > 1 && strcmp (x_name + (x_len - 1), "~") == 0) {
            DEBUG_YENV   yLOG_note    ("system marked temp, tilde (~) suffix");
            continue;
         }
         else if (x_len > 4 && strcmp (x_name + (x_len - 4), ".swp") == 0) {
            DEBUG_YENV   yLOG_note    ("program marked temp, å.swpæ extension");
            continue;
         }
      }
      /*---(extensions)------------------*/
      if (a_white != NULL || a_black != NULL) {
         rc = yENV_name_detail (x_name, NULL, NULL, NULL, NULL, NULL, x_ext, NULL, NULL);
         DEBUG_YENV   yLOG_point   ("detail"    , rc);
         if (rc < 0) {
            DEBUG_YENV   yLOG_note    ("could not parse name");
            continue;
         }
         sprintf (t, ",%s,", x_ext);
         DEBUG_YENV   yLOG_complex ("t"         , "%2då%sæ", strlen (t), t);
         if (a_white != NULL && a_white [0] != '\0') {
            p = strstr (a_white, t);
            DEBUG_YENV   yLOG_point   ("p"         , p);
            if (p == NULL) {
               DEBUG_YENV   yLOG_note    ("extension not on white-list");
               continue;
            }
         }
         if (a_black != NULL && a_black [0] != '\0') {
            p = strstr (a_black, t);
            DEBUG_YENV   yLOG_point   ("p"         , p);
            if (p != NULL) {
               DEBUG_YENV   yLOG_note    ("extension is on black-list");
               continue;
            }
         }
      }
      /*---(accept)----------------------*/
      ++x_accept;
      DEBUG_YENV   yLOG_value   ("x_accept"  , x_accept);
      break;
      /*---(done)------------------------*/
   }
   /*---(save-back)-------------------*/
   if (b_read   != NULL)  *b_read   = x_line;;
   if (b_accept != NULL)  *b_accept = x_accept;;
   if (r_name   != NULL)  strlcpy (r_name, x_name, LEN_HUND);
   /*---(complete)-----------------------*/
   DEBUG_YENV   yLOG_exit    (__FUNCTION__);
   return 1;
}

char 
yENV_dir_full           (char a_label [LEN_LABEL], char a_path [LEN_PATH], char c_self, char c_hide, char c_temp, char a_white [LEN_FULL], char a_black [LEN_FULL], int *r_read, int *r_accept, void *f_handler, char r_string [LEN_MASS])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char      (*x_handler)   (int a_read, int a_accept, char a_name [LEN_HUND]);
   DIR        *x_dir       = NULL;
   int         x_line      =    0;
   int         x_accept    =    0;
   char        x_name      [LEN_HUND]  = "";
   char        x_count     [LEN_TERSE] = "";
   char        x_string    [LEN_MASS]  = "";
   /*---(header)-------------------------*/
   DEBUG_YENV   yLOG_enter   (__FUNCTION__);
   /*---(default)------------------------*/
   if (r_read    != NULL)  *r_read   = 0;
   if (r_accept  != NULL)  *r_accept = 0;
   if (r_string  != NULL)  strcpy (r_string, "");
   if (f_handler != NULL)  x_handler = f_handler;
   /*---(open)---------------------------*/
   rc = yENV_dir_open (a_label, a_path, &x_dir);
   DEBUG_DATA   yLOG_value   ("open"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(walk directory)-----------------*/
   --rce; while (1) {
      /*---(read)------------------------*/
      rc = yENV_dir_read (x_dir, c_self, c_hide, c_temp, a_white, a_black, &x_line, &x_accept, x_name);
      DEBUG_DATA   yLOG_value   ("read"      , rc);
      if (rc < 0) {
         DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      DEBUG_DATA   yLOG_info    ("x_name"    , x_name);
      if (x_name [0] == '\0') {
         DEBUG_YENV   yLOG_note    ("hit end-of-dir");
         break;
      }
      DEBUG_DATA   yLOG_info    ("x_name"    , x_name);
      /*---(record in string)------------*/
      if (r_string != NULL) {
         strlcat (x_string, "  "  , LEN_MASS);
         strlcat (x_string, x_name, LEN_MASS);
      }
      /*---(handle)----------------------*/
      DEBUG_DATA   yLOG_point   ("f_handler" , f_handler);
      if (f_handler != NULL) {
         rc = x_handler (x_line, x_accept, x_name);
         DEBUG_DATA   yLOG_value   ("handler"   , rc);
         if (rc < 0) {
            DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
            return rce;
         }
      }
      /*---(done)------------------------*/
   }
   /*---(close)--------------------------*/
   rc = yENV_dir_close (a_label, &x_dir);
   DEBUG_DATA   yLOG_value   ("close"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(save-back)-------------------*/
   if (r_read    != NULL)  *r_read   = x_line;;
   if (r_accept  != NULL)  *r_accept = x_accept;;
   if (r_string  != NULL) {
      strlcpy (r_string, a_path   , LEN_MASS);
      sprintf (x_count, "  [%d/%d]"  , x_line, x_accept);
      strlcat (r_string, x_count  , LEN_MASS);
      strlcat (r_string, x_string , LEN_MASS);
      strlcat (r_string, "  Ï"    , LEN_MASS);
   }
   /*---(complete)-----------------------*/
   DEBUG_YENV   yLOG_exit    (__FUNCTION__);
   return 1;
}


