import org.ieee.cec15.cbcsono.DataGeneratorJNI;
import java.util.Arrays;


public class DataGeneratorTest {

 static {
  System.loadLibrary("datageneratorjni"); 
      // Load native library at runtime
      // cec15jni.dll (Windows) or libcec15jni.so (Unixes)
}

   // Declare a native method sayHello() that receives nothing and returns void
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