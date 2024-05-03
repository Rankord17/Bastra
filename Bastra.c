#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <stdbool.h>

#define max_cards 52
#define max_ranks 13

typedef struct { // Creates a structure with two components: Rank and Suit
 int rank;
 int suit;
} Card;

enum suit {Hearts = 3, Diamonds, Clubs, Spades}; // Enumirates the suits

void initialize(Card initial_deck[max_cards]);
void shuffle(Card shuffled_deck[max_cards]);

int player_distribution(int card_number, Card shuffled_deck[max_cards], Card player_one[4], Card player_two[4], Card player_three[4], Card player_four[4]); // For distributing cards among players +

int board_distribution(int card_number, Card board_cards[20], Card shuffled_deck[max_cards]); // Distributes cards on the board

void board_display(Card board_cards[20]); // Displays the cards that on the board

void player_display(int player, Card player_cards[4]); // Displays the cards that the player have
void adviced_display(Card adviced); // Displays the adviced card
void removing_player_card(int player_card_index, Card player_cards[4]); // Removes the card from the player's deck
void removing_board_card(int board_card_index, Card board_cards[20]); // Removes the card from the board
int which_action(Card player_card, Card board_cards[20]); // Checks which action must be done depending on the card (take from or put on the board)
int bastra_check(int points, int turn, Card board_cards[20]); // Checks if there's a Bastra on the board
int bonus_points(Card b_player_card); // Checks if the played card is the bonus cards that give additional points
int adviced_card(Card player_cards[4], Card board_cards[20]);


int main(void) {
    Card initial_deck[max_cards], shuffled_deck[max_cards], player_one[4], player_two[4], player_three[4], player_four[4], board_cards[20];
    int turn = 0, player_card_index, player1_points = 0, player2_points = 0, player3_points = 0, player4_points = 0, winner = 0;
    printf(" ...Welcome to the Bastra game... \n");
    sleep(1);
    printf(" ...Let's begin the game... \n");
    sleep(1);
    initialize(initial_deck);
    while (true) {
        int round = 1, card_number = 0;
        printf("Shuffling the deck...\n");
        sleep(1.5);
        shuffle(shuffled_deck);
        for (int board_reset = 0; board_reset <= 19; board_reset++){
            board_cards[board_reset].suit = 0;
            board_cards[board_reset].rank = 0;
        }
        card_number = board_distribution(card_number, board_cards, shuffled_deck);
        printf("Dealing cards on the board...");

        while (true) {
            printf("\n");
            sleep(1);
            printf("Distributing cards among players...\n");
            sleep(2);
            int use = 1;
            card_number = player_distribution(card_number, shuffled_deck, player_one, player_two, player_three, player_four);
            while (true){
                int action = 0;
                turn = turn % 4 + 1;

                board_display(board_cards); // For showing the state of the game
                sleep(1);
                switch(turn) {
                    case 1: player_display(turn, player_one);
                    break;
                    case 2: player_display(turn, player_two);
                    break;
                    case 3: player_display(turn, player_three);
                    break;
                    case 4: player_display(turn, player_four);
                    break;
                }
                while (true) {
                    int adviced_c;
                    switch (turn) {
                        case 1:
                        {
                            adviced_c = adviced_card(player_one, board_cards);
                            adviced_display(player_one[adviced_c]);
                        }
                        break;
                        case 2:
                        {
                            adviced_c = adviced_card(player_two, board_cards);
                            adviced_display(player_two[adviced_c]);
                        }
                        break;
                        case 3:
                        {
                            adviced_c = adviced_card(player_three, board_cards);
                            adviced_display(player_three[adviced_c]);
                        }
                        break;
                        case 4:
                        {
                            adviced_c = adviced_card(player_four, board_cards);
                            adviced_display(player_four[adviced_c]);
                        }
                        break;
                    }
                    sleep(1);
                    printf("\nWhich card do you want to play? Enter the index:");
                    scanf("%i", &player_card_index);
                    player_card_index--;

                    if (player_card_index >= 4)
                        printf("The card in the entered index doesn't exist. Please, try to enter the index again.\n");
                    else if (turn == 1 && player_one[player_card_index].suit != 0 && player_one[player_card_index].rank != 0)
                        break;
                    else if (turn == 2 && player_two[player_card_index].suit != 0 && player_two[player_card_index].rank != 0)
                        break;
                    else if (turn == 3 && player_three[player_card_index].suit != 0 && player_three[player_card_index].rank != 0)
                        break;
                    else if (turn == 4 && player_four[player_card_index].suit != 0 && player_four[player_card_index].rank != 0)
                        break;
                    else
                        printf("The card in the entered index doesn't exist. Please, try to enter the index again.\n");
                }

                switch(turn) {
                    case 1: action = which_action(player_one[player_card_index], board_cards);
                    break;
                    case 2: action = which_action(player_two[player_card_index], board_cards);
                    break;
                    case 3: action = which_action(player_three[player_card_index], board_cards);
                    break;
                    case 4: action = which_action(player_four[player_card_index], board_cards);
                    break;
                    }
                    if (action == 0){ // If player puts the card on the board
                        for (int index = 0; index <= 19; index++) {
                            if (board_cards[index].rank == 0) {
                                switch (turn) {
                                    case 1: { board_cards[index].suit = player_one[player_card_index].suit;
                                        board_cards[index].rank = player_one[player_card_index].rank; }
                                    break;
                                    case 2: { board_cards[index].suit =player_two[player_card_index].suit;
                                        board_cards[index].rank = player_two[player_card_index].rank; }
                                    break;
                                    case 3: { board_cards[index].suit =player_three[player_card_index].suit;
                                        board_cards[index].rank = player_three[player_card_index].rank; }
                                    break;
                                    case 4: { board_cards[index].suit = player_four[player_card_index].suit;
                                        board_cards[index].rank = player_four[player_card_index].rank; }
                                    break;
                                    }
                                    break;
                                }
                            }
                        }
                    else if (action == 1) {// For checking if the ranks of the player card and the board card are same
                        for (int index = 0; index <= 19; index++) {
                            switch(turn) {
                                case 1:
                                {
                                    if (board_cards[index].rank == player_one[player_card_index].rank) {
                                        removing_board_card(index, board_cards);
                                        player1_points++;
                                    }
                                }
                                break;
                                case 2:
                                {
                                    if (board_cards[index].rank == player_two[player_card_index].rank) {
                                        removing_board_card(index, board_cards);
                                        player2_points++;
                                    }
                                }
                                break;
                                case 3:
                                {
                                    if (board_cards[index].rank == player_three[player_card_index].rank) {
                                        removing_board_card(index, board_cards);
                                        player3_points++;
                                    }
                                }
                                break;
                                case 4:
                                {
                                    if (board_cards[index].rank == player_four[player_card_index].rank) {
                                        removing_board_card(index, board_cards);
                                        player4_points++;
                                    }
                                }
                                break;
                            }
                        }
                    }

                    else if (action == 2) {// Checks if the sum of 2 ranks of the board cards are equal to the rank of the player card
                        int done = 0;
                        for (int difference = 1; difference <= 19; difference++) {
                            if (turn == 1) {
                                for (int index = 0; index <= 19; index++) {
                                    if (index + difference <= 19) {
                                        if (player_one[player_card_index].rank == board_cards[index].rank + board_cards[index + difference].rank) {
                                            removing_board_card(index, board_cards);
                                            removing_board_card(index + difference, board_cards);

                                        done += 1;
                                    }
                                }
                            }
                        }
                        else if (turn == 2) {
                            for (int index = 0; index <= 19; index++) {
                                if (index + difference <= 19) {
                                    if (player_two[player_card_index].rank == board_cards[index].rank + board_cards[index + difference].rank) {
                                        removing_board_card(index, board_cards);
                                        removing_board_card(index + difference,board_cards);

                                        done += 1;
                                    }
                                }
                            }
                        }
                        else if (turn == 3) {
                            for (int index = 0; index <= 19; index++) {
                                if (index + difference <= 19) {
                                    if (player_three[player_card_index].rank == board_cards[index].rank + board_cards[index + difference].rank) {
                                        removing_board_card(index, board_cards);
                                        removing_board_card(index + difference, board_cards);

                                        done += 1;
                                    }
                                }
                            }
                        }
                        else if (turn == 4) {
                            for (int index = 0; index <= 19; index++) {
                                if (index + difference <= 19) {
                                    if (player_four[player_card_index].rank == board_cards[index].rank + board_cards[index + difference].rank) {
                                        removing_board_card(index, board_cards);
                                        removing_board_card(index + difference, board_cards);

                                        done += 1;
                                    }
                                }
                            }
                        }
                    }

                    switch(turn) // For giving points to the player depending on how many cards he has taken
                    {
                        case 1: player1_points += done;
                        break;
                        case 2: player2_points += done;
                        break;
                        case 3: player3_points += done;
                        break;
                        case 4: player4_points += done;
                        break;
                    }
                }
                else if (action == 3) {// If the card with the suit "Jack" was played
                    for (int b_index = 0; b_index <= 19; b_index++){ // Removes all board cards
                        removing_board_card(b_index, board_cards);
                    }

                    switch(turn) // Gives the player 1 point for using "Jack"
                    {
                        case 1: player1_points++;
                        break;
                        case 2: player2_points++;
                        break;
                        case 3: player3_points++;
                        break;
                        case 4: player4_points++;
                        break;
                    }
                }

                if (action != 0) {// Gives additional points if the played card was "2 Clubs" or "10 Diamonds"
                    switch (turn)
                    {
                        case 1: player1_points += bonus_points(player_one[player_card_index]);
                        break;
                        case 2: player2_points += bonus_points(player_two[player_card_index]);
                        break;
                        case 3: player3_points += bonus_points(player_three[player_card_index]);
                        break;
                        case 4: player4_points += bonus_points(player_four[player_card_index]);
                        break;
                    }
                }
                if (action != 3) {
                    switch(turn) // Checks if there's a Bastra on the board
                    {
                        case 1: player1_points += bastra_check(player1_points, turn, board_cards);
                        break;
                        case 2: player2_points += bastra_check(player2_points, turn, board_cards);
                        break;
                        case 3: player3_points += bastra_check(player3_points, turn, board_cards);
                        break;
                        case 4: player4_points += bastra_check(player4_points, turn, board_cards);
                        break;
                    }
                }
                // Removing card from player
                switch (turn)
                {
                    case 1: removing_player_card(player_card_index, player_one);
                    break;
                    case 2: removing_player_card(player_card_index, player_two);
                    break;
                    case 3: removing_player_card(player_card_index, player_three);
                    break;
                    case 4: removing_player_card(player_card_index, player_four);
                    break;
                }
                if (use == 16) // Checks if round has been ended or not
                    break;
                else
                    use++;
            }

            if (round == 3) // Checks if all 52 cards has been used or not
                break;
            else
                round++;
        }
        printf("Points: Player 1: %i | Player 2: %i | Player 3: %i | Player 4: %i\n", player1_points, player2_points, player3_points, player4_points);
        sleep(2);
        // For checking if there's a winner
        if (player1_points >= 100) {
            winner = 1;
            break;
        }
        else if (player2_points >= 100) {
            winner = 2;
            break;
        }
        else if (player3_points >= 100) {
            winner = 3;
            break;
        }
        else if (player4_points >= 100) {
            winner = 4;
            break;
        }
        else {// If there's no winner, then the cards will be shuffled again
            printf("All cards has been used, clearing the board and reshuffling the cards...\n");
            sleep(1);
        }
    }

    switch(winner)
    {
        case 1: printf("Player 1 has won. Congratulations!\n");
        break;
        case 2: printf("Player 2 has won. Congratulations!\n");
        break;
        case 3: printf("Player 3 has won. Congratulations!\n");
        break;
        case 4: printf("Player 4 has won. Congratulations!\n");
        break;
    }
}
// Initializes the deck
void initialize(Card initial_deck[max_cards]) {
    int cards_number = 0;
    for (int suits = 3; suits <= 6; suits++) {
        for (int ranks = 1; ranks <= 13; ranks++) {
            switch(suits)
            {
                case 3: initial_deck[cards_number].suit = Hearts;
                break;
                case 4: initial_deck[cards_number].suit = Diamonds;
                break;
                case 5: initial_deck[cards_number].suit = Clubs;
                break;
                case 6: initial_deck[cards_number].suit = Spades;
                break;
            }
            initial_deck[cards_number].rank = ranks;
            cards_number++;
        }
    }
}
// Shuffles the deck
void shuffle(Card shuffled_deck[max_cards]) {
    int hearts_count = max_ranks, diamonds_count = max_ranks, clubs_count = max_ranks, spades_count = max_ranks, ranks_list[max_cards];
    int s_suit, s_rank;
    for (int si = 0; si <= 51; si++) {// Gives a value for all cards to avoid duplicates in shuffling
        shuffled_deck[si].suit = 30;
        shuffled_deck[si].rank = 30;
    }
    for (int i = 0; i <= 51; i++) // Gives a value for the elements of the array to avoid errors
        ranks_list[i] = 22;

    srand(time(NULL));
    for (int card_number = 0; card_number <= 51; card_number++) {
        while (true) {
            int permission = 1; // Required to check if the selected pair of suit and rank has not been selected before
            while (true) {
                int accept = 1;
                s_suit = rand() % 4 + 3;

                if (s_suit == Hearts && hearts_count == 0)
                    accept--;
                else if (s_suit == Diamonds && diamonds_count == 0)
                    accept--;
                else if (s_suit == Clubs && clubs_count == 0)
                    accept--;
                else if (s_suit == Spades && spades_count == 0)
                    accept--;

                if (accept == 1) {
                    switch(s_suit)
                    {
                        case Hearts: hearts_count--;
                        break;
                        case Diamonds: diamonds_count--;
                        break;
                        case Clubs: clubs_count--;
                        break;
                        case Spades: spades_count--;
                        break;
                    }
                    break;
                }
            }
            while (true) {
                int accept = 1, number_count = 0;
                s_rank = rand() % 13 + 1;
                for (int i = 0; i <= max_cards; i++) {
                    if (ranks_list[i] == s_rank)
                    number_count++;
                }
               if (number_count >= 4)
                    accept--;
                if (accept == 1) {
                    ranks_list[card_number] = s_rank;
                    break;
                }
            }

            for (int si_check = 0; si_check <= 51; si_check++) {
                if (shuffled_deck[si_check].suit == s_suit && shuffled_deck[si_check].rank == s_rank) {// Checks if there's no pair of rank and suit that's been chosen before
                    switch(s_suit)// If there's a duplicate, then the count of the suit is returned back
                    {    
                        case 3: hearts_count++;
                        break;
                        case 4: diamonds_count++;
                        break;
                        case 5: clubs_count++;
                        break;
                        case 6: spades_count++;
                        break;
                    }
                    ranks_list[card_number] = 22; // Also, the rank is being removed from the list if there's a duplicate 
                    permission = 0;
                }
            }

            if (permission == 1) {// If there's no duplicate, then the card is accepted
                shuffled_deck[card_number].suit = s_suit;
                shuffled_deck[card_number].rank = s_rank;
                break;
            }
        }
    }
}
// Distributes cards among players
int player_distribution(int card_number, Card shuffled_deck[max_cards], Card player_one[4], Card player_two[4], Card player_three[4], Card player_four[4]) {
    for (int p = 1; p <= 4; p++) {
        for (int card_index = 0; card_index <= 3; card_index++) {
            switch (p) 
            {
                case 1:
                {
                    player_one[card_index].suit = shuffled_deck[card_number].suit;
                    player_one[card_index].rank = shuffled_deck[card_number].rank;
                }
                break;
                case 2:
                {
                    player_two[card_index].suit = shuffled_deck[card_number].suit;
                    player_two[card_index].rank = shuffled_deck[card_number].rank;
                }
                break;
                case 3:
                {
                    player_three[card_index].suit = shuffled_deck[card_number].suit;
                    player_three[card_index].rank = shuffled_deck[card_number].rank;
                }
                break;
                case 4:
                {
                    player_four[card_index].suit = shuffled_deck[card_number].suit;
                    player_four[card_index].rank = shuffled_deck[card_number].rank;
                }
                break;
            }
            card_number++;
        }
    }
    return card_number;
}

// Distributes cards on the board
int board_distribution(int card_number, Card board_cards[20], Card shuffled_deck[max_ranks]) {
    if (board_cards[0].rank == 0) {
        for (int b = 0; b <= 3; b++) {
            board_cards[b].suit = shuffled_deck[card_number].suit;
            board_cards[b].rank = shuffled_deck[card_number].rank;
            card_number++;
        }
    }
    return card_number;
}

// Displays the cards that on the board
void board_display(Card board_cards[20]) {
    printf("\nCards on the board: ");
    for (int board_show = 0; board_show <= 19; board_show++) {
        if (board_cards[board_show].rank != 0) {
            switch(board_cards[board_show].rank)
            {
                case 1: printf("A");
                break;
                case 11: printf("J");
                break;
                case 12: printf("Q");
                break;
                case 13: printf("K");
                break;
                default: printf("%i", board_cards[board_show].rank);
                break;
            }
        }
        switch(board_cards[board_show].suit)
        {
            case 3: printf("\u2665 ");
            break;
            case 4: printf("\u2666 ");
            break;
            case 5: printf("\u2663 ");
            break;
            case 6: printf("\u2660 ");
            break;
        }
    }
    printf("\n");
}

// Displays the cards that the player have
void player_display(int player, Card player_cards[4]) {
    printf("Player %i cards: ", player);
    for (int show = 0; show <= 3; show++) {
        if (player_cards[show].rank != 0) {
            switch(player_cards[show].rank)
            {
                case 1: printf("A");
                break;
                case 11: printf("J");
                break;
                case 12: printf("Q");
                break;
                case 13: printf("K");
                break;
                default: printf("%i", player_cards[show].rank);
                break;
            }
        }
        switch(player_cards[show].suit)
        {
            case 3: printf("\u2665 ");
            break;
            case 4: printf("\u2666 ");
            break;
            case 5: printf("\u2663 ");
            break;
            case 6: printf("\u2660 ");
            break;
        }
    }
}

// Displays the adviced card
void adviced_display(Card adviced) {
    printf("\nThe adviced card is ");
    switch(adviced.rank)
    {
        case 1: printf("A");
        break;
        case 11: printf("J");
        break;
        case 12: printf("Q");
        break;
        case 13: printf("K");
        break;
        default: printf("%i", adviced.rank);
        break;
    }

    switch(adviced.suit)
    {
        case 3: printf("\u2665.");
        break;
        case 4: printf("\u2666.");
        break;
        case 5: printf("\u2663.");
        break;
        case 6: printf("\u2660.");
        break;
    }
}

// Removes the card from the player's deck
void removing_player_card(int player_card_index, Card player_cards[4]) {
    for (player_card_index; player_card_index <= 3; player_card_index++) {
        player_cards[player_card_index].suit = player_cards[player_card_index + 1].suit;
        player_cards[player_card_index].rank = player_cards[player_card_index + 1].rank;
    }
    player_card_index -= 1;
    player_cards[player_card_index].suit = 0;
    player_cards[player_card_index].rank = 0;
}

// Removes the card from the board
void removing_board_card(int board_card_index, Card board_cards[20]) {
    board_cards[board_card_index].suit = 0;
    board_cards[board_card_index].rank = 0;
}

// Checks which action must be done depending on the card (take from or put on the board)
int which_action(Card player_card, Card board_cards[20]) {
    int action = 0;
    if (player_card.rank != 11) {
        for (int index = 0; index <= 19; index++) {
            if (player_card.rank == board_cards[index].rank) // For checking if the ranks of the player card and the board card are same
                action = 1;
        }
        for (int difference = 1; difference <= 19; difference++) {// For checking if the sum of 2 ranks of the board cards are equal to the rank of the player card
            for (int index = 0; index <= 19; index++) {
                if (index + difference <= 19) {
                    if (player_card.rank == board_cards[index].rank + board_cards[index + difference].rank && board_cards[index + difference].rank != 0)
                        action = 2;
                }
            }
        }
    }
    else {// In case if "Jack" was played and the board is clear, then the Jack must stay there
        int no_c = 0;
        for (int i = 0; i <= 19; i++) {
            if (board_cards[i].rank == 0 && board_cards[i].suit == 0)
                no_c++;
        }
        if (no_c != 20)
            action = 3;
    }

    return action;
}

// Checks if there's a Bastra on the board
int bastra_check(int points, int turn, Card board_cards[20]) {
    int no_cards = 0;
    for (int i = 0; i <= 19; i++){ // Checks if there's a Bastra
        if (board_cards[i].suit == 0 && board_cards[i].rank == 0)
            no_cards++;
    }
        if (no_cards == 20) {
            printf("\t ========= BASTRA =========\n");
            sleep(1);
            printf("10 additional points to the player %i.\n", turn);
            sleep(1);
            points = 10;
        }
        else
            points = 0;

        return points;
}

// Checks if the played card is the bonus cards that give additional points
int bonus_points(Card b_player_card) {
    int b_points;
    if (b_player_card.suit == Clubs && b_player_card.rank == 2)
        b_points = 1;
    else if (b_player_card.suit == Diamonds && b_player_card.rank == 10)
        b_points = 2;
    else
        b_points = 0;
    return b_points;
}

// Gives advice to the player which card to play
int adviced_card(Card player_cards[4], Card board_cards[20]){
    int adviced_index = -1, action_for_advice, baa = 0;
    for (int player_index = 0; player_index <= 3; player_index++) {
        action_for_advice = which_action(player_cards[player_index], board_cards);
        if (action_for_advice != 0 && player_cards[player_index].rank != 0 && baa <= action_for_advice) {
            adviced_index = player_index;
            baa = action_for_advice;
        }
    }
    if (adviced_index == -1) {
        while (true) {
            adviced_index = rand() % 4;
            if (player_cards[adviced_index].rank != 0)
                break;
        }
    }
    return adviced_index;
}