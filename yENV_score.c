/*===[[ START ]]==============================================================*/
#include    "yENV.h"
#include    "yENV_priv.h"


/*
 * tables rules...
 *
 *    labels are only 1 to 9 characters, best if all caps
 *    last entry in labels is "end-list" as sentinel
 *
 *    default entries are used to create starting point
 *
 *    sample entries are used to show full version
 *       0) indicates 4 character block headers (two upper case followed by '�' and ' ')
 *       1) indicates single character spacer (none of the other fields will be used
 *       3) indicates three character spacer
 *
 *    valid is to limit options, but i may remove as it can be fussy
 *
 *    print field is for creating headers
 *       block headers are horizontal on top line
 *       line headers are vertical 1 to 6 characters
 *
 *    description is short helper
 *
 *    long is used for legends telling the various content meanings
 *
 */


const static tENV_SCORE s_audits [LEN_FULL] = {

   /*===[[ NAME ]]==========================================================*/
   { "NM� "            , ' ' ,  0  , "NAME"            , ""                                 , ""                                                                                },
   /*===[[ REQUEST TYPE ]]==================================================*/
   { "NCONF"           , '�' , 'c' , "conf"            , "naming standard applied"          , "-) loose     n) normal    s) standard  l) local     c) central"                  }, 
   { " "               , ' ' ,  1  , ""                , ""                                 , ""                                                                                },
   /*===[[ NAMING ]]========================================================*/
   { "NFULL"           , '�' , 'n' , "name"            , "name quality checking"            , "-) no dir    =) no file   /) not abs   �) hidden    �) bad char  n) passed"      },
   { "NSTYLE"          , '�' , 'b' , "style"           , "dir, file, or both"               , "d) dir-only    f) file-only   b) both"                                           },
   { " "               , ' ' ,  1  , ""                , ""                                 , ""                                                                                },
   /*===[[ STANDARDS ]]=====================================================*/
   { "NFIXES"          , '�' , 'N' , "fixes"           , "prefix/suffix checking"           , "-) skipped   #) dot count P) pre bad   S) suf bad   �) rem bad   N) passed"      },
   { "NLOC"            , '�' , 'l' , "locs"            , "location  checking"               , "rR) root   hH) home   eE) etc    sS) spool    [ upper case passed]"              },
   { " "               , ' ' ,  1  , ""                , ""                                 , ""                                                                                },
   /*===[[ REQUEST ]]=======================================================*/
   { "NAME"            , '-' , '�' , "������"          , "judgement on naming"              , "�) passed"                                                                       },
   { "   "             , '�' ,  3  , ""                , ""                                 , ""                                                                                },

   /*===[[ REQUEST ]]=======================================================*/
   { "EX� "            , ' ' ,  0  , "EXPECT"          , ""                                 , ""                                                                                },
   /*===[[ REQUEST TYPE ]]==================================================*/
   { "ETYPE"           , '�' , 'r' , "type"            , "expected file type"               , "d) dir   r) reg   s) sym   h) hard  c) char  b) block p) pipe  i) ipsoc ?) WTF"  },
   { " "               , ' ' ,  1  , ""                , ""                                 , ""                                                                                },
   /*===[[ REQUEST CHARS ]]=================================================*/
   { "EOWNER"          , '�' , 'o' , "owner"           , "expected owner"                   , "o) standard   �) numeric    O) default    -) skipped"                            },
   { "EGROUP"          , '�' , 'g' , "group"           , "expected group"                   , "g) standard   �) numeric    G) default    -) skipped"                            },
   { "EPERMS"          , '�' , 'p' , "perms"           , "expected permissions"             , "p) standard   �) non-std    P) default    -) skipped"                            },
   { " "               , ' ' ,  1  , ""                , ""                                 , ""                                                                                },
   /*===[[ REQUEST DEVICE ]]================================================*/
   { "EMAJOR"          , '�' , 'j' , "major"           , "expected owner"                   , "j) in-range   -) skipped"                                                        },
   { "EMINOR"          , '�' , 'n' , "minor"           , "expected group"                   , "n) in-range   -) skipped"                                                        },
   { " "               , ' ' ,  1  , ""                , ""                                 , ""                                                                                },
   /*===[[ REQUEST LINK ]]==================================================*/
   { "ETTYPE"          , '�' , 'r' , "ttype"           , "expected link target type"        , "d) dir   r) reg   s) sym   h) hard  c) char  b) block p) pipe  i) ipsoc ?) WTF"  },
   { "ETARGET"         , '�' , 't' , "target"          , "expected link target"             , "/) not-abs    #) bad chars  t) accepted   -) skipped"                            },
   { " "               , ' ' ,  1  , ""                , ""                                 , ""                                                                                },
   /*===[[ REQUEST EXTENDED ]]==============================================*/
   { "EEPOCH"          , '�' , 'e' , "epoch"           , "expected update time"             , "e) accepted   -) skipped"                                                        },
   { "EBYTES"          , '�' , 'b' , "bytes"           , "expected size in bytes"           , "b) accepted   -) skipped"                                                        },
   { "EINODE"          , '�' , 'i' , "inode"           , "expected inode"                   , "i) accepted   -) skipped"                                                        },
   { "EHASH"           , '�' , 'h' , "hash"            , "expected file SHA hash"           , "h) accepted   -) skipped"                                                        },
   { " "               , ' ' ,  1  , ""                , ""                                 , ""                                                                                },
   /*===[[ REQUEST ]]=======================================================*/
   { "EXPECT"          , '-' , '�' , "������"          , "judgement on request"             , "�) passed"                                                                       },
   { "   "             , '�' ,  3  , ""                , ""                                 , ""                                                                                },

   /*===[[ PRECHECK ]]======================================================*/
   { "PR� "            , ' ' ,  0  , "CHECK"           , ""                                 , ""                                                                                },
   /*===[[ CHECK TYPE ]]====================================================*/
   { "CTYPE"           , '�' , 'r' , "type"            , "checked file type"                , "same as expected type, lower case if matching, upper case if not-match"          },
   { " "               , ' ' ,  1  , ""                , ""                                 , ""                                                                                },
   /*===[[ CHECK CHARS ]]===================================================*/
   { "COWNER"          , '�' , 'o' , "owner"           , "checked owner"                    , "o) match      O) not-match"                                                      },
   { "CGROUP"          , '�' , 'g' , "group"           , "checked group"                    , "g) match      G) not-match"                                                      },
   { "CPERMS"          , '�' , 'p' , "perms"           , "checked permissions"              , "p) match      P) not-match"                                                      },
   { " "               , ' ' ,  1  , ""                , ""                                 , ""                                                                                },
   /*===[[ CHECK DEVICE ]]==================================================*/
   { "CMAJOR"          , '�' , 'j' , "major"           , "checked owner"                    , "j) match      J) not-match"                                                      },
   { "CMINOR"          , '�' , 'n' , "minor"           , "checked group"                    , "n) match      N) not-match"                                                      },
   { " "               , ' ' ,  1  , ""                , ""                                 , ""                                                                                },
   /*===[[ CHECK LINK ]]====================================================*/
   { "CTTYPE"          , '�' , 'r' , "ttype"           , "checked link target type"         , "t) match      T) not-match"                                                      },
   { "CTARGET"         , '�' , 't' , "target"          , "checked link target"              , "t) match      T) not-match"                                                      },
   { " "               , ' ' ,  1  , ""                , ""                                 , ""                                                                                },
   /*===[[ CHECK JUDGE ]]===================================================*/
   { "CHECK"           , '-' , '�' , "������"          , "judgement on check"               , "-) skipped    �) passed"                                                         },
   { "   "             , '�' ,  3  , ""                , ""                                 , ""                                                                                },

   /*===[[ FIXES ]]=========================================================*/
   { "FX� "            , ' ' ,  0  , "FIXES"           , ""                                 , ""                                                                                },
   /*===[[ REQUEST ]]=======================================================*/
   { "EFLAG"           , '�' , 'F' , "flag"            , "fix/forcing flag interpretation"  , "-) none allowed  f) allow fix     F) allow create  !) can even remove"           },
   { " "               , ' ' ,  1  , ""                , ""                                 , ""                                                                                },
   /*===[[ CONFIGURATION ]]=================================================*/
   { "CONFC"           , '�' , 'y' , "check"           , "judgement on request"             , "y) precheck    -) not-requested"                                                 },
   { "CONFF"           , '�' , 'y' , "force"           , "judgement on request"             , "y) create, if must   !) remove, if must   -) not-requested"                      },
   { "CONFX"           , '�' , 'y' , "fix"             , "judgement on request"             , "y) fix, if must      -) not-requested"                                           },
   { " "               , ' ' ,  1  , ""                , ""                                 , ""                                                                                },
   /*===[[ FIX/FORCES ]]====================================================*/
   { "FDEL"            , '�' , 'r' , "remove"          , "need forced deletion"             , "r) requires deletion   -) not needed"                                            },
   { "FADD"            , '�' , 'c' , "create"          , "need forced creation"             , "c) requires creation   -) not needed"                                            },
   { "FUPD"            , '�' , 'u' , "update"          , "need forced updates"              , "u) requires updates    -) not needed"                                            },
   { " "               , ' ' ,  1  , ""                , ""                                 , ""                                                                                },
   /*===[[ ACTUAL ]]========================================================*/
   { "REMOVE"          , '�' , 'R' , "REMOVE"          , "actual deletion"                  , "R) really removed    ?) non-existant      !) not enough force  -) not needed"    },
   { " "               , ' ' ,  1  , ""                , ""                                 , ""                                                                                },
   { "CREATE"          , '�' , 'C' , "CREATE"          , "actual creation"                  , "C) really created    ?) already exists    !) not enough force  -) not needed"    },
   { " "               , ' ' ,  1  , ""                , ""                                 , ""                                                                                },
   { "UPDATE"          , '�' , 'U' , "UPDATE"          , "actual updates"                   , "U) really updated    !) not enough force  -) not needed"                         },
   { " "               , ' ' ,  1  , ""                , ""                                 , ""                                                                                },
   /*===[[ RE-CHECK JUDGE ]]================================================*/
   { "FIXES"           , '-' , '�' , "������"          , "judgement on fixes"               , "-) skipped    �) passed"                                                         },
   { "   "             , ' ' ,  3  , ""                , ""                                 , ""                                                                                },

   /*===[[ RECHECK ]]=======================================================*/
   { "RE� "            , ' ' ,  0  , "RECHECK"         , ""                                 , ""                                                                                },
   /*===[[ RE-CHECK TYPE ]]=================================================*/
   { "RTYPE"           , '�' , 'r' , "type"            , "checked file type"                , "same as expected type, lower case if matching, upper case if not-match"          },
   { " "               , ' ' ,  1  , ""                , ""                                 , ""                                                                                },
   /*===[[ RE-CHECK CHARS ]]================================================*/
   { "ROWNER"          , '�' , 'o' , "owner"           , "re-checked owner"                 , "o) match      O) not-match"                                                      },
   { "RGROUP"          , '�' , 'g' , "group"           , "re-checked group"                 , "g) match      G) not-match"                                                      },
   { "RPERMS"          , '�' , 'p' , "perms"           , "re-checked permissions"           , "p) match      P) not-match"                                                      },
   { " "               , ' ' ,  1  , ""                , ""                                 , ""                                                                                },
   /*===[[ RE-CHECK DEVICE ]]===============================================*/
   { "RMAJOR"          , '�' , 'j' , "major"           , "re-checked owner"                 , "j) match      J) not-match"                                                      },
   { "RMINOR"          , '�' , 'n' , "minor"           , "re-checked group"                 , "n) match      N) not-match"                                                      },
   { " "               , ' ' ,  1  , ""                , ""                                 , ""                                                                                },
   /*===[[ RE-CHECK LINK ]]=================================================*/
   { "RTTYPE"          , '�' , 'r' , "ttype"           , "re-checked link target type"      , "t) match      T) not-match"                                                      },
   { "RTARGET"         , '�' , 't' , "target"          , "re-checked link target"           , "t) match      T) not-match"                                                      },
   { " "               , ' ' ,  1  , ""                , ""                                 , ""                                                                                },
   /*===[[ RE-CHECK JUDGE ]]================================================*/
   { "RECHECK"         , '-' , '�' , "������"          , "judgement on re-check"            , "�) passed"                                                                       },
   { "   "             , ' ' ,  3  , ""                , ""                                 , ""                                                                                },

   /*===[[ FINAL ]]=========================================================*/
   { "JD� "            , ' ' ,  0  , "�"               , ""                                 , ""                                                                                },
   /*===[[ FINAL JUDGE ]]===================================================*/
   { "FINAL"           , '�' , '�' , "FINAL"           , "final judgement"                  , "�) passed"                                                                       },
   { "   "             , ' ' ,  3  , ""                , ""                                 , ""                                                                                },

   /*===[[ HACKED ]]========================================================*/
   { "HK� "            , ' ' ,  0  , "HACK"            , ""                                 , ""                                                                                },
   /*===[[ HACKING CHECK ]]=================================================*/
   { "AEPOCH"          , '�' , 'e' , "epoch"           , "check update time"                , "e) matches    E) not-match"                                                      },
   { "ABYTES"          , '�' , 'b' , "bytes"           , "check size in bytes"              , "b) matches    B) not-match"                                                      },
   { "AINODE"          , '�' , 'i' , "inode"           , "check inode"                      , "i) matches    I) not-match"                                                      },
   { "AHASH"           , '�' , 'h' , "hash"            , "check file SHA hash"              , "h) matches    H) not-match"                                                      },
   { " "               , ' ' ,  1  , ""                , ""                                 , ""                                                                                },
   /*===[[ HACKING FINAL ]]=================================================*/
   { "HACKED"          , '-' , '�' , "������"          , "final hacking judgement"          , "-) skipped    �) passed"                                                         },

   /*===[[ END-OF-LIST ]]===================================================*/
   { "end-list"        , '�' , '�' , ""                , "end-of-entries"                   , ""                                                                                },

   /*===[[ DONE ]]==========================================================*/
};
static char         s_terse      [LEN_FULL]  = "� �� �� -   � ��� �� �� ���� -   � ��� �� �� -   � ��� ��� � � � -   � ��� �� �� -   �   ���� -";
static char         s_score      [LEN_FULL]  = "NM� � �� �� -   EX� � ��� �� �� ���� -   PR� � ��� �� �� -   FX� � ��� ��� � � � -   RE� � ��� �� �� -   JD� �   HK� ���� -";
static char         s_full       [LEN_FULL]  = "NM� c nb Nl �   EX� r ogp jn rt ebih �   PR� r ogp jn rt �   FX� F yyy rcu R C U �   RE� r ogp jn rt �   JD� �   HK� ebih �";
static char         s_report     [LEN_FULL]  = " �  � �  � �  -   �  � � �  � �  � �  � � � �  -   �  � � �  � �  � �  -   �  � � �  � � �  �  �  �  -   �  � � �  � �  � �  -   �   � � � �  -";

static char         s_ttitle     [LEN_FULL]  = "NAME�����   EXPECT������������   CHECK��������   FIXES������������   RECHECK������   �   HACK��";
static char         s_stitle     [LEN_FULL]  = "NAME���������   EXPECT����������������   CHECK������������   FIXES����������������   RECHECK����������   �����   HACK������";
static char         s_rtitle     [LEN_FULL]  = " NAME����������   EXPECT������������������������   CHECK����������������   FIXES����������������������   RECHECK��������������   �   HACK������";

static tENV_SCORE  *s_TABLE   = NULL;
static char         s_TERSE      [LEN_FULL]  = "";
static char         s_SCORE      [LEN_FULL]  = "";
static char         s_FULL       [LEN_FULL]  = "";
static char         s_REPORT     [LEN_FULL]  = "";



/*                                               1         2         3         4         5         6         7         8         9            */
/*                                     -123456789-123456789-123456789-123456789-123456789-123456789-123456789-123456789-123456789-123456789   */
/*                                     --------request---------   cfg   ----check----   flg   -fix-   ---recheck---   f   hacked         */





/*>    REQUEST LEGEND ===============================================================================================================================================================\n");   <* 
 *>    ��������������������� type            d) directory    f) file         s) symlink      c) char dev     b) block dev    p) pipe/fifo    i) ipsoc        h) hard link    ?) illegal            <* 
 *>    � ������������������� name            n) valid        /) pathless     -) null/empty   �) illegal                                                                            <* 
 *>    � ������������������� owner           o) valid        O) defaulted    -) null         �) illegal                                                                                            <* 
 *>    � ������������������� group           g) valid        G) defaulted    -) null         �) illegal                                                                                            <* 
 *>    � ������������������� permissions     p) valid        P) defaulted    -) null         �) illegal                                                                                            <* 
 *>    � ���� �������������� major number
 *>    � ���� �������������� major number
 *>    � ���� �� ����������� target type     d) directory    f) file         s) symlink      c) char dev     b) block dev    p) pipe/fifo    i) ipsoc        h) hard link    ?) illegal            <*
 *>    � ���� �� ����������� target link     t) target       -) none\n");                                                                                                                          <*
 *>    � ���� �� �� �������� epoch
 *>    � ���� �� �� �������� bytes
 *>    � ���� �� �� �������� inode
 *>    � ���� �� �� �������� hash
 *>    � ���� �� �� ���� ��� summary         y) complete     !) issues\n");                                                                                                                        <* 
 *>    d togp �� �� ���� y (file/directory example)\n");                                                                                                                                         <* 
 *>    c togp jn��� ���� y (char/block device example\n");                                                                                                                                       <* 
 *>    s t��� ��ts� ���� y (symlink/hardlink example\n");                                                                                                                                                 <*/


/*>    CHECK/RECHECK LEGEND =========================================================================================================================================================\n");   <* 
 *>    ������������������� name            n) valid        �) null         �) empty        /) pathless     F) bad chars\n");                                                                     <* 
 *>    ������������������� exists          e) existing     �) not-exist\n");                                                                                                                     <* 
 *>    �� ���������������� actual type     d) directory    f) file         s) symlink      c) char dev     b) block dev    p) pipe/fifo    i) ipsoc        h) hard link\n");                     <* 
 *>    �� ���������������� owner           o) matches      -) no match\n");                                                                                                                      <* 
 *>    �� ���������������� group           g) matches      -) no match\n");                                                                                                                      <* 
 *>    �� ���������������� permissions     p) matches      -) no match\n");                                                                                                                      <* 
 *>    �� ���� ����������� major number
 *>    �� ���� ����������� minor number
 *>    �� ���� �� �������� source link
 *>    �� ���� �� �������� source exist    s) given        -) none\n");                                                                                                                          <* 
 *>    �� ���� �� �������� source type     s) given        -) none\n");                                                                                                                          <* 
 *>    �� ���� �� ��� ���� summary         y) complete     !) issues       � not-exist\n");                                                                                                      <* 
 *>    n- ---- �� ��� �    (file/directory does not exist yet)\n");                                                                                                                              <* 
 *>    ne dogp ���� y      (file/directory example)\n");                                                                                                                                         <* 
 *>    �� ���� �������� major number    j) matches      -) no match\n");                                                                                                                      <* 
 *>    �� ���� �������� minor number    n) matches      -) no match\n");                                                                                                                      <* 
 *>    �� ���� ��  ���� summary         y) complete     !) issues       � not-exist\n");                                                                                                      <* 
 *>    ne cogp �jn� y    (char/block device example)\n");                                                                                                                                      <* 
 *>    �� � ����������� source name     n) valid        �) null         �) empty        /) pathless     F) bad chars\n");                                                                     <* 
 *>    �� � ����������� source exists   e) existing     �) not-exist\n");                                                                                                                     <* 
 *>    �� � ����������� source type     d) directory    f) file         s) symlink      c) char dev     b) block dev    p) pipe/fifo    i) ipsoc        h) hard link\n");                     <* 
 *>    �� � ����������� source link     n) matches      -) no match\n");                                                                                                                      <* 
 *>    �� � ����   ���� summary         y) complete     !) issues       � not-exist\n");                                                                                                      <* 
 *>    ne s�necl�� y    (symlink example)\n");                                                                                                                                                <* 
 *>    n- -�nec-�� �    (symlink does not exist yet)\n");                                                                                                                                     <*/

/*>    UPDATE LEGEND ================================================================================================================================================================\n");   <* 
 *>    ���������������� remove          e) existing     D) made dir     S) made slink   C) made char    B) made block   P) made pipe    I) made ipsoc   H) made hlink\n");                    <* 
 *>    ���������������� create          e) existing     D) made dir     S) made slink   C) made char    B) made block   P) made pipe    I) made ipsoc   H) made hlink\n");                    <* 
 *>    �� ������������� owner           o) no action    O) updated\n");                                                                                                                       <* 
 *>    �� ��������������group            o) no action    O) updated\n");                                                                                                                       <* 
 *>    �� ��������������perms             o) no action    O) updated\n");                                                                                                                       <* 
 *>    �� ��� ����������summary         y) complete     !) issues\n");                                                                                                                        <* 
 *>    DO --- y    (file/directory created)\n");                                                                                                                                         <* 
 *>    eo g   y    (file/directory exists, permissions changed)\n");                                                                                                                     <* 
 *>    S� �   y    (symlink created)\n");                                                                                                                                                <* 
 *>    CO G   y    (char/block device created)\n");                                                                                                                                      <*/




/*====================------------------------------------====================*/
/*===----                         helpers                              ----===*/
/*====================------------------------------------====================*/
static void      o___HELPERS____________o (void) {;}

char* yenv_score_terse  (void)  { return s_terse; }
char* yENV_score_terse  (void)  { return s_TERSE; }

char* yenv_score        (void)  { return s_score; }
char* yENV_score        (void)  { return s_SCORE; }

char* yenv_score_full   (void)  { return s_full; }
char* yENV_score_full   (void)  { return s_FULL; }

char* yenv_score_report (void)  { return s_report; }
char* yENV_score_report (void)  { return s_REPORT; }

char* yENV_score_ttile  (void)  { return ""; }
char* yENV_score_rtile  (void)  { return ""; }



/*====================------------------------------------====================*/
/*===----                        program level                         ----===*/
/*====================------------------------------------====================*/
static void      o___PROGRAM_______o (void) {;};

char
yENV_score_init         (tENV_SCORE *a_table)
{
   s_TABLE = a_table;
   return 0;
}

char
yenv_score__clear       (tENV_SCORE *a_table, char r_terse [LEN_FULL], char r_score [LEN_FULL], char r_full [LEN_FULL], char r_report [LEN_FULL])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         i           =    0;
   char        s           [LEN_SHORT] = "";
   char        f           [LEN_SHORT] = "";
   char        t           [LEN_SHORT] = "";
   char        r           [LEN_SHORT] = "";
   char        x_terse     [LEN_FULL]  = "";
   char        x_score     [LEN_FULL]  = "";
   char        x_full      [LEN_FULL]  = "";
   char        x_report    [LEN_FULL]  = "";
   /*---(header)-------------------------*/
   DEBUG_YENV   yLOG_senter  (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YENV   yLOG_spoint  (a_table);
   --rce;  if (a_table == NULL) {
      DEBUG_YENV   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(create)-------------------------*/
   for (i = 0; i < LEN_FULL; ++i) {
      /*---(test for end)----------------*/
      if (strncmp (a_table [i].s_label, "end-", 4) == 0)  break;
      switch (a_table [i].s_sample) {
      case  0  :
         strlcpy (s     , a_table [i].s_label , LEN_SHORT);
         strlcpy (f     , a_table [i].s_label , LEN_SHORT);
         strlcpy (t     , ""                  , LEN_SHORT);
         strlcpy (r     , ""                  , LEN_SHORT);
         break;
      case  1  :
         strlcpy (s     , " "   , LEN_SHORT);
         strlcpy (f     , " "   , LEN_SHORT);
         strlcpy (t     , " "   , LEN_SHORT);
         strlcpy (r     , " "   , LEN_SHORT);
         break;
      case  3  :
         strlcpy (s     , "   " , LEN_SHORT);
         strlcpy (f     , "   " , LEN_SHORT);
         strlcpy (t     , "   " , LEN_SHORT);
         strlcpy (r     , "  "  , LEN_SHORT);
         break;
      default  :
         sprintf  (s, "%c" , a_table [i].s_default);
         sprintf  (f, "%c" , a_table [i].s_sample);
         sprintf  (t, "%c" , a_table [i].s_default);
         sprintf  (r, " %c", a_table [i].s_default);
      }
      strlcat (x_full  , f  , LEN_FULL);
      strlcat (x_score , s  , LEN_FULL);
      strlcat (x_terse , t  , LEN_FULL);
      strlcat (x_report, r  , LEN_FULL);
   }
   /*---(save-back)----------------------*/
   if (r_terse  != NULL)  strlcpy (r_terse , x_terse , LEN_FULL);
   if (r_score  != NULL)  strlcpy (r_score , x_score , LEN_FULL);
   if (r_full   != NULL)  strlcpy (r_full  , x_full  , LEN_FULL);
   if (r_report != NULL)  strlcpy (r_report, x_report, LEN_FULL);
   /*---(complete)-----------------------*/
   DEBUG_YENV   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char yenv_score_clear        (void) { return yenv_score__clear (s_audits, s_terse, s_score, s_full, s_report); }
char yENV_score_clear        (void) { return yenv_score__clear (s_TABLE , s_TERSE, s_SCORE, s_FULL, s_REPORT); }



/*====================------------------------------------====================*/
/*===----                       positioning                            ----===*/
/*====================------------------------------------====================*/
static void      o___POSITION______o (void) {;};

char
yenv_score__inc         (char a_sample, char *b_tpos, short *b_spos, short *b_rpos)
{
   /*---(locals)-----------+-----+-----+-*/
   char        t           =    0;
   char        s           =    0;
   char        r           =    0;
   /*---(set increment)------------------*/
   switch (a_sample) {
   case  0  :   t = 0;   s = 4;   r = 0;   break;
   case  1  :   t = 1;   s = 1;   r = 1;   break;
   case  3  :   t = 3;   s = 3;   r = 2;   break;
   default  :   t = 1;   s = 1;   r = 2;   break;
   }
   /*---(save-back)----------------------*/
   if (b_tpos != NULL)   *b_tpos += t;
   if (b_spos != NULL)   *b_spos += s;
   if (b_rpos != NULL)   *b_rpos += r;
   /*---(complete)-----------------------*/
   return 0;
}

char
yenv_score__accum       (tENV_SCORE *a_table, short n, short *b_tpos, short *b_spos, short *b_rpos)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   short       t           =    0;
   short       s           =    0;
   short       r           =    0;
   /*---(defense)------------------------*/
   --rce;  if (a_table == NULL)                  return rce;
   /*---(starting point)-----------------*/
   if (b_tpos != NULL)   t  = *b_tpos;
   if (b_spos != NULL)   s  = *b_spos;
   if (b_rpos != NULL)   r  = *b_rpos;
   /*---(specific adjustments)-----------*/
   if (n == 0)  r += 1;
   /*---(set increment)------------------*/
   rc = yenv_score__inc (a_table [n].s_sample, &t, &s, &r);
   --rce;  if (rc < 0)             return rce;
   /*---(checks)-------------------------*/
   --rce;  if (t <  0)             return rce;
   --rce;  if (t >= LEN_FULL - 1)  return rce;
   --rce;  if (s <  0)             return rce;
   --rce;  if (s >= LEN_FULL - 1)  return rce;
   --rce;  if (r <  0)             return rce;
   --rce;  if (r >= LEN_FULL - 1)  return rce;
   /*---(save-back)----------------------*/
   if (b_tpos != NULL)   *b_tpos = t;
   if (b_spos != NULL)   *b_spos = s;
   if (b_rpos != NULL)   *b_rpos = r;
   /*---(complete)-----------------------*/
   return 0;
}

char
yenv_score_accum        (tENV_SCORE *a_table, char a_type, short n, short *r_pos)
{
   switch (a_type) {
   case 't' :  return yenv_score__accum (a_table, n, r_pos, NULL , NULL );  break;
   case 's' :  return yenv_score__accum (a_table, n, NULL , r_pos, NULL );  break;
   case 'r' :  return yenv_score__accum (a_table, n, NULL , NULL , r_pos);  break;
   default  :  return -99;
   }
}

char
yenv_score__pos         (tENV_SCORE *a_table, char a_label [LEN_TERSE], short *r_tpos, short *r_spos, short *r_rpos)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         i           =    0;
   short       t           =    0;
   short       s           =    0;
   short       r           =    0;
   char        x_good      =  '-';
   /*---(header)-------------------------*/
   DEBUG_YENV   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YENV   yLOG_point   ("a_table"   , a_table);
   --rce;  if (a_table == NULL) {
      DEBUG_YENV   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(default)------------------------*/
   if (r_tpos != NULL)  *r_tpos = -1;
   if (r_spos != NULL)  *r_spos = -1;
   if (r_rpos != NULL)  *r_rpos = -1;
   /*---(defense)------------------------*/
   DEBUG_YENV   yLOG_point   ("a_label"   , a_label);
   --rce;  if (a_label == NULL || a_label [0] == '\0') {
      DEBUG_YENV    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YENV   yLOG_info    ("a_label"   , a_label);
   /*---(position)-----------------------*/
   for (i = 0; i < LEN_FULL; ++i) {
      /*---(test for end)----------------*/
      if (strncmp (a_table [i].s_label, "end-", 4) == 0)  break;
      /*---(drop-out)--------------------*/
      if (strcmp (a_table [i].s_label, a_label) == 0) {
         DEBUG_YENV   yLOG_value   ("FOUND"     , i);
         x_good = 'y';
         break;
      }
      /*---(accumulate)------------------*/
      rc = yenv_score__inc (a_table [i].s_sample, &t, &s, &r);
      --rce;  if (rc < 0)             return rce;
   }
   ++r;
   /*---(check for trouble)--------------*/
   DEBUG_YENV   yLOG_value   ("s"         , s);
   DEBUG_YENV   yLOG_value   ("t"         , t);
   DEBUG_YENV   yLOG_value   ("r"         , r);
   --rce;  if (x_good != 'y') {
      DEBUG_YENV    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(default)------------------------*/
   if (r_tpos != NULL)  *r_tpos = t;
   if (r_spos != NULL)  *r_spos = s;
   if (r_rpos != NULL)  *r_rpos = r;
   /*---(complete)-----------------------*/
   DEBUG_YENV    yLOG_exit    (__FUNCTION__);
   return 0;
}

char yenv_score_pos    (char a_label [LEN_TERSE], short *r_norm, short *r_terse, short *r_report)  { return yenv_score__pos (s_audits, a_label, r_norm, r_terse, r_report); }
char yENV_score_pos    (char a_label [LEN_TERSE], short *r_norm, short *r_terse, short *r_report)  { return yenv_score__pos (s_TABLE , a_label, r_norm, r_terse, r_report); }



/*====================------------------------------------====================*/
/*===----                       marking scores                         ----===*/
/*====================------------------------------------====================*/
static void      o___MARKING_______o (void) {;};

char
yenv_score__mark         (tENV_SCORE *a_table, char a_label [LEN_TERSE], uchar a_mark, char b_terse [LEN_FULL], char b_score [LEN_FULL], char b_report [LEN_FULL])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   short       t           =   -1;
   short       s           =   -1;
   short       r           =   -1;
   /*---(header)-------------------------*/
   DEBUG_YENV   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YENV   yLOG_point   ("a_table"   , a_table);
   --rce;  if (a_table == NULL) {
      DEBUG_YENV   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YENV   yLOG_value   ("a_mark"    , a_mark);
   --rce;  if (a_mark    < 32) {
      DEBUG_YENV    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YENV   yLOG_char    ("a_mark"    , a_mark);
   /*---(position)-----------------------*/
   rc = yenv_score__pos (a_table, a_label, &t, &s, &r);
   DEBUG_YENV   yLOG_value   ("pos"       , rc);
   --rce;  if (rc < 0) {
      DEBUG_YENV    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(update terse)-------------------*/
   if (b_terse != NULL) {
      DEBUG_YENV   yLOG_value   ("t"         , t);
      b_terse  [t] = a_mark;
      DEBUG_YENV   yLOG_info    ("b_terse"   , b_terse);
   }
   /*---(update score)-------------------*/
   if (b_score != NULL) {
      DEBUG_YENV   yLOG_value   ("s"         , s);
      b_score  [s] = a_mark;
      DEBUG_YENV   yLOG_info    ("b_score"   , b_score);
   }
   /*---(update report)------------------*/
   if (b_report != NULL) {
      DEBUG_YENV   yLOG_value   ("r"         , r);
      b_report [r] = a_mark;
      DEBUG_YENV   yLOG_info    ("b_report"  , b_report);
   }
   /*---(complete)-----------------------*/
   DEBUG_YENV    yLOG_exit    (__FUNCTION__);
   return 0;
}

char yenv_score_mark    (char a_label [LEN_TERSE], uchar a_mark)  { return yenv_score__mark  (s_audits, a_label, a_mark, s_terse, s_score, s_report); }
char yENV_score_mark    (char a_label [LEN_TERSE], uchar a_mark)  { return yenv_score__mark  (s_TABLE , a_label, a_mark, s_TERSE, s_SCORE, s_REPORT); }

char
yenv_score__value       (tENV_SCORE *a_table, char a_label [LEN_TERSE], char a_score [LEN_FULL])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   short       s           =   -1;
   char        x_value     =  '-';
   /*---(header)-------------------------*/
   DEBUG_YENV   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YENV   yLOG_point   ("a_table"   , a_table);
   --rce;  if (a_table == NULL) {
      DEBUG_YENV   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YENV   yLOG_point   ("a_score"   , a_score);
   --rce;  if (a_score == NULL) {
      DEBUG_YENV   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(position)-----------------------*/
   rc = yenv_score__pos (a_table, a_label, NULL, &s, NULL);
   DEBUG_YENV   yLOG_value   ("pos"       , rc);
   --rce;  if (rc < 0) {
      DEBUG_YENV    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YENV   yLOG_value   ("s"         , s);
   /*---(value)--------------------------*/
   x_value = a_score [s];
   DEBUG_YENV   yLOG_value   ("x_value"   , x_value);
   /*---(complete)-----------------------*/
   DEBUG_YENV    yLOG_exit    (__FUNCTION__);
   return x_value;
}

char yenv_score_value  (char a_label [LEN_TERSE])  { return yenv_score__value (s_audits, a_label, s_score); }
char yENV_score_value  (char a_label [LEN_TERSE])  { return yenv_score__value (s_TABLE , a_label, s_SCORE); }



/*====================------------------------------------====================*/
/*===----                        reporting support                     ----===*/
/*====================------------------------------------====================*/
static void      o___REPORT________o (void) {;};

char*
yenv_score__rpt_heads   (tENV_SCORE *a_table, char n)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         i           =    0;
   int         l           =    0;
   int         o           =    0;
   char        t           [LEN_SHORT] = "";
   /*---(header)-------------------------*/
   DEBUG_YENV   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YENV   yLOG_point   ("a_table"   , a_table);
   --rce;  if (a_table == NULL) {
      DEBUG_YENV   yLOG_exitr   (__FUNCTION__, rce);
      return "(no table)";
   }
   /*---(defense)------------------------*/
   --rce;  if (n < 0 || n > 6) {
      DEBUG_YENV   yLOG_exitr   (__FUNCTION__, rce);
      return g_print;
   }
   /*---(initialize)---------------------*/
   strcpy (g_print, "");
   /*---(create line)--------------------*/
   DEBUG_YENV   yLOG_note    ("PRINT LINES...");
   for (i = 0; i < LEN_FULL; ++i) {
      /*---(test for end)----------------*/
      if (strncmp (a_table [i].s_label, "end-", 4) == 0)  break;
      /*---(prepare)---------------------*/
      l = strlen (a_table [i].s_print);
      DEBUG_YENV   yLOG_complex ("item"      , "%3d, %c/%3d, %2d�%s�", i, a_table [i].s_sample, a_table [i].s_sample, l, a_table [i].s_print);
      /*---(normal stuff)---------------*/
      switch (a_table [i].s_sample) {
      case  0  : strcpy   (t, ""); break;
      case  1  : strcpy (t, " " ); break;
      case  3  : strcpy (t, "  "); break;
      default  :
                 if      (n == 0)   strcpy   (t, " -");
                 else if (n >  l)   strlcpy  (t, " �", LEN_SHORT);
                 else             { o = l - n; sprintf  (t, " %c", a_table [i].s_print [o]); }
      }
      strlcat (g_print, t  , LEN_FULL);
      /*---(done)------------------------*/
   }
   /*---(complete)-----------------------*/
   DEBUG_YENV    yLOG_exit    (__FUNCTION__);
   return g_print;
}

char* yenv_score_rpt_heads    (char n)   { return yenv_score__rpt_heads (s_audits, n); }
char* yENV_score_rpt_heads    (char n)   { return yenv_score__rpt_heads (s_TABLE , n); }

char*
yenv_score__title       (tENV_SCORE *a_table, char a_type)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         x_max       =    0;
   int         i           =    0;
   int         x_pos       =    0;
   int         l           =    0;
   int         o           =    0;
   int         j           =    0;
   /*---(header)-------------------------*/
   DEBUG_YENV   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YENV   yLOG_point   ("a_table"   , a_table);
   --rce;  if (a_table == NULL) {
      DEBUG_YENV   yLOG_exitr   (__FUNCTION__, rce);
      return "(no table)";
   }
   /*---(make base)----------------------*/
   DEBUG_YENV   yLOG_char    ("a_type"    , a_type);
   --rce;  switch (a_type) {
   case 't'  :  if (a_table == s_audits)   x_max = strlen (s_terse ); else x_max = strlen (s_TERSE );  break;
   case 's'  :  if (a_table == s_audits)   x_max = strlen (s_score ); else x_max = strlen (s_SCORE );  break;
   case 'r'  :  if (a_table == s_audits)   x_max = strlen (s_report); else x_max = strlen (s_REPORT);  break;
   default   :
                   DEBUG_YENV   yLOG_exitr   (__FUNCTION__, rce);
                   return "(bad type)";
   }
   DEBUG_YENV   yLOG_value   ("x_max"     , x_max);
   snprintf (g_print, LEN_FULL, "%*.*s", x_max, x_max, "                                                                                                                                                                                                        ");
   DEBUG_YENV   yLOG_complex ("g_print"   , "%3d�%s�", x_max, g_print);
   /*---(create)-------------------------*/
   --rce;  for (i = 0; i < LEN_FULL; ++i) {
      /*---(test for end)----------------*/
      if (strncmp (a_table [i].s_label, "end-", 4) == 0) {
         if (g_print [x_max - 1] == '�')  g_print [x_max - 1] = '�';
         break;
      }
      /*---(accumulate)------------------*/
      rc = yenv_score_accum (a_table, a_type, i, &x_pos);
      DEBUG_YENV   yLOG_complex ("accum"     , "%3d) %3d, inc %3d, pos %3d", i, a_table [i].s_sample, rc, x_pos);
      /*---(print)----------------------*/
      if (a_table [i].s_sample == 0) {
         /*---(prepare)---------------------*/
         l = strlen (a_table [i].s_print);
         DEBUG_YENV   yLOG_complex ("PREFIX"    , "%3d, %2d�%s�", i, l, a_table [i].s_print);
         for (j = 0; j < l; ++j) {
            if (a_type != 's')  o = j + x_pos;
            else                o = j + x_pos - 4;
            if (o < 0 || o >= x_max) {
               DEBUG_YENV   yLOG_exitr   (__FUNCTION__, rce);
               strlcat (g_print, "  (out of range)", LEN_FULL);
               return g_print;
            }
            DEBUG_YENV   yLOG_complex ("fill-in"   , "%3d, %c/%3d", o, a_table [i].s_print [j], a_table [i].s_print [j]);
            g_print [o] = a_table [i].s_print [j];
         }
         if (a_type != 's')  o = x_pos;
         else                o = x_pos - 4;
         for (j = o + l; j < x_max; ++j)   g_print [j] = '�';
      }
      if (a_table [i].s_sample == 3) {
         o = x_pos - 3;
         if (o > 0 && g_print [o - 1] == '�')  g_print [o - 1] = '�';
         if (g_print [o + 0] == '�')  g_print [o + 0] = ' ';
         if (g_print [o + 1] == '�')  g_print [o + 1] = ' ';
         if (g_print [o + 2] == '�')  g_print [o + 2] = ' ';
      }
      /*---(done)------------------------*/
   }
   /*---(complete)-----------------------*/
   DEBUG_YENV    yLOG_exit    (__FUNCTION__);
   return g_print;
}

char* yenv_score_title  (char a_type) { return yenv_score__title (s_audits, a_type); }
char* yENV_score_title  (char a_type) { return yenv_score__title (s_TABLE , a_type); }



/*====================------------------------------------====================*/
/*===----                        masking areas                         ----===*/
/*====================------------------------------------====================*/
static void      o___MASKING_______o (void) {;};

char
yenv_score__mask        (tENV_SCORE *a_table, char a_beg [LEN_TERSE], char a_end [LEN_TERSE], char b_terse [LEN_FULL], char b_score [LEN_FULL], char b_report [LEN_FULL])
{
   char         rce        =  -10;
   char         rc         =    0;
   int          i;
   short        bt, et;
   short        bs, es;
   short        br, er;
   --rce;  if (a_table == NULL)  return rce;
   rc = yenv_score__pos (a_table, a_beg, &bt, &bs, &br);
   --rce;  if (rc < 0)  return rce;
   --rce;  if (bs < 0)  return rce;
   rc = yenv_score__pos (a_table, a_end, &et, &es, &er);
   --rce;  if (rc < 0)  return rce;
   --rce;  if (es < 0)  return rce;
   if (b_terse  != NULL) { for (i = bt; i <= et; ++i)  b_terse  [i]   = '�'; }
   if (b_score  != NULL) { for (i = bs; i <= es; ++i)  b_score  [i]   = '�'; }
   if (b_report != NULL) { for (i = br; i <= er; ++i)  b_report [i]   = '�'; }
   return 0;
}

char yenv_score_mask         (char a_beg [LEN_TERSE], char a_end [LEN_TERSE])  { yenv_score__mask (s_audits, a_beg, a_end, s_terse, s_score, s_report); }
char yENV_score_mask         (char a_beg [LEN_TERSE], char a_end [LEN_TERSE])  { yenv_score__mask (s_TABLE , a_beg, a_end, s_TERSE, s_SCORE, s_REPORT); }

char yenv_score_nocheck      (void) { return yenv_score_mask ("PR� "      , "FIXES"     ); }
char yenv_score_nohacked     (void) { return yenv_score_mask ("HK� "      , "HACKED"    ); }



