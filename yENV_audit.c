/*===[[ START ]]==============================================================*/
#include    "yENV.h"
#include    "yENV_priv.h"

/*                                               1         2         3         4         5         6         7         8         9            */
/*                                     -123456789-123456789-123456789-123456789-123456789-123456789-123456789-123456789-123456789-123456789   */
/*                                     -------request--------   cfg   ----check----   flg   -fix-   ---recheck---   f   hacked         */
static char s_blank     [LEN_HUND]  = "· ··· ··· ·· ·· ···· -   ···   · ··· ·· ·· -   ···   · · ·   · ··· ·· ·· -   Ï   ···· -";
static char s_score     [LEN_HUND]  = "d t·· ogp ·· ·· ···h y   ···   n --- ·· ··     ···   · · ·   n --- ·· ··     Ï   ···· Ï";

#define     BEG_REQUEST    0

#define     BEG_CONF      25
#define     END_CONF      27

#define     BEG_CHECK     31
#define     END_CHECK     46

#define     BEG_FLAG      50
#define     END_FLAG      52

#define     BEG_UPDATE    56
#define     END_UPDATE    64

#define     BEG_RECHECK   68
#define     END_RECHECK   33

#define     END_FINAL     87

#define     BEG_HACKED    91
#define     END_HACKED    96

/*===[[ REQUEST ]]===============*/

#define     MARK_ETYPE     0
#define     MARK_EFULL     2
#define     MARK_EMODE     3
#define     MARK_EFLAG     4

#define     MARK_EOWNER    6
#define     MARK_EGROUP    7
#define     MARK_EPERMS    8

#define     MARK_EMAJOR   10
#define     MARK_EMINOR   11

#define     MARK_ETTYPE   13
#define     MARK_ETARGET  14

#define     MARK_EEPOCH   16
#define     MARK_EBYTES   17
#define     MARK_EINODE   18
#define     MARK_EHASH    19

#define     MARK_REQUEST  21

#define     MARK_CONFC    25
#define     MARK_CONFF    26
#define     MARK_CONFX    27

/*===[[ CHECK ]]=================*/

#define     MARK_CTYPE    31

#define     MARK_COWNER   33
#define     MARK_CGROUP   34
#define     MARK_CPERMS   35

#define     MARK_CMAJOR   37
#define     MARK_CMINOR   38

#define     MARK_CTTYPE   40
#define     MARK_CTARGET  41

#define     MARK_CHECK    43

#define     MARK_FDEL     47
#define     MARK_FADD     48
#define     MARK_FUPD     49

/*===[[ UPDATES ]]===============*/

#define     MARK_REMOVE   53
#define     MARK_CREATE   55
#define     MARK_UPDATE   57

/*===[[ RECHECK ]]===============*/

#define     MARK_RTYPE    61

#define     MARK_ROWNER   63
#define     MARK_RGROUP   64
#define     MARK_RPERMS   65

#define     MARK_RMAJOR   67
#define     MARK_RMINOR   68

#define     MARK_RTTYPE   70
#define     MARK_RTARGET  71

#define     MARK_RECHECK  73

/*===[[ FINAL ]]=================*/

#define     MARK_FINAL    77



/*>    REQUEST LEGEND ===============================================================================================================================================================\n");   <* 
 *>    ƒ²²²²²²²²²²²²²²²²²²²² type            d) directory    f) file         s) symlink      c) char dev     b) block dev    p) pipe/fifo    i) ipsoc        h) hard link    ?) illegal            <* 
 *>    Œ ƒ²²²²²²²²²²²²²²²²²² name            n) valid        /) pathless     -) null/empty   °) illegal                                                                            <* 
 *>    Œ Œƒ²²²²²²²²²²²²²²²²² owner           o) valid        O) defaulted    -) null         °) illegal                                                                                            <* 
 *>    Œ ŒŒƒ²²²²²²²²²²²²²²²² group           g) valid        G) defaulted    -) null         °) illegal                                                                                            <* 
 *>    Œ ŒŒŒƒ²²²²²²²²²²²²²²² permissions     p) valid        P) defaulted    -) null         °) illegal                                                                                            <* 
 *>    Œ ŒŒŒŒ ƒ²²²²²²²²²²²²² major number
 *>    Œ ŒŒŒŒ Œƒ²²²²²²²²²²²² major number
 *>    Œ ŒŒŒŒ ŒŒ ƒ²²²²²²²²²² target type     d) directory    f) file         s) symlink      c) char dev     b) block dev    p) pipe/fifo    i) ipsoc        h) hard link    ?) illegal            <*
 *>    Œ ŒŒŒŒ ŒŒ Œƒ²²²²²²²²² target link     t) target       -) none\n");                                                                                                                          <*
 *>    Œ ŒŒŒŒ ŒŒ ŒŒ ƒ²²²²²²² epoch
 *>    Œ ŒŒŒŒ ŒŒ ŒŒ Œƒ²²²²²² bytes
 *>    Œ ŒŒŒŒ ŒŒ ŒŒ ŒŒƒ²²²²² inode
 *>    Œ ŒŒŒŒ ŒŒ ŒŒ ŒŒŒƒ²²²² hash
 *>    Œ ŒŒŒŒ ŒŒ ŒŒ ŒŒŒŒ ƒ²² summary         y) complete     !) issues\n");                                                                                                                        <* 
 *>    d togp ·· ·· ···· y (file/directory example)\n");                                                                                                                                         <* 
 *>    c togp jn··· ···· y (char/block device example\n");                                                                                                                                       <* 
 *>    s t··· ··ts· ···· y (symlink/hardlink example\n");                                                                                                                                                 <*/


/*>    CHECK/RECHECK LEGEND =========================================================================================================================================================\n");   <* 
 *>    ƒ²²²²²²²²²²²²²²²²²² name            n) valid        £) null         ©) empty        /) pathless     F) bad chars\n");                                                                     <* 
 *>    Œƒ²²²²²²²²²²²²²²²²² exists          e) existing      ) not-exist\n");                                                                                                                     <* 
 *>    ŒŒ ƒ²²²²²²²²²²²²²²² actual type     d) directory    f) file         s) symlink      c) char dev     b) block dev    p) pipe/fifo    i) ipsoc        h) hard link\n");                     <* 
 *>    ŒŒ Œƒ²²²²²²²²²²²²²² owner           o) matches      -) no match\n");                                                                                                                      <* 
 *>    ŒŒ ŒŒƒ²²²²²²²²²²²²² group           g) matches      -) no match\n");                                                                                                                      <* 
 *>    ŒŒ ŒŒŒƒ²²²²²²²²²²²² permissions     p) matches      -) no match\n");                                                                                                                      <* 
 *>    ŒŒ ŒŒŒŒ ƒ²²²²²²²²²² major number
 *>    ŒŒ ŒŒŒŒ Œƒ²²²²²²²²² minor number
 *>    ŒŒ ŒŒŒŒ ŒŒ ƒ²²²²²²² source link
 *>    ŒŒ ŒŒŒŒ ŒŒ Œƒ²²²²²² source exist    s) given        -) none\n");                                                                                                                          <* 
 *>    ŒŒ ŒŒŒŒ ŒŒ ŒŒƒ²²²²² source type     s) given        -) none\n");                                                                                                                          <* 
 *>    ŒŒ ŒŒŒŒ ŒŒ ŒŒŒ ƒ²²² summary         y) complete     !) issues         not-exist\n");                                                                                                      <* 
 *>    n- ---- ·· ···      (file/directory does not exist yet)\n");                                                                                                                              <* 
 *>    ne dogp ···· y      (file/directory example)\n");                                                                                                                                         <* 
 *>    ŒŒ ŒŒŒŒ ƒ²²²²²²² major number    j) matches      -) no match\n");                                                                                                                      <* 
 *>    ŒŒ ŒŒŒŒ Œƒ²²²²²² minor number    n) matches      -) no match\n");                                                                                                                      <* 
 *>    ŒŒ ŒŒŒŒ ŒŒ  ƒ²²² summary         y) complete     !) issues         not-exist\n");                                                                                                      <* 
 *>    ne cogp ´jn· y    (char/block device example)\n");                                                                                                                                      <* 
 *>    ŒŒ Œ ƒ²²²²²²²²²² source name     n) valid        £) null         ©) empty        /) pathless     F) bad chars\n");                                                                     <* 
 *>    ŒŒ Œ Œƒ²²²²²²²²² source exists   e) existing      ) not-exist\n");                                                                                                                     <* 
 *>    ŒŒ Œ ŒŒƒ²²²²²²²² source type     d) directory    f) file         s) symlink      c) char dev     b) block dev    p) pipe/fifo    i) ipsoc        h) hard link\n");                     <* 
 *>    ŒŒ Œ ŒŒŒƒ²²²²²²² source link     n) matches      -) no match\n");                                                                                                                      <* 
 *>    ŒŒ Œ ŒŒŒŒ   ƒ²²² summary         y) complete     !) issues         not-exist\n");                                                                                                      <* 
 *>    ne s´necl·· y    (symlink example)\n");                                                                                                                                                <* 
 *>    n- -´nec-··      (symlink does not exist yet)\n");                                                                                                                                     <*/

/*>    UPDATE LEGEND ================================================================================================================================================================\n");   <* 
 *>    ƒ²²²²²²²²²²²²²²² remove          e) existing     D) made dir     S) made slink   C) made char    B) made block   P) made pipe    I) made ipsoc   H) made hlink\n");                    <* 
 *>    Œƒ²²²²²²²²²²²²²² create          e) existing     D) made dir     S) made slink   C) made char    B) made block   P) made pipe    I) made ipsoc   H) made hlink\n");                    <* 
 *>    ŒŒ ƒ²²²²²²²²²²²² owner           o) no action    O) updated\n");                                                                                                                       <* 
 *>    ŒŒ Œƒ²²²²²²²²²²²²group            o) no action    O) updated\n");                                                                                                                       <* 
 *>    ŒŒ ŒŒƒ²²²²²²²²²²²perms             o) no action    O) updated\n");                                                                                                                       <* 
 *>    ŒŒ ŒŒŒ ƒ²²²²²²²²²summary         y) complete     !) issues\n");                                                                                                                        <* 
 *>    DO --- y    (file/directory created)\n");                                                                                                                                         <* 
 *>    eo g   y    (file/directory exists, permissions changed)\n");                                                                                                                     <* 
 *>    S· ·   y    (symlink created)\n");                                                                                                                                                <* 
 *>    CO G   y    (char/block device created)\n");                                                                                                                                      <*/




/*====================------------------------------------====================*/
/*===----                         helpers                              ----===*/
/*====================------------------------------------====================*/
static void      o___HELPERS____________o (void) {;}

char* yENV_score      (void)  { return s_score; }
char  yENV_score_def  (void)  { strlcpy (s_score, s_blank, LEN_HUND); return 0; }



/*====================------------------------------------====================*/
/*===----                       subroutines                            ----===*/
/*====================------------------------------------====================*/
static void      o___PARTS______________o (void) {;}

char
yenv_audit_prepare      (char a_type, char c_flag, char a_dir [LEN_PATH], char a_file [LEN_PATH], char a_mode, char r_full [LEN_PATH], char r_tdesc [LEN_TERSE], char r_mode [LEN_SHORT], char r_note [LEN_LABEL], char *r_check, char *r_force, char *r_fix)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         ld          =    0;
   int         lf          =    0;
   char        x_tdesc     [LEN_TERSE] = "";
   char        x_full      [LEN_PATH]  = "";
   char        x_mode      [LEN_SHORT] = "";
   char        x_note      [LEN_LABEL] = "";
   int         l           =    0;
   int         i           =    0;
   char        x_check     =  '-';
   char        x_force     =  '-';
   char        x_fix       =  '-';
   /*---(header)-------------------------*/
   DEBUG_FILE   yLOG_enter   (__FUNCTION__);
   /*---(initialize)---------------------*/
   strlcpy (s_score, s_blank, LEN_HUND);
   /*---(default)------------------------*/
   if (r_full  != NULL)  strcpy (r_full , "");
   if (r_tdesc != NULL)  strcpy (r_tdesc, "");
   if (r_mode  != NULL)  strcpy (r_mode , "");
   if (r_note  != NULL)  strcpy (r_note , "");
   if (r_check != NULL)  *r_check = '-';
   if (r_force != NULL)  *r_force = '-';
   if (r_fix   != NULL)  *r_fix   = '-';
   /*---(type description)---------------*/
   strlcpy (x_tdesc, yENV_typedesc (a_type), LEN_TERSE);
   s_score [MARK_ETYPE] = '°';
   if (strcmp (x_tdesc, "WTF") != 0)   s_score [MARK_ETYPE] = a_type;
   /*---(defense)------------------------*/
   s_score [MARK_EFULL] = '£';
   DEBUG_FILE   yLOG_point   ("a_dir"     , a_dir);
   --rce;  if (a_dir       == NULL) {
      s_score [MARK_REQUEST] = '°';
      s_score [MARK_FINAL  ] = '°';
      DEBUG_FILE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_FILE   yLOG_info    ("a_dir"     , a_dir);
   DEBUG_FILE   yLOG_point   ("a_file"    , a_file);
   --rce;  if (a_file      == NULL) {
      s_score [MARK_REQUEST] = '°';
      s_score [MARK_FINAL  ] = '°';
      DEBUG_FILE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_FILE   yLOG_info    ("a_file"    , a_file);
   /*---(prepare full name)--------------*/
   s_score [MARK_EFULL] = '-';
   ld = strlen (a_dir);
   lf = strlen (a_file);
   DEBUG_FILE    yLOG_complex ("len"       , "ld=%d, lf=%d", ld, lf);
   if (ld + lf == 0) {
      s_score [MARK_REQUEST] = '°';
      s_score [MARK_FINAL  ] = '°';
      DEBUG_FILE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   if (ld == 0)      sprintf (x_full, "%s", a_file);
   else if (lf == 0) sprintf (x_full, "%s", a_dir);
   else {
      if (a_dir [ld - 1] != '/')    sprintf (x_full, "%s/%s", a_dir, a_file);
      else                          sprintf (x_full, "%s%s" , a_dir, a_file);
   }
   DEBUG_FILE    yLOG_info    ("x_full"    , x_full);
   /*---(absolute)-----------------------*/
   s_score [MARK_EFULL] = '/';
   DEBUG_FILE    yLOG_char    ("x_full [0]", x_full [0]);
   --rce;  if (x_full [0] != '/') {
      yURG_err ('f', "full name must be absolute reference, i.e., start with '/'");
      DEBUG_YJOBS   yLOG_note    ("name must start with '/'");
      s_score [MARK_REQUEST] = '°';
      s_score [MARK_FINAL  ] = '°';
      DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(check name quality)-------------*/
   s_score [MARK_EFULL] = '°';
   l = strlen (x_full);
   --rce;  for (i = 0; i < l; ++i) {
      if (strchr (YSTR_FILES, x_full [i]) == NULL) {
         yURG_err ('f', "full name has an illegal character (%c) at position %d (security risk)", x_full [i], i);
         DEBUG_YJOBS   yLOG_complex ("bad char"  , "can not include %c at %d", x_full [i], i);
         s_score [MARK_REQUEST] = '°';
         s_score [MARK_FINAL  ] = '°';
         DEBUG_YJOBS   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
   }
   s_score [MARK_EFULL] = 'n';
   /*---(set mode)-----------------------*/
   DEBUG_FILE   yLOG_char    ("a_mode"    , a_mode);
   s_score [MARK_EMODE] = '°';
   --rce;  switch (a_mode) {
   case 'r' :
      strlcpy (x_mode, "rt", LEN_TERSE);
      strlcpy (x_note, "reading as text"   , LEN_LABEL);
      break;
   case 'R' :
      strlcpy (x_mode, "rb", LEN_TERSE);
      strlcpy (x_note, "reading as binary" , LEN_LABEL);
      break;
   case 'w' :
      strlcpy (x_mode, "wt", LEN_TERSE);
      strlcpy (x_note, "writing as text"  , LEN_LABEL);
      break;
   case 'W' :
      strlcpy (x_mode, "wb", LEN_TERSE);
      strlcpy (x_note, "writing as binary", LEN_LABEL);
      break;
   case '-' :
      strlcpy (x_mode, "--", LEN_TERSE);
      strlcpy (x_note, "audit-only"       , LEN_LABEL);
      break;
   default  :
      yURG_err ('f', "openning mode (%c) is not legal (rRwW-) ", a_mode);
      DEBUG_FILE   yLOG_note    ("mode not understood");
      s_score [MARK_REQUEST] = '°';
      s_score [MARK_FINAL  ] = '°';
      DEBUG_FILE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_FILE   yLOG_info    ("x_mode"    , x_mode);
   s_score [MARK_EMODE] = 'm';
   /*---(flags)--------------------------*/
   s_score [MARK_EFLAG] = '°';
   switch (c_flag) {
   case '!' :  x_check = 'y';  x_force = '!';  x_fix   = 'y';  break;
   case 'F' :  x_check = 'y';  x_force = 'y';  x_fix   = 'y';  break;
   case 'f' :  x_check = 'y';  x_force = '-';  x_fix   = 'y';  break;
   case '-' :  x_check = '-';  x_force = '-';  x_fix   = '-';  break;
   default  :
               yURG_err ('f', "configuration flag (%c) is not legal (!Ff-) ", c_flag);
               DEBUG_FILE   yLOG_note    ("c_flag not understood");
               s_score [MARK_REQUEST] = '°';
               s_score [MARK_FINAL  ] = '°';
               DEBUG_FILE   yLOG_exitr   (__FUNCTION__, rce);
               return rce;
   }
   s_score [MARK_EFLAG] = 'f';
   s_score [MARK_CONFC] = x_check;
   s_score [MARK_CONFF] = x_force;
   s_score [MARK_CONFX] = x_fix;
   /*---(save-back)----------------------*/
   if (r_full  != NULL)  snprintf (r_full , LEN_PATH , "%s", x_full);
   if (r_tdesc != NULL)  snprintf (r_tdesc, LEN_TERSE, "%s", x_tdesc);
   if (r_mode  != NULL)  snprintf (r_mode , LEN_SHORT, "%s", x_mode);
   if (r_note  != NULL)  snprintf (r_note , LEN_LABEL, "%s", x_note);
   if (r_check != NULL)  *r_check = x_check;
   if (r_force != NULL)  *r_force = x_force;
   if (r_fix   != NULL)  *r_fix   = x_fix;
   /*---(complete)-----------------------*/
   DEBUG_FILE    yLOG_exit    (__FUNCTION__);
   return RC_POSITIVE;
}

char
yenv_audit_expect       (char b_owner [LEN_USER], char b_group [LEN_USER], char b_perms [LEN_TERSE], int *r_uid, int *r_gid, int *r_prm, char r_disp [LEN_LABEL])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        rc_final    = RC_POSITIVE;
   int         x_uid       =   -1;
   int         x_gid       =   -1;
   uint        x           =    0;
   int         x_prm       =   -1;
   char        x_owner     [LEN_USER]  = "";
   char        x_group     [LEN_USER]  = "";
   char        x_perms     [LEN_TERSE] = "";
   char        x_disp      [LEN_LABEL] = "";
   /*---(header)-------------------------*/
   DEBUG_FILE   yLOG_enter   (__FUNCTION__);
   /*---(default)------------------------*/
   if (r_uid   != NULL)  *r_uid = -1;
   if (b_owner != NULL)  { snprintf (x_owner, LEN_USER , "%s", b_owner); strcpy (b_owner, ""); }
   if (r_gid   != NULL)  *r_gid = -1;
   if (b_group != NULL)  { snprintf (x_group, LEN_USER , "%s", b_group); strcpy (b_group, ""); }
   if (r_prm   != NULL)  *r_prm = -1;
   if (b_perms != NULL)  { snprintf (x_perms, LEN_TERSE, "%s", b_perms); strcpy (b_perms, ""); }
   if (r_disp  != NULL)  strcpy (r_disp , "");
   /*---(user ownership)-----------------*/
   s_score [MARK_EOWNER] = '-';
   --rce;  if (b_owner != NULL) {
      s_score [MARK_EOWNER] = '°';
      if (strcmp (x_owner, "") == 0 ) {
         DEBUG_FILE   yLOG_note    ("requested owner not provided, using current uid");
         x_uid = getuid ();
         rc = yENV_user_data  ('i', x_owner, &x_uid, NULL, NULL, NULL);
         if (rc < 0) {
            yURG_err ('f', "attempting to use illegal requested owner å%sæ, uid %d", x_owner, x_uid);
            rc_final = rce;
         } else {
            DEBUG_FILE   yLOG_complex ("owner"     , "%4d, %s", x_uid, x_owner);
            s_score [MARK_EOWNER] = 'O';
         }
      } else {
         DEBUG_FILE   yLOG_note    ("owner requested, getting uid");
         rc = yENV_user_data  ('n', x_owner, &x_uid, NULL, NULL, NULL);
         if (rc < 0) {
            yURG_err ('f', "attempting to use illegal requested owner å%sæ, uid %d", x_owner, x_uid);
            rc_final = rce;
         } else {
            DEBUG_FILE   yLOG_complex ("owner"     , "%4d, %s", x_uid, x_owner);
            s_score [MARK_EOWNER] = 'o';
         }
      }
   }
   /*---(group ownership)----------------*/
   s_score [MARK_EGROUP] = '-';
   --rce;  if (b_group != NULL) {
      s_score [MARK_EGROUP] = '°';
      if (strcmp (x_group, "") == 0 ) {
         DEBUG_FILE   yLOG_note    ("requested group not provided, using current gid");
         x_gid = getgid ();
         DEBUG_FILE   yLOG_value   ("x_gid"     , x_gid);
         rc = yENV_group_data ('i', x_group, &x_gid);
         DEBUG_FILE   yLOG_value   ("group"     , rc);
         if (rc < 0) {
            yURG_err ('f', "attempting to use illegal requested group å%sæ, gid %d", x_group, x_gid);
            rc_final = rce;
         } else {
            DEBUG_FILE   yLOG_complex ("group"     , "%4d, %s", x_gid, x_group);
            s_score [MARK_EGROUP] = 'G';
         }
      } else {
         DEBUG_FILE   yLOG_note    ("group requested, getting gid");
         rc = yENV_group_data ('n', x_group, &x_gid);
         DEBUG_FILE   yLOG_value   ("group"     , rc);
         if (rc < 0) {
            yURG_err ('f', "attempting to use illegal requested group å%sæ, gid %d", x_group, x_gid);
            rc_final = rce;
         } else {
            DEBUG_FILE   yLOG_complex ("group"     , "%4d, %s", x_gid, x_group);
            s_score [MARK_EGROUP] = 'g';
         }
      }
   }
   /*---(permissions)--------------------*/
   s_score [MARK_EPERMS] = '-';
   --rce;  if (b_perms != NULL) {
      s_score [MARK_EPERMS] = '°';
      DEBUG_FILE   yLOG_info    ("x_perms"   , x_perms);
      sscanf (x_perms, "%o", &x);
      x_prm = x;
      DEBUG_FILE   yLOG_value   ("x_prm"     , x_prm);
      if (strcmp (x_perms, "") == 0 ) {
         DEBUG_FILE   yLOG_note    ("requested perms not provided, using f_tight (0600)");
         x_prm = 0600;
         DEBUG_FILE   yLOG_value   ("x_prm"     , x_prm);
         rc = yENV_perms_data ('i', x_perms, &x_prm, x_disp);
         DEBUG_FILE   yLOG_value   ("perms"     , rc);
         if (rc < 0) {
            yURG_err ('f', "attempting to use illegal requested perms å%sæ, prm %d", x_perms, x_prm);
            rc_final = rce;
         } else {
            DEBUG_FILE   yLOG_complex ("perms"     , "%4o, %s", x_prm, x_perms);
            s_score [MARK_EPERMS] = 'P';
         }
      } else if (x_prm > 0 || strcmp (x_perms, "0000") == 0) {
         DEBUG_FILE   yLOG_note    ("requested perms by octal, getting name");
         DEBUG_FILE   yLOG_value   ("x_prm"     , x_prm);
         rc = yENV_perms_data ('i', x_perms, &x_prm, x_disp);
         DEBUG_FILE   yLOG_value   ("perms"     , rc);
         if (rc < 0) {
            yURG_err ('f', "attempting to use illegal requested perms å%sæ, prm %d", x_perms, x_prm);
            rc_final = rce;
         } else {
            DEBUG_FILE   yLOG_complex ("perms"     , "%4o, %s", x_prm, x_perms);
            s_score [MARK_EPERMS] = 'p';
         }
      } else {
         DEBUG_FILE   yLOG_note    ("perms requested, getting octal");
         rc = yENV_perms_data ('n', x_perms, &x_prm, x_disp);
         DEBUG_FILE   yLOG_value   ("perms"     , rc);
         if (rc < 0) {
            yURG_err ('f', "attempting to use illegal requested perms å%sæ, prm %d", x_perms, x_prm);
            rc_final = rce;
         } else {
            DEBUG_FILE   yLOG_complex ("perms"     , "%4o, %s", x_prm, x_perms);
            s_score [MARK_EPERMS] = 'p';
         }
      }
   }
   /*---(save-back)----------------------*/
   if (strchr ("Oo", s_score [MARK_EOWNER]) != NULL) {
      if (r_uid   != NULL)  *r_uid = x_uid;
      if (b_owner != NULL)  snprintf (b_owner, LEN_USER , "%s", x_owner);
   }
   if (strchr ("Gg", s_score [MARK_EGROUP]) != NULL) {
      if (r_gid   != NULL)  *r_gid = x_gid;
      if (b_group != NULL)  snprintf (b_group, LEN_USER , "%s", x_group);
   }
   if (strchr ("Pp", s_score [MARK_EPERMS]) != NULL) {
      if (r_prm   != NULL)  *r_prm = x_prm;
      if (b_perms != NULL)  snprintf (b_perms, LEN_TERSE, "%s", x_perms);
      if (r_disp  != NULL)  snprintf (r_disp , LEN_LABEL, "%s", x_disp );
   }
   /*---(finalize)-----------------------*/
   if (rc_final < 0) {
      s_score [MARK_REQUEST] = '°';
      s_score [MARK_FINAL  ] = '°';
   }
   /*---(complete)-----------------------*/
   DEBUG_FILE    yLOG_exit    (__FUNCTION__);
   return rc_final;
}

char
yenv_audit_extra        (char a_type, int a_major, int a_minor, char a_ttype, char a_target [LEN_PATH], int a_epoch, long a_bytes, int a_inode, char a_hash [LEN_DESC])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        rc_final    = RC_POSITIVE;
   char        x_tdesc     [LEN_TERSE] = "";
   int         l           =   0;
   int         i           =   0;
   char        x_bad       = '-';
   /*---(header)-------------------------*/
   DEBUG_FILE   yLOG_enter   (__FUNCTION__);
   /*---(device nums)--------------------*/
   --rce;  if (strchr ("bc", a_type) != NULL) {
      if (a_major >= 0 && a_major <= 255)    s_score [MARK_EMAJOR] = 'j';
      else {
         s_score [MARK_EMAJOR] = '°';
         yURG_err ('f', "attempting to use illegal major device number (%d), expeced (0-255)", a_major);
         rc_final = rce;
      }
   } else if (a_major != -1){
      yURG_err ('w', "included superfluous major device number (%d)", a_major);
   }
   --rce;  if (strchr ("bc", a_type) != NULL) {
      if (a_minor >= 0 && a_minor <= 255)    s_score [MARK_EMINOR] = 'n';
      else {
         s_score [MARK_EMINOR] = '°';
         yURG_err ('f', "attempting to use illegal minor device number (%d), expeced (0-255)", a_minor);
         rc_final = rce;
      }
   } else if (a_minor != -1){
      yURG_err ('w', "included superfluous minor device number (%d)", a_minor);
   }
   /*---(target type)--------------------*/
   --rce;  if (strchr ("sh", a_type) != NULL) {
      strlcpy (x_tdesc, yENV_typedesc (a_ttype), LEN_TERSE);
      if (strcmp (x_tdesc, "WTF") != 0)   s_score [MARK_ETTYPE] = a_ttype;
      else {
         s_score [MARK_ETTYPE] = '°';
         yURG_err ('f', "attempting to use illegal target type %s (%c)", x_tdesc, a_ttype);
         rc_final = rce;
      }
   } else if (a_ttype != YENV_NONE){
      yURG_err ('w', "included superfluous target type (%d)", a_ttype);
   }
   --rce;  if (a_type == YENV_HARD) {
      if (a_ttype == 0 || strchr ("rh", a_ttype) == NULL) {
         strlcpy (x_tdesc, yENV_typedesc (a_ttype), LEN_TERSE);
         s_score [MARK_ETTYPE] = '°';
         yURG_err ('f', "attempting to use hardlink to illegal type %s (%c), only allow (rh)", x_tdesc, a_ttype);
         rc_final = rce;
      }
   }
   /*---(target name)--------------------*/
   --rce;  if (strchr ("sh", a_type) != NULL) {
      s_score [MARK_ETARGET] = '°';
      if (a_target != NULL && strcmp (a_target, "") != 0) {
         s_score [MARK_ETARGET] = '/';
         DEBUG_FILE    yLOG_char    ("a_target", a_target [0]);
         if (a_target [0] != '/') {
            yURG_err ('f', "target must be absolute reference, i.e., start with '/'");
            rc_final = rce;
         } else {
            l = strlen (a_target);
            s_score [MARK_ETARGET] = '#';
            x_bad = '-';
            --rce;  for (i = 0; i < l; ++i) {
               if (strchr (YSTR_FILES, a_target [i]) == NULL) {
                  yURG_err ('f', "target name has an illegal character (%c) at position %d", a_target [i], i);
                  rc_final = rce;
                  x_bad = 'y';
               }
            }
            if (x_bad != 'y')   s_score [MARK_ETARGET] = 't';
         }
      }
   } else  if (a_target != NULL && strcmp (a_target, "") != 0) {
      yURG_err ('w', "included superfluous target name å%sæ", a_target);
   }
   /*---(specialty)----------------------*/
   if (a_epoch > 0)                s_score [MARK_EEPOCH] = 'e';
   if (a_bytes > 0)                s_score [MARK_EBYTES] = 'b';
   if (a_inode > 0)                s_score [MARK_EINODE] = 'i';
   --rce;  if (a_hash != NULL && strcmp (a_hash, "") != 0) {
      s_score [MARK_EHASH] = '°';
      l = strlen (a_hash);
      if (l == 40) {
         s_score [MARK_EHASH] = '#';
         x_bad = '-';
         for (i = 0; i < l; ++i) {
            if (strchr (YSTR_HEXUP, a_hash [i]) == NULL) {
               yURG_err ('f', "hash code has an illegal character (%c) at position %d", a_hash [i], i);
               rc_final = rce;
               x_bad = 'y';
            }
         }
         if (x_bad != 'y')   s_score [MARK_EHASH] = 'h';
      } else {
         yURG_err ('f', "hash code is the wrong length (%d) vs standard (40)", l);
         rc_final = rce;
      }
   }
   /*---(finalize)-----------------------*/
   if (rc_final < 0) {
      s_score [MARK_REQUEST] = '°';
      s_score [MARK_FINAL  ] = '°';
   } else {
      s_score [MARK_REQUEST] = '=';
   }
   /*---(complete)-----------------------*/
   DEBUG_FILE    yLOG_exit    (__FUNCTION__);
   return rc_final;
}

char
yenv_audit_precheck     (char a_full [LEN_PATH], char a_etype, char a_eowner [LEN_USER], char a_egroup [LEN_USER], char a_eperms [LEN_TERSE], int a_emajor, int a_eminor, char a_ettype, char a_etarget [LEN_PATH], char *r_atype, char r_atdesc [LEN_TERSE], char *r_del, char *r_add, char *r_upd, char c_force, char c_fix)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        rc_final    = RC_POSITIVE;
   char        x_atype     = YENV_NONE;
   char        x_atdesc    [LEN_TERSE] = "";
   char        x_aowner    [LEN_USER]  = "";
   char        x_agroup    [LEN_USER]  = "";
   char        x_aperms    [LEN_TERSE] = "";
   char        x_miss      [LEN_HUND]  = "";
   int         x_amajor    =   -1;
   int         x_aminor    =   -1;
   char        x_alink     [LEN_PATH]  = "";
   int         x_inode     =   -1;
   int         n           =   -1;
   char        x_del       =  '-';
   char        x_add       =  '-';
   char        x_upd       =  '-';
   int         l           =    0;
   /*---(quick-out)----------------------*/
   if (c_force == '-' && c_fix == '-') {
      DEBUG_FILE   yLOG_senter  (__FUNCTION__);
      DEBUG_FILE   yLOG_snote   ("no precheck requested");
      DEBUG_FILE   yLOG_sexit   (__FUNCTION__);
      return RC_ACK;
   }
   /*---(header)-------------------------*/
   DEBUG_FILE   yLOG_enter   (__FUNCTION__);
   /*---(defaults))----------------------*/
   if (r_atype  != NULL)   *r_atype = '-';
   if (r_atdesc != NULL)   strcpy (r_atdesc, "");
   if (r_del    != NULL)   *r_del   = '-';
   if (r_add    != NULL)   *r_add   = '-';
   if (r_upd    != NULL)   *r_upd   = '-';
   /*---(get data)-----------------------*/
   x_atype = yENV_detail (a_full, x_atdesc, NULL, x_aowner, NULL, x_agroup, NULL, x_aperms, NULL, NULL, NULL, &x_amajor, &x_aminor, x_alink, NULL, &x_inode, NULL);
   DEBUG_FILE   yLOG_value   ("detail"    , x_atype);
   --rce;  if (x_atype <= 0) {
      yURG_err ('f', "file check generated a hard error (%d)", x_atype);
      DEBUG_FILE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   s_score [MARK_CTYPE ] = x_atype;
   /*---(quick out)----------------------*/
   DEBUG_FILE   yLOG_char    ("x_atype"   , x_atype);
   if (x_atype == YENV_NONE && a_etype == YENV_NONE) {
      yURG_msg ('-', "non-existance of filesystem entry confirmed");
      return RC_POSITIVE;
   }
   /*---(existance)----------------------       ----del----; ----add----; ----upd----;*/
   if      (x_atype  == YENV_NONE)            {            ; x_add = 'y';            ;  strcat (x_miss, "existance, "); }
   else if (a_etype  == YENV_NONE)            { x_del = 'y';            ;            ;  strcat (x_miss, "existance, "); }
   /*---(type changes)-------------------       ----del----; ----add----; ----upd----;*/
   else if (x_atype  != a_etype) {
      s_score [MARK_CTYPE ] = toupper (x_atype);
      if (strchr ("hs", a_etype) != NULL &&
            strchr ("hs", x_atype) != NULL)   { x_del = 'y'; x_add = 'y';            ;  strcat (x_miss, "type, "     ); }
      else                                    { x_del = '!'; x_add = 'y';            ;  strcat (x_miss, "type, "     ); }
   }
   /*---(entry details)------------------       ----del----; ----add----; ----upd----;*/
   if (x_atype == a_etype) {
      switch (a_etype) {
      case YENV_BLOCK : case YENV_CHAR  :
         s_score [MARK_CMAJOR] = 'j';
         s_score [MARK_CMINOR] = 'n';
         if (x_amajor != a_emajor)            { x_del = 'y'; x_add = 'y';            ;  strcat (x_miss, "maj, "      );  s_score [MARK_CMAJOR] = 'J'; }
         if (x_aminor != a_eminor)            { x_del = 'y'; x_add = 'y';            ;  strcat (x_miss, "min, "      );  s_score [MARK_CMINOR] = 'N'; }
         break;
      case YENV_SYM   :
         rc = yENV_detail (a_etarget, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
         s_score [MARK_CTTYPE] = rc;
         if (rc != a_ettype)  s_score [MARK_CTTYPE] = toupper (rc);
         s_score [MARK_CTARGET] = 't';
         if (strcmp (x_alink, a_etarget) != 0) { x_del = 'y'; x_add = 'y';            ;  strcat (x_miss, "target, "   );  s_score [MARK_CTARGET] = 'T'; }
         break;
      case YENV_HARD  :
         rc = yENV_detail (a_etarget, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, &n, NULL);
         s_score [MARK_CTTYPE] = rc;
         if (rc != a_ettype) {
            if (a_ettype == YENV_REG && rc == YENV_HARD)  s_score [MARK_CTTYPE] = YENV_REG;
            else                                          s_score [MARK_CTTYPE] = toupper (rc);
         }
         s_score [MARK_CTARGET] = 't';
         if (x_inode != n)                    { x_del = 'y'; x_add = 'y';            ;  strcat (x_miss, "target, "   );  s_score [MARK_CTARGET] = 'T'; }
         break;
      }
   }
   /*---(small fixest)-------------------       ----del----; ----add----; ----upd----;*/
   if (x_atype == a_etype && x_add != 'y' && a_etype != YENV_SYM) {
      s_score [MARK_COWNER] = 'o';
      s_score [MARK_CGROUP] = 'g';
      s_score [MARK_CPERMS] = 'p';
      if (strcmp (x_aowner, a_eowner) != 0)   {            ;            ; x_upd = 'y';  strcat (x_miss, "owner, "    );  s_score [MARK_COWNER] = 'O'; }
      if (strcmp (x_agroup, a_egroup) != 0)   {            ;            ; x_upd = 'y';  strcat (x_miss, "group, "    );  s_score [MARK_CGROUP] = 'G'; }
      if (strcmp (x_aperms, a_eperms) != 0)   {            ;            ; x_upd = 'y';  strcat (x_miss, "perms, "    );  s_score [MARK_CPERMS] = 'P'; }
   }
   /*---(entry fixes)--------------------       ----del----; ----add----; ----upd----;*/
   l = strlen (x_miss);
   if (l > 0) {
      s_score [MARK_CHECK] = '!';
      if (l > 2)  x_miss [l - 2] = '\0';
      yURG_err ('w', "troubles with entry %s", x_miss);
      rc_final = RC_WARNING;
   } else {
      s_score [MARK_CHECK] = '=';
   }
   /*---(finalize)-----------------------*/
   s_score [MARK_FDEL ] = x_del;
   s_score [MARK_FADD ] = x_add;
   s_score [MARK_FUPD ] = x_upd;
   /*---(save-back)----------------------*/
   if (r_atype  != NULL)   *r_atype = x_atype;
   if (r_atdesc != NULL)   strlcpy (r_atdesc, x_atdesc, LEN_TERSE);
   if (r_del    != NULL)   *r_del   = x_del;
   if (r_add    != NULL)   *r_add   = x_add;
   if (r_upd    != NULL)   *r_upd   = x_upd;
   /*---(complete)-----------------------*/
   DEBUG_FILE    yLOG_exit    (__FUNCTION__);
   return rc_final;
}

char
yenv_audit_remove       (char a_full [LEN_PATH], char a_atype, char a_atdesc [LEN_TERSE], char c_force, char c_del)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(quick-out)----------------------*/
   if (a_atype == YENV_NONE) {
      DEBUG_FILE   yLOG_senter  (__FUNCTION__);
      DEBUG_FILE   yLOG_snote   ("does not exist, removal not required");
      DEBUG_FILE   yLOG_sexit   (__FUNCTION__);
      return RC_ACK;
   }
   if (c_del == '-') {
      DEBUG_FILE   yLOG_senter  (__FUNCTION__);
      DEBUG_FILE   yLOG_snote   ("no removal necessary");
      DEBUG_FILE   yLOG_sexit   (__FUNCTION__);
      return RC_ACK;
   }
   /*---(header)-------------------------*/
   DEBUG_FILE   yLOG_enter   (__FUNCTION__);
   s_score [MARK_REMOVE] = '°';
   /*---(does not exist)-----------------*/
   rc = yENV_exists (a_full);
   DEBUG_FILE   yLOG_complex ("exists"    , "%d/%c", rc, rc);
   --rce;  if (rc < 0 || rc == YENV_NONE) {
      yURG_err ('w', "%s (%c) removal skipped, entry does not exist" , a_atdesc, a_atype);
      DEBUG_FILE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(critical removals)--------------*/
   if (c_del == '!') {
      if (c_force == '!') {
         rc = yENV_removier (a_atype, a_full);
         --rce;  if (rc != YENV_NONE) {
            yURG_err ('f', "%s (%c) requested removal (%c) failed (%d/%c)" , a_atdesc, a_atype, c_del, rc, rc);
            DEBUG_FILE   yLOG_exitr   (__FUNCTION__, rce);
            return rce;
         }
      } else {
         yURG_err ('f', "%s (%c) requested removal (%c) requires critical force (!), but used (%c)" , a_atdesc, a_atype, c_del, c_force);
         DEBUG_FILE   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
   }
   /*---(normal removals)----------------*/
   else {
      if (c_force != '-') {
         rc = yENV_removier (a_atype, a_full);
         --rce;  if (rc != YENV_NONE) {
            yURG_err ('f', "%s (%c) requested removal (%c) failed (%d/%c)" , a_atdesc, a_atype, c_del, rc, rc);
            DEBUG_FILE   yLOG_exitr   (__FUNCTION__, rce);
            return rce;
         }
      } else {
         yURG_err ('f', "%s (%c) requested removal (%c) requires any force (!y), but used (%c)" , a_atdesc, a_atype, c_del, c_force);
         DEBUG_FILE   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
   }
   /*---(message)------------------------*/
   s_score [MARK_REMOVE] = 'R';
   yURG_msg ('-', "%s (%c) entry removed successfully because of force flag (%c)", a_atdesc, a_atype, c_force);
   /*---(complete)-----------------------*/
   DEBUG_FILE    yLOG_exit    (__FUNCTION__);
   return RC_POSITIVE;
}

char
yenv_audit_create       (char a_full [LEN_PATH], char a_etype, char a_etdesc [LEN_TERSE], char a_eowner [LEN_USER], char a_egroup [LEN_USER], char a_eperms [LEN_TERSE], int a_emajor, int a_eminor, char a_etarget [LEN_PATH], char c_force, char c_add)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_tdesc     [LEN_TERSE] = "";
   /*---(quick-out)----------------------*/
   if (a_etype == YENV_NONE) {
      DEBUG_FILE   yLOG_senter  (__FUNCTION__);
      DEBUG_FILE   yLOG_snote   ("requested non-exist, creation not required");
      DEBUG_FILE   yLOG_sexit   (__FUNCTION__);
      return RC_ACK;
   }
   if (c_add == '-') {
      DEBUG_FILE   yLOG_senter  (__FUNCTION__);
      DEBUG_FILE   yLOG_snote   ("no creation necessary");
      DEBUG_FILE   yLOG_sexit   (__FUNCTION__);
      return RC_ACK;
   }
   /*---(header)-------------------------*/
   DEBUG_FILE   yLOG_enter   (__FUNCTION__);
   s_score [MARK_CREATE] = '°';
   /*---(already exists)-----------------*/
   rc = yENV_exists (a_full);
   DEBUG_FILE   yLOG_complex ("exists"    , "%d/%c", rc, rc);
   --rce;  if (rc != YENV_NONE) {
      strlcpy (x_tdesc, yENV_typedesc (rc), LEN_TERSE);
      yURG_err ('f', "%s (%c) creation stopped, FOUND it as %s (%c) already" , a_etdesc, a_etype, x_tdesc, rc);
      DEBUG_FILE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(additions)----------------------*/
   if (c_force != '-') {
      rc = yENV_touchier (a_etype, a_full, a_eowner, a_egroup, a_eperms, a_emajor, a_eminor, a_etarget);
      DEBUG_FILE   yLOG_complex ("touch"     , "%d/%c", rc, rc);
      --rce;  if (rc < 0 || rc == YENV_NONE) {
         yURG_err ('f', "%s (%c) requested creation (%c) failed (%d/%c)" , a_etdesc, a_etype, c_add, rc, rc);
         DEBUG_FILE   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
   } else {
      yURG_err ('f', "%s (%c) requested creation (%c) requires any force (!y), but used (%c)" , a_etdesc, a_etype, c_add, c_force);
      DEBUG_FILE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(message)------------------------*/
   s_score [MARK_CREATE] = 'C';
   yURG_msg ('-', "%s (%c) entry created successfully because of force flag (%c)", a_etdesc, a_etype, c_force);
   /*---(complete)-----------------------*/
   DEBUG_FILE    yLOG_exit    (__FUNCTION__);
   return RC_POSITIVE;
}

char
yenv_audit_update       (char a_full [LEN_PATH], char a_atype, char a_atdesc [LEN_TERSE], char a_eowner [LEN_USER], char a_egroup [LEN_USER], char a_eperms [LEN_TERSE], int a_emajor, int a_eminor, char a_etarget [LEN_PATH], char c_fix, char c_upd)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(quick-out)----------------------*/
   if (a_atype == YENV_NONE) {
      DEBUG_FILE   yLOG_senter  (__FUNCTION__);
      DEBUG_FILE   yLOG_snote   ("requested non-exist, update not required");
      DEBUG_FILE   yLOG_sexit   (__FUNCTION__);
      return RC_ACK;
   }
   if (c_upd == '-') {
      DEBUG_FILE   yLOG_senter  (__FUNCTION__);
      DEBUG_FILE   yLOG_snote   ("no update necessary");
      DEBUG_FILE   yLOG_sexit   (__FUNCTION__);
      return RC_ACK;
   }
   /*---(header)-------------------------*/
   DEBUG_FILE   yLOG_enter   (__FUNCTION__);
   s_score [MARK_UPDATE] = '°';
   /*---(does not exist)-----------------*/
   rc = yENV_exists (a_full);
   DEBUG_FILE   yLOG_complex ("exists"    , "%d/%c", rc, rc);
   --rce;  if (rc < 0 || rc == YENV_NONE) {
      yURG_err ('f', "%s (%c) update stopped, does not exist" , a_atdesc, a_atype);
      DEBUG_FILE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(update)-------------------------*/
   if (c_fix != '-') {
      rc = yENV_touchier (a_atype, a_full, a_eowner, a_egroup, a_eperms, a_emajor, a_eminor, a_etarget);
      DEBUG_FILE   yLOG_complex ("touch"     , "%d/%c", rc, rc);
      --rce;  if (rc < 0 || rc == YENV_NONE) {
         yURG_err ('f', "%s (%c) requested update (%c) failed (%d/%c)" , a_atdesc, a_atype, c_upd, rc, rc);
         DEBUG_FILE   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
   } else {
      yURG_err ('f', "%s (%c) requested update (%c) requires fix (y), but used (%c)" , a_atdesc, a_atype, c_upd, c_fix);
      DEBUG_FILE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(message)------------------------*/
   s_score [MARK_UPDATE] = 'U';
   yURG_msg ('-', "%s (%c) entry updated successfully because of fix flag (%c)", a_atdesc, a_atype, c_fix);
   /*---(complete)-----------------------*/
   DEBUG_FILE    yLOG_exit    (__FUNCTION__);
   return RC_POSITIVE;
}

char
yenv_audit_typing       (char a_etype, char a_etdesc [LEN_TERSE], char a_atype, char a_atdesc [LEN_TERSE])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   /*---(defense)----------+-----+-----+-*/
   --rce;  if (a_etype  == 0)     return rce;
   --rce;  if (a_etdesc == NULL)  return rce;
   --rce;  if (a_atype  == 0)     return rce;
   --rce;  if (a_atdesc == NULL)  return rce;
   /*---(prepare)------------------------*/
   s_score [MARK_RTYPE]  = '°';
   /*---(non-existance)------------------*/
   if (a_atype == YENV_NONE) {
      if (a_etype == YENV_NONE) {
         s_score [MARK_RTYPE]  = a_atype;
         yURG_msg ('-', "non-existance of filesystem entry confirmed");
         return RC_POSITIVE;
      } else {
         yURG_err ('f', "%s (%c) entry does not exist, AND not in FORCE mode"     , a_etdesc, a_etype);
         return RC_FATAL;
      }
   }
   /*---(match)--------------------------*/
   if (a_atype == a_etype) {
      s_score [MARK_RTYPE]  = a_atype;
      switch (a_atype) {
      case YENV_SYM  :
         yURG_msg ('-', "%s (%c) entry existance confirmed, AND not a normal/hardlink"  , a_etdesc, a_etype);
         return RC_ACK;
         break;
      case YENV_HARD :
         yURG_msg ('-', "%s (%c) entry existance confirmed, AND not a normal/symlink"   , a_etdesc, a_etype);
         return RC_ACK;
         break;
      default        :
         yURG_msg ('-', "%s (%c) entry existance confirmed, AND not a symlink/hardlink", a_etdesc, a_etype);
         return RC_ACK;
         break;
      }
   }
   /*---(not-matched)--------------------*/
   yURG_err ('f', "wanted %s (%c) entry ACTUALLY refers to a %s (%c)", a_etdesc, a_etype, a_atdesc, a_atype);
   return RC_FATAL;
}

char
yenv_audit_final        (char a_full [LEN_PATH], char a_etype, char a_etdesc [LEN_TERSE], char a_eowner [LEN_USER], char a_egroup [LEN_USER], char a_eperms [LEN_TERSE], int a_euid, int a_egid, int a_eprm, char a_adisp [LEN_LABEL], int a_emajor, int a_eminor, char a_ettype, char a_etarget [LEN_PATH])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        rc_final    = RC_POSITIVE;
   char        x_atype     = YENV_NONE;
   char        x_atdesc    [LEN_TERSE] = "";
   char        x_aowner    [LEN_USER]  = "";
   char        x_agroup    [LEN_USER]  = "";
   char        x_aperms    [LEN_TERSE] = "";
   int         x_auid      =    0;
   int         x_agid      =    0;
   uint        x_aprm      =    0;
   char        x_adisp     [LEN_LABEL] = "";
   int         x_amajor    =   -1;
   int         x_aminor    =   -1;
   char        x_atarget     [LEN_PATH]  = "";
   int         x_inode     =   -1;
   int         n           =   -1;
   /*---(header)-------------------------*/
   DEBUG_FILE   yLOG_enter   (__FUNCTION__);
   /*---(re-gather data)-----------------*/
   DEBUG_FILE   yLOG_note    ("re-gathering data");
   x_atype = yENV_detail (a_full, x_atdesc, &x_auid, x_aowner, &x_agid, x_agroup, &x_aprm, x_aperms, x_adisp, NULL, NULL, &x_amajor, &x_aminor, x_atarget, NULL, &x_inode, NULL);
   DEBUG_FILE   yLOG_value   ("detail"    , x_atype);
   --rce;  if (x_atype <= 0) {
      s_score [MARK_RECHECK] = '°';
      s_score [MARK_FINAL  ] = '°';
      yURG_err ('f', "file check generated a hard error (%d)", x_atype);
      DEBUG_FILE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_FILE   yLOG_char    ("detail"    , x_atype);
   /*---(existance check)----------------*/
   DEBUG_FILE   yLOG_note    ("conducting final-check");
   rc = yenv_audit_typing (a_etype, a_etdesc, x_atype, x_atdesc);
   DEBUG_FILE   yLOG_value   ("typing"    , rc);
   if (rc == RC_POSITIVE) {
      s_score [MARK_RECHECK] = '=';
      s_score [MARK_FINAL  ] = 'Y';
      DEBUG_FILE   yLOG_exit    (__FUNCTION__);
      return RC_POSITIVE;
   }
   if (rc == RC_FATAL) {
      s_score [MARK_RECHECK] = '°';
      s_score [MARK_FINAL  ] = '°';
      DEBUG_FILE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(major/minor)--------------------*/
   DEBUG_FILE   yLOG_complex ("device"    , "act %d:%d, exp %d:%d", x_amajor, x_aminor, a_emajor, a_eminor);
   --rce;  if (strchr ("bc", x_atype) != NULL) {
      s_score [MARK_RMAJOR] = 'j';
      if (x_amajor != a_emajor) {
         s_score [MARK_RMAJOR] = '°';
         yURG_err ('f', "device id (%d:%d); BUT expected (%d:%d)", x_amajor, x_aminor, a_emajor, a_eminor);
         rc_final = rce;
      }
      s_score [MARK_RMINOR] = 'n';
      if (x_aminor != a_eminor) {
         s_score [MARK_RMINOR] = '°';
         yURG_err ('f', "device id (%d:%d); BUT expected (%d:%d)", x_amajor, x_aminor, a_emajor, a_eminor);
         rc_final = rce;
      }
   }
   /*---(symlink)------------------------*/
   DEBUG_FILE   yLOG_info    ("target act", x_atarget);
   DEBUG_FILE   yLOG_info    ("target exp", a_etarget);
   --rce;  if (x_atype == YENV_SYM) { 
      s_score [MARK_RTTYPE ] = '°';
      s_score [MARK_RTARGET] = '°';
      if (x_atarget != NULL && a_etarget != NULL) {
         /*---(type/exist)---------------*/
         rc = yENV_detail (x_atarget, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
         if (rc == YENV_NONE) {
            yURG_err ('f', "symlink target does not exist");
            rc_final = rce;
         } else if (rc != a_ettype) {
            yURG_err ('f', "symlink target actual type (%c) does not match expected (%c)", rc, a_ettype);
            rc_final = rce;
         } else {
            s_score [MARK_RTTYPE ] = rc;
         }
         /*---(target)-------------------*/
         if (strcmp (x_atarget, a_etarget) == 0) {
            s_score [MARK_RTARGET] = 't';
         } else {
            yURG_err ('f', "symlink %2då%-30.30s]; BUT expected %2då%-30.30sæ", strlen (x_atarget), x_atarget, strlen (a_etarget), a_etarget);
            rc_final = rce;
         }
         /*---(done)---------------------*/
      }
   }
   /*---(hardlink)-----------------------*/
   --rce;  if (x_atype == YENV_HARD) { 
      s_score [MARK_RTTYPE ] = '°';
      s_score [MARK_RTARGET] = '°';
      if (x_atarget != NULL && a_etarget != NULL) {
         rc = yENV_detail (x_atarget, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
         /*---(type/exist)---------------*/
         rc = yENV_detail (x_atarget, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
         if (rc == YENV_NONE) {
            yURG_err ('f', "hardlink target does not exist");
            rc_final = rce;
         } else if (rc != a_ettype) {
            yURG_err ('f', "hardlink target actual type (%c) does not match expected (%c)", rc, a_ettype);
            rc_final = rce;
         } else {
            if (a_ettype == YENV_REG && rc == YENV_HARD)  s_score [MARK_RTTYPE] = YENV_REG;
            else                                          s_score [MARK_RTTYPE] = rc;
         }
         /*---(target)-------------------*/
         rc = yENV_detail (a_etarget, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, &n, NULL);
         if (x_inode == n) {
            s_score [MARK_RTARGET] = 't';
         } else {
            yURG_err ('f', "hardlink %2då%-30.30s] idode is (%d); BUT actually points at inode (%d)", strlen (a_etarget), a_etarget, n, x_inode);
            rc_final = rce;
         }
      }
   }
   /*---(owner)--------------------------*/
   DEBUG_FILE   yLOG_complex ("owner"     , "act %s, exp %s", x_aowner, a_eowner);
   s_score [MARK_ROWNER] = '°';
   --rce;  if (strcmp (x_aowner, a_eowner) != 0) {
      yURG_err ('f', "owned by å%sæ (%d); BUT expected å%sæ (%d)", x_aowner, x_auid, a_eowner, a_euid);
      rc_final = rce;
   } else {
      s_score [MARK_ROWNER] = 'o';
   }
   /*---(group)--------------------------*/
   DEBUG_FILE   yLOG_complex ("group"     , "act %s, ext %s", x_agroup, a_egroup);
   s_score [MARK_RGROUP] = '°';
   --rce;  if (strcmp (x_agroup, a_egroup) != 0) {
      yURG_err ('f', "grouped in å%sæ (%d); BUT expected å%sæ (%d)", x_agroup, x_agid, a_egroup, a_egid);
      rc_final = rce;
   } else {
      s_score [MARK_RGROUP] = 'g';
   }
   /*---(owner/group summary)------------*/
   if (s_score [MARK_ROWNER] == 'o' && s_score [MARK_RGROUP] == 'g') {
      yURG_msg ('-', "ownership confirmed, owned by å%sæ (%d) and in group å%sæ (%d)", a_eowner, a_euid, a_egroup, a_egid);
   }
   /*---(perms)--------------------------*/
   DEBUG_FILE   yLOG_complex ("perms"     , "act %s, ext %s", x_aperms, a_eperms);
   s_score [MARK_RPERMS] = '°';
   --rce;  if (strcmp (x_aperms, a_eperms) != 0) {
      yURG_err ('f', "permissions å%sæ, %04o, disp å%sæ; BUT expected å%sæ, %04o, disp å%sæ", x_aperms, x_aprm, x_adisp, a_eperms, a_eprm, a_adisp);
      rc_final = rce;
   } else {
      s_score [MARK_RPERMS] = 'p';
      yURG_msg ('-', "permissions confirmed, å%sæ, %04o, disp å%sæ", a_eperms, a_eprm, a_adisp);
   }
   /*---(finalize)-----------------------*/
   if (rc_final < 0) {
      s_score [MARK_RECHECK] = '°';
      s_score [MARK_FINAL  ] = '°';
   } else {
      s_score [MARK_RECHECK] = '=';
      s_score [MARK_FINAL  ] = 'Y';
   }
   /*---(complete)-----------------------*/
   DEBUG_FILE    yLOG_exit    (__FUNCTION__);
   return rc_final;
}

/*> char                                                                                                                                                                                                                                                                                                                    <* 
 *> yenv_audit_actual       (char a_full [LEN_PATH], char a_etype, char a_etdesc [LEN_TERSE], char a_eowner [LEN_USER], char a_egroup [LEN_USER], char a_eperms [LEN_TERSE], int a_euid, int a_egid, int a_eprm, char a_adisp [LEN_LABEL], int a_emajor, int a_eminor, char a_elink [LEN_PATH], char c_force, char c_fix)   <* 
 *> {                                                                                                                                                                                                                                                                                                                       <* 
 *>    /+---(locals)-----------+-----+-----+-+/                                                                                                                                                                                                                                                                             <* 
 *>    char        rce         =  -10;                                                                                                                                                                                                                                                                                      <* 
 *>    char        rc          =    0;                                                                                                                                                                                                                                                                                      <* 
 *>    char        rc_final    = RC_POSITIVE;                                                                                                                                                                                                                                                                               <* 
 *>    char        x_atype     = YENV_NONE;                                                                                                                                                                                                                                                                                 <* 
 *>    char        x_atdesc    [LEN_TERSE] = "";                                                                                                                                                                                                                                                                            <* 
 *>    char        x_score     =    0;                                                                                                                                                                                                                                                                                      <* 
 *>    char        x_aowner    [LEN_USER]  = "";                                                                                                                                                                                                                                                                            <* 
 *>    char        x_agroup    [LEN_USER]  = "";                                                                                                                                                                                                                                                                            <* 
 *>    char        x_aperms    [LEN_TERSE] = "";                                                                                                                                                                                                                                                                            <* 
 *>    char        x_miss      [LEN_HUND]  = "";                                                                                                                                                                                                                                                                            <* 
 *>    int         x_auid      =    0;                                                                                                                                                                                                                                                                                      <* 
 *>    int         x_agid      =    0;                                                                                                                                                                                                                                                                                      <* 
 *>    uint        x_aprm      =    0;                                                                                                                                                                                                                                                                                      <* 
 *>    char        x_adisp     [LEN_LABEL] = "";                                                                                                                                                                                                                                                                            <* 
 *>    int         x_amajor    =   -1;                                                                                                                                                                                                                                                                                      <* 
 *>    int         x_aminor    =   -1;                                                                                                                                                                                                                                                                                      <* 
 *>    char        x_alink     [LEN_PATH]  = "";                                                                                                                                                                                                                                                                            <* 
 *>    int         l           =    0;                                                                                                                                                                                                                                                                                      <* 
 *>    /+---(header)-------------------------+/                                                                                                                                                                                                                                                                             <* 
 *>    DEBUG_FILE   yLOG_enter   (__FUNCTION__);                                                                                                                                                                                                                                                                            <* 
 *>    /+---(check)--------------------------+/                                                                                                                                                                                                                                                                             <* 
 *>    /+> if (c_force != '-' || c_fix != '-') {                                                                                            <*                                                                                                                                                                              <* 
 *>     *>    rc = yenv_audit_precheck  (a_full, a_etype, a_eowner, a_egroup, a_eperms, a_emajor, a_eminor, a_elink, &x_del, &x_add, &x_upd)   <*                                                                                                                                                                           <* 
 *>     *> }                                                                                                                                <+/                                                                                                                                                                             <* 
 *>                                                                                                                                                                                                                                                                                                                         <* 
 *>    x_atype = yENV_detail (a_full, x_atdesc, NULL, x_aowner, NULL, x_agroup, NULL, x_aperms, NULL, NULL, NULL, NULL, &x_amajor, &x_aminor, x_alink, NULL, NULL);                                                                                                                                                         <* 
 *>    DEBUG_FILE   yLOG_value   ("detail"    , x_atype);                                                                                                                                                                                                                                                                   <* 
 *>    --rce;  if (x_atype <= 0) {                                                                                                                                                                                                                                                                                          <* 
 *>       yURG_err ('f', "file check generated a hard error (%d)", x_atype);                                                                                                                                                                                                                                                <* 
 *>       DEBUG_FILE   yLOG_exitr   (__FUNCTION__, rce);                                                                                                                                                                                                                                                                    <* 
 *>       return rce;                                                                                                                                                                                                                                                                                                       <* 
 *>    }                                                                                                                                                                                                                                                                                                                    <* 
 *>    /+---(quick out)----------------------+/                                                                                                                                                                                                                                                                             <* 
 *>    DEBUG_FILE   yLOG_char    ("x_atype"   , x_atype);                                                                                                                                                                                                                                                                   <* 
 *>    if (x_atype == YENV_NONE && a_etype == YENV_NONE) {                                                                                                                                                                                                                                                                  <* 
 *>       yURG_msg ('-', "non-existance of filesystem entry confirmed");                                                                                                                                                                                                                                                    <* 
 *>       return RC_POSITIVE;                                                                                                                                                                                                                                                                                               <* 
 *>    }                                                                                                                                                                                                                                                                                                                    <* 
 *>    /+---(pre-check)----------------------+/                                                                                                                                                                                                                                                                             <* 
 *>    DEBUG_FILE   yLOG_complex ("pre-check" , "%c force, %c fix", c_force, c_fix);                                                                                                                                                                                                                                        <* 
 *>    x_score = 0;                                                                                                                                                                                                                                                                                                         <* 
 *>    --rce;  if (c_force != '-' || c_fix != '-') {                                                                                                                                                                                                                                                                        <* 
 *>       DEBUG_FILE   yLOG_note    ("conducting pre-check");                                                                                                                                                                                                                                                               <* 
 *>       if (x_atype == YENV_NONE)               { x_score += 16;  strcat (x_miss, "existance, "); }                                                                                                                                                                                                                       <* 
 *>       if (x_atype != a_etype)                 { x_score +=  8;  strcat (x_miss, "type, " ); }                                                                                                                                                                                                                           <* 
 *>       if (strcmp (x_aowner, a_eowner) != 0)   { x_score +=  4;  strcat (x_miss, "owner, "); }                                                                                                                                                                                                                           <* 
 *>       if (strcmp (x_agroup, a_egroup) != 0)   { x_score +=  2;  strcat (x_miss, "group, "); }                                                                                                                                                                                                                           <* 
 *>       if (strcmp (x_aperms, a_eperms) != 0)   { x_score +=  1;  strcat (x_miss, "perms, "); }                                                                                                                                                                                                                           <* 
 *>       l = strlen (x_miss);                                                                                                                                                                                                                                                                                              <* 
 *>       if (l > 2)  x_miss [l - 2] = '\0';                                                                                                                                                                                                                                                                                <* 
 *>       if      (x_score >= 16)  yURG_err ('w', "troubles with entry existance (so everything)");                                                                                                                                                                                                                         <* 
 *>       else if (x_score >   0)  yURG_err ('w', "troubles with entry %s", x_miss);                                                                                                                                                                                                                                        <* 
 *>    }                                                                                                                                                                                                                                                                                                                    <* 
 *>    DEBUG_FILE   yLOG_value   ("x_score"   , x_score);                                                                                                                                                                                                                                                                   <* 
 *>    /+---(removal)------------------------+/                                                                                                                                                                                                                                                                             <* 
 *>    /+> if (x_score >= 16) {                                                                                                                 <*                                                                                                                                                                          <* 
 *>     *>    if (c_force == '!') {                                                                                                             <*                                                                                                                                                                          <* 
 *>     *>       if (x_atype != a_etype) {                                                                                                      <*                                                                                                                                                                          <* 
 *>     *>          yURG_err ('f', "wanted %s (%c) ACTUALLY refers to a %s (%c), won't force removal", a_etdesc, a_etype, a_atdesc, a_atype);   <*                                                                                                                                                                          <* 
 *>     *>          DEBUG_FILE   yLOG_exitr   (__FUNCTION__, rce);                                                                              <*                                                                                                                                                                          <* 
 *>     *>          return rce;                                                                                                                 <*                                                                                                                                                                          <* 
 *>     *>       }                                                                                                                              <*                                                                                                                                                                          <* 
 *>     *>       rc = yENV_removier (x_atype, x_full);                                                                                          <*                                                                                                                                                                          <* 
 *>     *>       DEBUG_FILE   yLOG_char    ("exists"    , rc);                                                                                  <*                                                                                                                                                                          <* 
 *>     *>       --rce;  if (rc < 0 || rc != a_etype) {                                                                                         <*                                                                                                                                                                          <* 
 *>     *>          yURG_err ('f', "%s (%c) removal failed (%d/%c), check return code", x_atdesc, x_atype, rc, rc);                             <*                                                                                                                                                                          <* 
 *>     *>          DEBUG_FILE   yLOG_exitr   (__FUNCTION__, rce);                                                                              <*                                                                                                                                                                          <* 
*>     *>          return rce;                                                                                                                 <*                                                                                                                                                                          <* 
*>     *>       }                                                                                                                              <*                                                                                                                                                                          <* 
*>     *>       /+---(message)------------------------+/                                                                                       <*                                                                                                                                                                          <* 
*>     *>       yURG_msg ('-', "%s (%c) entry removed successfully", a_atdesc, a_atype);                                                       <*                                                                                                                                                                          <* 
*>     *>    }                                                                                                                                 <*                                                                                                                                                                          <* 
*>     *> }                                                                                                                                    <+/                                                                                                                                                                         <* 
*>    /+---(creation)-----------------------+/                                                                                                                                                                                                                                                                             <* 
*>    /+> --rce;  if (x_score >= 16) {                                                   <*                                                                                                                                                                                                                                <* 
   *>     *>    if (c_force != 'y') {                                                       <*                                                                                                                                                                                                                                <* 
      *>     *>       yURG_err ('f', "file does not exist, and not in FORCE mode");            <*                                                                                                                                                                                                                                <* 
         *>     *>       DEBUG_FILE   yLOG_exitr   (__FUNCTION__, rce);                           <*                                                                                                                                                                                                                                <* 
         *>     *>       return rce;                                                              <*                                                                                                                                                                                                                                <* 
         *>     *>    }                                                                           <*                                                                                                                                                                                                                                <* 
         *>     *>    rc = yENV_touch (a_full, a_eowner, a_egroup, a_eperms);                     <*                                                                                                                                                                                                                                <* 
         *>     *>    DEBUG_FILE   yLOG_value   ("force"     , rc);                               <*                                                                                                                                                                                                                                <* 
         *>     *>    if (rc <= 0) {                                                              <*                                                                                                                                                                                                                                <* 
            *>     *>       yURG_err ('f', "file creation generated a hard error (%d)", rc);         <*                                                                                                                                                                                                                                <* 
               *>     *>       DEBUG_FILE   yLOG_exitr   (__FUNCTION__, rce);                           <*                                                                                                                                                                                                                                <* 
               *>     *>       return rce;                                                              <*                                                                                                                                                                                                                                <* 
               *>     *>    }                                                                           <*                                                                                                                                                                                                                                <* 
               *>     *>    rc_final = RC_REPAIR;                                                       <*                                                                                                                                                                                                                                <* 
               *>     *>    yURG_msg ('-', "system called in FORCE mode, so file created");             <*                                                                                                                                                                                                                                <* 
               *>     *> }                                                                              <*                                                                                                                                                                                                                                <* 
               *>     *> else if (x_score > 0) {                                                        <*                                                                                                                                                                                                                                <* 
                  *>     *>    if (c_fix == 'y') {                                                         <*                                                                                                                                                                                                                                <* 
                     *>     *>       rc = yENV_touch (a_full, a_eowner, a_egroup, a_eperms);                  <*                                                                                                                                                                                                                                <* 
                        *>     *>       DEBUG_FILE   yLOG_value   ("fix"       , rc);                            <*                                                                                                                                                                                                                                <* 
                        *>     *>       if (rc <= 0) {                                                           <*                                                                                                                                                                                                                                <* 
                           *>     *>          yURG_err ('f', "file creation generated a hard error (%d)", rc);      <*                                                                                                                                                                                                                                <* 
                              *>     *>          DEBUG_FILE   yLOG_exitr   (__FUNCTION__, rce);                        <*                                                                                                                                                                                                                                <* 
                              *>     *>          return rce;                                                           <*                                                                                                                                                                                                                                <* 
                              *>     *>       }                                                                        <*                                                                                                                                                                                                                                <* 
                              *>     *>       rc_final = RC_REPAIR;                                                    <*                                                                                                                                                                                                                                <* 
                              *>     *>       yURG_msg ('-', "system called in FIX mode, so file updated");            <*                                                                                                                                                                                                                                <* 
                              *>     *>    }                                                                           <*                                                                                                                                                                                                                                <* 
                              *>     *> }                                                                              <+/                                                                                                                                                                                                                               <* 
                              *>    /+---(re-gather data)-----------------+/                                                                                                                                                                                                                                                                             <* 
                              *>    DEBUG_FILE   yLOG_note    ("re-gathering data");                                                                                                                                                                                                                                                                     <* 
                              *>    x_atype = yENV_detail (a_full, x_atdesc, &x_auid, x_aowner, &x_agid, x_agroup, &x_aprm, x_aperms, x_adisp, NULL, NULL, NULL, &x_amajor, &x_aminor, x_alink, NULL, NULL);                                                                                                                                             <* 
                              *>    DEBUG_FILE   yLOG_value   ("detail"    , x_atype);                                                                                                                                                                                                                                                                   <* 
                              *>    --rce;  if (x_atype <= 0) {                                                                                                                                                                                                                                                                                          <* 
                                 *>       yURG_err ('f', "file check generated a hard error (%d)", x_atype);                                                                                                                                                                                                                                                <* 
                                    *>       DEBUG_FILE   yLOG_exitr   (__FUNCTION__, rce);                                                                                                                                                                                                                                                                    <* 
                                    *>       return rce;                                                                                                                                                                                                                                                                                                       <* 
                                    *>    }                                                                                                                                                                                                                                                                                                                    <* 
                                    *>    DEBUG_FILE   yLOG_char    ("detail"    , x_atype);                                                                                                                                                                                                                                                                   <* 
                                    *>    /+---(existance check)----------------+/                                                                                                                                                                                                                                                                             <* 
                                    *>    DEBUG_FILE   yLOG_note    ("conducting final-check");                                                                                                                                                                                                                                                                <* 
                                    *>    rc = yenv_audit_typing (a_etype, a_etdesc, x_atype, x_atdesc);                                                                                                                                                                                                                                                       <* 
                                    *>    DEBUG_FILE   yLOG_value   ("typing"    , rc);                                                                                                                                                                                                                                                                        <* 
                                    *>    /+> switch (x_atype) {                                                                                                                <*                                                                                                                                                                             <* 
                                       *>     *> case YENV_NONE   : yURG_err ('f', "file does not exist, and not in FORCE mode"        );           rc_final = RC_FATAL;  break;   <*                                                                                                                                                                             <* 
                                          *>     *> case YENV_REG    : yURG_msg ('-', "file existance confirmed and is not a dir/symlink" );           break;                         <*                                                                                                                                                                             <* 
                                          *>     *> case YENV_DIR    : yURG_err ('f', "actually refers to a directory (bad configuration)");           rc_final = RC_FATAL;  break;   <*                                                                                                                                                                             <* 
                                          *>     *> case YENV_SYM    : yURG_err ('f', "actually refers to a symbolic link (security risk)");           rc_final = RC_FATAL;  break;   <*                                                                                                                                                                             <* 
                                          *>     *> default          : yURG_err ('f', "entry is specialty type (%c) (bad configuration)"  , x_atype);  rc_final = RC_FATAL;  break;   <*                                                                                                                                                                             <* 
                                          *>     *> }                                                                                                                                 <+/                                                                                                                                                                            <* 
                                          *>    if (rc == RC_POSITIVE) {                                                                                                                                                                                                                                                                                             <* 
                                             *>       DEBUG_FILE   yLOG_exit    (__FUNCTION__);                                                                                                                                                                                                                                                                         <* 
                                                *>       return RC_POSITIVE;                                                                                                                                                                                                                                                                                               <* 
                                                *>    }                                                                                                                                                                                                                                                                                                                    <* 
                                                *>    if (rc == RC_FATAL) {                                                                                                                                                                                                                                                                                                <* 
                                                   *>       DEBUG_FILE   yLOG_exitr   (__FUNCTION__, rce);                                                                                                                                                                                                                                                                    <* 
                                                      *>       return rce;                                                                                                                                                                                                                                                                                                       <* 
                                                      *>    }                                                                                                                                                                                                                                                                                                                    <* 
                                                      *>    /+> if (rc > rc_final)  rc_final = rc;                                             <+/                                                                                                                                                                                                                               <* 
                                                      *>    /+---(owner)--------------------------+/                                                                                                                                                                                                                                                                             <* 
                                                      *>    DEBUG_FILE   yLOG_complex ("owner"     , "act %s, exp %s", x_aowner, a_eowner);                                                                                                                                                                                                                                      <* 
                                                      *>    --rce;  if (strcmp (x_aowner, a_eowner) != 0) {                                                                                                                                                                                                                                                                      <* 
                                                         *>       yURG_err ('f', "owned by å%sæ (%d); BUT expected å%sæ (%d)", x_aowner, x_auid, a_eowner, a_euid);                                                                                                                                                                                                                 <* 
                                                            *>       DEBUG_FILE   yLOG_exitr   (__FUNCTION__, rce);                                                                                                                                                                                                                                                                    <* 
                                                            *>       return rce;                                                                                                                                                                                                                                                                                                       <* 
                                                            *>    }                                                                                                                                                                                                                                                                                                                    <* 
                                                            *>    /+---(group)--------------------------+/                                                                                                                                                                                                                                                                             <* 
                                                            *>    DEBUG_FILE   yLOG_complex ("group"     , "act %s, ext %s", x_agroup, a_egroup);                                                                                                                                                                                                                                      <* 
                                                            *>    --rce;  if (strcmp (x_agroup, a_egroup) != 0) {                                                                                                                                                                                                                                                                      <* 
                                                               *>       yURG_err ('f', "grouped in å%sæ (%d); BUT expected å%sæ (%d)", x_agroup, x_agid, a_egroup, a_egid);                                                                                                                                                                                                               <* 
                                                                  *>       DEBUG_FILE   yLOG_exitr   (__FUNCTION__, rce);                                                                                                                                                                                                                                                                    <* 
                                                                  *>       return rce;                                                                                                                                                                                                                                                                                                       <* 
                                                                  *>    }                                                                                                                                                                                                                                                                                                                    <* 
                                                                  *>    yURG_msg ('-', "ownership confirmed, owned by å%sæ (%d) and in group å%sæ (%d)", a_eowner, a_euid, a_egroup, a_egid);                                                                                                                                                                                                <* 
                                                                  *>    /+---(perms)--------------------------+/                                                                                                                                                                                                                                                                             <* 
                                                                  *>    DEBUG_FILE   yLOG_complex ("perms"     , "act %s, ext %s", x_aperms, a_eperms);                                                                                                                                                                                                                                      <* 
                                                                  *>    --rce;  if (strcmp (x_aperms, a_eperms) != 0) {                                                                                                                                                                                                                                                                      <* 
                                                                     *>       yURG_err ('f', "permissions å%sæ, %04o, disp å%sæ; BUT expected å%sæ, %04o, disp å%sæ", x_aperms, x_aprm, x_adisp, a_eperms, a_eprm, a_adisp);                                                                                                                                                                    <* 
                                                                        *>       DEBUG_FILE   yLOG_exitr   (__FUNCTION__, rce);                                                                                                                                                                                                                                                                    <* 
                                                                        *>       return rce;                                                                                                                                                                                                                                                                                                       <* 
                                                                        *>    }                                                                                                                                                                                                                                                                                                                    <* 
                                                                        *>    yURG_msg ('-', "permissions confirmed, å%sæ, %04o, disp å%sæ", a_eperms, a_eprm, a_adisp);                                                                                                                                                                                                                           <* 
                                                                        *>    /+---(complete)-----------------------+/                                                                                                                                                                                                                                                                             <* 
                                                                        *>    DEBUG_FILE    yLOG_exit    (__FUNCTION__);                                                                                                                                                                                                                                                                           <* 
                                                                        *>    return rc_final;                                                                                                                                                                                                                                                                                                     <* 
                                                                        *> }                                                                                                                                                                                                                                                                                                                       <*/

char
yENV_audit_full         (char a_type, char c_flag, char a_dir [LEN_PATH], char a_file [LEN_LABEL], char a_owner [LEN_USER], char a_group [LEN_USER], char a_perms [LEN_TERSE], int a_major, int a_minor, char a_ttype, char a_target [LEN_PATH], int a_epoch, long a_bytes, int a_inode, char a_hash [LEN_DESC], FILE **r_file)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        rc_final    = RC_POSITIVE;
   char        x_full      [LEN_PATH]  = "";
   char        x_atype     =  '-';
   char        x_atdesc    [LEN_TERSE] = "";
   char        x_etdesc    [LEN_TERSE] = "";
   char        x_mode      [LEN_SHORT] = "";
   char        x_note      [LEN_LABEL] = "";
   char        x_eowner    [LEN_USER]  = "";
   char        x_egroup    [LEN_USER]  = "";
   char        x_eperms    [LEN_TERSE] = "";
   int         x_euid      =   -1;
   int         x_egid      =   -1;
   int         x_eprm      =   -1;
   char        x_edisp      [LEN_LABEL] = "";
   char        c_check     =  '-';
   char        c_force     =  '-';
   char        c_fix       =  '-';
   char        x_del       =  '-';
   char        x_add       =  '-';
   char        x_upd       =  '-';
   /*---(header)-------------------------*/
   DEBUG_FILE   yLOG_enter   (__FUNCTION__);
   /*---(defaults)-----------------------*/
   if (a_owner != NULL)   strlcpy (x_eowner, a_owner, LEN_USER);
   if (a_group != NULL)   strlcpy (x_egroup, a_group, LEN_USER);
   if (a_perms != NULL)   strlcpy (x_eperms, a_perms, LEN_TERSE);
   /*---(prepare)------------------------*/
   rc = yenv_audit_prepare (a_type, c_flag, a_dir, a_file, '-', x_full, x_etdesc, x_mode, x_note, &c_check, &c_force, &c_fix);
   DEBUG_FILE   yLOG_value   ("prepare"   , rc);
   --rce;  if (rc < 0) {
      DEBUG_FILE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(expected)-----------------------*/
   rc = yenv_audit_expect   (x_eowner, x_egroup, x_eperms, &x_euid, &x_egid, &x_eprm, x_edisp);
   DEBUG_FILE   yLOG_value   ("expect"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_FILE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(extra)--------------------------*/
   rc = yenv_audit_extra    (a_type, a_major, a_minor, a_ttype, a_target, a_epoch, a_bytes, a_inode, a_hash);
   DEBUG_FILE   yLOG_value   ("extra"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_FILE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(precheck)-----------------------*/
   rc = yenv_audit_precheck (x_full, a_type, x_eowner, x_egroup, x_eperms, a_major, a_minor, a_ttype, a_target, &x_atype, x_atdesc, &x_del, &x_add, &x_upd, c_force, c_fix);
   DEBUG_FILE   yLOG_value   ("check"     , rc);
   if (rc < 0) {
      DEBUG_FILE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(remove)-------------------------*/
   rc = yenv_audit_remove   (x_full, x_atype, x_atdesc, c_force, x_del);
   DEBUG_FILE   yLOG_value   ("remove"    , rc);
   if (rc < 0) {
      DEBUG_FILE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(create)-------------------------*/
   rc = yenv_audit_create   (x_full, a_type, x_etdesc, x_eowner, x_egroup, x_eperms, a_major, a_minor, a_target, c_force, x_add);
   DEBUG_FILE   yLOG_value   ("create"    , rc);
   if (rc < 0) {
      DEBUG_FILE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(update)-------------------------*/
   rc = yenv_audit_update   (x_full, a_type, x_etdesc, x_eowner, x_egroup, x_eperms, a_major, a_minor, a_target, c_fix, x_upd);
   DEBUG_FILE   yLOG_value   ("update"    , rc);
   if (rc < 0) {
      DEBUG_FILE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(final check)--------------------*/
   rc = yenv_audit_final    (x_full, a_type, x_etdesc, x_eowner, x_egroup, x_eperms, x_euid, x_egid, x_eprm, x_edisp, a_major, a_minor, a_ttype, a_target);
   DEBUG_FILE   yLOG_value   ("final"     , rc);
   if (rc < 0) {
      DEBUG_FILE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_FILE    yLOG_exit    (__FUNCTION__);
   return rc;
}

char
yENV_audit              (char a_type, char c_flag, char a_dir [LEN_PATH], char a_file [LEN_LABEL], char a_owner [LEN_USER], char a_group [LEN_USER], char a_perms [LEN_TERSE], int a_major, int a_minor, char a_ttype, char a_target [LEN_PATH])
{
   return yENV_audit_full (YENV_REG  , c_flag, a_dir, a_file, a_owner, a_group, a_perms, a_major, a_minor, a_ttype, a_target, -1, -1, -1, "", NULL);
}

char
yENV_audit_reg          (char c_flag, char a_dir [LEN_PATH], char a_file [LEN_LABEL], char a_owner [LEN_USER], char a_group [LEN_USER], char a_perms [LEN_TERSE])
{
   return yENV_audit_full (YENV_REG  , c_flag, a_dir, a_file, a_owner, a_group, a_perms, -1, -1, YENV_NONE, "", -1, -1, -1, "", NULL);
}

char
yENV_audit_dir          (char c_flag, char a_dir [LEN_PATH], char a_owner [LEN_USER], char a_group [LEN_USER], char a_perms [LEN_TERSE])
{
   return yENV_audit_full (YENV_DIR  , c_flag, a_dir, "", a_owner, a_group, a_perms, -1, -1, YENV_NONE, "", -1, -1, -1, "", NULL);
}

char
yENV_audit_sym          (char c_flag, char a_dir [LEN_PATH], char a_file [LEN_LABEL], char a_ttype, char a_target [LEN_PATH])
{
   return yENV_audit_full (YENV_SYM  , c_flag, a_dir, a_file, "", "", "", -1, -1, a_ttype, a_target, -1, -1, -1, "", NULL);
}

char
yENV_audit_hard         (char c_flag, char a_dir [LEN_PATH], char a_file [LEN_LABEL], char a_ttype, char a_target [LEN_PATH])
{
   return yENV_audit_full (YENV_HARD , c_flag, a_dir, a_file, "", "", "", -1, -1, a_ttype, a_target, -1, -1, -1, "", NULL);
}


