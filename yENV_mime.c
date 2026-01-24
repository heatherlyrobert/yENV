/*===[[ START ]]==============================================================*/
#include    "yENV.h"
#include    "yENV_priv.h"



/*===[[ GNU GENERAL PUBLIC LICENSE (GPL) ]]===================================*/
/*´´·········1·········2·········3·········4·········5·········6·········7·········8  */

#define  P_COPYRIGHT   \
   "copyright (c) 2020 robert.s.heatherly at balsashrike at gmail dot com"

#define  P_LICENSE     \
   "the only place you could have gotten this code is my github, my website,¦"   \
   "or illegal sharing. given that, you should be aware that this is GPL licensed."

#define  P_COPYLEFT    \
   "the GPL COPYLEFT REQUIREMENT means any modifications or derivative works¦"   \
   "must be released under the same GPL license, i.e, must be free and open."

#define  P_INCLUDE     \
   "the GPL DOCUMENTATION REQUIREMENT means that you must include the original¦" \
   "copyright notice and the full licence text with any resulting anything."

#define  P_AS_IS       \
   "the GPL NO WARRANTY CLAUSE means the software is provided without any¦"      \
   "warranty and the author cannot be held liable for damages."

#define  P_THEFT    \
   "if you knowingly violate the spirit of these ideas, i suspect you might "    \
   "find any number of freedom-minded hackers may take it quite personally ;)"

/*´´·········1·········2·········3·········4·········5·········6·········7·········8  */
/*===[[ GNU GENERAL PUBLIC LICENSE (GPL) ]]===================================*/



/*´´·········1·········2·········3·········4·········5·········6·········7·········8  */
#define  P_FILE_FOCUS  \
   "yENV_mime is focused on identification of mime-types (multipurpose internet¦"  \
   "mail extensions) which have been used to identify file types, and now i am¦"   \
   "using in a slightly expanded context to identify data purpose."



/*>                                                                                   <* 
 *> s_dir_lib                                                                         <* 
 *> s_dir_ulib                                                                        <* 
 *> s_dir_llib                                                                        <* 
 *> s_dir_llib                                                                        <* 
 *>                                                                                   <*/


/*   a  ,x···0··R   { '¥··31|·x··6|·p·a'¥··2l·R, "¥··l·5x··f ·r"··24|·5x·i, "¥··f ·r"··w·2x·i, '¥··2l·r'·l··D·A };¥··6|·i'·' , ¥··n···,y      */

struct {
   char        m_level;
   char        m_format;
   char        m_mime      [LEN_TERSE];
   char        m_desc      [LEN_DESC];
   char        m_imp;                        /* my chosen primary formats shown as '@' */
   char        m_keep;                       /* Ï my content/modified,   useful/interrun, ´ nned to convert, · temp or can just reinstall */
   char        m_test      [LEN_DESC];       /* for use in testing line */
} static const s_mime [MAX_MIME] = {

   /*===[[ GRAND TOTAL ]]===============================================================*/
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp   keep   unit-test-example------------------------------------*/
   { 'T',  '-' , "TOTAL"     , "grand²total²values"                                , '-' , '·' , ""                                                  },

   /*===[[ AUDIO ]]=====================================================================*/
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp   keep   unit-test-example------------------------------------*/
   { 'C' , 'a' , "AUDIO"     , "auditory²formats,²like²music"                      , '-' , '·' , ""                                                  },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp   keep   unit-test-example------------------------------------*/
   { '·' , 'a' , "aiff"      , "apple²standard²audio"                              , '-' , '´' , ""                                                  },
   { '·' , 'a' , "aac"       , "advanced²audio²coding"                             , '-' , '´' , ""                                                  },
   { '·' , 'a' , "au"        , "sun²standard²audio"                                , '-' , '´' , ""                                                  },
   { '·' , 'a' , "m4a"       , "apple²unprotected²coding"                          , '-' , '´' , ""                                                  },
   { '·' , 'a' , "mp3"       , "mpeg²layer²3²audio"                                , '@' , 'Ï' , ""                                                  },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp   keep   unit-test-example------------------------------------*/
   { '·' , 'a' , "ogg"       , "open²source²vorbis"                                , '-' , '´' , ""                                                  },
   { '·' , 'a' , "ra"        , "realnetworks²real²audio"                           , '-' , '´' , ""                                                  },
   { '·' , 'a' , "raw"       , "raw²audio²for²testing"                             , '-' , '´' , ""                                                  },
   { '·' , 'a' , "wav"       , "microsoft²standard²audio"                          , '-' , '´' , ""                                                  },
   { '·' , 'a' , "wma"       , "microsoft²protected²audio"                         , '-' , '´' , ""                                                  },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp   keep   unit-test-example------------------------------------*/
   { '·' , 'a' , "mid"       , "midi²sound"                                        , '-' , '´' , ""                                                  },
   { '·' , 'a' , "midi"      , "midi²sound"                                        , '-' , '´' , ""                                                  },

   /*===[[ VIDEO ]]=====================================================================*/
   { 'C' , 'v' , "VIDEO"     , "moving²visual²formats,²like²movies"                , '-' , '·' , ""                                                  },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp   keep   unit-test-example------------------------------------*/
   { '·' , 'v' , "flv"       , "adobe²flash²video"                                 , '-' , '·' , ""                                                  },
   { '·' , 'v' , "f4v"       , "adobe²flash²video²(updated)"                       , '-' , '·' , ""                                                  },
   { '·' , 'v' , "avi"       , "standard²video"                                    , '-' , '·' , ""                                                  },
   { '·' , 'v' , "mov"       , "quicktime²video"                                   , '-' , '´' , ""                                                  },
   { '·' , 'v' , "qt"        , "quicktime²video"                                   , '-' , '´' , ""                                                  },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp   keep   unit-test-example------------------------------------*/
   { '·' , 'v' , "wmv"       , "windows²media²video"                               , '-' , '´' , ""                                                  },
   { '·' , 'v' , "rm"        , "realnetworks²real²video"                           , '-' , '´' , ""                                                  },
   { '·' , 'v' , "mp4"       , "mpeg²layer²4²video"                                , '@' , 'Ï' , ""                                                  },
   { '·' , 'v' , "m4p"       , "mpeg²layer²4²protected"                            , '-' , ' ' , ""                                                  },
   { '·' , 'v' , "m4v"       , "mpeg²layer²4²video"                                , '-' , ' ' , ""                                                  },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp   keep   unit-test-example------------------------------------*/
   { '·' , 'v' , "mpg"       , "mpeg²layer²1²video"                                , '-' , ' ' , ""                                                  },
   { '·' , 'v' , "mpeg"      , "mpeg²layer²1²video"                                , '-' , ' ' , ""                                                  },
   { '·' , 'v' , "mpe"       , "mpeg²layer²1²video"                                , '-' , '·' , ""                                                  },
   { '·' , 'v' , "mpv"       , "mpeg²layer²1²video"                                , '-' , '·' , ""                                                  },
   { '·' , 'v' , "swf"       , "flash²small²web"                                   , '-' , '·' , ""                                                  },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp   keep   unit-test-example------------------------------------*/

   /*===[[ IMAGE ]]=====================================================================*/
   { 'C' , 'i' , "IMAGE"     , "still²visual²formats,²like²pictures"               , '-' , '-' , ""                                                  },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp   keep   unit-test-example------------------------------------*/
   { '·' , 'i' , "jpg"       , "jpeg²compressed²image"                             , '@' , 'Ï' , ""                                                  },
   { '·' , 'i' , "jpeg"      , "jpeg²compressed²image"                             , '-' , 'Ï' , ""                                                  },
   { '·' , 'i' , "tif"       , "tagged²image²file"                                 , '-' , '·' , ""                                                  },
   { '·' , 'i' , "tiff"      , "tagged²image²file"                                 , '-' , ' ' , ""                                                  },
   { '·' , 'i' , "rif"       , "raw²image²format"                                  , '-' , '·' , ""                                                  },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp   keep   unit-test-example------------------------------------*/
   { '·' , 'i' , "gif"       , "graphics²interchange"                              , '-' , '´' , ""                                                  },
   { '·' , 'i' , "bmp"       , "microsoft²bitmap"                                  , '-' , ' ' , ""                                                  },
   { '·' , 'i' , "png"       , "portable²net²graphics"                             , '@' , 'Ï' , ""                                                  },
   { '·' , 'i' , "pngtile"   , "portable²net²graphics²as²yGLTEX·tiles"             , '@' , 'Ï' , ""                                                  },
   { '·' , 'i' , "ppm"       , "portable²pixmap"                                   , '-' , '´' , ""                                                  },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp   keep   unit-test-example------------------------------------*/
   { '·' , 'i' , "pgm"       , "portable²pixmap"                                   , '-' , '´' , ""                                                  },
   { '·' , 'i' , "pbm"       , "portable²pixmap"                                   , '-' , '´' , ""                                                  },
   { '·' , 'i' , "pnm"       , "portable²pixmap"                                   , '-' , '´' , ""                                                  },
   { '·' , 'i' , "psd"       , "photoshop²drawing"                                 , '-' , '´' , ""                                                  },
   { '·' , 'i' , "xpm"       , "x-windows²pixmap"                                  , '-' , '´' , ""                                                  },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp   keep   unit-test-example------------------------------------*/
   { '·' , 'i' , "xbm"       , "x-windows²pixmap"                                  , '-' , '´' , ""                                                  },
   { '·' , 'i' , "xpm2"      , "x-windows²pixmap"                                  , '-' , '´' , ""                                                  },
   { '·' , 'i' , "xpm3"      , "x-windows²pixmap"                                  , '-' , '´' , ""                                                  },
   { '·' , 'i' , "svg"       , "xml²vector²graphics"                               , '-' , '´' , ""                                                  },
   { '·' , 'i' , "svgz"      , "xml²vector²compressed"                             , '-' , '´' , ""                                                  },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp   keep   unit-test-example------------------------------------*/
   { '·' , 'i' , "svgb"      , "xml²vector²binary"                                 , '-' , '´' , ""                                                  },
   { '·' , 'i' , "dwg"       , "autocad²drawing²file"                              , '-' , 'Ï' , ""                                                  },
   { '·' , 'i' , "dxf"       , "autocad²drawing²exchange"                          , '-' , '´' , ""                                                  },
   { '·' , 'i' , "xcf"       , "gimp²drawing²file"                                 , '-' , '´' , ""                                                  },
   { '·' , 'i' , "tga"       , "targa²bitmap²file"                                 , '-' , '´' , ""                                                  },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp   keep   unit-test-example------------------------------------*/
   { '·' , 'i' , "pic"       , "picture²file"                                      , '-' , '´' , ""                                                  },
   { '·' , 'i' , "rgb"       , "silicongraphics²bitmap"                            , '-' , '´' , ""                                                  },
   { '·' , 'i' , "rgba"      , "silicongraphics²image"                             , '-' , '´' , ""                                                  },
   { '·' , 'i' , "sgi"       , "silicongraphics²bitmap"                            , '-' , '´' , ""                                                  },
   { '·' , 'i' , "aae"       , "apple²metadata²and²adjustment²file"                , '-' , '´' , ""                                                  },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp   keep   unit-test-example------------------------------------*/
   { '·' , 'i' , "ithmb"     , "apple²thumbnail²image²file"                        , '-' , '´' , ""                                                  },
   { '·' , 'i' , "bdf"       , "font²file²in²bit"                                  , '-' , '´' , ""                                                  },
   { '·' , 'i' , "sfd"       , "font²file²in²fontforge"                            , '-' , '´' , ""                                                  },
   { '·' , 'i' , "pcf"       , "font²file²in²pixel"                                , '-' , '´' , ""                                                  },
   { '·' , 'i' , "i_scan"    , "scan²and²document²archive"                         , '-' , 'Ï' , ""                                                  },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp   keep   unit-test-example------------------------------------*/
   { '·' , 'i' , "i_wall"    , "exoteric²roach²wallpaper"                          , '-' , 'Ï' , ""                                                  },
   { '·' , 'i' , "i_photo"   , "photo²from²phone²or²camera"                        , '-' , 'Ï' , ""                                                  },
   { '·' , 'i' , "psf"       , "pc²screen²font²(normal)"                           , '-' , '´' , ""                                                  },
   { '·' , 'i' , "psfu"      , "pc²screen²font²(unicode)"                          , '-' , '´' , ""                                                  },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp   keep   unit-test-example------------------------------------*/

   /*===[[ SOURCE ]]====================================================================*/
   { 'C' , 's' , "SOURCE"    , "computer²language²files²(not²config)"              , '-' , '-' , ""                                                  },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp   keep   unit-test-example------------------------------------*/
   { '·' , 's' , "ada"       , "ada²source²code"                                   , '-' , '·' , ""                                                  },
   { '·' , 's' , "asm"       , "assembly²language²source²code"                     , '@' , 'Ï' , ""                                                  },
   { '·' , 's' , "s"         , "assembly²language²source²code"                     , '-' , '·' , ""                                                  },
   { '·' , 's' , "bas"       , "basic²language²source²code"                        , '-' , '·' , ""                                                  },
   { '·' , 's' , "bat"       , "windows²batch²file"                                , '-' , '·' , ""                                                  },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp   keep   unit-test-example------------------------------------*/
   { '·' , 's' , "vb"        , "visual²basic²language²source²code"                 , '-' , '·' , ""                                                  },
   { '·' , 's' , "vbs"       , "visual²basic²language²source²code"                 , '-' , '·' , ""                                                  },
   { '·' , 's' , "cls"       , "visual²basic²language²source²code"                 , '-' , '·' , ""                                                  },
   { '·' , 's' , "cob"       , "cobol²language²source²code"                        , '-' , '·' , ""                                                  },
   { '·' , 's' , "cbl"       , "cobol²language²source²code"                        , '-' , '·' , ""                                                  },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp   keep   unit-test-example------------------------------------*/
   { '·' , 's' , "cpp"       , "c++²language²source²code"                          , '-' , '·' , ""                                                  },
   { '·' , 's' , "c++"       , "c++²language²source²code"                          , '-' , '·' , ""                                                  },
   { '·' , 's' , "cc"        , "c++²language²source²code"                          , '-' , '·' , ""                                                  },
   { '·' , 's' , "cxx"       , "c++²language²source²code"                          , '-' , '·' , ""                                                  },
   { '·' , 's' , "cbp"       , "c++²language²source²code"                          , '-' , '·' , ""                                                  },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp   keep   unit-test-example------------------------------------*/
   { '·' , 's' , "hpp"       , "c++²language²header²code"                          , '-' , '·' , ""                                                  },
   { '·' , 's' , "hxx"       , "c++²language²header²code"                          , '-' , '·' , ""                                                  },
   { '·' , 's' , "h++"       , "c++²language²header²code"                          , '-' , '·' , ""                                                  },
   { '·' , 's' , "hh"        , "c++²language²header²code"                          , '-' , '·' , ""                                                  },
   { '·' , 's' , "c"         , "ansi-c²source²code"                                , '@' , 'Ï' , "/home/system/khronos/khronos_base.c"               },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp   keep   unit-test-example------------------------------------*/
   { '·' , 's' , "h"         , "ansi-c²header"                                     , '@' , 'Ï' , "/home/system/khronos/khronos.h"                    },
   { '·' , 's' , "for"       , "fortran²language²source²code"                      , '-' , '·' , ""                                                  },
   { '·' , 's' , "ftn"       , "fortran²language²source²code"                      , '-' , '·' , ""                                                  },
   { '·' , 's' , "f"         , "fortran²language²source²code"                      , '-' , '·' , ""                                                  },
   { '·' , 's' , "f77"       , "fortran²language²source²code"                      , '-' , '·' , ""                                                  },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp   keep   unit-test-example------------------------------------*/
   { '·' , 's' , "f90"       , "fortran²language²source²code"                      , '-' , '·' , ""                                                  },
   { '·' , 's' , "java"      , "java²language²source²code"                         , '-' , '·' , ""                                                  },
   { '·' , 's' , "class"     , "java²language²source²code"                         , '-' , '·' , ""                                                  },
   { '·' , 's' , "jsm"       , "javascript²code²module"                            , '-' , '·' , ""                                                  },
   { '·' , 's' , "lisp"      , "lisp²language²source²code"                         , '-' , '·' , ""                                                  },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp   keep   unit-test-example------------------------------------*/
   { '·' , 's' , "m4"        , "m4²language²source²code"                           , '-' , '·' , ""                                                  },
   { '·' , 's' , "pas"       , "pascal²language²source²code"                       , '-' , '·' , ""                                                  },
   { '·' , 's' , "p"         , "pascal²language,²python²pickle"                    , '-' , '·' , ""                                                  },
   { '·' , 's' , "pp"        , "pascal²language²source²code"                       , '-' , '·' , ""                                                  },
   { '·' , 's' , "php"       , "php²language²source²code"                          , '-' , '·' , ""                                                  },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp   keep   unit-test-example------------------------------------*/
   { '·' , 's' , "php3"      , "php²language²source²code"                          , '-' , '·' , ""                                                  },
   { '·' , 's' , "php4"      , "php²language²source²code"                          , '-' , '·' , ""                                                  },
   { '·' , 's' , "php5"      , "php²language²source²code"                          , '-' , '·' , ""                                                  },
   { '·' , 's' , "phps"      , "php²language²source²code"                          , '-' , '·' , ""                                                  },
   { '·' , 's' , "pl"        , "perl²language²source²code"                         , '-' , '·' , ""                                                  },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp   keep   unit-test-example------------------------------------*/
   { '·' , 's' , "ph"        , "perl²language²header²file"                         , '-' , '·' , ""                                                  },
   { '·' , 's' , "pm"        , "perl²language²source²code"                         , '-' , '·' , ""                                                  },
   { '·' , 's' , "py"        , "python²language²source²code"                       , '-' , '·' , ""                                                  },
   { '·' , 's' , "rpy"       , "python²language²source²code"                       , '-' , '·' , ""                                                  },
   { '·' , 's' , "ptl"       , "python²template²language²file"                     , '-' , '·' , ""                                                  },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp   keep   unit-test-example------------------------------------*/
   { '·' , 's' , "pyt"       , "python²declaration²file"                           , '-' , '·' , ""                                                  },
   { '·' , 's' , "pyw"       , "python²gui²source²script"                          , '-' , '·' , ""                                                  },
   { '·' , 's' , "rb"        , "ruby²language²source²code"                         , '-' , '·' , ""                                                  },
   { '·' , 's' , "rbx"       , "ruby²language²source²code"                         , '-' , '·' , ""                                                  },
   { '·' , 's' , "rjs"       , "ruby²language²source²code"                         , '-' , '·' , ""                                                  },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp   keep   unit-test-example------------------------------------*/
   { '·' , 's' , "scm"       , "scheme²language²source²code"                       , '-' , '·' , ""                                                  },
   { '·' , 's' , "sh"        , "bash²shell²language²source²code"                   , '@' , 'Ï' , "/home/system/yLOG/ulog.sh"                         },
   { '·' , 's' , "shh"       , "bash²shell²language²source²code"                   , '-' , '´' , ""                                                  },
   { '·' , 's' , "ws"        , "windows²scripting²language"                        , '-' , '·' , ""                                                  },
   { '·' , 's' , "wsf"       , "windows²scripting,²studio²script"                  , '-' , '·' , ""                                                  },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp   keep   unit-test-example------------------------------------*/
   { '·' , 's' , "bash"      , "bash²shell²language²source²code"                   , '-' , '´' , ""                                                  },
   { '·' , 's' , "vim"       , "vim²script"                                        , '@' , 'Ï' , "/home/machine/vim/plugin/yTAG.vim"                 },
   { '·' , 's' , "awk"       , "awk²script²file"                                   , '-' , '´' , ""                                                  },
   { '·' , 's' , "in"        , "automake/autoconf²file"                            , '-' , '·' , ""                                                  },
   { '·' , 's' , "am"        , "automake/autoconf²definition"                      , '-' , '·' , ""                                                  },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp   keep   unit-test-example------------------------------------*/
   { '·' , 's' , "vcproj"    , "microsoft²visual²project"                          , '-' , '·' , ""                                                  },
   { '·' , 's' , "csproj"    , "microsoft²visual²project"                          , '-' , '·' , ""                                                  },
   { '·' , 's' , "vcp"       , "microsoft²visual²project"                          , '-' , '·' , ""                                                  },
   { '·' , 's' , "dsp"       , "microsoft²developer²project"                       , '-' , '·' , ""                                                  },
   { '·' , 's' , "dsw"       , "microsoft²developer²workspace"                     , '-' , '·' , ""                                                  },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp   keep   unit-test-example------------------------------------*/
   { '·' , 's' , "js"        , "microsoft²studio²javascript"                       , '-' , '·' , ""                                                  },
   { '·' , 's' , "cd"        , "microsoft²studio²class²diagram"                    , '-' , '·' , ""                                                  },
   { '·' , 's' , "config"    , "microsoft²studio²configuration"                    , '-' , '·' , ""                                                  },
   { '·' , 's' , "jsl"       , "microsoft²studio²javascript²assembly"              , '-' , '·' , ""                                                  },
   { '·' , 's' , "resx"      , "microsoft²studio²resources²file"                   , '-' , '·' , ""                                                  },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp   keep   unit-test-example------------------------------------*/
   { '·' , 's' , "res"       , "microsoft²studio²resources²compiled"               , '-' , '·' , ""                                                  },
   { '·' , 's' , "ico"       , "microsoft²studio²icon²file"                        , '-' , '·' , ""                                                  },
   { '·' , 's' , "cur"       , "microsoft²studio²cursor²file"                      , '-' , '·' , ""                                                  },
   { '·' , 's' , "rpt"       , "microsoft²studio²crystal²report"                   , '-' , '·' , ""                                                  },
   { '·' , 's' , "mdf"       , "microsoft²studio²sql²database"                     , '-' , '·' , ""                                                  },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp   keep   unit-test-example------------------------------------*/
   { '·' , 's' , "lua"       , "lua²script²file"                                   , '-' , '·' , ""                                                  },
   { '·' , 's' , "tmac"      , "groff²macro"                                       , '-' , '·' , ""                                                  },
   { '·' , 's' , "wbt"       , "wilson²window²ware²batch²script"                   , '-' , '·' , ""                                                  },
   { '·' , 's' , "htc"       , "microsoft²html²component²script"                   , '-' , '·' , ""                                                  },
   { '·' , 's' , "xul"       , "xml²user²interface²language"                       , '-' , '·' , ""                                                  },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp   keep   unit-test-example------------------------------------*/
   { '·' , 's' , "gcode"     , "control²language"                                  , '-' , '·' , ""                                                  },
   { '·' , 's' , "pc"        , "developer²program²creation²file"                   , '-' , '·' , ""                                                  },
   { '·' , 's' , "script"    , "vi-keys²macro²script"                              , '@' , 'Ï' , "/root/voyager.script"                              },
   { '·' , 's' , "macro"     , "vi-keys²macro²repository"                          , '@' , 'Ï' , ""                                                  },
   { '·' , 's' , "unit"      , "koios²unit²test²source"                            , '@' , 'Ï' , "/home/system/metis/metis_data.unit"                },
   { '·' , 's' , "munit"     , "micro²unit²test²source²(c-lang)"                   , '@' , 'Ï' , "/home/system/yLOG/yLOG_long.munit"                 },
   { '·' , 's' , "wave"      , "koios²unit²test²saved²specs"                       , '-' , ' ' , "/home/system/yVIEW/yVIEW_horz.wave"                },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp   keep   unit-test-example------------------------------------*/
   { '·' , 's' , "la"        , "gun²libtool²library²description"                   , '-' , '·' , ""                                                  },
   { '·' , 's' , "lo"        , "gun²libtool²library²support²file"                  , '-' , '·' , ""                                                  },
   { '·' , 's' , "nib"       , "apple²interface²builder"                           , '-' , '·' , ""                                                  },
   { '·' , 's' , "strings"   , "used²to²localize²program"                          , '-' , '·' , ""                                                  },
   { '·' , 's' , "actual"    , "unstructured²unit²testing²results"                 , '-' , '·' , ""                                                  },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp   keep   unit-test-example------------------------------------*/
   { '·' , 's' , "expect"    , "unstructured²unit²testing²expects"                 , '-' , '·' , ""                                                  },
   { '·' , 's' , "make"      , "generic²make²file²extension"                       , '-' , 'Ï' , ""                                                  },
   { '·' , 's' , "makefile"  , "generic²make²file"                                 , '@' , 'Ï' , "/home/system/polymnia/Makefile"                    },
   { '·' , 's' , "mmake"     , "master²make²file"                                  , '@' , 'Ï' , "/home/system/Mmake"                                },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp   keep   unit-test-example------------------------------------*/
   { '·' , 's' , "patch"     , "quilt²patch²for²updating²code"                     , '-' , '·' , ""                                                  },
   { '·' , 's' , "dpatch"    , "debian²patch²for²updating²code"                    , '-' , '·' , ""                                                  },
   { '·' , 's' , "stdin"     , "unstructured²unit²testing²input"                   , '-' , '·' , ""                                                  },
   { '·' , 's' , "stdout"    , "unstructured²unit²testing²input"                   , '-' , '·' , ""                                                  },
   { '·' , 's' , "tcl"       , "tool²command²language"                             , '-' , '·' , ""                                                  },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp   keep   unit-test-example------------------------------------*/
   { '·' , 's' , "initd"     , "initialization²script"                             , '-' , '·' , ""                                                  },
   { '·' , 's' , "confd"     , "initialization²configuration"                      , '-' , '·' , ""                                                  },
   { '·' , 's' , "eclass"    , "bash²script²for²ebuild²environment"                , '-' , '·' , ""                                                  },
   { '·' , 's' , "rpm"       , "redhat²package²distribution²format"                , '-' , '·' , ""                                                  },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp   keep   unit-test-example------------------------------------*/

   /*===[[ ASCII TEXT ]]================================================================*/
   { 'C' , 't' , "TEXT"      , "ascii-text²files²(plain²and²structured)"           , '-' , '-' , ""                                                  },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp   keep   unit-test-example------------------------------------*/
   { '·' , 't' , "txt"       , "normal²text²file"                                  , '@' , 'Ï' , "/home/memeber/testing_data.txt"                    },
   { '·' , 't' , "asciiart"  , "normal²text²file²containing²ascii²art"             , '@' , 'Ï' , ""                                                  },
   { '·' , 't' , "rptg"      , "text²output²file²(write²only)"                     , '-' , ' ' , "/var/lib/helios/helios_mime.rptg"                  },
   { '·' , 't' , "ctrl"      , "inter-run²report/stats²storage²(rw)"               , '-' , ' ' , "/var/lib/helios/helios_mime.ctrl"                  },
   { '·' , 't' , "csv"       , "comma²seperated²values"                            , '-' , '·' , ""                                                  },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp   keep   unit-test-example------------------------------------*/
   { '·' , 't' , "tsv"       , "tab²seperated²values"                              , '-' , '·' , ""                                                  },
   { '·' , 't' , "howto"     , "heatherly²howto/notes"                             , '@' , 'Ï' , "/home/member/h_kane/man.howto"                     },
   { '·' , 't' , "conf"      , "configuration²file"                                , '@' , 'Ï' , "/etc/helios.conf"                                  },
   { '·' , 't' , "conf+"     , "configuration²file²(no²ext)"                       , '-' , 'Ï' , "/etc/sudoers"                                      },
   { '·' , 't' , "use"       , "gentoo²portage²use²flags"                          , '@' , 'Ï' , "/etc/portage/package.use"                          },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp   keep   unit-test-example------------------------------------*/
   { '·' , 't' , "ini"       , "windows²configuration²file"                        , '-' , '·' , ""                                                  },
   { '·' , 't' , "defs"      , "alternate²configuration²file"                      , '-' , '·' , ""                                                  },
   { '·' , 't' , "cfg"       , "alternate²configuration²file"                      , '-' , '·' , ""                                                  },
   { '·' , 't' , "xml"       , "extended²markup²language"                          , '-' , '·' , ""                                                  },
   { '·' , 't' , "rules"     , "custom²build²xml²rules²file"                       , '-' , '·' , ""                                                  },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp   keep   unit-test-example------------------------------------*/
   { '·' , 't' , "tmpl"      , "unix²template²file"                                , '-' , '·' , ""                                                  },
   { '·' , 't' , "def"       , "unix²definition²file"                              , '-' , '·' , ""                                                  },
   { '·' , 't' , "rdf"       , "firefox²and²database²xml-like²file"                , '-' , '·' , ""                                                  },
   { '·' , 't' , "json"      , "javascript²object²notation²format"                 , '-' , '·' , ""                                                  },
   { '·' , 't' , "htm"       , "hypertext²markup²language"                         , '-' , '·' , ""                                                  },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp   keep   unit-test-example------------------------------------*/
   { '·' , 't' , "html"      , "hypertext²markup²language"                         , '-' , '·' , ""                                                  },
   { '·' , 't' , "xhtml"     , "hypertext²markup²language"                         , '-' , '·' , ""                                                  },
   { '·' , 't' , "rhtml"     , "ruby²hypertext²markup²language²file"               , '-' , '·' , ""                                                  },
   { '·' , 't' , "css"       , "cascading²style²sheet"                             , '-' , '·' , ""                                                  },
   { '·' , 't' , "epub"      , "open²book²standard"                                , '@' , '·' , ""                                                  },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp   keep   unit-test-example------------------------------------*/
   { '·' , 't' , "pdf"       , "adobe²portable²document"                           , '@' , 'Ï' , ""                                                  },
   { '·' , 't' , "rtf"       , "rich²text²format"                                  , '-' , '·' , ""                                                  },
   { '·' , 't' , "eps"       , "encapsulated²postscript"                           , '-' , '·' , ""                                                  },
   { '·' , 't' , "ps"        , "postscript"                                        , '-' , '·' , ""                                                  },
   { '·' , 't' , "theme"     , "application²theming²file"                          , '-' , '·' , ""                                                  },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp   keep   unit-test-example------------------------------------*/
   { '·' , 't' , "ent"       , "bittorrent²information²file"                       , '-' , '·' , ""                                                  },
   { '·' , 't' , "dtd"       , "document²type²definition²file"                     , '-' , '·' , ""                                                  },
   { '·' , 't' , "xsl"       , "xml²style²sheet"                                   , '-' , '·' , ""                                                  },
   { '·' , 't' , "dsl"       , "dsssl²style²sheet"                                 , '-' , '·' , ""                                                  },
   { '·' , 't' , "xsd"       , "xml²schema²description²file"                       , '-' , '·' , ""                                                  },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp   keep   unit-test-example------------------------------------*/
   { '·' , 't' , "torrent"   , "bittorrent²information²file"                       , '-' , '·' , ""                                                  },
   { '·' , 't' , "nanorc"    , "nano²editor²configuration"                         , '-' , '·' , ""                                                  },
   { '·' , 't' , "vimrc"     , "vim²editor²configuration"                          , '@' , 'Ï' , ""                                                  },
   { '·' , 't' , "mo"        , "gnu²gettext²file"                                  , '-' , '·' , ""                                                  },
   { '·' , 't' , "gmo"       , "gnu²gettext²file"                                  , '-' , '·' , ""                                                  },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp   keep   unit-test-example------------------------------------*/
   { '·' , 't' , "gyges"     , "gyges²spreadsheet"                                 , '@' , 'Ï' , ""                                                  },
   { '·' , 't' , "texi"      , "texinfo²documentation"                             , '-' , '·' , ""                                                  },
   { '·' , 't' , "sgml"      , "sgml²document²file"                                , '-' , '·' , ""                                                  },
   { '·' , 't' , "inc"       , "include²file"                                      , '-' , '·' , ""                                                  },
   { '·' , 't' , "info"      , "gnu²info²reader²file"                              , '-' , '·' , ""                                                  },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp   keep   unit-test-example------------------------------------*/
   { '·' , 't' , "rst"       , "python²restructured²text²doc²file"                 , '-' , '·' , ""                                                  },
   { '·' , 't' , "rest"      , "python²restructured²text²doc²file"                 , '-' , '·' , ""                                                  },
   { '·' , 't' , "daily"     , "heatherly²time²tracking"                           , '-' , '·' , ""                                                  },
   { '·' , 't' , "url"       , "internet²url"                                      , '-' , '·' , ""                                                  },
   { '·' , 't' , "x"         , "man²file"                                          , '-' , '·' , ""                                                  },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp   keep   unit-test-example------------------------------------*/
   { '·' , 't' , "pod"       , "perl²documentation²file"                           , '-' , '·' , ""                                                  },
   { '·' , 't' , "arac"      , "arachne²sequencing²file"                           , '-' , '·' , ""                                                  },
   { '·' , 't' , "r_link"    , "link²to²another²file"                              , '-' , '·' , ""                                                  },
   { '·' , 't' , "tags"      , "ctag²tags²file"                                    , '-' , '·' , ""                                                  },
   { '·' , 't' , "changes"   , "generic²software²helper²file"                      , '-' , '·' , ""                                                  },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp   keep   unit-test-example------------------------------------*/
   { '·' , 't' , "copying"   , "generic²software²helper²file"                      , '-' , '·' , ""                                                  },
   { '·' , 't' , "readme"    , "generic²software²helper²file"                      , '-' , '·' , ""                                                  },
   { '·' , 't' , "todo"      , "generic²software²helper²file"                      , '-' , '·' , ""                                                  },
   { '·' , 't' , "copyright" , "generic²software²helper²file"                      , '-' , '·' , ""                                                  },
   { '·' , 't' , "changelog" , "generic²software²helper²file"                      , '-' , '·' , ""                                                  },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp   keep   unit-test-example------------------------------------*/
   { '·' , 't' , "install"   , "generic²software²helper²file"                      , '-' , '·' , ""                                                  },
   { '·' , 't' , "license"   , "generic²software²helper²file"                      , '-' , '·' , ""                                                  },
   { '·' , 't' , "manifest"  , "generic²software²helper²file"                      , '-' , '·' , ""                                                  },
   { '·' , 't' , "md"        , "generic²software²helper²file"                      , '-' , '·' , ""                                                  },
   { '·' , 't' , "manual"    , "man²documentation²file"                            , '@' , 'Ï' , ""                                                  },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp   keep   unit-test-example------------------------------------*/
   { '·' , 't' , "tasks"     , "metis²task²management²data"                        , '@' , 'Ï' , ""                                                  },
   { '·' , 't' , "diff"      , "linux²file²comparison²output"                      , '-' , '·' , ""                                                  },
   { '·' , 't' , "uni"       , "unicode²maps"                                      , '-' , '·' , ""                                                  },
   { '·' , 't' , "scrn"      , "ncurses²screen·print"                              , '-' , '·' , ""                                                  },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp   keep   unit-test-example------------------------------------*/

   /*===[[ DATABASE ]]==================================================================*/
   { 'C' , 'b' , "DBASE"     , "databases²(binary,²relational,²etc)"               , '-' , '·' , ""                                                  },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp   keep   unit-test-example------------------------------------*/
   { '·' , 'b' , "db"        , "unix²database²(binary)"                            , '@' , 'Ï' , "/var/lib/helios/helios.db"                         },
   { '·' , 'b' , "dbf"       , "dbase²file"                                        , '-' , 'Ï' , ""                                                  },
   { '·' , 'b' , "mdb"       , "microsoft²access²database"                         , '-' , '·' , ""                                                  },
   { '·' , 'b' , "acad"      , "autocad²database"                                  , '-' , '·' , ""                                                  },
   { '·' , 'b' , "odb"       , "openoffice²database"                               , '-' , '·' , ""                                                  },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp   keep   unit-test-example------------------------------------*/
   { '·' , 'b' , "dat"       , "generic²file²storage"                              , '-' , '·' , ""                                                  },
   { '·' , 'b' , "sqlite"    , "sqlite²database²file"                              , '-' , '·' , ""                                                  },
   { '·' , 'b' , "tbd"       , "text-based·database"                               , '@' , 'Ï' , ""                                                  },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp   keep   unit-test-example------------------------------------*/

   /*===[[ ENCRYPTED ]]=================================================================*/
   { 'C' , 'c' , "CRYPT"     , "compressed²and²encrypted²files"                    , '-' , '·' , ""                                                  },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp   keep   unit-test-example------------------------------------*/
   { '·' , 'c' , "gz"        , "gzip²compressed²file"                              , '@' , 'Ï' , ""                                                  },
   { '·' , 'c' , "tgz"       , "gzip²compressed²tar"                               , '-' , 'Ï' , ""                                                  },
   { '·' , 'c' , "bz2"       , "bzip2²compressed²file"                             , '-' , 'Ï' , ""                                                  },
   { '·' , 'c' , "tbz"       , "bzip2²compressed²tar"                              , '-' , 'Ï' , ""                                                  },
   { '·' , 'c' , "tbz2"      , "bzip2²compressed²tar"                              , '-' , 'Ï' , ""                                                  },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp   keep   unit-test-example------------------------------------*/
   { '·' , 'c' , "hqx"       , "mac²binhex²compressed"                             , '-' , '·' , ""                                                  },
   { '·' , 'c' , "zip"       , "zipped²compressed²file"                            , '-' , '·' , ""                                                  },
   { '·' , 'c' , "zipx"      , "zipped²compressed²file"                            , '-' , '·' , ""                                                  },
   { '·' , 'c' , "sit"       , "stuffit²compressed"                                , '-' , '·' , ""                                                  },
   { '·' , 'c' , "sitx"      , "stuffit²compressed"                                , '-' , '·' , ""                                                  },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp   keep   unit-test-example------------------------------------*/
   { '·' , 'c' , "pit"       , "packit²compressed"                                 , '-' , '·' , ""                                                  },
   { '·' , 'c' , "cpio"      , "unix²cpio²archive"                                 , '-' , '·' , ""                                                  },
   { '·' , 'c' , "tar"       , "unix²tar²archive"                                  , '-' , '·' , ""                                                  },
   { '·' , 'c' , "iso"       , "unix²distribution"                                 , '-' , '·' , ""                                                  },
   { '·' , 'c' , "lz"        , "lzma²compressed²file"                              , '-' , '·' , ""                                                  },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp   keep   unit-test-example------------------------------------*/
   { '·' , 'c' , "lzma"      , "lzma²compressed²file"                              , '-' , '·' , ""                                                  },
   { '·' , 'c' , "xz"        , "lzma²compressed²file"                              , '-' , '·' , ""                                                  },
   { '·' , 'c' , "lzo"       , "lzo²compressed²file"                               , '-' , '·' , ""                                                  },
   { '·' , 'c' , "z"         , "huffman²compressed"                                , '-' , '·' , ""                                                  },
   { '·' , 'c' , "s7z"       , "7-zip²compressed"                                  , '-' , '·' , ""                                                  },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp   keep   unit-test-example------------------------------------*/
   { '·' , 'c' , "cab"       , "windows²compressed²file"                           , '-' , '·' , ""                                                  },
   { '·' , 'c' , "rar"       , "rar²compressed²file"                               , '-' , '·' , ""                                                  },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp   keep   unit-test-example------------------------------------*/


   /*===[[ PROPRIETARY ]]===============================================================*/
   { 'C' , 'p' , "PROP"      , "proprietary²and²commercial²formats"                , '-' , '·' , ""                                                  },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp   keep   unit-test-example------------------------------------*/
   { '·' , 'p' , "ebuild"    , "gentoo²ebuild²for²portage"                         , '-' , '·' , ""                                                  },
   { '·' , 'p' , "xls"       , "ms²excel²(older)"                                  , '-' , '·' , ""                                                  },
   { '·' , 'p' , "xlsx"      , "ms²excel²(newer)"                                  , '-' , '·' , ""                                                  },
   { '·' , 'p' , "xlsm"      , "ms²excel"                                          , '-' , '·' , ""                                                  },
   { '·' , 'p' , "xlw"       , "ms²excel²workbook"                                 , '-' , '·' , ""                                                  },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp   keep   unit-test-example------------------------------------*/
   { '·' , 'p' , "wk3"       , "lotus²1-2-3²worksheet"                             , '-' , '·' , ""                                                  },
   { '·' , 'p' , "doc"       , "ms²word²(older)"                                   , '-' , '·' , ""                                                  },
   { '·' , 'p' , "docx"      , "ms²word²(newer)"                                   , '-' , '·' , ""                                                  },
   { '·' , 'p' , "dot"       , "ms²word²template"                                  , '-' , '·' , ""                                                  },
   { '·' , 'p' , "ppt"       , "ms²powerpoint²(older)"                             , '-' , '·' , ""                                                  },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp   keep   unit-test-example------------------------------------*/
   { '·' , 'p' , "pptm"      , "ms²powerpoint²(older)"                             , '-' , '·' , ""                                                  },
   { '·' , 'p' , "pptx"      , "ms²powerpoint²(newer)"                             , '-' , '·' , ""                                                  },
   { '·' , 'p' , "mpp"       , "ms²project²file"                                   , '-' , '·' , ""                                                  },
   { '·' , 'p' , "odc"       , "openoffice²file"                                   , '-' , '·' , ""                                                  },
   { '·' , 'p' , "odi"       , "openoffice²image"                                  , '-' , '·' , ""                                                  },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp   keep   unit-test-example------------------------------------*/
   { '·' , 'p' , "oti"       , "openoffice²image²template"                         , '-' , '·' , ""                                                  },
   { '·' , 'p' , "odp"       , "openoffice²presentation"                           , '-' , '·' , ""                                                  },
   { '·' , 'p' , "otp"       , "openoffice²presentation²template"                  , '-' , '·' , ""                                                  },
   { '·' , 'p' , "opf"       , "openoffice²document²interchange"                   , '-' , '·' , ""                                                  },
   { '·' , 'p' , "opg"       , "openoffice²drawing²file"                           , '-' , '·' , ""                                                  },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp   keep   unit-test-example------------------------------------*/
   { '·' , 'p' , "sda"       , "openoffice²drawing²file"                           , '-' , '·' , ""                                                  },
   { '·' , 'p' , "ops"       , "openoffice²spreadsheet"                            , '-' , '·' , ""                                                  },
   { '·' , 'p' , "ods"       , "openoffice²spreadsheet"                            , '-' , '·' , ""                                                  },
   { '·' , 'p' , "sdc"       , "openoffice²spreadsheet"                            , '-' , '·' , ""                                                  },
   { '·' , 'p' , "sxc"       , "openoffice²spreadsheet"                            , '-' , '·' , ""                                                  },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp   keep   unit-test-example------------------------------------*/
   { '·' , 'p' , "oos"       , "openoffice²spreadsheet"                            , '-' , '·' , ""                                                  },
   { '·' , 'p' , "opt"       , "openoffice²text²document"                          , '-' , '·' , ""                                                  },
   { '·' , 'p' , "oot"       , "openoffice²text²document"                          , '-' , '·' , ""                                                  },
   { '·' , 'p' , "sxw"       , "openoffice²text²document"                          , '-' , '·' , ""                                                  },
   { '·' , 'p' , "jar"       , "java²archive²file"                                 , '-' , '·' , ""                                                  },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp   keep   unit-test-example------------------------------------*/
   { '·' , 'p' , "gbr"       , "gimp²brush²file"                                   , '-' , '·' , ""                                                  },
   { '·' , 'p' , "slk"       , "silk²spreadsheet²file"                             , '-' , '·' , ""                                                  },
   { '·' , 'p' , "oleo"      , "oleo²spreadsheet²file"                             , '-' , '·' , ""                                                  },
   { '·' , 'p' , "font"      , "font²file"                                         , '-' , '·' , ""                                                  },
   { '·' , 'p' , "afm"       , "adobe²font²metrics"                                , '-' , '·' , ""                                                  },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp   keep   unit-test-example------------------------------------*/
   { '·' , 'p' , "ttf"       , "truetype²font"                                     , '-' , '·' , ""                                                  },
   { '·' , 'p' , "dict"      , "dictionary²file"                                   , '-' , '·' , ""                                                  },
   { '·' , 'p' , "cmake"     , "cmake²module²file"                                 , '-' , '·' , ""                                                  },
   { '·' , 'p' , "txf"       , "opengl²font"                                       , '-' , '·' , ""                                                  },
   { '·' , 'p' , "lnk"       , "microsoft²symbolic²link"                           , '-' , '·' , ""                                                  },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp   keep   unit-test-example------------------------------------*/
   { '·' , 'p' , "xpt"       , "firefox²component"                                 , '-' , '·' , ""                                                  },
   { '·' , 'p' , "dip"       , "diptrace²electronics²design²file"                  , '-' , '·' , ""                                                  },
   { '·' , 'p' , "xpi"       , "firefox²extension²installation²file"               , '-' , '·' , ""                                                  },
   { '·' , 'p' , "mf"        , "java²manifest²file²for²archives"                   , '-' , '·' , ""                                                  },
   { '·' , 'p' , "crt"       , "firefox²certificate"                               , '-' , '·' , ""                                                  },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp   keep   unit-test-example------------------------------------*/

   /*===[[ EXECUTABLE ]]================================================================*/
   { 'C' , 'x' , "EXEC"      , "directly²executable²files"                         , '-' , '·' , ""                                                  },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp   keep   unit-test-example------------------------------------*/
   { '·' , 'x' , "a"         , "unix²static²library"                               , '-' , '·' , ""                                                  },
   { '·' , 'x' , "a_debug"   , "unix²static²library²(debug)"                       , '-' , '·' , ""                                                  },
   { '·' , 'x' , "a_link"    , "unix²static²library²(linked)"                      , '-' , '·' , ""                                                  },
   { '·' , 'x' , "ar"        , "unix²static²library"                               , '-' , '·' , ""                                                  },
   { '·' , 'x' , "so"        , "unix²shared²library"                               , '@' , 'Ï' , ""                                                  },
   { '·' , 'x' , "so_debug"  , "unix²shared²library²(debug)"                       , '@' , 'Ï' , ""                                                  },
   { '·' , 'x' , "so_link"   , "unix²shared²library²(linked)"                      , '@' , 'Ï' , ""                                                  },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp   keep   unit-test-example------------------------------------*/
   { '·' , 'x' , "dll"       , "dynamic²library"                                   , '-' , '·' , ""                                                  },
   { '·' , 'x' , "bfd"       , "gnu²binary²descriptor"                             , '-' , '·' , ""                                                  },
   { '·' , 'x' , "exe"       , "executable²file"                                   , '-' , '·' , ""                                                  },
   { '·' , 'x' , "com"       , "executable²file"                                   , '-' , '·' , ""                                                  },
   { '·' , 'x' , "pyc"       , "compiled²python²script"                            , '-' , '·' , ""                                                  },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp   keep   unit-test-example------------------------------------*/
   { '·' , 'x' , "pyo"       , "compiled²python²file"                              , '-' , '·' , ""                                                  },
   { '·' , 'x' , "rake"      , "compiled²ruby²script"                              , '-' , '·' , ""                                                  },
   { '·' , 'x' , "pyd"       , "python²dynamic²module"                             , '-' , '·' , ""                                                  },
   { '·' , 'x' , "debug"     , "gnu²program²debug"                                 , '-' , '·' , ""                                                  },
   { '·' , 'x' , "x_exec"    , "unix²exec²(no²ext)"                                , '@' , 'Ï' , ""                                                  },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp   keep   unit-test-example------------------------------------*/
   { '·' , 'x' , "x_debug"   , "unix²exec²(heatherly²debug)"                       , '@' , 'Ï' , ""                                                  },
   { '·' , 'x' , "x_unit"    , "unix²exec²(heatherly²unit)"                        , '-' , '·' , ""                                                  },
   { '·' , 'x' , "c_dev"     , "unix²character²device"                             , '-' , 'Ï' , ""                                                  },
   { '·' , 'x' , "c_link"    , "link²to²char²device"                               , '-' , '·' , ""                                                  },
   { '·' , 'x' , "b_dev"     , "unix²block²device"                                 , '-' , 'Ï' , ""                                                  },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp   keep   unit-test-example------------------------------------*/
   { '·' , 'x' , "b_link"    , "link²to²block²device"                              , '-' , '·' , ""                                                  },
   { '·' , 'x' , "p_pipe"    , "unix²fifo/pipe²communications"                     , '-' , 'Ï' , ""                                                  },
   { '·' , 'x' , "p_link"    , "link²to²fifo/pipe²file"                            , '-' , '·' , ""                                                  },
   { '·' , 'x' , "i_socket"  , "unix²ip²socket²file"                               , '-' , 'Ï' , ""                                                  },
   { '·' , 'x' , "i_link"    , "link²to²socket²file"                               , '-' , '·' , ""                                                  },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp   keep   unit-test-example------------------------------------*/
   { '·' , 'x' , "x_link"    , "link²to²executable"                                , '-' , '·' , ""                                                  },
   { '·' , 'x' , "x_hidden"  , "hidden²executable"                                 , '-' , '·' , ""                                                  },
   { '·' , 'x' , "img"       , "iso²binary²image²file"                             , '-' , '·' , ""                                                  },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp   keep   unit-test-example------------------------------------*/

   /*===[[ DIRECTORIES ]]===============================================================*/
   { 'C' , 'd' , "DIR"       , "file²directories"                                  , '-' , '-' , ""                                                  },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp   keep   unit-test-example------------------------------------*/
   { '·' , 'd' , "d_dir"     , "directory"                                         , '@' , 'Ï' , ""                                                  },
   { '·' , 'd' , "d_link"    , "link²to²another²directory"                         , '-' , 'Ï' , ""                                                  },
   { '·' , 'd' , "d_hidden"  , "hidden²directory"                                  , '-' , 'Ï' , ""                                                  },
   { '·' , 'd' , "d_gitroot" , "git²root²directories"                              , '-' , 'Ï' , ""                                                  },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp   keep   unit-test-example------------------------------------*/

   /*===[[ JUNK ]]======================================================================*/
   { 'C' , 'j' , "TEMP"      , "temporary²and²transcient²files"                    , '-' , '-' , ""                                                  },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp   keep   unit-test-example------------------------------------*/
   { '·' , 'j' , "swp"       , "swap²file"                                         , '-' , '·' , ""                                                  },
   { '·' , 'j' , "swo"       , "swap²file"                                         , '-' , '·' , ""                                                  },
   { '·' , 'j' , "backup"    , "simple/copied²file"                                , '-' , '·' , ""                                                  },
   { '·' , 'j' , "b_tilde"   , "tilde²suffix²file"                                 , '-' , '·' , ""                                                  },
   { '·' , 'j' , "old"       , "simple/copied²file"                                , '-' , '·' , ""                                                  },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp   keep   unit-test-example------------------------------------*/
   { '·' , 'j' , "sav"       , "simple/copied²file"                                , '-' , '·' , ""                                                  },
   { '·' , 'j' , "save"      , "simple/copied²file"                                , '-' , '·' , ""                                                  },
   { '·' , 'j' , "bak"       , "simple/copied²file"                                , '-' , '·' , ""                                                  },
   { '·' , 'j' , "cache"     , "temporary²storage"                                 , '-' , '·' , ""                                                  },
   { '·' , 'j' , "tmp"       , "temporary²file"                                    , '-' , '·' , ""                                                  },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp   keep   unit-test-example------------------------------------*/
   { '·' , 'j' , "temp"      , "temporary²file"                                    , '-' , '·' , ""                                                  },
   { '·' , 'j' , "log"       , "unix²log²file"                                     , '-' , '·' , ""                                                  },
   { '·' , 'j' , "urun"      , "yUNIT²unit²test²output²file"                       , '-' , '·' , ""                                                  },
   { '·' , 'j' , "murun"     , "yUNIT²micro²unit²test²output²file"                 , '-' , '·' , ""                                                  },
   { '·' , 'j' , "ulog"      , "heatherly²log²file"                                , '-' , '·' , ""                                                  },
   { '·' , 'j' , "out"       , "unstructed²dump²file"                              , '-' , '·' , ""                                                  },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp   keep   unit-test-example------------------------------------*/
   { '·' , 'j' , "dmp"       , "program²crash²file"                                , '-' , '·' , ""                                                  },
   { '·' , 'j' , "dump"      , "text²reporting²file"                               , '-' , '·' , ""                                                  },
   { '·' , 'j' , "o"         , "compilier²object²file"                             , '-' , '·' , ""                                                  },
   { '·' , 'j' , "os"        , "stripped²object²file"                              , '-' , '·' , ""                                                  },
   { '·' , 'j' , "obj"       , "microsoft²object²file"                             , '-' , '·' , ""                                                  },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp   keep   unit-test-example------------------------------------*/
   { '·' , 'j' , "po"        , "object²file²portable"                              , '-' , '·' , ""                                                  },
   { '·' , 'j' , "lib-"      , "uninstalled/dup²library"                           , '-' , '·' , ""                                                  },
   { '·' , 'j' , "exec-"     , "unistalled/dup²exec"                               , '-' , '·' , ""                                                  },
   { '·' , 'j' , "unit-"     , "compiled²unit²test"                                , '-' , '·' , ""                                                  },
   { '·' , 'j' , "calls"     , "polyhmnia²external²call²file"                      , '-' , '·' , ""                                                  },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp   keep   unit-test-example------------------------------------*/
   { '·' , 'j' , "lcalls"    , "polyhmnia²local²call²file"                         , '-' , '·' , ""                                                  },
   { '·' , 'j' , "code"      , "polyhmnia²code²extract"                            , '-' , '·' , ""                                                  },
   { '·' , 'j' , "flow"      , "polyhmnia²code²tracing"                            , '-' , '·' , ""                                                  },
   { '·' , 'j' , "asterion"  , "polyhmnia²input²for²asterion"                      , '-' , '·' , ""                                                  },
   { '·' , 'j' , "cgraph"    , "polyhmnia²input²for²asterion"                      , '-' , '·' , ""                                                  },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp   keep   unit-test-example------------------------------------*/
   { '·' , 'j' , "ylib"      , "polyhymnia²yLIB²coord²list"                        , '-' , '·' , ""                                                  },
   { '·' , 'j' , "mystry"    , "polyhymnia²issues²file"                            , '-' , '·' , ""                                                  },
   { '·' , 'j' , "htags"     , "polyhymnia²tags²file"                              , '-' , '·' , ""                                                  },
   { '·' , 'j' , "cs"        , "stripped²c²source²code"                            , '-' , '·' , ""                                                  },
   { '·' , 'j' , "c-"        , "koios²generated²code"                              , '-' , '·' , ""                                                  },
   { '·' , 'j' , "h-"        , "koios²generated²header"                            , '-' , '·' , ""                                                  },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp   keep   unit-test-example------------------------------------*/
   { '·' , 'j' , "globals"   , "koios²unit²test²global²objects"                    , '-' , '·' , ""                                                  },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp   keep   unit-test-example------------------------------------*/

   /*===[[ OTHER ]]=====================================================================*/
   { 'C' , 'o' , "OTHER"     , "file²held²apart²from²other²categories"             , '-' , '·' , ""                                                  },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp   keep   unit-test-example------------------------------------*/
   { '·' , 'o' , "o_ext"     , "uncategorized²(has²suffix)"                        , '-' , '·' , ""                                                  },
   { '·' , 'o' , "o_none"    , "unlabeled²(no²suffix)"                             , '-' , '·' , ""                                                  },
   { '·' , 'o' , "gitignore" , "git²helper²file"                                   , '-' , '·' , ""                                                  },
   { '·' , 'o' , "o_hidden"  , "files²intentionally²hidden"                        , '-' , '·' , ""                                                  },
   { '·' , 'o' , "o_git"     , "git²local²file"                                    , '-' , '·' , ""                                                  },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp   keep   unit-test-example------------------------------------*/
   { '·' , 'o' , "o_portage" , "gentoo/portage²dist²file"                          , '-' , 'Ï' , ""                                                  },
   { '·' , 'o' , "o_kernel"  , "kernel²source²code"                                , '-' , 'Ï' , ""                                                  },
   { '·' , 'o' , "o_cache"   , "compilation²cache²file"                            , '-' , '·' , ""                                                  },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp   keep   unit-test-example------------------------------------*/

   /*===[[ HUH ]]=======================================================================*/
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp   keep   unit-test-example------------------------------------*/
   { 'C' , '?' , "HUH"       , "just²and²simply²confusing"                         , '-' , '·' , ""                                                  },
   { '·' , '?' , "u_link"    , "link²to²another²unknown²thing"                     , '-' , '·' , ""                                                  },

   /*===[[ PRIVATE ]]===================================================================*/
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp   keep   unit-test-example------------------------------------*/
   { 'C' , '!' , "PRIV"      , "details²hidden/obscured"                           , '-' , '·' , ""                                                  },
   { '·' , '!' , "!_priv"    , "details²hidden²for²privacy"                        , '-' , '·' , ""                                                  },

   /*===[[ EMPTY ]]=====================================================================*/
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp   keep   unit-test-example------------------------------------*/
   { 'C' , 'e' , "EMPTY"     , "empty²drive²space"                                 , '-' , '·' , ""                                                  },
   { '·' , 'e' , "e_empty"   , "empty²drive²space"                                 , '-' , '·' , ""                                                  },

   /*===[[ END-OF-LIST ]]===============================================================*/
   {  0  , '-' , "end"       , "end-of-list"                                       , '-' , '·' , ""                                                  },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp   keep   unit-test-example------------------------------------*/
};

static short s_nmime       =  0;
static short s_cmime       =  0;



#define     MIME_HUH       '?';



/*====================------------------------------------====================*/
/*===----                        support functions                     ----===*/
/*====================------------------------------------====================*/
static void  o___SUPPORT_________o () { return; }

short
yenv__mime_count        (void)
{
   int         i           =    0;
   s_nmime = 0;
   for (i = 0; i < MAX_MIME; ++i) {
      if (s_mime [i].m_level == 0) break;
   }
   s_nmime = i - 1;
   return s_nmime;
}



/*====================------------------------------------====================*/
/*===----                           searching                          ----===*/
/*====================------------------------------------====================*/
static void  o___SEARCH__________o () { return; }

char
yenv__mime_data         (char a_level, char a_format, char a_mime [LEN_TERSE], char r_fname [LEN_TERSE], char r_fmime [LEN_TERSE])
{
   char        rce         =  -10;
   char        x_fname     [LEN_TERSE] = "";
   char        x_fmime     [LEN_LABEL] = "";
   if (r_fname  != NULL)  strcpy (r_fname, "");
   if (r_fmime  != NULL)  strcpy (r_fmime, "");
   --rce;  if (a_format == 0)     return rce;
   --rce;  if (a_mime   == NULL)  return rce;
   switch (a_format) {
   case 'a'  : strcpy (x_fname, "audio"  );  break;
   case 'v'  : strcpy (x_fname, "video"  );  break;
   case 'i'  : strcpy (x_fname, "image"  );  break;
   case 's'  : strcpy (x_fname, "source" );  break;
   case 't'  : strcpy (x_fname, "text"   );  break;
   case 'b'  : strcpy (x_fname, "dbase"  );  break;
   case 'c'  : strcpy (x_fname, "crypt"  );  break;
   case 'p'  : strcpy (x_fname, "prop"   );  break;
   case 'x'  : strcpy (x_fname, "exec"   );  break;
   case 'd'  : strcpy (x_fname, "dir"    );  break;
   case 'j'  : strcpy (x_fname, "temp"   );  break;
   case 'o'  : strcpy (x_fname, "other"  );  break;
   case '?'  : strcpy (x_fname, "huh"    );  break;
   case '!'  : strcpy (x_fname, "priv"   );  break;
   case 'e'  : strcpy (x_fname, "empty"  );  break;
   }
   if      (a_level == 'T')  strcpy  (x_fmime, "GRAND²TOTAL");
   else if (a_level == 'C')  sprintf (x_fmime, "%s/TOTAL", a_mime);
   else                      sprintf (x_fmime, "%s/%s", x_fname, a_mime);
   if (r_fname  != NULL)  strlcpy (r_fname, x_fname, LEN_TERSE);
   if (r_fmime  != NULL)  strlcpy (r_fmime, x_fmime, LEN_LABEL);
   return 1;
}

short
yENV_mime_by_name       (char a_mime [LEN_TERSE], char *r_level, char *r_format, char r_fname [LEN_TERSE], char r_fmime [LEN_LABEL], char r_desc [LEN_DESC], char *r_imp, char *r_keep)
{
   /*---(local variables)--+-----+-----+-*/
   char        rce         =  -10;
   int         i           =    0;
   int         e           =   -1;
   int         c           =   -1;
   int         t           =   -1;
   /*---(header)-------------------------*/
   DEBUG_CONF  yLOG_enter   (__FUNCTION__);
   /*---(default)------------------------*/
   if (r_level  != NULL)  *r_level  = '-';
   if (r_format != NULL)  *r_format = '-';
   if (r_fname  != NULL)  strcpy (r_fname, "");
   if (r_fmime  != NULL)  strcpy (r_fmime, "");
   if (r_desc   != NULL)  strcpy (r_desc , "");
   if (r_imp    != NULL)  *r_imp    = '-';
   if (r_keep   != NULL)  *r_keep   = '·';
   /*---(defense)------------------------*/
   DEBUG_CONF  yLOG_point   ("a_mime"    , a_mime);
   --rce;  if (a_mime == NULL || a_mime [0] == '\0') {
      DEBUG_CONF  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_CONF  yLOG_info    ("a_mime"    , a_mime);
   /*---(find mime)----------------------*/
   for (i = 0; i < MAX_MIME; ++i) {
      /*---(filter)----------------------*/
      if (s_mime [i].m_level == 0)                  break;
      if (strcmp (s_mime [i].m_mime, a_mime) != 0)  continue;
      DEBUG_CONF  yLOG_value   ("found"     , i);
      /*---(save-back)-------------------*/
      if (r_level  != NULL)  *r_level  = s_mime [i].m_level;
      if (r_format != NULL)  *r_format = s_mime [i].m_format;
      if (r_desc   != NULL)   strlcpy (r_desc, s_mime [i].m_desc, LEN_DESC);
      yenv__mime_data  (s_mime [i].m_level, s_mime [i].m_format, a_mime, r_fname, r_fmime);
      if (r_imp    != NULL)  *r_imp    = s_mime [i].m_imp;
      if (r_keep   != NULL)  *r_keep   = s_mime [i].m_keep;
      s_cmime = i;
      /*---(complete)--------------------*/
      DEBUG_CONF  yLOG_exit    (__FUNCTION__);
      return i;
      /*---(done)------------------------*/
   }
   /*---(complete)-----------------------*/
   DEBUG_CONF  yLOG_note    ("never found");
   --rce;
   DEBUG_CONF  yLOG_exitr   (__FUNCTION__, rce);
   return rce;
}

short
yENV_mime_by_cursor     (char a_dir, char r_mime [LEN_TERSE], char *r_level, char *r_format, char r_fname [LEN_TERSE], char r_fmime [LEN_LABEL], char r_desc [LEN_DESC], char *r_imp, char *r_keep)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         rc          =   -1;
   int         x_pos       =   -1;
   /*---(header)-------------------------*/
   DEBUG_CONF  yLOG_enter   (__FUNCTION__);
   /*---(default)------------------------*/
   if (r_mime   != NULL)  strcpy (r_mime, "");
   if (r_level  != NULL)  *r_level  = '-';
   if (r_format != NULL)  *r_format = '-';
   if (r_fname  != NULL)  strcpy (r_fname, "");
   if (r_fmime  != NULL)  strcpy (r_fmime, "");
   if (r_desc   != NULL)  strcpy (r_desc, "");
   if (r_imp    != NULL)  *r_imp    = '-';
   if (r_keep   != NULL)  *r_keep   = '·';
   /*---(header)-------------------------*/
   DEBUG_YENV    yLOG_enter   (__FUNCTION__);
   /*---(verify count)-------------------*/
   DEBUG_YENV    yLOG_value   ("s_nmime"   , s_nmime);
   if (s_nmime <= 0) {
      yenv__mime_count ();
      DEBUG_YENV    yLOG_value   ("s_nmime"   , s_nmime);
   }
   DEBUG_YENV    yLOG_value   ("s_cmime"   , s_cmime);
   /*---(set target)---------------------*/
   DEBUG_YENV    yLOG_char    ("a_dir"     , a_dir);
   x_pos = s_cmime;
   DEBUG_YENV    yLOG_value   ("x_pos"     , x_pos);
   --rce;  switch (a_dir) {
   case YDLST_HEAD  : case YDLST_DHEAD :
      x_pos = 0;
      break;
   case YDLST_PREV  : case YDLST_DPREV :
      if (x_pos > 0)       --x_pos;
      else                  x_pos = -1;
      break;
   case YDLST_CURR  : case YDLST_DCURR :
      break;
   case YDLST_NEXT  : case YDLST_DNEXT : case '·' :  /* · means default */
      if (x_pos < s_nmime)  ++x_pos;
      else                    x_pos = -1;
      break;
   case YDLST_TAIL  : case YDLST_DTAIL :
      x_pos = s_nmime;
      break;
   default :
      DEBUG_YENV    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
      break;
   }
   /*---(trouble)------------------------*/
   DEBUG_YENV    yLOG_value   ("x_pos"     , x_pos);
   --rce;  if (x_pos < 0) {
      DEBUG_YENV    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(save-back)-------------------*/
   s_cmime = x_pos;
   if (r_mime   != NULL)   strlcpy (r_mime, s_mime [s_cmime].m_mime, LEN_TERSE);
   if (r_level  != NULL)  *r_level  = s_mime [s_cmime].m_level;
   if (r_format != NULL)  *r_format = s_mime [s_cmime].m_format;
   if (r_desc   != NULL)   strlcpy (r_desc, s_mime [s_cmime].m_desc, LEN_DESC);
   if (r_imp    != NULL)  *r_imp    = s_mime [s_cmime].m_imp;
   if (r_keep   != NULL)  *r_keep   = s_mime [s_cmime].m_keep;
   yenv__mime_data  (s_mime [s_cmime].m_level, s_mime [s_cmime].m_format, s_mime [s_cmime].m_mime, r_fname, r_fmime);
   /*---(complete)-----------------------*/
   DEBUG_YENV    yLOG_exit    (__FUNCTION__);
   return s_cmime;
}



/*====================------------------------------------====================*/
/*===----                       location related                       ----===*/
/*====================------------------------------------====================*/
static void      o___LOCATION___________o (void) {;}

/*
 *  if it resides in certain locations, it is a specific kind of file
 */

char
yenv__mime_gentoo       (char a_full [LEN_PATH], char **r_mime, char c_unittest)
{  /*
    *  everything within these directories is the same, i do not differentiate
    */
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char       *X_PORTAGE   = "o_portage";
   char       *X_KERNEL    = "o_kernel";
   char       *X_CACHE     = "o_cache";
   /*---(defense)------------------------*/
   --rce;  if (a_full == NULL)  return rce;
   --rce;  if (r_mime == NULL)  return rce;
   /*---(portage)------------------------*/
   if        (strncmp (a_full, "/var/lib/portage/"   , 17) == 0) {
      DEBUG_RPTG   yLOG_note    ("handling portage related I");
      *r_mime = X_PORTAGE;
      return 2;
   } else if (strncmp (a_full, "/var/tmp/portage/"   , 17) == 0) {
      DEBUG_RPTG   yLOG_note    ("handling portage related II");
      *r_mime = X_PORTAGE;
      return 2;
   } else if (strncmp (a_full, "/var/log/portage/"   , 17) == 0) {
      DEBUG_RPTG   yLOG_note    ("handling portage related III");
      *r_mime = X_PORTAGE;
      return 2;
   } else if (strncmp (a_full, "/var/db/pkg/"        , 12) == 0) {
      DEBUG_RPTG   yLOG_note    ("handling portage related IV");
      *r_mime = X_PORTAGE;
      return 2;
   } else if (strncmp (a_full, "/var/db/repos/"      , 14) == 0) {
      DEBUG_RPTG   yLOG_note    ("handling portage related V");
      *r_mime = X_PORTAGE;
      return 2;
   } else if (strncmp (a_full, "/usr/share/portage/" , 19) == 0) {
      DEBUG_RPTG   yLOG_note    ("handling portage related VI");
      *r_mime = X_PORTAGE;
      return 2;
   }
   /*---(transient)----------------------*/
   else if (strncmp (a_full, "/usr/src/"        ,  9) == 0) {
      DEBUG_RPTG   yLOG_note    ("handling kernel source related");
      *r_mime = X_KERNEL;
      return 2;
   }
   /*---(transient, BUT UNIT TESTING)----*/
   else if   (strncmp (a_full, "/tmp/",  5) == 0 && c_unittest != 'y') {
      DEBUG_RPTG   yLOG_note    ("handling global cache related I");
      *r_mime = X_CACHE;
      return 2;
   }
   /*---(transient)----------------------*/
   else if (strncmp (a_full, "/run/"            ,  5) == 0) {
      DEBUG_RPTG   yLOG_note    ("handling global cache related II");
      *r_mime = X_CACHE;
      return 2;
   } else if (strncmp (a_full, "/var/run/"        ,  9) == 0) {
      DEBUG_RPTG   yLOG_note    ("handling global cache related III");
      *r_mime = X_CACHE;
      return 2;
   } else if (strncmp (a_full, "/var/cache/"      , 11) == 0) {
      DEBUG_RPTG   yLOG_note    ("handling global cache related IV");
      *r_mime = X_CACHE;
      return 2;
   } else if (strncmp (a_full, "/var/tmp/"        ,  9) == 0) {
      DEBUG_RPTG   yLOG_note    ("handling global cache related V");
      *r_mime = X_CACHE;
      return 2;
   }
   /*---(failure)------------------------*/
   DEBUG_RPTG   yLOG_note    ("NOT gentoo related");
   /*---(complete)-----------------------*/
   return 0;
}

char
yenv__mime_git          (char a_full [LEN_PATH], char **r_mime)
{  /*
    *  everything under a /.git is git related and i do not differentiate
    */
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char       *X_GIT       = "o_git";
   /*---(defense)------------------------*/
   --rce;  if (a_full == NULL)  return rce;
   --rce;  if (r_mime == NULL)  return rce;
   /*---(check)--------------------------*/
   if (strstr (a_full, "/.git/") != NULL) {
      *r_mime = X_GIT;
      /*---(done)------------------------*/
      return 2;
   }
   /*---(failure)------------------------*/
   DEBUG_RPTG   yLOG_note    ("NOT git related");
   /*---(complete)-----------------------*/
   return 0;
}



/*====================------------------------------------====================*/
/*===----                     file-type related                        ----===*/
/*====================------------------------------------====================*/
static void      o___TYPES______________o (void) {;}

/*
 *  if it is a certain file type, it is a specific kind mime
 */

char
yenv__mime_symlink      (char a_type, char a_ltype, char **r_mime)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char       *X_DLINK     = "d_link";
   char       *X_RLINK     = "r_link";
   char       *X_ELINK     = "x_link";
   char       *X_CLINK     = "c_link";
   char       *X_BLINK     = "b_link";
   char       *X_PLINK     = "p_link";
   char       *X_ILINK     = "i_link";
   char       *X_ULINK     = "u_link";
   /*---(defense)------------------------*/
   --rce;  if (r_mime == NULL)  return rce;
   /*---(check)--------------------------*/
   if (a_type == YENV_SYM) {
      /*---(handle)----------------------*/
      DEBUG_ENVI   yLOG_note    ("handle as symlink entry");
      switch (a_ltype) {
      case   YENV_DIR    :  *r_mime = X_DLINK;  return 2;    break;
      case   YENV_REG    :  *r_mime = X_RLINK;  return 1;    break;
      case   YENV_CHAR   :  *r_mime = X_CLINK;  return 2;    break;
      case   YENV_BLOCK  :  *r_mime = X_BLINK;  return 2;    break;
      case   YENV_PIPE   :  *r_mime = X_PLINK;  return 2;    break;
      case   YENV_IPSOC  :  *r_mime = X_ILINK;  return 2;    break;
      default            :  *r_mime = X_ULINK;  return 1;    break;
      }
      /*---(done)------------------------*/
      return 1;
   }
   /*---(failure)------------------------*/
   DEBUG_RPTG   yLOG_note    ("NOT symlink related");
   /*---(complete)-----------------------*/
   return 0;
}

char
yenv__mime_device       (char a_type, char **r_mime)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char       *X_DIR       = "d_dir";
   char       *X_CHAR      = "c_dev";
   char       *X_BLOCK     = "b_dev";
   char       *X_PIPE      = "p_pipe";
   char       *X_IPSOC     = "i_socket";
   /*---(defense)------------------------*/
   --rce;  if (r_mime == NULL)  return rce;
   /*---(handle)-------------------------*/
   switch (a_type) {
   case   YENV_DIR     :  *r_mime = X_DIR;          break;
   case   YENV_CHAR    :  *r_mime = X_CHAR;         break;
   case   YENV_BLOCK   :  *r_mime = X_BLOCK;        break;
   case   YENV_PIPE    :  *r_mime = X_PIPE;         break;
   case   YENV_IPSOC   :  *r_mime = X_IPSOC;        break;
   default             : 
                          DEBUG_RPTG   yLOG_note    ("NOT device related");
                          return 0;                 break;
   }
   /*---(complete)-----------------------*/
   DEBUG_ENVI   yLOG_note    ("handle device/special entry");
   return 2;
}



/*====================------------------------------------====================*/
/*===----                      tilde files                             ----===*/
/*====================------------------------------------====================*/
static void      o___TILDE______________o (void) {;}

char
yenv__mime_tilde        (char a_name [LEN_HUND], char **b_mime)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         l           =    0;
   char       *X_BACKUP    = "b_tilde";
   /*---(defense)------------------------*/
   --rce;  if (a_name == NULL)  return rce;
   --rce;  if (b_mime == NULL)  return rce;
   /*---(handle)-------------------------*/
   l = strlen (a_name);
   if (a_name [l - 1] == '~') {
      DEBUG_ENVI   yLOG_note    ("handle backup/cache entry");
      *b_mime  = X_BACKUP;
      return 2;
   }
   /*---(failure)------------------------*/
   DEBUG_RPTG   yLOG_note    ("NOT tilde related");
   /*---(complete)-----------------------*/
   return 0;
}



/*====================------------------------------------====================*/
/*===----                    extention related                         ----===*/
/*====================------------------------------------====================*/
static void      o___SUFFIX_____________o (void) {;}

char
yenv__mime_suffix       (char a_name [LEN_HUND], char **b_mime)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        c           =    0;
   char       *p           = NULL;
   char        x_name      [LEN_HUND]  = "";
   char        l           =    0;
   int         i           =    0;
   short       x_mime      =    0;
   static char x_ext       [LEN_TERSE] = "";
   /*---(defense)------------------------*/
   --rce;  if (a_name == NULL)  return rce;
   --rce;  if (b_mime == NULL)  return rce;
   /*---(quick-out)----------------------*/
   if (*b_mime != NULL)         return 0;
   /*---(check length)-------------------*/
   strlcpy (x_name, a_name, LEN_HUND);
   l = strlen (x_name);
   if (l <= 2)  return 0;
   /*---(rightmost)----------------------*/
   for (i = 0;  i < 3;  ++i) {
      /*---(find extension)--------------*/
      p = strrchr (x_name, '.');
      if (p == NULL)  return 0;
      /*---(filter)----------------------*/
      l = p - x_name;
      if (l <= 1)  return 0;   /* no room for base name  */
      /*---(update)----------------------*/
      p [0] = '\0';
      l = strlen (++p);
      if (l >  9)  continue;   /* too long for an extension */
      DEBUG_RPTG   yLOG_complex ("testing"   , "%d) %d[%s]", i, l, p);
      /*---(handle)----------------------*/
      if (l > 0) {
         x_mime = yENV_mime_by_name  (p, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
         DEBUG_RPTG   yLOG_value   ("x_mime"    , x_mime);
         if (x_mime >= 0) {
            strlcpy (x_ext, p, LEN_TERSE);
            *b_mime = x_ext;
            return i + 1;
         }
      }
      /*---(done)------------------------*/
   }
   /*---(failure)------------------------*/
   DEBUG_RPTG   yLOG_note    ("NOT suffix related");
   /*---(complete)-----------------------*/
   return 0;
}

char
yenv__mime_hidden       (char a_name [LEN_HUND], char **b_mime)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char       *X_DIR       = "d_dir";
   char       *X_OHIDDEN   = "o_hidden";
   char       *X_DGIT      = "d_gitroot";
   char       *X_DHIDDEN   = "d_hidden";
   /*---(quick-out)----------------------*/
   --rce;  if (a_name == NULL)  return rce;
   --rce;  if (b_mime == NULL)  return rce;
   /*---(files)--------------------------*/
   /* only unidenfified files are assigned to hidden                          */
   if (*b_mime == NULL && a_name [0] == '.') {
      DEBUG_ENVI   yLOG_note    ("handle hidden file");
      *b_mime = X_OHIDDEN;
      return 2;
   }
   /*---(directories)--------------------*/
   if (*b_mime != NULL && strcmp (*b_mime, X_DIR) == 0) {
      if (strcmp (a_name, ".git") == 0) {
         DEBUG_ENVI   yLOG_note    ("git root directory");
         *b_mime = X_DGIT;
         return 2;
      }
      if (a_name [0] == '.') {
         DEBUG_ENVI   yLOG_note    ("handle hidden directory");
         *b_mime = X_DHIDDEN;
         return 2;
      }
   }
   /*---(failure)------------------------*/
   DEBUG_RPTG   yLOG_note    ("NOT hidden related");
   /*---(complete)-----------------------*/
   return 0;
}

char
yenv__mime_exec         (char a_name [LEN_HUND], char a_prms, char **b_mime)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        l           =    0;
   char       *X_OHIDDEN   = "o_hidden";
   char       *X_XHIDDEN   = "x_hidden";
   char       *X_DEBUG     = "x_debug";
   char       *X_UNIT      = "x_unit";
   char       *X_MAKEF     = "makefile";
   char       *X_MMAKE     = "mmake";
   char       *X_EXEC      = "x_exec";
   /*---(quick-out)----------------------*/
   --rce;  if (b_mime == NULL)  return rce;
   /*---(check)--------------------------*/
   if ((a_prms & S_IXUSR) || (a_prms & S_IXGRP) || (a_prms & S_IXOTH))  {
      /*---(update hidden)---------------*/
      if (*b_mime != NULL) {
         if (strcmp (*b_mime, X_OHIDDEN) == 0) {
            DEBUG_ENVI   yLOG_note    ("switching to a hidden executable entry");
            *b_mime  = X_XHIDDEN;
            return 1;
         }
      }
      /*---(primary executable)----------*/
      else {
         DEBUG_ENVI   yLOG_note    ("switching to an executable entry");
         DEBUG_ENVI   yLOG_info    ("a_name"    , a_name);
         l = strlen (a_name);
         if        (l >= 6  && strcmp ("_unit"      , a_name + l -  5) == 0) {
            *b_mime = X_UNIT;
         } else if (l >= 12 && strcmp ("_unit_debug", a_name + l - 11) == 0) {
            *b_mime = X_UNIT;
         } else if (l >= 7 && strcmp ("_debug", a_name + l - 6) == 0) {
            *b_mime = X_DEBUG;
         } else if (strcmp ("Makefile" , a_name) == 0) {
            *b_mime = X_MAKEF;
         } else if (strcmp ("Mmake"    , a_name) == 0) {
            *b_mime = X_MMAKE;
         } else {
            *b_mime = X_EXEC;
         }
         return 1;
      }
   }
   /*---(failure)------------------------*/
   DEBUG_RPTG   yLOG_note    ("NOT exec related");
   /*---(complete)-----------------------*/
   return 0;
}

char
yenv__mime_manual       (char a_name [LEN_HUND], char **b_mime)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         l           =    0;
   char       *X_MANUAL    = "manual";
   /*---(quick-out)----------------------*/
   --rce;  if (a_name == NULL)  return rce;
   --rce;  if (b_mime == NULL)  return rce;
   if (*b_mime != NULL)         return 0;
   /*---(check for manuals)---------------*/
   l = strlen (a_name);
   if (l >= 3 && a_name [l - 2] == '.') {
      DEBUG_ENVI   yLOG_note    ("handling normal manual extension");
      if (strchr ("123456789", a_name [l - 1]) != NULL) {
         *b_mime = X_MANUAL;
         return 1;
      }
   }
   else if (l >= 7 && a_name [l - 6] == '.') {
      DEBUG_ENVI   yLOG_note    ("handling special manual extension I");
      if (strcmp ("2type"   , a_name + l - 5) == 0) {
         *b_mime = X_MANUAL;
         return 1;
      }
      if (strcmp ("3type"   , a_name + l - 5) == 0) {
         *b_mime = X_MANUAL;
         return 1;
      }
      if (strcmp ("3head"   , a_name + l - 5) == 0) {
         *b_mime = X_MANUAL;
         return 1;
      }
   }
   else if (l >= 8 && a_name [l - 7] == '.') {
      DEBUG_ENVI   yLOG_note    ("handling special manual extension II");
      if (strcmp ("3const"  , a_name + l - 6) == 0) {
         *b_mime = X_MANUAL;
         return 1;
      }
   }
   /*---(failure)------------------------*/
   DEBUG_RPTG   yLOG_note    ("NOT manual related");
   /*---(complete)-----------------------*/
   return 0;
}

char
yenv__mime_unitc        (char a_name [LEN_HUND], char **b_mime)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        l           =    0;
   char       *X_JC        = "c-";
   char       *X_JH        = "h-";
   char        x_update    =  '-';
   /*---(quick-out)----------------------*/
   --rce;  if (a_name == NULL)  return rce;
   --rce;  if (b_mime == NULL)  return rce;
   if (*b_mime == NULL)         return 0;
   /*---(handle)--------------------------*/
   if (strcmp (*b_mime, "c") == 0) {
      l = strlen (a_name);
      if (l >= 8 && strcmp ("_unit.c" , a_name + l - 7) == 0) {
         DEBUG_ENVI   yLOG_note    ("handling transcient c unit file");
         *b_mime = X_JC;
         return 1;
      }
      if      (strcmp (a_name, "unit_head.c") == 0)  x_update = 'y';
      else if (strcmp (a_name, "unit_wide.c") == 0)  x_update = 'y';
      else if (strcmp (a_name, "unit_data.c") == 0)  x_update = 'y';
      else                                           x_update = '-';
      if (x_update == 'y') {
         DEBUG_ENVI   yLOG_note    ("handling transcient c unit file");
         *b_mime = X_JC;
         return 1;
      }
   }
   if (strcmp (*b_mime, "h") == 0) {
      if      (strcmp (a_name, "unit_head.h") == 0)  x_update = 'y';
      else if (strcmp (a_name, "unit_wide.h") == 0)  x_update = 'y';
      else if (strcmp (a_name, "unit_data.h") == 0)  x_update = 'y';
      else                                           x_update = '-';
      if (x_update == 'y') {
         DEBUG_ENVI   yLOG_note    ("handling transcient h unit file");
         *b_mime = X_JH;
         return 1;
      }
   }
   /*---(failure)------------------------*/
   DEBUG_RPTG   yLOG_note    ("NOT unitc related");
   /*---(complete)-----------------------*/
   return 0;
}

char
yenv__mime_libs_two     (char a_full [LEN_PATH], char a_name [LEN_HUND], char a_type, char a_prms, char **b_mime)
{ /* versions at end of libraries can hide suffixes                          */
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        l           =    0;
   char       *X_SO        = "so";
   char       *X_SO_LINK   = "so_link";
   char       *X_SO_DEBUG  = "so_debug";
   char       *X_A         = "a";
   char       *X_A_LINK    = "a_link";
   char       *X_A_DEBUG   = "a_debug";
   char       *X_JLIB      = "lib-";
   char        x_inst      = '-';
   char        x_check     = '-';
   /*---(quick-out)----------------------*/
   --rce;  if (a_full == NULL)  return rce;
   --rce;  if (a_name == NULL)  return rce;
   --rce;  if (b_mime == NULL)  return rce;
   /*---(check location)------------------*/
   /*> DEBUG_RPTG   yLOG_info    ("a_full"    , a_full);                              <*/
   /*> DEBUG_RPTG   yLOG_info    ("a_name"    , a_name);                              <*/
   if      (strncmp ("/lib"           , a_full,  4) == 0)  x_inst = 'y';
   else if (strncmp ("/usr/lib"       , a_full,  8) == 0)  x_inst = 'y';
   else if (strncmp ("/usr/local/lib" , a_full, 14) == 0)  x_inst = 'y';
   else if (strncmp ("/home/system"   , a_full, 12) == 0)  x_inst = '-';
   else return 0;
   /*> DEBUG_RPTG   yLOG_note    ("yenv__mime_libs_two, in right dirs");              <*/
   /*---(check executable)----------------*/
   /*> if ((a_prms & S_IXUSR) || (a_prms & S_IXGRP) || (a_prms & S_IXOTH))  ;         <* 
    *> else return 0;                                                                 <*/
   /*> DEBUG_RPTG   yLOG_note    ("yenv__mime_libs_two, executable");                 <*/
   /*---(prepare)-------------------------*/
   l = strlen (a_name);
   /*---(check shared)--------------------*/
   if      (l >= 4 && strcmp (".so" , a_name + l - 3) == 0)   x_check = 'y';
   else if (*b_mime != NULL && strcmp (*b_mime, "so") == 0)   x_check = 'y';
   else if (strstr (a_name, ".so.") != NULL)                  x_check = 'y';
   else                                                       x_check = '-';
   /*> DEBUG_RPTG   yLOG_char    ("so x_check", x_check);                             <*/
   if (x_check == 'y') {
      if (x_inst == 'y') {
         if      (a_type == YENV_SYM)                 { *b_mime = X_SO_LINK;  return 1; }
         else if (strstr (a_name, "_debug.") != NULL) { *b_mime = X_SO_DEBUG; return 1; }
         else                                         { *b_mime = X_SO;       return 1; }
      } else                                          { *b_mime = X_JLIB;     return 1; }
   }
   /*---(check shared)--------------------*/
   if      (l >= 3 && strcmp (".a"  , a_name + l - 2) == 0)   x_check = 'y';
   else if (*b_mime != NULL && strcmp (*b_mime, "a" ) == 0)   x_check = 'y';
   else if (strstr (a_name, ".a." ) != NULL)                  x_check = 'y';
   else                                                       x_check = '-';
   /*> DEBUG_RPTG   yLOG_char    ("a x_check" , x_check);                             <*/
   if (x_check == 'y') {
      if (x_inst == 'y') {
         if      (a_type == YENV_SYM)                 { *b_mime = X_A_LINK;   return 1; }
         else if (strstr (a_name, "_debug.") != NULL) { *b_mime = X_A_DEBUG;  return 1; }
         else                                         { *b_mime = X_A;        return 1; }
      } else                                          { *b_mime = X_JLIB;     return 1; }
   }
   /*---(failure)------------------------*/
   DEBUG_RPTG   yLOG_note    ("NOT libs_two related");
   /*---(complete)-----------------------*/
   return 0;
}

char
yenv__mime_exec_link    (char a_prms, char **b_mime)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char       *X_RLINK     = "r_link";
   char       *X_ELINK     = "x_link";
   /*---(quick-out)----------------------*/
   --rce;  if (b_mime == NULL)  return rce;
   if (*b_mime == NULL)         return 0;
   /*---(check executable link)----------*/
   if (strcmp (*b_mime, X_RLINK) == 0) {
      if ((a_prms & S_IXUSR) || (a_prms & S_IXGRP) || (a_prms & S_IXOTH))  {
         *b_mime  = X_ELINK;
         return 1;
      }
   }
   /*---(failure)------------------------*/
   DEBUG_RPTG   yLOG_note    ("NOT exec_link related");
   /*---(complete)-----------------------*/
   return 0;
}

char
yenv__mime_exec_junk    (char a_full [LEN_PATH], char **b_mime)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        l           =    0;
   char        x_inst      =  '-';
   char        x_ext       [LEN_LABEL] = "";
   char       *X_JEXEC     = "exec-";
   char       *X_JUNIT     = "unit-";
   /*---(quick-out)----------------------*/
   --rce;  if (a_full == NULL)  return rce;
   --rce;  if (b_mime == NULL)  return rce;
   if (*b_mime == NULL)         return 0;
   /*---(prepare)-------------------------*/
   sprintf (x_ext, " %s ", *b_mime);
   /*---(executables)---------------------*/
   if (strstr (" x_exec x_debug ", x_ext) != NULL) {
      if      (strncmp ("/bin"           , a_full,  4) == 0)  x_inst = 'y';
      else if (strncmp ("/sbin"          , a_full,  5) == 0)  x_inst = 'y';
      else if (strncmp ("/usr/bin"       , a_full,  8) == 0)  x_inst = 'y';
      else if (strncmp ("/usr/sbin"      , a_full,  9) == 0)  x_inst = 'y';
      else if (strncmp ("/usr/local/bin" , a_full, 14) == 0)  x_inst = 'y';
      else if (strncmp ("/usr/local/sbin", a_full, 15) == 0)  x_inst = 'y';
      else if (strncmp ("/usr/opt/bin"   , a_full, 12) == 0)  x_inst = 'y';
      else if (strncmp ("/usr/opt/sbin"  , a_full, 13) == 0)  x_inst = 'y';
      if (x_inst != 'y') {
         *b_mime = X_JEXEC;
         return 1;
      }
   }
   /*---(unittests)-----------------------*/
   else if (strstr (" x_unit ", x_ext) != NULL) {
      if      (strncmp ("/home/system/"  , a_full, 13) == 0)  x_inst = 'y';
      if (x_inst != 'y') {
         *b_mime = X_JUNIT;
         return 1;
      }
   }
   /*---(failure)------------------------*/
   DEBUG_RPTG   yLOG_note    ("NOT exec_junk related");
   /*---(complete)-----------------------*/
   return 0;
}

char
yenv__mime_cleanup      (char a_full [LEN_PATH], char a_name [LEN_HUND], char **b_mime)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char       *X_CONF      = "conf+";
   char       *X_MYSTERY   = "o_none";
   /*---(quick-out)----------------------*/
   --rce;  if (a_full == NULL)  return rce;
   --rce;  if (a_name == NULL)  return rce;
   --rce;  if (b_mime == NULL)  return rce;
   if (*b_mime != NULL)         return 0;
   /*---(handle)-------------------------*/
   if (strncmp (a_full, "/etc/", 5) == 0) {
      DEBUG_ENVI   yLOG_note    ("configuration entry");
      *b_mime  = X_CONF;
      return 1;
   } else {
      DEBUG_ENVI   yLOG_note    ("unknown entry");
      *b_mime  = X_MYSTERY;
      return 1;
   }
   /*---(failure)------------------------*/
   DEBUG_RPTG   yLOG_note    ("NOT cleanup related");
   /*---(complete)-----------------------*/
   return 0;
}



/*====================------------------------------------====================*/
/*===----                         driver                               ----===*/
/*====================------------------------------------====================*/
static void      o___DRIVER_____________o (void) {;}

short
yENV_mime               (char a_full [LEN_PATH], char a_type, char a_ltype, char a_prms, char *r_format, char r_fname [LEN_TERSE], char r_mime [LEN_TERSE], char r_fmime [LEN_LABEL], char r_desc [LEN_DESC], char *r_imp, char *r_keep)
{  /*---(design notes)-------------------*/
   /*
    * sub-functions return...
    *    0  - not recognized, not handleds
    *    1  - handled, could be updated later
    *    2  - handled and locked
    *
    */
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         rc          =    0;
   char        x_cat       = MIME_HUH;
   char       *x_mime      = NULL;
   char       *p           = NULL;
   char        x_name      [LEN_HUND]  = "";
   short       n           =   -1;
   /*---(header)-------------------------*/
   DEBUG_ENVI   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_ENVI   yLOG_point   ("a_full"    , a_full);
   --rce;  if (a_full == NULL) {
      DEBUG_ENVI   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_ENVI   yLOG_info    ("a_full"    , a_full);
   /*---(cut path)-----------------------*/
   p = strrchr (a_full, '/');
   if (p == NULL)   strlcpy (x_name, a_full, LEN_HUND);
   else             strlcpy (x_name, p + 1 , LEN_HUND);
   DEBUG_ENVI   yLOG_info    ("x_name"    , x_name);
   /*---(location)------------------------*/
   if (rc == 0) {
      rc = yenv__mime_gentoo  (a_full         , &x_mime, '-');
      DEBUG_ENVI   yLOG_complex ("gentoo"    , "rc=%-4d, å%sæ", rc, x_mime);
   }
   if (rc == 0) {
      rc = yenv__mime_git     (a_full         , &x_mime);
      DEBUG_ENVI   yLOG_complex ("git"       , "rc=%-4d, å%sæ", rc, x_mime);
   }
   /*---(type)----------------------------*/
   if (rc == 0) {
      rc = yenv__mime_symlink (a_type, a_ltype, &x_mime);
      DEBUG_ENVI   yLOG_complex ("symlink"   , "rc=%-4d, å%sæ", rc, x_mime);
   }
   if (rc == 0) {
      rc = yenv__mime_device  (a_type         , &x_mime);
      DEBUG_ENVI   yLOG_complex ("device"    , "rc=%-4d, å%sæ", rc, x_mime);
   }
   /*---(EXTENTIONS)----------------------*/
   if (rc == 0) {
      rc = yenv__mime_suffix  (x_name         , &x_mime);
      DEBUG_ENVI   yLOG_complex ("suffix"    , "rc=%-4d, å%sæ", rc, x_mime);
   }
   /*---(overrides)-----------------------*/
   if (rc >= 0) {
      rc = yenv__mime_tilde   (x_name         , &x_mime);
      DEBUG_ENVI   yLOG_complex ("tilde"     , "rc=%-4d, å%sæ", rc, x_mime);
   }
   if (rc >= 0) {
      rc = yenv__mime_hidden     (x_name        , &x_mime);
      DEBUG_ENVI   yLOG_complex ("hidden"    , "rc=%-4d, å%sæ", rc, x_mime);
   }
   /*---(trouble)-------------------------*/
   --rce;  if (rc < 0) {
      DEBUG_ENVI   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   if (rc == 0) DEBUG_ENVI   yLOG_note    ("marked as zero (0), not handled yet");
   if (rc == 1) DEBUG_ENVI   yLOG_note    ("marked as one (1), can be further modified");
   if (rc == 2) DEBUG_ENVI   yLOG_note    ("marked as two (2), locked in");
   /*---(reclass)-------------------------*/
   if (rc == 0 || rc == 1) {
      rc = yenv__mime_exec       (x_name, a_prms, &x_mime);
      DEBUG_ENVI   yLOG_complex ("exec"      , "rc=%-4d, å%sæ", rc, x_mime);
   }
   if (rc == 0 || rc == 1) {
      rc = yenv__mime_manual     (x_name        , &x_mime);
      DEBUG_ENVI   yLOG_complex ("manual"    , "rc=%-4d, å%sæ", rc, x_mime);
   }
   if (rc == 0 || rc == 1) {
      rc = yenv__mime_unitc      (x_name        , &x_mime);
      DEBUG_ENVI   yLOG_complex ("unitc"     , "rc=%-4d, å%sæ", rc, x_mime);
   }
   if (rc == 0 || rc == 1) {
      rc = yenv__mime_libs_two   (a_full, x_name, a_type, a_prms, &x_mime);
      DEBUG_ENVI   yLOG_complex ("libs_two"  , "rc=%-4d, å%sæ", rc, x_mime);
   }
   if (rc == 0 || rc == 1) {
      rc = yenv__mime_exec_link  (a_prms        , &x_mime);
      DEBUG_ENVI   yLOG_complex ("exec_link" , "rc=%-4d, å%sæ", rc, x_mime);
   }
   if (rc == 0 || rc == 1) {
      rc = yenv__mime_exec_junk  (a_full        , &x_mime);
      DEBUG_ENVI   yLOG_complex ("junk"      , "rc=%-4d, å%sæ", rc, x_mime);
   }
   if (rc == 0 || rc == 1) {
      rc = yenv__mime_cleanup    (a_full, x_name, &x_mime);
      DEBUG_ENVI   yLOG_complex ("cleanup"   , "rc=%-4d, å%sæ", rc, x_mime);
   }
   /*---(trouble)-------------------------*/
   --rce;  if (rc < 0) {
      DEBUG_ENVI   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(save)---------------------------*/
   if (r_mime != NULL)  strlcpy (r_mime, x_mime, LEN_TERSE);
   n = yENV_mime_by_name  (x_mime, NULL, r_format, r_fname, r_fmime, r_desc, r_imp, r_keep);
   DEBUG_ENVI   yLOG_value   ("n"         , n);
   /*---(complete)-----------------------*/
   DEBUG_ENVI   yLOG_exit    (__FUNCTION__);
   return n;
}

