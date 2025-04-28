/*===[[ START ]]==============================================================*/
#include    "yENV.h"
#include    "yENV_priv.h"



static  int zENV_ngroup  =   -1;
static  int zENV_cgroup  =   -1;



/*====================------------------------------------====================*/
/*===----                          main driver                         ----===*/
/*====================------------------------------------====================*/
static void      o___DRIVER_____________o (void) {;}

char
yENV_group_data         (char a_type, char b_name [LEN_USER], int *b_gid, char *r_quality, char *r_active, char *r_nuser, char r_unames [LEN_HUND], char r_uids [LEN_HUND])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   tGROUP     *x_group     = NULL;
   /*---(default)------------------------*/
   if (b_name  != NULL && a_type != 'n')    strcpy (b_name, "");
   if (b_gid   != NULL && a_type != 'i')    *b_gid     = -1;
   if (r_quality != NULL)                   *r_quality = '-';
   if (r_active  != NULL)                   *r_active  = '-';
   if (r_nuser   != NULL)                   *r_nuser   =  -1;
   if (r_unames  != NULL)                   strcpy (r_unames, "");
   if (r_uids    != NULL)                   strcpy (r_uids , "");
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
   /*---(fill in data)-------------------*/
   if (r_quality != NULL)  *r_quality = yenv_user_quality  (x_group->gr_name);
   if (r_active  != NULL)  *r_active  = yenv_user_active   (x_group->gr_passwd);
   if (r_nuser   != NULL)  *r_nuser   = yenv_group_users   (x_group->gr_name, r_unames, r_uids);
   /*---(complete)-----------------------*/
   return 0;
}

char
yENV_group_full         (char a_type, char a_text [LEN_USER], char r_name [LEN_USER], int *r_gid, char r_handle [LEN_LABEL], char *r_quality, char *r_active, char *r_nuser, char r_unames [LEN_HUND], char r_uids [LEN_HUND])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_group     [LEN_USER]  = "";
   int         x_gid       =   -1;
   /*---(header)-------------------------*/
   DEBUG_YENV    yLOG_senter  (__FUNCTION__);
   /*---(defaults)-----------------------*/
   if (r_name    != NULL)  strcpy (r_name  , "");
   if (r_gid     != NULL)  *r_gid   = -1;
   if (r_handle  != NULL)  strcpy (r_handle, "");
   if (r_quality != NULL)  *r_quality = '-';
   if (r_active  != NULL)  *r_active  = '-';
   if (r_nuser   != NULL)  *r_nuser   =  -1;
   if (r_unames  != NULL)  strcpy (r_unames, "");
   if (r_uids    != NULL)  strcpy (r_uids , "");
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
   strlcpy (x_group, a_text, LEN_USER);
   rc = -1;
   x_gid = atoi (a_text);
   if (x_gid <= 0)                 x_gid = -1;
   if (strcmp (a_text, "0") == 0)  x_gid = 0;
   /*---(group by gid)-------------------*/
   --rce;  if (x_gid >= 0) {
      DEBUG_YENV    yLOG_snote   ("handle by group uid");
      if (r_handle != NULL)  strlcpy (r_handle, "gid", LEN_LABEL);
      rc = yENV_group_data ('i', x_group, &x_gid, r_quality, r_active, r_nuser, r_unames, r_uids);
   }
   /*---(group by current gid)-----------*/
   --rce;  if (x_gid < 0 && strcmp (a_text, "@") == 0) {
      DEBUG_YENV    yLOG_snote   ("handle using current group");
      if (r_handle != NULL)  strlcpy (r_handle, "default", LEN_LABEL);
      x_gid = getgid ();
      rc = yENV_group_data ('i', x_group, &x_gid, r_quality, r_active, r_nuser, r_unames, r_uids);
   }
   /*---(group by name)------------------*/
   --rce;  if (x_gid < 0 && strcmp (a_text, "") != 0) {
      DEBUG_YENV    yLOG_snote   ("handle by group name");
      if (r_handle != NULL)  strlcpy (r_handle, "name", LEN_LABEL);
      rc = yENV_group_data ('n', x_group, &x_gid, r_quality, r_active, r_nuser, r_unames, r_uids);
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
   return RC_POSITIVE;
}



/*====================------------------------------------====================*/
/*===----                          simplifiers                         ----===*/
/*====================------------------------------------====================*/
static void      o___SIMPLE_____________o (void) {;}

char
yENV_group              (char a_text [LEN_USER], char r_name [LEN_USER], int *r_gid)
{
   return yENV_group_full (YENV_REG, a_text, r_name, r_gid, NULL, NULL, NULL, NULL, NULL, NULL);
}

char
yENV_group_gid          (char a_type, int a_value, char r_name [LEN_USER], int *r_gid)
{
   char        x_text      [LEN_TERSE] = "";
   snprintf (x_text, LEN_TERSE, "%d", a_value);
   return yENV_group_full (a_type, x_text, r_name, r_gid, NULL, NULL, NULL, NULL, NULL, NULL);
}

char
yenv_groups__by_user    (char a_recd [LEN_RECD], char a_user [LEN_LABEL], char r_names [LEN_HUND], char r_gids [LEN_HUND])
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_recd      [LEN_RECD]  = "";
   char       *p           = NULL;
   char       *q           = ":,";
   char       *r           = NULL;
   int         x_gid       =    0;
   int         x_uid       =    0;
   char        t           [LEN_LABEL] = "";
   char        c           =    0;
   char        x_group     [LEN_LABEL] = "";
   char        x_names     [LEN_HUND]  = "";
   char        x_gids      [LEN_HUND]  = "";
   /*---(default)------------------------*/
   if (r_names   != NULL)   strlcpy (x_names, r_names, LEN_HUND);
   if (r_gids    != NULL)   strlcpy (x_gids , r_gids , LEN_HUND);
   /*---(defense)---------------------*/
   --rce;  if (a_recd  == NULL)  return rce;
   --rce;  if (a_user  == NULL)  return rce;
   /*---(prepare)------------------------*/
   strlcpy (x_recd, a_recd, LEN_RECD);
   /*---(group name)---------------------*/
   p  = strtok_r (x_recd   , q, &r);
   --rce;  if (p == NULL)                  return rce;
   strlcpy (x_group, p, LEN_LABEL);
   /*---(password)-----------------------*/
   p  = strtok_r (NULL, q, &r);
   --rce;  if (p == NULL)                  return rce;
   /*---(gid)----------------------------*/
   p  = strtok_r (NULL, q, &r);
   --rce;  if (p == NULL)                  return rce;
   x_gid = atoi (p);
   /*---(walk-list)----------------------*/
   p  = strtok_r (NULL, q, &r);
   while (p != NULL) {
      /*---(filter)----------------------*/
      --rce;  if (strcmp (a_user , p) != 0) {
         p  = strtok_r (NULL, q, &r);
         continue;
      }
      /*---(name list)-------------------*/
      strlcat (x_names, x_group, LEN_HUND);
      strlcat (x_names, ","    , LEN_HUND);
      /*---(gid list)--------------------*/
      sprintf (t, "%d", x_gid);
      strlcat (x_gids , t      , LEN_HUND);
      strlcat (x_gids , ","    , LEN_HUND);
      /*---(increment)-------------------*/
      ++c;
      break;
      /*---(done)------------------------*/
   }
   /*---(save-back)----------------------*/
   if (r_names  != NULL)  strlcpy (r_names, x_names, LEN_HUND);
   if (r_gids   != NULL)  strlcpy (r_gids , x_gids , LEN_HUND);
   /*---(complete)-----------------------*/
   return c;
}

char
yenv_group_by_user      (char a_user [LEN_USER], char r_names [LEN_HUND], char r_gids [LEN_HUND])
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;
   FILE       *f           = NULL;
   char        x_recd      [LEN_RECD]  = "";
   char        l           =    0;
   char        n           =    0;
   char        c           =    0;
   char       *p           = NULL;
   char       *q           = ":,";
   char       *r           = NULL;
   char        x_group     [LEN_USER]  = "";
   int         x_gid       =    0;
   char        t           [LEN_LABEL] = "";
   char        x_names     [LEN_HUND]  = ",";
   char        x_gids      [LEN_HUND]  = ",";
   /*---(header)-------------------------*/
   DEBUG_YENV    yLOG_enter   (__FUNCTION__);
   /*---(default)------------------------*/
   if (r_names   != NULL)   strcpy (r_names, "");
   if (r_gids    != NULL)   strcpy (r_gids , "");
   /*---(defense)------------------------*/
   DEBUG_YENV    yLOG_point   ("a_user"    , a_user);
   --rce;  if (a_user     == NULL) {
      return rce;
   }
   DEBUG_YENV    yLOG_info    ("a_user"    , a_user);
   --rce;  if (a_user [0] == '\0') {
      return rce;
   }
   /*---(open)---------------------------*/
   f = fopen ("/etc/group", "r");
   DEBUG_YENV    yLOG_point   ("f"         , f);
   --rce;  if (f == NULL) {
      return rce;
   }
   /*---(walk entries)-------------------*/
   while (1) {
      /*---(read)------------------------*/
      fgets(x_recd, LEN_RECD, f);
      if (feof (f)) break;
      /*---(filter)----------------------*/
      if (x_recd [0] == '#' )  continue;
      if (x_recd [0] == '\0')  continue;
      /*---(fix)-------------------------*/
      l = strlen (x_recd);
      if (l > 0 && x_recd [l - 1] == '\n')  x_recd [--l] = '\0';
      DEBUG_YENV    yLOG_complex ("looking"   , "%3d å%sæ", n, x_recd);
      /*---(look for user)---------------*/
      p  = strtok_r (x_recd   , q, &r);
      if (p == NULL) continue;
      strlcpy (x_group, p, LEN_USER);
      DEBUG_YENV    yLOG_info    ("x_group"   , x_group);
      /*---(password)--------------------*/
      p  = strtok_r (NULL, q, &r);
      if (p == NULL) continue;
      /*---(gid)-------------------------*/
      p  = strtok_r (NULL, q, &r);
      if (p == NULL) continue;
      x_gid = atoi (p);
      /*---(check list)------------------*/
      p  = strtok_r (NULL, q, &r);
      while (p != NULL) {
         DEBUG_YENV    yLOG_info    ("check"     , p);
         if (strcmp (p, a_user) != 0) {
            DEBUG_YENV    yLOG_note    ("not match");
            p  = strtok_r (NULL, q, &r);
            DEBUG_YENV    yLOG_point   ("p"         , p);
            continue;
         }
         DEBUG_YENV    yLOG_note    ("FOUND");
         /*---(name list)----------------*/
         if (strcmp (x_group, a_user) == 0)   strlcat (x_names, "(SELF)", LEN_HUND);
         else                                 strlcat (x_names, x_group , LEN_HUND);
         strlcat (x_names, ",", LEN_HUND);
         /*---(gid list)-----------------*/
         sprintf (t, "%d", x_gid);
         strlcat (x_gids , t  , LEN_HUND);
         strlcat (x_gids , ",", LEN_HUND);
         /*---(increment)----------------*/
         ++c;
         break;
         /*---(done)---------------------*/
      }
      /*---(done)------------------------*/
      ++n;
   }
   /*---(save-back)----------------------*/
   if (strcmp (x_names, ",") == 0)  strcpy (x_names, ".");
   DEBUG_YENV    yLOG_complex ("x_names"   , "%3d å%sæ", c, x_names);
   if (r_names  != NULL)  strlcpy (r_names, x_names, LEN_HUND);
   if (strcmp (x_gids , ",") == 0)  strcpy (x_gids , ".");
   DEBUG_YENV    yLOG_complex ("x_gids"    , "%3d å%sæ", c, x_gids );
   if (r_gids   != NULL)  strlcpy (r_gids , x_gids , LEN_HUND);
   /*---(complete)-----------------------*/
   DEBUG_YENV    yLOG_exit    (__FUNCTION__);
   return c;
}

char
yenv_group__users       (char a_recd [LEN_RECD], char a_group [LEN_LABEL], char r_names [LEN_HUND], char r_uids [LEN_HUND])
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_recd      [LEN_RECD]  = "";
   char       *p           = NULL;
   char       *q           = ":,";
   char       *r           = NULL;
   int         x_uid       =    0;
   char        t           [LEN_LABEL] = "";
   char        c           =    0;
   char        x_names     [LEN_HUND]  = ".";
   char        x_uids      [LEN_HUND]  = ".";
   /*---(default)------------------------*/
   if (r_names   != NULL)   strcpy (r_names, "");
   if (r_uids    != NULL)   strcpy (r_uids , "");
   /*---(defense)---------------------*/
   --rce;  if (a_recd  == NULL)  return rce;
   --rce;  if (a_group == NULL)  return rce;
   /*---(prepare)------------------------*/
   strlcpy (x_recd, a_recd, LEN_RECD);
   /*---(group name)---------------------*/
   p  = strtok_r (x_recd   , q, &r);
   --rce;  if (p == NULL)                  return rce;
   /*---(filter)-------------------------*/
   --rce;  if (strcmp (a_group, p) != 0)   return rce;
   /*---(password)-----------------------*/
   p  = strtok_r (NULL, q, &r);
   --rce;  if (p == NULL)                  return rce;
   /*---(gid)----------------------------*/
   p  = strtok_r (NULL, q, &r);
   --rce;  if (p == NULL)                  return rce;
   /*---(walk-list)----------------------*/
   p  = strtok_r (NULL, q, &r);
   strcpy (x_names, ",");
   strcpy (x_uids , ",");
   while (p != NULL) {
      rc = yENV_user_data ('n', p, &x_uid, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
      /*---(name list)-------------------*/
      if (rc < 0) sprintf (t, "<%s>", p);
      else        sprintf (t, "%s"  , p);
      strlcat (x_names, t  , LEN_HUND);
      strlcat (x_names, ",", LEN_HUND);
      /*---(gid list)--------------------*/
      if (rc < 0) sprintf (t, "<>");
      else        sprintf (t, "%d", x_uid);
      strlcat (x_uids , t  , LEN_HUND);
      strlcat (x_uids , ",", LEN_HUND);
      /*---(next)------------------------*/
      ++c;
      p  = strtok_r (NULL, q, &r);
      /*---(done)------------------------*/
   }
   /*---(save-back)----------------------*/
   if (strcmp (x_names, ",") == 0)  strcpy (x_names, ".");
   DEBUG_YENV    yLOG_complex ("x_names"   , "%3d å%sæ", c, x_names);
   if (r_names  != NULL)  strlcpy (r_names, x_names, LEN_HUND);
   if (strcmp (x_uids , ",") == 0)  strcpy (x_uids , ".");
   DEBUG_YENV    yLOG_complex ("x_uids"    , "%3d å%sæ", c, x_uids );
   if (r_uids   != NULL)  strlcpy (r_uids , x_uids , LEN_HUND);
   /*---(complete)-----------------------*/
   return c;
}

char
yenv_group__lister      (char a_type, char a_text  [LEN_USER], char r_names [LEN_HUND], char r_ids [LEN_HUND])
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;
   char        rc          =    0;
   FILE       *f           = NULL;
   char        x_recd      [LEN_RECD]  = "";
   char        l           =    0;
   char        n           =    0;
   char        c           =    0;
   char        x_done      =  '-';
   /*---(header)-------------------------*/
   DEBUG_YENV    yLOG_enter   (__FUNCTION__);
   /*---(default)------------------------*/
   if (r_names   != NULL)   strcpy (r_names, "");
   if (r_ids     != NULL)   strcpy (r_ids  , "");
   /*---(defense)------------------------*/
   DEBUG_YENV    yLOG_point   ("a_text"    , a_text);
   --rce;  if (a_text     == NULL) {
      return rce;
   }
   DEBUG_YENV    yLOG_info    ("a_text"    , a_text);
   --rce;  if (a_text [0] == '\0') {
      return rce;
   }
   /*---(default)------------------------*/
   if (r_names   != NULL)   strcpy (r_names, ",");
   if (r_ids     != NULL)   strcpy (r_ids  , ",");
   /*---(open)---------------------------*/
   f = fopen ("/etc/group", "r");
   DEBUG_YENV    yLOG_point   ("f"         , f);
   --rce;  if (f == NULL) {
      return rce;
   }
   /*---(walk entries)-------------------*/
   while (1) {
      /*---(read)------------------------*/
      fgets(x_recd, LEN_RECD, f);
      if (feof (f)) break;
      /*---(filter)----------------------*/
      if (x_recd [0] == '#' )  continue;
      if (x_recd [0] == '\0')  continue;
      /*---(fix)-------------------------*/
      l = strlen (x_recd);
      if (l > 0 && x_recd [l - 1] == '\n')  x_recd [--l] = '\0';
      DEBUG_YENV    yLOG_complex ("looking"   , "%3d å%sæ", n, x_recd);
      /*---(parse)-----------------------*/
      switch (a_type) {
      case 'u' :
         DEBUG_YENV    yLOG_note    ("calling yenv_group__users");
         c   = yenv_group__users     (x_recd, a_text, r_names, r_ids);
         DEBUG_YENV    yLOG_value   ("c"         , c);
         if (c >= 0)  x_done = 'y';
         break;
      case 'g' :
         DEBUG_YENV    yLOG_note    ("calling yenv_groups_by_user");
         c  += yenv_groups__by_user  (x_recd, a_text, r_names, r_ids);
         DEBUG_YENV    yLOG_value   ("c"         , c);
         break;
      }
      DEBUG_YENV    yLOG_char    ("x_done"    , x_done);
      /*---(increment)-------------------*/
      ++n;
      if (x_done == 'y')  break;
      /*---(done)------------------------*/
   }
   DEBUG_YENV    yLOG_value   ("c"         , c);
   DEBUG_YENV    yLOG_value   ("n"         , n);
   /*---(fix)----------------------------*/
   if (r_names  != NULL && strcmp (r_names, ",") == 0)  strcpy (r_names, ".");
   if (r_ids    != NULL && strcmp (r_ids  , ",") == 0)  strcpy (r_ids  , ".");
   /*---(open)---------------------------*/
   rc = fclose (f);
   /*---(complete)-----------------------*/
   DEBUG_YENV    yLOG_exit    (__FUNCTION__);
   return c;
}

char yenv_group_users     (char a_group [LEN_USER], char r_names [LEN_HUND], char r_uids [LEN_HUND])  { return yenv_group__lister ('u', a_group, r_names, r_uids); }
char yenv_groups_by_user  (char a_user  [LEN_USER], char r_names [LEN_HUND], char r_gids [LEN_HUND])  { return yenv_group__lister ('g', a_user , r_names, r_gids); }



/*====================------------------------------------====================*/
/*===----                      data accessors                          ----===*/
/*====================------------------------------------====================*/
static void      o___ACCESS_____________o (void) {;}

int
yENV_group_count        (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   FILE       *f           = NULL;
   int         c           =    0;
   char        t           [LEN_RECD]  = "";
   /*---(open)---------------------------*/
   f = fopen ("/etc/group", "rt");
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
   zENV_ngroup = c;
   /*---(complete)-----------------------*/
   return c;
}

char*
yenv_group_detail       (char a_group [LEN_USER])
{
   char        rc          =    0;
   int         x_gid       =    0;
   char        x_naming, x_active;
   char        x_ngroup    =    0;
   char        x_names     [LEN_HUND]  = "";
   char        x_uids      [LEN_HUND]  = "";
   strcpy (g_print, "");
   if (a_group  == NULL)    return "(user null)";
   rc = yENV_group_data ('n', a_group, &x_gid, &x_naming, &x_active, &x_ngroup, x_names, x_uids);
   if (rc < 0)             return "(missing)";
   sprintf (g_print, "%-12.12s  %c  %c  %5d  %2d  %-50.50s  %-20.20s  Ï", a_group, x_naming, x_active, x_gid, x_ngroup, x_names, x_uids);
   return g_print;
}

char*
yENV_group_by_cursor    (char a_dir)
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
   char        x_group     [LEN_USER]  = "";
   /*---(header)-------------------------*/
   DEBUG_YENV    yLOG_enter   (__FUNCTION__);
   /*---(prepare)------------------------*/
   if (zENV_ngroup <= 0)   yENV_group_count ();
   /*---(set target)---------------------*/
   c      = zENV_ngroup - 1;
   DEBUG_YENV    yLOG_value   ("c"         , c);
   x_curr = zENV_cgroup;
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
   zENV_cgroup = x_curr;
   /*---(open)---------------------------*/
   f = fopen ("/etc/group", "rt");
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
      strlcpy (x_group, p, LEN_USER);
      DEBUG_YENV    yLOG_info    ("x_group"   , x_group);
      break;
      /*---(done)------------------------*/
   }
   /*---(close)--------------------------*/
   fclose (f);
   /*---(complete)-----------------------*/
   DEBUG_YENV    yLOG_exit    (__FUNCTION__);
   return yenv_group_detail (x_group);
}

char*
yENV_group_by_text      (char a_text [LEN_USER])
{
   int         rc          =   -1;
   char        x_group     [LEN_USER]  = "";
   if (a_text     == NULL)  return "(null)";
   if (a_text [0] == '\0')  return "(empty)";
   rc = yENV_group (a_text, x_group, NULL);
   if (rc < 0)  return "(n/a)";
   /*---(complete)-----------------------*/
   return yenv_group_detail (x_group);
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
   rc = yENV_group_data ('n', a_name, &g, NULL, NULL, NULL, NULL, NULL);
   --rce;  if (rc >= 0 && g >= 0) {
      if (g == a_gid)                              return 1;
      else                                         return rce;
   }
   rc = yENV_group_data ('i', x_name, &a_gid, NULL, NULL, NULL, NULL, NULL);
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
   rc = yENV_group_data ('n', a_name, NULL, NULL, NULL, NULL, NULL, NULL);
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
   rc = yENV_group_data ('n', a_name, &g, NULL, NULL, NULL, NULL, NULL);
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
   rc = yENV_group_data ('n', a_name, NULL, NULL, NULL, NULL, NULL, NULL);
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
      rc = yENV_group_data ('i', x_name, &i, NULL, NULL, NULL, NULL, NULL);
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
   rc = yENV_group_full (YENV_REG, a_text, NULL, &x_gid, NULL, NULL, NULL, NULL, NULL, NULL);
   --rce;  if (x_gid < 0)  return rce;
   rc = setegid (x_gid);
   --rce;  if (rc    < 0)  return rce;
   return 0;
}


