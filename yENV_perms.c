/*===[[ START ]]==============================================================*/
#include    "yENV.h"
#include    "yENV_priv.h"



#define     MAX_PERM         50
typedef     struct cPERM    tPERM;
struct cPERM {
   char        name        [LEN_TERSE];
   char        desc        [LEN_HUND];
   int         value;
   char        disp        [LEN_TERSE];
};
const tENV_PERM zENV_perms [MAX_PERM] = {
   /* 123456789012345    12345678901234567890123456789012345678901234567890123456789012345678901234567890   12345    123456789  */
   /* ---name--------    ---description------------------------------------------------------------------   perms    -display-  */
   { "g_only"         , "only the group can see, access, or modify"                                       , 00070 , "---rwx---"},
   { "g_share"        , "only the group can modify, but all others can see and access"                    , 00075 , "---rwxr-x"},
   /*---(directories)-------------*/
   { "d_open"         , "everyone can access directory, then list, read, create, and delete files"        , 00777 , "rwxrwxrwx"},
   { "d_group"        , "owner and group can do anything, others can read"                                , 00775 , "rwxrwxr-x"},
   { "d_control"      , "owner and group can do anything, everyone else can do nothing"                   , 00770 , "rwxrwx---"},
   { "d_normal"       , "everyone can access directory, group and other can list and read files only"     , 00755 , "rwxr-xr-x"},
   { "d_normals"      , "everyone can access directory, group and other can list and read files only"     , 01755 , "rwxr-xr-t"},
   { "d_sgroup"       , "same as d_normal, but new files get directories group id"                        , 02755 , "rwxr-sr-x"},
   { "d_secure"       , "owner can do anything,  group can list and read files only, all others nothing"  , 00750 , "rwxw-x---"},
   { "d_tight"        , "owner can do anything, all others nothing"                                       , 00700 , "rwx------"},
   { "d_tights"       , "everyone can see, access, and modify, but only owner can delete"                 , 01700 , "rwx-----T"},
   /*---(root)--------------------*/
   { "r_share"        , "only root specifically can modify; but all others can see and access"            , 00555 , "r-xr-xr-x"},
   { "r_only"         , "only root specifically can sse, access, or modify; even root group can not"      , 00000 , "---------"},
   /*---(regular files)-----------*/
   { "f_open"         , "everyone can read and write"                                                     , 00666 , "rw-rw-rw-"},
   { "f_control"      , "owner and group can read and write, everyone else gets nothing"                  , 00660 , "rw-rw----"},
   { "f_hidev"        , "owner and group can read and write, everyone else read-only"                     , 00664 , "rw-rw-r--"},
   { "f_usb"          , "owner and group can read and write, everyone else read-only"                     , 00662 , "rw-rw--w-"},
   { "f_normal"       , "owner can read and write, everyone else can read only"                           , 00644 , "rw-r--r--"},
   { "f_secure"       , "owner can read and write, group can read only, everyone else gets nothing"       , 00640 , "rw-r-----"},
   { "f_tty"          , "owner can read and write, group can write only, everyone else gets nothing"      , 00620 , "rw--w----"},
   { "f_tight"        , "owner can read and write, everyone else gets nothing"                            , 00600 , "rw-------"},
   { "f_nodel"        , "everyone can see, access, and modify, but only owner can delete"                 , 01777 , "rwxrwxrwt"},
   /*---(end)---------------------*/
   { "end-of-entries" , "---marker---"                                                                    , 00000 , "---------"},
};



/*====================------------------------------------====================*/
/*===----                        DEPRECIATED                           ----===*/
/*====================------------------------------------====================*/
static void      o___DEPRECIATED________o (void) {;}

char  /*--- DEPRICATED ---*/
yENV_perms_data         (char a_type, char b_name [LEN_TERSE], int *b_perms, char b_disp [LEN_TERSE])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         i           =    0;
   uint        x_perms     =   -1;
   char        o           [LEN_TERSE] = "";
   int         l           =    0;
   /*---(default)------------------------*/
   if (b_name  != NULL && a_type != 'n')  strcpy (b_name, "");
   if (b_perms != NULL && a_type != 'i')  *b_perms = -1;
   if (b_disp  != NULL && a_type != 'd')  strcpy (b_disp, "");
   /*---(defense)------------------------*/
   --rce;  if (a_type == '\0' || strchr ("nid", a_type) == NULL)               return rce;
   --rce;  if (a_type == 'n' && (b_name  == NULL || strcmp (b_name, "") == 0)) return rce;
   --rce;  if (a_type == 'i' && (b_perms == NULL || *b_perms < 0))             return rce;
   --rce;  if (a_type == 'd' && (b_disp  == NULL || strcmp (b_disp, "") == 0)) return rce;
   /*---(find by name)-------------------*/
   --rce;  if (a_type == 'n') {
      for (i = 0; i < MAX_PERM; ++i) {
         if (strcmp (zENV_perms [i].name, b_name) != 0)  continue;
         if (b_perms != NULL)  *b_perms = zENV_perms [i].value;
         if (b_disp  != NULL)  strlcpy (b_disp , zENV_perms [i].disp  , LEN_TERSE);
         return 0;
      }
      return rce;
   }
   /*---(find by display)----------------*/
   --rce;  if (a_type == 'd') {
      for (i = 0; i < MAX_PERM; ++i) {
         if (strcmp (zENV_perms [i].disp, b_disp) != 0)  continue;
         if (b_name  != NULL)  strlcpy (b_name , zENV_perms [i].name  , LEN_TERSE);
         if (b_perms != NULL)  *b_perms = zENV_perms [i].value;
         return 0;
      }
      l = strlen (b_disp);
      if (l == 9) {
         x_perms = 0;
         if      (b_disp  [0] == '-')  ;
         else if (b_disp  [0] == 'r')  x_perms += 00400;
         else                          return rce;
         if      (b_disp  [1] == '-')  ;
         else if (b_disp  [1] == 'w')  x_perms += 00200;
         else                          return rce;
         if      (b_disp  [2] == '-')  ;
         else if (b_disp  [2] == 'x')  x_perms += 00100;
         else if (b_disp  [2] == 's')  x_perms += 04100;
         else if (b_disp  [2] == 'S')  x_perms += 04000;
         else                          return rce;
         if      (b_disp  [3] == '-')  ;
         else if (b_disp  [3] == 'r')  x_perms += 00040;
         else                          return rce;
         if      (b_disp  [4] == '-')  ;
         else if (b_disp  [4] == 'w')  x_perms += 00020;
         else                          return rce;
         if      (b_disp  [5] == '-')  ;
         else if (b_disp  [5] == 'x')  x_perms += 00010;
         else if (b_disp  [5] == 's')  x_perms += 02010;
         else if (b_disp  [5] == 'S')  x_perms += 02000;
         else                          return rce;
         if      (b_disp  [6] == '-')  ;
         else if (b_disp  [6] == 'r')  x_perms += 00004;
         else                          return rce;
         if      (b_disp  [7] == '-')  ;
         else if (b_disp  [7] == 'w')  x_perms += 00002;
         else                          return rce;
         if      (b_disp  [8] == '-')  ;
         else if (b_disp  [8] == 'x')  x_perms += 00001;
         else if (b_disp  [8] == 't')  x_perms += 01001;
         else if (b_disp  [8] == 'T')  x_perms += 01000;
         else                          return rce;
         if (b_name  != NULL)  strlcpy (b_name , "(n/a)", LEN_TERSE);
         if (b_perms != NULL)  *b_perms = x_perms;
         return 0;
      }
      return rce;
   }
   /*---(find by number)-----------------*/
   --rce;  if (a_type == 'i') {
      for (i = 0; i < MAX_PERM; ++i) {
         if (zENV_perms [i].value != *b_perms)  continue;
         if (b_name  != NULL)  strlcpy (b_name , zENV_perms [i].name  , LEN_TERSE);
         if (b_disp  != NULL)  strlcpy (b_disp , zENV_perms [i].disp  , LEN_TERSE);
         return 0;
      }
      if (b_name  != NULL)  strlcpy (b_name , "(n/a)", LEN_TERSE);
      if (b_disp != NULL) {
         sprintf (o, "%-5.5o", *b_perms);
         strcpy  (b_disp, "");
         for (i = 2; i <= 4; ++i) {
            switch (o [i]) {
            case '7'  :  strcat (b_disp, "rwx");  break;
            case '6'  :  strcat (b_disp, "rw-");  break;
            case '5'  :  strcat (b_disp, "r-x");  break;
            case '4'  :  strcat (b_disp, "r--");  break;
            case '3'  :  strcat (b_disp, "-wx");  break;
            case '2'  :  strcat (b_disp, "-w-");  break;
            case '1'  :  strcat (b_disp, "--x");  break;
            case '0'  :  strcat (b_disp, "---");  break;
            }
         }
         i = o [1] - '0';
         if (i >= 4) {
            if (b_disp [2] == 'x')  b_disp [2] = 's';
            else                    b_disp [2] = 'S';
         }
         if (i > 0 && i != 4 && i % 2 == 0) {
            if (b_disp [5] == 'x')  b_disp [5] = 's';
            else                    b_disp [5] = 'S';
         }
         if (i % 2 == 1) {
            if (b_disp [8] == 'x')  b_disp [8] = 't';
            else                    b_disp [8] = 'T';
         }
      }
      return 0;
   }
   /*---(complete)-----------------------*/
   return 0;
}



/*====================------------------------------------====================*/
/*===----                        conversions                           ----===*/
/*====================------------------------------------====================*/
static void      o___CONVERT____________o (void) {;}

int
yenv_display2octal      (char a_text [LEN_TERSE])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         x_perms     =    0;
   int         l           =    0;
   char        x_boom      =  '-';
   /*---(header)-------------------------*/
   --rce;  if (a_text == NULL) return rce;
   l = strlen (a_text);
   --rce;  if (l != 9)          return rce;
   /*---(owner)-----------------------*/
   if      (a_text [0] == '-')  ;
   else if (a_text [0] == 'r')  x_perms += 00400;
   else                         x_boom  = '0';
   if      (a_text [1] == '-')  ;
   else if (a_text [1] == 'w')  x_perms += 00200;
   else                         x_boom  = '1';
   if      (a_text [2] == '-')  ;
   else if (a_text [2] == 'x')  x_perms += 00100;
   else if (a_text [2] == 's')  x_perms += 04100;
   else if (a_text [2] == 'S')  x_perms += 04000;
   else                         x_boom  = '2';
   /*---(group)-----------------------*/
   if      (a_text [3] == '-')  ;
   else if (a_text [3] == 'r')  x_perms += 00040;
   else                         x_boom  = '3';
   if      (a_text [4] == '-')  ;
   else if (a_text [4] == 'w')  x_perms += 00020;
   else                         x_boom  = '4';
   if      (a_text [5] == '-')  ;
   else if (a_text [5] == 'x')  x_perms += 00010;
   else if (a_text [5] == 's')  x_perms += 02010;
   else if (a_text [5] == 'S')  x_perms += 02000;
   else                         x_boom  = '5';
   /*---(other)-----------------------*/
   if      (a_text [6] == '-')  ;
   else if (a_text [6] == 'r')  x_perms += 00004;
   else                         x_boom  = '6';
   if      (a_text [7] == '-')  ;
   else if (a_text [7] == 'w')  x_perms += 00002;
   else                         x_boom  = '7';
   if      (a_text [8] == '-')  ;
   else if (a_text [8] == 'x')  x_perms += 00001;
   else if (a_text [8] == 't')  x_perms += 01001;
   else if (a_text [8] == 'T')  x_perms += 01000;
   else                         x_boom  = '8';
   /*---(done)------------------------*/
   --rce;  if (x_boom != '-')   return rce;
   return x_perms;
}

char*
yenv_octal2display      (int a_perms)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         x_perms     =    0;
   char        x_one       =  '-';
   char        x_two       =  '-';
   char        x_four      =  '-';
   /*---(prepare)---------------------*/
   strcpy (g_print, "");
   x_perms = a_perms;
   /*---(defence)---------------------*/
   --rce;  if (a_perms < 0)      return g_print;
   --rce;  if (a_perms > 04777)  return g_print;
   /*---(special)---------------------*/
   if (x_perms >= 04000)   {  x_four = 'y';           x_perms -= 04000;  }
   if (x_perms >= 02000)   {  x_two  = 'y';           x_perms -= 02000;  }
   if (x_perms >= 01000)   {  x_one  = 'y';           x_perms -= 01000;  }
   /*---(owner)-----------------------*/
   if (x_perms >=  0400)   {  strcat (g_print, "r");  x_perms -=  0400;  }
   else                    {  strcat (g_print, "-");                     }
   if (x_perms >=  0200)   {  strcat (g_print, "w");  x_perms -=  0200;  }
   else                    {  strcat (g_print, "-");                     }
   if (x_perms >=  0100)   {  strcat (g_print, "x");  x_perms -=  0100;  }
   else                    {  strcat (g_print, "-");                     }
   /*---(owner tweak)-----------------*/
   if (x_four == 'y') {
      if (g_print [2] == 'x')  g_print [2] = 's';
      else                     g_print [2] = 'S';
   }
   /*---(group)-----------------------*/
   if (x_perms >=  0040)   {  strcat (g_print, "r");  x_perms -=  0040;  }
   else                    {  strcat (g_print, "-");                     }
   if (x_perms >=  0020)   {  strcat (g_print, "w");  x_perms -=  0020;  }
   else                    {  strcat (g_print, "-");                     }
   if (x_perms >=  0010)   {  strcat (g_print, "x");  x_perms -=  0010;  }
   else                    {  strcat (g_print, "-");                     }
   /*---(group tweak)-----------------*/
   if (x_two  == 'y') {
      if (g_print [5] == 'x')  g_print [5] = 's';
      else                     g_print [5] = 'S';
   }
   /*---(other)-----------------------*/
   if (x_perms >=  0004)   {  strcat (g_print, "r");  x_perms -=  0004;  }
   else                    {  strcat (g_print, "-");                     }
   if (x_perms >=  0002)   {  strcat (g_print, "w");  x_perms -=  0002;  }
   else                    {  strcat (g_print, "-");                     }
   if (x_perms >=  0001)   {  strcat (g_print, "x");  x_perms -=  0001;  }
   else                    {  strcat (g_print, "-");                     }
   /*---(other tweak)-----------------*/
   if (x_one  == 'y') {
      if (g_print [8] == 'x')  g_print [8] = 't';
      else                     g_print [8] = 'T';
   }
   /*---(complete)--------------------*/
   return g_print;
}



/*====================------------------------------------====================*/
/*===----                         searching                            ----===*/
/*====================------------------------------------====================*/
static void      o___SEARCH_____________o (void) {;}

char
yenv_perms_by_name      (char a_text [LEN_TERSE], char r_name [LEN_TERSE], int *r_perms, char r_disp [LEN_TERSE], char r_desc [LEN_HUND])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         i           =    0;
   int         l           =    0;
   /*---(defaults)-----------------------*/
   if (r_name  != NULL)  strcpy (r_name, "");
   if (r_perms != NULL)  *r_perms = -1;
   if (r_disp  != NULL)  strcpy (r_disp, "");
   if (r_desc  != NULL)  strcpy (r_desc, "");
   /*---(defense)------------------------*/
   --rce;  if (a_text == NULL)     return rce;
   l = strlen (a_text);
   --rce;  if (l <  4)             return rce;
   --rce;  if (a_text [1] != '_')  return rce;
   /*---(find)---------------------------*/
   for (i = 0; i < MAX_PERM; ++i) {
      if (strcmp (zENV_perms [i].name, a_text) != 0)  continue;
      if (r_name  != NULL)  strlcpy (r_name, zENV_perms [i].name, LEN_TERSE);
      if (r_perms != NULL)  *r_perms = zENV_perms [i].value;
      if (r_disp  != NULL)  strlcpy (r_disp, zENV_perms [i].disp, LEN_TERSE);
      if (r_desc  != NULL)  strlcpy (r_desc, zENV_perms [i].desc, LEN_HUND);;
      return 0;
   }
   /*---(defense)------------------------*/
   return --rce;
}

char
yenv_perms_by_disp      (char a_text [LEN_TERSE], char r_name [LEN_TERSE], int *r_perms, char r_disp [LEN_TERSE], char r_desc [LEN_HUND])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         i           =    0;
   int         x_perms     =    0;
   int         l           =    0;
   /*---(defaults)-----------------------*/
   if (r_name  != NULL)  strcpy (r_name, "");
   if (r_perms != NULL)  *r_perms = -1;
   if (r_disp  != NULL)  strcpy (r_disp, "");
   if (r_desc  != NULL)  strcpy (r_desc, "");
   /*---(defense)------------------------*/
   --rce;  if (a_text == NULL)  return rce;
   l = strlen (a_text);
   --rce;  if (l != 9)          return rce;
   /*---(find)---------------------------*/
   for (i = 0; i < MAX_PERM; ++i) {
      if (strcmp (zENV_perms [i].disp, a_text) != 0)  continue;
      if (r_name  != NULL)  strlcpy (r_name, zENV_perms [i].name, LEN_TERSE);
      if (r_perms != NULL)  *r_perms = zENV_perms [i].value;
      if (r_disp  != NULL)  strlcpy (r_disp, zENV_perms [i].disp, LEN_TERSE);
      if (r_desc  != NULL)  strlcpy (r_desc, zENV_perms [i].desc, LEN_HUND);;
      return 0;
   }
   /*---(at least translate)-------------*/
   x_perms = yenv_display2octal (a_text);
   if (x_perms >= 0) {
      if (r_name  != NULL)  strcpy (r_name, "(n/a)");
      if (r_perms != NULL)  *r_perms = x_perms;
      if (r_disp  != NULL)  strlcpy (r_disp, a_text, LEN_TERSE);
      return 0;
   }
   /*---(defense)------------------------*/
   return --rce;
}

char
yenv_perms_by_octal     (char a_text [LEN_TERSE], char r_name [LEN_TERSE], int *r_perms, char r_disp [LEN_TERSE], char r_desc [LEN_HUND])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         i           =    0;
   int         x_value     =   -1;
   char        x_disp      [LEN_TERSE] = "";
   int         l           =    0;
   /*---(defaults)-----------------------*/
   if (r_name  != NULL)  strcpy (r_name, "");
   if (r_perms != NULL)  *r_perms = -1;
   if (r_disp  != NULL)  strcpy (r_disp, "");
   if (r_desc  != NULL)  strcpy (r_desc, "");
   /*---(defense)------------------------*/
   --rce;  if (a_text == NULL)     return rce;
   l = strlen (a_text);
   --rce;  if (l <= 3 || l >=  6)  return rce;
   --rce;  if (a_text [0] != '0')  return rce;
   /*---(prepare)------------------------*/
   rc = sscanf (a_text, "%o", &x_value);
   --rce;  if (rc      <= 0)       return rce;
   --rce;  if (x_value <  0)       return rce;
   --rce;  if (x_value >  04777)   return rce;
   /*---(find)---------------------------*/
   for (i = 0; i < MAX_PERM; ++i) {
      if (zENV_perms [i].value != x_value)  continue;
      if (r_name  != NULL)  strlcpy (r_name, zENV_perms [i].name, LEN_TERSE);
      if (r_perms != NULL)  *r_perms = zENV_perms [i].value;
      if (r_disp  != NULL)  strlcpy (r_disp, zENV_perms [i].disp, LEN_TERSE);
      if (r_desc  != NULL)  strlcpy (r_desc, zENV_perms [i].desc, LEN_HUND);;
      return 0;
   }
   /*---(at least translate)-------------*/
   strlcpy (x_disp, yenv_octal2display (x_value), LEN_TERSE);
   if (strcmp (x_disp, "") != 0) {
      if (r_name  != NULL)  strcpy  (r_name, "(n/a)");
      if (r_perms != NULL)  *r_perms = x_value;
      if (r_disp  != NULL)  strlcpy (r_disp, x_disp, LEN_TERSE);
      return 0;
   }
   /*---(defense)------------------------*/
   return --rce;
}



/*====================------------------------------------====================*/
/*===----                        main driver                           ----===*/
/*====================------------------------------------====================*/
static void      o___DRIVER_____________o (void) {;}

char
yENV_perms_full         (char a_type, char a_text [LEN_TERSE], char r_name [LEN_TERSE], int *r_perms, char r_disp [LEN_TERSE], char r_desc [LEN_HUND], char r_handle [LEN_LABEL])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         l           =    0;
   char        x_handle    [LEN_LABEL] = "anything";
   /*---(header)-------------------------*/
   DEBUG_YENV    yLOG_senter  (__FUNCTION__);
   /*---(defaults)-----------------------*/
   if (r_name   != NULL)  strcpy (r_name  , "");
   if (r_perms  != NULL)  *r_perms = -1;
   if (r_disp   != NULL)  strcpy (r_disp  , "");
   if (r_desc   != NULL)  strcpy (r_desc  , "");
   if (r_handle != NULL)  strcpy (r_handle, "");
   /*---(quick-out)----------------------*/
   if (a_type == YENV_NONE) {
      DEBUG_YENV    yLOG_snote   ("nothing to be done");
      DEBUG_YENV    yLOG_sexit   (__FUNCTION__);
      return RC_ACK;
   }
   if (a_type == YENV_SYM) {
      DEBUG_YENV    yLOG_snote   ("nothing to be done");
      DEBUG_YENV    yLOG_sexit   (__FUNCTION__);
      return RC_ACK;
   }
   if (a_text != NULL && strcmp (a_text, "-") == 0) {
      DEBUG_YENV    yLOG_snote   ("ignore request");
      if (r_handle != NULL)  strlcpy (r_handle, "ignore", LEN_LABEL);
      DEBUG_YENV    yLOG_sexit   (__FUNCTION__);
      return RC_ACK;
   }
   /*---(defense)------------------------*/
   DEBUG_YENV    yLOG_schar   (a_type);
   --rce;  if (a_type == 0 || strchr (YENV_REAL, a_type) == NULL) {
      DEBUG_YENV    yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YENV    yLOG_spoint  (a_text);
   --rce;  if (a_text == NULL) {
      DEBUG_YENV    yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YENV    yLOG_snote   (a_text);
   /*---(prepare)------------------------*/
   l = strlen (a_text);
   DEBUG_YENV    yLOG_sint    (l);
   rc = -1;
   /*---(octal)--------------------------*/
   --rce;  if (rc < 0 && l >= 4 && l <= 5 && a_text [0] == '0') {
      DEBUG_YENV    yLOG_snote   ("handle as octal");
      if (r_handle != NULL)  strlcpy (r_handle, "octal", LEN_LABEL);
      rc = yenv_perms_by_octal (a_text, r_name, r_perms, r_disp, r_desc);
   }
   /*---(standard)-----------------------*/
   --rce;  if (rc < 0 && l >= 5 && a_text [1] == '_') {
      DEBUG_YENV    yLOG_snote   ("handle as standard");
      if (r_handle != NULL)  strlcpy (r_handle, "standard", LEN_LABEL);
      rc = yenv_perms_by_name  (a_text, r_name, r_perms, r_disp, r_desc);
   }
   /*---(display)------------------------*/
   --rce;  if (rc < 0 && l == 9 && strchr ("r-", a_text [0]) != NULL) {
      DEBUG_YENV    yLOG_snote   ("handle as displayed");
      if (r_handle != NULL)  strlcpy (r_handle, "display", LEN_LABEL);
      rc = yenv_perms_by_disp  (a_text, r_name, r_perms, r_disp, r_desc);
   }
   /*---(default)------------------------*/
   --rce;  if (rc < 0 && strcmp (a_text, "@") == 0) {
      DEBUG_YENV    yLOG_snote   ("handle as default");
      if (r_handle != NULL)  strlcpy (r_handle, "default", LEN_LABEL);
      if (a_type == YENV_DIR)    rc = yenv_perms_by_name  ("d_tight", r_name, r_perms, r_disp, r_desc);
      else                       rc = yenv_perms_by_name  ("f_tight", r_name, r_perms, r_disp, r_desc);
   }
   /*---(trouble)------------------------*/
   DEBUG_YENV    yLOG_sint    (rc);
   if (rc < 0) {
      DEBUG_YENV    yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_YENV    yLOG_sexit   (__FUNCTION__);
   return RC_POSITIVE;
}



/*====================------------------------------------====================*/
/*===----                          simplifiers                         ----===*/
/*====================------------------------------------====================*/
static void      o___SIMPLE_____________o (void) {;}

char
yENV_perms              (char a_text [LEN_TERSE], char r_name [LEN_TERSE], int *r_prm, char r_disp [LEN_TERSE], char r_desc [LEN_HUND])
{
   return yENV_perms_full (YENV_REG, a_text, r_name, r_prm, r_disp, r_desc, NULL);
}

char
yENV_perms_octal        (char a_type, int a_value, char r_name [LEN_TERSE], int *r_prm, char r_disp [LEN_TERSE])
{
   int         x_prm       =    0;
   char        x_text      [LEN_TERSE] = "";
   x_prm = a_value & 07777;
   snprintf (x_text, LEN_TERSE, "%05o", x_prm);
   return yENV_perms_full (a_type, x_text, r_name, r_prm, r_disp, NULL, NULL);
}



