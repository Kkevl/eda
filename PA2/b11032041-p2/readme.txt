1. 學號：b11032041
2. 姓名：譚凱文
3. 使用之程式語言：C++
4. 使用之編譯平台：Linux GNU g++
5. 檔案壓縮方式: tar zcvf b11032041-p1.tgz b11032041-p1
6. 各檔案說明：
	b11032041-p2/main.cpp	: 主程式source code
	b11032041-p2/block.hpp	: save for input files.
	b11032041-p2/grapher.hpp: manage all changes to DAG graph.
	b11032041-p2/plotmanager.hpp: the manager of grapher.hpp, it also manage all of the ouput.
	b11032041-p2.DAG.hpp	: this file can create a DAG and also return the result of longest path from DAG.
  	b11032041-p2/Makefile	: Makefile
	b11032041-p2/readme.txt	: 本檔案
7. 編譯方式說明：        	
   主程式：
	   在 b11032041-p2/ 這個資料夾下指令 : make
	   即可在 b11032041-p2 產生 floorplanner 的執行檔
	
8. 執行、使用方式說明：
   主程式：
   	   compile 完成後，在 b11032041-p2/ 目錄下會產生一個 floorplanner 的執行檔
   	   執行檔的命令格式為 :
   	   ./floorplanner [input file name] [output file name]
	   ex: ./floorplanner input.txt output.out
