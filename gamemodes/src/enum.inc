/*      [ ПЕРЕМЕННЫЕ ДЛЯ СЕРВЕРА ]      */
/*      [ SERVER VARIABLES ]      */
enum ServerInfo
{
    MySQL:MySQL,
    Weather
}
new SInfo[ServerInfo];

enum ServerTimerInfo
{
    Minute
}
new STimerInfo[ServerTimerInfo];

/*      [ ПЕРЕМЕННЫЕ ДЛЯ ИГРОКА ]      */
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
    Donate,
    RegIP[16],
    LastIP[16],
    RegDate[22],
    LastDate[22],

    CharactersCount,
    CharacterSelect
}
new PInfo[MAX_PLAYERS][PlayerInfo];

/*      [ ПЕРЕМЕННЫЕ ТАЙМЕРА ДЛЯ ИГРОКА ]      */
/*      [ INFORMATION ABOUT PLAYER TIMERS ]      */
enum PlayerTimerInfo
{
    Authorization,
    Kicks,
    AnimationChat,

    Second
}
new PTimerInfo[MAX_PLAYERS][PlayerTimerInfo];

/*      [ ПЕРЕМЕННЫЕ КИКА ДЛЯ ИГРОКА ]      */
/*      [ INFORMATION ABOUT THE PLAYER'S KICK ]      */
enum PlayerKickInfo
{
    Nick[MAX_PLAYER_NAME],
    Reason[MAX_PLAYER_NAME*2]
}
new PKickInfo[MAX_PLAYERS][PlayerKickInfo];

/*      [ ПЕРЕМЕННЫЕ ДЛЯ ПЕРСОНАЖА ]      */
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
    Float:Armour,
    AdminLevel,
    AdminPassword,
    bool:IsAdmin
}
new CInfo[MAX_PLAYERS][MAX_CHARACTERS][CharacterInfo];

/*      [ ПЕРЕМЕННЫЕ ТРАНСПОРТА ]      */
/*      [ TRANSPORT VARIABLES ]      */
enum VehicleInfo
{
    ID,
    Model,
    Float:Position[3],
    Float:Rotation,
    Color1,
    Color2,
    Float:Fuel,
    Float:Health,
    Text3D:Description,
    
    bool:IsEngine,
    bool:IsLights,
    bool:IsDoorsClosed
}
new VInfo[MAX_VEHICLES][VehicleInfo];
new Vehicle_Count; // Количество созданного транспорта | Number of vehicles created