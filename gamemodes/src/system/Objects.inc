/*      [ СОЗДАТЬ ОБЪЕКТЫ ДЛЯ ИГРОКА ]      */
/*      [ CREATE OBJECTS FOR THE PLAYER ]      */
stock Objects_Create_For_Player(playerid)
{
    // 2522.0081, -1272.9301, 35.6090
    CreateDynamicObject(17946, 2533.8203, -1290.5547, 36.9453, 0.00000, 0.00000, 0.00000, -1, -1, playerid);
    CreateDynamicObject(17933, 2533.8203, -1290.5547, 36.9453, 0.00000, 0.00000, 0.00000, -1, -1, playerid);

    // -2719.0156, 861.2109, 72.1563
    CreateDynamicObject(19600, -2719.02002, 861.21100, 72.15620, 0.00000, 0.00000, 0.00000, -1, -1, playerid);
    CreateDynamicObject(19598, -2719.02002, 861.21100, 72.15620, 0.00000, 0.00000, 0.00000, -1, -1, playerid);
    CreateDynamicObject(19599, -2719.02002, 861.21100, 72.15620, 0.00000, 0.00000, 0.00000, -1, -1, playerid);

    // -1909.55469, 497.21881, 25.71090
    CreateDynamicObject(19485, -1909.55469, 497.21881, 25.71090, 0.00000, 0.00000, 0.00000, -1, -1, playerid);

    // -2110.8281, -27.3594, 36.9766
    CreateDynamicObject(19486, -2110.82813, -27.35940, 36.97660, 0.00000, 0.00000, -90.00000, -1, -1, playerid);

    // -1875.0234, -65.3281, 15.0625
    CreateDynamicObject(19484, -1875.02344, -65.32810, 15.06250, 0.00000, 0.00000, 0.00000, -1, -1, playerid);

    // 191.1406, 1870.0391, 21.4766
    CreateDynamicObject(19312, 191.14063, 1870.03906, 21.47656, 0.0, 0.0, 0.0, -1, -1, playerid);

    // 1787.1328, -1565.6797, 11.9688
    CreateDynamicObject(19794, 1787.13281, -1565.67969, 11.96880, 0.00000, 0.00000, 0.00000, -1, -1, playerid);

    // 1421.3750, -1477.6016, 42.2031
    CreateDynamicObject(19879, 1421.38000, -1477.59998, 42.20310, 0.00000, 0.00000, 0.00000, -1, -1, playerid);

    // 1117.5859, -1490.0078, 32.7188
    CreateDynamicObject(19322, 1117.58594, -1490.00781, 32.71880, 0.00000, 0.00000, 0.00000, -1, -1, playerid);
    CreateDynamicObject(19323, 1117.58594, -1490.00781, 32.71880, 0.00000, 0.00000, 0.00000, -1, -1, playerid);

    // 1160.9609, -1180.5781, 70.4141
    CreateDynamicObject(19595, 1160.95996, -1180.57996, 70.41410, 0.00000, 0.00000, 0.00000, -1, -1, playerid);
    CreateDynamicObject(19798, 1160.95996, -1180.57996, 20.41410, 0.00000, 0.00000, 0.00000, -1, -1, playerid);
    CreateDynamicObject(18755, 1181.58997, -1180.55359, 34.56100, 0.00000, 0.00000, 0.00000, -1, -1, playerid);
    CreateDynamicObject(18755, 1181.58997, -1180.55359, 20.94000, 0.00000, 0.00000, 0.00000, -1, -1, playerid);

    // 666.7109, -565.1328, 17.3359
    CreateDynamicObject(19876, 666.71100, -565.13300, 17.33590, 0.00000, 0.00000, 0.00000, -1, -1, playerid);
    CreateDynamicObject(19877, 666.49200, -571.17999, 17.31250, 0.00000, 0.00000, 0.00000, -1, -1, playerid);
    CreateDynamicObject(1514, 665.28607, -567.54132, 16.46700, 0.00000, 0.00000, 0.00000, -1, -1, playerid);
    return 1;
}

/*      [ УДАЛИТЬ ОБЪЕКТЫ ДЛЯ ИГРОКА ]      */
/*      [ DELETE OBJECTS FOR THE PLAYER ]      */
stock Objects_Remove_For_Player(playerid)
{
    // 213.0821, 1875.7795, 17.6406
    RemoveBuildingForPlayer(playerid, 2887, 213.0821, 1875.7795, 17.6406, 200.25);
    RemoveBuildingForPlayer(playerid, 2888, 213.0821, 1875.7795, 17.6406, 200.25);
    RemoveBuildingForPlayer(playerid, 2889, 213.0821, 1875.7795, 17.6406, 200.25);

    // 1055.1447, 2086.0205, 10.8203
    RemoveBuildingForPlayer(playerid, 2938, 1055.1447, 2086.0205, 10.8203, 200.25);

    // 710.6017, 913.7717, -18.6504
    RemoveBuildingForPlayer(playerid, 16328, 710.6017, 913.7717, -18.6504, 200.25);
    RemoveBuildingForPlayer(playerid, 16329, 710.6017, 913.7717, -18.6504, 200.25);
    RemoveBuildingForPlayer(playerid, 16330, 710.6017, 913.7717, -18.6504, 200.25);
    RemoveBuildingForPlayer(playerid, 16331, 710.6017, 913.7717, -18.6504, 200.25);
    RemoveBuildingForPlayer(playerid, 16332, 710.6017, 913.7717, -18.6504, 200.25);
    RemoveBuildingForPlayer(playerid, 16333, 710.6017, 913.7717, -18.6504, 200.25);

    // 1902.7299, 966.6155, 10.8203
    RemoveBuildingForPlayer(playerid, 3084, 1902.7299, 966.6155, 10.8203, 200.25);

    // -1437.0055, 501.5506, 18.2344
    RemoveBuildingForPlayer(playerid, 3114, -1437.0055, 501.5506, 18.2344, 200.25);
    RemoveBuildingForPlayer(playerid, 3115, -1437.0055, 501.5506, 18.2344, 200.25);

    // -2179.35352, 661.22162, 50.21000
    RemoveBuildingForPlayer(playerid, 3036, -2179.35352, 661.22162, 50.21000, 200.25);

    // -2072.2192, 254.0042, 35.4754
    RemoveBuildingForPlayer(playerid, 3054, -2072.2192, 254.0042, 35.4754, 200.25);
    RemoveBuildingForPlayer(playerid, 1403, -2072.2192, 254.0042, 35.4754, 200.25);
    RemoveBuildingForPlayer(playerid, 1404, -2072.2192, 254.0042, 35.4754, 200.25);
    RemoveBuildingForPlayer(playerid, 1383, -2072.2192, 254.0042, 35.4754, 200.25);
    RemoveBuildingForPlayer(playerid, 1385, -2072.2192, 254.0042, 35.4754, 200.25);
    RemoveBuildingForPlayer(playerid, 1384, -2072.2192, 254.0042, 35.4754, 200.25);
    RemoveBuildingForPlayer(playerid, 1684, -2072.2192, 254.0042, 35.4754, 200.25);

    // -1549.6687, 122.0678, 3.5547
    RemoveBuildingForPlayer(playerid, 1379, -1549.6687, 122.0678, 3.5547, 200.25);
    RemoveBuildingForPlayer(playerid, 1380, -1549.6687, 122.0678, 3.5547, 200.25);
    RemoveBuildingForPlayer(playerid, 1381, -1549.6687, 122.0678, 3.5547, 200.25);
    RemoveBuildingForPlayer(playerid, 1382, -1549.6687, 122.0678, 3.5547, 200.25);
    RemoveBuildingForPlayer(playerid, 1398, -1549.6687, 122.0678, 3.5547, 200.25);
    RemoveBuildingForPlayer(playerid, 1399, -1549.6687, 122.0678, 3.5547, 200.25);
    RemoveBuildingForPlayer(playerid, 1400, -1549.6687, 122.0678, 3.5547, 200.25);

    // 2309.5461, -15.1403, 27.0973
    RemoveBuildingForPlayer(playerid, 2946, 2309.5461, -15.1403, 27.0973, 200.25);
    RemoveBuildingForPlayer(playerid, 2947, 2309.5461, -15.1403, 27.0973, 200.25);
    
    // 2522.0081, -1272.9301, 35.6090
    RemoveBuildingForPlayer(playerid, 3059, 2522.0081, -1272.9301, 35.6090, 200.25);

    // 2169.7891, -1516.8173, 23.5625
    RemoveBuildingForPlayer(playerid, 3083, 2169.7891, -1516.8173, 23.5625, 200.25);

    // -2719.0156, 861.2109, 72.1563
    RemoveBuildingForPlayer(playerid, 9671, -2719.0156, 861.2109, 72.1563, 0.25);
    RemoveBuildingForPlayer(playerid, 9510, -2719.0156, 861.2109, 72.1563, 0.25);

    // -1909.55469, 497.21881, 25.71090
    RemoveBuildingForPlayer(playerid, 10938, -1909.5547, 497.2188, 25.7109, 0.25);
    RemoveBuildingForPlayer(playerid, 11144, -1909.5547, 497.2188, 25.7109, 0.25);

    // -2110.8281, -27.3594, 36.9766
    RemoveBuildingForPlayer(playerid, 11163, -2110.8281, -27.3594, 36.9766, 0.25);
    RemoveBuildingForPlayer(playerid, 11092, -2110.8281, -27.3594, 36.9766, 0.25);
    RemoveBuildingForPlayer(playerid, 11102, -2102.9297, -16.0547, 36.4844, 0.25);

    // -1875.0234, -65.3281, 15.0625
    RemoveBuildingForPlayer(playerid, 10850, -1875.0234, -65.3281, 15.0625, 0.25);
    RemoveBuildingForPlayer(playerid, 10919, -1875.0234, -65.3281, 15.0625, 0.25);

    // 191.1406, 1870.0391, 21.4766
    RemoveBuildingForPlayer(playerid, 16094, 191.1406, 1870.0391, 21.4766, 200.25);

    // 1787.1328, -1565.6797, 11.9688
    RemoveBuildingForPlayer(playerid, 4080, 1787.1328, -1565.6797, 11.9688, 0.25);
    RemoveBuildingForPlayer(playerid, 4000, 1787.1328, -1565.6797, 11.9688, 0.25);

    // 1421.3750, -1477.6016, 42.2031
    RemoveBuildingForPlayer(playerid, 4009, 1421.3750, -1477.6016, 42.2031, 0.25);
    RemoveBuildingForPlayer(playerid, 4007, 1421.3750, -1477.6016, 42.2031, 0.25);

    // 1117.5859, -1490.0078, 32.7188
    RemoveBuildingForPlayer(playerid, 6130, 1117.5859, -1490.0078, 32.7188, 0.25);
    RemoveBuildingForPlayer(playerid, 6255, 1117.5859, -1490.0078, 32.7188, 0.25);
    RemoveBuildingForPlayer(playerid, 762, 1175.3594, -1420.1875, 19.8828, 0.25);

    // 1160.9609, -1180.5781, 70.4141
    RemoveBuildingForPlayer(playerid, 5767, 1160.9609, -1180.5781, 70.4141, 0.25);
    RemoveBuildingForPlayer(playerid, 5964, 1160.9609, -1180.5781, 70.4141, 0.25);

    // 666.7109, -565.1328, 17.3359
    RemoveBuildingForPlayer(playerid, 13245, 666.7109, -565.1328, 17.3359, 0.25);
    RemoveBuildingForPlayer(playerid, 12854, 666.4922, -571.1797, 17.3125, 0.25);
    RemoveBuildingForPlayer(playerid, 1514, 665.2891, -567.2813, 16.4297, 0.25);
    RemoveBuildingForPlayer(playerid, 12853, 666.7109, -565.1328, 17.3359, 0.25);
    return 1;
}