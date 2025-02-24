/*===[[ START ]]==============================================================*/
#include    "yENV.h"
#include    "yENV_priv.h"



/*====================------------------------------------====================*/
/*===----                       subroutines                            ----===*/
/*====================------------------------------------====================*/
static void      o___PARTS______________o (void) {;}

char
yenv_audit_expect       (char b_owner [LEN_USER], char b_group [LEN_USER], char b_perms [LEN_TERSE], int *r_uid, int *r_gid, int *r_prm, char r_disp [LEN_LABEL])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
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
   --rce;  if (b_owner != NULL) {
      if (strcmp (x_owner, "") == 0 ) {
         DEBUG_FILE   yLOG_note    ("requested owner not provided, using current uid");
         x_uid = getuid ();
         rc = yENV_user_data  ('i', x_owner, &x_uid, NULL, NULL, NULL);
         if (rc < 0) {
            yURG_err ('f', "attempting to use illegal requested owner å%sæ, uid %d", x_owner, x_uid);
            DEBUG_FILE   yLOG_exitr   (__FUNCTION__, rce);
            return rce;
         }
      } else {
         DEBUG_FILE   yLOG_note    ("owner requested, getting uid");
         rc = yENV_user_data  ('n', x_owner, &x_uid, NULL, NULL, NULL);
         if (rc < 0) {
            yURG_err ('f', "attempting to use illegal requested owner å%sæ, uid %d", x_owner, x_uid);
            DEBUG_FILE   yLOG_exitr   (__FUNCTION__, rce);
            return rce;
         }
      }
      DEBUG_FILE   yLOG_complex ("owner"     , "%4d, %s", x_uid, x_owner);
   }
   /*---(group ownership)----------------*/
   --rce;  if (b_group != NULL) {
      if (strcmp (x_group, "") == 0 ) {
         DEBUG_FILE   yLOG_note    ("requested group not provided, using current gid");
         x_gid = getgid ();
         DEBUG_FILE   yLOG_value   ("x_gid"     , x_gid);
         rc = yENV_group_data ('i', x_group, &x_gid);
         DEBUG_FILE   yLOG_value   ("group"     , rc);
         if (rc < 0) {
            yURG_err ('f', "attempting to use illegal requested group å%sæ, gid %d", x_group, x_gid);
            DEBUG_FILE   yLOG_exitr   (__FUNCTION__, rce);
            return rce;
         }
      } else {
         DEBUG_FILE   yLOG_note    ("group requested, getting gid");
         rc = yENV_group_data ('n', x_group, &x_gid);
         DEBUG_FILE   yLOG_value   ("group"     , rc);
         if (rc < 0) {
            yURG_err ('f', "attempting to use illegal requested group å%sæ, gid %d", x_group, x_gid);
            DEBUG_FILE   yLOG_exitr   (__FUNCTION__, rce);
            return rce;
         }
      }
      DEBUG_FILE   yLOG_complex ("group"     , "%4d, %s", x_gid, x_group);
   }
   /*---(permissions)--------------------*/
   --rce;  if (b_perms != NULL) {
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
            DEBUG_FILE   yLOG_exitr   (__FUNCTION__, rce);
            return rce;
         }
      } else if (x_prm > 0 || strcmp (x_perms, "0000") == 0) {
         DEBUG_FILE   yLOG_note    ("requested perms by octal, getting name");
         DEBUG_FILE   yLOG_value   ("x_prm"     , x_prm);
         rc = yENV_perms_data ('i', x_perms, &x_prm, x_disp);
         DEBUG_FILE   yLOG_value   ("perms"     , rc);
         if (rc < 0) {
            yURG_err ('f', "attempting to use illegal requested perms å%sæ, prm %d", x_perms, x_prm);
            DEBUG_FILE   yLOG_exitr   (__FUNCTION__, rce);
            return rce;
         }
      } else {
         DEBUG_FILE   yLOG_note    ("perms requested, getting octal");
         rc = yENV_perms_data ('n', x_perms, &x_prm, x_disp);
         DEBUG_FILE   yLOG_value   ("perms"     , rc);
         if (rc < 0) {
            yURG_err ('f', "attempting to use illegal requested perms å%sæ, prm %d", x_perms, x_prm);
            DEBUG_FILE   yLOG_exitr   (__FUNCTION__, rce);
            return rce;
         }
      }
      DEBUG_FILE   yLOG_complex ("perms"     , "%4o, %s", x_prm, x_perms);
   }
   /*---(save-back)----------------------*/
   if (r_uid   != NULL)  *r_uid = x_uid;
   if (b_owner != NULL)  snprintf (b_owner, LEN_USER , "%s", x_owner);
   if (r_gid   != NULL)  *r_gid = x_gid;
   if (b_group != NULL)  snprintf (b_group, LEN_USER , "%s", x_group);
   if (r_prm   != NULL)  *r_prm = x_prm;
   if (b_perms != NULL)  snprintf (b_perms, LEN_TERSE, "%s", x_perms);
   if (r_disp  != NULL)  snprintf (r_disp , LEN_LABEL, "%s", x_disp );
   /*---(complete)-----------------------*/
   DEBUG_FILE    yLOG_exit    (__FUNCTION__);
   return RC_POSITIVE;
}

char
yenv_audit_prepare      (char a_type, char a_dir [LEN_PATH], char a_file [LEN_PATH], char a_mode, char r_full [LEN_PATH], char r_tdesc [LEN_TERSE], char r_mode [LEN_SHORT], char r_note [LEN_LABEL])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         ld          =    0;
   int         lf          =    0;
   char        x_tdesc     [LEN_TERSE] = "";
   char        x_name      [LEN_PATH]  = "";
   char        x_mode      [LEN_SHORT] = "";
   char        x_note      [LEN_LABEL] = "";
   /*---(header)-------------------------*/
   DEBUG_FILE   yLOG_enter   (__FUNCTION__);
   /*---(default)------------------------*/
   if (r_full  != NULL)  strcpy (r_full , "");
   if (r_tdesc != NULL)  strcpy (r_tdesc, "");
   if (r_mode  != NULL)  strcpy (r_mode , "");
   if (r_note  != NULL)  strcpy (r_note , "");
   /*---(defense)------------------------*/
   DEBUG_FILE   yLOG_point   ("a_dir"     , a_dir);
   --rce;  if (a_dir       == NULL) {
      DEBUG_FILE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_FILE   yLOG_info    ("a_dir"     , a_dir);
   DEBUG_FILE   yLOG_point   ("a_file"    , a_file);
   --rce;  if (a_file      == NULL) {
      DEBUG_FILE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_FILE   yLOG_info    ("a_file"    , a_file);
   /*---(prepare full name)--------------*/
   ld = strlen (a_dir);
   lf = strlen (a_file);
   DEBUG_FILE    yLOG_complex ("len"       , "ld=%d, lf=%d", ld, lf);
   if (ld + lf == 0) {
      DEBUG_FILE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   if (ld == 0)      sprintf (x_name, "%s", a_file);
   else if (lf == 0) sprintf (x_name, "%s", a_dir);
   else {
      if (a_dir [ld - 1] != '/')    sprintf (x_name, "%s/%s", a_dir, a_file);
      else                          sprintf (x_name, "%s%s" , a_dir, a_file);
   }
   DEBUG_FILE    yLOG_info    ("x_name"    , x_name);
   /*---(set mode)-----------------------*/
   DEBUG_FILE   yLOG_char    ("a_mode"    , a_mode);
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
      DEBUG_FILE   yLOG_note    ("mode not understood");
      DEBUG_FILE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_FILE   yLOG_info    ("x_mode"    , x_mode);
   /*---(type description)---------------*/
   strlcpy (x_tdesc, yENV_typedesc (a_type), LEN_TERSE);
   /*---(save-back)----------------------*/
   if (r_full  != NULL)  snprintf (r_full , LEN_PATH , "%s", x_name);
   if (r_tdesc != NULL)  snprintf (r_tdesc, LEN_TERSE, "%s", x_tdesc);
   if (r_mode  != NULL)  snprintf (r_mode , LEN_SHORT, "%s", x_mode);
   if (r_note  != NULL)  snprintf (r_note , LEN_LABEL, "%s", x_note);
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
   /*---(non-existance)------------------*/
   if (a_atype == YENV_NONE) {
      if (a_etype == YENV_NONE) {
         yURG_msg ('-', "non-existance of filesystem entry confirmed");
         return RC_POSITIVE;
      } else {
         yURG_err ('f', "%s (%c) entry does not exist, AND not in FORCE mode"     , a_etdesc, a_etype);
         return RC_FATAL;
      }
   }
   /*---(match)--------------------------*/
   if (a_atype == a_etype) {
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
yenv_audit_forcing      (void)
{

   /* code to remove entry if a_force == '!'                     */

   /* code to add entry    if a_force == '!' || a_force == 'y'   */

}


char
yenv_audit_actual       (char a_full [LEN_PATH], char a_etype, char a_etdesc [LEN_TERSE], char a_eowner [LEN_USER], char a_egroup [LEN_USER], char a_eperms [LEN_TERSE], int a_euid, int a_egid, int a_eprm, char a_adisp [LEN_LABEL], char c_force, char c_fix)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        rc_final    = RC_POSITIVE;
   char        x_atype     = YENV_NONE;
   char        x_atdesc    [LEN_TERSE] = "";
   char        x_score     =    0;
   char        x_aowner    [LEN_USER]  = "";
   char        x_agroup    [LEN_USER]  = "";
   char        x_aperms    [LEN_TERSE] = "";
   char        x_miss      [LEN_HUND]  = "";
   int         x_auid      =    0;
   int         x_agid      =    0;
   uint        x_aprm      =    0;
   char        x_adisp     [LEN_LABEL] = "";
   int         l           =    0;
   /*---(header)-------------------------*/
   DEBUG_FILE   yLOG_enter   (__FUNCTION__);
   /*---(get data)-----------------------*/
   x_atype = yENV_detail (a_full, x_atdesc, NULL, x_aowner, NULL, x_agroup, NULL, x_aperms, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
   DEBUG_FILE   yLOG_value   ("detail"    , x_atype);
   --rce;  if (x_atype <= 0) {
      yURG_err ('f', "file check generated a hard error (%d)", x_atype);
      DEBUG_FILE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(quick out)----------------------*/
   DEBUG_FILE   yLOG_char    ("x_atype"   , x_atype);
   if (x_atype == YENV_NONE && x_etype == YENV_NONE) {
      yURG_msg ('-', "non-existance of filesystem entry confirmed");
      return RC_POSITIVE;
   }
   /*---(pre-check)----------------------*/
   DEBUG_FILE   yLOG_complex ("pre-check" , "%c force, %c fix", c_force, c_fix);
   x_score = 0;
   --rce;  if (c_force != '-' || c_fix != '-') {
      DEBUG_FILE   yLOG_note    ("conducting pre-check");
      if (x_atype == YENV_NONE)                    { x_score += 16;  strcat (x_miss, "existance, "); }
      if (x_atype != a_etype)                 { x_score += 8;  strcat (x_miss, "type, " ); }
      if (strcmp (x_aowner, a_eowner) != 0)   { x_score += 4;  strcat (x_miss, "owner, "); }
      if (strcmp (x_agroup, a_egroup) != 0)   { x_score += 2;  strcat (x_miss, "group, "); }
      if (strcmp (x_aperms, a_eperms) != 0)   { x_score += 1;  strcat (x_miss, "perms, "); }
      l = strlen (x_miss);
      if (l > 2)  x_miss [l - 2] = '\0';
      if      (x_score >= 16)  yURG_err ('w', "troubles with entry existance (so everything)");
      else if (x_score >   0)  yURG_err ('w', "troubles with entry %s", x_miss);
   }
   DEBUG_FILE   yLOG_value   ("x_score"   , x_score);
   /*---(forcing)------------------------*/
   /*
    *  use new yenv_audit_forcing based on themis, yJOBS, etc
    *
    */

   --rce;  if (x_score >= 16) {
      if (c_force != 'y') {
         yURG_err ('f', "file does not exist, and not in FORCE mode");
         DEBUG_FILE   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      rc = yENV_touch (a_full, a_eowner, a_egroup, a_eperms);
      DEBUG_FILE   yLOG_value   ("force"     , rc);
      if (rc <= 0) {
         yURG_err ('f', "file creation generated a hard error (%d)", rc);
         DEBUG_FILE   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      rc_final = RC_REPAIR;
      yURG_msg ('-', "system called in FORCE mode, so file created");
   }
   else if (x_score > 0) {
      if (c_fix == 'y') {
         rc = yENV_touch (a_full, a_eowner, a_egroup, a_eperms);
         DEBUG_FILE   yLOG_value   ("fix"       , rc);
         if (rc <= 0) {
            yURG_err ('f', "file creation generated a hard error (%d)", rc);
            DEBUG_FILE   yLOG_exitr   (__FUNCTION__, rce);
            return rce;
         }
         rc_final = RC_REPAIR;
         yURG_msg ('-', "system called in FIX mode, so file updated");
      }
   }
   /*---(re-gather data)-----------------*/
   DEBUG_FILE   yLOG_note    ("re-gathering data");
   x_atype = yENV_detail (a_full, x_atdesc, &x_auid, x_aowner, &x_agid, x_agroup, &x_aprm, x_aperms, x_adisp, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
   DEBUG_FILE   yLOG_value   ("detail"    , x_atype);
   --rce;  if (x_atype <= 0) {
      yURG_err ('f', "file check generated a hard error (%d)", x_atype);
      DEBUG_FILE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_FILE   yLOG_char    ("detail"    , x_atype);
   /*---(existance check)----------------*/
   DEBUG_FILE   yLOG_note    ("conducting final-check");
   rc = yenv_audit_typing (a_etype, a_etdesc, x_atype, x_atdesc);
   DEBUG_FILE   yLOG_value   ("typing"    , rc);
   /*> switch (x_atype) {                                                                                                                <* 
    *> case YENV_NONE   : yURG_err ('f', "file does not exist, and not in FORCE mode"        );           rc_final = RC_FATAL;  break;   <* 
    *> case YENV_REG    : yURG_msg ('-', "file existance confirmed and is not a dir/symlink" );           break;                         <* 
    *> case YENV_DIR    : yURG_err ('f', "actually refers to a directory (bad configuration)");           rc_final = RC_FATAL;  break;   <* 
    *> case YENV_SYM    : yURG_err ('f', "actually refers to a symbolic link (security risk)");           rc_final = RC_FATAL;  break;   <* 
    *> default          : yURG_err ('f', "entry is specialty type (%c) (bad configuration)"  , x_atype);  rc_final = RC_FATAL;  break;   <* 
    *> }                                                                                                                                 <*/
   if (rc == RC_POSITIVE) {
      DEBUG_FILE   yLOG_exit    (__FUNCTION__);
      return RC_POSITIVE;
   }
   if (rc == RC_FATAL) {
      DEBUG_FILE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*> if (rc > rc_final)  rc_final = rc;                                             <*/
   /*---(owner)--------------------------*/
   DEBUG_FILE   yLOG_complex ("owner"     , "act %s, exp %s", x_aowner, a_eowner);
   --rce;  if (strcmp (x_aowner, a_eowner) != 0) {
      yURG_err ('f', "owned by å%sæ (%d); BUT expected å%sæ (%d)", x_aowner, x_auid, a_eowner, a_euid);
      DEBUG_FILE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(group)--------------------------*/
   DEBUG_FILE   yLOG_complex ("group"     , "act %s, ext %s", x_agroup, a_egroup);
   --rce;  if (strcmp (x_agroup, a_egroup) != 0) {
      yURG_err ('f', "grouped in å%sæ (%d); BUT expected å%sæ (%d)", x_agroup, x_agid, a_egroup, a_egid);
      DEBUG_FILE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   yURG_msg ('-', "ownership confirmed, owned by å%sæ (%d) and in group å%sæ (%d)", a_eowner, a_euid, a_egroup, a_egid);
   /*---(perms)--------------------------*/
   DEBUG_FILE   yLOG_complex ("perms"     , "act %s, ext %s", x_aperms, a_eperms);
   --rce;  if (strcmp (x_aperms, a_eperms) != 0) {
      yURG_err ('f', "permissions å%sæ, %04o, disp å%sæ; BUT expected å%sæ, %04o, disp å%sæ", x_aperms, x_aprm, x_adisp, a_eperms, a_eprm, a_adisp);
      DEBUG_FILE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   yURG_msg ('-', "permissions confirmed, å%sæ, %04o, disp å%sæ", a_eperms, a_eprm, a_adisp);
   /*---(complete)-----------------------*/
   DEBUG_FILE    yLOG_exit    (__FUNCTION__);
   return rc_final;
}



