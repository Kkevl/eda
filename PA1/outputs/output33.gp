reset
set title "result" 
set xlabel "X"
set ylabel "Y"
set object 1 rect from 406,749 to 539,1085
set label "bk1" at 472,917 center
set object 2 rect from 413,0 to 532,378
set label "bk10a" at 472,189 center
set object 3 rect from 588,378 to 728,539
set label "bk10b" at 658,458 center
set object 4 rect from 287,406 to 336,525
set label "bk10c" at 311,465 center
set object 5 rect from 847,357 to 966,532
set label "bk11" at 906,444 center
set object 6 rect from 273,0 to 413,406
set label "bk12" at 343,203 center
set object 7 rect from 133,0 to 273,497
set label "bk13" at 203,248 center
set object 8 rect from 0,679 to 119,875
set label "bk14a" at 59,777 center
set object 9 rect from 1078,532 to 1197,826
set label "bk14b" at 1137,679 center
set object 10 rect from 728,371 to 847,532
set label "bk14c" at 787,451 center
set object 11 rect from 826,532 to 945,798
set label "bk15a" at 885,665 center
set object 12 rect from 1141,0 to 1260,336
set label "bk15b" at 1200,168 center
set object 13 rect from 336,406 to 455,532
set label "bk16" at 395,469 center
set object 14 rect from 658,0 to 840,371
set label "bk17a" at 749,185 center
set object 15 rect from 119,679 to 301,882
set label "bk17b" at 210,780 center
set object 16 rect from 301,532 to 483,735
set label "bk18" at 392,633 center
set object 17 rect from 0,560 to 84,679
set label "bk19" at 42,619 center
set object 18 rect from 945,532 to 1078,826
set label "bk2" at 1011,679 center
set object 19 rect from 959,0 to 1141,350
set label "bk20" at 1050,175 center
set object 20 rect from 0,882 to 140,1197
set label "bk21" at 70,1039 center
set object 21 rect from 140,882 to 273,1197
set label "bk3" at 206,1039 center
set object 22 rect from 0,0 to 133,560
set label "bk4" at 66,280 center
set object 23 rect from 455,378 to 588,518
set label "bk5a" at 521,448 center
set object 24 rect from 966,350 to 1099,525
set label "bk5b" at 1032,437 center
set object 25 rect from 693,539 to 826,770
set label "bk5c" at 759,654 center
set object 26 rect from 273,882 to 406,1197
set label "bk6" at 339,1039 center
set object 27 rect from 1218,336 to 1316,518
set label "bk7" at 1267,427 center
set object 28 rect from 483,539 to 693,749
set label "bk8a" at 588,644 center
set object 29 rect from 532,0 to 658,378
set label "bk8b" at 595,189 center
set object 30 rect from 1099,350 to 1218,532
set label "bk9a" at 1158,441 center
set object 31 rect from 168,497 to 287,616
set label "bk9b" at 227,556 center
set object 32 rect from 840,0 to 959,357
set label "bk9c" at 899,178 center
set object 33 rect from 84,560 to 168,679
set label "bk9d" at 126,619 center
set xtics 280
set ytics 240
plot [0:1400][0:1200]0
set terminal png size 1024,768
set output "output.png"
replot