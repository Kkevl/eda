set object 1 rect from 750,400
set label "block_0" at 575 center
set object 2 rect from 800,500
set label "block_1" at 650 center
set object 3 rect from 800,500
set label "block_2" at 650 center
set object 4 rect from 625,800
set label "block_3" at 712 center
set object 5 rect from 500,1000
set label "block_4" at 750 center
set object 6 rect from 800,750
set label "block_5" at 775 center
set object 7 rect from 800,750
set label "block_6" at 775 center
set object 8 rect from 1120,625
set label "block_7" at 872 center
set object 9 rect from 875,800
set label "block_8" at 837 center
set object 10 rect from 800,1000
set label "block_9" at 900 center
set xtics 0
set ytics 0
plot [0:0][0:0]0
set terminal png size 1024,768
set output "output.png"
replot