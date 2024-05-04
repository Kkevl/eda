reset
set title "result" 
set xlabel "X"
set ylabel "Y"
set object 1 rect from 0,0 to 750,400
set label "block_0" at 375,200 center
set object 2 rect from 1250,0 to 2050,500
set label "block_1" at 1650,250 center
set object 3 rect from 750,1500 to 1550,2000
set label "block_2" at 1150,1750 center
set object 4 rect from 2050,750 to 2675,1550
set label "block_3" at 2362,1150 center
set object 5 rect from 750,0 to 1250,1000
set label "block_4" at 1000,500 center
set object 6 rect from 2850,0 to 3650,750
set label "block_5" at 3250,375 center
set object 7 rect from 2050,0 to 2850,750
set label "block_6" at 2450,375 center
set object 8 rect from 750,2800 to 1870,3425
set label "block_7" at 1310,3112 center
set object 9 rect from 750,2000 to 1625,2800
set label "block_8" at 1187,2400 center
set object 10 rect from 1250,500 to 2050,1500
set label "block_9" at 1650,1000 center
set xtics 200
set ytics 200
plot [0:4000][0:4000]0
set terminal png size 1024,1024
set output "output104.png"
replot