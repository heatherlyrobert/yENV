/*===[[ START ]]==============================================================*/
#include    "yENV.h"
#include    "yENV_priv.h"


char  g_print   [LEN_RECD] = "";


/*====================------------------------------------====================*/
/*===----                            program                           ----===*/
/*====================------------------------------------====================*/
void  o___PROGRAM_________o () { return; }

static char s_version    [LEN_HUND];

char*        /*--> return versioning information ---------[ ------ [ ------ ]-*/
yENV_version       (void)
{
   char        t [LEN_LABEL] = "";
#if    __TINYC__ > 0
   strncpy (t, "[tcc built  ]", LEN_LABEL);
#elif  __GNUC__  > 0
   strncpy (t, "[gnu gcc    ]", LEN_LABEL);
#elif  __HEPH__  > 0
   strncpy (t, "[hephaestus ]", LEN_LABEL);
#else
   strncpy (t, "[unknown    ]", LEN_LABEL);
#endif
   snprintf (s_version, LEN_HUND, "%s   %s : %s", t, P_VERNUM, P_VERTXT);
   return s_version;
}

char
yENV_whoami             (int *r_pid, int *r_ppid, int *r_uid, int *r_euid, char *r_root, char r_user [LEN_USER], char a_wheel, int *r_gid, int *r_egid, char r_group [LEN_USER])
{
   /*---(locals)-------------------------*/
   char        rce         =  -10;
   int         rc          =    0;
   int         x_euid      =    0;
   char        x_root      =  '-';
   int         x_egid      =    0;
   /*---(header)-------------------------*/
   DEBUG_YEXEC  yLOG_enter   (__FUNCTION__);
   /*---(default)--------------------------*/
   if (r_pid   != NULL)   *r_pid   = -1;
   if (r_ppid  != NULL)   *r_ppid  = -1;
   if (r_uid   != NULL)   *r_uid   = -1;
   if (r_euid  != NULL)   *r_euid  = -1;
   if (r_root  != NULL)   *r_root  = '-';
   if (r_user  != NULL)   strcpy (r_user , "");
   if (r_gid   != NULL)   *r_gid   = -1;
   if (r_egid  != NULL)   *r_egid  = -1;
   if (r_group != NULL)   strcpy (r_group, "");
   /*---(log pid info)---------------------*/
   DEBUG_YEXEC  yLOG_note    ("save process ids");
   if (r_pid  != NULL) {
      *r_pid  = getpid();
      DEBUG_YEXEC  yLOG_value   ("r_pid"     , *r_pid);
   }
   if (r_ppid != NULL) {
      *r_ppid = getppid();
      DEBUG_YEXEC  yLOG_value   ("r_ppid"    , *r_ppid);
   }
   /*---(get real uid)-------------------*/
   DEBUG_YEXEC  yLOG_note    ("save uid and user name");
   x_euid   = geteuid ();
   DEBUG_YEXEC  yLOG_value   ("x_euid"    , x_euid);
   if (r_uid   != NULL)   *r_uid   = getuid ();
   if (r_euid  != NULL)   *r_euid  = x_euid;
   rc = yENV_user_data ('i', r_user, &x_euid, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
   --rce;  if (rc < 0)  return rce;
   /*---(check for root user)--------------*/
   if (x_euid == 0)   x_root = 'y';
   DEBUG_YEXEC  yLOG_char    ("x_root"    , x_root);
   /*---(change uid/permissions)-----------*/
   DEBUG_YEXEC  yLOG_char    ("a_wheel"   , a_wheel);
   --rce;  if (x_root != 'y' && a_wheel == 'y') {
      DEBUG_YEXEC  yLOG_note    ("attempt to gain root (legally;)");
      rc = setuid (0);
      DEBUG_YEXEC  yLOG_value   ("setuid"    , rc);
      if (rc != 0) {
         DEBUG_YEXEC  yLOG_note    ("could not gain root access");
      } else {
         DEBUG_YEXEC  yLOG_note    ("successfully gained root (and put back to euid)");
         x_root = 'y';
      }
   }
   /*---(save user info)-----------------*/
   if (r_root != NULL)   *r_root = x_root;
   /*---(log group info)-------------------*/
   x_egid  = getegid ();
   DEBUG_YEXEC  yLOG_value   ("x_egid"    , x_egid);
   if (r_gid   != NULL)   *r_gid   = getgid ();
   if (r_egid  != NULL)   *r_egid  = x_egid;
   rc = yENV_group_data ('i', r_group, &x_egid);
   --rce;  if (rc < 0)  return rce;
   /*---(complete)-----------------------*/
   DEBUG_YEXEC  yLOG_exit    (__FUNCTION__);
   return 0;
}
