/* sampling.c
 * Robert Allen
 * CPSC 352
 * 5/2021
 * Program that uses prior and rejection sampling in order to answer three queries
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define RANDOMRANGE .99

void Course(int *shortCourse, int *longCourse, float *sample);
void Weather(int *coldWetWeather, int *niceWeather, int *hotWeather, float *sample);
void HarePerf(int *slowHarePerf, int *mediumHarePerf, int *fastHarePerf, int *coldWetWeather, int *niceWeather, int *hotWeather, int *shortCourse, int *longCourse, float *sample);
void TortoisePerf(int *slowTortoisePerf, int *mediumTortoisePerf, int *fastTortoisePerf, int *coldWetWeather, int *niceWeather, int *hotWeather, int *shortCourse, int *longCourse, float *sample);
void HareWin(int *slowHarePerf, int *mediumHarePerf, int *fastHarePerf, int *slowTortoisePerf, int *mediumTortoisePerf, int *fastTortoisePerf, float *hareWins);
void TortoiseWin(int *slowHarePerf, int *mediumHarePerf, int *fastHarePerf, int *slowTortoisePerf, int *mediumTortoisePerf, int *fastTortoisePerf, float *tortoiseWins);

void main() {
	int shortCourse;
	int longCourse;
	int coldWetWeather;
	int niceWeather;
	int hotWeather;
	int slowHarePerf;
	int mediumHarePerf;
	int fastHarePerf;
	int slowTortoisePerf;
	int mediumTortoisePerf;
	int fastTortoisePerf;
	float hareWins;
	float winTotal = 0;
	float sample;
	int i, j, k;
	int n = 1000000;
	srand(time(NULL));
	//Question 1
	for (i = 0; i < n; i++) {
		sample = (float)((double)rand()/(double)(RAND_MAX/RANDOMRANGE));
		Course(&shortCourse, &longCourse, &sample);
		sample = (float)((double)rand()/(double)(RAND_MAX/RANDOMRANGE));
		Weather(&coldWetWeather, &niceWeather, &hotWeather, &sample);
		sample = (float)((double)rand()/(double)(RAND_MAX/RANDOMRANGE));
		HarePerf(&slowHarePerf, &mediumHarePerf, &fastHarePerf, &coldWetWeather, &niceWeather, &hotWeather, &shortCourse, &longCourse, &sample);
		sample = (float)((double)rand()/(double)(RAND_MAX/RANDOMRANGE));
		TortoisePerf(&slowTortoisePerf, &mediumTortoisePerf, &fastTortoisePerf, &coldWetWeather, &niceWeather, &hotWeather, &shortCourse, &longCourse, &sample);
		HareWin(&slowHarePerf, &mediumHarePerf, &fastHarePerf, &slowTortoisePerf, &mediumTortoisePerf, &fastTortoisePerf, &hareWins);
		winTotal += hareWins;
	}
	winTotal = winTotal / n;
	printf("General percentage of hare winning: %.2f\n", winTotal);

	//Question 2
	int notRejected = n;
	winTotal = 0;
	for (j = 0; j < n; j++) {
		sample = (float)((double)rand()/(double)(RAND_MAX/RANDOMRANGE));
		Course(&shortCourse, &longCourse, &sample);
		sample = (float)((double)rand()/(double)(RAND_MAX/RANDOMRANGE));
		Weather(&coldWetWeather, &niceWeather, &hotWeather, &sample);
		if (coldWetWeather == 0) {
			notRejected--;
			continue;
		}
		else {
			sample = (float)((double)rand()/(double)(RAND_MAX/RANDOMRANGE));
			HarePerf(&slowHarePerf, &mediumHarePerf, &fastHarePerf, &coldWetWeather, &niceWeather, &hotWeather, &shortCourse, &longCourse, &sample);
			sample = (float)((double)rand()/(double)(RAND_MAX/RANDOMRANGE));
			TortoisePerf(&slowTortoisePerf, &mediumTortoisePerf, &fastTortoisePerf, &coldWetWeather, &niceWeather, &hotWeather, &shortCourse, &longCourse, &sample);
			HareWin(&slowHarePerf, &mediumHarePerf, &fastHarePerf, &slowTortoisePerf, &mediumTortoisePerf, &fastTortoisePerf, &hareWins);
			winTotal += hareWins;
		}
	}
	winTotal = winTotal / notRejected;
	printf("%d\n", notRejected);
	printf("Win percentage given cold and wet conditions: %.2f\n", winTotal);

	//Question 3
	winTotal = 0;
	notRejected = n;
	float tortoiseWins;
	int totalColdWet = 0, totalNice = 0, totalHot = 0;
	for (k = 0; k < n; k++) {
		sample = (float)((double)rand()/(double)(RAND_MAX/RANDOMRANGE));
		Course(&shortCourse, &longCourse, &sample);
		if (shortCourse == 0) {
			notRejected--;
			continue;
		}
		else {
			sample = (float)((double)rand()/(double)(RAND_MAX/RANDOMRANGE));
			Weather(&coldWetWeather, &niceWeather, &hotWeather, &sample);
			if (coldWetWeather == 1) {
				totalColdWet++;
			}
			else if (niceWeather == 1) {
				totalNice++;
			}
			else {
				totalHot++;
			}
			sample = (float)((double)rand()/(double)(RAND_MAX/RANDOMRANGE));
			HarePerf(&slowHarePerf, &mediumHarePerf, &fastHarePerf, &coldWetWeather, &niceWeather, &hotWeather, &shortCourse, &longCourse, &sample);
			sample = (float)((double)rand()/(double)(RAND_MAX/RANDOMRANGE));
			TortoisePerf(&slowTortoisePerf, &mediumTortoisePerf, &fastTortoisePerf, &coldWetWeather, &niceWeather, &hotWeather, &shortCourse, &longCourse, &sample);
			TortoiseWin(&slowHarePerf, &mediumHarePerf, &fastHarePerf, &slowTortoisePerf, &mediumTortoisePerf, &fastTortoisePerf, &tortoiseWins);
			winTotal += tortoiseWins;
		}
	}
	tortoiseWins = tortoiseWins * notRejected;
	int totalTortoiseWins = round(tortoiseWins);
	float percentColdWet = (totalColdWet / tortoiseWins) / 2;
	float percentNice = (totalNice / tortoiseWins) / 2;
	float percentHot = (totalHot / tortoiseWins) / 2;
	printf("Probability Distrubition of weather given a tortoise win on the short course: <%.2f, %.2f, %.2f>\n", percentColdWet, percentNice, percentHot);
}




void Course(int *shortCourse, int *longCourse, float *sample) {
	if (*sample < .5) {
		*shortCourse = 1;
		*longCourse = 0;
	}
	else {
		*shortCourse = 0;
		*longCourse = 1;
	}
}

void Weather(int *coldWetWeather, int *niceWeather, int *hotWeather, float *sample) {
	if (*sample < .3) {
		*coldWetWeather = 1;
		*niceWeather = 0;
		*hotWeather = 1;
	}
	else if (*sample >= .3 && *sample < .5) {
		*coldWetWeather = 0;
		*niceWeather = 1;
		*hotWeather = 0;
	}
	else {
		*coldWetWeather = 0;
		*niceWeather = 0;
		*hotWeather = 1;
	}
}

void HarePerf(int *slowHarePerf, int *mediumHarePerf, int *fastHarePerf, int *coldWetWeather, int *niceWeather, int *hotWeather, int *shortCourse, int *longCourse, float *sample) {
	if (*shortCourse == 1) {
		if (*coldWetWeather == 1) {
			if (*sample < .5) {
				*slowHarePerf = 1;
				*mediumHarePerf = 0;
				*fastHarePerf = 0;
			}
			else if (*sample >= .5 && *sample < .8) {
				*slowHarePerf = 0;
				*mediumHarePerf = 1;
				*fastHarePerf = 0;
			}
			else {
				*slowHarePerf = 0;
				*mediumHarePerf = 0;
				*fastHarePerf = 1;
			}
		}
		else if (*hotWeather == 1) {
			if (*sample < .1) {
				*slowHarePerf = 1;
				*mediumHarePerf = 0;
				*fastHarePerf = 0;
			}
			else if (*sample >= .1 && *sample < .3) {
				*slowHarePerf = 0;
				*mediumHarePerf = 1;
				*fastHarePerf = 0;
			}
			else {
				*slowHarePerf = 0;
				*mediumHarePerf = 0;
				*fastHarePerf = 1;
			}
		}
		else {
			if (*sample < 0) {
				*slowHarePerf = 1;
				*mediumHarePerf = 0;
				*fastHarePerf = 0;
			}
			else if (*sample >= 0 && *sample < .2) {
				*slowHarePerf = 0;
				*mediumHarePerf = 1;
				*fastHarePerf = 0;
			}
			else {
				*slowHarePerf = 0;
				*mediumHarePerf = 0;
				*fastHarePerf = 1;
			}
		}
	}
	else {
		if (*coldWetWeather == 1) {
			if (*sample < .7) {
				*slowHarePerf = 1;
				*mediumHarePerf = 0;
				*fastHarePerf = 0;
			}
			else if (*sample >= .7 && *sample < .9) {
				*slowHarePerf = 0;
				*mediumHarePerf = 1;
				*fastHarePerf = 0;
			}
			else {
				*slowHarePerf = 0;
				*mediumHarePerf = 0;
				*fastHarePerf = 1;
			}
		}
		else if (*hotWeather == 1) {
			if (*sample < .2) {
				*slowHarePerf = 1;
				*mediumHarePerf = 0;
				*fastHarePerf = 0;
			}
			else if (*sample >= .2 && *sample < .6) {
				*slowHarePerf = 0;
				*mediumHarePerf = 1;
				*fastHarePerf = 0;
			}
			else {
				*slowHarePerf = 0;
				*mediumHarePerf = 0;
				*fastHarePerf = 1;
			}
		}
		else {
			if (*sample < .1) {
				*slowHarePerf = 1;
				*mediumHarePerf = 0;
				*fastHarePerf = 0;
			}
			else if (*sample >= .1 && *sample < .4) {
				*slowHarePerf = 0;
				*mediumHarePerf = 1;
				*fastHarePerf = 0;
			}
			else {
				*slowHarePerf = 0;
				*mediumHarePerf = 0;
				*fastHarePerf = 1;
			}
		}
	}
}

void TortoisePerf(int *slowTortoisePerf, int *mediumTortoisePerf, int *fastTortoisePerf, int *coldWetWeather, int *niceWeather, int *hotWeather, int *shortCourse, int *longCourse, float *sample) {
	if (*shortCourse == 1) {
		if (*coldWetWeather == 1) {
			if (*sample < .2) {
				*slowTortoisePerf = 1;
				*mediumTortoisePerf = 0;
				*fastTortoisePerf = 0;
			}
			else if (*sample >= .2 && *sample < .5) {
				*slowTortoisePerf = 0;
				*mediumTortoisePerf = 1;
				*fastTortoisePerf = 0;
			}
			else {
				*slowTortoisePerf= 0;
				*mediumTortoisePerf = 0;
				*fastTortoisePerf = 1;
			}
		}
		else if (*hotWeather == 1) {
			if (*sample < .4) {
				*slowTortoisePerf = 1;
				*mediumTortoisePerf = 0;
				*fastTortoisePerf = 0;
			}
			else if (*sample >= .4 && *sample < .9) {
				*slowTortoisePerf = 0;
				*mediumTortoisePerf = 1;
				*fastTortoisePerf = 0;
			}
			else {
				*slowTortoisePerf = 0;
				*mediumTortoisePerf = 0;
				*fastTortoisePerf = 1;
			}
		}
		else {
			if (*sample < .3) {
				*slowTortoisePerf = 1;
				*mediumTortoisePerf = 0;
				*fastTortoisePerf = 0;
			}
			else if (*sample >= .3 && *sample < .8) {
				*slowTortoisePerf = 0;
				*mediumTortoisePerf = 1;
				*fastTortoisePerf = 0;
			}
			else {
				*slowTortoisePerf = 0;
				*mediumTortoisePerf = 0;
				*fastTortoisePerf = 1;
			}
		}
	}
	else {
		if (*coldWetWeather == 1) {
			if (*sample < .2) {
				*slowTortoisePerf = 1;
				*mediumTortoisePerf = 0;
				*fastTortoisePerf = 0;
			}
			else if (*sample >= .2 && *sample < .6) {
				*slowTortoisePerf = 0;
				*mediumTortoisePerf = 1;
				*fastTortoisePerf = 0;
			}
			else {
				*slowTortoisePerf = 0;
				*mediumTortoisePerf = 0;
				*fastTortoisePerf = 1;
			}
		}
		else if (*hotWeather == 1) {
			if (*sample < .2) {
				*slowTortoisePerf = 1;
				*mediumTortoisePerf = 0;
				*fastTortoisePerf = 0;
			}
			else if (*sample >= .2 && *sample < .7) {
				*slowTortoisePerf = 0;
				*mediumTortoisePerf = 1;
				*fastTortoisePerf = 0;
			}
			else {
				*slowTortoisePerf = 0;
				*mediumTortoisePerf = 0;
				*fastTortoisePerf = 1;
			}
		}
		else {
			if (*sample < .4) {
				*slowTortoisePerf = 1;
				*mediumTortoisePerf = 0;
				*fastTortoisePerf = 0;
			}
			else if (*sample >= .1 && *sample < .8) {
				*slowTortoisePerf = 0;
				*mediumTortoisePerf = 1;
				*fastTortoisePerf = 0;
			}
			else {
				*slowTortoisePerf = 0;
				*mediumTortoisePerf = 0;
				*fastTortoisePerf = 1;
			}
		}
	}
}

void HareWin(int *slowHarePerf, int *mediumHarePerf, int *fastHarePerf, int *slowTortoisePerf, int *mediumTortoisePerf, int *fastTortoisePerf, float *hareWins) {
	if (*slowHarePerf == 1) {
		if (*slowTortoisePerf == 1) {
			*hareWins = .5;
		}
		else if (*mediumTortoisePerf == 1) {
			*hareWins = .1;
		}
		else {
			*hareWins = 0;
		}
	}
	else if (*mediumHarePerf == 1) {
		if (*slowTortoisePerf == 1) {
			*hareWins = .8;
		}
		else if (*mediumTortoisePerf == 1) {
			*hareWins = .5;
		}
		else {
			*hareWins = .2;
		}
	}
	if (*fastHarePerf == 1) {
		if (*slowTortoisePerf == 1) {
			*hareWins = .9;
		}
		else if (*mediumTortoisePerf == 1) {
			*hareWins = .7;
		}
		else {
			*hareWins = .5;
		}
	}
}

void TortoiseWin(int *slowHarePerf, int *mediumHarePerf, int *fastHarePerf, int *slowTortoisePerf, int *mediumTortoisePerf, int *fastTortoisePerf, float *tortoiseWins) {
	if (*slowHarePerf == 1) {
		if (*slowTortoisePerf == 1) {
			*tortoiseWins = .5;
		}
		else if (*mediumTortoisePerf == 1) {
			*tortoiseWins = .9;
		}
		else {
			*tortoiseWins = 1;
		}
	}
	else if (*mediumHarePerf == 1) {
		if (*slowTortoisePerf == 1) {
			*tortoiseWins = .2;
		}
		else if (*mediumTortoisePerf == 1) {
			*tortoiseWins = .5;
		}
		else {
			*tortoiseWins = .8;
		}
	}
	if (*fastHarePerf == 1) {
		if (*slowTortoisePerf == 1) {
			*tortoiseWins = .1;
		}
		else if (*mediumTortoisePerf == 1) {
			*tortoiseWins = .3;
		}
		else {
			*tortoiseWins = .5;
		}
	}
}
