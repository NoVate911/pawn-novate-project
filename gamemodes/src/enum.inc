/*      [ ПЕРЕМЕННЫЕ ДЛЯ СЕРВЕРА ]      */
/*      [ SERVER VARIABLES ]      */
enum ServerInfo
{
    MySQL:MySQL,
    Weather
}
new SInfo[ServerInfo];

/*      [ ПЕРЕМЕННЫЕ ТАЙМЕРА ДЛЯ СЕРВЕРА ]      */
/*      [ TIMER VARIABLES FOR THE SERVER ]      */
enum ServerTimerInfo
{
    Second
}
new STimerInfo[ServerTimerInfo];

enum TimeInfo
{
    TimeOfDayTime,

    Hour,
    Minute,
    Second
}
new TInfo[TimeInfo];

/*      [ ПЕРЕМЕННЫЕ ДЛЯ ЗАРПЛАТЫ ]      */
/*      [ VARIABLES FOR SALARY ]      */
enum PayDayInfo
{
    bool:IsPassed
}
new PDInfo[PayDayInfo];

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
/*      [ TIMER VARIABLES FOR THE PLAYER ]      */
enum PlayerTimerInfo
{
    Authorization,
    Kicks,
    AnimationChat,

    Second
}
new PTimerInfo[MAX_PLAYERS][PlayerTimerInfo];

/*      [ ПЕРЕМЕННЫЕ КИКА ДЛЯ ИГРОКА ]      */
/*      [ KICK VARIABLES FOR THE PLAYER ]      */
enum PlayerKickInfo
{
    Author[MAX_PLAYER_NAME],
    Reason[MAX_PLAYER_NAME*2]
}
new PKickInfo[MAX_PLAYERS][PlayerKickInfo];

/*      [ ПЕРЕМЕННЫЕ С AFK ДЛЯ ИГРОКА ]      */
/*      [ VARIABLES WITH AFK FOR THE PLAYER ]      */
enum PlayerAFKInfo
{
    bool:IsTrue,
    Time,
    Float:Position[3]
}
new PAFKInfo[MAX_PLAYERS][PlayerAFKInfo];

/*      [ ПЕРЕМЕННЫЕ ДЛЯ ПЕРСОНАЖА ]      */
/*      [ VARIABLES FOR THE CHARACTER ]      */
enum CharacterInfo
{
    bool:IsSpawning,

    ID,
    Login[MAX_PLAYER_NAME],
    FirstName[MAX_PLAYER_NAME],
    LastName[MAX_PLAYER_NAME],
    FullName[MAX_PLAYER_NAME],
    Age,
    Sex,
    Race,
    Skin,
    Level,
    Exp,
    ExpTime,
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
    bool:IsAdmin,
    Money,
    MoneyTime
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