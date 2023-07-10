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
    AuthorizationTime,
    AuthorizationCountTry,

    ID,
    Nick[MAX_PLAYER_NAME],
    Password[MAX_PASSWORD_LEN],
    Email[MAX_EMAIL_LEN],
    RegIP[16],
    LastIP[16],
    RegDate[22],
    LastDate[22],

    CharactersCount,
    CharacterSelect
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

/*      [ оепелеммше дкъ оепянмюфю ]      */
/*      [ VARIABLES FOR THE CHARACTER ]      */
enum CharacterInfo
{
    bool:IsSpawning,

    ID,
    Login[MAX_PLAYER_NAME],
    FirstName[MAX_PLAYER_NAME],
    LastName[MAX_PLAYER_NAME],
    Age,
    Sex,
    Race,
    Skin,
    Level,
    Exp,
    RegIP[16],
    LastIP[16],
    RegDate[22],
    LastDate[22],
    Float:Position[3],
    Float:Rotation,
    Interior,
    VirtualWorld,
    Float:Health,
    Float:Armour
}
new CInfo[MAX_PLAYERS][MAX_CHARACTERS][CharacterInfo];