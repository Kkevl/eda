reset
set title "result" 
set xlabel "X"
set ylabel "Y"
set object 1 rect from 0,0 to 1708,3234
set label "M001" at 854,1617 center
set object 2 rect from 3262,5950 to 3934,7504
set label "M002" at 3598,6727 center
set object 3 rect from 3318,0 to 4326,2184
set label "M003" at 3822,1092 center
set object 4 rect from 1708,0 to 3318,3080
set label "M004" at 2513,1540 center
set object 5 rect from 2730,5936 to 3262,7322
set label "M005" at 2996,6629 center
set object 6 rect from 3962,5180 to 4844,7042
set label "M006" at 4403,6111 center
set object 7 rect from 2310,3864 to 2660,4732
set label "M007" at 2485,4298 center
set object 8 rect from 0,5810 to 644,7056
set label "M008" at 322,6433 center
set object 9 rect from 4802,2716 to 5264,3696
set label "M009" at 5033,3206 center
set object 10 rect from 168,3234 to 462,3850
set label "M010" at 315,3542 center
set object 11 rect from 4606,1890 to 4984,2716
set label "M011" at 4795,2303 center
set object 12 rect from 2926,3080 to 3332,3878
set label "M012" at 3129,3479 center
set object 13 rect from 462,3234 to 728,3906
set label "M013" at 595,3570 center
set object 14 rect from 3584,2982 to 3990,3906
set label "M014" at 3787,3444 center
set object 15 rect from 784,3976 to 1190,4816
set label "M015" at 987,4396 center
set object 16 rect from 3850,2184 to 4172,2982
set label "M016" at 4011,2583 center
set object 17 rect from 1470,3234 to 1862,3990
set label "M017" at 1666,3612 center
set object 18 rect from 1848,4844 to 2240,5922
set label "M018" at 2044,5383 center
set object 19 rect from 392,3962 to 784,4788
set label "M019" at 588,4375 center
set object 20 rect from 3598,2184 to 3850,2982
set label "M020" at 3724,2583 center
set object 21 rect from 0,3850 to 392,4676
set label "M021" at 196,4263 center
set object 22 rect from 3990,2996 to 4354,3948
set label "M022" at 4172,3472 center
set object 23 rect from 2240,4746 to 2730,5880
set label "M023" at 2485,5313 center
set object 24 rect from 3332,2184 to 3598,2982
set label "M024" at 3465,2583 center
set object 25 rect from 1862,3080 to 2184,3864
set label "M025" at 2023,3472 center
set object 26 rect from 728,3234 to 1078,3962
set label "M026" at 903,3598 center
set object 27 rect from 1190,3990 to 1554,4830
set label "M027" at 1372,4410 center
set object 28 rect from 1330,4844 to 1848,5908
set label "M028" at 1589,5376 center
set object 29 rect from 0,4788 to 490,5782
set label "M029" at 245,5285 center
set object 30 rect from 2002,5922 to 2730,7224
set label "M030" at 2366,6573 center
set object 31 rect from 938,4830 to 1330,5880
set label "M031" at 1134,5355 center
set object 32 rect from 2548,3080 to 2926,3864
set label "M032" at 2737,3472 center
set object 33 rect from 4326,0 to 5278,1890
set label "M033" at 4802,945 center
set object 34 rect from 2730,4788 to 3290,5936
set label "M034" at 3010,5362 center
set object 35 rect from 1918,3864 to 2310,4718
set label "M035" at 2114,4291 center
set object 36 rect from 490,4816 to 938,5810
set label "M036" at 714,5313 center
set object 37 rect from 4466,3962 to 5026,5180
set label "M037" at 4746,4571 center
set object 38 rect from 4354,2996 to 4802,3962
set label "M038" at 4578,3479 center
set object 39 rect from 2184,3080 to 2548,3864
set label "M039" at 2366,3472 center
set object 40 rect from 2660,3878 to 3052,4746
set label "M040" at 2856,4312 center
set object 41 rect from 1554,3990 to 1918,4844
set label "M041" at 1736,4417 center
set object 42 rect from 0,3234 to 168,3612
set label "M042" at 84,3423 center
set object 43 rect from 3052,3878 to 3584,4788
set label "M043" at 3318,4333 center
set object 44 rect from 1372,5922 to 2002,7224
set label "M044" at 1687,6573 center
set object 45 rect from 3290,4788 to 3962,5950
set label "M045" at 3626,5369 center
set object 46 rect from 3962,3962 to 4466,5166
set label "M046" at 4214,4564 center
set object 47 rect from 4172,2184 to 4606,2996
set label "M047" at 4389,2590 center
set object 48 rect from 644,5908 to 1372,7210
set label "M048" at 1008,6559 center
set object 49 rect from 1078,3234 to 1470,3976
set label "M049" at 1274,3605 center
set object 50 rect from 5279,0 to 5810,2530
set label "M050" at 5544,1265 center
set xtics 1200
set ytics 1600
plot [0:6000][0:8000]0
set terminal png size 1024,768
set output "output.png"
replot