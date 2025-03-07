/*===[[ START ]]==============================================================*/
#include    "yENV.h"
#include    "yENV_priv.h"



/*====================------------------------------------====================*/
/*===----                         foundation                           ----===*/
/*====================------------------------------------====================*/
static void      o___BASE_______________o (void) {;}

char
yENV_user_data          (char a_type, char b_name [LEN_USER], int *b_uid, int *r_gid, char r_dir [LEN_HUND], char r_shell [LEN_HUND])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   tPASSWD    *x_user      = NULL;
   /*---(default)------------------------*/
   if (b_name  != NULL && a_type != 'n')  strcpy (b_name, "");
   if (b_uid   != NULL && a_type != 'i')  *b_uid = -1;
   if (r_gid   != NULL)                   *r_gid = -1;
   if (r_dir   != NULL)                   strcpy (r_dir, "");
   if (r_shell != NULL)                   strcpy (r_shell, "");
   /*---(defense)------------------------*/
   --rce;  if (a_type == '\0' || strchr ("ni", a_type) == NULL)                return rce;
   --rce;  if (a_type == 'n' && (b_name == NULL || strcmp (b_name, "") == 0))  return rce;
   --rce;  if (a_type == 'i' && (b_uid  == NULL || *b_uid < 0))                return rce;
   /*---(get user record)----------------*/
   if (a_type == 'n')    x_user = getpwnam (b_name);
   else                  x_user = getpwuid (*b_uid);
   --rce;  if (x_user == NULL)                                                return rce;
   /*---(save back)----------------------*/
   if (a_type == 'i' && b_name  != NULL)  strlcpy (b_name , x_user->pw_name , LEN_USER);
   if (a_type == 'n' && b_uid   != NULL)  *b_uid = x_user->pw_uid;
   if (r_gid   != NULL)                   *r_gid = x_user->pw_gid;
   if (r_dir   != NULL)                   strlcpy (r_dir  , x_user->pw_dir  , LEN_HUND);
   if (r_shell != NULL)                   strlcpy (r_shell, x_user->pw_shell, LEN_HUND);
   /*---(complete)-----------------------*/
   return 0;
}



/*====================------------------------------------====================*/
/*===----                      unit testing support                    ----===*/
/*====================------------------------------------====================*/
static void      o___UNITTEST___________o (void) {;}

char
yENV_user_add           (char a_name [LEN_USER], int a_uid, char a_home, char a_shell)
{
   /*---(design notes)-------------------*/
   /*
    *  user names are 3 to 7 chars
    *  unit testing users using uid's 9000 to 9999 only
    *  in use, user names are prefixed with "UNIT_"
    *
    */
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         u           =   -1;
   char        x_name      [LEN_USER] = "";
   char        x_cmd       [LEN_RECD] = "";
   char        t           [LEN_RECD] = "";
   int         x_rand      =    0;
   char        x_pass      [LEN_LABEL] = "";
   char        x_ehome     [LEN_HUND]  = "";
   char        x_ahome     [LEN_HUND]  = "";
   char        x_eshell    [LEN_HUND]  = "/sbin/nologin";
   char        x_ashell    [LEN_HUND]  = "";
   /*---(defense)------------------------*/
   --rce;  if (a_name == NULL) return rce;
   --rce;  if (a_uid < 9000 || a_uid > 9999)       return rce;
   --rce;  if (strncmp (a_name, "USR_", 4) != 0)   return rce;
   /*---(check for existing)-------------*/
   rc = yENV_user_data ('n', a_name, &u, NULL, NULL, NULL);
   --rce;  if (rc >= 0 && u >= 0) {
      if (u == a_uid)                              return 1;
      else                                         return rce;
   }
   rc = yENV_user_data ('i', x_name, &a_uid, NULL, NULL, NULL);
   --rce;  if (rc >= 0) {
      if (strcmp (x_name, a_name) != 0)            return rce;
      else                                         return 2;
   }
   /*---(remove old version)-------------*/
   sprintf (x_cmd, "useradd --gid nobody --no-user-group ");
   /*---(home dir)-----------------------*/
   switch (a_home) {
   case 'y' :
      strcat (x_cmd, " --create-home ");
      break;
   default  :
      strcat (x_cmd, " --no-create-home ");
      break;
   }
   sprintf (x_ehome, "/home/%s", a_name);
   /*---(shell)--------------------------*/
   switch (a_shell) {
   case 'b' :
      strcpy  (x_eshell, "/bin/bash");
      break;
   case 'd' :
      strcpy  (x_eshell, "/bin/dash");
      break;
   default  :
      strcpy  (x_eshell, "/sbin/nologin");
      break;
   }
   sprintf (t, " --shell %s ", x_eshell);
   strcat   (x_cmd, t);
   /*---(change password)----------------*/
   srand (time (NULL));
   x_rand = rand ();
   sprintf (t, " --password %-8.8x ", x_rand);
   strcat   (x_cmd, t);
   /*---(create)-------------------------*/
   sprintf  (t, " --uid %d  %s  >> /dev/null 2>&1", a_uid, a_name);
   strcat   (x_cmd, t);
   rc = system (x_cmd);
   --rce;  if (rc < 0)   return rce;
   /*---(lock account)-------------------*/
   snprintf (x_cmd, LEN_RECD, "passwd -l %s >> /dev/null 2>&1", a_name);
   rc = system (x_cmd);
   --rce;  if (rc < 0)   return rce;
   /*---(sync)---------------------------*/
   snprintf (t, LEN_HUND, "sync");
   rc = system (t);
   --rce;  if (rc < 0)   return rce;
   /*---(verify)-------------------------*/
   rc = yENV_user_data ('n', a_name, NULL, NULL, &x_ahome, &x_ashell);
   --rce;  if (rc <  0)                           return rce;
   --rce;  if (strcmp (x_ehome , x_ahome ) != 0)  return rce;
   --rce;  if (strcmp (x_eshell, x_ashell) != 0)  return rce;
   /*---(complete)-----------------------*/
   return 0; 
}

char
yENV_user_del           (char a_name [LEN_USER])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        t           [LEN_HUND]  = "";
   int         u           =   -1;
   /*---(defense)------------------------*/
   --rce;  if (a_name == NULL)                     return rce;
   --rce;  if (strncmp (a_name, "USR_", 4) != 0)   return rce;
   /*---(check for group)----------------*/
   rc = yENV_user_data ('n', a_name, &u, NULL, NULL, NULL);
   --rce;  if (rc < 0)                             return 1;
   --rce;  if (u < 9000 || u > 9999)               return rce;
   /*---(delete)-------------------------*/
   snprintf (t, LEN_HUND, "userdel --remove %s >> /dev/null 2>&1", a_name);
   rc = system (t);
   --rce;  if (rc < 0)   return rce;
   /*---(sync)---------------------------*/
   snprintf (t, LEN_HUND, "sync");
   rc = system (t);
   --rce;  if (rc < 0)   return rce;
   /*---(verify)-------------------------*/
   rc = yENV_user_data ('n', a_name, NULL, NULL, NULL, NULL);
   --rce;  if (rc >= 0)  return rce;
   /*---(complete)-----------------------*/
   return 0; 
}

char
yENV_user_purge         (void)
{
   char        rc          =    0;
   int         i           =    0;
   char        c           =    0;
   char        x_name      [LEN_USER] = "";
   for (i = 9000; i <= 9999; ++i) {
      rc = yENV_user_data ('i', x_name, &i, NULL, NULL, NULL);
      if (rc >= 0 && strncmp (x_name, "USR_", 4) == 0) {
         rc = yENV_user_del (x_name);
         if (rc >= 0)  ++c;
      }
   }
   return c;
}

char
yENV_user_switch        (char a_name [LEN_USER])
{
   char        rce         =  -10;
   char        rc          =    0;
   int         x_uid       =   -1;
   rc = yENV_user_full (YENV_REG, a_name, NULL, &x_uid, NULL, NULL, NULL, NULL);
   /*> printf ("switching to %s (%d)\n", a_name, x_uid);                              <*/
   --rce;  if (x_uid < 0)  return rce;
   rc = seteuid (x_uid);
   /*> printf ("... uid %d, euid %d\n", getuid (), geteuid ());                       <*/
   --rce;  if (rc    < 0)  return rce;
   return 0;
}




/*====================------------------------------------====================*/
/*===----                         main driver                          ----===*/
/*====================------------------------------------====================*/
static void      o___DRIVER_____________o (void) {;}

char 
yENV_user_full          (char a_type, char a_text [LEN_USER], char r_name [LEN_USER], int *r_uid, int *r_gid, char r_dir [LEN_HUND], char r_shell [LEN_HUND], char r_handle [LEN_LABEL])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_name      [LEN_USER]  = "";
   int         x_uid       =   -1;
   int         x_gid       =   -1;
   char        x_dir       [LEN_HUND]  = "";
   char        x_shell     [LEN_HUND]  = "";
   /*---(header)-------------------------*/
   DEBUG_YENV    yLOG_senter  (__FUNCTION__);
   /*---(defaults)-----------------------*/
   if (r_name   != NULL)  strcpy (r_name  , "");
   if (r_uid    != NULL)  *r_uid   = -1;
   if (r_gid    != NULL)  *r_gid   = -1;
   if (r_dir    != NULL)  strcpy (r_dir   , "");
   if (r_shell  != NULL)  strcpy (r_shell , "");
   if (r_handle != NULL)  strcpy (r_handle, "");
   /*---(defense)------------------------*/
   DEBUG_YENV    yLOG_schar   (a_type);
   --rce;  if (a_type == 0 || strchr (YENV_REAL, a_type) == NULL) {
      DEBUG_YENV    yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
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
   strlcpy (x_name, a_text, LEN_USER);
   rc = -1;
   x_uid = atoi (a_text);
   if (x_uid <= 0)                 x_uid = -1;
   if (strcmp (a_text, "0") == 0)  x_uid = 0;
   /*---(user by number)-----------------*/
   --rce;  if (x_uid >= 0) {
      DEBUG_YENV    yLOG_snote   ("handle by user uid");
      if (r_handle != NULL)  strlcpy (r_handle, "uid", LEN_LABEL);
      rc = yENV_user_data  ('i', x_name, &x_uid, &x_gid, x_dir, x_shell);
   }
   /*---(user by name)-------------------*/
   --rce;  if (x_uid < 0 && strcmp (a_text, "") != 0) {
      DEBUG_YENV    yLOG_snote   ("handle by user name");
      if (r_handle != NULL)  strlcpy (r_handle, "name", LEN_LABEL);
      rc = yENV_user_data  ('n', a_text, &x_uid, &x_gid, x_dir, x_shell);
   }
   /*---(user by current uid)------------*/
   --rce;  if (x_uid < 0 && strcmp (a_text, "") == 0) {
      DEBUG_YENV    yLOG_snote   ("handle by current user");
      if (r_handle != NULL)  strlcpy (r_handle, "current", LEN_LABEL);
      x_uid = geteuid ();
      rc = yENV_user_data  ('i', x_name, &x_uid, &x_gid, x_dir, x_shell);
   }
   /*---(handle trouble)-----------------*/
   DEBUG_YENV    yLOG_sint    (rc);
   if (rc < 0) {
      DEBUG_YENV    yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YENV    yLOG_sint    (x_uid);
   /*---(save-back)----------------------*/
   if (r_name   != NULL)  strlcpy (r_name , x_name , LEN_USER);
   if (r_uid    != NULL)  *r_uid   = x_uid;
   if (r_gid    != NULL)  *r_gid   = x_gid;
   if (r_dir    != NULL)  strlcpy (r_dir  , x_dir  , LEN_HUND);
   if (r_shell  != NULL)  strlcpy (r_shell, x_shell, LEN_HUND);
   /*---(complete)-----------------------*/
   DEBUG_YENV    yLOG_sexit   (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                          simplifiers                         ----===*/
/*====================------------------------------------====================*/
static void      o___SIMPLE_____________o (void) {;}

char
yENV_user               (char a_text [LEN_USER], char r_name [LEN_USER], int *r_uid)
{
   return yENV_user_full (YENV_REG, a_text, r_name, r_uid, NULL, NULL, NULL, NULL);
}

char
yENV_user_uid           (char a_type, int a_value, char r_name [LEN_USER], int *r_uid)
{
   char        x_text      [LEN_TERSE] = "";
   snprintf (x_text, LEN_TERSE, "%d", a_value);
   return yENV_user_full (a_type, x_text, r_name, r_uid, NULL, NULL, NULL, NULL);
}

/*> int                                                                               <* 
 *> yenv_user               (char a_type, char a_name [LEN_USER])                     <* 
 *> {                                                                                 <* 
 *>    /+---(locals)-----------+-----+-----+-+/                                       <* 
 *>    char        rce         =  -10;                                                <* 
 *>    char        rc          =    0;                                                <* 
 *>    char        x_user      [LEN_USER]  = "";                                      <* 
 *>    int         x_uid       =   -1;                                                <* 
 *>    /+---(header)-------------------------+/                                       <* 
 *>    DEBUG_YENV    yLOG_senter  (__FUNCTION__);                                     <* 
 *>    /+---(defense)------------------------+/                                       <* 
 *>    DEBUG_YENV    yLOG_schar   (a_type);                                           <* 
 *>    --rce;  if (a_type == 0 || strchr (YENV_REAL, a_type) == NULL) {               <* 
 *>       DEBUG_YENV    yLOG_sexitr  (__FUNCTION__, rce);                             <* 
 *>       return rce;                                                                 <* 
 *>    }                                                                              <* 
 *>    /+---(quick-out)----------------------+/                                       <* 
 *>    if (a_type == YENV_NONE) {                                                     <* 
 *>       DEBUG_YENV    yLOG_snote   ("nothing to be done");                          <* 
 *>       DEBUG_YENV    yLOG_sexit   (__FUNCTION__);                                  <* 
 *>       return 0;                                                                   <* 
 *>    }                                                                              <* 
 *>    if (a_type == YENV_SYM) {                                                      <* 
 *>       DEBUG_YENV    yLOG_snote   ("nothing to be done");                          <* 
 *>       DEBUG_YENV    yLOG_sexit   (__FUNCTION__);                                  <* 
 *>       return 0;                                                                   <* 
 *>    }                                                                              <* 
 *>    /+---(defense)------------------------+/                                       <* 
 *>    DEBUG_YENV    yLOG_point   ("b_name"    , a_name);                             <* 
 *>    --rce;  if (a_type != YENV_SYM && a_name == NULL) {                            <* 
 *>       DEBUG_YENV    yLOG_exitr   (__FUNCTION__, rce);                             <* 
 *>       return rce;                                                                 <* 
 *>    }                                                                              <* 
 *>    DEBUG_YENV    yLOG_info    ("b_name"    , a_name);                             <* 
 *>    /+---(user by number)-----------------+/                                       <* 
 *>    --rce;  if (strcmp (a_name, "0") == 0 || atoi (a_name) > 0) {                  <* 
 *>       DEBUG_YENV    yLOG_snote   ("handle by user uid");                          <* 
 *>       x_uid = atoi (a_name);                                                      <* 
 *>       rc = yENV_user_data  ('i', x_user, &x_uid, NULL, NULL, NULL);               <* 
 *>    }                                                                              <* 
 *>    /+---(user by name)-------------------+/                                       <* 
 *>    else if (strcmp (a_name, "") != 0) {                                           <* 
 *>       DEBUG_YENV    yLOG_snote   ("handle by user name");                         <* 
 *>       rc = yENV_user_data  ('n', a_name, &x_uid, NULL, NULL, NULL);               <* 
 *>    }                                                                              <* 
 *>    /+---(user by current uid)------------+/                                       <* 
 *>    else {                                                                         <* 
 *>       DEBUG_YENV    yLOG_snote   ("handle by current user");                      <* 
 *>       x_uid = geteuid ();                                                         <* 
 *>       rc = yENV_user_data  ('i', x_user, &x_uid, NULL, NULL, NULL);               <* 
 *>    }                                                                              <* 
 *>    /+---(handle trouble)-----------------+/                                       <* 
 *>    DEBUG_YENV    yLOG_sint    (rc);                                               <* 
 *>    if (rc < 0) {                                                                  <* 
 *>       DEBUG_YENV    yLOG_exitr   (__FUNCTION__, rce);                             <* 
 *>       return rce;                                                                 <* 
 *>    }                                                                              <* 
 *>    DEBUG_YENV    yLOG_sint    (x_uid);                                            <* 
 *>    /+---(complete)-----------------------+/                                       <* 
 *>    DEBUG_YENV    yLOG_sexit   (__FUNCTION__);                                     <* 
 *>    return x_uid;                                                                  <* 
 *> }                                                                                 <*/

int
yenv_user_check        (char a_name [LEN_PATH])
{
   /*---(locals)-----------+-----+-----+-*/
   /*> char        rc          =    0;                                                <* 
    *> tSTAT       s;                                                                 <* 
    *> rc = lstat (a_name, &s);                                                       <* 
    *> if (rc < 0)   return YENV_NONE;                                                <* 
    *> return s.st_uid;                                                               <*/
}

char
yENV_user_update       (char a_name [LEN_PATH])
{
}


