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
/*===----                        security users                        ----===*/
/*====================------------------------------------====================*/
static void      o___USERS______________o (void) {;}

char
yENV_user_data          (char a_type, char b_name [LEN_USER], int *b_uid, int *r_gid, char r_dir [LEN_HUND], char r_shell [LEN_HUND])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   tPASSWD    *x_owner     = NULL;
   /*---(default)------------------------*/
   if (b_name  != NULL && a_type != 'n')  strcpy (b_name, "");
   if (b_uid   != NULL && a_type != 'i')  *b_uid = -1;
   if (r_gid   != NULL)                   *r_gid = -1;
   if (r_dir   != NULL)                   strcpy (r_dir, "");
   if (r_shell != NULL)                   strcpy (r_shell, "");
   /*---(defense)------------------------*/
   --rce;  if (a_type == '\0' || strchr ("ni", a_type) == NULL)                return rce;
   --rce;  if (a_type == 'n' && (b_name == NULL || strcmp (b_name, "") == 0))  return rce;
   --rce;  if (a_type == 'i' && (b_uid  == NULL || *b_uid < 0))                 return rce;
   /*---(get owner record)---------------*/
   if (a_type == 'n')    x_owner = getpwnam (b_name);
   else                  x_owner = getpwuid (*b_uid);
   --rce;  if (x_owner == NULL)                                                return rce;
   /*---(save back)----------------------*/
   if (a_type == 'i' && b_name  != NULL)  strlcpy (b_name , x_owner->pw_name , LEN_USER);
   if (a_type == 'n' && b_uid   != NULL)  *b_uid = x_owner->pw_uid;
   if (r_gid   != NULL)                   *r_gid = x_owner->pw_gid;
   if (r_dir   != NULL)                   strlcpy (r_dir  , x_owner->pw_dir  , LEN_HUND);
   if (r_shell != NULL)                   strlcpy (r_shell, x_owner->pw_shell, LEN_HUND);
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
   /*---(defense)------------------------*/
   --rce;  if (a_name == NULL) return rce;
   --rce;  if (strcmp (a_name, "root"   ) == 0) return rce;
   --rce;  if (strcmp (a_name, "system" ) == 0) return rce;
   --rce;  if (strcmp (a_name, "member" ) == 0) return rce;
   --rce;  if (strcmp (a_name, "machine") == 0) return rce;
   --rce;  if (strcmp (a_name, "shared" ) == 0) return rce;
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
   --rce;  if (rc == 0)  return rce;
   /*---(complete)-----------------------*/
   return 0; 
}

char       /*-> create a locked user for testing -------[ ------ [----------]-*/
yENV_user_add           (char a_name [LEN_USER], char a_home, char a_shell)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
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
   --rce;  if (strcmp (a_name, "root"   ) == 0) return rce;
   --rce;  if (strcmp (a_name, "system" ) == 0) return rce;
   --rce;  if (strcmp (a_name, "member" ) == 0) return rce;
   --rce;  if (strcmp (a_name, "machine") == 0) return rce;
   --rce;  if (strcmp (a_name, "shared" ) == 0) return rce;
   /*---(remove old version)-------------*/
   rc = yENV_user_data ('n', a_name, NULL, NULL, NULL, NULL);
   --rce;  if (rc >= 0) {
      rc = yENV_user_del (a_name);
      if (rc < 0)  return rce;
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
   sprintf  (t, " %s  >> /dev/null 2>&1", a_name);
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



/*====================------------------------------------====================*/
/*===----                        security groups                       ----===*/
/*====================------------------------------------====================*/
static void      o___GROUPS_____________o (void) {;}

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
   --rce;  if (a_type == 'i' && (b_gid  == NULL || *b_gid < 0))                 return rce;
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

char
yENV_group_del          (char a_name [LEN_USER])
{
   return 0;
}

char
yENV_group_add          (char a_name [LEN_USER], char a_user [LEN_USER])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =  -10;
   /*---(remove old version)-------------*/
   rc = yENV_group_data ('n', a_name, NULL);
   --rce;  if (rc < 0)  return rce;
   return 0;
}



/*====================------------------------------------====================*/
/*===----                        permissions                           ----===*/
/*====================------------------------------------====================*/
static void      o___PERMS______________o (void) {;}

char
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

