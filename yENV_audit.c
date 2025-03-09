/*===[[ START ]]==============================================================*/
#include    "yENV.h"
#include    "yENV_priv.h"

/*                                               1         2         3         4         5         6         7         8         9            */
/*                                     -123456789-123456789-123456789-123456789-123456789-123456789-123456789-123456789-123456789-123456789   */
/*                                     -------request--------   cfg   ----check----   flg   -fix-   ---recheck---   f   hacked         */
static char s_blank     [LEN_HUND]  = "· ··· ··· ·· ·· ···· -   ···   · ··· ·· ·· -   ···   · · ·   · ··· ·· ·· -   Ï   ···· -";
char        g_score     [LEN_HUND]  = "d t·· ogp ·· ·· ···h y   ···   n --- ·· ··     ···   · · ·   n --- ·· ··     Ï   ···· Ï";

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

char* yENV_score      (void)  { return g_score; }
char  yENV_score_def  (void)  { strlcpy (g_score, s_blank, LEN_HUND); return 0; }



/*====================------------------------------------====================*/
/*===----                       subroutines                            ----===*/
/*====================------------------------------------====================*/
static void      o___PARTS______________o (void) {;}


/*
 *
 *  add prefix (user version too) and suffix test
 *
 *  add restriction to not hidden or temp (~)
 *
 *  should i have absolute vs relative checking also ?
 *     maybe that's what a_dir vs a_file is
 *     x_full must be absolute, a_file must be pathless
 *
 *  create call yENV_audit_yjobs that adds c_yjobs, a_prefix, a_suffix
 *     c_yjobs (y/-) triggers these specific checks
 *     ... char c_yjobs, char a_prefix [LEN_USER], a_suffix [LEN_USER]
 *
 *  add check for (yjobs) user name matching the directory home above
 *
 *  add check for (yjobs) that limits directories to /root/ and /home/(user)/
 *
 *  c_yjobs flag also triggers the additional verbosity in yURG_msg
 *
 *
 *
 *  maybe c_yjobs flag is actually c_naming, to signal name/dir checks...
 *     '-'  loose, meaning filenames can be anything (helps with themis/helios)
 *     'n'  normal YSTR_FILES checking, allows for singular suffix (like .gyges)
 *     's'  yjobs or other standard with prefix (with user), suffix, not hidden
 *
 *
 */

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
   DEBUG_YENV   yLOG_enter   (__FUNCTION__);
   /*---(initialize)---------------------*/
   strlcpy (g_score, s_blank, LEN_HUND);
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
   g_score [MARK_ETYPE] = '°';
   if (strcmp (x_tdesc, "WTF") != 0)   g_score [MARK_ETYPE] = a_type;
   /*---(defense)------------------------*/
   g_score [MARK_EFULL] = '£';
   DEBUG_YENV   yLOG_point   ("a_dir"     , a_dir);
   --rce;  if (a_dir       == NULL) {
      g_score [MARK_REQUEST] = '°';
      g_score [MARK_FINAL  ] = '°';
      DEBUG_YENV   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YENV   yLOG_info    ("a_dir"     , a_dir);
   DEBUG_YENV   yLOG_point   ("a_file"    , a_file);
   --rce;  if (a_file      == NULL) {
      g_score [MARK_REQUEST] = '°';
      g_score [MARK_FINAL  ] = '°';
      DEBUG_YENV   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YENV   yLOG_info    ("a_file"    , a_file);
   /*---(prepare full name)--------------*/
   g_score [MARK_EFULL] = '-';
   ld = strlen (a_dir);
   lf = strlen (a_file);
   DEBUG_YENV    yLOG_complex ("len"       , "ld=%d, lf=%d", ld, lf);
   if (ld + lf == 0) {
      g_score [MARK_REQUEST] = '°';
      g_score [MARK_FINAL  ] = '°';
      DEBUG_YENV   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   if (ld == 0)      sprintf (x_full, "%s", a_file);
   else if (lf == 0) sprintf (x_full, "%s", a_dir);
   else {
      if (a_dir [ld - 1] != '/')    sprintf (x_full, "%s/%s", a_dir, a_file);
      else                          sprintf (x_full, "%s%s" , a_dir, a_file);
   }
   DEBUG_YENV    yLOG_info    ("x_full"    , x_full);
   /*---(absolute)-----------------------*/
   g_score [MARK_EFULL] = '/';
   DEBUG_YENV    yLOG_char    ("x_full [0]", x_full [0]);
   --rce;  if (x_full [0] != '/') {
      yURG_err ('f', "full name must be absolute reference, i.e., start with '/'");
      DEBUG_YENV    yLOG_note    ("name must start with '/'");
      g_score [MARK_REQUEST] = '°';
      g_score [MARK_FINAL  ] = '°';
      DEBUG_YENV    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(check name quality)-------------*/
   g_score [MARK_EFULL] = '°';
   l = strlen (x_full);
   --rce;  for (i = 0; i < l; ++i) {
      if (strchr (YSTR_FILES, x_full [i]) == NULL) {
         yURG_err ('f', "full name has an illegal character (%c) at position %d (security risk)", x_full [i], i);
         DEBUG_YENV    yLOG_complex ("bad char"  , "can not include %c at %d", x_full [i], i);
         g_score [MARK_REQUEST] = '°';
         g_score [MARK_FINAL  ] = '°';
         DEBUG_YENV    yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
   }
   g_score [MARK_EFULL] = 'n';
   /*---(set mode)-----------------------*/
   DEBUG_YENV   yLOG_char    ("a_mode"    , a_mode);
   g_score [MARK_EMODE] = '°';
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
      DEBUG_YENV   yLOG_note    ("mode not understood");
      g_score [MARK_REQUEST] = '°';
      g_score [MARK_FINAL  ] = '°';
      DEBUG_YENV   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YENV   yLOG_info    ("x_mode"    , x_mode);
   g_score [MARK_EMODE] = 'm';
   /*---(flags)--------------------------*/
   g_score [MARK_EFLAG] = '°';
   switch (c_flag) {
   case '!' :  x_check = 'y';  x_force = '!';  x_fix   = 'y';  break;
   case 'F' :  x_check = 'y';  x_force = 'y';  x_fix   = 'y';  break;
   case 'f' :  x_check = 'y';  x_force = '-';  x_fix   = 'y';  break;
   case '-' :  x_check = '-';  x_force = '-';  x_fix   = '-';  break;
   default  :
               yURG_err ('f', "configuration flag (%c) is not legal (!Ff-) ", c_flag);
               DEBUG_YENV   yLOG_note    ("c_flag not understood");
               g_score [MARK_REQUEST] = '°';
               g_score [MARK_FINAL  ] = '°';
               DEBUG_YENV   yLOG_exitr   (__FUNCTION__, rce);
               return rce;
   }
   g_score [MARK_EFLAG] = 'f';
   g_score [MARK_CONFC] = x_check;
   g_score [MARK_CONFF] = x_force;
   g_score [MARK_CONFX] = x_fix;
   /*---(save-back)----------------------*/
   if (r_full  != NULL)  snprintf (r_full , LEN_PATH , "%s", x_full);
   if (r_tdesc != NULL)  snprintf (r_tdesc, LEN_TERSE, "%s", x_tdesc);
   if (r_mode  != NULL)  snprintf (r_mode , LEN_SHORT, "%s", x_mode);
   if (r_note  != NULL)  snprintf (r_note , LEN_LABEL, "%s", x_note);
   if (r_check != NULL)  *r_check = x_check;
   if (r_force != NULL)  *r_force = x_force;
   if (r_fix   != NULL)  *r_fix   = x_fix;
   /*---(complete)-----------------------*/
   DEBUG_YENV    yLOG_exit    (__FUNCTION__);
   return RC_POSITIVE;
}

char
yenv_audit_expect       (char a_type, char b_owner [LEN_USER], char b_group [LEN_USER], char b_perms [LEN_TERSE], int *r_uid, int *r_gid, int *r_prm, char r_disp [LEN_LABEL])
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
   char        x_handle    [LEN_LABEL] = "";
   char        t           [LEN_TERSE] = "";
   /*---(header)-------------------------*/
   DEBUG_YENV   yLOG_enter   (__FUNCTION__);
   /*---(quick-out)----------------------*/
   DEBUG_YENV   yLOG_char    ("a_type"    , a_type);
   if (a_type == YENV_NONE) {
      DEBUG_YENV    yLOG_note    ("nothing to do");
      DEBUG_YENV    yLOG_exit    (__FUNCTION__);
      return RC_ACK;
   }
   /*---(default)------------------------*/
   if (r_uid   != NULL)  *r_uid = -1;
   if (b_owner != NULL)  { snprintf (x_owner, LEN_USER , "%s", b_owner); strcpy (b_owner, ""); }
   if (r_gid   != NULL)  *r_gid = -1;
   if (b_group != NULL)  { snprintf (x_group, LEN_USER , "%s", b_group); strcpy (b_group, ""); }
   if (r_prm   != NULL)  *r_prm = -1;
   if (b_perms != NULL)  { snprintf (x_perms, LEN_TERSE, "%s", b_perms); strcpy (b_perms, ""); }
   if (r_disp  != NULL)  strcpy (r_disp , "");
   /*---(user ownership)-----------------*/
   g_score [MARK_EOWNER] = '-';
   --rce;  if (b_owner != NULL) {
      g_score [MARK_EOWNER] = '°';
      DEBUG_YENV   yLOG_info    ("x_owner"   , x_owner);
      strlcpy (t, x_owner, LEN_USER);
      rc = yENV_user_full  (a_type, t, x_owner, &x_uid, NULL, NULL, NULL, x_handle);
      if (rc >= 0) {
         if      (strcmp (t      , ""     ) == 0)  g_score [MARK_EOWNER] = 'O';  /* default  */
         else                                      g_score [MARK_EOWNER] = 'o';  /* standard */
      } else {
         yURG_err ('f', "could not interpret owner å%sæ using %s", t, x_handle);
         rc_final = rce;
      }
   }
   /*---(group ownership)----------------*/
   g_score [MARK_EGROUP] = '-';
   --rce;  if (b_group != NULL) {
      g_score [MARK_EGROUP] = '°';
      DEBUG_YENV   yLOG_info    ("x_group"   , x_group);
      strlcpy (t, x_group, LEN_USER);
      rc = yENV_group_full (a_type, t, x_group, &x_gid, x_handle);
      if (rc >= 0) {
         if      (strcmp (t      , ""     ) == 0)  g_score [MARK_EGROUP] = 'G';  /* default  */
         else                                      g_score [MARK_EGROUP] = 'g';  /* standard */
      } else {
         yURG_err ('f', "could not interpret group å%sæ using %s", t, x_handle);
         rc_final = rce;
      }
   }
   /*---(permissions)--------------------*/
   g_score [MARK_EPERMS] = '-';
   --rce;  if (b_perms != NULL) {
      g_score [MARK_EPERMS] = '°';
      DEBUG_YENV   yLOG_info    ("x_perms"   , x_perms);
      strlcpy (t, x_perms, LEN_TERSE);
      rc = yENV_perms_full (a_type, t, x_perms, &x_prm, x_disp, NULL, x_handle);
      if (rc >= 0) {
         if      (strcmp (t      , ""     ) == 0)  g_score [MARK_EPERMS] = 'P';  /* default  */
         else if (strcmp (x_perms, "(n/a)") == 0)  g_score [MARK_EPERMS] = 'P';  /* specific */
         else                                      g_score [MARK_EPERMS] = 'p';  /* standard */
      } else {
         yURG_err ('f', "could not interpret permissions å%sæ using %s", t, x_handle);
         rc_final = rce;
      }
   }
   /*---(save-back)----------------------*/
   if (strchr ("Oo", g_score [MARK_EOWNER]) != NULL) {
      if (r_uid   != NULL)  *r_uid = x_uid;
      if (b_owner != NULL)  snprintf (b_owner, LEN_USER , "%s", x_owner);
   }
   if (strchr ("Gg", g_score [MARK_EGROUP]) != NULL) {
      if (r_gid   != NULL)  *r_gid = x_gid;
      if (b_group != NULL)  snprintf (b_group, LEN_USER , "%s", x_group);
   }
   if (strchr ("Pp", g_score [MARK_EPERMS]) != NULL) {
      if (r_prm   != NULL)  *r_prm = x_prm;
      if (b_perms != NULL)  snprintf (b_perms, LEN_TERSE, "%s", x_perms);
      if (r_disp  != NULL)  snprintf (r_disp , LEN_LABEL, "%s", x_disp );
   }
   /*---(finalize)-----------------------*/
   if (rc_final < 0) {
      g_score [MARK_REQUEST] = '°';
      g_score [MARK_FINAL  ] = '°';
   }
   /*---(complete)-----------------------*/
   DEBUG_YENV    yLOG_exit    (__FUNCTION__);
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
   DEBUG_YENV   yLOG_enter   (__FUNCTION__);
   /*---(device nums)--------------------*/
   --rce;  if (strchr ("bc", a_type) != NULL) {
      if (a_major >= 0 && a_major <= 255)    g_score [MARK_EMAJOR] = 'j';
      else {
         g_score [MARK_EMAJOR] = '°';
         yURG_err ('f', "attempting to use illegal major device number (%d), expeced (0-255)", a_major);
         rc_final = rce;
      }
   } else if (a_major != -1){
      yURG_err ('w', "included superfluous major device number (%d)", a_major);
   }
   --rce;  if (strchr ("bc", a_type) != NULL) {
      if (a_minor >= 0 && a_minor <= 255)    g_score [MARK_EMINOR] = 'n';
      else {
         g_score [MARK_EMINOR] = '°';
         yURG_err ('f', "attempting to use illegal minor device number (%d), expeced (0-255)", a_minor);
         rc_final = rce;
      }
   } else if (a_minor != -1){
      yURG_err ('w', "included superfluous minor device number (%d)", a_minor);
   }
   /*---(target type)--------------------*/
   --rce;  if (strchr ("sh", a_type) != NULL) {
      strlcpy (x_tdesc, yENV_typedesc (a_ttype), LEN_TERSE);
      if (strcmp (x_tdesc, "WTF") != 0)   g_score [MARK_ETTYPE] = a_ttype;
      else {
         g_score [MARK_ETTYPE] = '°';
         yURG_err ('f', "attempting to use illegal target type %s (%c)", x_tdesc, a_ttype);
         rc_final = rce;
      }
   } else if (a_ttype != YENV_NONE){
      yURG_err ('w', "included superfluous target type (%d)", a_ttype);
   }
   --rce;  if (a_type == YENV_HARD) {
      if (a_ttype == 0 || strchr ("rh", a_ttype) == NULL) {
         strlcpy (x_tdesc, yENV_typedesc (a_ttype), LEN_TERSE);
         g_score [MARK_ETTYPE] = '°';
         yURG_err ('f', "attempting to use hardlink to illegal type %s (%c), only allow (rh)", x_tdesc, a_ttype);
         rc_final = rce;
      }
   }
   /*---(target name)--------------------*/
   --rce;  if (strchr ("sh", a_type) != NULL) {
      g_score [MARK_ETARGET] = '°';
      if (a_target != NULL && strcmp (a_target, "") != 0) {
         g_score [MARK_ETARGET] = '/';
         DEBUG_YENV    yLOG_char    ("a_target", a_target [0]);
         if (a_target [0] != '/') {
            yURG_err ('f', "target must be absolute reference, i.e., start with '/'");
            rc_final = rce;
         } else {
            l = strlen (a_target);
            g_score [MARK_ETARGET] = '#';
            x_bad = '-';
            --rce;  for (i = 0; i < l; ++i) {
               if (strchr (YSTR_FILES, a_target [i]) == NULL) {
                  yURG_err ('f', "target name has an illegal character (%c) at position %d", a_target [i], i);
                  rc_final = rce;
                  x_bad = 'y';
               }
            }
            if (x_bad != 'y')   g_score [MARK_ETARGET] = 't';
         }
      }
   } else  if (a_target != NULL && strcmp (a_target, "") != 0) {
      yURG_err ('w', "included superfluous target name å%sæ", a_target);
   }
   /*---(specialty)----------------------*/
   if (a_epoch > 0)                g_score [MARK_EEPOCH] = 'e';
   if (a_bytes > 0)                g_score [MARK_EBYTES] = 'b';
   if (a_inode > 0)                g_score [MARK_EINODE] = 'i';
   --rce;  if (a_hash != NULL && strcmp (a_hash, "") != 0) {
      g_score [MARK_EHASH] = '°';
      l = strlen (a_hash);
      if (l == 40) {
         g_score [MARK_EHASH] = '#';
         x_bad = '-';
         for (i = 0; i < l; ++i) {
            if (strchr (YSTR_HEXUP, a_hash [i]) == NULL) {
               yURG_err ('f', "hash code has an illegal character (%c) at position %d", a_hash [i], i);
               rc_final = rce;
               x_bad = 'y';
            }
         }
         if (x_bad != 'y')   g_score [MARK_EHASH] = 'h';
      } else {
         yURG_err ('f', "hash code is the wrong length (%d) vs standard (40)", l);
         rc_final = rce;
      }
   }
   /*---(finalize)-----------------------*/
   if (rc_final < 0) {
      g_score [MARK_REQUEST] = '°';
      g_score [MARK_FINAL  ] = '°';
   } else {
      g_score [MARK_REQUEST] = '=';
   }
   /*---(complete)-----------------------*/
   DEBUG_YENV    yLOG_exit    (__FUNCTION__);
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
   int         i           =    0;
   /*---(quick-out)----------------------*/
   if (c_force == '-' && c_fix == '-') {
      DEBUG_YENV   yLOG_senter  (__FUNCTION__);
      DEBUG_YENV   yLOG_snote   ("no precheck requested");
      for (i = MARK_CONFC;  i <= MARK_UPDATE;  ++i)  g_score [i] = '¬';
      DEBUG_YENV   yLOG_sexit   (__FUNCTION__);
      return RC_ACK;
   }
   /*---(header)-------------------------*/
   DEBUG_YENV   yLOG_enter   (__FUNCTION__);
   /*---(defaults))----------------------*/
   if (r_atype  != NULL)   *r_atype = '-';
   if (r_atdesc != NULL)   strcpy (r_atdesc, "");
   if (r_del    != NULL)   *r_del   = '-';
   if (r_add    != NULL)   *r_add   = '-';
   if (r_upd    != NULL)   *r_upd   = '-';
   /*---(get data)-----------------------*/
   x_atype = yENV_detail (a_full, x_atdesc, NULL, x_aowner, NULL, x_agroup, NULL, x_aperms, NULL, NULL, NULL, &x_amajor, &x_aminor, x_alink, NULL, &x_inode, NULL);
   DEBUG_YENV   yLOG_value   ("detail"    , x_atype);
   --rce;  if (x_atype <= 0) {
      yURG_err ('f', "file check generated a hard error (%d)", x_atype);
      DEBUG_YENV   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   g_score [MARK_CTYPE ] = x_atype;
   /*---(quick out)----------------------*/
   DEBUG_YENV   yLOG_char    ("x_atype"   , x_atype);
   if (x_atype == YENV_NONE && a_etype == YENV_NONE) {
      yURG_msg ('-', "non-existance of filesystem entry confirmed");
      return RC_POSITIVE;
   }
   /*---(existance)----------------------       ----del----; ----add----; ----upd----;*/
   if      (x_atype  == YENV_NONE)            {            ; x_add = 'y';            ;  strcat (x_miss, "non-existance, "); }
   else if (a_etype  == YENV_NONE)            { x_del = 'y';            ;            ;  strcat (x_miss, "existance, "); }
   /*---(type changes)-------------------       ----del----; ----add----; ----upd----;*/
   else if (x_atype  != a_etype) {
      g_score [MARK_CTYPE ] = toupper (x_atype);
      if (strchr ("hs", a_etype) != NULL &&
            strchr ("hs", x_atype) != NULL)   { x_del = 'y'; x_add = 'y';            ;  strcat (x_miss, "type, "     ); }
      else                                    { x_del = '!'; x_add = 'y';            ;  strcat (x_miss, "type, "     ); }
   }
   /*---(entry details)------------------       ----del----; ----add----; ----upd----;*/
   if (x_atype == a_etype) {
      switch (a_etype) {
      case YENV_BLOCK : case YENV_CHAR  :
         g_score [MARK_CMAJOR] = 'j';
         g_score [MARK_CMINOR] = 'n';
         if (x_amajor != a_emajor)            { x_del = 'y'; x_add = 'y';            ;  strcat (x_miss, "maj, "      );  g_score [MARK_CMAJOR] = 'J'; }
         if (x_aminor != a_eminor)            { x_del = 'y'; x_add = 'y';            ;  strcat (x_miss, "min, "      );  g_score [MARK_CMINOR] = 'N'; }
         break;
      case YENV_SYM   :
         rc = yENV_detail (a_etarget, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
         g_score [MARK_CTTYPE] = rc;
         if (rc != a_ettype)  g_score [MARK_CTTYPE] = toupper (rc);
         g_score [MARK_CTARGET] = 't';
         if (strcmp (x_alink, a_etarget) != 0) { x_del = 'y'; x_add = 'y';            ;  strcat (x_miss, "target, "   );  g_score [MARK_CTARGET] = 'T'; }
         break;
      case YENV_HARD  :
         rc = yENV_detail (a_etarget, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, &n, NULL);
         g_score [MARK_CTTYPE] = rc;
         if (rc != a_ettype) {
            if (a_ettype == YENV_REG && rc == YENV_HARD)  g_score [MARK_CTTYPE] = YENV_REG;
            else                                          g_score [MARK_CTTYPE] = toupper (rc);
         }
         g_score [MARK_CTARGET] = 't';
         if (x_inode != n)                    { x_del = 'y'; x_add = 'y';            ;  strcat (x_miss, "target, "   );  g_score [MARK_CTARGET] = 'T'; }
         break;
      }
   }
   /*---(small fixest)-------------------       ----del----; ----add----; ----upd----;*/
   if (x_atype == a_etype && x_add != 'y' && a_etype != YENV_SYM) {
      g_score [MARK_COWNER] = 'o';
      g_score [MARK_CGROUP] = 'g';
      g_score [MARK_CPERMS] = 'p';
      if (strcmp (x_aowner, a_eowner) != 0)   {            ;            ; x_upd = 'y';  strcat (x_miss, "owner, "    );  g_score [MARK_COWNER] = 'O'; }
      if (strcmp (x_agroup, a_egroup) != 0)   {            ;            ; x_upd = 'y';  strcat (x_miss, "group, "    );  g_score [MARK_CGROUP] = 'G'; }
      if (strcmp (x_aperms, a_eperms) != 0)   {            ;            ; x_upd = 'y';  strcat (x_miss, "perms, "    );  g_score [MARK_CPERMS] = 'P'; }
   }
   /*---(entry fixes)--------------------       ----del----; ----add----; ----upd----;*/
   l = strlen (x_miss);
   if (l > 0) {
      g_score [MARK_CHECK] = '!';
      if (l > 2)  x_miss [l - 2] = '\0';
      yURG_err ('w', "troubles with entry %s", x_miss);
      rc_final = RC_POSITIVE;
   } else {
      g_score [MARK_CHECK] = '=';
   }
   /*---(finalize)-----------------------*/
   g_score [MARK_FDEL ] = x_del;
   g_score [MARK_FADD ] = x_add;
   g_score [MARK_FUPD ] = x_upd;
   /*---(save-back)----------------------*/
   if (r_atype  != NULL)   *r_atype = x_atype;
   if (r_atdesc != NULL)   strlcpy (r_atdesc, x_atdesc, LEN_TERSE);
   if (r_del    != NULL)   *r_del   = x_del;
   if (r_add    != NULL)   *r_add   = x_add;
   if (r_upd    != NULL)   *r_upd   = x_upd;
   /*---(complete)-----------------------*/
   DEBUG_YENV    yLOG_exit    (__FUNCTION__);
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
      DEBUG_YENV   yLOG_senter  (__FUNCTION__);
      DEBUG_YENV   yLOG_snote   ("does not exist, removal not required");
      DEBUG_YENV   yLOG_sexit   (__FUNCTION__);
      return RC_ACK;
   }
   if (c_del == '-') {
      DEBUG_YENV   yLOG_senter  (__FUNCTION__);
      DEBUG_YENV   yLOG_snote   ("no removal necessary");
      DEBUG_YENV   yLOG_sexit   (__FUNCTION__);
      return RC_ACK;
   }
   /*---(header)-------------------------*/
   DEBUG_YENV   yLOG_enter   (__FUNCTION__);
   g_score [MARK_REMOVE] = '°';
   /*---(does not exist)-----------------*/
   rc = yENV_exists (a_full);
   DEBUG_YENV   yLOG_complex ("exists"    , "%d/%c", rc, rc);
   --rce;  if (rc < 0 || rc == YENV_NONE) {
      g_score [MARK_FINAL ] = '°';
      yURG_err ('w', "%s (%c) removal skipped, entry does not exist" , a_atdesc, a_atype);
      DEBUG_YENV   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(critical removals)--------------*/
   if (c_del == '!') {
      if (c_force == '!') {
         rc = yENV_removier (a_atype, a_full);
         --rce;  if (rc != YENV_NONE) {
            yURG_err ('f', "%s (%c) conflicting entry removal (%c) failed (%d/%c)" , a_atdesc, a_atype, c_del, rc, rc);
            g_score [MARK_FINAL ] = '°';
            DEBUG_YENV   yLOG_exitr   (__FUNCTION__, rce);
            return rce;
         }
      } else {
         yURG_err ('f', "%s (%c) conflicting entry removal (%c) requires critical force (!), but used (%c)" , a_atdesc, a_atype, c_del, c_force);
         g_score [MARK_FINAL ] = '°';
         DEBUG_YENV   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
   }
   /*---(normal removals)----------------*/
   else {
      if (c_force != '-') {
         rc = yENV_removier (a_atype, a_full);
         --rce;  if (rc != YENV_NONE) {
            yURG_err ('f', "%s (%c) conflicting entry removal (%c) failed (%d/%c)" , a_atdesc, a_atype, c_del, rc, rc);
            g_score [MARK_FINAL ] = '°';
            DEBUG_YENV   yLOG_exitr   (__FUNCTION__, rce);
            return rce;
         }
      } else {
         yURG_err ('f', "%s (%c) conflicting entry removal (%c) requires any force (!y), but used (%c)" , a_atdesc, a_atype, c_del, c_force);
         g_score [MARK_FINAL ] = '°';
         DEBUG_YENV   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
   }
   /*---(message)------------------------*/
   g_score [MARK_REMOVE] = 'R';
   yURG_msg ('-', "%s (%c) conflicting entry removed successfully because of force flag (%c)", a_atdesc, a_atype, c_force);
   /*---(complete)-----------------------*/
   DEBUG_YENV    yLOG_exit    (__FUNCTION__);
   return RC_REPAIR;
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
      DEBUG_YENV   yLOG_senter  (__FUNCTION__);
      DEBUG_YENV   yLOG_snote   ("requested non-exist, creation not required");
      DEBUG_YENV   yLOG_sexit   (__FUNCTION__);
      return RC_ACK;
   }
   if (c_add == '-') {
      DEBUG_YENV   yLOG_senter  (__FUNCTION__);
      DEBUG_YENV   yLOG_snote   ("no creation necessary");
      DEBUG_YENV   yLOG_sexit   (__FUNCTION__);
      return RC_ACK;
   }
   /*---(header)-------------------------*/
   DEBUG_YENV   yLOG_enter   (__FUNCTION__);
   g_score [MARK_CREATE] = '°';
   /*---(already exists)-----------------*/
   rc = yENV_exists (a_full);
   DEBUG_YENV   yLOG_complex ("exists"    , "%d/%c", rc, rc);
   --rce;  if (rc != YENV_NONE) {
      strlcpy (x_tdesc, yENV_typedesc (rc), LEN_TERSE);
      yURG_err ('f', "%s (%c) creation stopped, FOUND it as %s (%c) already" , a_etdesc, a_etype, x_tdesc, rc);
      g_score [MARK_FINAL ] = '°';
      DEBUG_YENV   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(additions)----------------------*/
   if (c_force != '-') {
      rc = yENV_touchier (a_etype, a_full, a_eowner, a_egroup, a_eperms, a_emajor, a_eminor, a_etarget);
      DEBUG_YENV   yLOG_complex ("touch"     , "%d/%c", rc, rc);
      --rce;  if (rc < 0 || rc == YENV_NONE) {
         yURG_err ('f', "%s (%c) requested creation (%c) failed (%d/%c)" , a_etdesc, a_etype, c_add, rc, rc);
         g_score [MARK_FINAL ] = '°';
         DEBUG_YENV   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
   } else {
      yURG_err ('f', "%s (%c) requested creation (%c) requires any force (!y), but used (%c)" , a_etdesc, a_etype, c_add, c_force);
      g_score [MARK_FINAL ] = '°';
      DEBUG_YENV   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(message)------------------------*/
   g_score [MARK_CREATE] = 'C';
   yURG_msg ('-', "%s (%c) entry created successfully because of force flag (%c)", a_etdesc, a_etype, c_force);
   /*---(complete)-----------------------*/
   DEBUG_YENV    yLOG_exit    (__FUNCTION__);
   return RC_REPAIR;
}

char
yenv_audit_update       (char a_full [LEN_PATH], char a_atype, char a_atdesc [LEN_TERSE], char a_eowner [LEN_USER], char a_egroup [LEN_USER], char a_eperms [LEN_TERSE], int a_emajor, int a_eminor, char a_etarget [LEN_PATH], char c_fix, char c_upd)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(quick-out)----------------------*/
   if (a_atype == YENV_NONE) {
      DEBUG_YENV   yLOG_senter  (__FUNCTION__);
      DEBUG_YENV   yLOG_snote   ("requested non-exist, update not required");
      DEBUG_YENV   yLOG_sexit   (__FUNCTION__);
      return RC_ACK;
   }
   if (c_upd == '-') {
      DEBUG_YENV   yLOG_senter  (__FUNCTION__);
      DEBUG_YENV   yLOG_snote   ("no update necessary");
      DEBUG_YENV   yLOG_sexit   (__FUNCTION__);
      return RC_ACK;
   }
   /*---(header)-------------------------*/
   DEBUG_YENV   yLOG_enter   (__FUNCTION__);
   g_score [MARK_UPDATE] = '°';
   /*---(does not exist)-----------------*/
   rc = yENV_exists (a_full);
   DEBUG_YENV   yLOG_complex ("exists"    , "%d/%c", rc, rc);
   --rce;  if (rc < 0 || rc == YENV_NONE) {
      g_score [MARK_FINAL ] = '°';
      yURG_err ('f', "%s (%c) update stopped, does not exist" , a_atdesc, a_atype);
      DEBUG_YENV   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(update)-------------------------*/
   if (c_fix != '-') {
      rc = yENV_touchier (a_atype, a_full, a_eowner, a_egroup, a_eperms, a_emajor, a_eminor, a_etarget);
      DEBUG_YENV   yLOG_complex ("touch"     , "%d/%c", rc, rc);
      --rce;  if (rc < 0 || rc == YENV_NONE) {
         g_score [MARK_FINAL ] = '°';
         yURG_err ('f', "%s (%c) requested update (%c) failed (%d/%c)" , a_atdesc, a_atype, c_upd, rc, rc);
         DEBUG_YENV   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
   } else {
      g_score [MARK_FINAL ] = '°';
      yURG_err ('f', "%s (%c) requested update (%c) requires fix (y), but used (%c)" , a_atdesc, a_atype, c_upd, c_fix);
      DEBUG_YENV   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(message)------------------------*/
   g_score [MARK_UPDATE] = 'U';
   yURG_msg ('-', "%s (%c) entry updated successfully because of fix flag (%c)", a_atdesc, a_atype, c_fix);
   /*---(complete)-----------------------*/
   DEBUG_YENV    yLOG_exit    (__FUNCTION__);
   return RC_REPAIR;
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
   g_score [MARK_RTYPE]  = '°';
   /*---(non-existance)------------------*/
   if (a_atype == YENV_NONE) {
      if (a_etype == YENV_NONE) {
         g_score [MARK_RTYPE]  = a_atype;
         yURG_msg ('-', "non-existance of filesystem entry confirmed");
         return RC_POSITIVE;
      } else {
         yURG_err ('f', "%s (%c) entry does not exist, AND not in FORCE mode"     , a_etdesc, a_etype);
         return RC_FAILED;
      }
   }
   /*---(match)--------------------------*/
   if (a_atype == a_etype) {
      g_score [MARK_RTYPE]  = a_atype;
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
   return RC_FAILED;
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
   DEBUG_YENV   yLOG_enter   (__FUNCTION__);
   /*---(re-gather data)-----------------*/
   DEBUG_YENV   yLOG_note    ("re-gathering data");
   x_atype = yENV_detail (a_full, x_atdesc, &x_auid, x_aowner, &x_agid, x_agroup, &x_aprm, x_aperms, x_adisp, NULL, NULL, &x_amajor, &x_aminor, x_atarget, NULL, &x_inode, NULL);
   DEBUG_YENV   yLOG_value   ("detail"    , x_atype);
   --rce;  if (x_atype <= 0) {
      g_score [MARK_RECHECK] = '°';
      g_score [MARK_FINAL  ] = '°';
      yURG_err ('f', "file check generated a hard error (%d)", x_atype);
      DEBUG_YENV   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YENV   yLOG_char    ("detail"    , x_atype);
   /*---(existance check)----------------*/
   DEBUG_YENV   yLOG_note    ("conducting final-check");
   rc = yenv_audit_typing (a_etype, a_etdesc, x_atype, x_atdesc);
   DEBUG_YENV   yLOG_value   ("typing"    , rc);
   if (rc == RC_POSITIVE) {
      g_score [MARK_RECHECK] = '=';
      g_score [MARK_FINAL  ] = 'Y';
      DEBUG_YENV   yLOG_exit    (__FUNCTION__);
      return RC_POSITIVE;
   }
   if (rc == RC_FAILED) {
      g_score [MARK_RECHECK] = '°';
      g_score [MARK_FINAL  ] = '°';
      DEBUG_YENV   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(major/minor)--------------------*/
   DEBUG_YENV   yLOG_complex ("device"    , "act %d:%d, exp %d:%d", x_amajor, x_aminor, a_emajor, a_eminor);
   --rce;  if (strchr ("bc", x_atype) != NULL) {
      g_score [MARK_RMAJOR] = 'j';
      if (x_amajor != a_emajor) {
         g_score [MARK_RMAJOR] = '°';
         yURG_err ('f', "device id (%d:%d); BUT expected (%d:%d)", x_amajor, x_aminor, a_emajor, a_eminor);
         rc_final = rce;
      }
      g_score [MARK_RMINOR] = 'n';
      if (x_aminor != a_eminor) {
         g_score [MARK_RMINOR] = '°';
         yURG_err ('f', "device id (%d:%d); BUT expected (%d:%d)", x_amajor, x_aminor, a_emajor, a_eminor);
         rc_final = rce;
      }
   }
   /*---(symlink)------------------------*/
   DEBUG_YENV   yLOG_info    ("target act", x_atarget);
   DEBUG_YENV   yLOG_info    ("target exp", a_etarget);
   --rce;  if (x_atype == YENV_SYM) { 
      g_score [MARK_RTTYPE ] = '°';
      g_score [MARK_RTARGET] = '°';
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
            g_score [MARK_RTTYPE ] = rc;
         }
         /*---(target)-------------------*/
         if (strcmp (x_atarget, a_etarget) == 0) {
            g_score [MARK_RTARGET] = 't';
         } else {
            yURG_err ('f', "symlink %2då%-30.30s]; BUT expected %2då%-30.30sæ", strlen (x_atarget), x_atarget, strlen (a_etarget), a_etarget);
            rc_final = rce;
         }
         /*---(done)---------------------*/
      }
   }
   /*---(hardlink)-----------------------*/
   --rce;  if (x_atype == YENV_HARD) { 
      g_score [MARK_RTTYPE ] = '°';
      g_score [MARK_RTARGET] = '°';
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
            if (a_ettype == YENV_REG && rc == YENV_HARD)  g_score [MARK_RTTYPE] = YENV_REG;
            else                                          g_score [MARK_RTTYPE] = rc;
         }
         /*---(target)-------------------*/
         rc = yENV_detail (a_etarget, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, &n, NULL);
         if (x_inode == n) {
            g_score [MARK_RTARGET] = 't';
         } else {
            yURG_err ('f', "hardlink %2då%-30.30s] idode is (%d); BUT actually points at inode (%d)", strlen (a_etarget), a_etarget, n, x_inode);
            rc_final = rce;
         }
      }
   }
   /*---(owner)--------------------------*/
   DEBUG_YENV   yLOG_complex ("owner"     , "act %s, exp %s", x_aowner, a_eowner);
   g_score [MARK_ROWNER] = '°';
   --rce;  if (strcmp (x_aowner, a_eowner) != 0) {
      yURG_err ('f', "owned by å%sæ (%d); BUT expected å%sæ (%d)", x_aowner, x_auid, a_eowner, a_euid);
      rc_final = rce;
   } else {
      g_score [MARK_ROWNER] = 'o';
   }
   /*---(group)--------------------------*/
   DEBUG_YENV   yLOG_complex ("group"     , "act %s, ext %s", x_agroup, a_egroup);
   g_score [MARK_RGROUP] = '°';
   --rce;  if (strcmp (x_agroup, a_egroup) != 0) {
      yURG_err ('f', "grouped in å%sæ (%d); BUT expected å%sæ (%d)", x_agroup, x_agid, a_egroup, a_egid);
      rc_final = rce;
   } else {
      g_score [MARK_RGROUP] = 'g';
   }
   /*---(owner/group summary)------------*/
   if (g_score [MARK_ROWNER] == 'o' && g_score [MARK_RGROUP] == 'g') {
      yURG_msg ('-', "ownership confirmed, owned by å%sæ (%d) and in group å%sæ (%d)", a_eowner, a_euid, a_egroup, a_egid);
   }
   /*---(perms)--------------------------*/
   DEBUG_YENV   yLOG_complex ("perms"     , "act %s, ext %s", x_aperms, a_eperms);
   g_score [MARK_RPERMS] = '°';
   --rce;  if (strcmp (x_aperms, a_eperms) != 0) {
      yURG_err ('f', "permissions å%sæ, %04o, disp å%sæ; BUT expected å%sæ, %04o, disp å%sæ", x_aperms, x_aprm, x_adisp, a_eperms, a_eprm, a_adisp);
      rc_final = rce;
   } else {
      g_score [MARK_RPERMS] = 'p';
      yURG_msg ('-', "permissions confirmed, å%sæ, %04o, disp å%sæ", a_eperms, a_eprm, a_adisp);
   }
   /*---(finalize)-----------------------*/
   if (rc_final < 0) {
      g_score [MARK_RECHECK] = '°';
      g_score [MARK_FINAL  ] = '°';
   } else {
      g_score [MARK_RECHECK] = '=';
      g_score [MARK_FINAL  ] = 'Y';
   }
   /*---(complete)-----------------------*/
   DEBUG_YENV    yLOG_exit    (__FUNCTION__);
   return rc_final;
}

char
yenv_audit_hacked       (char a_full [LEN_PATH], int a_epoch, long a_bytes, int a_inode, char a_hash [LEN_DESC])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        rc_final    = RC_POSITIVE;
   char        x_atype     = YENV_NONE;
   int         x_epoch     =   -1;
   int         x_bytes     =   -1;
   int         x_inode     =   -1;
   char        x_hash      [LEN_DESC]  = "";
   char        c           =    0;
   /*---(header)-------------------------*/
   DEBUG_YENV   yLOG_enter   (__FUNCTION__);
   /*---(re-gather data)-----------------*/
   DEBUG_YENV   yLOG_note    ("re-gathering data");
   x_atype = yENV_detail (a_full, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, &x_epoch, &x_bytes, NULL, NULL, NULL, NULL, &x_inode, x_hash);
   DEBUG_YENV   yLOG_value   ("detail"    , x_atype);
   --rce;  if (x_atype <= 0) {
      g_score [MARK_HACKED ] = '°';
      yURG_err ('f', "file check generated a hard error (%d)", x_atype);
      DEBUG_YENV   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YENV   yLOG_char    ("detail"    , x_atype);
   /*---(epoch)--------------------------*/
   DEBUG_YENV   yLOG_complex ("epoch"     , "act %d, vs exp %d", x_epoch, a_epoch);
   --rce;  if (a_epoch > 0) {
      ++c;
      g_score [MARK_AEPOCH] = 'e';
      if (strchr ("rh", x_atype) != NULL) {
         if (x_epoch != a_epoch) {
            g_score [MARK_AEPOCH] = '°';
            yURG_err ('f', "epoch (%d); BUT expected (%d)", x_epoch, a_epoch);
            rc_final = rce;
         }
      } else {
         g_score [MARK_AEPOCH] = '-';
      }
   }
   /*---(bytes)--------------------------*/
   DEBUG_YENV   yLOG_complex ("bytes"     , "act %d, vs exp %d", x_bytes, a_bytes);
   --rce;  if (a_bytes > 0) {
      ++c;
      g_score [MARK_ABYTES] = 'b';
      if (strchr ("rh", x_atype) != NULL) {
         if (x_bytes != a_bytes) {
            g_score [MARK_ABYTES] = '°';
            yURG_err ('f', "bytes (%d); BUT expected (%d)", x_bytes, a_bytes);
            rc_final = rce;
            g_score [MARK_ABYTES] = '-';
         }
      } else {
         g_score [MARK_ABYTES] = '-';
      }
   }
   /*---(inode)--------------------------*/
   DEBUG_YENV   yLOG_complex ("inode"     , "act %d, vs exp %d", x_inode, a_inode);
   --rce;  if (a_inode > 0) {
      ++c;
      g_score [MARK_AINODE] = 'i';
      if (x_inode != a_inode) {
         g_score [MARK_AINODE] = '°';
         yURG_err ('f', "inode (%d); BUT expected (%d)", x_inode, a_inode);
         rc_final = rce;
      }
   }
   /*---(hash)---------------------------*/
   --rce;  if (a_hash != NULL && strcmp (a_hash, "") != 0) {
      ++c;
      g_score [MARK_AHASH ] = 'h';
      if (strchr ("rh", x_atype) != NULL) {
         if (strcmp (x_hash, a_hash) != 0) {
            g_score [MARK_AHASH ] = '°';
            yURG_err ('f', "hash å%sæ; BUT expected å%sæ", x_hash, a_hash);
            rc_final = rce;
         }
      } else {
         g_score [MARK_AHASH ] = '-';
      }
   }
   /*---(finalize)-----------------------*/
   if (rc_final < 0) {
      g_score [MARK_HACKED ] = '°';
   } else if (c > 0) {
      g_score [MARK_HACKED ] = '´';
   } else {
      g_score [MARK_HACKED ] = '-';
   }
   /*---(complete)-----------------------*/
   DEBUG_YENV    yLOG_exit    (__FUNCTION__);
   return rc_final;
}

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
   DEBUG_YENV   yLOG_enter   (__FUNCTION__);
   /*---(defaults)-----------------------*/
   if (a_owner != NULL)   strlcpy (x_eowner, a_owner, LEN_USER);
   if (a_group != NULL)   strlcpy (x_egroup, a_group, LEN_USER);
   if (a_perms != NULL)   strlcpy (x_eperms, a_perms, LEN_TERSE);
   /*---(prepare)------------------------*/
   rc = yenv_audit_prepare (a_type, c_flag, a_dir, a_file, '-', x_full, x_etdesc, x_mode, x_note, &c_check, &c_force, &c_fix);
   if (rc > rc_final)  rc_final = rc;
   DEBUG_YENV   yLOG_complex ("prepare"   , "%4d rc, %4d final", rc, rc_final);
   --rce;  if (rc < 0) {
      DEBUG_YENV   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(expected)-----------------------*/
   rc = yenv_audit_expect   (a_type, x_eowner, x_egroup, x_eperms, &x_euid, &x_egid, &x_eprm, x_edisp);
   if (rc > rc_final)  rc_final = rc;
   DEBUG_YENV   yLOG_complex ("expect"    , "%4d rc, %4d final", rc, rc_final);
   --rce;  if (rc < 0) {
      DEBUG_YENV   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(extra)--------------------------*/
   rc = yenv_audit_extra    (a_type, a_major, a_minor, a_ttype, a_target, a_epoch, a_bytes, a_inode, a_hash);
   if (rc > rc_final)  rc_final = rc;
   DEBUG_YENV   yLOG_complex ("extra"     , "%4d rc, %4d final", rc, rc_final);
   --rce;  if (rc < 0) {
      DEBUG_YENV   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(precheck)-----------------------*/
   rc = yenv_audit_precheck (x_full, a_type, x_eowner, x_egroup, x_eperms, a_major, a_minor, a_ttype, a_target, &x_atype, x_atdesc, &x_del, &x_add, &x_upd, c_force, c_fix);
   if (rc > rc_final)  rc_final = rc;
   DEBUG_YENV   yLOG_complex ("check"     , "%4d rc, %4d final", rc, rc_final);
   --rce;  if (rc < 0) {
      DEBUG_YENV   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(remove)-------------------------*/
   rc = yenv_audit_remove   (x_full, x_atype, x_atdesc, c_force, x_del);
   if (rc > rc_final)  rc_final = rc;
   DEBUG_YENV   yLOG_complex ("remove"    , "%4d rc, %4d final", rc, rc_final);
   --rce;  if (rc < 0) {
      DEBUG_YENV   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(create)-------------------------*/
   rc = yenv_audit_create   (x_full, a_type, x_etdesc, x_eowner, x_egroup, x_eperms, a_major, a_minor, a_target, c_force, x_add);
   if (rc > rc_final)  rc_final = rc;
   DEBUG_YENV   yLOG_complex ("create"    , "%4d rc, %4d final", rc, rc_final);
   --rce;  if (rc < 0) {
      DEBUG_YENV   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(update)-------------------------*/
   rc = yenv_audit_update   (x_full, a_type, x_etdesc, x_eowner, x_egroup, x_eperms, a_major, a_minor, a_target, c_fix, x_upd);
   if (rc > rc_final)  rc_final = rc;
   DEBUG_YENV   yLOG_complex ("update"    , "%4d rc, %4d final", rc, rc_final);
   --rce;  if (rc < 0) {
      DEBUG_YENV   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(final check)--------------------*/
   rc = yenv_audit_final    (x_full, a_type, x_etdesc, x_eowner, x_egroup, x_eperms, x_euid, x_egid, x_eprm, x_edisp, a_major, a_minor, a_ttype, a_target);
   if (rc > rc_final)  rc_final = rc;
   DEBUG_YENV   yLOG_complex ("final"     , "%4d rc, %4d final", rc, rc_final);
   --rce;  if (rc < 0) {
      DEBUG_YENV   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(hacker check)-------------------*/
   rc = yenv_audit_hacked       (x_full, a_epoch, a_bytes, a_inode, a_hash);
   if (rc > rc_final)  rc_final = rc;
   DEBUG_YENV   yLOG_complex ("hacked"    , "%4d rc, %4d final", rc, rc_final);
   --rce;  if (rc < 0) {
      DEBUG_YENV   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_YENV    yLOG_exit    (__FUNCTION__);
   return rc_final;
}

char
yENV_audit              (char a_type, char c_flag, char a_dir [LEN_PATH], char a_file [LEN_LABEL], char a_owner [LEN_USER], char a_group [LEN_USER], char a_perms [LEN_TERSE], int a_major, int a_minor, char a_ttype, char a_target [LEN_PATH])
{
   return yENV_audit_full (a_type, c_flag, a_dir, a_file, a_owner, a_group, a_perms, a_major, a_minor, a_ttype, a_target, -1, -1, -1, "", NULL);
}

char
yENV_audit_del          (char c_flag, char a_dir [LEN_PATH], char a_file [LEN_LABEL])
{
   return yENV_audit_full (YENV_NONE , c_flag, a_dir, a_file, "", "", "", -1, -1, YENV_NONE, "", -1, -1, -1, "", NULL);
}

char
yENV_audit_reg          (char c_flag, char a_dir [LEN_PATH], char a_file [LEN_LABEL], char a_owner [LEN_USER], char a_group [LEN_USER], char a_perms [LEN_TERSE])
{
   return yENV_audit_full (YENV_REG  , c_flag, a_dir, a_file, a_owner, a_group, a_perms, -1, -1, YENV_NONE, "", -1, -1, -1, "", NULL);
}

