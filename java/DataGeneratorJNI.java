package org.ieee.cec15.cbcsono;
import java.util.Arrays;


public class DataGeneratorJNI {

 static {
  System.loadLibrary("datageneratorjni"); 
      // Load native library at runtime
      // cec15jni.dll (Windows) or libcec15jni.so (Unixes)
}

   // Declare a native method sayHello() that receives nothing and returns void
public native double rand();
   // Use long as unsigned int 0 - 2^32-1
public native void reseed(long x, long y, long z, long c);   
public native double[][] rand(int m, int n);
public native int [] shuffle(int n);
public native double[][] rotate(int n);

   // Test Driver
public static void main(String[] args) {
 DataGeneratorJNI jk = new DataGeneratorJNI();

 jk.reseed(10,20,30,40);
 double [][] mat = jk.rotate(2);
 if (mat!=null)
 {
  System.out.println(Arrays.toString(mat[0]));
  System.out.println(Arrays.toString(mat[1]));
}

jk.reseed(10,20,30,40);
mat = jk.rand(2,2);
if (mat!=null)
{
  System.out.println(Arrays.toString(mat[0]));
  System.out.println(Arrays.toString(mat[1]));
}
jk.reseed(10,20,30,40);



int [] s = jk.shuffle(10);
if (s!=null)
  System.out.println(Arrays.toString(s));


}
}