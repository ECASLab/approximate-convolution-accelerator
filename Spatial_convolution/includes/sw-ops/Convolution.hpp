/*
 * Copyright 2021
 * Author: Alejandro Rodriguez Figueroa <alejandrorf@estudiantec.cr>
 * Supervisor: Luis G. Leon-Vega <lleon95@estudiantec.cr>
 */
#include <iostream>
#pragma once

namespace ama {
namespace sw {

template <typename T, int M, int N, int k>
/**
 * @brief Matrix spatial convolution
 * It performs the convolution of two matrices.
 * @param kernel Matrix use as kernel
 * @param image Matrix padd for a kernel size k 
 * @param imagecamb Matrix with the result of the convolution
 */
void conv(const T kernel[k][k],const T image[M+(k-1)][N+(k-1)], T imagecamb[M+(k-1)][N+(k-1)]) {
	int start = k/2;
	T suma = 0;
//	std::cout<< start<< std::endl; 
  for (int i = start; i < M+start; i++) {
    for (int j = start; j < N+start; j++) {
		for (int e = 0; e < k; e++) {
			for (int r = 0; r < k; r++) {
				suma = kernel[e][r] * image[i-start+e][j-start+r] + suma;
				//if(i == 2 && j == 2){
				//	std::cout<< "Posicion :" << "(" << e << "  , " << r << ")" << "(" << i-start+e << "  , " << j-start+r << ")" << std::endl << kernel[e][r] << " * " << image[i-start+e][j-start+r] << " = " << suma << std::endl;
				//}
    		}
    	}
    	imagecamb[i][j]=suma;
    	suma = 0;
    }
  }
}
};
};
