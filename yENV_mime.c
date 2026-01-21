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



/*   a  ,x···0··R   { '¥··31|·x··6|·p·a'¥··2l·R, "¥··l·5x··f ·r"··24|·5x·i, "¥··f ·r"··w·2x·i, '¥··2l·r'·l··D·A };¥··6|·i'·' , ¥··n···,y      */

struct {
   char        m_level;
   char        m_format;
   char        m_mime      [LEN_TERSE];
   char        m_desc      [LEN_DESC];
   char        m_imp;
} static const s_mime [MAX_MIME] = {

   /*===[[ GRAND TOTAL ]]===============================================================*/
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp */
   { 'T',  '-' , "TOTAL"     , "grand²total²values"                                , '-' },

   /*===[[ AUDIO ]]=====================================================================*/
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp */
   { 'C' , 'a' , "AUDIO"     , "auditory²formats,²like²music"                      , '-' },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp */
   { '·' , 'a' , "aiff"      , "apple²standard²audio"                              , '-' },
   { '·' , 'a' , "aac"       , "advanced²audio²coding"                             , '-' },
   { '·' , 'a' , "au"        , "sun²standard²audio"                                , '-' },
   { '·' , 'a' , "m4a"       , "apple²unprotected²coding"                          , '-' },
   { '·' , 'a' , "mp3"       , "mpeg²layer²3²audio"                                , '@' },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp */
   { '·' , 'a' , "ogg"       , "open²source²vorbis"                                , '-' },
   { '·' , 'a' , "ra"        , "realnetworks²real²audio"                           , '-' },
   { '·' , 'a' , "raw"       , "raw²audio²for²testing"                             , '-' },
   { '·' , 'a' , "wav"       , "microsoft²standard²audio"                          , '-' },
   { '·' , 'a' , "wma"       , "microsoft²protected²audio"                         , '-' },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp */
   { '·' , 'a' , "mid"       , "midi²sound"                                        , '-' },
   { '·' , 'a' , "midi"      , "midi²sound"                                        , '-' },

   /*===[[ VIDEO ]]=====================================================================*/
   { 'C' , 'v' , "VIDEO"     , "moving²visual²formats,²like²movies"                , '-' },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp */
   { '·' , 'v' , "flv"       , "adobe²flash²video"                                 , '-' },
   { '·' , 'v' , "f4v"       , "adobe²flash²video²(updated)"                       , '-' },
   { '·' , 'v' , "avi"       , "standard²video"                                    , '-' },
   { '·' , 'v' , "mov"       , "quicktime²video"                                   , '-' },
   { '·' , 'v' , "qt"        , "quicktime²video"                                   , '-' },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp */
   { '·' , 'v' , "wmv"       , "windows²media²video"                               , '-' },
   { '·' , 'v' , "rm"        , "realnetworks²real²video"                           , '-' },
   { '·' , 'v' , "mp4"       , "mpeg²layer²4²video"                                , '@' },
   { '·' , 'v' , "m4p"       , "mpeg²layer²4²protected"                            , '-' },
   { '·' , 'v' , "m4v"       , "mpeg²layer²4²video"                                , '-' },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp */
   { '·' , 'v' , "mpg"       , "mpeg²layer²1²video"                                , '-' },
   { '·' , 'v' , "mpeg"      , "mpeg²layer²1²video"                                , '-' },
   { '·' , 'v' , "mpe"       , "mpeg²layer²1²video"                                , '-' },
   { '·' , 'v' , "mpv"       , "mpeg²layer²1²video"                                , '-' },
   { '·' , 'v' , "swf"       , "flash²small²web"                                   , '-' },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp */

   /*===[[ IMAGE ]]=====================================================================*/
   { 'C' , 'i' , "IMAGE"     , "still²visual²formats,²like²pictures"               , '-' },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp */
   { '·' , 'i' , "jpg"       , "jpeg²compressed²image"                             , '@' },
   { '·' , 'i' , "jpeg"      , "jpeg²compressed²image"                             , '-' },
   { '·' , 'i' , "tif"       , "tagged²image²file"                                 , '-' },
   { '·' , 'i' , "tiff"      , "tagged²image²file"                                 , '-' },
   { '·' , 'i' , "rif"       , "raw²image²format"                                  , '-' },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp */
   { '·' , 'i' , "gif"       , "graphics²interchange"                              , '-' },
   { '·' , 'i' , "bmp"       , "microsoft²bitmap"                                  , '-' },
   { '·' , 'i' , "png"       , "portable²net²graphics"                             , '@' },
   { '·' , 'i' , "pngtile"   , "portable²net²graphics²as²yGLTEX·tiles"             , '@' },
   { '·' , 'i' , "ppm"       , "portable²pixmap"                                   , '-' },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp */
   { '·' , 'i' , "pgm"       , "portable²pixmap"                                   , '-' },
   { '·' , 'i' , "pbm"       , "portable²pixmap"                                   , '-' },
   { '·' , 'i' , "pnm"       , "portable²pixmap"                                   , '-' },
   { '·' , 'i' , "psd"       , "photoshop²drawing"                                 , '-' },
   { '·' , 'i' , "xpm"       , "x-windows²pixmap"                                  , '-' },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp */
   { '·' , 'i' , "xbm"       , "x-windows²pixmap"                                  , '-' },
   { '·' , 'i' , "xpm2"      , "x-windows²pixmap"                                  , '-' },
   { '·' , 'i' , "xpm3"      , "x-windows²pixmap"                                  , '-' },
   { '·' , 'i' , "svg"       , "xml²vector²graphics"                               , '-' },
   { '·' , 'i' , "svgz"      , "xml²vector²compressed"                             , '-' },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp */
   { '·' , 'i' , "svgb"      , "xml²vector²binary"                                 , '-' },
   { '·' , 'i' , "dwg"       , "autocad²drawing²file"                              , '-' },
   { '·' , 'i' , "dxf"       , "autocad²drawing²exchange"                          , '-' },
   { '·' , 'i' , "xcf"       , "gimp²drawing²file"                                 , '-' },
   { '·' , 'i' , "tga"       , "targa²bitmap²file"                                 , '-' },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp */
   { '·' , 'i' , "pic"       , "picture²file"                                      , '-' },
   { '·' , 'i' , "rgb"       , "silicongraphics²bitmap"                            , '-' },
   { '·' , 'i' , "rgba"      , "silicongraphics²image"                             , '-' },
   { '·' , 'i' , "sgi"       , "silicongraphics²bitmap"                            , '-' },
   { '·' , 'i' , "aae"       , "apple²metadata²and²adjustment²file"                , '-' },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp */
   { '·' , 'i' , "ithmb"     , "apple²thumbnail²image²file"                        , '-' },
   { '·' , 'i' , "bdf"       , "font²file²in²bit"                                  , '-' },
   { '·' , 'i' , "sfd"       , "font²file²in²fontforge"                            , '-' },
   { '·' , 'i' , "pcf"       , "font²file²in²pixel"                                , '-' },
   { '·' , 'i' , "i_scan"    , "scan²and²document²archive"                         , '-' },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp */
   { '·' , 'i' , "i_wall"    , "exoteric²roach²wallpaper"                          , '-' },
   { '·' , 'i' , "i_photo"   , "photo²from²phone²or²camera"                        , '-' },
   { '·' , 'i' , "psf"       , "pc²screen²font²(normal)"                           , '-' },
   { '·' , 'i' , "psfu"      , "pc²screen²font²(unicode)"                          , '-' },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp */

   /*===[[ SOURCE ]]====================================================================*/
   { 'C' , 's' , "SOURCE"    , "computer²language²files²(not²config)"              , '-' },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp */
   { '·' , 's' , "ada"       , "ada²source²code"                                   , '-' },
   { '·' , 's' , "asm"       , "assembly²language²source²code"                     , '@' },
   { '·' , 's' , "s"         , "assembly²language²source²code"                     , '-' },
   { '·' , 's' , "bas"       , "basic²language²source²code"                        , '-' },
   { '·' , 's' , "bat"       , "windows²batch²file"                                , '-' },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp */
   { '·' , 's' , "vb"        , "visual²basic²language²source²code"                 , '-' },
   { '·' , 's' , "vbs"       , "visual²basic²language²source²code"                 , '-' },
   { '·' , 's' , "cls"       , "visual²basic²language²source²code"                 , '-' },
   { '·' , 's' , "cob"       , "cobol²language²source²code"                        , '-' },
   { '·' , 's' , "cbl"       , "cobol²language²source²code"                        , '-' },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp */
   { '·' , 's' , "cpp"       , "c++²language²source²code"                          , '-' },
   { '·' , 's' , "c++"       , "c++²language²source²code"                          , '-' },
   { '·' , 's' , "cc"        , "c++²language²source²code"                          , '-' },
   { '·' , 's' , "cxx"       , "c++²language²source²code"                          , '-' },
   { '·' , 's' , "cbp"       , "c++²language²source²code"                          , '-' },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp */
   { '·' , 's' , "hpp"       , "c++²language²header²code"                          , '-' },
   { '·' , 's' , "hxx"       , "c++²language²header²code"                          , '-' },
   { '·' , 's' , "h++"       , "c++²language²header²code"                          , '-' },
   { '·' , 's' , "hh"        , "c++²language²header²code"                          , '-' },
   { '·' , 's' , "c"         , "ansi-c²source²code"                                , '@' },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp */
   { '·' , 's' , "h"         , "ansi-c²header"                                     , '@' },
   { '·' , 's' , "for"       , "fortran²language²source²code"                      , '-' },
   { '·' , 's' , "ftn"       , "fortran²language²source²code"                      , '-' },
   { '·' , 's' , "f"         , "fortran²language²source²code"                      , '-' },
   { '·' , 's' , "f77"       , "fortran²language²source²code"                      , '-' },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp */
   { '·' , 's' , "f90"       , "fortran²language²source²code"                      , '-' },
   { '·' , 's' , "java"      , "java²language²source²code"                         , '-' },
   { '·' , 's' , "class"     , "java²language²source²code"                         , '-' },
   { '·' , 's' , "jsm"       , "javascript²code²module"                            , '-' },
   { '·' , 's' , "lisp"      , "lisp²language²source²code"                         , '-' },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp */
   { '·' , 's' , "m4"        , "m4²language²source²code"                           , '-' },
   { '·' , 's' , "pas"       , "pascal²language²source²code"                       , '-' },
   { '·' , 's' , "p"         , "pascal²language,²python²pickle"                    , '-' },
   { '·' , 's' , "pp"        , "pascal²language²source²code"                       , '-' },
   { '·' , 's' , "php"       , "php²language²source²code"                          , '-' },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp */
   { '·' , 's' , "php3"      , "php²language²source²code"                          , '-' },
   { '·' , 's' , "php4"      , "php²language²source²code"                          , '-' },
   { '·' , 's' , "php5"      , "php²language²source²code"                          , '-' },
   { '·' , 's' , "phps"      , "php²language²source²code"                          , '-' },
   { '·' , 's' , "pl"        , "perl²language²source²code"                         , '-' },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp */
   { '·' , 's' , "ph"        , "perl²language²header²file"                         , '-' },
   { '·' , 's' , "pm"        , "perl²language²source²code"                         , '-' },
   { '·' , 's' , "py"        , "python²language²source²code"                       , '-' },
   { '·' , 's' , "rpy"       , "python²language²source²code"                       , '-' },
   { '·' , 's' , "ptl"       , "python²template²language²file"                     , '-' },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp */
   { '·' , 's' , "pyt"       , "python²declaration²file"                           , '-' },
   { '·' , 's' , "pyw"       , "python²gui²source²script"                          , '-' },
   { '·' , 's' , "rb"        , "ruby²language²source²code"                         , '-' },
   { '·' , 's' , "rbx"       , "ruby²language²source²code"                         , '-' },
   { '·' , 's' , "rjs"       , "ruby²language²source²code"                         , '-' },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp */
   { '·' , 's' , "scm"       , "scheme²language²source²code"                       , '-' },
   { '·' , 's' , "sh"        , "bash²shell²language²source²code"                   , '@' },
   { '·' , 's' , "shh"       , "bash²shell²language²source²code"                   , '-' },
   { '·' , 's' , "ws"        , "windows²scripting²language"                        , '-' },
   { '·' , 's' , "wsf"       , "windows²scripting,²studio²script"                  , '-' },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp */
   { '·' , 's' , "bash"      , "bash²shell²language²source²code"                   , '-' },
   { '·' , 's' , "vim"       , "vim²script"                                        , '-' },
   { '·' , 's' , "awk"       , "awk²script²file"                                   , '-' },
   { '·' , 's' , "in"        , "automake/autoconf²file"                            , '-' },
   { '·' , 's' , "am"        , "automake/autoconf²definition"                      , '-' },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp */
   { '·' , 's' , "vcproj"    , "microsoft²visual²project"                          , '-' },
   { '·' , 's' , "csproj"    , "microsoft²visual²project"                          , '-' },
   { '·' , 's' , "vcp"       , "microsoft²visual²project"                          , '-' },
   { '·' , 's' , "dsp"       , "microsoft²developer²project"                       , '-' },
   { '·' , 's' , "dsw"       , "microsoft²developer²workspace"                     , '-' },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp */
   { '·' , 's' , "js"        , "microsoft²studio²javascript"                       , '-' },
   { '·' , 's' , "cd"        , "microsoft²studio²class²diagram"                    , '-' },
   { '·' , 's' , "config"    , "microsoft²studio²configuration"                    , '-' },
   { '·' , 's' , "jsl"       , "microsoft²studio²javascript²assembly"              , '-' },
   { '·' , 's' , "resx"      , "microsoft²studio²resources²file"                   , '-' },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp */
   { '·' , 's' , "res"       , "microsoft²studio²resources²compiled"               , '-' },
   { '·' , 's' , "ico"       , "microsoft²studio²icon²file"                        , '-' },
   { '·' , 's' , "cur"       , "microsoft²studio²cursor²file"                      , '-' },
   { '·' , 's' , "rpt"       , "microsoft²studio²crystal²report"                   , '-' },
   { '·' , 's' , "mdf"       , "microsoft²studio²sql²database"                     , '-' },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp */
   { '·' , 's' , "lua"       , "lua²script²file"                                   , '-' },
   { '·' , 's' , "tmac"      , "groff²macro"                                       , '-' },
   { '·' , 's' , "wbt"       , "wilson²window²ware²batch²script"                   , '-' },
   { '·' , 's' , "htc"       , "microsoft²html²component²script"                   , '-' },
   { '·' , 's' , "xul"       , "xml²user²interface²language"                       , '-' },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp */
   { '·' , 's' , "gcode"     , "control²language"                                  , '-' },
   { '·' , 's' , "pc"        , "developer²program²creation²file"                   , '-' },
   { '·' , 's' , "script"    , "yVIKEYS²script²(also²apple²newton)"                , '-' },
   { '·' , 's' , "macro"     , "yVIKEYS²macro²repository"                          , '-' },
   { '·' , 's' , "unit"      , "koios²unit²test²source"                            , '@' },
   { '·' , 's' , "munit"     , "micro²unit²test²source²(c-lang)"                   , '@' },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp */
   { '·' , 's' , "la"        , "gun²libtool²library²description"                   , '-' },
   { '·' , 's' , "lo"        , "gun²libtool²library²support²file"                  , '-' },
   { '·' , 's' , "nib"       , "apple²interface²builder"                           , '-' },
   { '·' , 's' , "strings"   , "used²to²localize²program"                          , '-' },
   { '·' , 's' , "actual"    , "unstructured²unit²testing²results"                 , '-' },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp */
   { '·' , 's' , "expect"    , "unstructured²unit²testing²expects"                 , '-' },
   { '·' , 's' , "make"      , "generic²make²file²extension"                       , '-' },
   { '·' , 's' , "makefile"  , "generic²make²file"                                 , '@' },
   { '·' , 's' , "mmake"     , "master²make²file"                                  , '@' },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp */
   { '·' , 's' , "patch"     , "quilt²patch²for²updating²code"                     , '-' },
   { '·' , 's' , "dpatch"    , "debian²patch²for²updating²code"                    , '-' },
   { '·' , 's' , "stdin"     , "unstructured²unit²testing²input"                   , '-' },
   { '·' , 's' , "stdout"    , "unstructured²unit²testing²input"                   , '-' },
   { '·' , 's' , "tcl"       , "tool²command²language"                             , '-' },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp */
   { '·' , 's' , "initd"     , "initialization²script"                             , '-' },
   { '·' , 's' , "confd"     , "initialization²configuration"                      , '-' },
   { '·' , 's' , "eclass"    , "bash²script²for²ebuild²environment"                , '-' },
   { '·' , 's' , "rpm"       , "redhat²package²distribution²format"                , '-' },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp */

   /*===[[ ASCII TEXT ]]================================================================*/
   { 'C' , 't' , "TEXT"      , "ascii-text²files²(plain²and²structured)"           , '-' },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp */
   { '·' , 't' , "txt"       , "normal²text²file"                                  , '@' },
   { '·' , 't' , "asciiart"  , "normal²text²file²containing²ascii²art"             , '@' },
   { '·' , 't' , "rptg"      , "text²output²file²(write²only)"                     , '-' },
   { '·' , 't' , "ctrl"      , "inter-run²report/stats²storage²(rw)"               , '-' },
   { '·' , 't' , "csv"       , "comma²seperated²values"                            , '-' },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp */
   { '·' , 't' , "tsv"       , "tab²seperated²values"                              , '-' },
   { '·' , 't' , "howto"     , "heatherly²howto/notes"                             , '@' },
   { '·' , 't' , "conf"      , "configuration²file"                                , '@' },
   { '·' , 't' , "t_conf"    , "configuration²file²(no²ext)"                       , '-' },
   { '·' , 't' , "use"       , "portage²use²flags"                                 , '-' },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp */
   { '·' , 't' , "ini"       , "windows²configuration²file"                        , '-' },
   { '·' , 't' , "defs"      , "alternate²configuration²file"                      , '-' },
   { '·' , 't' , "cfg"       , "alternate²configuration²file"                      , '-' },
   { '·' , 't' , "xml"       , "extended²markup²language"                          , '-' },
   { '·' , 't' , "rules"     , "custom²build²xml²rules²file"                       , '-' },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp */
   { '·' , 't' , "tmpl"      , "unix²template²file"                                , '-' },
   { '·' , 't' , "def"       , "unix²definition²file"                              , '-' },
   { '·' , 't' , "rdf"       , "firefox²and²database²xml-like²file"                , '-' },
   { '·' , 't' , "json"      , "javascript²object²notation²format"                 , '-' },
   { '·' , 't' , "htm"       , "hypertext²markup²language"                         , '-' },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp */
   { '·' , 't' , "html"      , "hypertext²markup²language"                         , '-' },
   { '·' , 't' , "xhtml"     , "hypertext²markup²language"                         , '-' },
   { '·' , 't' , "rhtml"     , "ruby²hypertext²markup²language²file"               , '-' },
   { '·' , 't' , "css"       , "cascading²style²sheet"                             , '-' },
   { '·' , 't' , "epub"      , "open²book²standard"                                , '@' },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp */
   { '·' , 't' , "pdf"       , "adobe²portable²document"                           , '@' },
   { '·' , 't' , "rtf"       , "rich²text²format"                                  , '-' },
   { '·' , 't' , "eps"       , "encapsulated²postscript"                           , '-' },
   { '·' , 't' , "ps"        , "postscript"                                        , '-' },
   { '·' , 't' , "theme"     , "application²theming²file"                          , '-' },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp */
   { '·' , 't' , "ent"       , "bittorrent²information²file"                       , '-' },
   { '·' , 't' , "dtd"       , "document²type²definition²file"                     , '-' },
   { '·' , 't' , "xsl"       , "xml²style²sheet"                                   , '-' },
   { '·' , 't' , "dsl"       , "dsssl²style²sheet"                                 , '-' },
   { '·' , 't' , "xsd"       , "xml²schema²description²file"                       , '-' },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp */
   { '·' , 't' , "torrent"   , "bittorrent²information²file"                       , '-' },
   { '·' , 't' , "nanorc"    , "nano²editor²configuration"                         , '-' },
   { '·' , 't' , "vimrc"     , "vim²editor²configuration"                          , '-' },
   { '·' , 't' , "mo"        , "gnu²gettext²file"                                  , '-' },
   { '·' , 't' , "gmo"       , "gnu²gettext²file"                                  , '-' },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp */
   { '·' , 't' , "gyges"     , "gyges²spreadsheet"                                 , '@' },
   { '·' , 't' , "texi"      , "texinfo²documentation"                             , '-' },
   { '·' , 't' , "sgml"      , "sgml²document²file"                                , '-' },
   { '·' , 't' , "inc"       , "include²file"                                      , '-' },
   { '·' , 't' , "info"      , "gnu²info²reader²file"                              , '-' },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp */
   { '·' , 't' , "rst"       , "python²restructured²text²doc²file"                 , '-' },
   { '·' , 't' , "rest"      , "python²restructured²text²doc²file"                 , '-' },
   { '·' , 't' , "daily"     , "heatherly²time²tracking"                           , '-' },
   { '·' , 't' , "url"       , "internet²url"                                      , '-' },
   { '·' , 't' , "x"         , "man²file"                                          , '-' },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp */
   { '·' , 't' , "pod"       , "perl²documentation²file"                           , '-' },
   { '·' , 't' , "arac"      , "arachne²sequencing²file"                           , '-' },
   { '·' , 't' , "r_link"    , "link²to²another²file"                              , '-' },
   { '·' , 't' , "tags"      , "ctag²tags²file"                                    , '-' },
   { '·' , 't' , "changes"   , "generic²software²helper²file"                      , '-' },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp */
   { '·' , 't' , "copying"   , "generic²software²helper²file"                      , '-' },
   { '·' , 't' , "readme"    , "generic²software²helper²file"                      , '-' },
   { '·' , 't' , "todo"      , "generic²software²helper²file"                      , '-' },
   { '·' , 't' , "copyright" , "generic²software²helper²file"                      , '-' },
   { '·' , 't' , "changelog" , "generic²software²helper²file"                      , '-' },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp */
   { '·' , 't' , "install"   , "generic²software²helper²file"                      , '-' },
   { '·' , 't' , "license"   , "generic²software²helper²file"                      , '-' },
   { '·' , 't' , "manifest"  , "generic²software²helper²file"                      , '-' },
   { '·' , 't' , "md"        , "generic²software²helper²file"                      , '-' },
   { '·' , 't' , "manual"    , "man²documentation²file"                            , '@' },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp */
   { '·' , 't' , "tasks"     , "metis²task²management²data"                        , '-' },
   { '·' , 't' , "diff"      , "linux²file²comparison²output"                      , '-' },
   { '·' , 't' , "uni"       , "unicode²maps"                                      , '-' },
   { '·' , 't' , "scrn"      , "ncurses²screen·print"                              , '-' },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp */

   /*===[[ DATABASE ]]==================================================================*/
   { 'C' , 'b' , "DBASE"     , "databases²(binary,²relational,²etc)"               , '-' },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp */
   { '·' , 'b' , "db"        , "unix²database²(binary)"                            , '@' },
   { '·' , 'b' , "dbf"       , "dbase²file"                                        , '-' },
   { '·' , 'b' , "mdb"       , "microsoft²access²database"                         , '-' },
   { '·' , 'b' , "acad"      , "autocad²database"                                  , '-' },
   { '·' , 'b' , "odb"       , "openoffice²database"                               , '-' },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp */
   { '·' , 'b' , "dat"       , "generic²file²storage"                              , '-' },
   { '·' , 'b' , "sqlite"    , "sqlite²database²file"                              , '-' },
   { '·' , 'b' , "tbd"       , "text-based·database"                               , '-' },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp */

   /*===[[ ENCRYPTED ]]=================================================================*/
   { 'C' , 'c' , "CRYPT"     , "compressed²and²encrypted²files"                    , '-' },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp */
   { '·' , 'c' , "gz"        , "gzip²compressed²file"                              , '@' },
   { '·' , 'c' , "tgz"       , "gzip²compressed²tar"                               , '-' },
   { '·' , 'c' , "bz2"       , "bzip2²compressed²file"                             , '-' },
   { '·' , 'c' , "tbz"       , "bzip2²compressed²tar"                              , '-' },
   { '·' , 'c' , "tbz2"      , "bzip2²compressed²tar"                              , '-' },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp */
   { '·' , 'c' , "hqx"       , "mac²binhex²compressed"                             , '-' },
   { '·' , 'c' , "zip"       , "zipped²compressed²file"                            , '-' },
   { '·' , 'c' , "zipx"      , "zipped²compressed²file"                            , '-' },
   { '·' , 'c' , "sit"       , "stuffit²compressed"                                , '-' },
   { '·' , 'c' , "sitx"      , "stuffit²compressed"                                , '-' },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp */
   { '·' , 'c' , "pit"       , "packit²compressed"                                 , '-' },
   { '·' , 'c' , "cpio"      , "unix²cpio²archive"                                 , '-' },
   { '·' , 'c' , "tar"       , "unix²tar²archive"                                  , '-' },
   { '·' , 'c' , "iso"       , "unix²distribution"                                 , '-' },
   { '·' , 'c' , "lz"        , "lzma²compressed²file"                              , '-' },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp */
   { '·' , 'c' , "lzma"      , "lzma²compressed²file"                              , '-' },
   { '·' , 'c' , "xz"        , "lzma²compressed²file"                              , '-' },
   { '·' , 'c' , "lzo"       , "lzo²compressed²file"                               , '-' },
   { '·' , 'c' , "z"         , "huffman²compressed"                                , '-' },
   { '·' , 'c' , "s7z"       , "7-zip²compressed"                                  , '-' },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp */
   { '·' , 'c' , "cab"       , "windows²compressed²file"                           , '-' },
   { '·' , 'c' , "rar"       , "rar²compressed²file"                               , '-' },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp */


   /*===[[ PROPRIETARY ]]===============================================================*/
   { 'C' , 'p' , "PROP"      , "proprietary²and²commercial²formats"                , '-' },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp */
   { '·' , 'p' , "ebuild"    , "gentoo²ebuild²for²portage"                         , '-' },
   { '·' , 'p' , "xls"       , "ms²excel²(older)"                                  , '-' },
   { '·' , 'p' , "xlsx"      , "ms²excel²(newer)"                                  , '-' },
   { '·' , 'p' , "xlsm"      , "ms²excel"                                          , '-' },
   { '·' , 'p' , "xlw"       , "ms²excel²workbook"                                 , '-' },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp */
   { '·' , 'p' , "wk3"       , "lotus²1-2-3²worksheet"                             , '-' },
   { '·' , 'p' , "doc"       , "ms²word²(older)"                                   , '-' },
   { '·' , 'p' , "docx"      , "ms²word²(newer)"                                   , '-' },
   { '·' , 'p' , "dot"       , "ms²word²template"                                  , '-' },
   { '·' , 'p' , "ppt"       , "ms²powerpoint²(older)"                             , '-' },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp */
   { '·' , 'p' , "pptm"      , "ms²powerpoint²(older)"                             , '-' },
   { '·' , 'p' , "pptx"      , "ms²powerpoint²(newer)"                             , '-' },
   { '·' , 'p' , "mpp"       , "ms²project²file"                                   , '-' },
   { '·' , 'p' , "odc"       , "openoffice²file"                                   , '-' },
   { '·' , 'p' , "odi"       , "openoffice²image"                                  , '-' },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp */
   { '·' , 'p' , "oti"       , "openoffice²image²template"                         , '-' },
   { '·' , 'p' , "odp"       , "openoffice²presentation"                           , '-' },
   { '·' , 'p' , "otp"       , "openoffice²presentation²template"                  , '-' },
   { '·' , 'p' , "opf"       , "openoffice²document²interchange"                   , '-' },
   { '·' , 'p' , "opg"       , "openoffice²drawing²file"                           , '-' },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp */
   { '·' , 'p' , "sda"       , "openoffice²drawing²file"                           , '-' },
   { '·' , 'p' , "ops"       , "openoffice²spreadsheet"                            , '-' },
   { '·' , 'p' , "ods"       , "openoffice²spreadsheet"                            , '-' },
   { '·' , 'p' , "sdc"       , "openoffice²spreadsheet"                            , '-' },
   { '·' , 'p' , "sxc"       , "openoffice²spreadsheet"                            , '-' },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp */
   { '·' , 'p' , "oos"       , "openoffice²spreadsheet"                            , '-' },
   { '·' , 'p' , "opt"       , "openoffice²text²document"                          , '-' },
   { '·' , 'p' , "oot"       , "openoffice²text²document"                          , '-' },
   { '·' , 'p' , "sxw"       , "openoffice²text²document"                          , '-' },
   { '·' , 'p' , "jar"       , "java²archive²file"                                 , '-' },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp */
   { '·' , 'p' , "gbr"       , "gimp²brush²file"                                   , '-' },
   { '·' , 'p' , "slk"       , "silk²spreadsheet²file"                             , '-' },
   { '·' , 'p' , "oleo"      , "oleo²spreadsheet²file"                             , '-' },
   { '·' , 'p' , "font"      , "font²file"                                         , '-' },
   { '·' , 'p' , "afm"       , "adobe²font²metrics"                                , '-' },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp */
   { '·' , 'p' , "ttf"       , "truetype²font"                                     , '-' },
   { '·' , 'p' , "dict"      , "dictionary²file"                                   , '-' },
   { '·' , 'p' , "cmake"     , "cmake²module²file"                                 , '-' },
   { '·' , 'p' , "txf"       , "opengl²font"                                       , '-' },
   { '·' , 'p' , "lnk"       , "microsoft²symbolic²link"                           , '-' },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp */
   { '·' , 'p' , "xpt"       , "firefox²component"                                 , '-' },
   { '·' , 'p' , "dip"       , "diptrace²electronics²design²file"                  , '-' },
   { '·' , 'p' , "xpi"       , "firefox²extension²installation²file"               , '-' },
   { '·' , 'p' , "mf"        , "java²manifest²file²for²archives"                   , '-' },
   { '·' , 'p' , "crt"       , "firefox²certificate"                               , '-' },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp */

   /*===[[ EXECUTABLE ]]================================================================*/
   { 'C' , 'x' , "EXEC"      , "directly²executable²files"                         , '-' },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp */
   { '·' , 'x' , "a"         , "unix²static²library"                               , '-' },
   { '·' , 'x' , "a_debug"   , "unix²static²library²(debug)"                       , '-' },
   { '·' , 'x' , "ar"        , "unix²static²library"                               , '-' },
   { '·' , 'x' , "so"        , "unix²shared²library"                               , '@' },
   { '·' , 'x' , "so_debug"  , "unix²shared²library²(debug)"                       , '@' },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp */
   { '·' , 'x' , "dll"       , "dynamic²library"                                   , '-' },
   { '·' , 'x' , "bfd"       , "gnu²binary²descriptor"                             , '-' },
   { '·' , 'x' , "exe"       , "executable²file"                                   , '-' },
   { '·' , 'x' , "com"       , "executable²file"                                   , '-' },
   { '·' , 'x' , "pyc"       , "compiled²python²script"                            , '-' },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp */
   { '·' , 'x' , "pyo"       , "compiled²python²file"                              , '-' },
   { '·' , 'x' , "rake"      , "compiled²ruby²script"                              , '-' },
   { '·' , 'x' , "pyd"       , "python²dynamic²module"                             , '-' },
   { '·' , 'x' , "debug"     , "gnu²program²debug"                                 , '-' },
   { '·' , 'x' , "x_exec"    , "unix²exec²(no²ext)"                                , '@' },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp */
   { '·' , 'x' , "x_debug"   , "unix²exec²(heatherly²debug)"                       , '@' },
   { '·' , 'x' , "x_unit"    , "unix²exec²(heatherly²unit)"                        , '-' },
   { '·' , 'x' , "c_dev"     , "unix²character²device"                             , '-' },
   { '·' , 'x' , "c_link"    , "link²to²char²device"                               , '-' },
   { '·' , 'x' , "b_dev"     , "unix²block²device"                                 , '-' },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp */
   { '·' , 'x' , "b_link"    , "link²to²another²block²device"                      , '-' },
   { '·' , 'x' , "p_pipe"    , "unix²fifo/pipe²communications"                     , '-' },
   { '·' , 'x' , "p_link"    , "link²to²fifo/pipe²file"                            , '-' },
   { '·' , 'x' , "i_socket"  , "unix²ip²socket²file"                               , '-' },
   { '·' , 'x' , "i_link"    , "link²to²socket²file"                               , '-' },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp */
   { '·' , 'x' , "x_link"    , "link²to²executable"                                , '-' },
   { '·' , 'x' , "x_hidden"  , "hidden²executable"                                 , '-' },
   { '·' , 'x' , "img"       , "iso²binary²image²file"                             , '-' },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp */

   /*===[[ DIRECTORIES ]]===============================================================*/
   { 'C' , 'd' , "DIR"       , "file²directories"                                  , '-' },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp */
   { '·' , 'd' , "d_dir"     , "directory"                                         , '@' },
   { '·' , 'd' , "d_link"    , "link²to²another²directory"                         , '-' },
   { '·' , 'd' , "d_hidden"  , "hidden²directory"                                  , '-' },
   { '·' , 'd' , "d_gitroot" , "git²root²directories"                              , '-' },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp */

   /*===[[ JUNK ]]======================================================================*/
   { 'C' , 'j' , "JUNK"      , "temporary²and²transcient²files"                    , '-' },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp */
   { '·' , 'j' , "swp"       , "swap²file"                                         , '-' },
   { '·' , 'j' , "swo"       , "swap²file"                                         , '-' },
   { '·' , 'j' , "backup"    , "simple/copied²file"                                , '-' },
   { '·' , 'j' , "b_tilde"   , "tilde²suffix²file"                                 , '-' },
   { '·' , 'j' , "old"       , "simple/copied²file"                                , '-' },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp */
   { '·' , 'j' , "sav"       , "simple/copied²file"                                , '-' },
   { '·' , 'j' , "save"      , "simple/copied²file"                                , '-' },
   { '·' , 'j' , "bak"       , "simple/copied²file"                                , '-' },
   { '·' , 'j' , "cache"     , "temporary²storage"                                 , '-' },
   { '·' , 'j' , "tmp"       , "temporary²file"                                    , '-' },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp */
   { '·' , 'j' , "temp"      , "temporary²file"                                    , '-' },
   { '·' , 'j' , "log"       , "unix²log²file"                                     , '-' },
   { '·' , 'j' , "urun"      , "yUNIT²unit²test²output²file"                       , '-' },
   { '·' , 'j' , "murun"     , "yUNIT²micro²unit²test²output²file"                 , '-' },
   { '·' , 'j' , "ulog"      , "heatherly²log²file"                                , '-' },
   { '·' , 'j' , "out"       , "unstructed²dump²file"                              , '-' },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp */
   { '·' , 'j' , "dmp"       , "program²crash²file"                                , '-' },
   { '·' , 'j' , "dump"      , "text²reporting²file"                               , '-' },
   { '·' , 'j' , "o"         , "complier²object²file"                              , '-' },
   { '·' , 'j' , "os"        , "stripped²object²file"                              , '-' },
   { '·' , 'j' , "obj"       , "microsoft²object²file"                             , '-' },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp */
   { '·' , 'j' , "po"        , "object²file²portable"                              , '-' },
   { '·' , 'j' , "j_lib"     , "unistalled/dup²library"                            , '-' },
   { '·' , 'j' , "j_exec"    , "unistalled/dup²exec"                               , '-' },
   { '·' , 'j' , "j_unit"    , "compiled²unit²test"                                , '-' },
   { '·' , 'j' , "calls"     , "polyhmnia²external²call²file"                      , '-' },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp */
   { '·' , 'j' , "lcalls"    , "polyhmnia²local²call²file"                         , '-' },
   { '·' , 'j' , "code"      , "polyhmnia²code²extract"                            , '-' },
   { '·' , 'j' , "flow"      , "polyhmnia²code²tracing"                            , '-' },
   { '·' , 'j' , "asterion"  , "polyhmnia²input²for²asterion"                      , '-' },
   { '·' , 'j' , "cgraph"    , "polyhmnia²input²for²asterion"                      , '-' },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp */
   { '·' , 'j' , "ylib"      , "polyhymnia²yLIB²coord²list"                        , '-' },
   { '·' , 'j' , "mystry"    , "polyhymnia²issues²file"                            , '-' },
   { '·' , 'j' , "htags"     , "polyhymnia²tags²file"                              , '-' },
   { '·' , 'j' , "cs"        , "stripped²c²source²code"                            , '-' },
   { '·' , 'j' , "j_c"       , "koios²generated²code"                              , '-' },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp */

   /*===[[ OTHER ]]=====================================================================*/
   { 'C' , 'o' , "OTHER"     , "file²held²apart²from²other²categories"             , '-' },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp */
   { '·' , 'o' , "o_ext"     , "uncategorized²(has²suffix)"                        , '-' },
   { '·' , 'o' , "o_none"    , "unlabeled²(no²suffix)"                             , '-' },
   { '·' , 'o' , "gitignore" , "git²helper²file"                                   , '-' },
   { '·' , 'o' , "o_hidden"  , "files²intentionally²hidden"                        , '-' },
   { '·' , 'o' , "o_git"     , "git²local²file"                                    , '-' },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp */
   { '·' , 'o' , "o_portage" , "gentoo/portage²dist²file"                          , '-' },
   { '·' , 'o' , "o_kernel"  , "kernel²source²code"                                , '-' },
   { '·' , 'o' , "o_cache"   , "compilation²cache²file"                            , '-' },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp */

   /*===[[ HUH ]]=======================================================================*/
   { 'C' , '?' , "HUH"       , "just²and²simply²confusing"                         , '-' },
   { '·' , '?' , "u_link"    , "link²to²another²unknown²thing"                     , '-' },

   /*===[[ PRIVATE ]]===================================================================*/
   { 'C' , '!' , "PRIV"      , "details²hidden/obscured"                           , '-' },
   { '·' , '!' , "!_priv"    , "details²hidden²for²privacy"                        , '-' },

   /*===[[ EMPTY ]]=====================================================================*/
   { 'C' , 'e' , "EMPTY"     , "empty²drive²space"                                 , '-' },
   { '·' , 'e' , "e_empty"   , "empty²drive²space"                                 , '-' },

   /*===[[ END-OF-LIST ]]===============================================================*/
   {  0  , '-' , "end"       , "end-of-list"                                       , '-' },
   /*----  cat  ---ext------  ---desc---------------------------------------------  imp */
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

short
yenv__mime_by_name      (char a_mime [LEN_TERSE], char *r_level, char *r_format, char r_desc [LEN_DESC])
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
   if (r_desc   != NULL)  strcpy (r_desc, "");
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
yenv__mime_by_cursor    (char a_dir, char r_mime [LEN_TERSE], char *r_level, char *r_format, char r_desc [LEN_DESC])
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
   if (r_desc   != NULL)  strcpy (r_desc, "");
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
      return 1;
   } else if (strncmp (a_full, "/var/tmp/portage/"   , 17) == 0) {
      DEBUG_RPTG   yLOG_note    ("handling portage related II");
      *r_mime = X_PORTAGE;
      return 1;
   } else if (strncmp (a_full, "/var/log/portage/"   , 17) == 0) {
      DEBUG_RPTG   yLOG_note    ("handling portage related III");
      *r_mime = X_PORTAGE;
      return 1;
   } else if (strncmp (a_full, "/var/db/pkg/"        , 12) == 0) {
      DEBUG_RPTG   yLOG_note    ("handling portage related IV");
      *r_mime = X_PORTAGE;
      return 1;
   } else if (strncmp (a_full, "/var/db/repos/"      , 14) == 0) {
      DEBUG_RPTG   yLOG_note    ("handling portage related V");
      *r_mime = X_PORTAGE;
      return 1;
   } else if (strncmp (a_full, "/usr/share/portage/" , 19) == 0) {
      DEBUG_RPTG   yLOG_note    ("handling portage related VI");
      *r_mime = X_PORTAGE;
      return 1;
   }
   /*---(transient)----------------------*/
   else if (strncmp (a_full, "/usr/src/"        ,  9) == 0) {
      DEBUG_RPTG   yLOG_note    ("handling kernel source related");
      *r_mime = X_KERNEL;
      return 1;
   }
   /*---(transient, BUT UNIT TESTING)----*/
   else if   (strncmp (a_full, "/tmp/",  5) == 0 && c_unittest != 'y') {
      DEBUG_RPTG   yLOG_note    ("handling global cache related I");
      *r_mime = X_CACHE;
      return 1;
   }
   /*---(transient)----------------------*/
   else if (strncmp (a_full, "/run/"            ,  5) == 0) {
      DEBUG_RPTG   yLOG_note    ("handling global cache related II");
      *r_mime = X_CACHE;
      return 1;
   } else if (strncmp (a_full, "/var/run/"        ,  9) == 0) {
      DEBUG_RPTG   yLOG_note    ("handling global cache related III");
      *r_mime = X_CACHE;
      return 1;
   } else if (strncmp (a_full, "/var/cache/"      , 11) == 0) {
      DEBUG_RPTG   yLOG_note    ("handling global cache related IV");
      *r_mime = X_CACHE;
      return 1;
   } else if (strncmp (a_full, "/var/tmp/"        ,  9) == 0) {
      DEBUG_RPTG   yLOG_note    ("handling global cache related V");
      *r_mime = X_CACHE;
      return 1;
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
      return 1;
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
      case   YENV_DIR    :  *r_mime = X_DLINK;      break;
      case   YENV_REG    :  *r_mime = X_RLINK;      break;
      case   YENV_CHAR   :  *r_mime = X_CLINK;      break;
      case   YENV_BLOCK  :  *r_mime = X_BLINK;      break;
      case   YENV_PIPE   :  *r_mime = X_PLINK;      break;
      case   YENV_IPSOC  :  *r_mime = X_ILINK;      break;
      default            :  *r_mime = X_ULINK;      break;
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
   return 1;
}



/*====================------------------------------------====================*/
/*===----                      tilde files                             ----===*/
/*====================------------------------------------====================*/
static void      o___TILDE______________o (void) {;}

char
yenv__mime_tilde        (char a_full [LEN_PATH], char **b_mime)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         l           =    0;
   char       *X_BACKUP    = "b_tilde";
   /*---(defense)------------------------*/
   --rce;  if (a_full == NULL)  return rce;
   --rce;  if (b_mime == NULL)  return rce;
   /*---(handle)-------------------------*/
   l = strlen (a_full);
   if (a_full [l - 1] == '~') {
      DEBUG_ENVI   yLOG_note    ("handle backup/cache entry");
      *b_mime  = X_BACKUP;
      return 1;
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
   /*---(check dots)---------------------*/
   /*> c = ystrldcnt (x_name, '.', LEN_HUND);                                         <*/
   /*> if (c <= 0)  return 0;                                                         <*/
   /*> DEBUG_RPTG   yLOG_value   ("dots"      , c);                                   <*/
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
         x_mime = yenv__mime_by_name (p, NULL, NULL, NULL);
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



/*====================------------------------------------====================*/
/*===----                         driver                               ----===*/
/*====================------------------------------------====================*/
static void      o___DRIVER_____________o (void) {;}

short
yENV_mime               (char a_full [LEN_PATH], char a_type, char a_ltype, char a_prms, long a_bytes, char *r_cat, char r_mime [LEN_TERSE], char b_ext [LEN_TERSE])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         rc          =    0;
   char        x_cat       = MIME_HUH;
   char       *x_mime      = NULL;
   char        x_name      [LEN_HUND]  = "";
   /*---(header)-------------------------*/
   DEBUG_ENVI   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_ENVI   yLOG_point   ("a_full"    , a_full);
   --rce;  if (a_full == NULL) {
      DEBUG_ENVI   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_ENVI   yLOG_info    ("a_full"    , a_full);
   /*---(location)------------------------*/
   rc = 0;       rc = yenv__mime_gentoo  (a_full         , &x_mime, '-');
   if (rc == 0)  rc = yenv__mime_git     (a_full         , &x_mime);
   /*---(type)----------------------------*/
   if (rc == 0)  rc = yenv__mime_symlink (a_type, a_ltype, &x_mime);
   if (rc == 0)  rc = yenv__mime_device  (a_type         , &x_mime);
   /*---(tilde)---------------------------*/
   if (rc == 0)  rc = yenv__mime_tilde   (a_full         , &x_mime);
   /*---(EXTENTIONS)----------------------*/

   /*> if (rc == 0)  rc = EXT__suffix  (a_name   , &x_mime);                          <*/
   /*---(second pass)---------------------*/
   /*> rc = EXT__hidden    (a_name, &x_mime);                                          <* 
    *> rc = EXT__exec      (a_name, a_prms, &x_mime);                                  <* 
    *> rc = EXT__manual    (a_name, &x_mime);                                          <* 
    *> rc = EXT__unitc     (a_name, &x_mime);                                          <* 
    *> rc = EXT__libs_two  (a_full, a_name, a_prms, &x_mime);                          <* 
    *> rc = EXT__exec_two  (a_full, a_name, &x_mime);                                  <* 
    *> rc = EXT__cleanup   (a_full, a_name, &x_mime);                                  <*/
   /*---(save)---------------------------*/
   /*> MIME_add_seen (x_mime, a_bytes, &x_cat);                                        <*/
   if (r_cat != NULL)  *r_cat = x_cat;
   if (r_mime != NULL)  strlcpy (r_mime, x_mime, LEN_TERSE);
   /*---(complete)-----------------------*/
   DEBUG_ENVI   yLOG_exit    (__FUNCTION__);
   return 0;
}

