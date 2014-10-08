javac DataGeneratorJNI.java -d .

javah org.ieee.cec15.cbcsono.DataGeneratorJNI

cl /LD datageneratorjni.c ..\datagenerator\datagenerator.c /I..\datagenerator /I..\meschach /I"D:\Program Files\Java\jdk1.8.0_20\include" /I"D:\Program Files\Java\jdk1.8.0_20\include\win32" ..\meschach\copy.c ..\meschach\err.c ..\meschach\hsehldr.c ..\meschach\init.c ..\meschach\ivecop.c ..\meschach\machine.c ..\meschach\meminfo.c ..\meschach\memory.c ..\meschach\memstat.c ..\meschach\qrfactor.c ..\meschach\submat.c ..\meschach\vecop.c

del *.obj

javac DataGeneratorTest.java

java -Djava.library.path=. DataGeneratorTest