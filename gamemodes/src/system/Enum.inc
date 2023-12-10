/*      [ ПЕРЕМЕННЫЕ ТРАНСПОРТА ]      */
/*      [ TRANSPORT VARIABLES ]      */
enum VehicleInfo
{
    ID,
    Model,
    Float:SpawnPosition[3],
    Float:SpawnRotation,
    Float:CurrentPosition[3],
    Float:CurrentRotation,
    Color1,
    Color2,
    Float:Fuel,
    Float:Health,
    Float:Speed,
    Float:Mileage,
    Text3D:Description,
    VirtualWorld,
    
    bool:IsUsed,
    bool:IsEngine,
    bool:IsLights,
    bool:IsDoorsClosed
}
new VInfo[MAX_VEHICLES][VehicleInfo];
new VehicleCount; // Количество созданного транспорта | Number of vehicles created

/*      [ ПЕРЕМЕННЫЕ ИНТЕРФЕЙСА (сервер) ]      */
/*      [ INTERFACE VARIABLES (server) ]      */
enum TextDrawInfo
{
    Text:Time
}
new TDInfo[TextDrawInfo];

/*      [ ПЕРЕМЕННЫЕ ИНТЕРФЕЙСА (игрок) ]      */
/*      [ INTERFACE VARIABLES (player) ]      */
enum PlayerTextDrawInfo
{
    PlayerText:Notification,
    PlayerText:Speedometer[6],
}
new PTDInfo[MAX_PLAYERS][PlayerTextDrawInfo];