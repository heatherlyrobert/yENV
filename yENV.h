/*===[[ HEADER GUARD ]]=======================================================*/
#ifndef YENV_HGUARD
#define YENV_HGUARD loaded



#include    <stdio.h>        /* C_ANSI : strcpy, strlen, strchr, strcmp, ...  */
#include <ySTR_solo.h>



/*---(standard recturn codes)-------------------*/
#define     RC_ACK          0
#define     RC_POSITIVE     1
#define     RC_OVERRIDE     2
#define     RC_REPAIR       3
#define     RC_WARNING      4
#define     RC_FATAL        5



#define     YENV_BLOCK       'b'
#define     YENV_CHAR        'c'
#define     YENV_DIR         'd'
#define     YENV_HARD        'h'
#define     YENV_IPSOC       'i'
#define     YENV_PIPE        'p'
#define     YENV_REG         'r'
#define     YENV_SYM         's'
#define     YENV_NONE        '-'
#define     YENV_WTF         '?'




/*===[[ yENV_audit.c ]]=======================================================*/
/*��������� ����������������������� ������������������������������������������*/


/*===[[ koios_base.c ]]=======================================================*/
/*��������� ����������������������� ������������������������������������������*/
char*       yENV_version            (void);
/*---(done)-----------------*/



/*===[[ koios_data.c ]]=======================================================*/
/*��������� ����������������������� ������������������������������������������*/
/*---(users)----------------*/
char        yENV_user_data          (char a_type, char b_name [LEN_USER], int *b_uid, int *r_gid, char r_dir [LEN_HUND], char r_shell [LEN_HUND]);
char        yENV_user_del           (char a_name [LEN_USER]);
char        yENV_user_add           (char a_name [LEN_USER], char a_home, char a_shell);
/*---(groups)---------------*/
char        yENV_group_data         (char a_type, char b_name [LEN_USER], int *b_gid);
char        yENV_group_del          (char a_name [LEN_USER]);
char        yENV_group_add          (char a_name [LEN_USER], char a_user [LEN_USER]);
/*---(perms)----------------*/
char        yENV_perms_data         (char a_type, char b_name [LEN_TERSE], int *b_perms, char b_disp [LEN_TERSE]);
/*---(done)-----------------*/



/*===[[ koios_entry.c ]]======================================================*/
/*��������� ����������������������� ������������������������������������������*/
/*---(create)---------------*/
char        yENV_touchier           (char a_type, char a_name [LEN_PATH], char a_own [LEN_LABEL], char a_grp [LEN_LABEL], char a_perms [LEN_LABEL], int a_major, int a_minor, char a_link [LEN_PATH]);
char        yENV_touch              (char a_name [LEN_PATH], char a_own [LEN_LABEL], char a_grp [LEN_LABEL], char a_perms [LEN_LABEL]);
char        yENV_mkdir              (char a_name [LEN_PATH], char a_own [LEN_LABEL], char a_grp [LEN_LABEL], char a_perms [LEN_LABEL]);
/*---(remove)---------------*/
char        yENV_removier           (char a_type, char a_name [LEN_PATH]);
char        yENV_rm                 (char a_name [LEN_PATH]);
char        yENV_rmdir              (char a_name [LEN_PATH]);
/*---(checking)-------------*/
char        yENV_exists             (char a_name [LEN_PATH]);
char*       yENV_typedesc           (char a_type);
char        yENV_detail             (char a_name [LEN_PATH], char r_tdesc [LEN_TERSE], int *r_uid, char r_own [LEN_LABEL], int *r_gid, char r_grp [LEN_LABEL], int *r_perms, char r_pname [LEN_LABEL], char r_pdisp [LEN_TERSE], long *r_bytes, int *r_epoch, int *r_major, int *r_minor, char r_link [LEN_PATH], int *r_dev, int *r_inode, char r_hash [LEN_DESC]);
char*       yENV_detail_unit        (char a_name [LEN_PATH]);
/*---(done)-----------------*/



/*===[[ koios_peek.c ]]=======================================================*/
/*��������� ����������������������� ������������������������������������������*/
/*---(content)--------------*/
char*       yENV_peekier            (char a_style, char a_name [LEN_PATH], int n, int *a_count);
char*       yENV_peek               (char a_name [LEN_PATH], int n);
char*       yENV_peek_vis           (char a_name [LEN_PATH], int n);
char*       yENV_peek_field         (char a_name [LEN_PATH], int n);
int         yENV_lines              (char a_name [LEN_PATH]);
/*---(comparision)----------*/
char        yENV_diff               (char *a_actual, char *a_expect);
/*---(done)-----------------*/



/*===[[ koios_self.c ]]=======================================================*/
/*��������� ����������������������� ������������������������������������������*/
/*---(myself)---------------*/
char        yENV_whoami             (int *r_pid, int *r_ppid, int *r_uid, int *r_euid, char *r_root, char r_user [LEN_USER], char a_wheel, int *r_gid, int *r_egid, char r_group [LEN_USER]);
/*---(done)-----------------*/



/*===[[ koios_file.c ]]=======================================================*/
/*��������� ����������������������� ������������������������������������������*/
/*---(openning)-------------*/
char        yENV_open_full          (char a_dir [LEN_PATH], char a_file [LEN_LABEL], char a_mode, FILE **r_file, char c_check, char c_force, char c_fix, char a_owner [LEN_USER], char a_group [LEN_USER], char a_perms [LEN_TERSE]);
char        yENV_open               (char a_dir [LEN_PATH], char a_file [LEN_LABEL], char a_mode, FILE **r_file);
char        yENV_open_safe          (char a_dir [LEN_PATH], char a_file [LEN_LABEL], char a_mode, FILE **r_file, char a_owner [LEN_USER], char a_group [LEN_USER], char a_perms [LEN_TERSE]);
char        yENV_open_fix           (char a_dir [LEN_PATH], char a_file [LEN_LABEL], char a_mode, FILE **r_file, char a_owner [LEN_USER], char a_group [LEN_USER], char a_perms [LEN_TERSE]);
char        yENV_open_force         (char a_dir [LEN_PATH], char a_file [LEN_LABEL], char a_mode, FILE **r_file, char a_owner [LEN_USER], char a_group [LEN_USER], char a_perms [LEN_TERSE]);
/*---(closing)--------------*/
char        yENV_close_full         (char a_dir [LEN_PATH], char a_file [LEN_PATH], char a_mode, FILE **b_file, char c_check);
char        yENV_close              (FILE **b_file);
/*---(done)-----------------*/





#endif
/*===[[ END ]]================================================================*/
