# include <iostream>
# include "mat.h"
using namespace std;

int main()
{

    int row,col;
    cin>>row>>col;
    double *data=new double[row*col];

    for(int i=0;i<row;i++){
        for(int j=0; j<col;j++){
            cin>>data[i*j];
        }
    }
    Matrix imageData(row,col,data,"Image Data");
    //imageData.print("Original Image Data");


    Matrix mean = imageData.meanVec();
    //mean.print("Mean of the columns");

    //Center Data in each column around the mean
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            imageData.set(i,j,imageData.get(i,j)-mean.get(0,j));
        }
    }
    //imageData.print("Centered around the mean: Image Data");

    //Covariance matrix
    Matrix covariance = imageData.cov();
    //covariance.print("CoVariance Matrix");

    Matrix eigenVectorMatrix=imageData;

    //Compute eigenvalues and sort into descending order
    double *eigenValues;
    eigenVectorMatrix.eigenSystem(eigenValues);
    Matrix eigenValueMatrix(1,col,eigenValues,"Eigen Values");
    eigenValueMatrix.print();
    eigenVectorMatrix.print("Eigen Vectors");

    //Sort the eigenvalues in descending order
    Matrix indices(1,col,"Indices");




/*
    double m[] = {2, 1, 0, 2, 1, 2, 1, 0, 0, 1, 3, 1, 2, 0, 1, 3};
//    double z[] =  {2.2615, -0.0923, 0, 0,  -0.0923, 1.1829, 0.8958, 0 , 0, 0.8958, 5.5556, 3.0000 , 0, 0, 3.0000, -1.0000};
    double b[] = {3, 5, 7, 11, 1, 2, 3, 4};

    Matrix x(4, 4, m, "M");
//    Matrix h(4, 4, z, "H");
    Matrix emptyMatrix(0, 0, "Empty Matrix");
    Matrix y;
    Matrix B(2, 4, b, "B");

    y = x;
    y.print("before");
    y.transposeSelf();
    y.print("after");

    double *d;

    y.eigenSystem(d);
    
    Matrix dd(1, 4, d, "D");  // convert double * to matrix
    dd.print("eigen values");

    y.print("eigen vectors");

    x.print();
    B = B.transpose();
    x.solve(B);
    x.print("inverse");
    B.print("ans");

    x.inverse();
    x.print("re-inverse");*/
//    x.LU();
//    x.print("original");

    return 0;
}


