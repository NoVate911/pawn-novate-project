/*      [ сярюмнбйю мнбшу гмювемхи ]      */
/*      [ SETTING NEW VALUES ]      */
#undef MAX_PLAYER_NAME
    #define MAX_PLAYER_NAME         (24)
#undef MAX_PLAYERS
    #define MAX_PLAYERS             (50)

/*      [ ьюакнм дкъ бшбндю ]      */
/*      [ TEMPLATES FOR OUTPUT ]      */
#define DEBUG_MYSQL                 "[MySQL] |"
#define DEBUG_LOAD                  "[LOAD] |"
#define DEBUG_INFO                  "[INFO] |"

/*      [ ьюакнм рщцю сбеднлкемхи ]      */
/*      [ NOTIFICATION TAG TEMPLATES ]      */
#define NOTIF_ERROR                 ""C_RED"[нЬХАЙЮ]"
#define NOTIF_WARNING               ""C_YELLOW"[бМХЛЮМХЕ]"
#define NOTIF_SUCCESS               ""C_GREEN"[сЯОЕЬМН]"

/*      [ мюярпнийю аюгш дюммшу ]      */
/*      [ DATABASE SETTINGS ]      */
#define MYSQL_HOSTNAME              "localhost"
#define MYSQL_USERNAME              "root"
#define MYSQL_PASSWORD              ""
#define MYSQL_DATABASE              "samp-novateproject"

/*      [ хмтнплюжхъ н яепбепе ]      */
/*      [ SERVER INFORMATION ]      */
#define SERVER_NAME                 "NoVate Project"
#define SERVER_AUTHOR               "NoVate Source"
#define SERVER_VERSION              "v1.0.0"
#define SERVER_TYPE                 "RolePlay"

#define MAX_AUTHORIZATION_TIME      (120) // Second / яЕЙСМД
#define MAX_REGISTRATION_TIME       (180) // Second / яЕЙСМД
#define AUTHORIZATION_COUNT_TRY     (3)
#define MAX_PASSWORD_LEN            (32)
#define MIN_PASSWORD_LEN            (4)
#define MAX_EMAIL_LEN               (64)
#define MIN_EMAIL_LEN               (1)

/*      [ жберю ]      */
/*      [ COLORS ]      */
#define C_F_WHITE                   0xFFFFFFFF
#define C_WHITE                     "{FFFFFF}"
#define C_F_BLACK                   0x000000FF
#define C_BLACK                     "{000000}"
#define C_F_EMERALD                 0x00FFB2FF
#define C_EMERALD                   "{00FFB2}"
#define C_F_GRAY                    0x666666FF
#define C_GRAY                      "{666666}"
#define C_F_RED                     0xFF2244FF
#define C_RED                       "{FF2244}"
#define C_F_YELLOW                  0xFFCC22FF
#define C_YELLOW                    "{FFCC22}"
#define C_F_GREEN                   0x33DD00FF
#define C_GREEN                     "{33DD00}"

/*      [ оепелеммше тсмйжхи ]      */
/*      [ FUNCTION VARIABLES ]      */
#define function%0(%1)              forward%0(%1); public%0(%1)
#define dCreate:%0(%1)              DialogCreate:%0(%1)
#define dResponse:%0(%1)            DialogResponse:%0(%1, response, listitem, inputtext[])
#define randomEx(%1, %2)            (random(%2 - %1) + %1)
#define SCM                         SendClientMessage
#define SCMTA                       SendClientMessageToAll
#define SPD                         ShowPlayerDialog
#define SCMf                        SendClientMessagef
#define SCMTAf                      SendClientMessageToAllf

/*      [ оепелеммше дкъ яепбепю ]      */
/*      [ SERVER VARIABLES ]      */
enum ServerInfo
{
    MySQL:MySQL
}
new SInfo[ServerInfo];

/*      [ оепелеммше дкъ хцпнйю ]      */
/*      [ PLAYER INFORMATION ]      */
enum PlayerInfo
{
    bool:IsConnection,
    bool:IsLogged,
    bool:IsSpawning,
    AuthorizationTime,
    AuthorizationCountTry,

    Nick[MAX_PLAYER_NAME],
    Password[MAX_PASSWORD_LEN],
    Email[MAX_EMAIL_LEN],
    RegIP[15],
    LastIP[15],
    RegDate[12],
    LastDate[12]
}
new PInfo[MAX_PLAYERS][PlayerInfo];

/*      [ оепелеммше рюилепю дкъ хцпнйю ]      */
/*      [ INFORMATION ABOUT PLAYER TIMERS ]      */
enum PlayerTimerInfo
{
    Authorization,
    Kicks,

    Second
}
new PTimerInfo[MAX_PLAYERS][PlayerTimerInfo];

/*      [ оепелеммше йхйю дкъ хцпнйю ]      */
/*      [ INFORMATION ABOUT THE PLAYER'S KICK ]      */
enum PlayerKickInfo
{
    Nick[MAX_PLAYER_NAME],
    Reason[MAX_PLAYER_NAME*2]
}
new PKickInfo[MAX_PLAYERS][PlayerKickInfo];