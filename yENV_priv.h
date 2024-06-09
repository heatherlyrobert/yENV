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
#define     P_VERMINOR  "1.1-, tuning"
#define     P_VERNUM    "1.1a"
#define     P_VERTXT    "added yENV_ulines to yENV_uver as it is too useful for yURG unit testing"
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



#include    <yLOG.h>
#include    <yURG.h>
#include    <yDLST_solo.h>


#define     DEBUG_YENV   if (1) 

typedef struct stat      tSTAT;
typedef struct passwd    tPASSWD;
typedef struct group     tGROUP;
typedef struct tm        tTIME;



#define     MAX_PERM         50
typedef     struct cENV_PERM    tENV_PERM;
struct cENV_PERM {
   char        name        [LEN_TERSE];
   char        desc        [LEN_HUND];
   int         value;
   char        disp        [LEN_TERSE];
};
extern const tENV_PERM zENV_perms [MAX_PERM];


/*===[[ koios_data.c ]]=======================================================*/
/*········· ´······················ ´·········································*/
char        yENV__unit_quiet        (void);
char        yENV__unit_loud         (void);
char        yENV__unit_end          (void);

#endif
