#include <jni.h>
#include <stdlib.h>
#include "org_ieee_cec15_cbcsono_DataGeneratorJNI.h"
#include "datagenerator.h"




unsigned int get_uint32(jlong x)
{
    return (unsigned int) (x & 0xffffffff);
}



/*
 * Class:     org_ieee_cec15_cbcsono_DataGeneratorJNI
 * Method:    reseed
 * Signature: (JJJJ)V
 */
JNIEXPORT void JNICALL Java_org_ieee_cec15_cbcsono_DataGeneratorJNI_reseed
  (JNIEnv *env, jobject obj, jlong jx, jlong jy, jlong jz, jlong jc)
{
    unsigned int x,y,z,c;
    x = get_uint32(jx);
    y = get_uint32(jy);
    z = get_uint32(jz);
    c = get_uint32(jc);
    cec15_reseed(x,y,z,c);
}

/*
 * Class:     org_ieee_cec15_cbcsono_DataGeneratorJNI
 * Method:    rand
 * Signature: ()D
 */
JNIEXPORT jdouble JNICALL Java_org_ieee_cec15_cbcsono_DataGeneratorJNI_rand__
  (JNIEnv *env, jobject obj)
{
    return cec15_rand();
}




/*
 * Class:     org_ieee_cec15_cbcsono_DataGeneratorJNI
 * Method:    rand
 * Signature: (II)[[D
 */
JNIEXPORT jobjectArray JNICALL Java_org_ieee_cec15_cbcsono_DataGeneratorJNI_rand__II
  (JNIEnv *env, jobject obj, jint m, jint n)
{
    // The 2D long array to return

    double* mat = malloc(sizeof(double)*n*m);
    int i;   
    jobjectArray myReturnable2DArray;
    jdoubleArray doubleArray;
    // Get the double array class
    jclass doubleArrayClass = (*env)->FindClass(env, "[D");


    cec15_rand_matrix(m, n, mat);

    // Check if we properly got the long double class
    if (doubleArrayClass == NULL) {
        // Ooops
        //printf("Can't find jclass for doubleArrayClass [[D\n");
        return NULL;
    }

    // Create the returnable 2D array
    myReturnable2DArray = (*env)->NewObjectArray(env, (jsize) m, doubleArrayClass, NULL);

    // Go through the firs dimension and add the second dimension arrays
    for (i = 0; i < m; i++) {
        doubleArray = (*env)->NewDoubleArray(env, n);
        (*env)->SetDoubleArrayRegion(env, doubleArray, (jsize) 0, (jsize) n, (jdouble*) (mat+i*n));
        (*env)->SetObjectArrayElement(env, myReturnable2DArray, (jsize) i, doubleArray);
        (*env)->DeleteLocalRef(env, doubleArray);
    }


    free(mat);
    // Return a Java consumable 2D double array
    return myReturnable2DArray;    
}

/*
 * Class:     org_ieee_cec15_cbcsono_DataGeneratorJNI
 * Method:    shuffle
 * Signature: (I)[I
 */
JNIEXPORT jintArray JNICALL Java_org_ieee_cec15_cbcsono_DataGeneratorJNI_shuffle
  (JNIEnv *env, jobject obj, jint n)
{
   int *vec = malloc(n * sizeof(int));
   jint* outVec = malloc(n*sizeof(int));
   int i;
   // // Step 1: Convert the incoming JNI jintarray to C's jint[]
   // jint *inCArray = (*env)->GetIntArrayElements(env, inJNIArray, NULL);
   // if (NULL == inCArray) return NULL;
   // jsize length = (*env)->GetArrayLength(env, inJNIArray);
 
   // // Step 2: Perform its intended operations
   // jint sum = 0;
   // int i;
   // for (i = 0; i < length; i++) {
   //    sum += inCArray[i];
   // }
   // jdouble average = (jdouble)sum / length;
   // (*env)->ReleaseIntArrayElements(env, inJNIArray, inCArray, 0); // release resources
 
   // jdouble outCArray[] = {sum, average};
 
   // Step 3: Convert the C's Native jdouble[] to JNI jdoublearray, and return
   jintArray outJNIArray = (*env)->NewIntArray(env, n);  // allocate
   if (NULL == outJNIArray) return NULL;

   cec15_shuffle(n, vec);
   for (i=0; i<n; i++)
     outVec[i] = (jint)vec[i];


   (*env)->SetIntArrayRegion(env, outJNIArray, (jsize)0 , (jsize)n, outVec);  // copy


   free(vec);
   free(outVec);
   return outJNIArray;    
}

/*
 * Class:     org_ieee_cec15_cbcsono_DataGeneratorJNI
 * Method:    rotate
 * Signature: (I)[[D
 */
JNIEXPORT jobjectArray JNICALL Java_org_ieee_cec15_cbcsono_DataGeneratorJNI_rotate
  (JNIEnv *env, jobject obj, jint m)
{
    // The 2D long array to return

    double* mat = malloc(sizeof(double)*m*m);
    int i;   
    jobjectArray myReturnable2DArray;
    jdoubleArray doubleArray;
    // Get the double array class
    jclass doubleArrayClass = (*env)->FindClass(env, "[D");


    cec15_rotate(m, mat);

    // Check if we properly got the long double class
    if (doubleArrayClass == NULL) {
        // Ooops
        //printf("Can't find jclass for doubleArrayClass [[D\n");
        return NULL;
    }

    // Create the returnable 2D array
    myReturnable2DArray = (*env)->NewObjectArray(env, (jsize) m, doubleArrayClass, NULL);

    // Go through the firs dimension and add the second dimension arrays
    for (i = 0; i < m; i++) {
        doubleArray = (*env)->NewDoubleArray(env, m);
        (*env)->SetDoubleArrayRegion(env, doubleArray, (jsize) 0, (jsize) m, (jdouble*) (mat+i*m));
        (*env)->SetObjectArrayElement(env, myReturnable2DArray, (jsize) i, doubleArray);
        (*env)->DeleteLocalRef(env, doubleArray);
    }


    free(mat);
    // Return a Java consumable 2D double array
    return myReturnable2DArray;      
}


