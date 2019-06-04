/*
Karina Erika dos Santos
Trabalho da disciplina de Processamento de Imagem
Programa de Pós-Graduação em Ciência da Computação
Prof.: Aristófanes Correa
Técnica de quantização Não uniforme
*/

#include "pch.h"
#include<opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>
#include <cstdlib>
#include<math.h>
#include <opencv2/core/types.hpp>
#include <opencv2/core/types_c.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp> 
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;



void quantiza_Nuniforme(int bits_resultado, Mat img) {
	int i, j, min = 300, max = 0, t, aux;
	double k;
	int bits = 8;// pega os bits da imagem carregada
	bits = pow(2, bits);

	bits_resultado = pow(2, bits_resultado);

	//pega o minimo e maximo da imagem
	for (i = 0; i < img.cols; i++) {
		for (j = 0; j < img.rows; j++) {
			k = img.at<uchar>(i, j);
			if (k < min)min = k;//minimo
			if (k > max)max = k;//maximo
		}
	}

	//calcula a quantização
	if (bits != bits_resultado) {
		for (i = 0; i < img.cols; i++) {
			for (j = 0; j < img.rows; j++) {
				k = img.at<uchar>(i, j);
				k = (bits_resultado - 1) * (k - min) / (max - min);
				t = round(k); //arredonda o valor da formula da quantização
				aux = max / bits_resultado;
				img.at<uchar>(i, j) = t * aux;
			}
		}
	}

	namedWindow("Quantizada", WINDOW_AUTOSIZE);
	imshow("Quantizada", img);
	imwrite("../data/lenaQuantizada.png", img); //Salva a imagem

	waitKey(0);
}

int main()
{
	Mat img;
	int bits_resultado;
	String imageName("./data/lena.jpg");
	cout << "\nDigite o numero de bits para a nova imagem: ";
	cin >> bits_resultado;

	img = imread(imageName, IMREAD_GRAYSCALE);


	namedWindow("Original", WINDOW_AUTOSIZE);
	imshow("Original", img);

	quantiza_Nuniforme(bits_resultado, img); //chamada da função quantização
	return 0;
}