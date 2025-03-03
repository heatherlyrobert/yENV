/*===[[ HEADER GUARD ]]=======================================================*/
#ifndef YENV_priv_hguard
#define YENV_priv_hguard loaded



/*===[[ ONE_LINERS ]]=========================================================*/
/*                      ┤иииииииии1иииииииии2иииииииии3иииииииии4иииииииии5иииииииии6иииииииии7*/
/*--------- 12345678901 ┤123456789-123456789-123456789-123456789-123456789-123456789-123456789-*/
/*иииииииии иииииииииии ┤иииииииииииииииииииииииииииии┤ииииииииииииииииииииииииииииииииииииииии*/
#define     P_FOCUS     "RS (run-time support)"
#define     P_NICHE     "de (debugging/logging control)"
#define     P_SUBJECT   ""
#define     P_PURPOSE   ""
/*иииииииии иииииииииии ┤иииииииииииииииииииииииииииии┤ииииииииииииииииииииииииииииииииииииииии*/
#define     P_NAMESAKE  ""
#define     P_PRONOUNCE ""
#define     P_HERITAGE  ""
#define     P_BRIEFLY   ""
#define     P_IMAGERY   ""
#define     P_REASON    ""
/*иииииииии иииииииииии ┤иииииииииииииииииииииииииииии┤ииииииииииииииииииииииииииииииииииииииии*/
#define     P_ONELINE   P_NAMESAKE " " P_SUBJECT
/*иииииииии иииииииииии ┤иииииииииииииииииииииииииииии┤ииииииииииииииииииииииииииииииииииииииии*/
#define     P_BASENAME  "yENV"
#define     P_HOMEDIR   "/home/system/yENV.environment_handling"
#define     P_FULLPATH  "/usr/local/lib64/libyENV.so"
#define     P_SUFFIX    "иии"
#define     P_CONTENT   "иии"
/*иииииииии иииииииииии ┤иииииииииииииииииииииииииииии┤ииииииииииииииииииииииииииииииииииииииии*/
#define     P_SYSTEM    "gnu/linux   (powerful, ubiquitous, technical, and hackable)"
#define     P_LANGUAGE  "ansi-c      (wicked, limitless, universal, and everlasting)"
#define     P_COMPILER  "gcc 5.3.0"
#define     P_CODESIZE  "small       (appoximately 1,000 slocl)"
/*иииииииии иииииииииии ┤иииииииииииииииииииииииииииии┤ииииииииииииииииииииииииииииииииииииииии*/
#define     P_AUTHOR    "heatherlyrobert"
#define     P_CREATED   "2024-05"
/*иииииииии иииииииииии ┤иииииииииииииииииииииииииииии┤ииииииииииииииииииииииииииииииииииииииии*/
#define     P_VERMAJOR  "1.--, production improvements"
#define     P_VERMINOR  "1.2-, adding detailed audit, open, close ability"
#define     P_VERNUM    "1.2b"
#define     P_VERTXT    "ported and modded hermes and yJOBS checks"
/*иииииииии иииииииииии ┤иииииииииииииииииииииииииииии┤ииииииииииииииииииииииииииииииииииииииии*/
#define     P_PRIORITY  "direct, simple, brief, vigorous, and lucid (h.w. fowler)"
#define     P_PRINCIPAL "[grow a set] and build your wings on the way down (r. bradbury)"
#define     P_REMINDER  "there are many better options, but i *own* every byte of this one"
/*иииииииии иииииииииии ┤иииииииииииииииииииииииииииии┤ииииииииииииииииииииииииииииииииииииииии*/
/*--------- 12345678901 ┤123456789-123456789-123456789-123456789-123456789-123456789-123456789-*/



/*===[[ END_HEADER ]]=========================================================*/

/*345678901-12345678901-123456789-123456789-123456789-123456789-123456789-123456789-123456789-*/

#include    <stdio.h>        /* C_ANSI : strcpy, strlen, strchr, strcmp, ...  */
#include    <string.h>       /* C_ANSI : printf, snprintf, fgets, fopen, ...  */
#include    <stdlib.h>       /* C_ANSI : exit                                 */
#include    <stdarg.h>       /* C_ANSI : va_args                              */
#include    <ctype.h>        /* C_ANSI : tolower, toupper, ...                */
#include    <sys/stat.h>          /* fstat, umask                                */
#include    <unistd.h>       /* stat(),crpyt()                      */
#include    <sys/mount.h>    /* C_ANSI : mount                                */
#include    <pwd.h>               /* getpwuid, getpwnam                       */
#include    <grp.h>               /* getgruid, getgrnam                       */
#include    <fcntl.h>             /* creat, open, fcntl                       */
#include    <sys/sysmacros.h>
#include    <openssl/sha.h>       /* openssl implementation of sha1           */
#include    <time.h>              /* time, localtime, strftime, ...              */
#include    <errno.h>             /* allow use of errno value                 */



#include    <yLOG.h>
#include    <yURG.h>
#include    <yDLST_solo.h>
#include    <yCOLOR_solo.h>  /* CUSTOM : heatherly color constants            */


#define     DEBUG_YENV   if (1) 

typedef struct stat      tSTAT;
typedef struct passwd    tPASSWD;
typedef struct group     tGROUP;
typedef struct tm        tTIME;



extern char  g_print   [LEN_RECD];



#define     MAX_PERM         50
typedef     struct cENV_PERM    tENV_PERM;
struct cENV_PERM {
   char        name        [LEN_TERSE];
   char        desc        [LEN_HUND];
   int         value;
   char        disp        [LEN_TERSE];
};
extern const tENV_PERM zENV_perms [MAX_PERM];



/*===[[ yENV_audit.c ]]=======================================================*/
/*иииииииии ┤ииииииииииииииииииииии ┤иииииииииииииииииииииииииииииииииииииииии*/
/*---(parts)----------------*/
char        yenv_audit_prepare      (char a_type, char c_flag, char a_dir [LEN_PATH], char a_file [LEN_PATH], char a_mode, char r_full [LEN_PATH], char r_tdesc [LEN_TERSE], char r_mode [LEN_SHORT], char r_note [LEN_LABEL], char *r_check, char *r_force, char *r_fix);
char        yenv_audit_expect       (char b_owner [LEN_USER], char b_group [LEN_USER], char b_perms [LEN_TERSE], int *r_uid, int *r_gid, int *r_prm, char r_disp [LEN_LABEL]);
char        yenv_audit_extra        (char a_type, int a_major, int a_minor, char a_ttype, char a_target [LEN_PATH], int a_epoch, long a_bytes, int a_inode, char a_hash [LEN_DESC]);
char        yenv_audit_precheck     (char a_full [LEN_PATH], char a_etype, char a_eowner [LEN_USER], char a_egroup [LEN_USER], char a_eperms [LEN_TERSE], int a_emajor, int a_eminor, char a_ettype, char a_etarget [LEN_PATH], char *r_atype, char r_atdesc [LEN_TERSE], char *r_del, char *r_add, char *r_upd, char c_force, char c_fix);
char        yenv_audit_remove       (char a_full [LEN_PATH], char a_atype, char a_atdesc [LEN_TERSE], char c_force, char c_del);
char        yenv_audit_create       (char a_full [LEN_PATH], char a_etype, char a_etdesc [LEN_TERSE], char a_eowner [LEN_USER], char a_egroup [LEN_USER], char a_eperms [LEN_TERSE], int a_emajor, int a_eminor, char a_etarget [LEN_PATH], char c_force, char c_add);
char        yenv_audit_update       (char a_full [LEN_PATH], char a_atype, char a_atdesc [LEN_TERSE], char a_eowner [LEN_USER], char a_egroup [LEN_USER], char a_eperms [LEN_TERSE], int a_emajor, int a_eminor, char a_etarget [LEN_PATH], char c_fix, char c_upd);
char        yenv_audit_typing       (char a_etype, char a_etdesc [LEN_TERSE], char a_atype, char a_atdesc [LEN_TERSE]);
char        yenv_audit_final        (char a_full [LEN_PATH], char a_etype, char a_etdesc [LEN_TERSE], char a_eowner [LEN_USER], char a_egroup [LEN_USER], char a_eperms [LEN_TERSE], int a_euid, int a_egid, int a_eprm, char a_adisp [LEN_LABEL], int a_emajor, int a_eminor, char a_ettype, char a_etarget [LEN_PATH]);
char        yenv_audit_hacker       (char a_full [LEN_PATH], int a_epoch, long a_bytes, int a_inode, char a_hash [LEN_DESC]);
/*---(driver)---------------*/
char        yENV_audit              (char a_type, char c_flag, char a_dir [LEN_PATH], char a_file [LEN_LABEL], char a_owner [LEN_USER], char a_group [LEN_USER], char a_perms [LEN_TERSE], int a_major, int a_minor, char a_ttype, char a_target [LEN_PATH]);
/*---(done)-----------------*/



/*===[[ yENV_data.c ]]========================================================*/
/*иииииииии ┤ииииииииииииииииииииии ┤иииииииииииииииииииииииииииииииииииииииии*/
char        yENV__unit_quiet        (void);
char        yENV__unit_loud         (void);
char        yENV__unit_end          (void);
/*---(done)-----------------*/



/*===[[ yENV_file.c ]]========================================================*/
/*иииииииии ┤ииииииииииииииииииииии ┤иииииииииииииииииииииииииииииииииииииииии*/
/*---(parts)----------------*/
char        yenv_open__expect       (char b_owner [LEN_USER], char b_group [LEN_USER], char b_perms [LEN_TERSE], int *r_uid, int *r_gid, int *r_prm, char r_disp [LEN_LABEL]);
char        yenv_open__prepare      (char a_dir [LEN_PATH], char a_file [LEN_PATH], char a_mode, char r_full [LEN_PATH], char r_mode [LEN_SHORT], char r_note [LEN_LABEL]);
char        yenv_open__actual       (char a_full [LEN_PATH], char a_eowner [LEN_USER], char a_egroup [LEN_USER], char a_eperms [LEN_TERSE], int a_euid, int a_egid, int a_eprm, char a_adisp [LEN_LABEL], char c_force, char c_fix);
/*---(done)-----------------*/



#endif
