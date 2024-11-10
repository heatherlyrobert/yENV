/*===[[ START ]]==============================================================*/
#include    "yENV.h"
#include    "yENV_priv.h"



/*====================------------------------------------====================*/
/*===----                      creating files                          ----===*/
/*====================------------------------------------====================*/
static void      o___CREATE_____________o (void) {;}

char
yENV_touchier           (char a_type, char a_name [LEN_PATH], char a_own [LEN_LABEL], char a_grp [LEN_LABEL], char a_perms [LEN_LABEL], int a_major, int a_minor, char a_link [LEN_PATH])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_type      = YENV_NONE;
   FILE       *f           = NULL;
   tPASSWD    *x_owner     = NULL;
   tGROUP     *x_group     = NULL;
   int         x_uid       =   -1;
   int         x_gid       =   -1;
   uint        x_perms     =   -1;
   int         i, l, x_euid, x_egid, x_eperm, x_emaj, x_emin;
   char        x_link      [LEN_PATH];
   /*---(defense)------------------------*/
   --rce;  if (a_name  == NULL)                  return rce;
   --rce;  if (strcmp (a_name, "") == 0)         return rce;
   --rce;  if (a_own   == NULL)                  return rce;
   --rce;  if (a_grp   == NULL)                  return rce;
   --rce;  if (a_perms == NULL)                  return rce;
   /*---(check on file)------------------*/
   x_type = yENV_exists (a_name);
   --rce;  if (x_type < 0)                       return rce;
   --rce;  if (x_type > YENV_NONE && x_type != a_type) return rce;
   /*---(pre-work ownership)-------------*/
   x_owner = getpwnam (a_own);
   --rce;  if (x_owner == NULL)                  return rce;
   x_uid   = x_owner->pw_uid;
   x_group = getgrnam (a_grp);
   --rce;  if (x_group == NULL)                  return rce;
   x_gid   = x_group->gr_gid;
   /*---(pre-work permissions)-----------*/
   l = strlen (a_perms);
   --rce;
   if      (a_perms [0] == '0')   sscanf (a_perms, "%o", &x_perms);
   else if (l >= 5 && a_perms [1] == '_') {
      for (i = 0; i < MAX_PERM; ++i) {
         if (strcmp (zENV_perms [i].name, a_perms) != 0)  continue;
         x_perms = zENV_perms [i].value;
         break;
      }
      if (x_perms == -1)                         return rce;
   }
   else if (l == 9) {
      x_perms = 0;
      if      (a_perms [0] == '-')  ;
      else if (a_perms [0] == 'r')  x_perms += 00400;
      else                          return rce;
      if      (a_perms [1] == '-')  ;
      else if (a_perms [1] == 'w')  x_perms += 00200;
      else                          return rce;
      if      (a_perms [2] == '-')  ;
      else if (a_perms [2] == 'x')  x_perms += 00100;
      else if (a_perms [2] == 's')  x_perms += 04100;
      else if (a_perms [2] == 'S')  x_perms += 04000;
      else                          return rce;
      if      (a_perms [3] == '-')  ;
      else if (a_perms [3] == 'r')  x_perms += 00040;
      else                          return rce;
      if      (a_perms [4] == '-')  ;
      else if (a_perms [4] == 'w')  x_perms += 00020;
      else                          return rce;
      if      (a_perms [5] == '-')  ;
      else if (a_perms [5] == 'x')  x_perms += 00010;
      else if (a_perms [5] == 's')  x_perms += 02010;
      else if (a_perms [5] == 'S')  x_perms += 02000;
      else                          return rce;
      if      (a_perms [6] == '-')  ;
      else if (a_perms [6] == 'r')  x_perms += 00004;
      else                          return rce;
      if      (a_perms [7] == '-')  ;
      else if (a_perms [7] == 'w')  x_perms += 00002;
      else                          return rce;
      if      (a_perms [8] == '-')  ;
      else if (a_perms [8] == 'x')  x_perms += 00001;
      else if (a_perms [8] == 't')  x_perms += 01001;
      else if (a_perms [8] == 'T')  x_perms += 01000;
      else                          return rce;
   }
   else  return rce;
   /*---(create, if needed)--------------*/
   --rce;  if (x_type == YENV_NONE) {
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
   /*---(ownership)----------------------*/
   rc = chown (a_name, x_uid, x_gid);
   --rce;  if (rc < 0)            return rce;
   /*---(permissions)--------------------*/
   rc = chmod (a_name, x_perms);
   --rce;  if (rc < 0)            return rce;
   /*---(verify)-------------------------*/
   x_type = yENV_detail (a_name, &x_euid, NULL, &x_egid, NULL, &x_eperm, NULL, NULL, NULL, NULL, &x_emaj, &x_emin, x_link, NULL, NULL, NULL);
   --rce;  if (x_type == YENV_NONE)                      return YENV_NONE;
   --rce;  if (x_type <  0)                        return rce;
   --rce;  if (x_type >  YENV_NONE && x_type != a_type)  return rce;
   --rce;  if (x_uid   != x_euid)                  return rce;
   --rce;  if (x_gid   != x_egid)                  return rce;
   --rce;  if (x_type != YENV_SYM  ) {
      --rce;  if (x_perms != x_eperm)              return rce;
   }
   --rce;  if (strchr ("bc", x_type) != NULL) {
      if (a_major != x_emaj)                       return rce;
      if (a_minor != x_emin)                       return rce;
   }
   --rce;  if (x_type == YENV_SYM  ) {
      if (strcmp (a_link, x_link) != 0)            return rce;
   }
   /*---(complete)-----------------------*/
   return x_type;
}

char yENV_touch              (char a_name [LEN_PATH], char a_own [LEN_LABEL], char a_grp [LEN_LABEL], char a_perms [LEN_LABEL]) { return yENV_touchier (YENV_REG  , a_name, a_own, a_grp, a_perms, 0, 0, ""); }
char yENV_mkdir              (char a_name [LEN_PATH], char a_own [LEN_LABEL], char a_grp [LEN_LABEL], char a_perms [LEN_LABEL]) { return yENV_touchier (YENV_DIR  , a_name, a_own, a_grp, a_perms, 0, 0, ""); }



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
   /*---(defense)------------------------*/
   --rce;  if (a_name == NULL)                             return rce;
   --rce;  if (strcmp (a_name, "") == 0)                   return rce;
   /*---(check on file)------------------*/
   x_type = yENV_exists (a_name);
   --rce;  if (x_type < 0)                                 return rce;
   --rce;  if (x_type > YENV_NONE && x_type != a_type)     return rce;
   /*---(create, if needed)--------------*/
   --rce;  switch (a_type) {
   case YENV_BLOCK :
      break;
   case YENV_CHAR  :
      break;
   case YENV_DIR   : 
      rc = rmdir   (a_name);
      break;
   case YENV_REG   : case YENV_HARD  : case YENV_SYM   : 
      rc = unlink (a_name);
      break;
   case YENV_IPSOC :
      break;
   case YENV_PIPE  :
      break;
   }
   /*---(complete)-----------------------*/
   return yENV_exists (a_name);
}

char yENV_rm            (char a_name [LEN_PATH]) { yENV_removier (YENV_REG  , a_name); }
char yENV_rmdir         (char a_name [LEN_PATH]) { yENV_removier (YENV_DIR  , a_name); }



/*====================------------------------------------====================*/
/*===----                      examining files                         ----===*/
/*====================------------------------------------====================*/
static void      o___EXAMINE____________o (void) {;}

char 
yENV_detail             (char a_name [LEN_PATH], int *r_uid, char r_own [LEN_LABEL], int *r_gid, char r_grp [LEN_LABEL], int *r_perms, char r_pname [LEN_LABEL], char r_pdisp [LEN_TERSE], long *r_bytes, int *r_epoch, int *r_major, int *r_minor, char r_link [LEN_PATH], int *r_dev, int *r_inode, char r_hash [LEN_DESC])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tSTAT       s;
   tPASSWD    *x_owner     = NULL;
   tGROUP     *x_group     = NULL;
   char        x_type      = YENV_NONE;
   int         x_perms     =    0;
   int         i           =    0;
   FILE       *f           = NULL;
   SHA_CTX     ctx;
   uchar       x_buf       [LEN_RECD]  = "";
   uchar       x_hash      [LEN_DESC]  = "";
   uchar       t           [LEN_SHORT] = "";
   int         x_bytes     = 0;
   int         x_total     = 0;
   /*---(default)------------------------*/
   if (r_uid   != NULL)  *r_uid   = -1;
   if (r_own   != NULL)  strcpy (r_own  , "");
   if (r_gid   != NULL)  *r_gid   = -1;
   if (r_grp   != NULL)  strcpy (r_grp  , "");
   if (r_perms != NULL)  *r_perms = -1;
   if (r_pname != NULL)  strcpy (r_pname, "");
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
   rc = lstat (a_name, &s);
   if (rc < 0)   return YENV_NONE;
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
   if (x_type == YENV_REG   && s.st_nlink > 1) x_type = YENV_HARD ;
   /*---(ownership)----------------------*/
   if (r_uid != NULL || r_own != NULL) {
      x_owner = getpwuid (s.st_uid);
      if (x_owner != NULL)  {
         if (r_uid != NULL)  *r_uid   = x_owner->pw_uid;
         if (r_own != NULL)  strlcpy (r_own, x_owner->pw_name, LEN_LABEL);
      }
   }
   if (r_gid != NULL || r_grp != NULL) {
      x_group = getgrgid (s.st_gid);
      if (x_group != NULL)  {
         if (r_gid != NULL)  *r_gid   = x_group->gr_gid;
         if (r_grp != NULL)  strlcpy (r_grp, x_group->gr_name, LEN_LABEL);
      }
   }
   /*---(permissions)--------------------*/
   x_perms = s.st_mode & 007777;
   if (r_perms != NULL)      *r_perms = x_perms;
   if (r_pname != NULL || r_pdisp != NULL) {
      for (i = 0; i < MAX_PERM; ++i) {
         if (zENV_perms [i].value != x_perms)  continue;
         if (r_pname != NULL)   strlcpy (r_pname, zENV_perms [i].name, LEN_TERSE);
         if (r_pdisp != NULL)   strlcpy (r_pdisp, zENV_perms [i].disp, LEN_TERSE);
         break;
      }
   }
   /*---(size)---------------------------*/
   if (r_bytes != NULL)      *r_bytes = s.st_size;
   /*---(update)-------------------------*/
   if (r_epoch != NULL)      *r_epoch = s.st_mtime;
   /*---(device)-------------------------*/
   if (strchr ("bc", x_type) != NULL) {
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
   if (x_type == YENV_REG   && r_hash != NULL) {
      /*---(prepare)---------------------*/
      f = fopen (a_name, "rb");
      --rce;  if (f == NULL)  return rce;
      rc = SHA1_Init (&ctx);
      --rce;  if (rc != 1)   return rce;
      /*---(hash all)--------------------*/
      while (1) {
         x_bytes = fread (x_buf, 1, sizeof (x_buf), f);
         --rce;  if (x_bytes <  0)  { fclose (f); return rce; }
         x_total += x_bytes;
         if (x_bytes == 0)  break;
         rc = SHA1_Update (&ctx, x_buf, x_bytes);
         --rce;  if (rc != 1)       { fclose (f); return rce; }
      }
      /*---(finalize hash)---------------*/
      fclose (f);
      rc = SHA1_Final (x_hash, &ctx);
      /*> printf ("x_total = %d\n", x_total);                                         <*/
      --rce;  if (rc != 1)  return rce;
      strcpy (r_hash, "");
      for (i = 0; i < 20; ++i) {
         sprintf (t, "%02x", x_hash [i]);
         strlcat (r_hash, t, LEN_DESC);
      }
      r_hash [40] = '\0';
      /*---(done)------------------------*/
   }
   /*---(complete)-----------------------*/
   return x_type;
}

char yENV_exists  (char a_name [LEN_PATH]) { return yENV_detail (a_name, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL); }

char*
yENV_detail_unit        (char a_name [LEN_PATH])
{
   char        x_type      = '-';
   char        x_owner     [LEN_LABEL] = "";
   char        x_group     [LEN_LABEL] = "";
   char        x_perms     [LEN_TERSE] = "";
   static char x_out       [LEN_FULL]  = "";
   x_type = yENV_detail (a_name, NULL, x_owner, NULL, x_group, NULL, NULL, x_perms, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
   if (x_type == '-') {
      sprintf (x_out, "%-45.45s  -  ·           ·           ·          ´", a_name);
   } else {
      sprintf (x_out, "%-45.45s  %c  %-10.10s  %-10.10s  %-10.10s ´", a_name, x_type, x_owner, x_group, x_perms);
   }
   return x_out;
}


