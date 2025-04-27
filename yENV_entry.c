/*===[[ START ]]==============================================================*/
#include    "yENV.h"
#include    "yENV_priv.h"



/*====================------------------------------------====================*/
/*===----                      supporting functions                    ----===*/
/*====================------------------------------------====================*/
static void      o___SUPPORT____________o (void) {;}

char*
yENV_typedesc           (char a_type)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   /*---(header)-------------------------*/
   DEBUG_FILE   yLOG_senter  (__FUNCTION__);
   /*---(set type desc)------------------*/
   DEBUG_FILE   yLOG_schar   (a_type);
   switch (a_type) {
   case YENV_NONE   :  strlcpy (g_print, "non-exist" , LEN_TERSE);  break;
   case YENV_BLOCK  :  strlcpy (g_print, "block-dev" , LEN_TERSE);  break;
   case YENV_CHAR   :  strlcpy (g_print, "char-dev"  , LEN_TERSE);  break;
   case YENV_DIR    :  strlcpy (g_print, "directory" , LEN_TERSE);  break;
   case YENV_HARD   :  strlcpy (g_print, "hardlink"  , LEN_TERSE);  break;
   case YENV_IPSOC  :  strlcpy (g_print, "ip-socket" , LEN_TERSE);  break;
   case YENV_PIPE   :  strlcpy (g_print, "fifo-pipe" , LEN_TERSE);  break;
   case YENV_REG    :  strlcpy (g_print, "regular"   , LEN_TERSE);  break;
   case YENV_SYM    :  strlcpy (g_print, "symlink"   , LEN_TERSE);  break;
   default          :  strlcpy (g_print, "WTF"       , LEN_TERSE);  break;
   }
   DEBUG_FILE   yLOG_snote   (g_print);
   /*---(complete)-----------------------*/
   DEBUG_FILE   yLOG_sexit   (__FUNCTION__);
   return g_print;
}

char
yENV_exists             (char a_name [LEN_PATH])
{
   /*---(design notes)-------------------*/
   /*
    *  just a subset of the yENV_detail function, but allows extensive
    *  use in unit testing due simplicity and to speed increase
    *
    */
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_type      = YENV_NONE;
   tSTAT       s;
   /*---(header)-------------------------*/
   DEBUG_YENV    yLOG_senter  (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YENV    yLOG_spoint  (a_name);
   --rce;  if (a_name  == NULL) {
      DEBUG_YENV    yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YENV    yLOG_snote   (a_name);
   --rce;  if (strcmp (a_name, "") == 0) {
      DEBUG_YENV    yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(check existance)----------------*/
   rc = lstat (a_name, &s);
   DEBUG_YENV    yLOG_sint    (rc);
   --rce;  if (rc < 0) {
      DEBUG_YENV    yLOG_sexit   (__FUNCTION__);
      return YENV_NONE;
   }
   /*---(normal types)-------------------*/
   if      (S_ISBLK  (s.st_mode))   x_type = YENV_BLOCK;
   else if (S_ISCHR  (s.st_mode))   x_type = YENV_CHAR ;
   else if (S_ISDIR  (s.st_mode))   x_type = YENV_DIR  ;
   else if (S_ISREG  (s.st_mode))   x_type = YENV_REG  ;
   else if (S_ISSOCK (s.st_mode))   x_type = YENV_IPSOC;
   else if (S_ISFIFO (s.st_mode))   x_type = YENV_PIPE ;
   else if (S_ISLNK  (s.st_mode))   x_type = YENV_SYM  ;
   else                             x_type = YENV_WTF  ;
   /*---(check hard link)----------------*/
   DEBUG_YENV    yLOG_sint    (s.st_nlink);
   if (x_type == YENV_REG   && s.st_nlink > 1) x_type = YENV_HARD ;
   DEBUG_YENV    yLOG_schar   (x_type);
   /*---(complete)-----------------------*/
   DEBUG_YENV    yLOG_sexit   (__FUNCTION__);
   return x_type;
}



/*====================------------------------------------====================*/
/*===----                      creating files                          ----===*/
/*====================------------------------------------====================*/
static void      o___CREATE_____________o (void) {;}

char
yenv_creator            (char a_curr, char a_type, char a_name [LEN_PATH], int a_uid, int a_gid, int a_prm, int a_major, int a_minor, char a_link [LEN_PATH])
{
   /*---(design notes)-------------------*/
   /*
    *  kept creation and permission changes in one function
    *  with no sub-function calls, to limit potential window
    *  of inapproprite access exposure
    *
    */
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   FILE       *f           = NULL;
   /*---(defense)------------------------*/
   --rce;  if (a_curr == 0)                            return rce;
   --rce;  if (strchr (YENV_TYPES, a_curr) == NULL)    return rce;
   --rce;  if (a_type == 0)                            return rce;
   --rce;  if (strchr (YENV_REAL , a_type) == NULL)    return rce;
   --rce;  if (a_name == NULL || a_name [0] == '\0')   return rce;
   --rce;  if (a_type != YENV_SYM  ) {
      if (a_uid < 0 || a_uid > 65534)                  return rce;
      if (a_gid < 0 || a_gid > 65534)                  return rce;
      if (a_prm < 0 || a_prm > 04777)                  return rce;
   }
   --rce;  if (strchr ("bc", a_type) != NULL) {
      if (a_major < 0 || a_major > 255)                return rce;
      if (a_minor < 0 || a_minor > 255)                return rce;
   }
   --rce;  if (strchr ("sh", a_type) != NULL) {
      if (a_link == NULL || a_link [0] == '\0')        return rce;
   }
   /*---(create)-------------------------*/
   --rce;  if (a_curr == YENV_NONE) {
      --rce;  switch (a_type) {
      case YENV_BLOCK :
         rc = mknod   (a_name, S_IFBLK, makedev (a_major, a_minor));
         break;
      case YENV_CHAR  :
         rc = mknod   (a_name, S_IFCHR, makedev (a_major, a_minor));
         break;
      case YENV_DIR   : 
         rc = mkdir   (a_name, 00000);
         break;
      case YENV_REG   : 
         f  = fopen   (a_name, "wt");
         if (f == NULL)  return rce;
         fflush (f);
         fclose (f);
         f == NULL;
         break;
      case YENV_HARD  : 
         rc = link    (a_link, a_name);
         break;
      case YENV_SYM   : 
         rc = symlink (a_link, a_name);
         break;
      case YENV_IPSOC :
         break;
      case YENV_PIPE  :
         rc = mkfifo (a_name, 00000);
         break;
      }
   }
   --rce;  if (rc < 0)  return rce;
   /*---(ownership)----------------------*/
   --rce;  if (a_type != YENV_SYM) {
      rc = chown (a_name, a_uid, a_gid);
      if (rc < 0)            return rce;
   }
   /*---(permissions)--------------------*/
   --rce;  if (a_type != YENV_SYM) {
      rc = chmod (a_name, a_prm);
      if (rc < 0)            return rce;
   }
   /*---(complete)-----------------------*/
   return 0;
}

char
yENV_create             (char a_type, char a_name [LEN_PATH], int a_uid, int a_gid, int a_prm, int a_major, int a_minor, char a_link [LEN_PATH])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        x_curr      = YENV_NONE;
   /*---(check on file)------------------*/
   x_curr = yENV_exists (a_name);
   --rce;  if (x_curr < 0)            return rce;
   --rce;  if (x_curr != YENV_NONE)   return rce;
   /*---(create)-------------------------*/
   return yenv_creator (x_curr, a_type, a_name, a_uid, a_gid, a_prm, a_major, a_minor, a_link);
}

char
yENV_touchier           (char a_type, char a_name [LEN_PATH], char a_owner [LEN_USER], char a_group [LEN_USER], char a_perms [LEN_TERSE], int a_major, int a_minor, char a_link [LEN_PATH])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_curr      = YENV_NONE;
   int         x_uid       =   -1;
   int         x_gid       =   -1;
   int         x_prm       =   -1;
   int         i, l, x_euid, x_egid, x_eprm, x_emaj, x_emin;
   char        x_link      [LEN_PATH];
   /*---(header)-------------------------*/
   DEBUG_YENV    yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YENV    yLOG_complex ("a_type"    , "%c/%d", a_type, a_type);
   --rce;  if (a_type == 0 || strchr (YENV_REAL, a_type) == NULL) {
      DEBUG_YENV    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YENV    yLOG_point   ("a_name"    , a_name);
   --rce;  if (a_name == NULL || strcmp (a_name, "") == 0) {
      DEBUG_YENV    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YENV    yLOG_info    ("a_name"    , a_name);
   DEBUG_YENV    yLOG_point   ("a_owner"   , a_owner);
   --rce;  if (a_type != YENV_SYM && a_owner  == NULL) {
      DEBUG_YENV    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YENV    yLOG_info    ("a_owner"   , a_owner);
   DEBUG_YENV    yLOG_point   ("a_group"   , a_group);
   --rce;  if (a_type != YENV_SYM && a_group   == NULL) {
      DEBUG_YENV    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YENV    yLOG_info    ("a_group"   , a_group);
   /*---(check on file)------------------*/
   x_curr = yENV_exists (a_name);
   DEBUG_YENV    yLOG_char    ("x_curr"    , x_curr);
   --rce;  if (x_curr < 0) {
      DEBUG_YENV    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (x_curr > YENV_NONE && x_curr != a_type) {
      DEBUG_YENV    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(pre-work owner)-----------------*/
   --rce;  if (a_type != YENV_SYM) {
      rc = yENV_user_full  (a_type, a_owner, NULL, &x_uid, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
      DEBUG_YENV    yLOG_value   ("x_uid"     , x_uid);
      if (rc < 0 || x_uid < 0) {
         DEBUG_YENV    yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
   }
   /*---(pre-work group)-----------------*/
   --rce;  if (a_type != YENV_SYM) {
      rc = yENV_group_full (a_type, a_group, NULL, &x_gid, NULL);
      DEBUG_YENV    yLOG_value   ("x_gid"     , x_gid);
      if (rc < 0 || x_gid < 0) {
         DEBUG_YENV    yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
   }
   /*---(pre-work permissions)-----------*/
   --rce;  if (a_type != YENV_SYM) {
      rc = yENV_perms_full (a_type, a_perms, NULL, &x_prm, NULL, NULL, NULL);
      DEBUG_YENV    yLOG_value   ("x_prm"    , x_prm);
      if (rc < 0 || x_prm < 0) {
         DEBUG_YENV    yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
   }
   /*---(create, if needed)--------------*/
   rc = yenv_creator (x_curr, a_type, a_name, x_uid, x_gid, x_prm, a_major, a_minor, a_link);
   DEBUG_YENV    yLOG_value   ("creator"  , rc);
   --rce;  if (rc < 0) {
      DEBUG_YENV    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(verify)-------------------------*/
   x_curr = yENV_detail (a_name, NULL, &x_euid, NULL, &x_egid, NULL, &x_eprm, NULL, NULL, NULL, NULL, &x_emaj, &x_emin, x_link, NULL, NULL, NULL);
   --rce;  if (x_curr == YENV_NONE) {
      DEBUG_YENV    yLOG_exitr   (__FUNCTION__, rce);
      return YENV_NONE;
   }
   --rce;  if (x_curr <  0) {
      DEBUG_YENV    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (x_curr >  YENV_NONE && x_curr != a_type) {
      DEBUG_YENV    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (x_curr != YENV_SYM  ) {
      if (x_uid   != x_euid) {
         DEBUG_YENV    yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      if (x_gid   != x_egid) {
         DEBUG_YENV    yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      if (x_prm   != x_eprm) {
         DEBUG_YENV    yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
   }
   --rce;  if (strchr ("bc", x_curr) != NULL) {
      if (a_major != x_emaj) {
         DEBUG_YENV    yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      if (a_minor != x_emin) {
         DEBUG_YENV    yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
   }
   --rce;  if (x_curr == YENV_SYM  ) {
      if (strcmp (a_link, x_link) != 0) {
         DEBUG_YENV    yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
   }
   /*---(complete)-----------------------*/
   DEBUG_YENV    yLOG_exit    (__FUNCTION__);
   return x_curr;
}

char yENV_touch              (char a_name [LEN_PATH], char a_owner [LEN_USER], char a_group [LEN_USER], char a_perms [LEN_TERSE]) { return yENV_touchier (YENV_REG  , a_name, a_owner, a_group, a_perms, 0, 0, ""); }
char yENV_mkdir              (char a_name [LEN_PATH], char a_owner [LEN_USER], char a_group [LEN_USER], char a_perms [LEN_TERSE]) { return yENV_touchier (YENV_DIR  , a_name, a_owner, a_group, a_perms, 0, 0, ""); }



/*====================------------------------------------====================*/
/*===----                      destroying files                        ----===*/
/*====================------------------------------------====================*/
static void      o___DESTROY____________o (void) {;}

char
yENV_removier           (char a_type, char a_name [LEN_PATH])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_type      =  YENV_NONE;
   /*---(header)-------------------------*/
   DEBUG_YENV    yLOG_enter   (__FUNCTION__);
   DEBUG_YENV    yLOG_complex ("a_type"    , "%3d/%c", a_type, a_type);
   /*---(defense)------------------------*/
   DEBUG_YENV    yLOG_point   ("a_name"    , a_name);
   --rce;  if (a_name == NULL) {
      DEBUG_YENV    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YENV    yLOG_info    ("a_name"    , a_name);
   --rce;  if (strcmp (a_name, "") == 0) {
      DEBUG_YENV    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(check on file)------------------*/
   x_type = yENV_exists (a_name);
   DEBUG_YENV    yLOG_complex ("exists"    , "%d/%c", x_type, x_type);
   if (x_type == YENV_NONE) {
      DEBUG_YENV    yLOG_exit    (__FUNCTION__);
      return x_type;
   }
   --rce;  if (x_type < 0) {
      DEBUG_YENV    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*> --rce;  if (a_type != YENV_ANY && x_type != a_type)     return rce;            <*/
   /*---(create, if needed)--------------*/
   DEBUG_YENV    yLOG_char    ("a_type"    , a_type);
   --rce;  switch (a_type) {
   case YENV_DIR   : 
      DEBUG_YENV    yLOG_note    ("handle as directory");
      rc = rmdir   (a_name);
      break;
   default :
      DEBUG_YENV    yLOG_note    ("handle as non-directory");
      rc = unlink (a_name);
      break;
   }
   /*---(complete)-----------------------*/
   DEBUG_YENV    yLOG_exit    (__FUNCTION__);
   return yENV_exists (a_name);
}

char yENV_rm            (char a_name [LEN_PATH]) { yENV_removier (YENV_ANY  , a_name); }
char yENV_rmdir         (char a_name [LEN_PATH]) { yENV_removier (YENV_DIR  , a_name); }

char
yENV_rmdir_and_files    (char a_name [LEN_PATH])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_name      [LEN_DESC]  = "";
   int         l           =    0;
   char        x_cmd       [LEN_FULL]  = "";
   /*---(header)-------------------------*/
   DEBUG_YENV    yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YENV    yLOG_point   ("a_name"    , a_name);
   --rce;  if (a_name == NULL) {
      DEBUG_YENV    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YENV    yLOG_info    ("a_name"    , a_name);
   /*---(quick-out)----------------------*/
   --rce;  if (strncmp (a_name, "/tmp/", 5) != 0) {
      DEBUG_YENV    yLOG_note    ("can't mess around with or outside å/tmp/æ");
      DEBUG_YENV    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare)------------------------*/
   strlcpy (x_name, a_name, LEN_PATH);
   l = strlen (x_name);
   if (x_name [l - 1] != '/')  strlcat (x_name, "/", LEN_PATH);
   DEBUG_YENV    yLOG_info    ("x_name"    , x_name);
   /*---(remove files in dir)------------*/
   snprintf (x_cmd, LEN_FULL, "rm -f %s*.*  > /dev/null  2>&1", x_name);
   DEBUG_YENV    yLOG_info    ("x_cmd"     , x_cmd);
   rc = system (x_cmd);
   DEBUG_YENV    yLOG_value   ("rc"        , rc);
   /*---(remove directory)---------------*/
   rc = yENV_removier (YENV_DIR  , x_name);
   DEBUG_YENV    yLOG_value   ("rc"        , rc);
   /*---(complete)-----------------------*/
   DEBUG_YENV    yLOG_exit    (__FUNCTION__);
   return rc;
}



/*====================------------------------------------====================*/
/*===----                      examining files                         ----===*/
/*====================------------------------------------====================*/
static void      o___EXAMINE____________o (void) {;}

char
yENV_hash               (char a_type, char a_name [LEN_PATH], char r_hash [LEN_DESC])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   FILE       *f           = NULL;
   SHA_CTX     ctx;
   int         i           =    0;
   uchar       x_buf       [LEN_RECD]  = "";
   uchar       x_hash      [LEN_DESC]  = "";
   uchar       t           [LEN_SHORT] = "";
   int         x_bytes     = 0;
   int         x_total     = 0;
   /*---(header)-------------------------*/
   DEBUG_YENV    yLOG_senter  (__FUNCTION__);
   /*---(default)------------------------*/
   if (r_hash  != NULL)  strcpy (r_hash , "");
   /*---(quick-out)----------------------*/
   if (a_type != YENV_REG && a_type != YENV_HARD) {
      DEBUG_YENV    yLOG_snote   ("nothing to be done");
      DEBUG_YENV    yLOG_sexit   (__FUNCTION__);
      return 0;
   }
   /*---(defense)------------------------*/
   DEBUG_YENV    yLOG_spoint  (a_name);
   --rce;  if (a_name == NULL || a_name [0] == '\0') {
      DEBUG_YENV    yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YENV    yLOG_snote   (a_name);
   DEBUG_YENV    yLOG_spoint  (r_hash);
   --rce;  if (r_hash == NULL) {
      DEBUG_YENV    yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare)------------------------*/
   f = fopen (a_name, "rb");
   --rce;  if (f == NULL) {
      DEBUG_YENV    yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   rc = SHA1_Init (&ctx);
   --rce;  if (rc != 1) {
      DEBUG_YENV    yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(hash all)-----------------------*/
   --rce;  while (1) {
      x_bytes = fread (x_buf, 1, sizeof (x_buf), f);
      if (x_bytes <  0)  {
         fclose (f);
         DEBUG_YENV    yLOG_sexitr  (__FUNCTION__, rce);
         return rce;
      }
      x_total += x_bytes;
      if (x_bytes == 0)  break;
      rc = SHA1_Update (&ctx, x_buf, x_bytes);
      --rce;  if (rc != 1) {
         fclose (f);
         DEBUG_YENV    yLOG_sexitr  (__FUNCTION__, rce);
         return rce;
      }
   }
   /*---(finalize hash)------------------*/
   fclose (f);
   rc = SHA1_Final (x_hash, &ctx);
   /*> printf ("x_total = %d\n", x_total);                                         <*/
   --rce;  if (rc != 1) {
      DEBUG_YENV    yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   strcpy (r_hash, "");
   for (i = 0; i < 20; ++i) {
      sprintf (t, "%02x", x_hash [i]);
      strlcat (r_hash, t, LEN_DESC);
   }
   r_hash [40] = '\0';
   DEBUG_YENV    yLOG_snote   (r_hash);
   /*---(complete)-----------------------*/
   DEBUG_YENV    yLOG_sexit   (__FUNCTION__);
   return 1;
}

char 
yENV_detail             (char a_name [LEN_PATH], char r_tdesc [LEN_TERSE], int *r_uid, char r_owner [LEN_USER], int *r_gid, char r_group [LEN_USER], int *r_prm, char r_perms [LEN_TERSE], char r_pdisp [LEN_TERSE], long *r_bytes, int *r_epoch, int *r_major, int *r_minor, char r_link [LEN_PATH], int *r_dev, int *r_inode, char r_hash [LEN_DESC])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tSTAT       s;
   /*> tPASSWD    *x_owner     = NULL;                                                <*/
   /*> tGROUP     *x_group     = NULL;                                                <*/
   char        x_type      = YENV_NONE;
   char        x_tdesc     [LEN_TERSE] = "WTF";
   int         x_prm       =    0;
   int         i           =    0;
   FILE       *f           = NULL;
   SHA_CTX     ctx;
   uchar       x_buf       [LEN_RECD]  = "";
   uchar       x_hash      [LEN_DESC]  = "";
   uchar       t           [LEN_SHORT] = "";
   int         x_bytes     = 0;
   int         x_total     = 0;
   /*---(default)------------------------*/
   if (r_tdesc != NULL)  strcpy (r_tdesc, "");
   if (r_uid   != NULL)  *r_uid   = -1;
   if (r_owner != NULL)  strcpy (r_owner, "");
   if (r_gid   != NULL)  *r_gid   = -1;
   if (r_group != NULL)  strcpy (r_group, "");
   if (r_prm   != NULL)  *r_prm   = -1;
   if (r_perms != NULL)  strcpy (r_perms, "");
   if (r_pdisp != NULL)  strcpy (r_pdisp, "");
   if (r_bytes != NULL)  *r_bytes = -1;
   if (r_epoch != NULL)  *r_epoch = -1;
   if (r_major != NULL)  *r_major = -1;
   if (r_minor != NULL)  *r_minor = -1;
   if (r_link  != NULL)  strcpy (r_link , "");
   if (r_dev   != NULL)  *r_dev   = -1;
   if (r_inode != NULL)  *r_inode = -1;
   if (r_hash  != NULL)  strcpy (r_hash , "");
   /*---(defense)------------------------*/
   --rce;  if (a_name == NULL)            return rce;
   --rce;  if (strcmp (a_name, "") == 0)  return rce;
   /*---(check existance)----------------*/
   if (r_tdesc != NULL)  strlcpy (r_tdesc, "non-exist", LEN_TERSE);
   rc = lstat (a_name, &s);
   if (rc < 0)   return YENV_NONE;
   /*---(normal types)-------------------*/
   /*> x_type = yenv_type (&s);                                                       <*/
   if      (S_ISBLK  (s.st_mode))   x_type = YENV_BLOCK;
   else if (S_ISCHR  (s.st_mode))   x_type = YENV_CHAR ;
   else if (S_ISDIR  (s.st_mode))   x_type = YENV_DIR  ;
   else if (S_ISREG  (s.st_mode))   x_type = YENV_REG  ;
   else if (S_ISSOCK (s.st_mode))   x_type = YENV_IPSOC;
   else if (S_ISFIFO (s.st_mode))   x_type = YENV_PIPE ;
   else if (S_ISLNK  (s.st_mode))   x_type = YENV_SYM  ;
   else                             x_type = YENV_WTF  ;
   /*---(check hard link)----------------*/
   if (x_type == YENV_REG   && s.st_nlink > 1) x_type = YENV_HARD ;
   /*---(set type desc)------------------*/
   strlcpy (x_tdesc, yENV_typedesc (x_type), LEN_TERSE);
   DEBUG_FILE   yLOG_info    ("x_tdesc"   , x_tdesc);
   if (r_tdesc != NULL)  strlcpy (r_tdesc, x_tdesc, LEN_TERSE);
   /*---(owner)--------------------------*/
   rc = yENV_user_uid   (x_type, s.st_uid, r_owner, r_uid);
   /*---(group)--------------------------*/
   rc = yENV_group_gid   (x_type, s.st_gid, r_group, r_gid);
   /*---(permissions)--------------------*/
   rc = yENV_perms_octal (x_type, s.st_mode, r_perms, r_prm, r_pdisp);
   /*---(size)---------------------------*/
   if (x_type != YENV_SYM && r_bytes != NULL)      *r_bytes = s.st_size;
   /*---(update)-------------------------*/
   if (x_type != YENV_SYM && r_epoch != NULL)      *r_epoch = s.st_mtime;
   /*---(device)-------------------------*/
   IF_DEV {
      if (r_major != NULL)   *r_major = major (s.st_rdev);
      if (r_minor != NULL)   *r_minor = minor (s.st_rdev);
   }
   /*---(symlink)------------------------*/
   if (x_type == YENV_SYM  ) {
      if (r_link  != NULL) {
         i = readlink (a_name, r_link, LEN_PATH);
         r_link [i] = '\0';
      }
   }
   /*---(device and inode)---------------*/
   if (r_dev   != NULL)  *r_dev   = s.st_dev;
   if (r_inode != NULL)  *r_inode = s.st_ino;
   /*---(file hash)----------------------*/
   rc = yENV_hash (x_type, a_name, r_hash);
   /*---(complete)-----------------------*/
   return x_type;
}

char*
yENV_detail_unit        (char a_name [LEN_PATH])
{
   char        x_type      = YENV_NONE;
   char        x_owner     [LEN_LABEL] = "";
   char        x_group     [LEN_LABEL] = "";
   char        x_perms     [LEN_TERSE] = "";
   int         x_major     =   -1;
   int         x_minor     =   -1;
   char        x_ttype     = YENV_NONE;
   char        x_target    [LEN_PATH]  = "";
   static char x_out       [LEN_FULL]  = "";
   x_type  = yENV_detail (a_name, NULL, NULL, x_owner, NULL, x_group, NULL, NULL, x_perms, NULL, NULL, &x_major, &x_minor, x_target, NULL, NULL, NULL);
   if (x_type < 0) { strcpy (x_out, "(n/a)");  return x_out; }
   if (strcmp (x_target, "") != 0)  x_ttype = yENV_detail (x_target, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
   switch (x_type) {
   case YENV_NONE  : sprintf (x_out, "%-45.45s  -  ·           ·           ·          ´", a_name);  break;
   case YENV_BLOCK :
   case YENV_CHAR  : sprintf (x_out, "%-45.45s  %c  %-10.10s  %-10.10s  %-10.10s  %3d %3d ´", a_name, x_type, x_owner, x_group, x_perms, x_major, x_minor);  break;
   case YENV_SYM   : sprintf (x_out, "%-45.45s  %c  %c  %2då%.35sæ ´", a_name, x_type, x_ttype, strlen (x_target), x_target);  break;
   case YENV_DIR   :
   case YENV_REG   :
   case YENV_HARD  :
   default         : sprintf (x_out, "%-45.45s  %c  %-10.10s  %-10.10s  %-10.10s ´", a_name, x_type, x_owner, x_group, x_perms);  break;
   }
   return x_out;
}


