/*      [ сярюмюбкхбюел мнбше гмювемхъ ]      */
/*      [ SETTING NEW VALUES ]      */
#undef MAX_PLAYER_NAME
    #define MAX_PLAYER_NAME         (24)
#undef MAX_PLAYERS
    #define MAX_PLAYERS             (50)

/*      [ ьюакнмш дкъ бшбндю ]      */
/*      [ TEMPLATES FOR OUTPUT ]      */
#define DEBUG_MYSQL                 "[MySQL] |"
#define DEBUG_LOAD                  "[LOAD] |"

/*      [ мюярпнийх аюгш дюммшу ]      */
/*      [ DATABASE SETTINGS ]      */
#define MYSQL_HOSTNAME              "localhost"
#define MYSQL_USERNAME              "root"
#define MYSQL_PASSWORD              ""
#define MYSQL_DATABASE              "samp-novateproject"

/*      [ оепелеммше яепбепю ]      */
/*      [ SERVER VARIABLES ]      */
enum ServerInfo
{
    MySQL:MySQL
}
new SInfo[ServerInfo];

/*      [ оепелеммше хцпнйю ]      */
/*      [ PLAYER VARIABLES ]      */
enum PlayerInfo
{
    Nick[MAX_PLAYER_NAME],
    Password[30],
    Email[30]
}
new PInfo[MAX_PLAYERS][PlayerInfo];