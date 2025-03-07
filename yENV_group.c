/*===[[ START ]]==============================================================*/
#include    "yENV.h"
#include    "yENV_priv.h"



/*====================------------------------------------====================*/
/*===----                          core function                       ----===*/
/*====================------------------------------------====================*/
static void      o___CORE_______________o (void) {;}

char
yENV_group_data         (char a_type, char b_name [LEN_USER], int *b_gid)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   tGROUP     *x_group     = NULL;
   /*---(default)------------------------*/
   if (b_name  != NULL && a_type != 'n')  strcpy (b_name, "");
   if (b_gid   != NULL && a_type != 'i')  *b_gid = -1;
   /*---(defense)------------------------*/
   --rce;  if (a_type == '\0' || strchr ("ni", a_type) == NULL)                return rce;
   --rce;  if (a_type == 'n' && (b_name == NULL || strcmp (b_name, "") == 0))  return rce;
   --rce;  if (a_type == 'i' && (b_gid  == NULL || *b_gid < 0))                return rce;
   /*---(get owner record)---------------*/
   if (a_type == 'n')    x_group = getgrnam (b_name);
   else                  x_group = getgrgid (*b_gid);
   --rce;  if (x_group == NULL)                                                return rce;
   /*---(save back)----------------------*/
   if (a_type == 'i' && b_name  != NULL)  strlcpy (b_name , x_group->gr_name , LEN_USER);
   if (a_type == 'n' && b_gid   != NULL)  *b_gid = x_group->gr_gid;
   /*---(complete)-----------------------*/
   return 0;
}



/*====================------------------------------------====================*/
/*===----                     unit testing support                     ----===*/
/*====================------------------------------------====================*/
static void      o___UNITEST____________o (void) {;}

char
yENV_group_add          (char a_name [LEN_USER], int a_gid)
{
   /*---(design notes)-------------------*/
   /*
    *  group names are 3 to 7 chars
    *  unit testing groups using gid's 900 to 999 only
    *  in use, group names are prefixed with "UNIT_"
    *
    */
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_name      [LEN_USER] = "";
   char        x_cmd       [LEN_RECD] = "";
   char        t           [LEN_RECD] = "";
   int         x_rand      =    0;
   int         g           =   -1;
   /*---(defense)------------------------*/
   --rce;  if (a_name == NULL) return rce;
   --rce;  if (a_gid < 900 || a_gid > 999)         return rce;
   --rce;  if (strncmp (a_name, "GRP_", 4) != 0)   return rce;
   /*---(check for existing)-------------*/
   rc = yENV_group_data ('n', a_name, &g);
   --rce;  if (rc >= 0 && g >= 0) {
      if (g == a_gid)                              return 1;
      else                                         return rce;
   }
   rc = yENV_group_data ('i', x_name, &a_gid);
   --rce;  if (rc >= 0) {
      if (strcmp (x_name, a_name) != 0)            return rce;
      else                                         return 2;
   }
   /*---(remove old version)-------------*/
   sprintf (x_cmd, "groupadd --gid %d", a_gid);
   /*---(change password)----------------*/
   srand (time (NULL));
   x_rand = rand ();
   sprintf (t, " --password %-8.8x ", x_rand);
   strcat   (x_cmd, t);
   /*---(create)-------------------------*/
   sprintf  (t, " %s  >> /dev/null 2>&1", a_name);
   strcat   (x_cmd, t);
   rc = system (x_cmd);
   --rce;  if (rc < 0)                             return rce;
   /*---(lock account)-------------------*/
   snprintf (x_cmd, LEN_RECD, "gpasswd --restrict %s >> /dev/null 2>&1", a_name);
   rc = system (x_cmd);
   --rce;  if (rc < 0)                             return rce;
   /*---(sync)---------------------------*/
   snprintf (t, LEN_HUND, "sync");
   rc = system (t);
   --rce;  if (rc < 0)                             return rce;
   /*---(verify)-------------------------*/
   rc = yENV_group_data ('n', a_name, NULL);
   --rce;  if (rc <  0)                            return rce;
   /*---(complete)-----------------------*/
   return 0; 
}

char
yENV_group_del          (char a_name [LEN_USER])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        t           [LEN_HUND]  = "";
   int         g           =   -1;
   /*---(defense)------------------------*/
   --rce;  if (a_name == NULL)                     return rce;
   --rce;  if (strncmp (a_name, "GRP_", 4) != 0)   return rce;
   /*---(check for group)----------------*/
   rc = yENV_group_data ('n', a_name, &g);
   --rce;  if (rc < 0)                             return 1;
   --rce;  if (g < 900 || g > 999)                 return rce;
   /*---(delete)-------------------------*/
   snprintf (t, LEN_HUND, "groupdel %s >> /dev/null 2>&1", a_name);
   rc = system (t);
   --rce;  if (rc < 0)   return rce;
   /*---(sync)---------------------------*/
   snprintf (t, LEN_HUND, "sync");
   rc = system (t);
   --rce;  if (rc < 0)   return rce;
   /*---(verify)-------------------------*/
   rc = yENV_group_data ('n', a_name, NULL);
   --rce;  if (rc >= 0)  return rce;
   /*---(complete)-----------------------*/
   return 0; 
}

char
yENV_group_purge        (void)
{
   char        rc          =    0;
   int         i           =    0;
   char        c           =    0;
   char        x_name      [LEN_USER] = "";
   for (i = 900; i <= 999; ++i) {
      rc = yENV_group_data ('i', x_name, &i);
      if (rc >= 0 && strncmp (x_name, "GRP_", 4) == 0) {
         rc = yENV_group_del (x_name);
         if (rc >= 0)  ++c;
      }
   }
   return c;
}

char
yENV_group_switch       (char a_text [LEN_USER])
{
   char        rce         =  -10;
   char        rc          =    0;
   int         x_gid       =   -1;
   rc = yENV_group_full (YENV_REG, a_text, NULL, &x_gid, NULL);
   --rce;  if (x_gid < 0)  return rce;
   rc = setegid (x_gid);
   --rce;  if (rc    < 0)  return rce;
   return 0;
}



/*====================------------------------------------====================*/
/*===----                          main driver                         ----===*/
/*====================------------------------------------====================*/
static void      o___DRIVER_____________o (void) {;}

char
yENV_group_full         (char a_type, char a_text [LEN_USER], char r_name [LEN_USER], int *r_gid, char r_handle [LEN_LABEL])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_group     [LEN_USER]  = "";
   int         x_gid       =   -1;
   /*---(header)-------------------------*/
   DEBUG_YENV    yLOG_senter  (__FUNCTION__);
   /*---(defaults)-----------------------*/
   if (r_name   != NULL)  strcpy (r_name  , "");
   if (r_gid    != NULL)  *r_gid   = -1;
   if (r_handle != NULL)  strcpy (r_handle, "");
   /*---(quick-out)----------------------*/
   if (a_type == YENV_NONE) {
      DEBUG_YENV    yLOG_snote   ("nothing to be done");
      DEBUG_YENV    yLOG_sexit   (__FUNCTION__);
      return 0;
   }
   if (a_type == YENV_SYM) {
      DEBUG_YENV    yLOG_snote   ("nothing to be done");
      DEBUG_YENV    yLOG_sexit   (__FUNCTION__);
      return 0;
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
   strlcpy (x_group, a_text, LEN_USER);
   rc = -1;
   x_gid = atoi (a_text);
   if (x_gid <= 0)                 x_gid = -1;
   if (strcmp (a_text, "0") == 0)  x_gid = 0;
   /*---(group by number)----------------*/
   --rce;  if (x_gid >= 0) {
      DEBUG_YENV    yLOG_snote   ("handle by group uid");
      if (r_handle != NULL)  strlcpy (r_handle, "gid", LEN_LABEL);
      rc = yENV_group_data ('i', x_group, &x_gid);
   }
   /*---(group by name)------------------*/
   --rce;  if (x_gid < 0 && strcmp (a_text, "") != 0) {
      DEBUG_YENV    yLOG_snote   ("handle by group name");
      if (r_handle != NULL)  strlcpy (r_handle, "name", LEN_LABEL);
      rc = yENV_group_data ('n', x_group, &x_gid);
   }
   /*---(group by current gid)-----------*/
   --rce;  if (x_gid < 0 && strcmp (a_text, "") == 0) {
      DEBUG_YENV    yLOG_snote   ("handle by current group");
      if (r_handle != NULL)  strlcpy (r_handle, "current", LEN_LABEL);
      x_gid = getgid ();
      rc = yENV_group_data ('i', x_group, &x_gid);
   }
   /*---(trouble)------------------------*/
   DEBUG_YENV    yLOG_sint    (rc);
   if (rc < 0) {
      DEBUG_YENV    yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YENV    yLOG_sint    (x_gid);
   /*---(save-back)----------------------*/
   if (r_name   != NULL)  strlcpy (r_name  , x_group, LEN_USER);
   if (r_gid    != NULL)  *r_gid   = x_gid;
   /*---(complete)-----------------------*/
   DEBUG_YENV    yLOG_sexit   (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                          simplifiers                         ----===*/
/*====================------------------------------------====================*/
static void      o___SIMPLE_____________o (void) {;}

char
yENV_group              (char a_text [LEN_USER], char r_name [LEN_USER], int *r_gid)
{
   return yENV_group_full (YENV_REG, a_text, r_name, r_gid, NULL);
}

char
yENV_group_gid          (char a_type, int a_value, char r_name [LEN_USER], int *r_gid)
{
   char        x_text      [LEN_TERSE] = "";
   snprintf (x_text, LEN_TERSE, "%d", a_value);
   return yENV_group_full (a_type, x_text, r_name, r_gid, NULL);
}



