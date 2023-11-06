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