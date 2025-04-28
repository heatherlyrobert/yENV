/*===[[ START ]]==============================================================*/
#include    "yENV.h"
#include    "yENV_priv.h"



static  int zENV_nuser   =   -1;
static  int zENV_cuser   =   -1;



/*====================------------------------------------====================*/
/*===----                         foundation                           ----===*/
/*====================------------------------------------====================*/
static void      o___BASE_______________o (void) {;}

char
yenv_user_quality       (char a_user [LEN_HUND])
{
   int         l           =    0;
   int         i           =    0;
   if (a_user     == NULL)  return YENV_WTF;
   if (a_user [0] == '\0')  return YENV_WTF;
   l = strlen (a_user);
   if (l < 3)           return YENV_TOOSHORT;
   if (l >= LEN_USER)   return YENV_TOOLONG;
   for (i = 0; i < l; ++i) {
      if (strchr (YSTR_ALNUM, a_user [i]) == NULL)  return YENV_BADCHAR;
   }
   return YENV_QUALITY;
}

char
yenv_user_login         (char a_shell [LEN_HUND])
{
   char        x_login     = YENV_WTF;
   if (a_shell     == NULL)  return YENV_WTF;
   if (a_shell [0] == '\0')  return YENV_WTF;
   if      (strcmp (a_shell, "/bin/sh"       ) == 0)   x_login = YENV_LOGIN;
   else if (strcmp (a_shell, "/bin/bash"     ) == 0)   x_login = YENV_LOGIN;
   else if (strcmp (a_shell, "/bin/dash"     ) == 0)   x_login = YENV_LOGIN;
   else if (strcmp (a_shell, "/bin/csh"      ) == 0)   x_login = YENV_LOGIN;
   else if (strcmp (a_shell, "/bin/tcsh"     ) == 0)   x_login = YENV_LOGIN;
   else if (strcmp (a_shell, "/bin/zsh"      ) == 0)   x_login = YENV_LOGIN;
   else if (strcmp (a_shell, "/dev/null"     ) == 0)   x_login = YENV_NOLOGIN;
   else if (strcmp (a_shell, "/bin/false"    ) == 0)   x_login = YENV_NOLOGIN;
   else if (strcmp (a_shell, "/sbin/nologin" ) == 0)   x_login = YENV_NOLOGIN;
   else                                                x_login = YENV_WTF;
   return x_login;
}

char
yenv_user_active        (char a_pass [LEN_LABEL])
{
   char        x_active    = YENV_WTF;
   if (a_pass     == NULL)  return YENV_WTF;
   if      (a_pass [0] == '*' )   x_active = YENV_UNSET;
   else if (a_pass [0] == '!' )   x_active = YENV_LOCKED;
   else if (a_pass [0] == 'x' )   x_active = YENV_ACTIVE;
   else if (a_pass [0] == '\0')   x_active = YENV_NOPASS;
   else                           x_active = YENV_LOCAL;
   return x_active;
}



/*====================------------------------------------====================*/
/*===----                         main driver                          ----===*/
/*====================------------------------------------====================*/
static void      o___DRIVER_____________o (void) {;}

char
yENV_user_data          (char a_type, char b_name [LEN_USER], int *b_uid, int *r_gid, char r_home [LEN_HUND], char r_shell [LEN_HUND], char *r_quality, char *r_active, char *r_login, char *r_ngroup, char r_gnames [LEN_HUND], char r_gids [LEN_HUND])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   tPASSWD    *x_user      = NULL;
   /*---(default)------------------------*/
   if (b_name    != NULL && a_type != 'n')  strcpy (b_name, "");
   if (b_uid     != NULL && a_type != 'i')  *b_uid     = -1;
   if (r_gid     != NULL)  *r_gid     = -1;
   if (r_home    != NULL)  strcpy (r_home , "");
   if (r_shell   != NULL)  strcpy (r_shell, "");
   if (r_quality != NULL)  *r_quality = '-';
   if (r_login   != NULL)  *r_login   = '-';
   if (r_active  != NULL)  *r_active  = '-';
   if (r_ngroup  != NULL)  *r_ngroup  =   0;
   if (r_gnames  != NULL)  strcpy (r_gnames, "");
   if (r_gids    != NULL)  strcpy (r_gids , "");
   /*---(defense)------------------------*/
   --rce;  if (a_type == '\0' || strchr ("ni", a_type) == NULL)                return rce;
   --rce;  if (a_type == 'n' && (b_name == NULL || strcmp (b_name, "") == 0))  return rce;
   --rce;  if (a_type == 'i' && (b_uid  == NULL || *b_uid < 0))                return rce;
   /*---(get user record)----------------*/
   if (a_type == 'n')    x_user = getpwnam (b_name);
   else                  x_user = getpwuid (*b_uid);
   --rce;  if (x_user == NULL)                                                return rce;
   /*---(save back)----------------------*/
   if (a_type == 'i' && b_name  != NULL)   strlcpy (b_name , x_user->pw_name , LEN_USER);
   if (a_type == 'n' && b_uid   != NULL)   *b_uid    = x_user->pw_uid;
   if (r_gid     != NULL)                   *r_gid    = x_user->pw_gid;
   if (r_home    != NULL)                   strlcpy (r_home , x_user->pw_dir  , LEN_HUND);
   if (r_shell   != NULL)                   strlcpy (r_shell, x_user->pw_shell, LEN_HUND);
   /*---(fill in data)-------------------*/
   if (r_quality != NULL)  *r_quality = yenv_user_quality  (x_user->pw_name);
   if (r_login   != NULL)  *r_login   = yenv_user_login    (x_user->pw_shell);
   if (r_active  != NULL)  *r_active  = yenv_user_active   (x_user->pw_passwd);
   if (r_ngroup  != NULL)  *r_ngroup  = yenv_group_by_user (x_user->pw_name, r_gnames, r_gids);
   /*---(complete)-----------------------*/
   return 0;
}

char 
yENV_user_full          (char a_type, char a_text [LEN_USER], char r_name [LEN_USER], int *r_uid, int *r_gid, char r_home [LEN_HUND], char r_shell [LEN_HUND], char r_handle [LEN_LABEL], char *r_quality, char *r_active, char *r_login, char *r_ngroup, char r_gnames [LEN_HUND], char r_gids [LEN_HUND])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_name      [LEN_USER]  = "";
   int         x_uid       =   -1;
   int         x_gid       =   -1;
   char        x_home      [LEN_HUND]  = "";
   char        x_shell     [LEN_HUND]  = "";
   /*---(header)-------------------------*/
   DEBUG_YENV    yLOG_senter  (__FUNCTION__);
   /*---(defaults)-----------------------*/
   if (r_name    != NULL)  strcpy (r_name  , "");
   if (r_uid     != NULL)  *r_uid     = -1;
   if (r_gid     != NULL)  *r_gid     = -1;
   if (r_home    != NULL)  strcpy (r_home  , "");
   if (r_shell   != NULL)  strcpy (r_shell , "");
   if (r_handle  != NULL)  strcpy (r_handle, "");
   if (r_quality != NULL)  *r_quality = '-';
   if (r_login   != NULL)  *r_login   = '-';
   if (r_active  != NULL)  *r_active  = '-';
   if (r_ngroup  != NULL)  *r_ngroup  =   0;
   if (r_gnames  != NULL)  strcpy (r_gnames, "");
   if (r_gids    != NULL)  strcpy (r_gids , "");
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
   strlcpy (x_name, a_text, LEN_USER);
   rc = -1;
   x_uid = atoi (a_text);
   if (x_uid <= 0)                 x_uid = -1;
   if (strcmp (a_text, "0") == 0)  x_uid = 0;
   /*---(user by number)-----------------*/
   --rce;  if (x_uid >= 0) {
      DEBUG_YENV    yLOG_snote   ("handle by user uid");
      if (r_handle != NULL)  strlcpy (r_handle, "uid", LEN_LABEL);
      rc = yENV_user_data  ('i', x_name, &x_uid, &x_gid, x_home, x_shell, r_quality, r_login, r_active, r_ngroup, r_gnames, r_gids);
   }
   /*---(user by current uid)------------*/
   --rce;  if (x_uid < 0 && strcmp (a_text, "@") == 0) {
      DEBUG_YENV    yLOG_snote   ("handle using current user");
      if (r_handle != NULL)  strlcpy (r_handle, "default", LEN_LABEL);
      x_uid = geteuid ();
      rc = yENV_user_data  ('i', x_name, &x_uid, &x_gid, x_home, x_shell, r_quality, r_login, r_active, r_ngroup, r_gnames, r_gids);
   }
   /*---(user by name)-------------------*/
   --rce;  if (x_uid < 0 && strcmp (a_text, "") != 0) {
      DEBUG_YENV    yLOG_snote   ("handle by user name");
      if (r_handle != NULL)  strlcpy (r_handle, "name", LEN_LABEL);
      rc = yENV_user_data  ('n', a_text, &x_uid, &x_gid, x_home, x_shell, r_quality, r_login, r_active, r_ngroup, r_gnames, r_gids);
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
   if (r_home   != NULL)  strlcpy (r_home , x_home , LEN_HUND);
   if (r_shell  != NULL)  strlcpy (r_shell, x_shell, LEN_HUND);
   /*---(complete)-----------------------*/
   DEBUG_YENV    yLOG_sexit   (__FUNCTION__);
   return RC_POSITIVE;
}



/*====================------------------------------------====================*/
/*===----                          simplifiers                         ----===*/
/*====================------------------------------------====================*/
static void      o___SIMPLE_____________o (void) {;}

char
yENV_user               (char a_text [LEN_USER], char r_name [LEN_USER], int *r_uid)
{
   return yENV_user_full (YENV_REG, a_text, r_name, r_uid, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
}

char
yENV_user_uid           (char a_type, int a_value, char r_name [LEN_USER], int *r_uid)
{
   char        x_text      [LEN_TERSE] = "";
   snprintf (x_text, LEN_TERSE, "%d", a_value);
   return yENV_user_full (a_type, x_text, r_name, r_uid, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
}



/*====================------------------------------------====================*/
/*===----                      data accessors                          ----===*/
/*====================------------------------------------====================*/
static void      o___ACCESS_____________o (void) {;}

int
yENV_user_count         (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   FILE       *f           = NULL;
   int         c           =    0;
   char        t           [LEN_RECD]  = "";
   /*---(open)---------------------------*/
   f = fopen ("/etc/passwd", "rt");
   --rce;  if (f == NULL)  return rce;
   /*---(walk file)----------------------*/
   while (1) {
      fgets (t, LEN_RECD, f);
      if (feof (f))  break;
      ++c;
   }
   /*---(close)--------------------------*/
   fclose (f);
   /*---(save-back)----------------------*/
   zENV_nuser = c;
   /*---(complete)-----------------------*/
   return c;
}

char*
yenv_user_detail        (char a_user [LEN_USER])
{
   char        rc          =    0;
   int         x_uid, x_gid;
   char        x_home      [LEN_HUND]  = "";
   char        x_shell     [LEN_HUND]  = "";
   char        x_naming, x_login, x_active;
   char        x_groups    =    0;
   char        x_glist     [LEN_HUND]  = "";
   char        x_gids      [LEN_HUND]  = "";
   strcpy (g_print, "");
   if (a_user  == NULL)    return "(user null)";
   rc = yENV_user_data ('n', a_user, &x_uid, &x_gid, x_home, x_shell, &x_naming, &x_active, &x_login, &x_groups, x_glist, x_gids);
   if (rc < 0)             return "(missing)";
   sprintf (g_print, "%-12.12s  %c  %c  %c  %5d  %5d  %-30.30s  %-20.20s  %2d  %-60.60s  %-30.30s  Ï", a_user, x_naming, x_active, x_login, x_uid, x_gid, x_home, x_shell, x_groups, x_glist, x_gids);
   return g_print;
}

char*
yENV_user_by_cursor     (char a_dir)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         rc          =   -1;
   int         x_curr      =    0;
   FILE       *f           = NULL;
   char        t           [LEN_RECD]  = "";
   int         l           =    0;
   int         c           =    0;
   int         n           =    0;
   char       *p           = NULL;
   char       *r           = NULL;
   char        x_user      [LEN_USER]  = "";
   /*---(header)-------------------------*/
   DEBUG_YENV    yLOG_enter   (__FUNCTION__);
   /*---(prepare)------------------------*/
   if (zENV_nuser <= 0)   yENV_user_count ();
   /*---(set target)---------------------*/
   c      = zENV_nuser - 1;
   DEBUG_YENV    yLOG_value   ("c"         , c);
   x_curr = zENV_cuser;
   DEBUG_YENV    yLOG_value   ("x_curr"    , x_curr);
   DEBUG_YENV    yLOG_char    ("a_dir"     , a_dir);
   --rce;  switch (a_dir) {
   case YDLST_HEAD  : case YDLST_DHEAD :
      x_curr = 0;
      break;
   case YDLST_PREV  : case YDLST_DPREV :
      if (x_curr > 0)  --x_curr;
      else             return "(n/a)";
      break;
   case YDLST_CURR  : case YDLST_DCURR :
      break;
   case YDLST_NEXT  : case YDLST_DNEXT : case '·' :  /* · means default */
      if (x_curr < c)  ++x_curr;
      else             return "(n/a)";
      break;
   case YDLST_TAIL  : case YDLST_DTAIL :
      x_curr = c;
      break;
   default :
      DEBUG_YENV    yLOG_exitr   (__FUNCTION__, rce);
      return "(bad dir)";
      break;
   }
   /*---(save-back)----------------------*/
   zENV_cuser = x_curr;
   /*---(open)---------------------------*/
   f = fopen ("/etc/passwd", "rt");
   DEBUG_YENV    yLOG_point   ("f"         , f);
   --rce;  if (f == NULL) {
      DEBUG_YENV    yLOG_exitr   (__FUNCTION__, rce);
      return "(not open)";
   }
   /*---(walk file)----------------------*/
   while (1) {
      /*---(read)------------------------*/
      fgets (t, LEN_RECD, f);
      if (feof (f))  break;
      /*---(filter)----------------------*/
      if (t [0] == '#' )  continue;
      if (t [0] == '\0')  continue;
      /*---(fix)-------------------------*/
      l = strlen (t);
      if (l > 0 && t [l - 1] == '\n')  t [--l] = '\0';
      DEBUG_YENV    yLOG_complex ("looking"   , "%3d %3d å%sæ", x_curr, n, t);
      /*---(check)-----------------------*/
      if (n != x_curr) {
         ++n;
         continue;
      }
      /*---(found)-----------------------*/
      DEBUG_YENV    yLOG_note    ("FOUND");
      p = strtok_r (t, ":", &r);
      if (p == NULL)  return "(strtok)";
      strlcpy (x_user, p, LEN_USER);
      DEBUG_YENV    yLOG_info    ("x_user"    , x_user);
      break;
      /*---(done)------------------------*/
   }
   /*---(close)--------------------------*/
   fclose (f);
   /*---(complete)-----------------------*/
   DEBUG_YENV    yLOG_exit    (__FUNCTION__);
   return yenv_user_detail (x_user);
}

char*
yENV_user_by_text       (char a_text [LEN_USER])
{
   int         rc          =   -1;
   char        x_user      [LEN_USER]  = "";
   if (a_text     == NULL)  return "(null)";
   if (a_text [0] == '\0')  return "(empty)";
   rc = yENV_user  (a_text, x_user, NULL);
   if (rc < 0)  return "(n/a)";
   /*---(complete)-----------------------*/
   return yenv_user_detail (x_user);
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
   /*---(reset)--------------------------*/
   zENV_nuser = -1;
   /*---(defense)------------------------*/
   --rce;  if (a_name == NULL) return rce;
   --rce;  if (a_uid < 9000 || a_uid > 9999)       return rce;
   --rce;  if (strncmp (a_name, "USR_", 4) != 0)   return rce;
   /*---(check for existing)-------------*/
   rc = yENV_user_data ('n', a_name, &u, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
   --rce;  if (rc >= 0 && u >= 0) {
      if (u == a_uid)                              return 1;
      else                                         return rce;
   }
   rc = yENV_user_data ('i', x_name, &a_uid, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
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
   rc = yENV_user_data ('n', a_name, NULL, NULL, &x_ahome, &x_ashell, NULL, NULL, NULL, NULL, NULL, NULL);
   --rce;  if (rc <  0)                           return rce;
   --rce;  if (strcmp (x_ehome , x_ahome ) != 0)  return rce;
   --rce;  if (strcmp (x_eshell, x_ashell) != 0)  return rce;
   /*---(update count)-------------------*/
   yENV_user_count ();
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
   /*---(reset)--------------------------*/
   zENV_nuser = -1;
   /*---(defense)------------------------*/
   --rce;  if (a_name == NULL)                     return rce;
   --rce;  if (strncmp (a_name, "USR_", 4) != 0)   return rce;
   /*---(check for group)----------------*/
   rc = yENV_user_data ('n', a_name, &u, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
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
   rc = yENV_user_data ('n', a_name, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
   --rce;  if (rc >= 0)  return rce;
   /*---(update count)-------------------*/
   yENV_user_count ();
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
      rc = yENV_user_data ('i', x_name, &i, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
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
   rc = yENV_user_full (YENV_REG, a_name, NULL, &x_uid, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
   /*> printf ("switching to %s (%d)\n", a_name, x_uid);                              <*/
   --rce;  if (x_uid < 0)  return rce;
   rc = seteuid (x_uid);
   /*> printf ("... uid %d, euid %d\n", getuid (), geteuid ());                       <*/
   --rce;  if (rc    < 0)  return rce;
   return 0;
}


