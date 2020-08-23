#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define max(a,b)    (((a) > (b)) ? (a) : (b))
#define min(a,b)    (((a) < (b)) ? (a) : (b))

double time = 0.0;
double dist = 500.0;
double vel = 50.0;
double grav = 5.0;
double fuel = 120.0;
double burn = 0.0;

#define BURN_MIN 0.0
#define BURN_MAX 30.0
#define MAX_IMPACT 2.0
#define TIME_STEP 1.0

void print_head() {
	printf("%10s %10s %10s %10s %s(%g-%g)\n", "sec", "feet", "speed", "fuel", "burn", BURN_MIN, BURN_MAX);
}

void print_state() {
	printf("%10.0f %10.1f %10.1f %10.0f ", time, dist, vel, fuel);
}

double get_burn() {
	double b;
	printf("?");
	scanf("%lf", &b);
	return b;
}

void contact() {
	printf("contact\n");
	double td;
	if (burn == grav) 
		td = dist / vel;
	else
		td = (-vel + sqrt(vel*vel + dist * (10.0 - 2 * burn))) / (grav - burn);
	double v1 = vel + (grav - burn) * td;
	printf("touchdown at %g seconds.\n", time + td);
	printf("landing velocity is %g feet/sec\n", v1);
	printf("%g units of fuel remaining.\n", fuel);
	if (v1 > MAX_IMPACT) {
		printf("sorry, but you blew it!\n");
	} else if (v1 == 0.0 ) {
		printf("congratulations! a perfect landing.\n");
	} else {
		printf("good landing.\n");
	}
}

int main() {
	print_head();

	do {
		print_state();
		burn = 0.0;
		if (fuel > 0.0)
			burn = get_burn();
		else
			printf("\n");

		burn = max(min(burn, BURN_MAX), BURN_MIN);
		burn = min(burn, fuel);

		double v1 = vel + (grav - burn) * TIME_STEP;
		fuel -= burn;
		dist -= (v1 + vel) / 2;

		if (dist <= 0.0) {
			dist += (v1 + vel) / 2;  // recover
			contact();
			break;
		}

		time += TIME_STEP;
		vel = v1;
	} while (true);

	return 0;
}
