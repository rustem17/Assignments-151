#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

int main(void) {
	
	printf("WELCOME to the guessing game!\n");
	
	int max = 9999;
	char l1;		
	
	int count_values = 0;
        int count_num = 0;
	
	while (1) {
		printf("MENU: (s) to start a game, (n) to set a new range, or (q) to quit: \n");

	        scanf(" %c", &l1);
		
		int secret;
		secret = rand() % max;
		
		if (l1 == 's') {
			printf("The secret number is BETWEEN 0 AND %i. Guess: \n", max);
			
			int guess;
			int count = 0;

			while(scanf("%i", &guess)) {
				count++;	

				if (guess == secret) {
					printf("Correct: You TOOK %i guesses!\n", count);
					break;
				} else if (guess < secret) {
					printf("Too LOW! Guess: \n");
				} else if (guess > secret) {
					printf("Too HIGH! Guess: \n");
				}
				
			}
			count_values += count;
			count_num++;
		} else if (l1 == 'n') {
			printf("Enter a new MAXIMUM: \n");
			scanf("%i", &max);
		} else if (l1 == 'q') {
			if (count_num != 0) {
				float average = count_values / count_num;
				printf("Thanks for playing. Your guess count AVERAGE %0.2f\n", average);
			} else {
				printf("Thanks for playing. Your guess count AVERAGE 0.0\n");
			}
			return 0;
		} else {
			printf("UNRECOGNIZED command.\n");
			continue;
		}
		
		int seed = time(NULL);
		srand(seed);
	}
	
}
