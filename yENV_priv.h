/*===[[ HEADER GUARD ]]=======================================================*/
#ifndef YENV_priv_hguard
#define YENV_priv_hguard loaded



/*===[[ ONE_LINERS ]]=========================================================*/
/*                      ´·········1·········2·········3·········4·········5·········6·········7*/
/*--------- 12345678901 ´123456789-123456789-123456789-123456789-123456789-123456789-123456789-*/
/*········· ··········· ´·····························´········································*/
#define     P_FOCUS     "RS (run-time support)"
#define     P_NICHE     "de (debugging/logging control)"
#define     P_SUBJECT   ""
#define     P_PURPOSE   ""
/*········· ··········· ´·····························´········································*/
#define     P_NAMESAKE  ""
#define     P_PRONOUNCE ""
#define     P_HERITAGE  ""
#define     P_BRIEFLY   ""
#define     P_IMAGERY   ""
#define     P_REASON    ""
/*········· ··········· ´·····························´········································*/
#define     P_ONELINE   P_NAMESAKE " " P_SUBJECT
/*········· ··········· ´·····························´········································*/
#define     P_BASENAME  "yENV"
#define     P_HOMEDIR   "/home/system/yENV.environment_handling"
#define     P_FULLPATH  "/usr/local/lib64/libyENV.so"
#define     P_SUFFIX    "···"
#define     P_CONTENT   "···"
/*········· ··········· ´·····························´········································*/
#define     P_SYSTEM    "gnu/linux   (powerful, ubiquitous, technical, and hackable)"
#define     P_LANGUAGE  "ansi-c      (wicked, limitless, universal, and everlasting)"
#define     P_COMPILER  "gcc 5.3.0"
#define     P_CODESIZE  "small       (appoximately 1,000 slocl)"
/*········· ··········· ´·····························´········································*/
#define     P_AUTHOR    "heatherlyrobert"
#define     P_CREATED   "2024-05"
/*········· ··········· ´·····························´········································*/
#define     P_VERMAJOR  "1.--, production improvements"
#define     P_VERMINOR  "1.2-, adding detailed audit, open, close ability"
#define     P_VERNUM    "1.2e"
#define     P_VERTXT    "added all shared/common file name quality code from yJOBS (unit tested)"
/*········· ··········· ´·····························´········································*/
#define     P_PRIORITY  "direct, simple, brief, vigorous, and lucid (h.w. fowler)"
#define     P_PRINCIPAL "[grow a set] and build your wings on the way down (r. bradbury)"
#define     P_REMINDER  "there are many better options, but i *own* every byte of this one"
/*········· ··········· ´·····························´········································*/
/*--------- 12345678901 ´123456789-123456789-123456789-123456789-123456789-123456789-123456789-*/



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


extern char  g_score   [LEN_HUND];

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

/*===[[ HACKING ]]===============*/

#define     MARK_AEPOCH   81
#define     MARK_ABYTES   82
#define     MARK_AINODE   83
#define     MARK_AHASH    84

#define     MARK_HACKED   86

/*===[[ DONE ]]==================*/



#define     MAX_PERM         50
typedef     struct cENV_PERM    tENV_PERM;
struct cENV_PERM {
   char        name        [LEN_TERSE];
   char        desc        [LEN_HUND];
   int         value;
   char        disp        [LEN_TERSE];
};
extern const tENV_PERM zENV_perms [MAX_PERM];




#define    IF_DEV         if (strchr ("bc", x_type) != NULL) 



/*===[[ yENV_audit.c ]]=======================================================*/
/*········· ´······················ ´·········································*/
/*---(parts)----------------*/
char        yenv_audit_prepare      (char a_type, char c_flag, char a_dir [LEN_PATH], char a_file [LEN_PATH], char a_mode, char r_full [LEN_PATH], char r_tdesc [LEN_TERSE], char r_mode [LEN_SHORT], char r_note [LEN_LABEL], char *r_check, char *r_force, char *r_fix);
char        yenv_audit_expect       (char a_type, char b_owner [LEN_USER], char b_group [LEN_USER], char b_perms [LEN_TERSE], int *r_uid, int *r_gid, int *r_prm, char r_disp [LEN_LABEL]);
char        yenv_audit_extra        (char a_type, int a_major, int a_minor, char a_ttype, char a_target [LEN_PATH], int a_epoch, long a_bytes, int a_inode, char a_hash [LEN_DESC]);
char        yenv_audit_precheck     (char a_full [LEN_PATH], char a_etype, char a_eowner [LEN_USER], char a_egroup [LEN_USER], char a_eperms [LEN_TERSE], int a_emajor, int a_eminor, char a_ettype, char a_etarget [LEN_PATH], char *r_atype, char r_atdesc [LEN_TERSE], char *r_del, char *r_add, char *r_upd, char c_force, char c_fix);
char        yenv_audit_remove       (char a_full [LEN_PATH], char a_atype, char a_atdesc [LEN_TERSE], char c_force, char c_del);
char        yenv_audit_create       (char a_full [LEN_PATH], char a_etype, char a_etdesc [LEN_TERSE], char a_eowner [LEN_USER], char a_egroup [LEN_USER], char a_eperms [LEN_TERSE], int a_emajor, int a_eminor, char a_etarget [LEN_PATH], char c_force, char c_add);
char        yenv_audit_update       (char a_full [LEN_PATH], char a_atype, char a_atdesc [LEN_TERSE], char a_eowner [LEN_USER], char a_egroup [LEN_USER], char a_eperms [LEN_TERSE], int a_emajor, int a_eminor, char a_etarget [LEN_PATH], char c_fix, char c_upd);
char        yenv_audit_typing       (char a_etype, char a_etdesc [LEN_TERSE], char a_atype, char a_atdesc [LEN_TERSE]);
char        yenv_audit_final        (char a_full [LEN_PATH], char a_etype, char a_etdesc [LEN_TERSE], char a_eowner [LEN_USER], char a_egroup [LEN_USER], char a_eperms [LEN_TERSE], int a_euid, int a_egid, int a_eprm, char a_adisp [LEN_LABEL], int a_emajor, int a_eminor, char a_ettype, char a_etarget [LEN_PATH]);
char        yenv_audit_hacked       (char a_full [LEN_PATH], int a_epoch, long a_bytes, int a_inode, char a_hash [LEN_DESC]);
/*---(driver)---------------*/
char        yENV_audit              (char a_type, char c_flag, char a_dir [LEN_PATH], char a_file [LEN_LABEL], char a_owner [LEN_USER], char a_group [LEN_USER], char a_perms [LEN_TERSE], int a_major, int a_minor, char a_ttype, char a_target [LEN_PATH]);
/*---(done)-----------------*/



/*===[[ yENV_name.c ]]========================================================*/
/*········· ´······················ ´·········································*/
char        yenv_name_quality       (char a_type, char a_dir [LEN_PATH], char a_file [LEN_PATH], char *r_style, char r_full [LEN_PATH], char c_naming);
char        yenv_name_standard      (char a_type, char a_dir [LEN_PATH], char a_file [LEN_PATH], char a_prefix [LEN_TERSE], char a_suffix [LEN_TERSE], char c_naming, char c_style);
/*---(done)-----------------*/



/*===[[ yENV_test.c ]]========================================================*/
/*········· ´······················ ´·········································*/
char        yENV__unit_quiet        (void);
char        yENV__unit_loud         (void);
char        yENV__unit_end          (void);
/*---(done)-----------------*/



/*===[[ yENV_data.c ]]========================================================*/
/*········· ´······················ ´·········································*/
int         yenv_perms              (char a_type, char a_name [LEN_LABEL]);
/*---(done)-----------------*/



/*===[[ yENV_entry.c ]]=======================================================*/
/*········· ´······················ ´·········································*/
char        yenv_creator            (char a_curr, char a_type, char a_name [LEN_PATH], int a_uid, int a_gid, int a_prm, int a_major, int a_minor, char a_link [LEN_PATH]);
/*---(done)-----------------*/



/*===[[ yENV_perms.c ]]=======================================================*/
/*········· ´······················ ´·········································*/
/*---(conversion)-----------*/
int         yenv_display2octal      (char a_text [LEN_TERSE]);
char*       yenv_octal2display      (int a_perms);
/*---(search)---------------*/
char        yenv_perms_by_name      (char a_text [LEN_TERSE], char r_name [LEN_TERSE], int *r_perms, char r_disp [LEN_TERSE], char r_desc [LEN_HUND]);
char        yenv_perms_by_disp      (char a_text [LEN_TERSE], char r_name [LEN_TERSE], int *r_perms, char r_disp [LEN_TERSE], char r_desc [LEN_HUND]);
char        yenv_perms_by_octal     (char a_text [LEN_TERSE], char r_name [LEN_TERSE], int *r_perms, char r_disp [LEN_TERSE], char r_desc [LEN_HUND]);
/*---(driver)---------------*/
char        yENV_perms_full         (char a_type, char a_text [LEN_TERSE], char r_name [LEN_TERSE], int *r_perms, char r_disp [LEN_TERSE], char r_desc [LEN_HUND], char r_handle [LEN_LABEL]);
char        yENV_perms              (char a_text [LEN_TERSE], char r_name [LEN_TERSE], int *r_perms, char r_disp [LEN_TERSE], char r_desc [LEN_HUND]);
/*---(done)-----------------*/



/*===[[ yENV_file.c ]]========================================================*/
/*········· ´······················ ´·········································*/
/*---(parts)----------------*/
char        yenv_open__expect       (char b_owner [LEN_USER], char b_group [LEN_USER], char b_perms [LEN_TERSE], int *r_uid, int *r_gid, int *r_prm, char r_disp [LEN_LABEL]);
char        yenv_open__prepare      (char a_dir [LEN_PATH], char a_file [LEN_PATH], char a_mode, char r_full [LEN_PATH], char r_mode [LEN_SHORT], char r_note [LEN_LABEL]);
char        yenv_open__actual       (char a_full [LEN_PATH], char a_eowner [LEN_USER], char a_egroup [LEN_USER], char a_eperms [LEN_TERSE], int a_euid, int a_egid, int a_eprm, char a_adisp [LEN_LABEL], char c_force, char c_fix);
/*---(done)-----------------*/



#endif
