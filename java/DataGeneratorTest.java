import org.ieee.cec15.cbcsono.DataGeneratorJNI;
import java.io.*;


public class DataGeneratorTest {

 static {
  System.loadLibrary("datageneratorjni"); 
      // Load native library at runtime
      // cec15jni.dll (Windows) or libcec15jni.so (Unixes)
}

   // Declare a native method sayHello() that receives nothing and returns void
   // Test Driver
public static void main(String[] args) {

  try{

    DataGeneratorTest.ProduceDataFiles();

  }catch(IOException e)
  {
    System.out.println("IO Error " + e);
  }
//  DataGeneratorJNI jk = new DataGeneratorJNI();

//  jk.reseed(10,20,30,40);
//  double [][] mat = jk.rotate(2);
//  if (mat!=null)
//  {
//   System.out.println(Arrays.toString(mat[0]));
//   System.out.println(Arrays.toString(mat[1]));
// }

// jk.reseed(10,20,30,40);
// mat = jk.rand(2,2);
// if (mat!=null)
// {
//   System.out.println(Arrays.toString(mat[0]));
//   System.out.println(Arrays.toString(mat[1]));
// }
// jk.reseed(10,20,30,40);



// int [] s = jk.shuffle(10);
// if (s!=null)
//   System.out.println(Arrays.toString(s));


}


public static void ProduceDataFiles()   throws IOException
{    
    // new variables
  int cf_numbers[] = {1,1,1,1,1,1,1,1,1,1,1,1,5,3,5};

  DataGeneratorJNI jk = new DataGeneratorJNI();

  jk.reseed(12345, 67890, 98765, 43210);


  for (int func_num = 1; func_num <= 15; func_num++) {
    for (int dim = 10; dim<=30; dim+= 20){


      int cf_number = cf_numbers[func_num-1];

            //Mdata = (double*)malloc(dim*cf_number*dim*sizeof(double));
      String Mfile = "M_" + func_num + "_D"+ dim +".txt";

      PrintWriter out = new PrintWriter(Mfile);

      for (int i = 1; i<= cf_number; i++) {
        double[][] Mdata = jk.rotate(dim);
        for (int j=0; j<dim; j++) {
          for (int k=0; k<dim; k++) {
            out.printf("%24.16e ", Mdata[j][k]);
          }
          out.printf("\n");
        }

      }

      out.close();


      String Sfile = "shift_data_" + func_num + "_D"+ dim +".txt";

      out = new PrintWriter(Sfile);
      for (int i = 1; i<= cf_number; i++) {
        double [][] Sdata = jk.rand(1, dim);
        for (int j=0; j<dim; j++) {
          out.printf("%24.16e ", Sdata[0][j]);
        }
        out.printf("\n");
      }
      out.close();


      int []shuffle = jk.shuffle(dim);


      String Permfile = "shuffle_data_" + func_num + "_D" + dim + ".txt";

      out = new PrintWriter(Permfile);
      for (int k=0; k<dim; k++)
        out.printf("%d\t", shuffle[k]);
      out.close();

           //free(Mdata);
            //free(Sdata);

    }
  }
}


}
